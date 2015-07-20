<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access('mle');

$db->Query("SELECT email FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
list($email) = $db->FetchRow();

if ($submitted == 'cleared')
{
  $db->Query("DELETE FROM bounced WHERE bademail='$email' LIMIT 1");

  header('Location: main.php');
  exit;
}

?>