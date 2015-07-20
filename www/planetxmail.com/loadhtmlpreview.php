<?php
include("phpsecure/classes.inc");
$db = new MySQL_Access("mle");

if ($id)
{
  $db->Query("SELECT message FROM soloads WHERE id='$id'");
  list($message) = $db->FetchRow();
}
else
{
  echo "<h3>Error:  Missing Message ID</h3>";
  exit;
}

$message = stripslashes($message); echo $message;

?>