<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

$id = $_SESSION['aalistownerID'];

$db->Query("SELECT username FROM listowner WHERE listownerID='{$id}' LIMIT 1");
list($oldlistownername) = $db->FetchRow();

if ($submitted == 'change' AND $listownername)
{
  $listownername = trim($listownername);

  if (has_weird($listownername))                   $notValid = 'ERROR: List Owner Username may only contain Letters, Numbers or underscores (_).';
  else if ($_SESSION['aalistownername']=='demoit') $notValid = 'ERROR: This is the DEMO LIST so changes will NOT be applied.';
  else if (strlen($listownername) > 20)            $notValid = 'ERROR: List Owner name is too long. 20 maximum characters.';
  else if (strlen($listownername) < 3)             $notValid = 'ERROR: List Owner name is too short. 3 minimum characters.';
  else if ($db->Query("SELECT username FROM listowner WHERE username='$listownername' LIMIT 1"))
    $notValid = "ERROR: List Owner User Name <i>$listownername</i> is already taken.";
  else
  {
    $db->Query("UPDATE listowner SET username='$listownername' WHERE listownerID='$id' LIMIT 1");

    $db->SelectDB('pxm');

    $db->Query("UPDATE orders SET listownername='$listownername' WHERE listownername='$oldlistownername'");
    $db->Query("UPDATE extended SET listownername='$listownername' WHERE listownername='$oldlistownername'");

    $_SESSION['aalistownername'] = $listownername;

    $notValid = 'List Owner Username was changed.';
    $oldlistownername = $_SESSION['aalistownername'];
  }
}

?>