<?php
include("../../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("elp");

if ($submitted=="generate")
{
	if ($elpmember && $memtype)
	{
		$receipt = trim($receipt);

		if (strlen($receipt)>18) $notValid = "ERROR: Receipt can not exceed 18 chars.";
		else if (strlen($receipt)==0) $notValid = "ERROR: Missing receipt.";
		else
		{
			$db->Query("SELECT commission, monthlycommission, commissionlite FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
			list($commission, $monthlycommission, $commissionlite) = $db->FetchRow();

			if ($transtype=="signup")
				$commissionowed = $commission + $monthlycommission;
			else
				$commissionowed = $monthlycommission;

			if ($elpmember!="test_me")
			{
			  $today = date("F j, Y");

			  if ($memtype=="pro")
			  {
  				if ($transtype=="signup")
  					$db->Query("UPDATE users SET paid='1', blocked='0', verified='1', datelastbilled=NOW() WHERE username='$elpmember' AND elpownername='$_SESSION[aaelp]ownername'");
  				else
  					$db->Query("UPDATE users SET paid='1', blocked='0', verified='1', datelastbilled=NOW() WHERE username='$elpmember' AND elpownername='$_SESSION[aaelp]ownername'");

  				$db->Query("INSERT INTO membertrans VALUES('','$_SESSION[aaelp]ownername','$elpmember','$transtype','$amount','$receipt','$mop',NOW(),'$commissionowed','0')");
			  }
			  else if ($memtype=="lite")
			  {
			    $db->Query("UPDATE users SET paid='1', blocked='0', verified='1', datelastbilled=NOW(), datesignedup=NOW() WHERE username='$elpmember' AND elpownername='$_SESSION[aaelp]ownername'");
			    $db->Query("INSERT INTO membertrans VALUES('','$_SESSION[aaelp]ownername','$elpmember','lite','$amount','$receipt','$mop',NOW(),'$commissionlite','0')");
			  }

			  @mail("accounts@planetxmail.com", "New ELP Member $transtype.", "A $memtype member paid vai $mop MANUAL TRANSACTION.

Username: $elpmember
Amount: \$ $amount USD

Date: $today

ELP Owner Name: $_SESSION[aaelp]ownername", "From: ELP_SYS <accounts@planetxmail.com>");

			}
			else
				$notValid = "<p align=\"left\">ERROR: The test_me account is intended to TEST the paylinks.  Therefore you can not manually set as paid as this would defeat the purpose of TESTING.<br><br>\nPlease review the paylink instructions and goto Edit Config and make sure its all set up correctly. You can test as many times as you need to by just deleting the test_me account and starting the paylink tests over.<br><br>\nThis is all important as this is how you will be getting paid!</p>";
		}
	}
	else
		$notValid = "ERROR: Missing required params.";
}

$db->Query("SELECT paid FROM users WHERE username='$elpmember' AND elpownername='$_SESSION[aaelp]ownername'");
list($paid) = $db->FetchRow();

if ($paid)
{
	header("Location: showmember.php?elpmember=$elpmember");
	exit;
}

$db->Query("SELECT price, monthlyprice, pricelite FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
list($price, $monthlyprice, $pricelite) = $db->FetchRow();

if ($memtype=="pro") $amount = $price;
else $amount = $pricelite;

?>