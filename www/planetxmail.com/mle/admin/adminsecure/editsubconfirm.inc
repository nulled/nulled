<?php
include("../mlpsecure/config/config.inc");
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

if ($submitted=="1")
{
  if (strstr($subconfirm, "[subscribe_link]"))
  {
    $subconfirm = trim($subconfirm);

    $db->Query("UPDATE listmanager SET subconfirm='$subconfirm' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
    $notValid = "Subscribe confirm successfully updated.";
  }
  else
    $notValid = "ERROR: MUST have [subscribe_link] somewhere in the message.";
}

$db->Query("SELECT subconfirm FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($subconfirm) = $db->FetchRow();

?>