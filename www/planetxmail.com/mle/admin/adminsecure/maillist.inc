<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

set_time_limit(0);

if ($whichaddress != 'listemail' AND $whichaddress != 'email')
  exit('ERROR: Missing whichaddress param in maillist.php.');

$db = new MySQL_Access('mle');

$num_admin_mail  = 1;
$numListsMailed  = 0;
$numMails        = 0;
$numBadMails     = 0;
$startTime       = time();
$bgInc           = 0;
$bgColor1        = '#E0E0E0';
$bgColor2        = '#D0D0D0';

$db->Query("SELECT adminmailcount FROM listconfig WHERE {$_listID} LIMIT 1");
list($adminmailmax) = $db->FetchRow();

if ($adminmailmax >= $num_admin_mail AND ! $_SESSION['aaadminpsk']) // super listadmin (you matt) can mail all you want
{
  echo "<h3>You have mailed your limit. <b>{$num_admin_mail}</b> per day.";
  echo '<br><input type="button" value="Back to Send Mail" ';
  echo "onClick=\"location.href='sendmail.php?mailtomem={$mailtomem}&mailtopro={$mailtopro}&mailtoexe={$mailtoexe}&mailtoall={$mailtoall}&whichaddress={$whichaddress}&mailstatus={$mailstatus}'\">";
  exit;
}

if ($mailtolistowners AND $_SESSION['aaadminpsk'])
{
  if (! $db->Query("SELECT email FROM listowner WHERE password != '2d233e098aedb11bee7a654751264485'"))
    exit('<b>No Listowners to mail to!</b>');

  $i = 0;
  $emails = array();
  while (list($email) = $db->FetchRow())
  {
    $emails[$i][0] = $email;
    $i++;
  }

  $mailtomem = $mailtopro = $mailtoexe = '';
  $db->Query("SELECT listname, listownerID FROM listmanager WHERE created='1' AND {$_listID} LIMIT 1");
}
else if ($mailtoall AND $_SESSION['aaadminpsk']) // this option is just like a SOLO AD
  $db->Query("SELECT listname, listownerID FROM listmanager WHERE created='1' AND listtype='Safelist [openlist]' ORDER BY listname");
else if ($mailtoall)
  $db->Query("SELECT listname, listownerID FROM listmanager WHERE created='1' AND listtype='Safelist [openlist]' AND listownerID='{$_SESSION['aalistownerID']}' ORDER BY listname");
else
  $db->Query("SELECT listname, listownerID FROM listmanager WHERE created='1' AND {$_listID}");

$result = $db->result;

$mailstatus = urlencode('Finished Mailing...');

echo "<html><head><title>Mailing</title></head>\n<body>\n";
echo "<table width=\"300\"><tr><td>\n";
echo "<h2>Started Mailing...</h2> DO NOT Close or fiddle with this window while it works!\n";
echo "</tr></td></table>\n";
echo str_repeat(' ', 200)."\n";

