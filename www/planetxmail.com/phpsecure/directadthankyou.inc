<?php
include('/home/nulled/www/planetxmail.com/phpsecure/cbvalid.php');
include('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
include('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$headers = "From: PXM <do_not_reply@planetxmail.com>";

function process_directad($db, $id, $mop, $page, $receipt, $headers)
{
  $date = date('F j, Y');

  if ($db->Query("SELECT email, numdays, amount, ad, receipt FROM directads WHERE id='$id' AND page='$page'"))
  {
    list($email, $numDays, $amount, $admessage, $r) = $db->FetchRow();

    if ($r != '')  exit('<h2>Order has already been processed!</h2>');

    $db->Query("UPDATE directads SET receipt='$receipt', mop='$mop' WHERE id='$id' AND page='$page'");
    $db->Query("DELETE FROM directads WHERE mop='' AND page='$page' AND (UNIX_TIMESTAMP(NOW()) - 172800) >= UNIX_TIMESTAMP(datesubmitted)");

    // mail buyer
    $subject = "Planet X Mail Direct Exposure AD receipt.";
    $message = file_get_contents("/home/nulled/www/planetxmail.com/messages/directadreceipt.txt");
    $message = str_replace("[numdays]", $numDays, $message);
    $message = str_replace("[message]", $admessage, $message);
    $message = str_replace("[mop]", "ClickBank", $message);
    $message = str_replace("[price]", $amount, $message);
    $message = str_replace("[date]", $date, $message);

    $message = wordwrap($message, 70);

    @mail($email, $subject, $message, $headers);
    @mail("elitescripts2000@yahoo.com", $subject, $message, $headers);

    $amount -= 1;
		$fees = $amount * .075;
		$amount -= $fees;
		$profits = number_format($amount, 2, '.', '');

		// record in transactions table
		$db->SelectDB("pxm");
		$db->Query("INSERT INTO transactions VALUES('','directad','$profits','$mop','$receipt',NOW())");
  }
  else
  {
    echo "Error: Processing your order.  The Admins have been automatically mailed.  Stand By.  Or contact: <b>elitescripts2000@yahoo.com</b>";
    @mail('elitescripts2000@yahoo.com', 'directad check POST', print_r($_POST, 1), $headers);
    @mail('elitescripts2000@yahoo.com', 'directad check GET',  print_r($_GET, 1), $headers);
  }
}

if ($_GET['cbreceipt'])
{
  // tvid is clickbank specific custom param
  $vtid = trim($_GET['vtid']);
  list($id, $page) = explode('O', $vtid);

  $id = trim($id);
  $page = trim($page);

  $cbreceipt = $_GET['cbreceipt'];

  if (! cbValid())
  {
    echo "<h2>Error: Invalid ClickBank transaction!</h2>";
    @mail("elitescripts2000@yahoo.com", "Direct AD cbValid FAILED", "id=$id cbpop=$cbpop cbreceipt=$cbreceipt item=$item time=$time", $headers);
    exit;
  }

  process_directad(new MySQL_Access('mle'), $id, 'clickbank', $page, $cbreceipt, $headers);
}
else if ($_POST['ap_securitycode']) // alertpay
{
  $ap_custfirstname    = $_POST['ap_custfirstname'];
  $ap_custlastname     = $_POST['ap_custlastname'];
  $ap_custemailaddress = $_POST['ap_custemailaddress'];
  $ap_itemname         = $_POST['ap_itemname'];
  $ap_quantity         = $_POST['ap_quantity'];
  $ap_amount           = $_POST['ap_amount'];
  $ap_totalamount      = $_POST['ap_totalamount'];
  $ap_referencenumber  = $_POST['ap_referencenumber'];
  $ap_status           = $_POST['ap_status'];
  $apc_1               = $_POST['apc_1'];
  $apc_2               = $_POST['apc_2'];
  $ap_securitycode     = $_POST['ap_securitycode'];

  $id   = $apc_1;
  $page = $apc_2;

  if ('lk7f53bPo/6P7oF5QgR6wQ' == $ap_securitycode)
    process_directad(new MySQL_Access('mle'), $id, 'alertpay', $page, $ap_referencenumber, $headers);
  else
  {
    echo "<h2>Error: Invalid AlertPay transaction!</h2>";
    @mail("elitescripts2000@yahoo.com", "Direct AD AlertPay Hash keys do not match", "ap_securitycode=$ap_securitycode", $headers);
    unset($id);
  }
}

?>
