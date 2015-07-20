<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access('mle');

if ($e AND $h)
{
  $listemail = urldecode(trim($e));
  $vhash     = substr(sha1('sddsf876DFJDhf8' . $listemail), 0, 5);
}

if ($e AND trim($h) == $vhash) {}
else
{
  $db->Query("SELECT listemail FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
  list($listemail) = $db->FetchRow();
}

$db->Query("SELECT reason FROM bounced WHERE bademail='$listemail' LIMIT 1");
list($reason) = $db->FetchRow();

$reason = wordwrap($reason, 85);

?>