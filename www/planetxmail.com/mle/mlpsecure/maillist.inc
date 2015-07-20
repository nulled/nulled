<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

$username    = $_SESSION['aausername'];
$userID      = $_SESSION['aauserID'];
$listname    = $_SESSION['aalistname'];
$listownerID = $_SESSION['aalistownerID'];
$status      = $_SESSION['aastatus'];

if ($submitted == 'mail' OR $submitted == 'mailcredits')
{
  $subject = trim($subject);
  $message = trim($message);

  $crediturl = trim($crediturl);

  if ($subject == '') $subject = 'Subject';
  if ($message == '') $message = 'Message';

  $message = str_replace("\r\n", "\n", $message);

  $subject = substr($subject, 0, $email_subject_length);
  $message = substr($message, 0, $email_length);

  $message = $subject . 'n!t!w_s!4!0' . $message . 'n!t!w_s!4!0' . $crediturl;

  if ($submitted == 'mail')        $db->Query("UPDATE users SET message='$message' WHERE userID='$userID' LIMIT 1");
  if ($submitted == 'mailcredits') $db->Query("UPDATE users SET messagecredit='$message' WHERE userID='$userID' LIMIT 1");
}
else
  exit('ERROR: mail or mailcredits expected.');

// At top of pop up window will display Banner and BILL board ads.. also the DB class object was created in getad.php
//require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/getad.php');
// file is saved in Desktop/Business folder for now ...

$head = '<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title>' . $program_name . ' - Mail Sent Status</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
' . flush() . '
<body>
<table border="1" width="590" cellspacing="0" cellpadding="0">
';

$db->Query("SELECT mailtoday, mailweek, mailcreditstoday, mailcreditsweek, listemail, vacation, lastvacation, message, messagecredit, email, credits FROM users WHERE userID='$userID' LIMIT 1");
$usermail = $db->FetchArray();

$maxweeklymail = ($status == 'mem' AND $submitted == 'mail') ? $mem_sendmail_times_week : $mem_sendmailcredits_times_week;
$maxweeklymail = ($status == 'pro' AND $submitted == 'mail') ? $pro_sendmail_times_week : $pro_sendmailcredits_times_week;
$maxweeklymail = ($status == 'exe' AND $submitted == 'mail') ? $exe_sendmail_times_day  : $exe_sendmailcredits_times_day;

if ($_SESSION['aastatus'] == 'exe')
  $usermail['mailweek'] = $usermail['mailcreditsweek'] = 0;

$h1 = '<tr><td align="center" colspan="2"><br><font size="3"><b class="red">';
$h2 = "</b></font><br /><br />\n";

$crediturl_bad = (strtolower(substr($crediturl, 0, 7)) == 'http://' OR strtolower(substr($crediturl, 0, 8)) == 'https://') ? 0 : 1;

$go1 = ($submitted == 'mail' AND ! $usermail['mailtoday'] AND $usermail['mailweek'] < $maxweeklymail) ? 1 : 0;
$go2 = ($submitted == 'mailcredits' AND ! $usermail['mailcreditstoday'] AND $usermail['mailcreditsweek'] < $maxweeklymail AND $usermail['credits'] > 0) ? 1 : 0;

