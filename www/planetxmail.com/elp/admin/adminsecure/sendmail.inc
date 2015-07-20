<?php
include("../../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("elp");

if ($submitted=="save")
{
  $subject = trim($subject);
  $message = trim($message);
  $message = $subject."n!t!w_s!4!0".$message;

  $db->Query("UPDATE elpowners SET message='$message' WHERE elpownername='$_SESSION[aaelp]ownername'");

  $saved = true;
  $notValid = "Message saved.";
}
else
{
  $saved = "false";
  $notValid = "Not saved yet.";
}

$db->Query("SELECT message FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
list($data) = $db->FetchRow();
list($subject, $message) = explode("n!t!w_s!4!0", $data);

?>