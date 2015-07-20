<?php

function writeproc($str)
{
  if ($fp = @fopen("secure/pp_processorder.log","a"))
  {
  	chmod("secure/pp_processorder.log", 0777);
    fwrite($fp, "$str\n");
    fclose($fp);
  }
  else
  	@mail("accounts@planetxmail.com", "pp_processorder error", "unable to open log file for writting.");
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

  // check for duplicate receipt
  $db->Query("SELECT COUNT(*) FROM transactions WHERE receipt='$receipt' AND listhash='$listhash' LIMIT 1");
  list($receiptfound) = $db->FetchRow();

  if ($receiptfound)
  {
  	writeproc("receipt already present in signup - receipt: $receipt - listhash: $listhash\n");
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

	@mail($adminemail, "$list - Member Paid Signup", "New member paid and signed up.\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: Paypal\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);
	//@mail("accounts@planetxmail.com", "$list - Member Paid Signup", "New member paid and signed up.\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: Paypal\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);

	// add to transactions
	$db->Query("INSERT INTO transactions VALUES('','$listhash','$userID','signup','$profits','$commissionowed','0','paypal','$receipt',NOW())");
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
  if ($db->Query("SELECT username, referer, listname, listownerID, status FROM users WHERE userID='$userID'"))
  	list($username, $referer, $list, $id, $status) = $db->FetchRow();
  else
  {
  	writeproc("userID not found in renewal - userID: $userID\n");
  	exit;
  }

  // check for duplicate receipt
  $db->Query("SELECT COUNT(*) FROM transactions WHERE receipt='$receipt' AND listhash='$listhash' LIMIT 1");
  list($receiptfound) = $db->FetchRow();

  if ($receiptfound)
  {
  	writeproc("receipt already present in renewal - receipt: $receipt - listhash: $listhash\n");
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

	@mail($adminemail, "$list - Member Paid Renewal", "New member renewed their membership\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: Paypal\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);
	//@mail("accounts@planetxmail.com", "$list - Member Paid Renewal", "New member renewed their membership\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: Paypal\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);

	// add to transactions
	$db->Query("INSERT INTO transactions VALUES('','$listhash','$userID','renewal','$profits','$commissionowed','0','paypal','$receipt',NOW())");
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

  // check for duplicate receipt
  $db->Query("SELECT COUNT(*) FROM transactions WHERE receipt='$receipt' AND listhash='$listhash' LIMIT 1");
  list($receiptfound) = $db->FetchRow();

  if ($receiptfound)
  {
  	writeproc("receipt already present in upgrade - receipt: $receipt - listhash: $listhash\n");
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

	@mail($adminemail, "$list - Member Paid for Upgrade", "New member Upgraded their membership\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: Paypal\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);
	//@mail("accounts@planetxmail.com", "$list - Member Paid for Upgrade", "New member Upgraded their membership\n\nList Name: $list\nUsername: $username\nStatus: $status\nMethod: Paypal\nAmount: $profits\nReceipt: $receipt\nDate: $today", $headers);

	// add to transactions
	$db->Query("INSERT INTO transactions VALUES('','$listhash','$userID','upgrade','$profits','$commissionowed','0','paypal','$receipt',NOW())");
}

// read the post from PayPal system and add 'cmd'
$req = 'cmd=_notify-validate';

foreach ($_POST as $key => $value) {
$value = urlencode(stripslashes($value));
$req .= "&$key=$value";
}

// assign posted variables to local variables
$receiver_email = $_POST['receiver_email'];
$item_name      = $_POST['item_name'];
$custom         = $_POST['custom'];
$payment_status = $_POST['payment_status'];
$payment_gross  = $_POST['payment_gross'];
$payment_fee 	  = $_POST['payment_fee'];
$txn_id         = $_POST['txn_id'];
$payer_email    = $_POST['payer_email'];

$temptransparts = explode("-", $custom);

$server 	= $temptransparts[0];
$product 	= $temptransparts[1];
$username = $temptransparts[2];
$owner 		= $temptransparts[3];
$extra 		= $temptransparts[4];

if ($server!="PXMO")
{
	//writeproc("- SERVER UNKNOWN!\n");
	//@mail("accounts@planetxmail.com", "pp_processorder error", "Server unknown! $server");
	exit;
}

$today = date("F j, Y");
writeproc("*********************************************************************************\n$today - New transaction start");

include("/home/nulled/www/planetxmail.com/phpsecure/classes.inc");

writeproc("item_name = $item_name");
writeproc("custom = $custom");
writeproc("payment_status = $payment_status");
writeproc("payment_gross = $payment_gross");
writeproc("payment_fee = $payment_fee");
writeproc("txn_id = $txn_id");
writeproc("payer_email = $payer_email");
writeproc("---------------");
writeproc("server = $server");
writeproc("product = $product");
writeproc("username = $username");
writeproc("owner = $owner");
writeproc("extra = $extra");
writeproc("---------------");

// post back to PayPal system to validate
$header .= "POST /cgi-bin/webscr HTTP/1.0\r\n";
$header .= "Content-Type: application/x-www-form-urlencoded\r\n";
$header .= "Content-Length: " . strlen ($req) . "\r\n\r\n";
$fp = fsockopen ("www.paypal.com", 80, $errno, $errstr, 30);

if (! $fp)
{
  // HTTP ERROR
  $errorHappened = "$errstr ($errno)";
  writeproc("Tried to re-post back to PayPal ERROR: $errorHappened\n");
  exit;
}
else
{
  fputs ($fp, $header . $req);

  while (! feof($fp))
  {
    $res = fgets ($fp, 1024);

    if (strcmp ($res, "VERIFIED") == 0)
    {
      if ($payment_status=="Completed" || $payment_status=="Pending")
      {
      	//$profits = $payment_gross - $payment_fee;
      	//$profits = number_format($profits, 2, '.', '');

        // process the order
        switch($product)
        {
          case "signup":
          	signup($username, $owner, $extra, $txn_id, $payment_gross);
            break;
          case "renewal":
          	renewal($username, $owner, $txn_id, $payment_gross);
            break;
          case "upgrade":
          	upgrade($username, $owner, $extra, $txn_id, $payment_gross);
            break;
          default:
            writeproc("Product not found!\n");
            fclose ($fp);
            exit;
        }
        break;
      }
      else
      {
        writeproc("Bad Payment Status: $payment_status\n");
        fclose ($fp);
        exit;
      }
    }
    else if (strcmp ($res, "INVALID") == 0)
    {
      writeproc("ALERT!!! INVALID... $res\n");
      @mail("accounts@planetxmail.com", "pp_processorder error", "ALERT!!! INVALID... $res");
      fclose ($fp);
      exit;
    }
  }
  fclose ($fp);
}

writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

?>
