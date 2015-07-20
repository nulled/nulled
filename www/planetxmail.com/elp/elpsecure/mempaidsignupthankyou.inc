<?php
if ($cbreceipt)
{
	if (! $u || ! $o)
	{
		echo "<h2>Error: Missing User and/or Owner param.</h2> Please contact: <b>accounts@planetxmail.com</b>";
		exit;
	}

  $headers = "From: PXM <accounts@planetxmail.com>";

	include("elpsecure/cbvalid.php");
	include("../mle/mlpsecure/validationfunctions.php");
	include("../mle/mlpsecure/config/classes.inc");

	if (! $seed || ! $cbpop)
  {
    echo "Error: Missing SEED or CBPOP. Please contact: <b>accounts@planetxmail.com</b>";
    @mail("accounts@planetxmail.com", "ELP signup thankyou CB Error", "owner: $o\nuser: $u\nseed: $seed\ncbpop: $cbpop", $headers);
    exit;
  }

  $db = new MySQL_Access("elp");

  $db->Query("SELECT email, price, monthlyprice, commission, monthlycommission, clickbankkey FROM elpowners WHERE elpownername='$o'");
	list($elpowneremail, $price, $monthlyprice, $commission, $monthlycommission, $ownercgikey) = $db->FetchRow();

  if (! cbValid($seed, $cbpop, $ownercgikey))
  {
    echo "<h2>Error: Invalid ClickBank transaction!</h2>";
    @mail("accounts@planetxmail.com", "ELP signup Clickbank FRAUD!", "owner: $o\nuser: $u\nseed: $seed\ncbpop: $cbpop\nownercgikey: $ownercgikey", $headers);
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

	$db->Query("SELECT paid, fname, email FROM users WHERE username='$u' AND elpownername='$o'");
	list($paid, $fname, $email) = $db->FetchRow();

	if ($paid)
	{
	  echo "<h3>You are currently Paid and up to date.</h3>";
	  exit;
	}

	if ($db->rows)
	{
		$total = $price + $monthlyprice;
		$commissionowed = $commission + $monthlycommission;

		$headers = "From: ELP_SYS <$elpowneremail>";

		if (strtolower($u)!="test_me")
		{
			$db->Query("INSERT INTO membertrans VALUES('','$o','$u','signup','$total','$cbreceipt','ClickBank',NOW(),'$commissionowed','0')");
			$db->Query("UPDATE users SET verified='1', paid='1', blocked='0', datesignedup=NOW(), datelastbilled=NOW() WHERE username='$u' AND elpownername='$o'");
			$db->Query("INSERT INTO cbseeds VALUES('$seed')");

			// record in transactions table
		  if (strtolower($o)=="elitescripts")
		  {
		  	$total -= 1;
				$fees = $total * .075;
				$total -= $fees;
				$profits = number_format($total, 2, '.', '');

				$db->SelectDB("pxm");
				$db->Query("INSERT INTO transactions VALUES('','elp_mem_signup','$profits','clickbank','$cbreceipt',NOW())");
				$db->SelectDB("elp");
			}
		}
		else
		{
			$db->Query("UPDATE users SET verified='1', blocked='0', datesignedup=NOW(), datelastbilled=NOW() WHERE username='$u' AND elpownername='$o'");

			$subject = "ELP  test_me  Sign up account test PASSED.";
			$message = file_get_contents("../elp/messages/test_mesignup.txt");
			$link = "http://www.planetxmail.com/elp/memmonthlypaylinks.php?u=$u&o=$o";

			$message = str_replace("[monthly_paylink]", $link, $message);

			@mail($elpowneremail, $subject, $message, $headers);
			@mail($useremail, $subject, $message, $headers);
		}

		$date = date("F j, Y");

		//  Mail to OWNER
		$subject = "New ELP Member Signup.";
		$message = file_get_contents("../elp/messages/newmembersignupnotice.txt");

		$message = str_replace("[date]", $date, $message);
		$message = str_replace("[amount]", $total, $message);
		$message = str_replace("[user_name]", $u, $message);
		$message = str_replace("[user_email]", $useremail, $message);
		$message = str_replace("[mop]", "ClickBank", $message);

		@mail($elpowneremail, $subject, $message, $headers);

		if ($elpowneremail!="accounts@planetxmail.com")
			@mail("accounts@planetxmail.com", $subject, $message, $headers);

		// Mail to USER
		$subject = "$fname, Your Receipt for ELP sign up.";
		$message = file_get_contents("../elp/messages/newmembersignupreceipt.txt");

		$message = str_replace("[date]", $date, $message);
		$message = str_replace("[amount]", $total, $message);
		$message = str_replace("[user_name]", $u, $message);
		$message = str_replace("[mop]", "ClickBank", $message);
		$message = str_replace("[elp_owner]", $o, $message);
		$message = str_replace("[receipt]", $receipt, $message);
		$message = str_replace("[elpowner_email]", $elpowneremail, $message);

		@mail($useremail, $subject, $message, $headers);

	}
	else
	{
	  echo "ERROR: Missing USER NAME param.  Please contact: <b>accounts@planetxmail.com</b>";
	  exit;
	}
}

?>