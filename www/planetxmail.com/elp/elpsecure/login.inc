<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

session_start();
set_time_limit(180);

session_start();
@session_destroy();
session_start();

function mysql_timestamp_to_humandatetime1($dt)
{
	$yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,4,2)); $da=strval(substr($dt,6,2)); $hr=strval(substr($dt,8,2));
	$mi=strval(substr($dt,10,2)); $se=strval(substr($dt,12,2)); return date("Y-m-d H:i:s", mktime ($hr,$mi,$se,$mo,$da,$yr));
}

if ($submitted=="login")
{
	if ($username AND $password AND $elpowner)
	{
		$db = new MySQL_Access('elp');

		$username = trim($username);
		$password = trim($password);
		$elpowner = trim($elpowner);

		$passwordenc = md5($password);

		if ($is_Demo_Dood)
		{
			$elpowner = "EliteScripts";
			$passwordenc = md5("demoit");
			$username = "demo";
		}
		else
		{
			if ($username=="demo")
			{
				echo "You can only access the demo account from the <b>DEMO version</b> of ELP.";
				exit;
			}
		}

		if ($db->Query("SELECT username FROM users WHERE (UNIX_TIMESTAMP(NOW()) - 2160000) >= UNIX_TIMESTAMP(datesignedup) AND paid='0' AND username='$username' AND password='$passwordenc' AND elpownername='$elpowner'"))
	    $needPayMonthly = 1;

		$db->Query("SELECT verified, blocked, paid, memtype FROM users WHERE username='$username' AND password='$passwordenc' AND elpownername='$elpowner'");
	  list($verified, $blocked, $paid, $memtype) = $db->FetchRow();

		if ($db->rows)
		{
			if ($access=="yourinFV" && ! $is_Demo_Dood && ($memtype=="pro" || $username=="test_me"))
				$access = "nt54yh_1h";
			else if ($access=="yourinDV" && $is_Demo_Dood)
				$access = "nt54yh_1h";
			else if ($access=="yourinFVLITE" && ! $is_Demo_Dood && ($memtype=="lite" || $username=="test_me"))
				$access = "nt54yh_1h";

			if ($access=="nt54yh_1h")
			{
				if (! $blocked)
				{
					if ($paid)
					{
						$ipaddress = $_SERVER["REMOTE_ADDR"];

            $db->Query("REPLACE INTO ipaddresses VALUES('$username','$elpowner','$ipaddress',NOW())");

						// check if system needs cleaning
						$midnight = mktime(0, 0, -1, date("m"), date("d"), date("y"));
				    $midnight = timestamp_to_mysql_timestamp($midnight);
						usleep(generateID(3));

				    if ($db->Query("SELECT lastcleaned FROM system WHERE elpownername='$elpowner' AND (UNIX_TIMESTAMP(NOW()) - 86400) >= UNIX_TIMESTAMP(lastcleaned)"))
				    {
				      $db->Query("UPDATE system SET lastcleaned='$midnight'");

				      $db->Query("SELECT elpownername FROM elpowners");
				      $allelpowners = $db->result;

				      while (list($elpowner) = mysqli_fetch_row($allelpowners))
				      {
					      // delete unverified users after 7 days
		      			$db->Query("DELETE FROM users WHERE verified='0' AND paid='0' AND elpownername='$elpowner' AND (UNIX_TIMESTAMP(NOW()) - 604800) >= UNIX_TIMESTAMP(datesignedup)");

                $db->Query("SELECT email FROM elpowners WHERE elpownername='$elpowner'");
                list($elpowneremail) = $db->FetchRow();

		      			/////// SEND mail to unverified users ///////
					      $db->Query("SELECT email, username, fname FROM users WHERE verified='0' AND elpownername='$elpowner' AND memtype='pro' AND (UNIX_TIMESTAMP(NOW()) - 86400) >= UNIX_TIMESTAMP(datesignedup)");

					      $headers = "From: ELP <accounts@planetxmail.com>";
								$subject = "ELP Sign up validation reminder.";
					      $message = file_get_contents("messages/sendunverified.txt");

					      $message = wordwrap($message, 60);

					      $message = str_replace("[owner_name]", $elpowner, $message);
					      $message = str_replace("[owner_email]", $elpowneremail, $message);

					      while (list($uemail, $uname, $fname) = $db->FetchRow())
					      {
					      	$body = str_replace("[user_name]", $uname, $message);
					      	$body = str_replace("[validateemail_url]", "http://www.planetxmail.com/elp/validateemail.php?u=$uname&o=$elpowner", $body);
					      	$body = str_replace("[signup_paylink_url]", "http://www.planetxmail.com/elp/memsignuppaylinks.php?u=$uname&o=$elpowner", $body);
					      	$body = str_replace("[fname]", $fname, $body);

					        @mail($uemail, $subject, $body, $headers);
					      }
					      /////// END SEND mail to unverified users ///////

								/////// Send Mail to members that need to pay monthly //////

					      // delete members that havent paid after 25 days
					      $db->Query("SELECT username FROM users WHERE paid='0' AND verified='1' AND username!='test_me' AND username!='demo' AND memtype='pro' AND (UNIX_TIMESTAMP(NOW()) - (86400 * 25)) >= UNIX_TIMESTAMP(datelastbilled) AND elpownername='$elpowner'");
					      while (list($uname) = $db->FetchRow())
					      {
								  $db->Query("DELETE FROM users WHERE username='$uname' AND elpownername='$elpowner'");
								  $db->Query("DELETE FROM ipaddresses WHERE username='$uname' AND elpownername='$elpowner'");
								}

								// check for members that need to pay and set them as paid=0
								$currentdate = mysql_timestamp_to_humandatetime1(timestamp_to_mysql_timestamp(time()));
								list($cyear, $cmonth, $cday, $ctime) = preg_split('/[- ]/', $currentdate);

								$today = date("F j, Y");

								$db->Query("SELECT datesignedup, username FROM users WHERE verified='1' AND paid='1' AND username!='test_me' AND username!='demo' AND memtype='pro' AND elpownername='$elpowner'");

								// reset all to paid=0 if current day is on the same day they signed up
								while (list($date, $uname) = $db->FetchRow())
								{
									list($syear, $smonth, $sday, $stime) = preg_split('/[- ]/', $date);

									if ($cday==$sday && ($cmonth!=$smonth || $cyear>$syear))
								  	$db->Query("UPDATE users SET paid='0', datelastbilled=NOW() WHERE username='$uname' AND elpownername='$elpowner'");
								}

                // send mail to those that need to pay monthly bill
								$db->Query("SELECT email, monthlyprice FROM elpowners WHERE elpownername='$elpowner'");
								list($elpowneremail, $monthlyprice) = $db->FetchRow();

								$db->Query("SELECT email FROM admin WHERE name='admin'");
								list($elpsystemowneremail) = $db->FetchRow();

								$headers = "From: ELP <accounts@planetxmail.com>";
								$subject = "Ezy-List Pro monthly payment due.";
								$message = file_get_contents("messages/memmonthlybill.txt");

								$message = str_replace("[monthly_price]", $monthlyprice, $message);
								$message = str_replace("[elp_partner_name]", $elpowner, $message);
								$message = str_replace("[elp_partner_email]", $elpowneremail, $message);
								$message = str_replace("[elp_system_owner_email]", $elpsystemowneremail, $message);
								$message = str_replace("[date_today]", $today, $message);

								$paylink = "http://www.planetxmail.com/elp/memmonthlypaylinks.php";

								$db->Query("SELECT email, fname, datesignedup, username FROM users WHERE paid='0' AND verified='1' AND memtype='pro' AND (UNIX_TIMESTAMP(NOW()) - 2160000) >= UNIX_TIMESTAMP(datesignedup) AND username!='demo' AND username!='test_me' AND elpownername='$elpowner'");

								while (list($uemail, $fname, $datesignedup, $uname) = $db->FetchRow())
								{
									$datesignedup = mysql_datetime_to_humandate($datesignedup);

									$body = str_replace("[fname]", $fname, $message);
									$body = str_replace("[monthly_payment_link]", $paylink."?u=$uname&o=$elpowner", $body);
									$body = str_replace("[date_signed_up]", $datesignedup, $body);

									@mail($uemail, $subject, $body, $headers);
								}
								//////// END monthly billing code ///////

					      /// Calculate billing for elp partners on 1st and 15th ////
					      list ($month, $day, $year) = preg_split('/[ ,]/', $today);
					      if ($day=="1" || $day=="15")
					      {
					        $transdata = $totalids = "";
                  $totalsignups = $totalmonthlys = $totalcommissionowed = $totalearned = $absoluteowed = $absoluteearned = 0;

									$mess = file_get_contents("messages/elpownerperiodicbill.txt");

					      	$db->Query("SELECT id, username, transtype, amount, receipt, mop, commissionowed FROM membertrans WHERE elpownername='$elpowner' AND paid='0' AND username!='test_me' AND username!='demo' ORDER BY id");
					      	if ($db->rows)
					      	{
						      	while (list($id, $username, $transtype, $amount, $receipt, $mop, $commissionowed) = $db->FetchRow())
						      	{
						      		if ($transtype=="signup")
						      			$totalsignups++;
						      		else
						      			$totalmonthlys++;

						      		$totalids .= $id.",";
						      		$totalcommissionowed += $commissionowed;
						      		$totalearned += $amount;

						      		$amount = "\$ $amount";
						      		$commissionowed = "\$ $commissionowed";

						      		$transdata .= sprintf("%-8s%-20s%-11s%-8s%-18s%-10s%-s\n", $id, $username, $transtype, $amount, $receipt, $mop, $commissionowed);
						      	}

						      	$totalprofits = $totalearned - $totalcommissionowed;
						      	$totalids = substr($totalids, 0, strlen($totalids)-1);
						      	$db->Query("UPDATE billingperiods SET bypassed='1' WHERE paid='0' AND elpownername='$elpowner'");
						      	$db->Query("INSERT INTO billingperiods VALUES('','$elpowner','$totalids','$totalearned','$totalcommissionowed','0','0',NOW(),'0')");
						      	$transID = mysqli_insert_id($db->link);
						      	$db->Query("SELECT email, price, commission, monthlyprice, monthlycommission, datesignedup FROM elpowners WHERE elpownername='$elpowner'");
										list($email, $price, $commission, $monthlyprice, $monthlycommission, $dateelpownersignedup) = $db->FetchRow();

										$dateelpownersignedup = mysql_datetime_to_humandate($dateelpownersignedup);

						      	$message = str_replace("[total_earned]", $totalearned, $mess);
						      	$message = str_replace("[total_owed]", $totalcommissionowed, $message);
						      	$message = str_replace("[total_profits]", $totalprofits, $message);
						      	$message = str_replace("[trans_data]", $transdata, $message);
						      	$message = str_replace("[ending_date]", $today, $message);
						      	$message = str_replace("[monthly_payment_url]", "http://www.planetxmail.com/elp/elpownerpaylinks.php?o=$elpowner&id=$transID", $message);
						      	$message = str_replace("[total_signups]", $totalsignups, $message);
						      	$message = str_replace("[total_monthlys]", $totalmonthlys, $message);
						      	$message = str_replace("[price]", $price, $message);
						      	$message = str_replace("[monthly]", $monthly, $message);
						      	$message = str_replace("[monthly_price]", $monthlyprice, $message);
						      	$message = str_replace("[commission]", $commission, $message);
						      	$message = str_replace("[monthly_commission]", $monthlycommission, $message);
						      	$message = str_replace("[date_elpowner_signed_up]", $dateelpownersignedup, $message);

						      	$db->Query("SELECT COUNT(*) FROM membertrans WHERE transtype='signup' AND username!='test_me' AND username!='demo' AND elpownername='$elpowner'");
						      	list($absolutesignups) = $db->FetchRow();

						      	$db->Query("SELECT COUNT(*) FROM membertrans WHERE transtype='monthly' AND username!='test_me' AND username!='demo' AND elpownername='$elpowner'");
						      	list($absolutemonthlys) = $db->FetchRow();

						      	$db->Query("SELECT amount, commissionowed FROM membertrans WHERE username!='test_me' AND username!='demo' AND elpownername='$elpowner'");

						      	while (list($earned, $owed) = $db->FetchRow())
						      	{
						      		$absoluteearned += $earned;
						      		$absoluteowed += $owed;
						      	}

						      	$absoluteprofits = $absoluteearned - $absoluteowed;

						      	$message = str_replace("[absolute_earned]", $absoluteearned, $message);
						      	$message = str_replace("[absolute_owed]", $absoluteowed, $message);
						      	$message = str_replace("[absolute_profits]", $absoluteprofits, $message);
						      	$message = str_replace("[absolute_signups]", $absolutesignups, $message);
						      	$message = str_replace("[absolute_monthlys]", $absolutemonthlys, $message);

										$headers = "From: ELP <accounts@planetxmail.com>\r\nReturn-Path: accounts@planetxmail.com";
										$subject = "ELP Partner Bill for weeks ending: $today";

						      	@mail($email, $subject, $message, $headers);
						      	@mail("elitescripts2000@yahoo.com", $subject, $message, $headers);
						      }
					      }
					      //// Calculate Billing End //////
					    }
					    // end system cleaning for all elp owners
						}

						// activate elp
						if ($is_Demo_Dood)
							$_SESSION['elpID'] = '!elpDEMO!';
						else
							$_SESSION['elpID'] = '!elp123!';

						header("Location: 123acbelp.php");
						exit;
				  }
				  else if ($needPayMonthly)
				  	$notValid = "ERROR: You have not paid your monthly bill. <a href=\"http://planetxmail.com/elp/memmonthlypaylinks.php?u=$username&o=$elpowner\">Click Here to pay Monthly Bill.</a>";
				  else
				    $notValid = "ERROR: You have not paid your Sign up Fee. <a href=\"http://planetxmail.com/elp/memsignuppaylinks.php?u=$username&o=$elpowner\">Click Here to pay Signup fee.</a>";
				}
				else
					$notValid = "ERROR: You have been BLOCKED from logging in.";
			}
			else
				$notValid = "ERROR: You can only gain access using Ezy-List Pro";
		}
		else
			$notValid = "ERROR: Loggin failed. Check that your Username, Password and ELP Owner is correct.";
	}
	else
		$notValid = "ERROR: Missing required parameters.";
}

?>