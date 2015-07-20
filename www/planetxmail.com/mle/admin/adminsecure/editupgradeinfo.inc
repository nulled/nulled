<?php
include("../mlpsecure/config/config.inc");
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

if ($submitted=="1")
{
  $prohtml = trim($prohtml);
  $exehtml = trim($exehtml);

  $html = $prohtml."!N_T_W_S_4_0!".$exehtml;

  $db->Query("UPDATE listconfig SET upgradeinfo='$html' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $notValid = "HTML successfully updated.";
}

$db->Query("SELECT upgradeinfo FROM listconfig WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($html) = $db->FetchRow();
list($prohtml, $exehtml) = explode("!N_T_W_S_4_0!", $html);

?>