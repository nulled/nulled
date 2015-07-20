<?php
if ($id==""||$o=="")
{
	echo "Missing required params.";
	exit;
}

include("../mle/mlpsecure/validationfunctions.php");
include("../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

////// Check for Paid, bypassed, outstanding Periods. ///////
$db->Query("SELECT amountowed, paid, bypassed, dateowed FROM billingperiods WHERE id='$id' AND elpownername='$o'");
if ($db->rows)
{
	list($amountowed, $paid, $bypassed, $billingdate) = $db->FetchRow();

	if ($paid)
	{
		// check for outstanding bills
		$db->Query("SELECT id, dateowed FROM billingperiods WHERE paid='0' AND bypassed='0' AND elpownername='$o'");

		if ($db->rows)
		{
			list($nextID, $dateowed) = $db->FetchRow();
			$dateowed = mysql_datetime_to_humandate($dateowed);

			echo "You already paid this Billing Period!  But, you do have a more recent <b>outstanding</b> Billing Period you owe.<br><br>\n";
			echo "<a href=\"http://www.planetxmail.com/elp/elpownerpaylinks.php?id=$nextID&o=$o\">Click here</a> to pay this <b>outstanding</b> Billing Period.<br><br>\n";
			echo "You can view its transaction details by <a href=\"http://www.planetxmail.com/elp/admin/indexelpowner.php\" target=\"_blank\">logging into your ELP Admin control</a> and referencing:<br><br>\n";
			echo "Transaction ID: <b>$nextID</b><br>\nPeriod Ending Date: <b>$dateowed</b>\n";
		}
		else
			echo "You already paid this Billing Period!<br><br>You have <b>NO outstanding Billing Periods</b> to pay.";
	}
	else if ($bypassed)
	{
		$db->Query("SELECT id FROM billingperiods WHERE paid='0' AND bypassed='0' AND elpownername='$o'");
		list($nextID) = $db->FetchRow();

		echo "This Billing Period was <b>\"BYPASSED\"</b>. Meaning you were late in paying so was merged with the <b>NEXT Billing Period</b>.<br><br>\n";
		echo "<a href=\"http://www.planetxmail.com/elp/elpownerpaylinks.php?id=$nextID&o=$o\">Click here</a> to pay the <b>NEXT</b> Billing Period which will include this one.";
	}
	else
	{
		// payment needed, build the payment links
		$db->Query("SELECT fname, lname FROM elpowners WHERE elpownername='$o'");
		list($fname, $lname) = $db->FetchRow();

		$billingdate = mysql_datetime_to_humandate($billingdate);

		$pp_email = "accounts@planetxmail.com";
		$egold = "381141";

		//$amountowed = ".05"; // for DEBUGGING

		$billpaylinks = file_get_contents("messages/elpownerpaylinks.txt");

    // pp
		$billpaylinks = str_replace("[pp_email_address]", $pp_email, $billpaylinks);
		$billpaylinks = str_replace("[paypal_custom_params]", "PXM-elp_partner-unused-$o-$id", $billpaylinks);

		// eg
		$billpaylinks = str_replace("[egold_account]", $egold, $billpaylinks);
		$billpaylinks = str_replace("[egold_process_trans_link]", "http://www.planetxmail.com/proctrans/eg_proctrans.php", $billpaylinks);
		$billpaylinks = str_replace("[server_name]", "PXM", $billpaylinks);
		$billpaylinks = str_replace("[product]", "elp_partner", $billpaylinks);
		$billpaylinks = str_replace("[elp_owner]", $o, $billpaylinks);

		// both
		$billpaylinks = str_replace("[price]", $amountowed, $billpaylinks);
		$billpaylinks = str_replace("[payment_complete_link]", "http://www.planetxmail.com/elp/elpownerthankyou.php?id=$id&o=$o", $billpaylinks);
		$billpaylinks = str_replace("[payment_cancel_link]", "http://www.planetxmail.com/elp/canceledorder.php", $billpaylinks);
		$billpaylinks = str_replace("[item_number]", $id, $billpaylinks);

		$good = 1;
	}
}
else
{
	echo "There was an <b>error processing</b> your Billing Period Payment. Contact: <b>accounts@planetxmail.com</b>";
	exit;
}

?>