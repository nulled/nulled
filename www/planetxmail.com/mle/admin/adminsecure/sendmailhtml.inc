<?php
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

// Check if the list is a NewsLetter, if not goto regular sendmail
$db->Query("SELECT listtype FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($listtype) = $db->FetchRow();

if ($listtype!="Newsletter [closedlist]")
{
  header("Location: sendmail.php");
  exit;
}

if ($submitted=="save")
{
  $nlsubject     = trim($nlsubject);
  $nlmessage     = trim($nlmessage);
  $nlhtmlsubject = trim($nlhtmlsubject);
  $nlhtmlmessage = trim($nlhtmlmessage);

  if (! $nlsubject) $nlsubject = "Enter subject here.";
  if (! $nlmessage) $nlmessage = "Enter message here.";
  if (! $nlhtmlsubject) $nlhtmlsubject = "Enter subject here.";
  if (! $nlhtmlmessage) $nlhtmlmessage = "Enter message here.";

  $message = $subject."n!t!w_s!4!0".$message."n!t!w_s!4!0".$nlsubject."n!t!w_s!4!0".$nlmessage."n!t!w_s!4!0".$nlhtmlsubject."n!t!w_s!4!0".$nlhtmlmessage;

	$db->Query("UPDATE listmanager SET message='$message' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
	$saved = "true";
  $notValid = "Message saved.";
}
else
  $saved = "false";


$db->Query("SELECT message FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($data) = $db->FetchRow();
$messageParts = explode("n!t!w_s!4!0", $data);

$nlsubject = $messageParts[2];
$nlmessage = $messageParts[3];
$nlhtmlsubject = $messageParts[4];
$nlhtmlmessage = $messageParts[5];

if ($saved=="true")
	$savedstatus = "Message saved.";
else
	$savedstatus = "Message NOT saved.";

?>