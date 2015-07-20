<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/phpsecure/processorder.class.inc');

$db = new MySQL_Access();

if ($submitted=="search")
{
	set_time_limit(0);

  $usertosearch = trim($usertosearch);

	if (strlen($usertosearch)>2)
  {
	  if ($searchby=="username")       $db->Query("SELECT userID FROM users WHERE username LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
	  else if ($searchby=="listemail") $db->Query("SELECT userID FROM users WHERE listemail LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
	  else if ($searchby=="email")     $db->Query("SELECT userID FROM users WHERE email LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
		else if ($searchby=="firstname") $db->Query("SELECT userID FROM users WHERE fname LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
		else if ($searchby=="lastname")  $db->Query("SELECT userID FROM users WHERE lname LIKE '%$usertosearch%' AND listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
	}
	else
		$notValid = "Search must contain at least 3 characters.";

	if (! $notValid)
	{
		while (list($uIDs) = $db->FetchRow()) $totalIDs .= "$uIDs|";

		if ($totalIDs)
		{
			header("Location: searchresults.php?totalIDs=$totalIDs");
		  exit;
		}
		else
			$notValid = "No user match found.";
	}
}
else if ($submitted=="resetpassword")
{
  $db->Query("UPDATE listowner SET password='96e79218965eb72c92a549dd5a330112' WHERE listownerID='$_SESSION[aalistownerID]'");
}
else if ($submitted=="deletelist"||$submitted=="clearlist")
{
  set_time_limit(0);
  $db->Query("SELECT userID FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $allUsers = $db->result;

  while (list($row) = mysqli_fetch_row($allUsers))
  {
    $db->Query("DELETE FROM urlmanager WHERE userID='$row'");
    $db->Query("DELETE FROM urldata WHERE userID='$row'");
    $db->Query("DELETE FROM users WHERE userID='$row'");
  }

  /////////  DELETE AD IMAGES ////////
  $db->Query("SELECT adimage FROM ads WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $adImages = $db->result;

  while (list($img) = mysqli_fetch_row($adImages))
    @unlink($img);

  $db->Query("DELETE FROM ads WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  //////// END DELETE AD IMAGES ///////

  /////////  DELETE BANNER IMAGES ////////
  $db->Query("SELECT banner FROM banners WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $bannerImages = $db->result;

  while (list($img) = mysqli_fetch_row($bannerImages))
    @unlink($img);

  $db->Query("DELETE FROM banners WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  //////// END DELETE BANNER IMAGES //////

  if ($submitted=="clearlist")
  {
    $newlistname = generateID(12);
    $newlistname = "new$newlistname";
    $db->Query("UPDATE listmanager SET listname='$newlistname', fromname='', fromemail='', adminemail='', bounceemail='', listtype='', description='', paymenthtml='', message='', header='', footer='', subconfirm='', subsuccess='', unsubsuccess='', mailingrule='0', created='0', html='' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  }
  else if ($submitted=="deletelist")
    $db->Query("DELETE FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");

  $db->Query("DELETE FROM system WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $db->Query("DELETE FROM banneddomains WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $db->Query("DELETE FROM listconfig WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $db->Query("DELETE FROM listurls WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");

  $db->Query("SELECT email FROM listowner WHERE listownerID='$_SESSION[aalistownerID]'");
  list($email) = $db->FetchRow();

  $db->SelectDB("pxm");
  $db->Query("DELETE FROM orders WHERE listownername='$_SESSION[aalistownername]' AND listname='$_SESSION[aalistname]'");
  $db->Query("DELETE FROM extended WHERE listownername='$_SESSION[aalistownername]' AND listname='$_SESSION[aalistname]'");
  $db->Query("DELETE FROM clients WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $db->SelectDB("mle");

  // get created lists
  $db->Query("SELECT listname FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' AND created='1' LIMIT 1");
  list($createdlistname) = $db->FetchRow();
  $availableList = $db->rows;

  // get uncreated lists
  $db->Query("SELECT listname FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' AND created='0'");
  $availableUncreatedList = $db->rows;

  // if there is an available CREATED list load that, else check if there is an empty list, or create empty list if last one
  if ($availableList)
  {
    $_SESSION['aalistname'] = $createdlistname;
  }
  else
  {
    if ($availableUncreatedList)
    {
      if ($availableUncreatedList==1)
      {
        header("Location: createlist.php?firstList=1");
        exit;
      }
      else
      {
        header("Location: createlist.php");
        exit;
      }
    }
    else
    {
      // last list deleted so add new empty one
      $newlistname = generateID(12);
      $newlistname = "new$newlistname";

      $db->Query("INSERT INTO listmanager VALUES('$_SESSION[aalistownerID]','$newlistname','','','','','','','','','','','','','','','','')");

      header("Location: createlist.php?firstList=1");
      exit;
    }
  }
}
else if ($submitted == 'convert')
{
  $convert = $_POST['convert'];

  if ($convert)
  {
    $po = new ProcessOrder('blah');
    $converted = $po->unmix_data($convert);
  }
  else
    $converted = 'Nothing to convert.';
}
else if ($submitted=="changelist")
{
  if (substr($list, 0, 3)=="new")
  {
    header("Location: createlist.php");
    exit;
  }

  $_SESSION['aalistname'] = $list;
}
else if ($submitted=="changemailingrule")
{
  $db->Query("UPDATE listmanager SET mailingrule='$mailingrule' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
}
else if ($submitted=="createlist")
{
  $listnameID = generateID();
  $listnameID = "new$listnameID";

  $db->Query("INSERT INTO listmanager VALUES('$_SESSION[aalistownerID]','$listnameID','','','','','','','','','','','','','','0','0','')");
}

$db->Query("SELECT listname FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' AND created='1' LIMIT 1");

$noList = (! $db->rows) ? true : false;

if ($noList == false)
{
	$getData = 0;

  require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/getmembers.inc');

  $db->Query("SELECT listtype FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $listtype = $db->FetchRow();

  $db->Query("SELECT listname FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' ORDER BY listname");
  $lists = $db->result;

  $db->Query("SELECT mailingrule FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $mailingrule = $db->FetchRow();

  $db->Query("SELECT listownerID, username FROM listowner ORDER BY username");
  $listowners = $db->result;

  $db->Query("SELECT listhash FROM listurls WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
  list($listhash) = $db->FetchRow();
}

require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/billing.inc');

?>