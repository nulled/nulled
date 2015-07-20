<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access('mle');

$db->Query("SELECT listemail FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
list($listemail) = $db->FetchRow();

if ($submitted == 'cleared')
{
  $db->Query("DELETE FROM bounced WHERE bademail='$listemail' LIMIT 1");

  header('Location: main.php');
  exit;
}

?>