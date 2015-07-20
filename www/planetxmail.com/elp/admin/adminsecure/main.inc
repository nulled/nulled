<?php
include("../../mle/mlpsecure/config/classes.inc");
include("../../mle/mlpsecure/validationfunctions.php");

$db = new MySQL_Access("elp");

if ($submitted=="getprofile")
{
  header("Location: showmember.php?elpmember=$member");
  exit;
}
else if ($submitted=="search")
{
  $usertosearch = trim($usertosearch);

  if ($searchby=="username")
    $db->Query("SELECT username FROM users WHERE username='$usertosearch' AND verified='1' AND elpownername='$_SESSION[aaelp]ownername'");
  else
    $db->Query("SELECT username FROM users WHERE email='$usertosearch' AND verified='1' AND elpownername='$_SESSION[aaelp]ownername'");

  if (! $db->rows) $notValid = "No member match found.";
  else
  {
  	list($member) = $db->FetchRow();

    header("Location: showmember.php?elpmember=$member");
    exit;
  }
}
else if ($submitted=="deleteunverifiedmember")
{
  $db->Query("DELETE FROM users WHERE username='$member' AND elpownername='$_SESSION[aaelp]ownername'");
}
else if ($submitted=="resetpassword")
{
  $db->Query("UPDATE elpowners SET password='96e79218965eb72c92a549dd5a330112' WHERE elpownername='$_SESSION[aaelp]ownername'");
}
else if ($submitted=="deleteelpowner"&&$_SESSION['aaadminpsk'])
{
	$db->Query("SELECT titlegraphic FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
  list($titlegraphic) = $db->FetchRow();
  @unlink($titlegraphic);

  $db->Query("DELETE FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
  $db->Query("DELETE FROM users WHERE elpownername='$_SESSION[aaelp]ownername'");
  $db->Query("DELETE FROM ipaddresses WHERE elpownername='$_SESSION[aaelp]ownername'");
  $db->Query("DELETE FROM membertrans WHERE elpownername='$_SESSION[aaelp]ownername'");
  $db->Query("DELETE FROM elpownertrans WHERE elpownername='$_SESSION[aaelp]ownername'");
	$db->Query("DELETE FROM system WHERE elpownername='$_SESSION[aaelp]ownername'");

  // saved for referencing our profits as a whole, only paid billing periods
  $newname = trim(substr($_SESSION[aaelp]ownername, 0, 13));
  $deleteID = generateID(5);
  $deletedelpownername = $newname."_GONE".$deleteID;
  $db->Query("UPDATE billingperiods SET elpownername='$deletedelpownername' WHERE paid='1' AND elpownername='$_SESSION[aaelp]ownername'");

  // delete the rest of the unpaid
  $db->Query("DELETE FROM billingperiods WHERE elpownername='$_SESSION[aaelp]ownername'");

  header("Location: logout.php");
  exit;
}

$db->Query("SELECT username FROM users WHERE paid='1' AND elpownername='$_SESSION[aaelp]ownername' AND memtype='lite' ORDER BY username");
$liteData = $db->result;
$liteNum = $db->rows;

$db->Query("SELECT username FROM users WHERE paid='0' AND elpownername='$_SESSION[aaelp]ownername' AND memtype='lite' ORDER BY username");
$unvliteData = $db->result;
$unvliteNum = $db->rows;

$db->Query("SELECT username FROM users WHERE paid='1' AND elpownername='$_SESSION[aaelp]ownername' AND memtype='pro' ORDER BY username");
$memData = $db->result;
$memNum = $db->rows;

$totalMem = $memNum + $liteNum;

$db->Query("SELECT username FROM users WHERE paid='0' AND elpownername='$_SESSION[aaelp]ownername' AND memtype='pro' ORDER BY username");
$unvData = $db->result;
$unvNum = $db->rows;

$db->Query("SELECT elpownername FROM elpowners ORDER BY elpownername");
$elpowners = $db->result;

?>