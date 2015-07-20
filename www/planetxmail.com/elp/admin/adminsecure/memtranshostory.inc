<?php
include ("../../mle/mlpsecure/validationfunctions.php");
include ("../../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

$db->Query("SELECT username, transtype, amount, receipt, datepaid, paid, commissionowed FROM membertrans WHERE username='$u' AND elpownername='$o'");
$membertrans = $db->result;
?>