<?php
include("mlpsecure/config/classes.inc");
include("mlpsecure/config/config.inc");

$db = new MySQL_Access();

$db->Query("SELECT html FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
list($html) = $db->FetchRow();

list($htmlmem, $htmlpro, $htmlexe) = explode("!N_T_W_S_4_0!", $html);
$html = "";

$db->Query("SELECT COUNT(*) FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]' AND verified='yes'");
list($totalcount) = $db->FetchRow();

$db->Query("SELECT COUNT(*) FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]' AND verified='yes' AND status='mem'");
list($memcount) = $db->FetchRow();

$db->Query("SELECT COUNT(*) FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]' AND verified='yes' AND status='pro'");
list($procount) = $db->FetchRow();

$db->Query("SELECT COUNT(*) FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]' AND verified='yes' AND status='exe'");
list($execount) = $db->FetchRow();

if ($_SESSION['aastatus']=="mem") { $userstatus = "Member"; $html = $htmlmem; }
else if ($_SESSION['aastatus']=="pro") { $userstatus = "Professional"; $html = $htmlpro; }
else if ($_SESSION['aastatus']=="exe") { $userstatus = "Executive"; $html = $htmlexe; }

if ($html)
{
  $html = str_replace("[list_name]", $_SESSION['aalistname'], $html);
  $html = str_replace("[program_name]", $program_name, $html);
  $html = str_replace("[member_status]", $userstatus, $html);

  $html = str_replace("[total_count]", $totalcount, $html);
  $html = str_replace("[mem_count]", $memcount, $html);
  $html = str_replace("[pro_count]", $procount, $html);
  $html = str_replace("[exe_count]", $execount, $html);
}

?>