while (list($listname, $listownerID) = mysqli_fetch_row($result))
{
  set_time_limit(0);

  $whichstatus = '';

  if ($mailtomem)
    $whichstatus = "status='mem'";

  if ($mailtomem AND $mailtopro)
    $whichstatus .= " OR status='pro'";
  else if ($mailtopro)
    $whichstatus .= "status='pro'";

  if (($mailtomem OR $mailtopro) AND $mailtoexe)
    $whichstatus .= " OR status='exe'";
  else if ($mailtoexe)
    $whichstatus .= "status='exe'";

  if ($whichstatus)
  {
    if ($whichaddress == 'listemail')
    {
      $db->Query("SELECT listemail, userID, username, fname, lname
                  FROM users
                  LEFT JOIN bounced ON users.listemail = bounced.bademail
                  WHERE users.listemail != ''
                  AND users.listemail NOT LIKE '%unconfirmed'
                  AND ($whichstatus)
                  AND users.lastvacation='0000-00-00 00:00:00'
                  AND users.verified='yes'
                  AND users.vacation='0'
                  AND users.listname='$listname'
                  AND users.listownerID='$listownerID'
                  AND ((bounced.count < 1 AND bounced.mailboxfull < 1) OR bounced.bademail IS NULL)");
    }
    else if ($whichaddress == 'email')
    {
      $db->Query("SELECT email, userID, username, fname, lname
                  FROM users
                  LEFT JOIN bounced ON users.email = bounced.bademail
                  WHERE users.email != ''
                  AND ($whichstatus)
                  AND users.verified='yes'
                  AND users.listname='$listname'
                  AND users.listownerID='$listownerID'
                  AND ((bounced.count < 1 AND bounced.mailboxfull < 1) OR bounced.bademail IS NULL)");
    }

    $i = 0;
    $emails = array();
    while (list($email, $userID, $username, $fname, $lname) = $db->FetchRow())
    {
      $emails[$i][0] = $email;
      $emails[$i][1] = $userID;
      $emails[$i][2] = $username;
      $emails[$i][3] = $fname;
      $emails[$i][4] = $lname;
      $i++;
    }
  }

  $bgColor = ($bgInc % 2) ? $bgColor1 : $bgColor2;

  $bgInc++;

  $emailcount = count($emails);
  if ($emailcount)
  {
    $db->Query("SELECT message FROM listmanager WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");
    list($data) = $db->FetchRow();

    list($subject, $message) = explode("n!t!w_s!4!0", $data);
    unset($data);

    $db->Query("SELECT footer FROM listmanager WHERE listname='$listname' AND listownerID='$listownerID'");
    list($footer) = $db->FetchRow();

    $db->Query("SELECT fromname, fromemail, bounceemail, adminemail FROM listmanager WHERE listname='$listname' AND listownerID='$listownerID'");
    list($fromname, $fromemail, $bounceemail, $adminemail) = $db->FetchRow();

    if ($mailtolistowners AND $_SESSION['aaadminpsk'])
    {
      $fromname = "Admin";
      $footer = "____________________________________\nThis message from Admin of planetxmail.com";
    }

    $db->Query("SELECT listhash FROM listurls WHERE listname='$listname' AND listownerID='$listownerID'");
    list($listhash) = $db->FetchRow();

    $message = "$message\n\n$footer";

    $unsublink = 'http://planetxmail.com/mle/rl.php'; // unsublink is created down below in the for loop, dont confuse it with the sublink :)
    $sublink   = "http://planetxmail.com/mle/signup.php?l=$listhash";
    $loginlink = "http://planetxmail.com/mle/login.php?l=$listhash";

    $message = str_replace(array('[subscribe_link]','[login_link]','[list_name]','[admin_email_address]','[program_name]'),
                           array($sublink,          $loginlink,     $listname,    $adminemail,            $program_name),
                           $message);

    $subject = stripslashes($subject);
    $message = stripslashes($message);

    $message = wordwrap($message, $email_wordwrap_length);

    $headers = "From: {$fromname} <do_not_reply@planetxmail.com>";

    echo '<table width="300"><tr><td bgcolor="' . $bgColor . '"><b>' . $listname . '</b><br /><br />'."\n";

    flush();

    $mailcountergood = 0;
    $mailcounterbad  = 0;

    for ($i=0; $i < $emailcount; $i++)
    {
      $usr = '?u=' . strrev($emails[$i][1]) . '&v=' . strrev(substr(md5($emails[$i][1]), 0, 5));

      $body = str_replace('[unsubscribe_link]', $unsublink.$usr, $message);
      $body = str_replace('[user_name]', $emails[$i][2], $body);
      $body = str_replace('[first_name]', $emails[$i][3], $body);
      $body = str_replace('[last_name]', $emails[$i][4], $body);

      $subj = str_replace('[user_name]', $emails[$i][2], $subject);
      $subj = str_replace('[first_name]', $emails[$i][3], $subj);
      $subj = str_replace('[last_name]', $emails[$i][4], $subj);

      @mail($emails[$i][0], $subj, $body, $headers) ? $mailcountergood++ : $mailcounterbad++;
    }

    echo "<b>$mailcountergood</b> mails sent.<br>\n";
    echo "<b>$mailcounterbad</b> failed.<br>\n";
    echo "Done.</td></tr></table>\n";

    $numListsMailed++;

    $numMails    += $mailcountergood;
    $numBadMails += $mailcounterbad;
  }
  else
    echo "<table width=\"300\"><tr><td bgcolor=\"$bgColor\">Notice: No members in List: <b>$listname</b> OR <b>Solo Ads</b> not mailed to lists under 20 members.</td></tr></table>\n";
}

if ($numMails AND ! $_SESSION['aaadminpsk'])
  $db->Query("UPDATE listconfig SET adminmailcount=adminmailcount+1 WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");

$endTime   = time();
$timeTaken = $endTime - $startTime;
$timeTaken = substr(($timeTaken/60), 0, 3);

echo "<table width=\"300\"><tr><td bgcolor=\"lightblue\"><b>$numListsMailed</b> total lists mailed.<br>\n";
//echo "<b>$numMails</b> total emails sent.<br>\n";
//echo "<b>$numBadMails</b> total emails failed to mail.<br><br>\n";
echo "It took <b>$timeTaken</b> minutes to mail.<br><br>\n";

echo "<input type=\"button\" value=\"Back to Send Mail\" onClick=\"location.href='sendmail.php?mailtomem=$mailtomem&mailtopro=$mailtopro&mailtoexe=$mailtoexe&mailtoall=$mailtoall&whichaddress=$whichaddress&mailstatus=$mailstatus'\"></td></tr></table>\n";
echo "</body></html>";

if ($numListsMailed)
{
  // mail me what the other admins are mailing
  @mail('elitescripts2000@yahoo.com', 'ADMIN-MAILER-CHECK '.$subj, "listname={$_SESSION['aalistname']}\nnumMails=$numMails\nnumBadMails=$numBadMails\n\n$body", $headers);

  // logdate, logins, signup, mails, adminmail
  $today = date('F j, Y');
  $db->Query("INSERT INTO hitcounter (logdate, adminmail) VALUES('$today','$numMails') ON DUPLICATE KEY UPDATE adminmail = adminmail + {$numMails}");
}

?>