if ($usermail['vacation'] == 1)                                     $notValid = $h1 . 'ERROR: Your vacation switch is on. Goto Profile to turn it off.' . $h2;
else if (substr($usermail['lastvacation'], 0, 1) == '2')            $notValid = $h1 . 'ERROR: Your vacation switch is off, but you need to wait until the day after the next mailing day for it to reset!' . $h2;
else if ($submitted == 'mailcredits' AND ! is_numeric($usecredits)) $notValid = $h1 . 'ERROR: Credits must be a numeric value.' . $h2;
else if ($submitted == 'mailcredits' AND $usecredits < 1)           $notValid = $h1 . 'ERROR: Credits entered must be greater than Zero.' . $h2;
else if (! $crediturl OR $crediturl_bad)                            $notValid = $h1 . 'ERROR: Credit URL must begin with http:// or https://' . $h2;
else if ($go1 OR $go2)
{
  $emailcount = 1;

  if ($usecredits > 100000)
    $usecredits = 100000;

  if ($submitted == 'mail')
  {
    $db->Query("UPDATE users SET mailtoday='1', mailweek=mailweek+1 WHERE userID='$userID' LIMIT 1");
    list($subject, $message) = explode('n!t!w_s!4!0', $usermail['message']);
  }
  else if ($submitted == 'mailcredits')
  {
    $db->Query("UPDATE users SET mailcreditstoday='1', mailcreditsweek=mailcreditsweek+1 WHERE userID='$userID' LIMIT 1");
    list($subject, $message) = explode('n!t!w_s!4!0', $usermail['messagecredit']);
  }

  $db->Query("SELECT listhash FROM listurls WHERE listname='$listname' AND listownerID='$listownerID' LIMIT 1");
  list($listhash) = $db->FetchRow();

  $db->Query("SELECT footer, fromname, fromemail, adminemail FROM listmanager WHERE listname='$listname' AND listownerID='$listownerID' LIMIT 1");
  list($footer, $fromname, $fromemail, $adminemail) = $db->FetchRow();

  $footer = "_______________________________________________________
This message is not spam! You received this because you joined
the Double Opt-In List: {$_SESSION['aalistname']} sent by User: {$_SESSION['aausername']}
and agreed to receive daily mail from other list members, in return
for You being able to post Your own daily offers.

[unsubscribe_link]
32811 7th Ave SW, Federal Way, WA, 98023
";

  if ($sendashtml)
    $footer = str_replace("\n", "<br />\n", $footer);

  $sublink = 'http://planetxmail.com/mle/signup.php?l=' . $listhash;
  $headers = "From: {$fromname} <do_not_reply@planetxmail.com>";

  $message = trim($message) . '[credit_mailer_link]' . trim($footer);

  $message = str_replace(array('[subscribe_link]', '[list_name]','[program_name]','[admin_email_address]'),
                         array($sublink,            $listname,    $program_name,   $adminemail),
                         $message);

  $subject = $db->EscapeString($subject);
  $message = $db->EscapeString($message);

  $mess = strtolower($subject.$message);

  $offensive = 0;
  if (stristr($mess, ' xxx '))            $offensive = 'xxx';
  else if (strstr($mess, 'pussy'))        $offensive = 'pussy';
  else if (strstr($mess, ' cock '))       $offensive = 'cock';
  else if (strstr($mess, 'teen sex'))     $offensive = 'teen sex';
  else if (strstr($mess, 'clit '))        $offensive = 'clit';
  else if (strstr($mess, 'horney '))      $offensive = 'horney';
  else if (strstr($mess, 'masterbate '))  $offensive = 'masterbate';
  else if (strstr($mess, ' cum '))        $offensive = 'cum';
  else if (strstr($mess, ' prick '))      $offensive = 'prick';
  else if (strstr($mess, ' fuck '))       $offensive = 'fuck';
  else if (strstr($mess, ' fucker '))     $offensive = 'fucker';
  else if (strstr($mess, ' fucking '))    $offensive = 'fucking';
  else if (strstr($mess, ' nipples '))    $offensive = 'nipples';
  else if (strstr($mess, 'hotsex'))       $offensive = 'hotsex';
  else if (strstr($mess, ' porn '))       $offensive = 'porn';
  else if (strstr($mess, 'adult store'))  $offensive = 'adult store';
  else if (strstr($mess, 'sextoy'))       $offensive = 'sextoy';
  else if (strstr($mess, 'nigeria'))      $offensive = 'nigeria';
  else if (strstr($mess, ' panty '))      $offensive = 'panty';
  else if (strstr($mess, ' bra '))        $offensive = 'bra';
  else if (strstr($subject, 'Notification')) $offensive = 'Notification';

  if ($offensive)
  {
    // do not mail this out
    $emailcount = 0;

    $subj_offender = 'You are mailing content in disagreement with Terms of Service';
    $subj_owner    = 'Illegal AD Alert!';

    $mess_offender = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/sexnotice.txt');
    $mess_owner    = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/sexnoticetolistowner.txt');

    $mess_offender = str_replace(array('[subject]','[message]'),
                                 array($subject,    $message),
                                 $mess_offender);

    $mess_owner = str_replace(array('[list_name]','[user_name]','[email]',          '[word]',   '[subject]','[message]'),
                              array($listname,     $username,    $usermail['email'], $offensive, $subject,   $message),
                              $mess_owner);

    $mess_offender = wordwrap($mess_offender, $email_wordwrap_length);
    $mess_owner    = wordwrap($mess_owner, $email_wordwrap_length);

    $db->Query("SELECT email FROM listowner WHERE listownerID='$listownerID' LIMIT 1");
    list($le1) = $db->FetchRow();
    $db->Query("SELECT adminemail FROM listmanager WHERE listownerID='$listownerID' LIMIT 1");
    list($le2) = $db->FetchRow();
    $db->Query("SELECT adminemailaddress FROM listconfig WHERE listownerID='$listownerID' LIMIT 1");
    list($le3) = $db->FetchRow();

         if ($le1) $listowneremail = $le1;
    else if ($le2) $listowneremail = $le2;
    else if ($le3) $listowneremail = $le3;
    else $listowneremail = '';

    if ($listowneremail)    mail($listowneremail, $subj_owner, $mess_owner, $headers);
    if ($usermail['email']) mail($usermail['email'], $subj_offender, $mess_offender, $headers);
    mail('elitescripts2000@yahoo.com', $subj_offender, $mess_offender, $headers);
  }

  $sendashtml = ($sendashtml) ? 'HTML' : 'PLAIN';
  $headers    = "From: {$fromname} <do_not_reply@planetxmail.com>,{$sendashtml}";

  $urlID = '0';

  if ($emailcount)
  {
    $urlID = create_creditID($crediturl, $userID);

    $is_creditmailer = '';
    if ($submitted == 'mailcredits')
      $is_creditmailer = " LIMIT {$usecredits}";

    $numToMail = $db->Query("SELECT listemail, userID, username, fname, lname
                             FROM users
                             LEFT JOIN bounced ON users.listemail = bounced.bademail
                             WHERE users.listemail != ''
                             AND users.listemail NOT LIKE '%unconfirmed'
                             AND users.verified='yes'
                             AND users.vacation='0'
                             AND users.lastvacation='0000-00-00 00:00:00'
                             AND users.listname = '$listname'
                             AND users.listownerID = '$listownerID'
                             AND ((bounced.count < 1 AND bounced.mailboxfull < 1) OR bounced.bademail IS NULL){$is_creditmailer}");
    if ($numToMail)
    {
      // 10 credits per email
      $creds_deducted = $numToMail * 10;

      if ($submitted == 'mailcredits')
      {
        if ($db->Query("SELECT credits FROM users WHERE userID='$userID' LIMIT 1"))
          list($_creds) = $db->FetchRow();

        $_creds = $_creds - $creds_deducted;
        if ($_creds < 1) $_creds = 0;

        $db->Query("UPDATE users SET credits='{$_creds}' WHERE userID='$userID' LIMIT 1");
        $credits = ($urlID) ? $numToMail . '|' . $urlID : $numToMail . '|0';
      }
      else
        $credits = ($urlID) ? '0|' . $urlID : '0|0';

      $db->Query("INSERT INTO queue (userID,     listownerID,   listname,   headers,   subject,   message,   credits, datesubmitted)
                             VALUES ('$userID','$listownerID','$listname','$headers','$subject','$message','$credits', NOW())");

      if ($maillist_redirect)
      {
        header('Location: http://planetxmail.com/mle/getad.php?option=mailed');
        exit;
      }

      $res = '<tr><td align="center" colspan="2">
              <br /><font size="3"><b class="red">
                Your Message Was Queued for Delivery.<br />
                You will see your Ad Tomorrow.<br />
                We spread each Days Mail over One Full Day. (86400 Seconds)
              </b></font><br /><br />
              </td></tr>
              ';
    }
    else
    {
      if ($maillist_redirect)
      {
        header('Location: http://planetxmail.com/mle/getad.php?option=none');
        exit;
      }

      $res = '<tr><td align="center" colspan="2">
              <br /><font size="3"><b class="red">
                A) No members to Mail.<br />
                B) All are On Vacation.<br />
                C) Emails are all Bounced or Full Box.<br />
              </b></font><br /><br />
              </td></tr>
              ';
    }
  }
  else
  {
    if ($maillist_redirect)
    {
      header('Location: http://planetxmail.com/mle/getad.php?option=none');
      exit;
    }

    $res = '<tr><td align="center" colspan="2">
            <br /><font size="3"><b class="red">
              A) No members to Mail.<br />
              B) All are On Vacation.<br />
              C) Emails are all Bounced or Full Box.<br />
            </b></font><br /><br />
            </td></tr>
            ';
  }
}
else
{
  if ($maillist_redirect)
  {
    header('Location: http://planetxmail.com/mle/getad.php?option=alreadymailed');
    exit;
  }

  $res = '<tr><td align="center" colspan="2">
          <br /><font size="3"><b class="red">
            A) You already sent mail today.<br />
            B) Your Weekly Mail Limit was Reached.<br />
            C) If Mailed from the Credit Mailer, You may be Out of Credits.
          </b></font><br /><br />
          </td></tr>
          ';
}

exit($head . $notValid . $res . '
</table>
</body>
</html>');

?>
