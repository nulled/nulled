#!/usr/bin/php -q
<?php
set_time_limit(0);

$_SKIP_FORCED_REGISTER_GLOBALS = 1;

require_once('/home/nulled/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

// config vars
$postfix_queue = '/var/spool/postfix/active';
$queue_max     = 500;
$u_sleep       = 5000000; // 1 second = 1 000 000

// init vars
$numMails  = $numBad = $skipped_mails = 0;
$starttime = time();
$allemails = array();
$today     = date('F j, Y');

$firstnames = array('~firstname~','[fname]','[first_name]','[firstname]','%firstname%','{firstname}','{first_name}','{!firstname}','(firstname)','(first_name)','FNAME','FIRST_NAME','FIRSTNAME');
$lastnames  = array('~lastname~','[lname]','[last_name]','[lastname]','%lastname%','{lastname}','{last_name}','{!lastname}','(lastname)','(last_name)','LNAME','LAST_NAME','LASTNAME');

if ($argv[1] != 'cron')
  exit("ERROR: Must be run as a cronjob ... exiting\n");

if ($is_running = start_program('sendsoload.php cron'))
  exit("$is_running:sendsoload.php is already operating ... exiting\n");

if (date('G') == 0 AND date('i') < 5)
  exit("It is midnight. Give time for all cronjobs to finish ... exiting\n");

$queue_size = check_queue_size($postfix_queue);

if ($queue_size > $queue_max)
  exit("Postfix queue is full:{$queue_size}\n");

$db = new MySQL_Access('mle');

if (! $db->Query("SELECT id, subject, message, listname, crediturl FROM soloads WHERE mailed = '0' AND receipt != '' ORDER BY datesubmitted ASC LIMIT 1"))
  exit("No SOLO ADs ... exiting\n");
else
  list($id, $subject, $message, $type, $urlID) = $db->FetchRow();

$db->Query("UPDATE soloads SET mailed='1' WHERE id='$id'");

$subject = stripslashes(trim($subject));
$message = str_replace("\r\n", "\n", stripslashes(trim($message)));

$numlists = $db->Query("SELECT listname, listownerID FROM listmanager WHERE created='1' AND listtype='Safelist [openlist]' ORDER BY listname");

$lists = array();
while ($row = $db->FetchArray())
  $lists[] = $row;

// Do not mail to FAP/TAP as SoloAds are handled by sendqueue.php
$db->SelectDB('fap');
$db->Query("SELECT email FROM users WHERE verified != 0 AND email != '' ORDER BY email");
while (list($email) = $db->FetchRow())
  $allemails[] = strtolower($email);

$db->SelectDB('tap');
$db->Query("SELECT email FROM users WHERE verified != 0 AND email != '' ORDER BY email");
while (list($email) = $db->FetchRow())
  $allemails[] = strtolower($email);

$db->SelectDB('mle');
$allemails = array_unique($allemails);

foreach ($lists as $listcounter => $list)
{
  $good = $bad = 0;

  if (! $db->Ping()) exit("MySQL db connection dropped ... exiting\n");

  $db->Query("SELECT footer, adminemail FROM listmanager WHERE listname='{$list['listname']}' AND listownerID='{$list['listownerID']}' LIMIT 1");
  list($footer, $adminemail) = $db->FetchRow();
  $db->Query("SELECT programname FROM listconfig WHERE listname='{$list['listname']}' AND listownerID='{$list['listownerID']}' LIMIT 1");
  list($program_name) = $db->FetchRow();

  $emailcount = $db->Query("SELECT email, userID, username, fname, lname
                            FROM users
                            LEFT JOIN bounced ON users.email = bounced.bademail
                            WHERE users.email != ''
                            AND users.lastvacation='0000-00-00 00:00:00'
                            AND users.verified='yes'
                            AND users.vacation='0'
                            AND users.listname='{$list['listname']}'
                            AND users.listownerID='{$list['listownerID']}'
                            AND users.email NOT LIKE '%unconfirmed'
                            AND ((bounced.count < 6 AND bounced.mailboxfull < 1) OR bounced.bademail IS NULL)
                            ORDER BY email");

  $emails = array();
  while ($row = $db->FetchArray())
    $emails[] = $row;

  $footer = "______________________________________________________________
This message is not spam! You received this because you joined
the Double Opt-In List: {$list['listname']} sent by Solo AD Submit
and agreed to receive daily mail from other list members, in return
for You being able to post Your own daily offers.

[unsubscribe_link]
32811 7th Ave SW, Federal Way, WA, 98023
";

  $unsublink = 'http://planetxmail.com/mle/rl.php';
  $headers   = "From: PXM SOLO AD <do_not_reply@planetxmail.com>\n";

  if (strstr($type, 'HTMLSOLOAD'))
  {
    $headers .= "MIME-Version: 1.0\nContent-type: text/html; charset=iso-8859-1\n";
    $mess = $message . '[credit_mailer_link]' . str_replace("\n", '<br />', $footer);
  }
  else
    $mess = wordwrap($message, 75) . '[credit_mailer_link]' . wordwrap($footer, 75);

  $headers .= "X-PXM-UID: CUSERID HASH Report: http://planetxmail.com/openticket.php\n";

  foreach ($emails as $emailcounter => $e)
  {
    $e['email'] = strtolower($e['email']);

    if (in_array($e['email'], $allemails))
    {
      $skipped_mails++;
      echo "Skipping: {$e['email']}\n";
      continue;
    }

    $allemails[] = $e['email'];

    $usr = '?u=' . strrev($e['userID']) . '&v=' . strrev(substr(md5($e['userID']), 0, 5));
    $cl = create_credit_link($e['userID'], $urlID, 2);

    if (strstr($type, 'HTMLSOLOAD'))
    {
      $credlink  = '<a href="http://planetxmail.com/earn.php?' . $cl . '">** Click Here</a> to Earn 5 times the Credits from this SOLO AD.<br /><br />';
      $unsublink = '<a href="' . $unsublink . $usr . '">Click Here to Unsubscribe</a>';
      $newline   = '<br /><br />';
    }
    else
    {
      $credlink  = "** Earn 5 times the Credits from this SOLO AD by visiting:\n".'http://planetxmail.com/earn.php?' . $cl . "\n\n";
      $unsublink = "Click the Link below to Unsubscribe.\n" . $unsublink . $usr;
      $newline   = "\n\n";
    }

    $credlink = ($cl) ? $newline.$credlink : $newline;

    $mess = str_ireplace(array('[credit_mailer_link]','[unsubscribe_link]','[list_name]',     '[program_name]','[admin_email_address]'),
                         array($credlink,               $unsublink,         $list['listname'], $program_name,   $adminemail),
                         $mess);

    $mess = str_ireplace($firstnames, $e['fname'], $mess);
    $mess = str_ireplace($lastnames,  $e['lname'], $mess);

    $subj = str_ireplace($firstnames, $e['fname'], $subject);
    $subj = str_ireplace($lastnames,  $e['lname'], $subj);

    $header_hash = substr(sha1('jd93JdmAz3hF1' . $e['userID']), 0, 5);

    $head = str_ireplace(array('USERID','HASH'), array($e['userID'], $header_hash), $headers);

    if (mail($e['email'], $subj, $mess, $head))
    {
      echo ($listcounter + 1) . "/{$numlists}   " . ($emailcounter + 1) . "/{$emailcount}   abstotal:$numMails   list:{$list['listname']}   email:{$e['email']}\n";
      $good++;
    }
    else
    {
      echo "--> totalbad:{$numBad} BAD EMAIL   {$e['email']}\n";
      $bad++;
    }

    usleep($u_sleep);
  }

  $numMails += $good;
  $numBad   += $bad;

  $db->Query("UPDATE soloads SET numemails='$numMails', bademails='$numBad' WHERE id='$id'");
}

$db->Query("UPDATE soloads SET datemailed=NOW() WHERE id='$id'");

// logdate, logins, signup, mails, adminmail
if ($numMails)
  $db->Query("INSERT INTO hitcounter (logdate, mails) VALUES('$today', '$numMails') ON DUPLICATE KEY UPDATE mails = mails + {$numMails}");

?>
