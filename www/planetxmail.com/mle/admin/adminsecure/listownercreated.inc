<?php
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();
$db->Query("SELECT * FROM listowner WHERE listownerID='$_SESSION[aalistownerID]'");

$listownerData = $db->FetchArray();

?>