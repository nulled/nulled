<?php
include("../mlpsecure/config/config.inc");
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

if ($submitted=="1")
{
  if (strstr($footer, "[unsubscribe_link]"))
  {
    $footer = trim($footer);

    $db->Query("UPDATE listmanager SET footer='$footer' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
    $notValid = "Footer successfully updated.";
  }
  else
    $notValid = "ERROR: MUST have [unsubscribe_link] somewhere in the footer.";
}

$db->Query("SELECT footer FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($footer) = $db->FetchRow();

?>