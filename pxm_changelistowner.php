<?php
require_once('config.inc');

exit;

/*
To move a list to Planet X Mail control, 
simply change 'howheard' field in pxm database to 'cluster'
then run this script.
*/

$db = new MySQL_Access('pxm');

$listownerID   = '4032668343';
$listownername = 'PlanetXMail';

$db->Query("SELECT listname, listownername FROM orders WHERE howheard='cluster' ORDER BY listname");
$result = $db->result;

while (list($listname, $_listownername) = mysqli_fetch_row($result))
{
  $db->SelectDB('pxm');
  $db->Query("UPDATE clients SET listownerID='$listownerID' WHERE listname='$listname'");
  $db->Query("UPDATE orders SET listownername='$listownername' WHERE listownername='$_listownername'");
  
  $db->SelectDB('mle');
  $db->Query("UPDATE listconfig SET listownerID='$listownerID' WHERE listname='$listname'");
  $db->Query("UPDATE listmanager SET listownerID='$listownerID' WHERE listname='$listname'");
  $db->Query("UPDATE listurls SET listownerID='$listownerID' WHERE listname='$listname'");
  $db->Query("UPDATE banners SET listownerID='$listownerID' WHERE listname='$listname'");
  $db->Query("UPDATE banneddomains SET listownerID='$listownerID' WHERE listname='$listname'");
  $db->Query("UPDATE ads SET listownerID='$listownerID' WHERE listname='$listname'");
  $db->Query("UPDATE users SET listownerID='$listownerID' WHERE listname='$listname'");

  if ($_listownername != $listownername) 
    $db->Query("DELETE FROM listowner WHERE username='$_listownername'");
}

?>
