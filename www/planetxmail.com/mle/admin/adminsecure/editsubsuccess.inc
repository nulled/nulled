<?php
include("../mlpsecure/config/config.inc");
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

if ($submitted=="1")
{
  $subsuccess = trim($subsuccess);

  $db->Query("UPDATE listmanager SET subsuccess='$subsuccess' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $notValid = "Subscription success successfully updated.";
}

$db->Query("SELECT subsuccess FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($subsuccess) = $db->FetchRow();

?>