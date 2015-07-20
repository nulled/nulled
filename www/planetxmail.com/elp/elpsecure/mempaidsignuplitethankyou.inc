<?php
if ($cbreceipt)
{
  $headers = "From: PXM <accounts@planetxmail.com>";

	include("elpsecure/cbvalid.php");
	include("../mle/mlpsecure/validationfunctions.php");
	include("../mle/mlpsecure/config/classes.inc");

	$db = new MySQL_Access("elp");

	if (! $seed || ! $cbpop)
  {
    echo "Error: Missing SEED or CBPOP. Please contact: <b>accounts@planetxmail.com</b>";
    @mail("accounts@planetxmail.com", "ELP signuplite thankyou CB Error", "owner: $o\nuser: $u\nseed: $seed\ncbpop: $cbpop", $headers);
    exit;
  }

  $db->Query("SELECT clickbankkey FROM elpowners WHERE elpownername='$o'");
  list($ownercgikey) = $db->FetchRow();

  if (! cbValid($seed, $cbpop, $ownercgikey))
  {
    echo "<h2>Error: Invalid ClickBank transaction!</h2>";
    @mail("accounts@planetxmail.com", "ELP signuplite Clickbank FRAUD!", "owner: $o\nuser: $u\nseed: $seed\ncbpop: $cbpop", $headers);
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

	if ($o && $u)
	{
		$db->Query("SELECT paid FROM users WHERE username='$u' AND elpownername='$o'");
		list($paid) = $db->FetchRow();

		if ($paid)
		{
		  echo "<h3>You are currently Paid and up to date.</h3>";
		  exit;
		}

		if ($db->rows)
		{
			$db->Query("SELECT email, price, commission, clickbankkey FROM elpowners WHERE elpownername='$o'");
			list($elpowneremail, $pricelite, $commissionlite, $ownercgikey) = $db->FetchRow();

			$db->Query("SELECT fname, email FROM users WHERE username='$u' AND elpownername='$o'");
			list($fname, $useremail) = $db->FetchRow();

			$total = $price;
			$commissionowed = $commissionlite;

			$headers = "From: ELP_SYS <accounts@planetxmail.com>";

			if (strtolower($u)!="test_me")
			{
				$db->Query("INSERT INTO membertrans VALUES('','$o','$u','lite','$total','$cbreceipt','ClickBank',NOW(),'$commissionowed','0')");
				$db->Query("UPDATE users SET verified='1', paid='1', blocked='0', datesignedup=NOW(), datelastbilled=NOW() WHERE username='$u' AND elpownername='$o'");
				$db->Query("INSERT INTO cbseeds VALUES('$seed')");

				// record in transactions table
				$db->SelectDB("pxm");
				$db->Query("INSERT INTO transactions VALUES('','elp_mem_signup','$commissionowed','clickbank','$cbreceipt',NOW())");
				$db->SelectDB("elp");
			}
			else
			{
				$db->Query("UPDATE users SET verified='1', blocked='0', datesignedup=NOW(), datelastbilled=NOW() WHERE username='$u' AND elpownername='$o'");

				$subject = "ELL  test_me  Sign up account test PASSED.";
				$message = file_get_contents("../elp/messages/test_mesignup.txt");
				$link = "http://www.planetxmail.com/elp/memmonthlypaylinks.php?u=$u&o=$o";

				$message = str_replace("[monthly_paylink]", $link, $message);

				@mail($elpowneremail, $subject, $message, $headers);
				@mail($useremail, $subject, $message, $headers);
			}

			$date = date("F j, Y");

			//  Mail to OWNER
			$subject = "New ELL Member Signup.";
			$message = file_get_contents("../elp/messages/newmembersignuplitenotice.txt");

			$message = str_replace("[date]", $date, $message);
			$message = str_replace("[amount]", $total, $message);
			$message = str_replace("[user_name]", $u, $message);
			$message = str_replace("[user_email]", $useremail, $message);
			$message = str_replace("[mop]", "ClickBank", $message);

			@mail($elpowneremail, $subject, $message, $headers);

			if ($elpowneremail!="accounts@planetxmail.com")
				@mail("accounts@planetxmail.com", $subject, $message, $headers);

			// Mail to USER
			$subject = "$fname, Your Receipt for ELL sign up.";
			$message = file_get_contents("../elp/messages/newmembersignuplitereceipt.txt");

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
			echo "ERROR: Your not found in database.  Contact: <b>accounts@planetxmail.com</b>";
			exit;
		}
	}
	else
	{
	  echo "ERROR: Missing ELP OWNER and or USER NAME param.  Please contact: <b>accounts@planetxmail.com</b>";
	  exit;
	}
}

?>