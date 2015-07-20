<?php
include("mlpsecure/config/classes.inc");

$db = new Mysql_Access();

$parts  = explode('|', $affid);

$userID = strrev(trim($parts[0]));
$listhash = strtolower(($parts[1]));

if (strlen($userID) != 10 || strlen($listhash) != 5)
{
  header("Location: logininvalid.php");
	exit;
}

if (! $db->Query("SELECT listname, listownerID FROM listurls WHERE listhash='$listhash'"))
{
	header("Location: logininvalid.php");
	exit;
}
list($listname, $listownerID) = $db->FetchRow();

if (! $db->Query("SELECT referer, freeearnedcredits, proearnedcredits, exeearnedcredits FROM listconfig WHERE listownerID='$listownerID' AND listname='$listname'"))
{
  header("Location: login.php?l=$listhash");
  exit;
}
list($referrallink, $freeearnedcredits, $proearnedcredits, $exeearnedcredits) = $db->FetchRow();

// if member refering is valid, set cookie for prospect, then redirect to referal location
if ($db->Query("SELECT status FROM users WHERE userID='$userID' AND verified='yes' AND listname='$listname' AND listownerID='$listownerID'"))
  setcookie("$listhash", "$affid", time()+999999999);

if ($referrallink == '' OR ! @file_get_contents($referrallink))
{
  header("Location: login.php?l=$listhash");
  exit;
}
else
{
  header("Location: $referrallink");
  exit;
}

?>