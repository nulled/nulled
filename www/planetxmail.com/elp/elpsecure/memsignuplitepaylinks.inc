<?php
if (!$u || !$o)
{
	echo "Missing required params. Contact: <b>accounts@planetxmail.com</b>";
	exit;
}

include("../mle/mlpsecure/validationfunctions.php");
include("../mle/mlpsecure/config/classes.inc");
$db = new MySQL_Access("elp");

$db->Query("SELECT username FROM users WHERE elpownername='$o' AND username='$u' AND paid='1'");
if ($db->rows)
{
  echo "You have already paid your sign up fee!  Or you are trying to register with a user name that is already taken.<br><br>";
  echo "Contact: <b>accounts@planetxmail.com</b> for further assitance.";
  exit;
}
else
{
  $db->Query("SELECT useclickbanklite, usepaypal, useegold, clickbanklinknumberlite, clickbankaccount, paypalaccount, egoldaccount, email, pricelite, fname, lname FROM elpowners WHERE elpownername='$o'");

  if ($db->rows)
  {
  	list($useclickbanklite, $usepaypal, $useegold, $clickbanklinknumberlite, $clickbankaccount, $paypalaccount, $egoldaccount, $email, $pricelite, $fname, $lname) = $db->FetchRow();

  	$total = $pricelite;

  	if (strtolower($u)=="test_me") $total = .05;

  	$db->Query("SELECT fname, verified, paid FROM users WHERE username='$u' AND elpownername='$o'");
  	list($ufname, $verified, $paid) = $db->FetchRow();

  	if ($db->rows)
  	{
  	  if (! $paid)
  	  {
    		if ($usepaypal)    $signuppaylinks .= file_get_contents("messages/paypal.txt");
    		if ($useegold)	   $signuppaylinks .= file_get_contents("messages/egold.txt");
    		if ($useclickbanklite) $signuppaylinks .= file_get_contents("messages/clickbank.txt");

    		$signuppaylinks = str_replace("[memo]", "ELP_Member_Signup", $signuppaylinks);
    		$signuppaylinks = str_replace("[item_name]", "ELL Sign up - $u - $o", $signuppaylinks);
    		$signuppaylinks = str_replace("[price]", $total, $signuppaylinks);
    		$signuppaylinks = str_replace("[payment_thankyou_link]", "http://www.planetxmail.com/elp/mempaidsignuplitethankyou.php?u=$u&o=$o", $signuppaylinks);
    		$signuppaylinks = str_replace("[payment_cancel_link]", "http://www.planetxmail.com/elp/canceledorder.php", $signuppaylinks);

    		// paypal proc trans params
    		$signuppaylinks = str_replace("[paypal_account]", $paypalaccount, $signuppaylinks);
    		$signuppaylinks = str_replace("[paypal_custom]", "PXM-elp_mem_signup-$u-$o", $signuppaylinks);

    		// e-gold proc trans params
    		$signuppaylinks = str_replace("[egold_account]", $egoldaccount, $signuppaylinks);
    		$signuppaylinks = str_replace("[fname_lname]", "$fname $lname", $signuppaylinks);
    		$signuppaylinks = str_replace("[server_name]", "PXM", $signuppaylinks);
    		$signuppaylinks = str_replace("[product]", "elp_mem_signup", $signuppaylinks);
    		$signuppaylinks = str_replace("[username]", $u, $signuppaylinks);
    		$signuppaylinks = str_replace("[elp_owner]", $o, $signuppaylinks);
    		$signuppaylinks = str_replace("[egold_process_trans_link]", "http://www.planetxmail.com/proctrans/eg_proctrans.php", $signuppaylinks);

    		// click bank params
    		// generate seed making sure not to use one that has been
    		srand((double)microtime()*1000000);
				for ($i=0; $i<100; $i++)
				{
					$seedfound = 0;
					$seed = strtoupper(substr(md5(md5($u).microtime().rand().$o), 0, 9));

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
					@mail("accounts@planetxmail.com", "CB Generate Error", "Could not generate a CB SEED!");
					exit;
				}

    		$signuppaylinks = str_replace("[click_bank_params]", "&u=$u&o=$o&seed=$seed", $signuppaylinks);
    		$signuppaylinks = str_replace("[click_bank_link_number]", $clickbanklinknumberlite, $signuppaylinks);
    		$signuppaylinks = str_replace("[click_bank_user_name]", $clickbankaccount, $signuppaylinks);
    	}
    	else
    	{
    	  $signuppaylinks = file_get_contents("messages/memsignupalreadypaid.txt");
  		  $signuppaylinks = str_replace("[fname]", $ufname, $signuppaylinks);
    	}
  	}
  	else
  	{
  		echo "Username and/or ELP Owner not found. Contact: <b>accounts@planetxmail.com</b>";
  	  exit;
  	}
  }
  else
  {
    echo "ELP Owner not found: Owner: $o  -  Please contact <b>accounts@planetxmail.com</b>";
    exit;
  }
}

?>