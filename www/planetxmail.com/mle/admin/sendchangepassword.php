<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("../mlpsecure/config/classes.inc");
include("../mlpsecure/config/config.inc");
include("../mlpsecure/validationfunctions.php");

$db = new MySQL_Access('mle');

$db->Query("SELECT userID, password, email, username FROM users WHERE userID='$_SESSION[aauserID]' LIMIT 1");
$linkData = $db->FetchRow();

$removelink = "http://planetxmail.com/mle/enternewpassword.php?uID=$linkData[0]&pID=$linkData[1]&list=$_SESSION[aalistname]&id=$_SESSION[aalistownerID]";

$db->Query("SELECT fromname, fromemail FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
$listemails = $db->FetchRow();

$message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/lostpassmessage.txt');
$message = str_replace('[link]', $removelink, $message);

$subject = $_SESSION['aalistname'] . ' - Lost Password';
$header = "From: {$listemails[0]} <{$listemails[1]}>";

if(@mail($linkData[2], $subject, $message, $header))
{
  header("Location: changepasswordsent.php?username={$linkData[3]}&email={$linkData[2]}&aauserID={$_SESSION['aauserID']}");
  exit;
}
else
  $notValid = "ERROR: Mail server is down.  Try again later.";
?>
