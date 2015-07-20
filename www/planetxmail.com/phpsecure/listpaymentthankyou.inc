<?php
require_once('phpsecure/cbvalid.php');
require_once('phpsecure/classes.inc');

function process_listpayment($id, $ex, $mop, $receipt, $headers)
{
  $db = new MySQL_Access('pxm');

  if (! is_numeric($id))         exit("<h2>Error: Missing params: id</h2>");
	if ($ex AND ! is_numeric($ex)) exit("<h2>Error: Missing params: ex</h2>");

  if ($ex)
  {
	  if (! $db->Query("SELECT price FROM extended WHERE id='$id'"))
	  {
	    @mail("elitescripts2000@yahoo.com", "PXM List Order error", "The ID was not found in database when the THANK YOU page tried to complete the order.\nID: $id\n");
	    exit("There has been a problem setting up your account. Admins have been notified as we speak.  Their email addres is <b>elitescripts2000@yahoo.com</b> if you do not hear from us in 24 hours.");
	  }
	  list($price) = $db->FetchRow();
	}
	else
	{
		if (! $db->Query("SELECT price FROM orders WHERE id='$id'"))
	  {
	    @mail("elitescripts2000@yahoo.com", "PXM List Order error", "The ID was not found in database when the THANK YOU page tried to complete the order.\nID: $id\n");
	    exit("There has been a problem setting up your account.  Admins have been notified as we speak.  Their email addres is <b>elitescripts2000@yahoo.com</b> if you do not hear from us in 24 hours.");
	  }

	  list($price) = $db->FetchRow();
	  $price -= 25;
	}

	if (! $ex)
	  $db->Query("UPDATE orders SET paid='yes', datesubmitted=NOW() WHERE id='$id'");
	else
	  $db->Query("UPDATE extended SET paid='1', datesubmitted=NOW() WHERE id='$id'");

  if ($mop == 'clickbank')
  {
  	$price -= 1;
  	$fees = $price * .075;
  	$price -= $fees;
  }

  $price = number_format($price, 2, '.', '');

	$db->Query("INSERT INTO transactions VALUES('','pxm_monthly','$price','$mop','$receipt',NOW())");
}

$headers = "From: PXM <do_not_reply@planetxmail.com>";

list($id, $ex) = explode('O', trim($_GET['vtid']));

$id = trim($id);
$ex = trim($ex);

if ($_GET['cbreceipt'])
{
  $cbreceipt = $_GET['cbreceipt'];

  if (! cbValid())
  {
    @mail("elitescripts2000@yahoo.com", "PXM listpayment thankyou CB Error", "id: $id", $headers);
    exit("<h2>Error: Transaction already processed!</h2>");
  }

  process_listpayment($id, $ex, 'clickbank', $cbreceipt, $headers);
}

?>
