<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access("elp");

if ($submitted=="save")
{
  if ($_SESSION['aaadminpsk'])
  {
    if ($price && $commission && $monthlyprice && $monthlycommission && $pricelite && $commissionlite)
    {
      // totals to check is SIGN UP Profits are in the Positve
      $totalsignupcommission = $commission + $monthlycommission;
      $totalsignup = $price + $monthlyprice;

      if ($pricelite<29)
        $pricelite = 29;

      $paypalaccount    = trim($paypalaccount);
      $egoldaccount     = trim($egoldaccount);
      $egoldaltphrase   = trim($egoldaltphrase);
      $clickbankaccount = trim($clickbankaccount);
      $clickbanklinknumbersignup  = trim($clickbanklinknumbersignup);
      $clickbanklinknumbermonthly = trim($clickbanklinknumbermonthly);
      $clickbanklinknumberlite    = trim($clickbanklinknumberlite);

      if (! is_numeric($price = trim($price))) $notValid = "ERROR: Price not a number.";
      else if (! is_numeric($monthlyprice = trim($monthlyprice))) $notValid = "ERROR: Month price not a number.";
      else if (! is_numeric($commission = trim($commission))) $notValid = "ERROR: Commission not a number.";
      else if (! is_numeric($monthlycommission = trim($monthlycommission))) $notValid = "ERROR: Monthly commission not a number.";
      else if (! is_numeric($pricelite = trim($pricelite))) $notValid = "ERROR: LITE price not a number.";
      else if (! is_numeric($commissionlite = trim($commissionlite))) $notValid = "ERROR: Commission LITE not a number.";
      else if ($price<1) $notValid = "ERROR: Your Sign up fee can not be less then \$ 1";
      else if ($monthlyprice<=$monthlycommission) $notValid = "ERROR: Your Monthly fee can not be less then \$ ".($monthlycommission+1)." <a href=\"#\" onClick=\"window.open('rates.php',0,'height=450,width=650,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\">Click Here for Explaination</a>.";
      else if ($totalsignup<=$totalsignupcommission) $notValid = "Error: Your SIGN UP plus MONTHLY price profits is 0 or less after what you would owe us, per Sign up. <a href=\"#\" onClick=\"window.open('rates.php',0,'height=450,width=650,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\">Click Here for Explaination</a>.";
      else if ($monthlyprice<=$monthlycommission) $notValid = "Error: Your MONTHLY price is too low compared to what you will owe EliteScripts. <a href=\"#\" onClick=\"window.open('rates.php',0,'height=450,width=650,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\">Click Here for Explaination</a>.";
      else if ($notValid = EmailFormat($email)) {}
      else
      {
        $db->Query("UPDATE elpowners SET email='$email', price='$price', commission='$commission', monthlyprice='$monthlyprice', monthlycommission='$monthlycommission', useclickbank='$useclickbank', usepaypal='$usepaypal', useegold='$useegold', clickbanklinknumbersignup='$clickbanklinknumbersignup', clickbanklinknumbermonthly='$clickbanklinknumbermonthly', clickbankaccount='$clickbankaccount', paypalaccount='$paypalaccount', egoldaccount='$egoldaccount', egoldaltphrase='$egoldaltphrase', pricelite='$pricelite', commissionlite='$commissionlite', clickbanklinknumberlite='$clickbanklinknumberlite', useclickbanklite='$useclickbanklite', clickbankkey='$clickbankkey' WHERE elpownername='$_SESSION[aaelp]ownername'");
        $notValid = "Configuration settings updated.";
      }
    }
    else
      $notValid = "ERROR: Missing required parameters.";
  }
  else
  {
    if ($price && $monthlyprice)
    {
      // totals to check is SIGN UP Profits are in the Positve
      $totalsignupcommission = $commission + $monthlycommission;
      $totalsignup = $price + $monthlyprice;

      if ($pricelite<29)
        $pricelite = 29;

      $paypalaccount    = trim($paypalaccount);
      $egoldaccount     = trim($egoldaccount);
      $egoldaltphrase   = trim($egoldaltphrase);
      $clickbankaccount = trim($clickbankaccount);
      $clickbanklinknumbersignup  = trim($clickbanklinknumbersignup);
      $clickbanklinknumbermonthly = trim($clickbanklinknumbermonthly);

      if (! is_numeric($price = trim($price))) $notValid = "ERROR: Price not a number.";
      else if (! is_numeric($monthlyprice = trim($monthlyprice))) $notValid = "ERROR: Month price not a number.";
      else if (! is_numeric($commission = trim($commission))) $notValid = "ERROR: Commission not a number.";
      else if (! is_numeric($monthlycommission = trim($monthlycommission))) $notValid = "ERROR: Monthly commission not a number.";
      else if (! is_numeric($pricelite = trim($pricelite))) $notValid = "ERROR: LITE price not a number.";
      else if (! is_numeric($commissionlite = trim($commissionlite))) $notValid = "ERROR: Commission LITE not a number.";
      else if ($price<1) $notValid = "ERROR: Your Sign up fee can not be less then \$ 1";
      else if ($monthlyprice<=$monthlycommission) $notValid = "ERROR: Your Monthly fee can not be less then \$ ".($monthlycommission+1)." <a href=\"#\" onClick=\"window.open('rates.php',0,'height=450,width=650,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\">Click Here for Explaination</a>.";
      else if ($totalsignup<=$totalsignupcommission) $notValid = "Error: Your SIGN UP plus MONTHLY price profits is 0 or less after what you would owe us, per Sign up. <a href=\"#\" onClick=\"window.open('rates.php',0,'height=450,width=650,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\">Click Here for Explaination</a>.";
      else if ($monthlyprice<=$monthlycommission) $notValid = "Error: Your MONTHLY price is too low compared to what you will owe EliteScripts. <a href=\"#\" onClick=\"window.open('rates.php',0,'height=450,width=650,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')\">Click Here for Explaination</a>.";
      else if ($pricelite<29) $notValid = "ERROR: Your Sign up LITE fee can not be less then \$ 29";
      else if ($notValid = EmailFormat($email)) {}
      else
      {
        $db->Query("UPDATE elpowners SET email='$email', price='$price', monthlyprice='$monthlyprice', useclickbank='$useclickbank', usepaypal='$usepaypal', useegold='$useegold', clickbanklinknumbersignup='$clickbanklinknumbersignup', clickbanklinknumbermonthly='$clickbanklinknumbermonthly', clickbankaccount='$clickbankaccount', paypalaccount='$paypalaccount', egoldaccount='$egoldaccount', egoldaltphrase='$egoldaltphrase', pricelite='$pricelite', clickbanklinknumberlite='$clickbanklinknumberlite', useclickbanklite='$useclickbanklite', clickbankkey='$clickbankkey' WHERE elpownername='$_SESSION[aaelp]ownername'");
        $notValid = "Configuration settings updated.";
      }
    }
    else
      $notValid = "ERROR: Missing required parameters.";
  }
}

$db->Query("SELECT email, price, commission, monthlyprice, monthlycommission, useclickbank, usepaypal, useegold, clickbanklinknumbersignup, clickbanklinknumbermonthly, clickbankaccount, paypalaccount, egoldaccount, egoldaltphrase, pricelite, commissionlite, clickbanklinknumberlite, useclickbanklite, clickbankkey FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
list($email, $price, $commission, $monthlyprice, $monthlycommission, $useclickbank, $usepaypal, $useegold, $clickbanklinknumbersignup, $clickbanklinknumbermonthly, $clickbankaccount, $paypalaccount, $egoldaccount, $egoldaltphrase, $pricelite, $commissionlite, $clickbanklinknumberlite, $useclickbanklite, $clickbankkey) = $db->FetchRow();

?>