<?php
include("adminsecure/session/sessionsecureelpowner.inc");
include("../../mle/mlpsecure/config/classes.inc");
include("../../mle/mlpsecure/validationfunctions.php");

$db = new MySQL_Access("elp");

$emails = array();
$i = 0;

if ($mailtoelpowners=="1"&&$_SESSION['aaadminpsk'])
{
  $db->Query("SELECT email, elpownername FROM elpowners ORDER BY email");

	while (list($email, $elpownername) = $db->FetchRow())
	{
	  $emails[$i][0] = $email;
	  $emails[$i][1] = $elpownername;
	  $i++;
	}
}
else
{
  $db->Query("SELECT email, username FROM users WHERE verified='1' AND elpownername='$_SESSION[aaelp]ownername' ORDER BY email");

	while (list($email, $username) = $db->FetchRow())
	{
	  $emails[$i][0] = $email;
	  $emails[$i][1] = $username;
	  $i++;
	}
}

$emailcount = count($emails);

set_time_limit(180);
if ($emailcount)
{
	$db->Query("SELECT message FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
	list($message) = $db->FetchRow();

	list($subject, $message) = explode("n!t!w_s!4!0", $message);

  $message = str_replace("[admin_email_address]", $adminemail, $message);

  $subject = stripslashes($subject);
  $message = stripslashes($message);
  $message = wordwrap($message, 60);

	$headers = "From: ELP <bounce@planetxmail.com>\r\nReturn-Path: bounce@planetxmail.com\r\nReply-To: bounce@planetxmail.com";

 	for ($i=0; $i<$emailcount; $i++)
 	{
  	if (@mail($emails[$i][0], $subject, $message, $headers))
  		echo "Sent To User: <b>".$emails[$i][1]."</b><br>\n";
  	else
  		echo "ERROR To User: <b>".$emails[$i][1]."</b><br>\n";
  }

  echo "<b>$emailcount total emails sent.</b>";
}
else
  echo "<tr><td align=\"center\" colspan=\"2\"><b class=\"red\"><h4>WARNING: No members to mail to</b></h4><br>\n";

echo "<br><br><input type=\"button\" value=\"Back to Send Mail\" onClick=\"location.href='sendmail.php'\">\n";

?>