<?php
if ($cbreceipt)
{
	function mysql_timestamp_to_humandatetime1($dt)
	{
		$yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,4,2)); $da=strval(substr($dt,6,2)); $hr=strval(substr($dt,8,2));
		$mi=strval(substr($dt,10,2)); $se=strval(substr($dt,12,2)); return date("Y-m-d H:i:s", mktime ($hr,$mi,$se,$mo,$da,$yr));
	}

	if (! $u || ! $o)
	{
		echo "<h2>Error: Missing User and/or Owner param.</h2> Please contact: <b>accounts@planetxmail.com</b>";
		exit;
	}

	$headers = "From: PXM <accounts@planetxmail.com>";

	include("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");
	include("elpsecure/cbvalid.php");
	include("../mle/mlpsecure/config/classes.inc");

	if (! $seed || ! $cbpop)
  {
    echo "Error: Missing SEED or CBPOP. Please contact: <b>accounts@planetxmail.com</b>";
    @mail("accounts@planetxmail.com", "ELP monthly thankyou CB Error", "owner: $o\nuser: $u\nseed: $seed\ncbpop: $cbpop", $headers);
    exit;
  }

  $db = new MySQL_Access("elp");

  $db->Query("SELECT email, monthlyprice, monthlycommission, clickbankkey FROM elpowners WHERE elpownername='$o'");
	list($elpowneremail, $monthlyprice, $monthlycommission, $ownercgikey) = $db->FetchRow();

  if (! cbValid($seed, $cbpop, $ownercgikey))
  {
    echo "<h2>Error: Invalid ClickBank transaction!</h2>";
    @mail("accounts@planetxmail.com", "ELP monthly Clickbank FRAUD!", "owner: $o\nuser: $u\nseed: $seed\ncbpop: $cbpop\nownercgikey: $ownercgikey", $headers);
    exit;
  }

	// check if seed is in database if so reject transaction
  $db->Query("SELECT COUNT(*) FROM cbseeds WHERE seed='$seed' LIMIT 1");
  list($seedfound) = $db->FetchRow();

  if ($seedfound)
  {
  	echo "<h2>Error: Invalid ClickBank transaction!</h2> Contact: <b>accounts@planetxmail.com</b>";
  	@mail("accounts@planetxmail.com", "Duplicate SEED - ELP monthly Clickbank FRAUD!", "Duplicate SEED found!\nowner: $o\nuser: $u\nseed: $seed\ncbpop: $cbpop", $headers);
    exit;
  }

	$db->Query("SELECT paid, fname, email, datesignedup FROM users WHERE username='$u' AND elpownername='$o'");
	list($paid, $fname, $email, $datesignedup) = $db->FetchRow();

	if ($paid)
	{
	  echo "<h3>You are currently Paid and up to date.</h3>";
	  exit;
	}

	if ($db->rows)
	{
		$total = $monthlyprice;
		$commissionowed = $monthlycommission;

		$headers = "From: ELP_SYS <$elpowneremail>";

		if (strtolower($u)!="test_me")
		{
		  $db->Query("INSERT INTO membertrans VALUES('','$o','$u','monthly','$total','$cbreceipt','clickbank',NOW(),'$commissionowed','0')");
			$db->Query("INSERT INTO cbseeds VALUES('$seed')");

			// record in transactions table
			if (strtolower($o)=="elitescripts")
		  {
		  	$total -= 1;
				$fees = $total * .075;
				$total -= $fees;
				$profits = number_format($total, 2, '.', '');

				$db->SelectDB("pxm");
				$db->Query("INSERT INTO transactions VALUES('','elp_mem_monthly','$profits','clickbank','$cbreceipt',NOW())");
				$db->SelectDB("elp");
			}
		}
		else
		{
			$subject = "ELP  test_me  Monthly account test PASSED.";
			$message = file_get_contents("/home/nulled/www/planetxmail.com/elp/messages/test_memonthly.txt");

			@mail($elpowneremail, $subject, $message, $headers);
			@mail($useremail, $subject, $message, $headers);
		}

		$db->Query("UPDATE users SET paid='1', verified='1', blocked='0' WHERE username='$u' AND elpownername='$o'");

		$datesignedup = mysql_timestamp_to_humandatetime1($datesignedup);
		$datepayment = date("F j, Y");

		//  Mail to OWNER
		$subject = "ELP - Member Monthly Payment.";
		$message = file_get_contents("/home/nulled/www/planetxmail.com/elp/messages/memmonthlypaymentnotice.txt");

		$message = str_replace("[date_payment]", $datepayment, $message);
		$message = str_replace("[amount]", $total, $message);
		$message = str_replace("[user_name]", $u, $message);
		$message = str_replace("[user_email]", $useremail, $message);
		$message = str_replace("[mop]", "Paypal", $message);

		@mail($elpowneremail, $subject, $message, $headers);

		if ($elpowneremail!="accounts@planetxmail.com")
			@mail("accounts@planetxmail.com", $subject, $message, $headers);

		// Mail to USER
		$subject = "$fname, Receipt for your ELP monthly payment.";
		$message = file_get_contents("/home/nulled/www/planetxmail.com/elp/messages/memmonthlypaymentreceipt.txt");

		$message = str_replace("[date_payment]", $datepayment, $message);
		$message = str_replace("[date_signedup]", $datesignedup, $message);
		$message = str_replace("[amount]", $total, $message);
		$message = str_replace("[user_name]", $u, $message);
		$message = str_replace("[mop]", "Paypal", $message);
		$message = str_replace("[elp_owner]", $o, $message);
		$message = str_replace("[receipt]", $receipt, $message);
		$message = str_replace("[elpowner_email]", $elpowneremail, $message);

		@mail($useremail, $subject, $message, $headers);
	}
	else
	{
		echo "Error: Missing User Name param.  Please contact: <b>accounts@planetxmail.com</b>";
		exit;
	}
}

?>