<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

set_time_limit(0);
$num_admin_mail  = 1;

$db = new MySQL_Access('mle');

$db->Query("SELECT adminmailcount FROM listconfig WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");
list($adminmailmax) = $db->FetchRow();

if ($adminmailmax >= $num_admin_mail AND ! $_SESSION['aaadminpsk'])
{
  echo "<h3>You have mailed your limit.  <b>$num_admin_mail</b> per day.</h3>";
  echo "<br><input type=\"button\" value=\"Back to Send Mail\" onClick=\"location.href='sendmailhtml.php'\">";
  exit;
}

$i = 0;
$emails = array();

$db->Query("SELECT email, userID, fname, lname FROM users
            LEFT JOIN bounced ON users.email = bounced.bademail
            WHERE users.email != ''
            AND users.verified='yes'
            AND users.listname='{$_SESSION['aalistname']}'
            AND users.listownerID='{$_SESSION['aalistownerID']}'
            AND ((bounced.count > 1 AND bounced.mailboxfull > 1) OR bounced.bademail IS NULL))");

while (list($email, $userID, $fname, $lname) = $db->FetchRow())
{
  $emails[$i][0] = $email;
  $emails[$i][1] = $userID;
  $emails[$i][2] = $fname;
  $emails[$i][3] = $lname;
  $i++;
}

$emailcount = count($emails);
if ($emailcount)
{
  // build the email message
  $db->Query("SELECT message FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  list($data) = $db->FetchRow();

  $db->Query("SELECT header, footer FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  list($header, $footer) = $db->FetchRow();

  // extract the HTML and PLAIN TEXT parts of the message
  $messageParts = explode("n!t!w_s!4!0", $data);
  unset($data);

  $subject = $messageParts[2];
  $message = $messageParts[3];
  $htmlsubject = $messageParts[4];
  $htmlmessage = $messageParts[5];
  unset($messageParts);

  $db->Query("SELECT fromname, fromemail, adminemail FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  list($fromname, $fromemail, $adminemail) = $db->FetchRow();

  $headers = "From: $fromname <do_not_reply@planetxmail.com>";

  $soloadhtml = "Send a Solo AD to 230,000+ members spanning 245+ SafeLists!<br><a href=\"http://www.planetxmail.com/soloads.php?list=nl\">Click Here - 100% Optin - 100% Spam Free - Click Here</a>";
  $soloadtext = "Send a Solo AD to 230,000+ members spanning 245+ SafeLists!\nhttp://www.planetxmail.com/soloads.php?list=nl\n\nOr Send an HTML Solo AD to 230,000+ members spanning 245+ SafeLists!\nhttp://www.planetxmail.com/htmlsoloads.php?list=nl";

  if ($isHTML)
  {
    $subject = $htmlsubject;

    $header = str_replace("\n", "<br>\n", $header);
    $footer = str_replace("\n", "<br>\n", $footer);
    $message = "$header<br>$htmlmessage<br>$footer<br><br>$soloadhtml";

    $headers .= "\r\nContent-Type: text/html; charset=iso-8859-1";
  }
  else
    $message = "$header\n$message\n$footer\n\n$soloadtext";

  $unsublink = "http://www.planetxmail.com/mle/rl.php";
  $sublink   = "http://www.planetxmail.com/mle/signup.php?list=$_SESSION[aalistname]&id=$_SESSION[aalistownerID]";

  $message = str_ireplace("[subscribe_link]", $sublink, $message);
  $message = str_ireplace("[list_name]", $_SESSION[aalistname], $message);
  $message = str_ireplace("[admin_email_address]", $adminemail, $message);

  $subject = stripslashes($subject);
  $message = wordwrap(stripslashes($message), $email_wordwrap_length);

  $counterbad = $countergood = 0;

  if (! $_SESSION['aaadminpsk'])
    $db->Query("UPDATE listconfig SET adminmailcount=adminmailcount+1 WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");

  for ($i=0; $i<$emailcount; $i++)
  {
    $body = str_ireplace("[first_name]", $emails[$i][2], $message);
    $body = str_ireplace("[last_name]", $emails[$i][3], $body);

    $usr = "?u=".strrev($emails[$i][1])."&v=".strrev(substr(md5($emails[$i][1]), 0, 5));

    if ($isHTML)
      $body = str_ireplace("[unsubscribe_link]", "<a href=\"".$unsublink.$usr."\">Click Here to Unsubscribe</a>", $body);
    else
      $body = str_ireplace("[unsubscribe_link]", $unsublink.$usr, $body);

    $subj = str_ireplace("[first_name]", $emails[$i][2], $subject);
    $subj = str_ireplace("[last_name]", $emails[$i][3], $subj);

    $head = str_ireplace("USERID", $emails[$i][1], $headers);

    if (@mail($emails[$i][0], $subj, $body, $head))
    {
      $sentemail = $countergood + 1;
      $countergood++;
   }
    else
    {
      $counterbad++;
    }
  }

  @mail('elitescripts2000@yahoo.com', 'PXM - Admin Mail Sent Notice - HTML', "listname=$_SESSION[aalistname]");

  $today = date("F j, Y");
  $db->Query("SELECT adminmail FROM hitcounter WHERE logdate='$today'");
  if ($db->rows)
  {
    list($adminmail) = $db->FetchRow();
    $adminmail += $countergood;
    $db->Query("UPDATE hitcounter SET adminmail='$adminmail' WHERE logdate='$today'");
  }
  else
    $db->Query("INSERT INTO hitcounter VALUES('$today','0','0','0','$countergood')");
}
else
  echo "<b>No emails found in database.</b><br><br>\n";

echo "<br><b>$emailcount total emails sent.</b><br><br>";

echo "<input type=\"button\" value=\"Back to Send Mail\" onClick=\"location.href='sendmailhtml.php'\">\n";

?>