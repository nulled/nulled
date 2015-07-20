<?php
include ("../../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

$db->Query("SELECT * FROM elpownertrans");
$elpownertrans = $db->result;

?>