<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

if ($deleteemail=="1")
{
  $db->Query("DELETE FROM banneddomains WHERE domain='$email' AND listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");
  $notValid = 'ERROR: Email has been removed from the list.';
}
else if ($addemail=="1" AND $email)
{
  $email = trim($email);

  $db->Query("REPLACE INTO banneddomains VALUES('{$_SESSION['aalistownerID']}','{$_SESSION['aalistname']}','$email')");
}

$db->Query("SELECT domain FROM banneddomains WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");
$bannedlist = $db->result;

?>