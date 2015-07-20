<?php
include("../../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("elp");

$db->Query("SELECT ip FROM ipaddresses WHERE username='$u' AND elpownername='$o' ORDER BY ip");
$ipdata = $db->result;

?>