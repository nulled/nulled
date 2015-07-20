<?php
include("mlpsecure/config/classes.inc");

$db = new MySQL_Access();

$name = $urlID;

$db->Query("DELETE FROM urlmanager WHERE userID='$_SESSION[aauserID]' AND name='$name'");
$db->Query("DELETE FROM urldata WHERE userID='$_SESSION[aauserID]' AND name='$name'");

$notValid = urlencode("URL tracker removed.");
header("Location: main.php?option=urltrackers&notValid=$notValid");
exit;

?>