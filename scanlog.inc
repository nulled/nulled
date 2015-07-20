<?php
set_time_limit(120);

require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$mail_log   = '/var/log/mail.log';
$timenow    = time()-5;
$num_cycles = 120;
$year       = date('Y');
$i          = 0;

$mn = array('','Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec');

for ($m=0; $m < count($mn); $m++) $months[$mn[$m]] = $m;

$e = trim($_GET['e']);
$h = trim($_GET['h']);

/*
// used to test
$e = 'elitescripts2000@yahoo.com'; // good email
$e = 'sdlf@sdkfljsf.com'; // bad email domain
//$e = 'elitescripts200034534534@yahoo.com'; // bad email
mail($e, 'test', 'test');
*/

$hash = strrev(substr(md5(sha1(strrev($e))), 0, 5));

if ($e == '')    exit('No email supplied.');
if ($h == '')    exit('No hash supplied.');
if ($hash != $h) exit('Invalid email input.');

/*
Mar  6 21:27:50 planetxmail postfix/pickup[27274]: 85CAA154EF1: uid=0 from=<do_not_reply@planetxmail.com>
Mar  6 21:27:50 planetxmail postfix/cleanup[31697]: 85CAA154EF1: message-id=<20070307022750.85CAA154EF1@planetxmail.com>
Mar  6 21:27:50 planetxmail postfix/qmgr[9112]: 85CAA154EF1: from=<do_not_reply@planetxmail.com>, size=604, nrcpt=1 (queue active)
Mar  6 21:27:52 planetxmail postfix/smtp[6944]: 85CAA154EF1: to=<elitescripts2000@yahoo.com>, relay=c.mx.mail.yahoo.com[68.142.237.182]:25, delay=1.9, delays=0.01/0/0.06/1.8, dsn=2.0.0, status=sent (250 ok dirdel)
Mar  6 21:27:52 planetxmail postfix/qmgr[9112]: 85CAA154EF1: removed
// deferred
Mar  6 22:00:40 planetxmail postfix/smtp[31008]: 0A0251559E4: to=<marketing@homework-online.ws>, relay=homework-online.ws[204.92.87.177]:25, delay=32, delays=0.02/0/0.26/31, dsn=4.0.0, status=deferred (host homework-online.ws[204.92.87.177] said: 421 zeus.ghshosting.com: Service not available - closing connection (in reply to RCPT TO command))
*/

echo '<b>Confirming Email Delivery, please wait</b>';
flush();

while (true)
{
  if (! $p = @popen('/usr/bin/tail -n 250 ' . $mail_log . ' 2>&1 | grep ' . $e . ' | grep status=[beds]', 'r')) exit('ERROR1: popen()');
  $buffer = trim(fread($p, 1024000));
  pclose($p);

  if (! $buffer)
  {
    usleep(250000);
    continue;
  }

  $lines = explode("\n", $buffer);

  foreach ($lines as $line)
  {
    $line = trim($line);

    if ($line)
      $line = preg_replace("/( +)/", " ", preg_replace("/(\\t)/", " ", $line));
    else
      continue;

    unset($month, $day, $time, $server, $process, $id, $d1, $d2, $d3, $d4, $d5, $d6, $d7, $d8, $d9, $said);
    list($month, $day, $time, $server, $process, $id, $d1, $d2, $d3, $d4, $d5, $d6, $d7, $d8, $d9) = explode(' ', $line);

    $m = $months[$month];

    // construct postfix date to mysql date
    $date = (strlen($m) < 2) ? "$year-0$m" : "$year-$m";

    $date .= (strlen($day) < 2) ? "-0$day $time" : "-$day $time";

    $postfixdate = mysql_datetime_to_timestamp($date);

    //echo "$date - $postfixdate < $timenow\n";

    if ($postfixdate < $timenow) continue;

    //echo "$month, $day, $time, $server, $process, $id, $d1, $d2, $d3, $d4, $d5, d6=$d6, $d7, $d8, $d9\n";

    if ($d6 == 'status=sent' OR $d7 == 'status=sent')
    {
      exit('<br /><br /><font color="green"><b>Status OK: You should receive our delivery to your Email Inbox.</b></font><br />'."\n");
    }
    else if ($d6 == 'status=deferred' OR $d7 == 'status=deferred')
    {
      //echo 'DEFERRED = '.htmlentities($line).'<br />';
      list(, $said) = explode('said:', $line);
      echo '<br />' . htmlentities(trim($said)) . '<br /><font color="red"><b>Retrying Delivery, please wait</b></font>';
    }
    else if ($d6 == 'status=bounced' OR $d7 == 'status=bounced')
    {
      list(, $said) = explode('status=bounced', $line);
      exit('<br /><br /><font color="red"><b>' . htmlentities(trim($said)) . "</b></font><br />\n");
    }
    else
    {
      list(, $said) = explode('status=expired', $line);
      exit('<br /><br /><font color="red"><b>' . htmlentities(trim($said)) . "</b></font><br />\n");
    }

    $timenow = time();
    break;
  }

  usleep(500000);
  $i++;
  echo '.';
  flush();
  if ($i > $num_cycles) exit('<br /><br /><font color="red"><b>Unable to Confirm Delivery due to: script timeout. However, Delivery is still possible.</b></font>');
}

?>