<?php
include("../mlpsecure/config/config.inc");
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

if ($submitted=="1")
{
  $unsubsuccess = trim($unsubsuccess);

  $db->Query("UPDATE listmanager SET unsubsuccess='$unsubsuccess' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $notValid = "Unsubsuccess successfully updated.";
}

$db->Query("SELECT unsubsuccess FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($unsubsuccess) = $db->FetchRow();

?>