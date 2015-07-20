<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$setupFee = 25;

if ($submitted == "login")
{
  if ($listowner AND $password)
  {
    $password = md5($password);

    $db = new MySQL_Access('mle');

    $foundOwner = $db->Query("SELECT username FROM listowner WHERE username='$listowner' AND password='$password'");

    $db->SelectDB('pxm');

    $foundOrder = $db->Query("SELECT name FROM orders WHERE listownername='$listowner' AND verified='yes'");

    if ($foundOwner)
    {
      if (! $foundOrder)
        $notValid = "ERROR: You are a listowner with us. But, there was a problem finding your order information.  Please contact: <a href=\"openticket.php\">Click here to mail PlanetXmail</a>";
      else
      {
        session_start();
        @session_destroy();
        session_start();

        $_SESSION['listownername'] = $listowner;

        header("Location: index.php?option=ownersignup");
        exit;
      }
    }
    else
      $notValid = "ERROR: Name or Password is invalid.";
  }
  else
    $notValid = "ERROR: Missing required fields.";
}
else if ($submitted=="signup")
{
  if ($name && $country && $email && $importlist && $listname && $listownername && $listowneremail && $howheard && $mop)
  {
    $email   = trim($email);
    $name    = trim($name);
    $address = trim($address);
    $city    = trim($city);
    $state   = trim($state);
    $zipcode = trim($zipcode);
    $country = trim($country);
    $phone   = trim($phone);
    $listname = trim($listname);
    $listowner = trim($listowner);
    $organization = trim($organization);
    $listowneremail = trim($listowneremail);

    if ($notValid = EmailFormat($email)) {}
    else if ($notValid = EmailFormat($listowneremail)) {}
    else if (has_space($listownername)) $notValid = "ERROR: List Owner Name has a space.";
    else if (has_weird($listownername)) $notValid = "ERROR: List Owner Name must have A-Z, a-z, 0-9 or _ only.";
    else if (has_illegal($listownername)) $notValid = "ERROR: List Owner Name has illegal characters.";
    else if (strlen($listownername)>20) $notValid = "ERROR: List Owner Name canhave 20 chars MAX.";

    else if (has_space($listname)) $notValid = "ERROR: List Name has a space.";
    else if (has_weird($listname)) $notValid = "ERROR: List Name must have A-Z, a-z, 0-9 or _ only.";
    else if (has_illegal($listname)) $notValid = "ERROR: List Name has illegal characters.";
    else if (strlen($listname)>20) $notValid = "ERROR: List Name can have 20 chars MAX.";
    else $notValid = "";

    $db = new MySQL_Access('mle');

    if ($db->Query("SELECT username FROM listowner WHERE username='{$listownername}'"))
      $notValid = "ERROR: List Owner Name not available.  Pick another.";

    if (! $whichlist) $notValid = "ERROR: You need to pick a Type of List.";

    if (! $notValid)
    {
      // assign List Type
      if (substr($whichlist, 0, 2)=="sl")
        $listtype = "safelist";
      else if (substr($whichlist, 0, 2)=="nl")
        $listtype = "newsletter";

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

      $db->SelectDB('pxm');

      $db->Query("INSERT INTO orders (name,    email,   listtype,   nummembers,   importlist,   listname,   listownername,  listowneremail,   howheard,    price, verified, datesubmitted, mop, paid)
                              VALUES ('$name','$email','$listtype','$nummembers','$importlist','$listname','$listownername','$listowneremail','$howheard','$price','no',NOW(),'$mop','no')");

      $id = $db->GetLastID();

      // make sure the day of the week is 28 or less
      $db->Query("SELECT datesubmitted FROM orders WHERE id='$id'");
      list($datesubmitted) = $db->FetchRow();

      $parts = preg_split("/[- ]/", $datesubmitted);
      if ($parts[2] > 28)
      {
        $parts[2] = '28';
        $datesubmitted = "$parts[0]-$parts[1]-$parts[2] $parts[3]";
        $db->Query("UPDATE orders SET datesubmitted='$datesubmitted' WHERE id='$id'");
      }

      header ("Location: index.php?option=paylinks&id=$id&mop=$mop");
      exit;
    }
  }
  else
    $notValid = "ERROR: Missing required fields.";
}

?>