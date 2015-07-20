<?php
include ("../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

$db->Query("SELECT amount FROM elpownertrans WHERE 1");

while (list($amount) = $db->FetchRow())
	$total += $amount;

echo $total;

?>