<?php
include ("../../mle/mlpsecure/validationfunctions.php");
include ("../../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

$db->Query("SELECT username, transtype, amount, receipt, mop, datepaid, paid, commissionowed FROM membertrans WHERE username='$u' AND elpownername='$o' ORDER BY datepaid");
$membertrans = $db->result;
?>