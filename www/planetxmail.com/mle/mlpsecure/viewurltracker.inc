<?php
include("mlpsecure/config/classes.inc");
include("mlpsecure/config/config.inc");

$db = new MySQL_Access();

$db->Query("SELECT * FROM urlmanager WHERE userID='$_SESSION[aauserID]' AND name='$tracker'");
$urlInfo = $db->FetchArray();

?>