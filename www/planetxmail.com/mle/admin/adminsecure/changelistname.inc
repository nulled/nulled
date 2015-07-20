<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

$id        = $_SESSION['aalistownerID'];
$ownername = $_SESSION['aalistownername'];
$listname  = $_SESSION['aalistname'];

$db->Query("SELECT listname FROM listmanager WHERE listname='{$listname}' AND listownerID='{$id}' LIMIT 1");
list($oldlistname) = $db->FetchRow();

if ($submitted == 'change')
{
  $newlistname = trim($newlistname);

  if (has_weird($newlistname))      $notValid = 'ERROR: List name may only contain numbers, letters and _ (underscores).';
  else if ($ownername == 'demoit')  $notValid = 'ERROR: This is the DEMO LIST so changes will not be applied.';
  else if (strlen($newlistname)>20) $notValid = 'ERROR: List name may not exceed 20 characters.';
  else if (has_space($newlistname)) $notValid = 'ERROR: List name may not contain spaces';
  else if ($db->Query("SELECT listname FROM listmanager WHERE listname='$newlistname' AND listownerID='$id' LIMIT 1"))
    $notValid = "ERROR: Listname <i>{$newlistname}</i> is already taken.";
  else
  {
    $listID = "'listname='$oldlistname' AND listownerID='$id'";

    $db->Query("UPDATE users SET listname='$newlistname' WHERE {$listID}");
    $db->Query("UPDATE upgrade SET listname='$newlistname' WHERE {$listID}");
    $db->Query("UPDATE system SET listname='$newlistname' WHERE {$listID}");
    $db->Query("UPDATE listmanager SET listname='$newlistname' WHERE {$listID}");
    $db->Query("UPDATE listconfig SET listname='$newlistname' WHERE {$listID}");
    $db->Query("UPDATE banners SET listname='$newlistname' WHERE {$listID}");
    $db->Query("UPDATE banneddomains SET listname='$newlistname' WHERE {$listID}");
    $db->Query("UPDATE ads SET listname='$newlistname' WHERE {$listID}");
    $db->Query("UPDATE listurls SET listname='$newlistname' WHERE {$listID}");

    $db->SelectDB('pxm');
    $db->Query("UPDATE orders SET listname='$newlistname' WHERE listname='$oldlistname' AND listownername='$ownername'");
    $db->Query("UPDATE extended SET listname='$newlistname' WHERE listname='$oldlistname' AND listownername='$ownername'");

    if ($db->Query("SELECT listname FROM clients WHERE {$listID}"))
      $db->Query("UPDATE clients SET listname='$newlistname' WHERE {$listID}");

    $_SESSION['aalistname'] = $oldlistname = $newlistname;

    $notValid = 'List Name has been changed.';
  }
}
?>