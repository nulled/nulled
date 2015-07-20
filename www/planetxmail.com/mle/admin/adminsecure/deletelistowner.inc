<?php
include("../mlpsecure/config/classes.inc");

if (! $_SESSION[aalistownerID])
{
  echo "SCRIPT ERROR: Missing listownerID.";
  exit;
}

$db = new MySQL_Access();

$db->Query("SELECT listname FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]'");
$listnames = $db->result;

set_time_limit(0);
while (list($aListname) = mysqli_fetch_row($listnames))
{
  $db->Query("SELECT userID FROM users WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");
  $allUsers = $db->result;

  while (list($row) = mysqli_fetch_row($allUsers))
  {
  	$db->Query("DELETE FROM urldata WHERE userID='$row'");
    $db->Query("DELETE FROM urlmanager WHERE userID='$row'");
    $db->Query("DELETE FROM users WHERE userID='$row'");
  }

  /////////  DELETE AD IMAGES ////////
  $db->Query("SELECT adimage FROM ads WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");
  $adImages = $db->result;

  while (list($img) = mysqli_fetch_row($adImages))
    @unlink($img);

  $db->Query("DELETE FROM ads WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");
  //////// END DELETE AD IMAGES ///////

  /////////  DELETE BANNER IMAGES ////////
  $db->Query("SELECT banner FROM banners WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");
  $bannerImages = $db->result;

  while (list($img) = mysqli_fetch_row($bannerImages))
    @unlink($img);

  $db->Query("DELETE FROM banners WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");
  //////// END DELETE BANNER IMAGES //////

  $db->Query("DELETE FROM listmanager WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");

  $db->Query("DELETE FROM system WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");
  $db->Query("DELETE FROM banneddomains WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");
  $db->Query("DELETE FROM listconfig WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");
  $db->Query("DELETE FROM listurls WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");

  $db->Query("SELECT email FROM listowner WHERE listownerID='$_SESSION[aalistownerID]'");
  list($email) = $db->FetchRow();

	// delete from pxm database
  $db->SelectDB("pxm");
  $db->Query("DELETE FROM orders WHERE listownername='$_SESSION[aalistownername]' AND listname='$aListname'");
  $db->Query("DELETE FROM extended WHERE listownername='$_SESSION[aalistownername]' AND listname='$aListname'");
  $db->Query("DELETE FROM clients WHERE listname='$aListname' AND listownerID='$_SESSION[aalistownerID]'");
  $db->SelectDB("mle");
}

$db->Query("DELETE FROM listowner WHERE listownerID='$_SESSION[aalistownerID]'");

?>