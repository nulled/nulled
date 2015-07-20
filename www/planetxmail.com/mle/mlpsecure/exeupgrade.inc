<?php
include("../mlpsecure/sessionsecure.inc");
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();
$db->Query("SELECT * FROM users WHERE userID='$_SESSION[aauserID]' AND listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
$userData = $db->FetchArray();

?>