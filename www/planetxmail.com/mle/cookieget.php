<?php
include("mlpsecure/config/classes.inc");

$db = new MySQL_Access();

if (! $db->Query("SELECT listname FROM listmanager WHERE listname='$list' AND listownerID='$id'"))
{
  if ($db->Query("SELECT listname FROM deletedlists WHERE listname='$list' AND listownerID='$id'"))
    header("Location: listdiscontinued.php");
  else
    header("Location: logininvalid.php");

  exit;
}

echo $_COOKIE["$id$list"];

?>