<?php
include("phpsecure/classes.inc");

$db = new MySQL_Access("pxm");

if ($submitted == "buylist")
{
	// redirect cuz paypal banned planetxmail.com
	header("Location: http://planetxforms.com/s4s.php?id=$id");
	exit;
}
else
{
	$db->Query("SELECT id, listname, listownername FROM orders WHERE howheard LIKE 'cancelled' ORDER BY listname");
	$lists4sale = $db->result;

	$db->SelectDB("mle");

  $price = $nummemactive = $numproactive = $numexeactive = $nummeminactive = $numproinactive = $numexeinactive = $totalmemactive = $totalmeminactive = array();
	while (list($id, $listname, $listownername) = mysqli_fetch_row($lists4sale))
	{
		$db->Query("SELECT listownerID FROM listowner WHERE username='$listownername'");
		list($listownerID) = $db->FetchRow();

		$listnames[] = $listname;
		$listids[] = $id;

		// get active members
		$db->Query("SELECT COUNT(*) FROM users WHERE listname='$listname' AND listownerID='$listownerID' AND status='mem' AND RIGHT(listemail, 11)!='unconfirmed' AND listemail!='' AND verified='yes'");
		list($nummemactive[]) = $db->FetchRow();

		$db->Query("SELECT COUNT(*) FROM users WHERE listname='$listname' AND listownerID='$listownerID' AND status='pro' AND RIGHT(listemail, 11)!='unconfirmed' AND listemail!='' AND verified='yes'");
		list($numproactive[]) = $db->FetchRow();

		$db->Query("SELECT COUNT(*) FROM users WHERE listname='$listname' AND listownerID='$listownerID' AND status='exe' AND RIGHT(listemail, 11)!='unconfirmed' AND listemail!='' AND verified='yes'");
		list($numexeactive[]) = $db->FetchRow();

		// get inactive members
		$db->Query("SELECT COUNT(*) FROM users WHERE listname='$listname' AND listownerID='$listownerID' AND status='mem' AND verified='yes'");
		list($nummeminactive[]) = $db->FetchRow();

		$db->Query("SELECT COUNT(*) FROM users WHERE listname='$listname' AND listownerID='$listownerID' AND status='pro' AND verified='yes'");
		list($numproinactive[]) = $db->FetchRow();

		$db->Query("SELECT COUNT(*) FROM users WHERE listname='$listname' AND listownerID='$listownerID' AND status='exe' AND verified='yes'");
		list($numexeinactive[]) = $db->FetchRow();

		$num1 = $nummemactive[count($nummemactive)-1];
		$num2 = $numproactive[count($numproactive)-1];
		$num3 = $numexeactive[count($numexeactive)-1];

		$totalmemactive[] = $num1 + $num2 + $num3;

		$num1 = $nummeminactive[count($nummeminactive)-1];
		$num2 = $numproinactive[count($numproinactive)-1];
		$num3 = $numexeinactive[count($numexeinactive)-1];

		$totalmembers = $totalmeminactive[] = $num1 + $num2 + $num3;

		if ($totalmembers < 200) $price[] = 50;
		else if ($totalmembers < 400 && $totalmembers >= 200) $price[] = 65;
		else if ($totalmembers < 500 && $totalmembers >= 400) $price[] = 75;
		else if ($totalmembers < 600 && $totalmembers >= 500) $price[] = 85;
		else if ($totalmembers < 700 && $totalmembers >= 600) $price[] = 95;
		else if ($totalmembers < 800 && $totalmembers >= 700) $price[] = 100;
		else if ($totalmembers < 900 && $totalmembers >= 800) $price[] = 105;
		else if ($totalmembers < 1000 && $totalmembers >= 900) $price[] = 110;
		else if ($totalmembers < 1100 && $totalmembers >= 1000) $price[] = 115;
		else if ($totalmembers < 1200 && $totalmembers >= 1100) $price[] = 120;
		else if ($totalmembers >= 1200) $price[] = 125;
		else
			$price[] = "Something screwed up in the pricing.";

	  // echo $totalmembers." - ".$price[count($price)-1]."<br />\n";
	}
}

?>

