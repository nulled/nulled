<?php
include("../../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("elp");
$db->Query("SELECT elpownername, email FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");

$elpownerData = $db->FetchArray();

?>