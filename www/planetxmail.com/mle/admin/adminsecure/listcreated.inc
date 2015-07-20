<?php
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();
$db->Query("SELECT * FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");

$listData = $db->FetchArray();

?>