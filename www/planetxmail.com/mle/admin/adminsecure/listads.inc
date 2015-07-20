<?php
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();
$db->Query("SELECT * FROM ads WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");

$ads = $db->result;

?>