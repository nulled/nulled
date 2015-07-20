<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

session_start();

if (! $listownername)
{
  header("Location: index.php");
  exit;
}

$db = new MySQL_Access("pxm");

$foundOrder = $db->Query("SELECT * FROM orders WHERE listownername='$listownername' AND verified='yes'");
$data = $db->FetchArray();

if (! $foundOrder)
{
  // send an error code 1 meaning in ownersignup.php but order was not found yet the listowner session variable was some how set.
  $notValid = "ERROR: You are a listowner with us. But, there was a problem finding your order information.  Please contact: <a href=\"openticket.php\">Click here to mail PlanetXmail</a>";
  $notValid = urlencode($notValid);
  header("Location: index.php?option=signup&notValid=$notValid");
  exit;
}

$id      = $data['id'];
$name    = $data['name'];
$address = $data['address'];
$city    = $data['city'];
$state   = $data['state'];
$zipcode = $data['zipcode'];
$country = $data['country'];
$phone   = $data['phone'];
$email   = $data['email'];
$organization   = $data['organization'];
$listowneremail = $data['listowneremail'];

$setupFee = 0;

if ($submitted=="signup")
{
  if ($name && $organization && $address && $city && $state && $zipcode && $country && $phone && $email && $importlist && $listname && $listownername && $listowneremail && $howheard && $mop)
  {
    $db->SelectDB("mle");
    $db->Query("SELECT listownerID FROM listowner WHERE username='$listownername'");
    list($listownerID) = $db->FetchRow();

    if ($notValid = EmailFormat($email)) {}
    else if ($notValid = EmailFormat($listowneremail)) {}
    else if (has_space($listownername)) $notValid = "ERROR: List Owner Name has a space.";
    else if (has_weird($listownername)) $notValid = "ERROR: List Owner Name must have A-Z, a-z, 0-9 or _ only.";
    else if (has_illegal($listownername)) $notValid = "ERROR: List Owner Name has illegal characters.";
    else if (strlen($listownername)>20) $notValid = "ERROR: List Owner Name can have 20 chars MAX.";
    else if (has_space($listname)) $notValid = "ERROR: List Name has a space.";
    else if (has_weird($listname)) $notValid = "ERROR: List Name must have A-Z, a-z, 0-9 or _ only.";
    else if (has_illegal($listname)) $notValid = "ERROR: List Name has illegal characters.";
    else if (strlen($listname)>20) $notValid = "ERROR: List Name can have 20 chars MAX.";
    else if (! $whichlist) $notValid = "ERROR: You need to pick a Type of List and Size of List.";
    else if ($db->Query("SELECT listname FROM listmanager WHERE listname='$listname' AND listownerID='$listownerID'")) $notValid = "ERROR: List Name, <i>$listname</i>, already taken.";
    else
    {
      // assign List Type
      if (substr($whichlist, 0, 2)=="sl")      $listtype = "safelist";
      else if (substr($whichlist, 0, 2)=="nl") $listtype = "newsletter";

      // assign Number of members
      if ($listtype=="safelist")
      {
        if (substr($whichlist, 2, 2)=="1")
        {
          $nummembers = "0-1000";
          $price = $setupFee + 30;
        }
        else if (substr($whichlist, 2, 2)=="2")
        {
          $nummembers = "1001-2000";
          $price = $setupFee + 35;
        }
        else if (substr($whichlist, 2, 2)=="3")
        {
          $nummembers = "2001-3000";
          $price = $setupFee + 40;
        }
        else if (substr($whichlist, 2, 2)=="4")
        {
          $nummembers = "3001-4000";
          $price = $setupFee + 45;
        }
        else if (substr($whichlist, 2, 2)=="5")
        {
          $nummembers = "4001-8000";
          $price = $setupFee + 50;
        }
        else if (substr($whichlist, 2, 2)=="6")
        {
          $nummembers = "8001-10000";
          $price = $setupFee + 55;
        }
        else if (substr($whichlist, 2, 2)=="7")
        {
          $nummembers = "10001-15000";
          $price = $setupFee + 60;
        }
        else if (substr($whichlist, 2, 2)=="8")
        {
          $nummembers = "15001-20000";
          $price = $setupFee + 65;
        }
      }
      else if ($listtype=="newsletter")
      {
        if (substr($whichlist, 2, 2)=="1")
        {
          $nummembers = "0-5000";
          $price = $setupFee + 20;
        }
        else if (substr($whichlist, 2, 2)=="2")
        {
          $nummembers = "5001-10000";
          $price = $setupFee + 25;
        }
        else if (substr($whichlist, 2, 2)=="3")
        {
          $nummembers = "10001-15000";
          $price = $setupFee + 30;
        }
        else if (substr($whichlist, 2, 2)=="4")
        {
          $nummembers = "15001-20000";
          $price = $setupFee + 35;
        }
        else if (substr($whichlist, 2, 2)=="5")
        {
          $nummembers = "20001-40000";
          $price = $setupFee + 40;
        }
        else if (substr($whichlist, 2, 2)=="6")
        {
          $nummembers = "40001-60000";
          $price = $setupFee + 45;
        }
        else if (substr($whichlist, 2, 2)=="7")
        {
          $nummembers = "60001-80000";
          $price = $setupFee + 50;
        }
        else if (substr($whichlist, 2, 2)=="8")
        {
          $nummembers = "80001-100000";
          $price = $setupFee + 55;
        }
      }

      $db->SelectDB("pxm");
      $db->Query("INSERT INTO extended VALUES('','$listownername','$listtype','$nummembers','$importlist','$listname','$howheard','$price','no',NOW(),'$mop','0')");

      $id = mysqli_insert_id($db->link);

      // make sure the day of the week is 28 or less
      $parts = preg_split("/[- ]/", $datesubmitted);
      if ($parts[2]>28)
      {
        $parts[2] = "28";
        $datesubmitted = "$parts[0]-$parts[1]-$parts[2] $parts[3]";
        $db->Query("UPDATE extended SET datesubmitted='$datesubmitted' WHERE id='$id'");
      }

      header ("Location: index.php?option=paylinks&id=$id&ex=1&mop=$mop");
      exit;
    }
  }
  else
    $notValid = "ERROR: Missing required fields.";
}
?>