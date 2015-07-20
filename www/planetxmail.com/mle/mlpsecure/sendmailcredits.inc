<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

$db->Query("SELECT email, listemail FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
list($email, $listemail) = $db->FetchRow();

$banned      = ($db->Query("SELECT count FROM bounced WHERE bademail='$listemail' AND count > 4 LIMIT 1")) ? 1 : 0;
$mailboxfull = ($db->Query("SELECT bademail FROM bounced WHERE bademail='$listemail' AND mailboxfull > 0 LIMIT 1")) ? 1 : 0;

$cbanned      = ($db->Query("SELECT count FROM bounced WHERE count > 4 AND bademail='{$email}' LIMIT 1")) ? 1 : 0;
$cmailboxfull = ($db->Query("SELECT bademail FROM bounced WHERE mailboxfull > 0 AND bademail='{$email}' LIMIT 1")) ? 1 : 0;

$listemailconfirmed = (substr($listemail, (strlen($listemail)-11), 11) == 'unconfirmed') ? 0 : 1;
$emailconfirmed     = (substr($listemail, (strlen($email)-11), 11) == 'unconfirmed') ? 0 : 1;

if ($email == '')
{
  header('Location: main.php?option=changesignupemail');
  exit;
}
else if ($listemail == '')
{
  header('Location: main.php?option=enterlistemail');
  exit;
}
else if (! $listemailconfirmed)
{
  header('Location: main.php?option=enterlistemailunconfirmed');
  exit;
}
else if (in_array($email, $_GREYLISTED_DOMAINS) AND $cbanned)
{
  header('Location: main.php?option=greylist');
  exit;
}
else if ($banned)
{
  header('Location: main.php?option=bannedmessage');
  exit;
}
else if ($mailboxfull)
{
  header('Location: main.php?option=mailboxfull');
  exit;
}
else if ($cbanned)
{
  header('Location: main.php?option=bannedmessagecontact');
  exit;
}
else if ($cmailboxfull)
{
  header('Location: main.php?option=mailboxfullcontact');
  exit;
}
else if (! $emailconfirmed)
{
  header('Location: main.php?option=enteremailunconfirmed');
  exit;
}

$db->Query("SELECT mailcreditstoday, mailcreditsweek, lastmailweek, vacation, lastvacation, credits, messagecredit FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
list($mailcreditstoday, $mailcreditsweek, $lastmailweek, $vacation, $lastvacation, $credits, $data) = $db->FetchRow();

list($subject, $message, $crediturl) = explode("n!t!w_s!4!0", $data);

$subject = stripslashes($subject);

// detect if this is HTML, if so redirect to HTML mode
if (stristr($message, '<p>') AND ! $html)
{
  header('Location: main.php?option=sendmailcredits&html=1');
  exit;
}

// determine if we need the mail timer
if ($_SESSION['aastatus'] == 'mem')      $maxweeklymail = $mem_sendmailcredits_times_week;
else if ($_SESSION['aastatus'] == 'pro') $maxweeklymail = $pro_sendmailcredits_times_week;
else if ($_SESSION['aastatus'] == 'exe') $maxweeklymail = $exe_sendmailcredits_times_day;

if ($_SESSION['aastatus'] == 'exe') $mailweek = 0;

$nextmaildate == '';
$servertime = mysql_timestamp_to_humandatetime(timestamp_to_mysql_timestamp(time()));

if ($_SESSION['aastatus'] == 'exe' AND $mailcreditstoday == 0) {}
else if ($mailcreditstoday == 0 AND $mailcreditsweek < $maxweeklymail) {}
else
{
  if ($_SESSION['aastatus'] == 'exe')
    $nextmaildate = date('F j, Y', mktime(0, 0, 0, date('m'), date('d')+1, date('y')));
  else
  {
    if ($mailcreditsweek < $maxweeklymail)
      $nextmaildate = date('F j, Y', mktime(0, 0, 0, date('m'), date('d')+1, date('y')));
    else
    {
      $nextweek = mysql_datetime_to_timestamp($lastmailweek);
      $nextweek += 604801; // + 1 to compensate for -1 sec to make it midnight based on login.inc
      $nextmaildate = timestamp_to_mysql_date($nextweek);
      $nextmaildate = mysql_datetime_to_humandate($nextmaildate);
    }
  }
}

// build direct ads
$numAds = $db->Query("SELECT ad FROM directads WHERE LEFT(dateexpired, 1)='0' AND mop!='' AND page='sendmail' ORDER BY MD5(RAND())");
if ($numAds > 1) $db->Query("SELECT ad FROM directads WHERE LEFT(dateexpired, 1)='0' AND mop!='' AND page='sendmail' AND id!='1' ORDER BY MD5(RAND())");
$directads = $db->result;

// delete expired direct ads
$db->Query("UPDATE directads SET dateexpired=NOW() WHERE LEFT(dateexpired, 1)='0' AND mop!='' AND page='sendmail' AND ($mletime - (numdays * 86400)) > UNIX_TIMESTAMP(datesubmitted)");

?>
