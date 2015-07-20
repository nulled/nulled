<?php
include("/home/nulled/www/planetxmail.com/phpsecure/cbvalid.php");
include("/home/nulled/www/planetxmail.com/phpsecure/classes.inc");

if ($cbreceipt)
{
	if (! $u || !$l || !$s || !$seed || !$cbpop)
	{
	  echo "Error: Missing l or u or s SEED or CBPOP. Please contact: <b>accounts@planetxmail.com</b>";
	  //@mail("accounts@planetxmail.com", "upgradethankyou.php Error", "l: $l\nseed: $seed\nu: $u\ns: $s\ncbpop: $cbpop\nURL plus params: $HTTP_HOST.$REQUEST_URI", $headers);
	  exit;
	}

  $db = new MySQL_Access("mle");

  $db->Query("SELECT listname, listownerID FROM listurls WHERE listhash='$l'");
  list($list, $id) = $db->FetchRow();

  $db->Query("SELECT paylinkparams FROM listmanager WHERE listname='$list' AND listownerID='$id'");
  list($paylinkparms) = $db->FetchRow();

  $parts = explode("|", $paylinkparms);
  $cgikey = trim($parts[12]);

  if (! cbValid($seed, $cbpop, $cgikey))
  {
    echo "<h2>Error: Invalid ClickBank transaction!</h2>";
    //@mail("accounts@planetxmail.com", "upgradethankyou.php Clickbank FRAUD!", "l: $l", $headers);
    exit;
  }

  // check if seed is in database if so reject transaction
  $db->Query("SELECT COUNT(*) FROM cbseeds WHERE seed='$seed' LIMIT 1");
  list($seedfound) = $db->FetchRow();

  $db->Query("SELECT COUNT(*) FROM transactions WHERE receipt='$cbreceipt' AND listhash='$l' LIMIT 1");
  list($cbreceiptfound) = $db->FetchRow();

  if ($seedfound)
  {
  	echo "<h2>Error: Transaction already processed!</h2>";
  	//@mail("accounts@planetxmail.com", "Duplicate SEED in upgradethankyou.php", "Duplicate SEED found!\nu: $u\nseed: $seed\ncbpop: $cbpop", $headers);
    exit;
  }

  if ($cbreceiptfound)
  {
  	echo "<h2>Error: Transaction already processed!  Duplicate receipt found.</h2>";
  	//@mail("accounts@planetxmail.com", "Duplicate CBRECEIPT in upgradethankyou.php", "Duplicate CBRECEIPT found!\nu: $u\nseed: $seed\ncbpop: $cbpop", $headers);
    exit;
  }

  $db->Query("INSERT INTO cbseeds VALUES('$seed')");

  // all checks pass
  // check if userID is there fetch referer
  if ($db->Query("SELECT username, referer FROM users WHERE userID='$u'"))
  	list($username, $referer) = $db->FetchRow();
  else
  {
  	echo "ERROR: user not found. Admins have been notified.";
  	//@mail("accounts@planetxmail.com", "upgradethankyou.php ERROR", "u: $u not found\nl: $l");
  	exit;
  }

	$db->Query("UPDATE users SET memberpaid='1', status='$s', datesignedup=NOW() WHERE userID='$u'");

	$db->Query("SELECT fromname, adminemail FROM listmanager WHERE listname='$list' AND listownerID='$id'");
	list($fromname, $adminemail) = $db->FetchRow();

	$headers = "From: $fromname <$adminemail>";

	// check if commission is owed and on
	$db->Query("SELECT costofpro, costofexe, commission, referer FROM listconfig WHERE listname='$list' AND listownerID='$id'");
	list($costofpro, $costofexe, $commission, $refererON) = $db->FetchRow();
	list($commissionpro, $commissionexe, $allowcommissions) = explode("|", $commission);
	list($signupcostpro, $renewalcostpro, $upgradecostpro) = explode("|", $costofpro);
	list($signupcostexe, $renewalcostexe, $upgradecostexe) = explode("|", $costofexe);

	if ($s=="pro") $profits = $upgradecostpro;
	else if ($s=="exe") $profits = $upgradecostexe;
	else
	{
		echo "Status invalid.  Admins have been contacted.";
		//@mail("accounts@planetxmail.com", "upgradethankyou.php ERROR", "Status Invalid status: $s");
		exit;
	}

	$commissionowed = 0;
	if ($refererON AND $s!="mem" AND $referer AND ($allowcommissions=="2" OR $allowcommissions=="3"))
	{
		if ($s=="pro" AND $commissionpro)
		{
			$commissionowed = number_format(($profits*($commissionpro/100)), '2', '.', '');
		}
		else if ($commissionexe)
		{
			$commissionowed = number_format(($profits*($commissionexe/100)), '2', '.', '');
		}
	}

	$today = date("F j, Y  H:i");

	@mail($adminemail, "$list - Member Upgraded", "Member Upgraded.\n\nList Name: $list\nUsername: $username\nStatus: $s\nMethod: ClickBank\nAmount: $profits\nReceipt: $cbreceipt\nDate: $today", $headers);
	//@mail("accounts@planetxmail.com", "$list - Member Upgraded", "Member Upgraded.\n\nList Name: $list\nUsername: $username\nStatus: $s\nMethod: ClickBank\nAmount: $profits\nReceipt: $cbreceipt\nDate: $today", $headers);

	// add to transactions
	$db->Query("INSERT INTO transactions VALUES('','$l','$u','upgrade','$profits','$commissionowed','0','clickbank','$cbreceipt',NOW())");
}

?>