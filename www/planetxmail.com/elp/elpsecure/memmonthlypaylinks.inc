<?php
if (! $u || ! $o)
{
	echo "Missing required params. Contact: <b>accounts@planetxmail.com</b>";
	exit;
}

include("../mle/mlpsecure/validationfunctions.php");
include("../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

$db->Query("SELECT useclickbank, usepaypal, useegold, clickbanklinknumbermonthly, clickbankaccount, paypalaccount, egoldaccount, email, monthlyprice, fname, lname FROM elpowners WHERE elpownername='$o'");

if ($db->rows)
{
	list($useclickbank, $usepaypal, $useegold, $clickbanklinknumbermonthly, $clickbankaccount, $paypalaccount, $egoldaccount, $email, $monthlyprice, $fname, $lname) = $db->FetchRow();

	$total = $monthlyprice;

	if ($total) $centsperday = $total / 30;

	if (strtolower($u)=="test_me")
		$total = .05;

	$db->Query("SELECT fname, paid FROM users WHERE username='$u' AND elpownername='$o'");
	list($ufname, $paid) = $db->FetchRow();

	if (! $paid)
	{
		if ($usepaypal)    $monthlypaylinks .= file_get_contents("messages/paypal.txt");
		if ($useegold)	   $monthlypaylinks .= file_get_contents("messages/egold.txt");
		if ($useclickbank) $monthlypaylinks .= file_get_contents("messages/clickbank.txt");

		$monthlypaylinks = str_replace("[memo]", "ELP_Member_Monthly", $monthlypaylinks);
		$monthlypaylinks = str_replace("[item_name]", "ELP Monthly - $u - $o", $monthlypaylinks);
		$monthlypaylinks = str_replace("[price]", $total, $monthlypaylinks);
		$monthlypaylinks = str_replace("[payment_thankyou_link]", "http://www.planetxmail.com/elp/memmonthlythankyou.php?u=$u&o=$o", $monthlypaylinks);
		$monthlypaylinks = str_replace("[payment_cancel_link]", "http://www.planetxmail.com/elp/canceledorder.php", $monthlypaylinks);

		// paypal proc trans params
		$monthlypaylinks = str_replace("[paypal_account]", $paypalaccount, $monthlypaylinks);
		$monthlypaylinks = str_replace("[paypal_custom]", "PXM-elp_mem_monthly-$u-$o", $monthlypaylinks);

		// e-gold proc trans params
		$monthlypaylinks = str_replace("[egold_account]", $egoldaccount, $monthlypaylinks);
		$monthlypaylinks = str_replace("[fname_lname]", "$fname $lname", $monthlypaylinks);
		$monthlypaylinks = str_replace("[server_name]", "PXM", $monthlypaylinks);
		$monthlypaylinks = str_replace("[product]", "elp_mem_monthly", $monthlypaylinks);
		$monthlypaylinks = str_replace("[username]", $u, $monthlypaylinks);
		$monthlypaylinks = str_replace("[elp_owner]", $o, $monthlypaylinks);
		$monthlypaylinks = str_replace("[egold_process_trans_link]", "http://www.planetxmail.com/proctrans/eg_proctrans.php", $monthlypaylinks);

		// click bank params
		// generate seed making sure not to use one that has been
		srand((double)microtime()*1000000);
		for ($i=0; $i<100; $i++)
		{
			$seedfound = 0;
			$seed = strtoupper(substr(md5($u.microtime().rand().$o), 0, 9));

			$db->Query("SELECT COUNT(*) FROM cbseeds WHERE seed='$seed' LIMIT 1");
			list($seedfound) = $db->FetchRow();

			if ($seedfound)
			{
				usleep(100);
				continue;
			}
			else
			{
				$seedfound = "allgood";
				break;
			}
		}

		if ($seedfound!="allgood")
		{
			echo "<h2>Error Generating CB-SEED. Please contact: <b>accounts@planetxmail.com</b>";
			@mail("accounts@planetxmail.com", "CB Generate ERROR", "Could not generate a CB SEED!");
			exit;
		}

		$monthlypaylinks = str_replace("[click_bank_params]", "&u=$u&o=$o&seed=$seed", $monthlypaylinks);
		$monthlypaylinks = str_replace("[click_bank_link_number]", $clickbanklinknumbermonthly, $monthlypaylinks);
		$monthlypaylinks = str_replace("[click_bank_user_name]", $clickbankaccount, $monthlypaylinks);
	}
	else
	{
		$monthlypaylinks = file_get_contents("messages/memmonthlyalreadypaid.txt");
		$monthlypaylinks = str_replace("[fname]", $ufname, $monthlypaylinks);
	}
}
else
{
	echo "Username and/or ELP Owner not found. Contact: <b>accounts@planetxmail.com</b>";
	exit;
}

?>