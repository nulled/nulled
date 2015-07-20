<?php
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

$db->Query("SELECT reason FROM bounced WHERE bademail='$email'");
list($reason) = $db->FetchRow();

?>