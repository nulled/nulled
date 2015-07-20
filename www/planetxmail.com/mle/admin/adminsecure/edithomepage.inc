<?php
include("../mlpsecure/config/config.inc");
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

if ($submitted=="1")
{
  $htmlmem = trim($htmlmem);
  $htmlpro = trim($htmlpro);
  $htmlexe = trim($htmlexe);

  $html = $htmlmem."!N_T_W_S_4_0!".$htmlpro."!N_T_W_S_4_0!".$htmlexe;

  $db->Query("UPDATE listmanager SET html='$html' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $notValid = "HTML successfully updated.";
}

$db->Query("SELECT html FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($html) = $db->FetchRow();

list($htmlmem, $htmlpro, $htmlexe) = explode("!N_T_W_S_4_0!", $html);

?>