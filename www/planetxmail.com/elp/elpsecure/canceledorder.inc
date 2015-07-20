<?php
include("../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

$db->Query("SELECT email FROM admin");
list($email) = $db->FetchRow();

?>