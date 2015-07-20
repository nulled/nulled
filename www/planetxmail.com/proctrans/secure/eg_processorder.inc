<?php

function writeproc($str)
{
  if ($fp = @fopen("secure/eg_processorder.log","a"))
  {
  	chmod("secure/eg_processorder.log", 0777);
    fwrite($fp, "$str\n");
    fclose($fp);
  }
  else
  	@mail("accounts@planetxmail.com", "eg_processorder error", "unable to open log file for writting.");
}

function signup($userID, $listhash, $status, $receipt, $profits)
{
	writeproc("signup attempt - userID: $userID - receipt: $receipt");

  if (! $userID)
  {
  	writeproc("Missing required params for: signup\n");
  	exit;
  }

  $db = new MySQL_Access("mle");

  // check if userID is there fetch referer
  if ($db->Query("SELECT username, referer, listname, listownerID FROM users WHERE userID='$userID'"))
  	list($username, $referer, $list, $id) = $db->FetchRow();
  else
  {
  	writeproc("userID not found in signup - userID: $userID\n");
  	exit;
  }

	$db->Query("UPDATE users SET verified='yes', memberpaid='1', status='$status', datesignedup=NOW(), datelastbilled=NOW() WHERE userID='$userID'");

	$db->Query("SELECT fromname, adminemail FROM listmanager WHERE listname='$list' AND listownerID='$id'");
	list($fromname, $adminemail) = $db->FetchRow();

	$headers = "From: $fromname <do_not_reply@planetxmail.com>\r\nReturn-Path: do_not_reply@planetxmail.com";

	// check if commission is owed and on
	$db->Query("SELECT commission, referer FROM listconfig WHERE listname='$list' AND listownerID='$id'");
	list($commission, $refererON) = $db->FetchRow();
	list($commissionpro, $commissionexe, $allowcommissions) = explode("|", $commission);

	$commissionowed = 0;
	if ($refererON && $status!="mem" && $referer)
	{
		if ($status=="pro" && $commissionpro)
		{
			$commissionowed = number_format(($profits*($commissionpro/100)), '2', '.', '');
			writeproc("commissionpro calculated\n");
		}
		else if ($commissionexe)
		{
			$commissionowed = number_format(($profits*($commissionexe/100)), '2', '.', '');
			writeproc("commissionexe calculated\n");
		}
	}

	$today = date("F j, Y  H:i");

	@mail($adminemail, "$list - Member Paid Signup", "New member paid and signed up.\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: egold\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);
	//@mail("accounts@planetxmail.com", "$list - Member Paid Signup", "New member paid and signed up.\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: egold\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);

	// add to transactions
	$db->Query("INSERT INTO transactions VALUES('','$listhash','$userID','signup','$profits','$commissionowed','0','egold','$receipt',NOW())");
}

function renewal($userID, $listhash, $receipt, $profits)
{
	writeproc("renewal attempt - userID: $userID - receipt: $receipt");

  if (! $userID)
  {
  	writeproc("Missing required params for: renewal\n");
  	exit;
  }

  $db = new MySQL_Access("mle");

  // check if userID is there fetch referer
  if ($db->Query("SELECT username, referer, listname, listownerID, $status FROM users WHERE userID='$userID'"))
  	list($username, $referer, $list, $id, $status) = $db->FetchRow();
  else
  {
  	writeproc("userID not found in renewal - userID: $userID\n");
  	exit;
  }

	$db->Query("UPDATE users SET memberpaid='1' WHERE userID='$userID'");

	$db->Query("SELECT fromname, adminemail FROM listmanager WHERE listname='$list' AND listownerID='$id'");
	list($fromname, $adminemail) = $db->FetchRow();

	$headers = "From: $fromname <do_not_reply@planetxmail.com>\r\nReturn-Path: do_not_reply@planetxmail.com";

	// check if commission is owed and on
	$db->Query("SELECT commission, referer FROM listconfig WHERE listname='$list' AND listownerID='$id'");
	list($commission, $refererON) = $db->FetchRow();
	list($commissionpro, $commissionexe, $allowcommissions) = explode("|", $commission);

	$commissionowed = 0;
	if ($refererON && $status!="mem" && $referer && ($allowcommissions=="1" || $allowcommissions=="3"))
	{
		if ($status=="pro" && $commissionpro)
		{
			$commissionowed = number_format(($profits*($commissionpro/100)), '2', '.', '');
			writeproc("commissionpro calculated\n");
		}
		else if ($commissionexe)
		{
			$commissionowed = number_format(($profits*($commissionexe/100)), '2', '.', '');
			writeproc("commissionexe calculated\n");
		}
	}

	$today = date("F j, Y  H:i");

	@mail($adminemail, "$list - Member Paid Renewal", "New member renewed their membership\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: egold\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);
	//@mail("accounts@planetxmail.com", "$list - Member Paid Renewal", "New member renewed their membership\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: egold\nAmount: $profits\nDate: $today", $headers);

	// add to transactions
	$db->Query("INSERT INTO transactions VALUES('','$listhash','$userID','renewal','$profits','$commissionowed','0','egold','$receipt',NOW())");
}

function upgrade($userID, $listhash, $status, $receipt, $profits)
{
	writeproc("upgrade attempt - userID: $userID - receipt: $receipt");

  if (! $userID)
  {
  	writeproc("Missing required params for: upgrade\n");
  	exit;
  }

  $db = new MySQL_Access("mle");

  // check if userID is there fetch referer
  if ($db->Query("SELECT username, referer, listname, listownerID FROM users WHERE userID='$userID'"))
  	list($username, $referer, $list, $id) = $db->FetchRow();
  else
  {
  	writeproc("userID not found in upgrade - userID: $userID\n");
  	exit;
  }

	$db->Query("UPDATE users SET memberpaid='1', status='$status', datesignedup=NOW() WHERE userID='$userID'");

	$db->Query("SELECT fromname, adminemail FROM listmanager WHERE listname='$list' AND listownerID='$id'");
	list($fromname, $adminemail) = $db->FetchRow();

	$headers = "From: $fromname <do_not_reply@planetxmail.com>\r\nReturn-Path: do_not_reply@planetxmail.com";

	// check if commission is owed and on
	$db->Query("SELECT commission, referer FROM listconfig WHERE listname='$list' AND listownerID='$id'");
	list($commission, $refererON) = $db->FetchRow();
	list($commissionpro, $commissionexe, $allowcommissions) = explode("|", $commission);

	$commissionowed = 0;
	if ($refererON && $status!="mem" && $referer && ($allowcommissions=="2" || $allowcommissions=="3"))
	{
		if ($status=="pro" && $commissionpro)
		{
			$commissionowed = number_format(($profits*($commissionpro/100)), '2', '.', '');
			writeproc("commissionpro calculated: \$ $commissionowed\n");
		}
		else if ($commissionexe)
		{
			$commissionowed = number_format(($profits*($commissionexe/100)), '2', '.', '');
			writeproc("commissionexe calculated \$ $commissionowed\n");
		}
	}

	$today = date("F j, Y  H:i");

	@mail($adminemail, "$list - Member Paid for Upgrade", "New member Upgraded their membership\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: egold\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);
	//@mail("accounts@planetxmail.com", "$list - Member Paid for Upgrade", "New member Upgraded their membership\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: egold\nAmount: $profits\nDate: $today", $headers);

	// add to transactions
	$db->Query("INSERT INTO transactions VALUES('','$listhash','$userID','upgrade','$profits','$commissionowed','0','egold','$receipt',NOW())");
}

// assign posted variables to local variables
$payee_account      = $_POST['PAYEE_ACCOUNT'];
$v2_hash            = $_POST['V2_HASH'];
$timestampgmt       = $_POST['TIMESTAMPGMT'];
$feeweight          = $_POST['FEEWEIGHT'];
$usd_per_ounce      = $_POST['USD_PER_OUNCE'];
$handshake_hash     = $_POST['HANDSHAKE_HASH'];
$payer_account      = $_POST['PAYER_ACCOUNT'];
$payment_batch_num  = $_POST['PAYMENT_BATCH_NUM'];
$payment_metal_id   = $_POST['PAYMENT_METAL_ID'];
$payment_units      = $_POST['PAYMENT_UNITS'];
$payment_amount     = $_POST['PAYMENT_AMOUNT'];
$payment_id 			  = $_POST['PAYMENT_ID'];
$actual_payment_ounces  = $_POST['ACTUAL_PAYMENT_OUNCES'];

// baggage defined by me
$server			 = $_POST['SERVER_NAME'];
$product     = $_POST['PRODUCT'];
$username    = $_POST['USERNAME'];
$owner    	 = $_POST['OWNER'];
$extra    	 = $_POST['EXTRA'];

if ($server!="PXMO")
{
	writeproc("- SERVER UNKNOWN!\n");
	exit;
}

$today = date("F j, Y");
writeproc("***************************\n$today - New transaction start");

writeproc("---------------");
writeproc("payee_account = $payee_account");
writeproc("timestampgmt = $timestampgmt");
writeproc("feeweight = $feeweight");
writeproc("usd_per_ounce = $usd_per_ounce");
writeproc("handshake_hash = $handshake_hash");
writeproc("payer_account = $payer_account");
writeproc("payment_batch_num = $payment_batch_num");
writeproc("payment_metal_id = $payment_metal_id");
writeproc("payment_units = $payment_units");
writeproc("payment_amount = $payment_amount");
writeproc("payment_id = $payment_id");
writeproc("actual_payment_ounces = $actual_payment_ounces");
writeproc("---------------");
writeproc("server = $server");
writeproc("product = $product");
writeproc("username = $username");
writeproc("owner = $owner");
writeproc("extra = $extra");
writeproc("---------------");

include("/home/nulled/www/planetxmail.com/phpsecure/classes.inc");

// fetch alt pass phrase
$db = new MySQL_Access("mle");

$db->Query("SELECT listname, listownerID FROM listurls WHERE listhash='$owner'");
list($list, $id) = $db->FetchRow();

if ($db->Query("SELECT paylinkparams FROM listmanager WHERE listname='$list' AND listownerID='$id'"))
{
	list($params) = $db->FetchRow();

	$parts = explode("|", $params);
	$egoldaltphrase = trim($parts[9]);

	if (! $egoldaltphrase)
	{
		writeproc("Alt pass phrase is blank.\n");
		exit;
	}
}
else
{
	writeproc("Owner param not found to fetch alt pass phrase.\n");
	exit;
}


$altpassphrasehash = strtoupper(md5($egoldaltphrase));
$hashkey = strtoupper(md5("$payment_id:$payee_account:$payment_amount:$payment_units:$payment_metal_id:$payment_batch_num:$payer_account:$altpassphrasehash:$actual_payment_ounces:$usd_per_ounce:$feeweight:$timestampgmt"));

writeproc("$v2_hash = $hashkey");

if ($v2_hash != $hashkey)
{
  writeproc("Hash keys do not match\n");
  exit;
}

$profits = number_format($payment_amount, 2, '.', '');

switch($product)
{
  case "signup":
  	signup($username, $owner, $extra, $payment_batch_num, $profits);
    break;
  case "renewal":
  	renewal($username, $owner, $payment_batch_num, $profits);
    break;
  case "upgrade":
  	upgrade($username, $owner, $extra, $payment_batch_num, $profits);
    break;
	default:
		writeproc("Product not recognized\n");
		exit;
}

writeproc("---=== END TRANSACTION ===---\n");

?>