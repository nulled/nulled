<?php
set_time_limit(240);
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');

function writeproc($str)
{
  if ($filep = fopen('/home/nulled/www/planetxmail.com/proctrans/secure/pp_proctrans.log', 'a'))
  {
    chmod('/home/nulled/www/planetxmail.com/proctrans/secure/pp_proctrans.log', 0777);
    fwrite($filep, $str."\n");
    fclose($filep);
  }
  else
  	@mail('elitescripts2000@yahoo.com', 'pp_proctrans error', 'unable to open log file for writing.');
}

function mysql_timestamp_to_humandatetime1($dt)
{
	$yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,4,2)); $da=strval(substr($dt,6,2)); $hr=strval(substr($dt,8,2));
	$mi=strval(substr($dt,10,2)); $se=strval(substr($dt,12,2)); return date('Y-m-d H:i:s', mktime ($hr,$mi,$se,$mo,$da,$yr));
}

function s4s($id, $receipt, $buyeremail, $profits, $db)
{
	writeproc("safelist4sale attempt - id: $id - receipt: $receipt");

  if (! $id)
  {
  	writeproc("Missing required params for: safelist4sale\n");
  	exit;
  }

  $headers = "From: PXM <do_not_reply@planetxmail.com>\r\nReturn-Path: do_not_reply@planetxmail.com";

  // check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");
  	exit;
  }

	// do some list error checking
  $db->Query("SELECT listname, listownername, howheard FROM orders WHERE id='$id'");
  list($listname, $listownername, $howheard) = $db->FetchRow();

  if (! stristr($howheard, "cancelled"))
  {
  	writeproc("id: $id found but list: $listname is not set as cancelled!");
  	@mail("elitescripts2000@yahoo.com", "pp_proctrans safelist4sale ERROR!" ,"id: $id found but list: $listname is not set as cancelled!\nMeaning someone tried to purchase seconds after another.", $headers);
  	exit;
  }

  $db->SelectDB("mle");
	if (! $db->Query("SELECT listownerID FROM listowner WHERE username='$listownername'"))
	{
  	writeproc("id: $id found but listownername: $listownername not found in mle DB!");
  	@mail("elitescripts2000@yahoo.com", "pp_proctrans safelist4sale ERROR!" ,"id: $id found but listownername: $listownername not found in mle DB!", $headers);
  	exit;
  }
  list($listownerID) = $db->FetchRow();
  // end list error checking //

  $db->SelectDB("pxm");
  $db->Query("UPDATE orders SET howheard='List purchased', verified='yes', paid='yes', datesubmitted=NOW(), email='$buyeremail', listowneremail='$buyeremail' WHERE id='$id'");
	$db->SelectDB("mle");

	$newpass = md5($buyeremail);

	$db->Query("UPDATE listowner SET password='$newpass', email='$buyeremail' WHERE listownerID='$listownerID'");
	$db->Query("UPDATE listmanager SET adminemail='$buyeremail' WHERE listname='$listname' AND listownerID='$listownerID'");
	$db->Query("UPDATE listconfig SET adminemailaddress='$buyeremail' WHERE listname='$listname' AND listownerID='$listownerID'");

	$subject = "Your PXM Safelists4Sale Receipt";
	$message = "Thank you, $buyeremail, for purchasing our Premium Pre-Owned Safelist!\n\nTo Log in to your new Safelist use the link below:\nhttp://www.planetxmail.com/mle/admin/indexlistowner.php\n\nUser Name: $listownername\nPassword: $buyeremail\n\nFor Tech Support: elitescripts2000@yahoo.com\n\nWelcome Aboard,\nMatt Kukowski\n\nhttp://www.pxmb.com";
	@mail($buyeremail, $subject, $message, $headers);

	// record in transactions table
	$db->SelectDB("pxm");
	$db->Query("INSERT INTO transactions VALUES('','safelist4sale','$profits','paypal','$receipt',NOW())");
}

function pxm_signup($id, $ex, $receipt, $profits, $db)
{
	writeproc("pxm_signup attempt - id: $id - ex: $ex - receipt: $receipt");

  if (! $id)
  {
  	writeproc("Missing required params for: pxm_signup\n");
  	exit;
  }

  require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");

  $header = "From: PXM <elitescripts2000@yahoo.com>";

  // check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

  	//@mail("elitescripts2000@yahoo.com", "pp_proctrans eCheck", "eCheck Updated in transactions table. receipt: $receipt");
  	exit;
  }

  if ($ex=="1")
	{
	  if (! $db->Query("SELECT listtype, importlist, listownername, price, nummembers, listname, howheard FROM extended WHERE id='$id'"))
	  {
	  	writeproc("pxm_signup ID not found! id: $id");
	  	@mail("elitescripts2000@yahoo.com", "pxm_signup pp_proctrans ERROR!", "pxm_signup ID not found! id: $id");
	  	exit;
	  }

	  list($listtype, $importlist, $listownername, $price, $nummembers, $listname, $howheard) = $db->FetchRow();

		$db->Query("UPDATE extended SET paid='1', verified='yes' WHERE id='$id'");

		// create list for extended order
	  if ($db->Query("SELECT name, address, state, country, email, organization, city, zipcode, phone, listowneremail FROM orders WHERE listownername='$listownername'"))
	  {
	  	list($name, $address, $state, $country, $email, $organization, $city, $zipcode, $phone, $listowneremail) = $db->FetchRow();

	    $orderdate = date("F j, Y");

	    // Send Reciept to customer
	    $subject = "Planet X Mail - List Order Receipt";
			$message = file_get_contents("/home/nulled/www/planetxmail.com/messages/listsignupexreceipt.txt");

			$message = str_replace("[id]", $id, $message);
			$message = str_replace("[name]", $name, $message);
			$message = str_replace("[orderdate]", $orderdate, $message);
			$message = str_replace("[price]", $price, $message);
			$message = str_replace("[listowneremail]", $listowneremail, $message);
			$message = str_replace("[listownername]", $listownername, $message);
			$message = str_replace("[importlist]", $importlist, $message);
			$message = str_replace("[nummembers]", $nummembers, $message);
			$message = str_replace("[listtype]", $listtype, $message);
			$message = str_replace("[listname]", $listname, $message);
			$message = str_replace("[email]", $email, $message);
			$message = str_replace("[phone]", $phone, $message);
			$message = str_replace("[country]", $country, $message);
			$message = str_replace("[zipcode]", $zipcode, $message);
			$message = str_replace("[state]", $state, $message);
			$message = str_replace("[city]", $city, $message);
			$message = str_replace("[address]", $address, $message);
			$message = str_replace("[organization]", $organization, $message);

	    @mail($email, $subject, $message, $header);

	    $db->SelectDB("mle");

	    if (! $db->Query("SELECT listownerID FROM listowner WHERE username='$listownername'"))
	    {
	    	writeproc("pxm_signup error - id: $id found for ex: $ex but listownerID not found in listowner table");
				@mail("elitescripts2000@yahoo.com", "pxm_signup pp_proctrans error", "pxm_signup error - id: $id found for ex: $ex but listownerID not found in listowner table");
				exit;
			}

	    list($listownerID) = $db->FetchRow();
	    $db->Query("INSERT INTO listmanager VALUES('$listownerID','$listname','','','','','','','','','','','','','','0','0','')");

	    //////////// Create List /////////////////////////////
	    if ($listtype=="safelist") $listtype = "Safelist [openlist]";
	    else if ($listtype=="newsletter") $listtype = "Newsletter [closedlist]";

	    $subconfirm   = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/subconfirm.txt");
	    $subsuccess   = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/subsuccess.txt");
	    $unsubsuccess = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/unsubsuccess.txt");
	    $footer       = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/footer.txt");
	    $header       = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/header.txt");
	    $paymenthtml  = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/paymenthtml.txt");
	    $html         = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/html.txt");
	    $html = $html."!N_T_W_S_4_0!".$html."!N_T_W_S_4_0!".$html;

	    // make sure listhash is unique
			while(1)
			{
	    	$listhash = substr(md5($listownerID.$listname.microtime().rand()), 0, 5);
	    	if ($db->Query("SELECT listhash FROM listurls WHERE listhash='$listhash' LIMIT 1"))
	    		continue;
	    	else
	    		break;
	    }

	    $db->Query("INSERT INTO listurls VALUES('$listownerID','$listname','$listhash')");

	    // build THREE list messages each with a subject and message body.
	    // Safelist non-html, newsletter non-html, newsletter html
	    $subject       = "Enter subject line here";
	    $message       = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/message.txt");
	    $nlsubject     = "Enter NON HTML newsletter subject line here.";
	    $nlmessage     = "Enter NON HTML message here.";
	    $nlhtmlsubject = "Enter HTML newsletter subject line here.";
	    $nlhtmlmessage = "Enter HTML newsletter message here.";

	    $message = $subject."n!t!w_s!4!0".$message."n!t!w_s!4!0".$nlsubject."n!t!w_s!4!0".$nlmessage."n!t!w_s!4!0".$nlhtmlsubject."n!t!w_s!4!0".$nlhtmlmessage;

	    require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/config/configdefaults.inc");
	    $db->Query("UPDATE listmanager SET listownerID='$listownerID', listname='$listname', fromname='$listname', fromemail='$bounceemail', adminemail='$listowneremail', bounceemail='$bounceemail', listtype='$listtype', message='$message', footer='$footer', header='$header', subconfirm='$subconfirm', subsuccess='$subsuccess', unsubsuccess='$unsubsuccess', paymenthtml='$paymenthtml', created='1', html='$html' WHERE listname='$listname' AND listownerID='$listownerID'");
	    $midnight = mktime(0, 0, -1, date("m"), date("d"), date("y"));
	    $midnight = timestamp_to_mysql_timestamp($midnight);
	    $db->Query("INSERT INTO system VALUES('$listownerID','$listname',$midnight)");
		  $db->Query("INSERT INTO listconfig VALUES('$listownerID','$listname','$program_name','$commission','','$admin_email_address','$logout_location','$upgradeinfo','$numurltrackersMem','$numurltrackersPro','$numurltrackersExe','$mem_sendmail_times_week','$pro_sendmail_times_week','$exe_sendmail_times_day','$cost_of_pro','$cost_of_exe','$pro_upgradeform','$exe_upgradeform','$usepaylinks','$defaultstatus','$allowupgrades','$newmembernotice','0')");
		}
		else
		{
			writeproc("pxm_signup error - id: $id found for ex: $ex but listownername: $listownername not found in orders table");
			@mail("elitescripts2000@yahoo.com", "pxm_signup pp_proctrans error", "pxm_signup error - id: $id found for ex: $ex but listownername: $listownername not found in orders table");
			exit;
		}

		// record in transactions table
		$db->SelectDB("pxm");
		$db->Query("INSERT INTO transactions VALUES('','pxm_signup','$profits','paypal','$receipt',NOW())");
	}
	else
	{
		// process order for first time signup
		if (! $db->Query("SELECT id FROM orders WHERE id='$id'"))
	  {
	  	writeproc("pxm_signup ID not found! id: $id");
	  	@mail("elitescripts2000@yahoo.com", "pxm_signup pp_proctrans ERROR!", "pxm_signup ID not found! id: $id");
	  	exit;
	  }

		$db->Query("UPDATE orders SET verified='yes', paid='yes' WHERE id='$id'");

	  if ($db->Query("SELECT name, state, email, listname, howheard, address, country, nummembers, listowneremail, organization, zipcode, listtype, listownername, price, city, phone, importlist FROM orders WHERE id='$id'"))
	  {
	  	list($name, $state, $email, $listname, $howheard, $address, $country, $nummembers, $listowneremail, $organization, $zipcode, $listtype, $listownername, $price, $city, $phone, $importlist) = $db->FetchRow();

	    $orderdate = date("F j, Y");

	    // Send Receipt to customer
	    $subject = "Planet X Mail - List Order Receipt $id";
			$message = file_get_contents("/home/nulled/www/planetxmail.com/messages/listsignupreceipt.txt");

			$message = str_replace("[id]", $id, $message);
			$message = str_replace("[name]", $name, $message);
			$message = str_replace("[orderdate]", $orderdate, $message);
			$message = str_replace("[price]", $price, $message);
			$message = str_replace("[listowneremail]", $listowneremail, $message);
			$message = str_replace("[listownername]", $listownername, $message);
			$message = str_replace("[importlist]", $importlist, $message);
			$message = str_replace("[nummembers]", $nummembers, $message);
			$message = str_replace("[listtype]", $listtype, $message);
			$message = str_replace("[listname]", $listname, $message);
			$message = str_replace("[email]", $email, $message);
			$message = str_replace("[phone]", $phone, $message);
			$message = str_replace("[country]", $country, $message);
			$message = str_replace("[zipcode]", $zipcode, $message);
			$message = str_replace("[state]", $state, $message);
			$message = str_replace("[city]", $city, $message);
			$message = str_replace("[address]", $address, $message);
			$message = str_replace("[organization]", $organization, $message);

	    @mail($email, $subject, $message, $header);

	    $db->SelectDB("mle");

	    // generate new listownerID making sure not to generate an existing one
	    while (1)
	    {
	      $listownerID = generateID();

	      $db->Query("SELECT listownerID FROM listowner WHERE listownerID='$listownerID'");

	      if ($db->rows) continue;
	      else
	        break;
	    }

	    $db->Query("INSERT INTO listowner VALUES('$listownerID','$listownername','96e79218965eb72c92a549dd5a330112','$listowneremail',NOW())");
	    $db->Query("INSERT INTO listmanager VALUES('$listownerID','$listname','','','','','','','','','','','','','','0','0','')");

	    //////////// Create List /////////////////////////////
	    if ($listtype=="safelist") $listtype = "Safelist [openlist]";
	    else if ($listtype=="newsletter") $listtype = "Newsletter [closedlist]";

	    $subconfirm   = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/subconfirm.txt");
	    $subsuccess   = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/subsuccess.txt");
	    $unsubsuccess = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/unsubsuccess.txt");
	    $footer       = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/footer.txt");
	    $header       = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/header.txt");
	    $paymenthtml  = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/paymenthtml.txt");
	    $html         = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/html.txt");
	    $html = $html."!N_T_W_S_4_0!".$html."!N_T_W_S_4_0!".$html;

	    // make sure listhash is unique
			while(1)
			{
	    	$listhash = substr(md5($listownerID.$listname.microtime().rand()), 0, 5);
	    	if ($db->Query("SELECT listhash FROM listurls WHERE listhash='$listhash' LIMIT 1"))
	    		continue;
	    	else
	    		break;
	    }

	    $db->Query("INSERT INTO listurls VALUES('$listownerID','$listname','$listhash')");

	    // build THREE list messages each with a subject and message body.
	    // Safelist non-html, newsletter non-html, newsletter html
	    $subject       = "Enter subject line here";
	    $message       = file_get_contents("/home/nulled/www/planetxmail.com/mle/messages/message.txt");
	    $nlsubject     = "Enter NON HTML newsletter subject line here.";
	    $nlmessage     = "Enter NON HTML message here.";
	    $nlhtmlsubject = "Enter HTML newsletter subject line here.";
	    $nlhtmlmessage = "Enter HTML newsletter message here.";

	    $message = $subject."n!t!w_s!4!0".$message."n!t!w_s!4!0".$nlsubject."n!t!w_s!4!0".$nlmessage."n!t!w_s!4!0".$nlhtmlsubject."n!t!w_s!4!0".$nlhtmlmessage;

	    require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/config/configdefaults.inc");
	    $db->Query("UPDATE listmanager SET listownerID='$listownerID', listname='$listname', fromname='$listname', fromemail='$bounceemail', adminemail='$listowneremail', bounceemail='$bounceemail', listtype='$listtype', message='$message', footer='$footer', header='$header', subconfirm='$subconfirm', subsuccess='$subsuccess', unsubsuccess='$unsubsuccess', paymenthtml='$paymenthtml', created='1', html='$html' WHERE listname='$listname' AND listownerID='$listownerID'");
	    $midnight = mktime(0, 0, -1, date("m"), date("d"), date("y"));
	    $midnight = timestamp_to_mysql_timestamp($midnight);
	    $db->Query("INSERT INTO system VALUES('$listownerID','$listname',$midnight)");
	    $db->Query("INSERT INTO listconfig VALUES('$listownerID','$listname','$program_name','$commission','','$admin_email_address','$logout_location','$upgradeinfo','$numurltrackersMem','$numurltrackersPro','$numurltrackersExe','$mem_sendmail_times_week','$pro_sendmail_times_week','$exe_sendmail_times_day','$cost_of_pro','$cost_of_exe','$pro_upgradeform','$exe_upgradeform','$usepaylinks','$defaultstatus','$allowupgrades','$newmembernotice','0')");
		}
		else
		{
			writeproc("pxm_signup error - id: $id found for ex: $ex but listownername: $listownername not found in orders table");
			@mail("elitescripts2000@yahoo.com", "pxm_signup pp_proctrans error", "pxm_signup error - id: $id found for ex: $ex but listownername: $listownername not found in orders table");
			exit;
		}

		$db->SelectDB("pxm");
		$db->Query("INSERT INTO transactions VALUES('','pxm_signup','$profits','paypal','$receipt',NOW())");
	}
}

function pxm_monthly($id, $ex, $receipt, $profits, $db)
{
	writeproc("pxm_monthly attempt - id: $id - ex: $ex - receipt: $receipt");

  if (! $id)
  {
  	writeproc("Missing required params for: pxm_monthly\n");
  	exit;
  }

  // check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

  	@mail("elitescripts2000@yahoo.com", "pp_proctrans eCheck", "eCheck Updated in transactions table. receipt: $receipt");
  	exit;
  }

 	// check that ID exists
  if ($ex)
  {
  	if (! $db->Query("SELECT paid FROM extended WHERE id='$id'"))
  	{
  		writeproc("pxm_monthly ID not found! id: $id");
	  	@mail("elitescripts2000@yahoo.com", "pxm_monthly pp_proctrans ERROR!", "pxm_monthly ID not found! id: $id");
	  	exit;
	  }
	}
  else
  {
  	if (! $db->Query("SELECT paid FROM orders WHERE id='$id'"))
  	{
  		writeproc("pxm_monthly ID not found! id: $id");
	  	@mail("elitescripts2000@yahoo.com", "pxm_monthly pp_proctrans ERROR!", "pxm_monthly ID not found! id: $id");
	  	exit;
	  }
	}

	if ($ex)
		$db->Query("UPDATE extended SET paid='1', datesubmitted=NOW() WHERE id='$id'");
	else
  	$db->Query("UPDATE orders SET paid='yes', datesubmitted=NOW() WHERE id='$id'");

  // record in transactions table
	$db->Query("INSERT INTO transactions VALUES('','pxm_monthly','$profits','paypal','$receipt',NOW())");
}

function elp_partner($o, $id, $receipt, $profits, $db)
{
  writeproc("elp_partner attempt - owner: $o - id: $id - receipt: $receipt");

  if (! $id || ! $o)
  {
  	writeproc("Missing required params for: elp_partner\n");
  	exit;
  }

  require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");

  // check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

  	@mail("elitescripts2000@yahoo.com", "pp_proctrans eCheck", "eCheck Updated in transactions table. receipt: $receipt");
  	exit;
  }

  $db->SelectDB("elp");

  $db->Query("SELECT amountowed, dateowed FROM billingperiods WHERE id='$id' AND elpownername='$o'");

  if ($db->rows)
  {
  	list($amountpaid, $perioddate) = $db->FetchRow();

		// update billing periods
		$db->Query("UPDATE billingperiods SET paid='1', datepaid=NOW() WHERE id='$id' AND elpownername='$o'");
		$db->Query("UPDATE billingperiods SET paid='1', datepaid=NOW() WHERE bypassed='1' AND elpownername='$o'");

		// get all membertrans ids from billing period
		$db->Query("SELECT transids FROM billingperiods WHERE id='$id' AND elpownername='$o'");
		list($transids) = $db->FetchRow();
		$ids = explode(",", $transids);

		// update membertrans as paid
		for ($i=0; $i < count($ids); $i++)
			$db->Query("UPDATE membertrans SET paid='1' WHERE id='$ids[$i]' AND elpownername='$o'");

		// add paid elp owner trans
		$db->Query("INSERT INTO elpownertrans VALUES('','$o','$id','$amountpaid','$receipt','Paypal',NOW())");

    // mail receipt to ELP Owner
		$db->Query("SELECT elpownername, email FROM elpowners WHERE elpownername='$o'");
		list($elpownername, $email) = $db->FetchRow();

		$headers = "From: ELP_SYS <do_not_reply@planetxmail.com>\r\nReturn-Path: do_not_reply@planetxmail.com";

		$perioddate = mysql_timestamp_to_humandatetime1($perioddate);

		$subject = "ELP Partnership Billing Period Receipt";
		$message = file_get_contents("/home/nulled/www/planetxmail.com/elp/messages/elpownerreceipt.txt");

		$message = str_replace("[period_id]", $id, $message);
		$message = str_replace("[period_date]", $perioddate, $message);
		$message = str_replace("[amount]", $amountpaid, $message);
		$message = str_replace("[mop]", "Paypal", $message);
		$message = str_replace("[owner_name]", $elpownername, $message);

		$message = wordwrap($message, 60);

		@mail($email, $subject, $message, $headers);

		// mail to US
		$subject = "ELP Partner Paid Bill";
		$message = "ELP Owner: $o\nBilling ID: $id\nAmount: $amountpaid";
		// record in transactions table
		$db->SelectDB("pxm");
		$db->Query("INSERT INTO transactions VALUES('','elp_partner','$profits','paypal','$receipt',NOW())");
  }
  else
  {
    writeproc("No billing period found: elp_partner - id = $id - o = $o\n");
  	exit;
  }
}

function elp_mem_signup($u, $o, $receipt, $profits, $db)
{
	writeproc("elp_mem_signup attempt - user: $u - owner: $o - receipt: $receipt");

	if (! $u || ! $o)
	{
		writeproc("Missing required params for: elp_mem_signup\n");
		exit;
	}

	require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");

	// check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

  	@mail("elitescripts2000@yahoo.com", "pp_proctrans eCheck", "eCheck Updated in transactions table. receipt: $receipt");
  	exit;
  }

  $db->SelectDB("elp");

	$db->Query("SELECT paid FROM users WHERE username='$u' AND elpownername='$o'");

	if ($db->rows)
	{
	  list($paid) = $db->FetchRow();

		if (! $paid)
		{
			$db->Query("SELECT email, price, monthlyprice, commission, monthlycommission FROM elpowners WHERE elpownername='$o'");
			list($elpowneremail, $price, $monthlyprice, $commission, $monthlycommission) = $db->FetchRow();

			$db->Query("SELECT fname, email FROM users WHERE username='$u' AND elpownername='$o'");
			list($fname, $useremail) = $db->FetchRow();

			$total = $price + $monthlyprice;
			$commissionowed = $commission + $monthlycommission;

			$headers = "From: ELP_SYS <do_not_reply@planetxmail.com>\r\nReturn-Path: do_not_reply@planetxmail.com";

			if (strtolower($u)!="test_me")
			{
				$db->Query("INSERT INTO membertrans VALUES('','$o','$u','signup','$total','$receipt','Paypal',NOW(),'$commissionowed','0')");
				$db->Query("UPDATE users SET paid='1', verified='1', blocked='0', datelastbilled=NOW() WHERE username='$u' AND elpownername='$o'");

			  // record in transactions table
			  if (strtolower($o)=="elitescripts")
			  {
					$db->SelectDB("pxm");
					$db->Query("INSERT INTO transactions VALUES('','elp_mem_signup','$profits','paypal','$receipt',NOW())");
					$db->SelectDB("elp");
				}
			}
			else
			{
				$db->Query("UPDATE users SET verified='1', blocked='0', datelastbilled=NOW() WHERE username='$u' AND elpownername='$o'");

				$subject = "ELP  test_me  Sign up account test PASSED.";
				$message = file_get_contents("/home/nulled/www/planetxmail.com/elp/messages/test_mesignup.txt");
				$link = "http://www.planetxmail.com.com/elp/memmonthlypaylinks.php?u=$u&o=$o";

				$message = str_replace("[monthly_paylink]", $link, $message);

				@mail($elpowneremail, $subject, $message, $headers);
				@mail($useremail, $subject, $message, $headers);
			}

			$date = date("F j, Y");

			//  Mail to OWNER
			$subject = "New ELP Member Signup.";
			$message = file_get_contents("/home/nulled/www/planetxmail.com/elp/messages/newmembersignupnotice.txt");

			$message = str_replace("[date]", $date, $message);
			$message = str_replace("[amount]", $total, $message);
			$message = str_replace("[user_name]", $u, $message);
			$message = str_replace("[elp_owner]", $o, $message);
			$message = str_replace("[user_email]", $useremail, $message);
			$message = str_replace("[mop]", "Paypal", $message);

			@mail($elpowneremail, $subject, $message, $headers);

			// Mail to USER
			$subject = "$fname, Your Receipt for ELP sign up.";
			$message = file_get_contents("/home/nulled/www/planetxmail.com/elp/messages/newmembersignupreceipt.txt");

			$message = str_replace("[date]", $date, $message);
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
			writeproc("Already signed up for: p = elp_mem_signup  -  u = $u  -  o = $o\n");
			exit;
		}
	}
	else
	{
		writeproc("ELP Owner or ELP Member not found for: p = elp_mem_signup\n");
		exit;
	}
}

function elp_mem_monthly($u, $o, $receipt, $profits, $db)
{
	writeproc("elp_mem_monthly attempt - user: $u - owner: $o - receipt: $receipt");

	if (! $u || ! $o)
	{
		writeproc("Missing required params for: elp_mem_monthly\n");
		exit;
	}

	require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");

	// check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

  	@mail("elitescripts2000@yahoo.com", "pp_proctrans eCheck", "eCheck Updated in transactions table. receipt: $receipt");
  	exit;
  }

  $db->SelectDB("elp");

	$db->Query("SELECT username FROM users WHERE username='$u' AND elpownername='$o'");

	if ($db->rows)
	{
		$db->Query("SELECT email, monthlyprice, monthlycommission FROM elpowners WHERE elpownername='$o'");
		if ($db->rows)
			list($elpowneremail, $monthlyprice, $monthlycommission) = $db->FetchRow();
		else
			writeproc("Member Monthly ELP Owner info not found - username = $u  -  elpowner = $o  -  receipt = $receipt");

		$db->Query("SELECT fname, email, datesignedup FROM users WHERE username='$u' AND elpownername='$o'");
		if ($db->rows)
			list($fname, $useremail, $datesignedup) = $db->FetchRow();
		else
			writeproc("Member Monthly ELP USER info not found - username = $u  -  elpowner = $o  -  receipt = $receipt");

		$total = $monthlyprice;
		$commissionowed = $monthlycommission;

		$headers = "From: ELP_SYS <do_not_reply@planetxmail.com>\r\nReturn-Path: do_not_reply@planetxmail.com";

		if (strtolower($u)!="test_me")
		{
			// check for duplicate receipt number
			if ($db->Query("SELECT receipt FROM membertrans WHERE username='$u' AND elpownername='$o' AND receipt='$receipt'"))
			{
				@mail("elitescripts2000@yahoo.com", "ELP Monthly Receipt Dup", "User: $u\nOwner: $o\nReceipt: $receipt", $headers);
				writeproc("Member Monthly Found DUP Receipt and was Skipped - username = $u  -  elpowner = $o  -  receipt = $receipt");
				exit;
			}

			$db->Query("INSERT INTO membertrans VALUES('','$o','$u','monthly','$total','$receipt','Paypal',NOW(),'$commissionowed','0')");

			// record in transactions table
		  if (strtolower($o)=="elitescripts")
		  {
				$db->SelectDB("pxm");
				$db->Query("INSERT INTO transactions VALUES('','elp_mem_monthly','$profits','paypal','$receipt',NOW())");
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
		writeproc("ELP Owner or ELP Member not found for: p = elp_mem_monthly  -  u = $u  -  o = $o\n");
		exit;
	}
}

function directad($id, $receipt, $page, $profits, $db)
{
  require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");
  writeproc("directad attempt - page = $page");

  // check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

  	@mail("elitescripts2000@yahoo.com", "pp_proctrans eCheck", "eCheck Updated in transactions table. receipt: $receipt");
  	exit;
  }

  $db->SelectDB("mle");

  $date = date("F j, Y");
  $headers = "From: PXM <do_not_reply@planetxmail.com>\r\nReturn-Path: do_not_reply@planetxmail.com";

  $db->Query("SELECT email, numdays, amount, ad FROM directads WHERE id='$id' AND page='$page'");

  if ($db->rows)
  {
    list($email, $numDays, $amount, $admessage) = $db->FetchRow();

    $db->Query("UPDATE directads SET receipt='$receipt', mop='Paypal' WHERE id='$id' AND page='$page'");
    $db->Query("DELETE FROM directads WHERE mop='' AND page='$page' AND (UNIX_TIMESTAMP(NOW()) - 43200) >= UNIX_TIMESTAMP(datesubmitted)");

    // mail buyer
    $subject = "Planet X Mail Direct Exposure AD receipt.";
    $message = file_get_contents("/home/nulled/www/planetxmail.com/messages/directadreceipt.txt");

    $message = str_replace("[numdays]", $numDays, $message);
    $message = str_replace("[message]", $admessage, $message);
    $message = str_replace("[mop]", "Paypal", $message);
    $message = str_replace("[price]", $amount, $message);
    $message = str_replace("[date]", $date, $message);
    $message = str_replace("[id]", $id, $message);
    $message = str_replace("[transid]", $receipt, $message);

    $message = wordwrap($message, 70);
    @mail($email, $subject, $message, $headers);

    // record in transactions table
		$db->SelectDB("pxm");
		$db->Query("INSERT INTO transactions VALUES('','directad','$profits','paypal','$receipt',NOW())");
  }
  else
  {
    writeproc("ID not found when in directad()\n");
    exit;
  }
}

function soload($id, $whichaddress, $receipt, $profits, $payer_email, $db)
{
  writeproc("soload attempt - id: $id - whichaddress: $whichaddress - receipt: $receipt");

  // check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

  	@mail("elitescripts2000@yahoo.com", "pp_proctrans eCheck", "eCheck Updated in transactions table. receipt: $receipt");
  	exit;
  }

  $db->SelectDB("mle");

  $date = date("F j, Y");
  $headers = "From: PXM <do_not_reply@planetxmail.com>\r\nReturn-Path: do_not_reply@planetxmail.com";

  if ($db->Query("SELECT email, subject, message, listname FROM soloads WHERE id='$id'"))
  {
    list($email, $adsubject, $admessage, $type) = $db->FetchRow();

    require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");

    // contact or list address 1=contact 2=list address
    if ($whichaddress == '1')
    {
      if ($profits < 43)
      {
        @mail('elitescripts2000@yahoo.com', 'FRAUDULANT Solo AD Sale - '.$profits, 'Just a WARNING. id:'.$id, $headers);
        @mail($payer_email, 'You are a FRAUD', 'Planet X Mail has detected you are doing Fraudulant price hacking and have been reported to Paypal and Police Departments. Your Solo Ad was NOT mailed.', $headers);
        exit;
      }
      $price = '49';
    }
    else
    {
      if ($profits < 33)
      {
        @mail('elitescripts2000@yahoo.com', 'FRAUDULANT Solo AD Sale - '.$profits, 'Just a WARNING. id:'.$id, $headers);
        @mail($payer_email, 'You are a FRAUD', 'Planet X Mail has detected you are doing Fraudulant price hacking and have been reported to Paypal and Police Departments. Your Solo Ad was NOT mailed.', $headers);
        exit;
      }
      $price = '39';
    }

    $db->Query("UPDATE soloads SET receipt='$receipt', mop='Paypal', price='$price' WHERE id='$id'");

    // mail buyer
    $subject = "Planet X Mail SOLO AD receipt.";
    $message = file_get_contents("/home/nulled/www/planetxmail.com/messages/soloadreceipt.txt");

    if (strstr($type, "HTMLSOLOAD"))
    {
      $message = str_replace("\n", "<br />\n", $message);
      $headers .= "\r\nContent-Type: text/html; charset=iso-8859-1";
    }

    $sastatuslink = "http://planetxmail.com/sastatus.php?v=$id";

    $message = str_replace("[subject]", $adsubject, $message);
    $message = str_replace("[message]", $admessage, $message);
    $message = str_replace("[mop]", "Paypal", $message);
    $message = str_replace("[date]", $date, $message);
    $message = str_replace("[sastatus_link]", $sastatuslink, $message);

    $message = wordwrap($message, 70);

    @mail($email, $subject, $message, $headers);
    @mail('elitescripts2000@yahoo.com', 'Solo AD Sale - '.$price, 'Just a reminder.', $headers);

    // record in transactions table
		$db->SelectDB("pxm");
		$db->Query("INSERT INTO transactions VALUES('','soload','$profits','paypal','$receipt',NOW())");
  }
  else
  {
    writeproc("ID not found when in soload()\n");
    exit;
  }
}

function m2m_signup($payer_email, $receipt, $profits, $fname, $lname, $db)
{
	writeproc("m2m_signup attempt - receipt: $receipt");

  require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/datefunctions.inc");
  require_once("/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php");

  // check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

  	@mail("elitescripts2000@yahoo.com", "pp_proctrans eCheck", "eCheck Updated in transactions table. receipt: $receipt");
  	exit;
  }

  $db->SelectDB("mle");

  $list = "Marketing2Masses";
  $id 	= "4032668343";
  $l 		= "0a862";

  while (1)
  {
    $uID = generateID();

    $db->Query("SELECT COUNT(*) FROM users WHERE userID='$uID' LIMIT 1");
    list($tryagain) = $db->FetchRow();

    if ($tryagain) continue;
    else
      break;
  }

  // get when list was last cleaned and apply to new user
  $db->Query("SELECT lastcleaned FROM system WHERE listname='$list' AND listownerID='$id'");
  list($lastcleaned) = $db->FetchRow();
  $lastcleaned = timestamp_to_mysql_timestamp(mysql_datetime_to_timestamp($lastcleaned));

  $password = md5("123456");
  $s = "exe";
  $username = substr($receipt, 0, 8);

  $db->Query("INSERT INTO users VALUES ('$uID','$fname','$lname','$payer_email','$s','$username','$password',NOW(),'yes','','$list','0','0',NOW(),$lastcleaned,'$id','','0','0','','0','','0',NOW())");

	$today = date("F j, Y  H:i");

	// record in transactions table
	$db->SelectDB("pxm");
	$db->Query("INSERT INTO transactions VALUES('','m2m_signup','$profits','paypal','$receipt',NOW())");

	$loginurl = "http://www.planetxmail.com/mle/login.php?l=$l&username=$username";

	$subject = "Marketing2Masses Signup Notice";
	$message = "Thank you for signing up with us.\n\nYour Login URL is below. Please keep your User/Pass in a safe location.\n\n$loginurl\n\nUsername: $username\nPassword: 123456\n\nThe Resourse Center and SafeList is accessible from this location.";
	$headers = "From: M2Masses <elitescripts2000@yahoo.com>\r\nReturn-Path: elitescripts2000@yahoo.com";
	@mail($payer_email, $subject, $message, $headers);
}

function pxmb_signup($id, $receipt, $profits, $payeremail, $db)
{
	writeproc("pxmb_signup attempt - receipt: $receipt");

	$db->SelectDB("pxmb");

	if (! $db->Query("SELECT user, contactemail, name, pass, price FROM presignup WHERE id='$id'"))
	{
		writeproc("id: $id not found.. most likely a pending eCheck Cleared");
		return;
	}

	list($user, $contactemail, $name, $pass, $price) = $db->FetchRow();
	$user = strtolower($user);

	writeproc("Queried: $user, $contactemail, $name, $pass, $price");

	if ($price=='5') 			 $quota = 1024*1024*50;
	else if ($price=='7')  $quota = 1024*1024*100;
	else if ($price=='10') $quota = 1024*1024*175;
	else
		$quota = 1024*1024*200;

  $server = 'pxmb2';
  $server_ip = '10.0.0.12';

  $payeremail = strtolower($payeremail);

	writeproc("Found server to host mBox: $server_ip");

	// create a user entry on host mailbox server
	writeproc("CONNECTED to db_remote: $server_ip");

	$db_remote->Query("INSERT INTO users VALUES('$user@pxmb.com','$pass','$payeremail','$user/Maildir/',NOW(),NOW(),'$name','1','$quota','0|0|0|','0')");
	writeproc("INSERT INTO users VALUES('$user@pxmb.com','$pass','$payeremail','$user/Maildir/',NOW(),NOW(),'$name','1','$quota','0|0|0|','0')");

	// create operation to create the mailbox on selected host mailbox server
	$db->Query("INSERT INTO ops VALUES('','$server','create','$user')");
	writeproc("Inserted VALUES('','$server','create','$user')");

  // mail the user
	$subject = 'Planet X MailBox Sign-up Notice';
	$headers = "From: PXMB <elitescripts2000@yahoo.com>";

	@mail($contactemail, $subject, "Thank you $name for signing up to Planet X MailBox!\n\nLogin Here:\nhttp://pxmb.com/webmail\n\nUser: $user\nPass: $pass\n\nPlease write this information down!\n\nBest Regards,\nPlanet X MailBox Staff\n\nhttp://www.planetxmailbox.com\nhttp://www.pxmb.com", $headers);
	//@mail("elitescripts2000@yahoo.com", $subject, "Thank you $name for signing up to Planet X MailBox!\n\nLogin Here:\nhttp://www.pxmb.com/webmail/\n\nUser: $user\nPass: $pass\n\nPlease write this information down!\n\nBest Regards,\nPlanet X MailBox Staff\n\nhttp://www.planetxmailbox.com\nhttp://www.pxmb.com", $headers);

  // delete presignup entry
  $db->Query("DELETE FROM presignup WHERE id='$id'");

  // record in transactions table
	$db->SelectDB("pxm");
	$db->Query("INSERT INTO transactions VALUES('','pxmb_signup','$profits','paypal','$receipt',NOW())");
}

function pxmb_renewal($u, $receipt, $profits, $payer_email, $upgrade, $db)
{
	writeproc("pxmb_renewal attempt - receipt: $receipt");

	$server = "10.0.0.12";


	$headers = "From: PlanetXMail Box <elitescripts2000@yahoo.com>";

	if ($db_remote->Query("SELECT name, contactemail FROM users WHERE id='$u@pxmb.com'"))
	{
		list($name, $contactemail) = $db_remote->FetchRow();
		$contactemail = trim($contactemail);

		if (! $contactemail)
		{
			$contactemail = $payer_email;

			if ($upgrade)
			{
			  $db_remote->Query("UPDATE users SET contactemail='$contactemail', paid='1', quota='$upgrade' WHERE id='$u@pxmb.com'");
			  @mail("elitescripts2000@yahoo.com", "PXMB Upgrade", "$u@pxmb.com UPGRADED to: $upgrade", $headers);
			}
			else
			  $db_remote->Query("UPDATE users SET contactemail='$contactemail', paid='1' WHERE id='$u@pxmb.com'");
		}
		else
		{
			if ($upgrade)
			{
			  $db_remote->Query("UPDATE users SET paid='1', quota='$upgrade' WHERE id='$u@pxmb.com'");
			  @mail("elitescripts2000@yahoo.com", "PXMB Upgrade", "$u@pxmb.com UPGRADED to: $upgrade", $headers);
			}
			else
			  $db_remote->Query("UPDATE users SET paid='1' WHERE id='$u@pxmb.com'");
		}
	}
	else
	{
		writeproc("id: $u  NOT FOUND in any PXMB servers");
		exit;
	}

	$subject = "Planet X MailBox - Payment ThankYou";
	$message = "Hello $name,\n\nYour $u@pxmb.com / $u@planetxmailbox.com account has been renewed.\n\nBest Regards,\nPlanet X MailBox Staff";

	@mail($contactemail, $subject, $message, $headers);
	//@mail("elitescripts2000@yahoo.com", $subject, $message, $headers);

	// record in transactions table
	$db->SelectDB("pxm");
	$db->Query("INSERT INTO transactions VALUES('','pxmb_renewal','$profits','paypal','$receipt',NOW())");
}

function digipanel_license($licID, $receipt, $profits, $payer_email, $years, $affID, $db)
{
  writeproc("digipanel_license attempt - receipt: ".$receipt.", licID: ".$licID.", affID: ".$affID."\n");

  $headers = "From: DigiPanel <support@digipanel.com>\r\nReturn-Path: support@digipanel.com";

	// check if receipt already there if so update true amount
  if ($db->Query("SELECT receipt FROM transactions WHERE receipt='$receipt' LIMIT 1"))
  {
  	$db->Query("UPDATE transactions SET amount='$profits' WHERE receipt='$receipt'");

  	writeproc("Pending cleared eCheck updated amount in transactions table\n");
  	writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");

  	@mail("elitescripts2000@yahoo.com", "pp_proctrans DigiPanel eCheck", "eCheck Updated in transactions table. receipt: $receipt");
  	exit;
  }

  $db->SelectDB("digipanel");

  if (! $db->Query("SELECT userID, mac, paid, datelastbilled FROM licenses WHERE licID='$licID'"))
  {
    writeproc("digipanel_license - licID=".$licID." does not exist in database\n");
    @mail("elitescripts2000@yahoo.com", "digipanel_license ERROR", "licID=".$licID." does not exist in database\n\nreceipt=".$receipt, $headers);
    exit;
  }
	list($userID, $macaddress, $paid, $datelastbilled) = $db->FetchRow();

  if (! $db->Query("SELECT email, name, pass FROM accounts WHERE userID='$userID'"))
  {
    writeproc("digipanel_license - userID=".$userID." does not exist in database\n");
    @mail("elitescripts2000@yahoo.com", "digipanel_license ERROR", "userID=".$userID." does not exist in database\n\nreceipt=".$receipt, $headers);
    exit;
  }
  list($email, $name, $pass) = $db->FetchRow();

  if ($paid)
  {
    writeproc("digipanel_license - licID=".$licID." was already paid\n");
    return;
  }
  else
  {
    $db->Query("UPDATE licenses SET paid='1', years='$years', datelastbilled=NOW() WHERE licID='$licID'");

$message = "Hello ".$name.",

We received payment for your DigiPanel License.

License for MAC Address: ".$macaddress."

We will begin processing your order right away.
You may check the status of your order by going to:
http://www.digipanel.com and logging into the Members
Login Area. Your account information is below:

Account: ".$email."
Password: ".$pass."

If you have further questions you may reply to this email.

Warm Regards,
DigiPanel Staff
http://www.digipanel.com
support@digipanel.com
";
    @mail($payer_email, "DigiPanel License Payment Received", $message, $headers);
    @mail($email, "DigiPanel License Payment Received", $message, $headers);
    @mail("elitescripts2000@yahoo.com", "DigiPanel Customer PAID", $message."\n\nlicID=".$licID."\n\nReceipt=".$receipt."\n\nAmount=".$profits, $headers);

    // HYG has the encoder, tell it to upload with new expire date for this license
    $db->Query("INSERT INTO ops VALUES('','create','$licID')");

    if ($affID)
    {
      if ($db->Query("SELECT userID FROM accounts WHERE userID='$affID'"))
      {
        $amount = number_format(($profits * .20), 2, ".", "");
        $db->Query("INSERT INTO affiliate_transactions VALUES('','$affID','$licID','$amount','$receipt',NOW())");
        $mysqlID = mysqli_insert_id($db->link);
        writeproc("digipanel_license - licID=".$licID." INSERT INTO affiliate_transactions affiliate affID=".$affID." id=".$mysqlID."\n");
      }
      else
        writeproc("digipanel_license - licID=".$licID." affID=".$affID." AFFILIATE WAS NOT FOUND\n");
    }

    // record in transactions table
  	$db->SelectDB("pxm");
  	$db->Query("INSERT INTO transactions VALUES('','digipanel_license','$profits','paypal','$receipt',NOW())");

    writeproc("digipanel_license - licID=".$licID." was set as paid=".$paid."\n");
  }
}

function ebooks($receipt, $profits, $payer_email, $db)
{
	writeproc("ebooks attempt - receipt: $receipt");

	$headers = "From: PXM <elitescripts2000@yahoo.com>\r\nReturn-Path: elitescripts2000@yahoo.com";

	$subject = "eBooks - Payment Thank You";
	$message = "Dear Customer,\n\nYour eBooks can be downloaded using the link below:\n\nhttp://www.planetxmail.com/ebook_s_here\n\nBest Regards,\nPlanet X Mail Staff";

	@mail($payer_email, $subject, $message, $headers);
	@mail("elitescripts2000@yahoo.com", $subject, $message, $headers);

	// record in transactions table
	$db->SelectDB("pxm");
	$db->Query("INSERT INTO transactions VALUES('','ebooks','$profits','paypal','$receipt',NOW())");
}

// read the post from PayPal system and add 'cmd'
$req = 'cmd=_notify-validate';
foreach ($_POST as $key => $value)
{
  $key   = urlencode(stripslashes($key));
  $value = urlencode(stripslashes($value));
  $req .= "&$key=$value";
}

$good_trans = 0;

$today = date("F j, Y, g:i a");

//writeproc("$today DEBUG Start 1\n");

// assign posted variables to local variables
$fname 					= $_POST['first_name'];
$lname 					= $_POST['last_name'];
$receiver_email = $_POST['receiver_email'];
$item_name      = $_POST['item_name'];
$custom         = $_POST['custom'];
$payment_status = $_POST['payment_status'];
$payment_gross  = $_POST['payment_gross'];
$payment_fee 	  = $_POST['payment_fee'];
$txn_id         = $_POST['txn_id'];
$payer_email    = $_POST['payer_email'];
$complete_url   = $_POST['option_selection1'];

list($server, $product, $username, $owner, $extra) = explode('-', $custom);

//writeproc("$today DEBUG Start 2\n");

if ($server != 'PXM' && $server != 'HOST') exit;

//writeproc("$today DEBUG Start 3\n");

writeproc("*****************************************************************\n$today - New transaction start");

writeproc("fname = $fname");
writeproc("lname = $lname");
writeproc("item_name = $item_name");
writeproc("custom = $custom");
writeproc("payment_status = $payment_status");
writeproc("payment_gross = $payment_gross");
writeproc("payment_fee = $payment_fee");
writeproc("txn_id = $txn_id");
writeproc("payer_email = $payer_email");
writeproc("complete_url = $complete_url");
writeproc("---------------");
writeproc("server = $server");
writeproc("product = $product");
writeproc("username = $username");
writeproc("owner = $owner");
writeproc("extra = $extra");
writeproc("---------------");

// post back to PayPal system to validate
if ($server == "PXM")
  $header  = "POST /cgi-bin/webscr HTTP/1.0\r\n";
else if ($server == "DIGIPANEL")
  $header  = "POST /digipanel/digipanel.php?c=process_paypal HTTP/1.0\r\n";
else
{
  //writeproc("$today DEBUG Start 4 $server unknown server\n");
  exit;
}

$db = new MySQL_Access("pxm");

$header .= "Content-Type: application/x-www-form-urlencoded\r\n";
$header .= "Content-Length: " . strlen($req) . "\r\n\r\n";

if ($server == 'PXM')
  $fp = fsockopen ('www.paypal.com', 80, $errno, $errstr, 30);
else if ($server == 'DIGIPANEL')
{
  // writeproc("Here: 1");
  $fp = fsockopen ('www.hostyougood.com', 80, $errno, $errstr, 30);
  if (! $fp)
  {
    $errorHappened = "$errstr ($errno)";
    writeproc("Tried to re-post back to HYG ERROR: $errorHappened\n");
    $db->Query("INSERT INTO trans_errors VALUES ('','$custom','$txn_id','error happened before being processed','$errorHappened')");
    @fclose($fp);
    exit;
  }
  fputs ($fp, $header . $req);
  $result = fgets ($fp, 1024);
  writeproc($result);
  @fclose($fp);
  exit;
}
else
  exit;

if (! $fp)
{
  // HTTP ERROR
  $errorHappened = "$errstr ($errno)";
  writeproc("Tried to re-post back to PayPal ERROR: $errorHappened\n");
}
else
{
  fputs ($fp, $header . $req);

  while (! feof($fp))
  {
    $res = fgets ($fp, 1024);

    if (strcmp($res, 'VERIFIED') == 0)
    {
      if ($payment_status == 'Completed' || $payment_status == 'Pending')
      {
      	$profits = $payment_gross - $payment_fee;
      	$profits = number_format($profits, 2, '.', '');

        // process the order
        switch($product)
        {
          case "soload":
            soload($username, $owner, $txn_id, $profits, $payer_email, $db);
            $good_trans = 1;
            break;
          case "directad":
            directad($username, $txn_id, $extra, $profits, $db);
            $good_trans = 1;
            break;
          case "elp_mem_signup":
          	elp_mem_signup($username, $owner, $txn_id, $profits, $db);
          	$good_trans = 1;
            break;
          case "elp_mem_monthly":
          	elp_mem_monthly($username, $owner, $txn_id, $profits, $db);
          	$good_trans = 1;
          	break;
          case "elp_partner":
            elp_partner($owner, $extra, $txn_id, $profits, $db);
            $good_trans = 1;
            break;
          case "pxm_signup":
          	pxm_signup($username, $extra, $txn_id, $profits, $db);
          	$good_trans = 1;
          	break;
          case "pxm_monthly":
          	pxm_monthly($username, $extra, $txn_id, $profits, $db);
          	$good_trans = 1;
          	break;
          case "s4s":
          	s4s($username, $txn_id, $payer_email, $profits, $db);
          	$good_trans = 1;
          	break;
          case "m2m_signup":
          	m2m_signup($payer_email, $txn_id, $profits, $fname, $lname, $db);
          	$good_trans = 1;
          	break;
          case "pxmb_signup":
          	pxmb_signup($username, $txn_id, $profits, $payer_email, $db);
          	$good_trans = 1;
          	break;
          case "pxmb_renewal":
          	pxmb_renewal($username, $txn_id, $profits, $payer_email, $owner, $db);
          	$good_trans = 1;
          	break;
          case "digipanel_license":
          	digipanel_license($username, $txn_id, $profits, $payer_email, $owner, $extra, $db);
          	$good_trans = 1;
          	break;
          case "ebooks":
          	ebooks($txn_id, $profits, $payer_email, $db);
          	$good_trans = 1;
          	break;
          default:
            writeproc("Product not found!\n");
            break 2;
        }
        break;
      }
      else
      {
        writeproc("Bad Payment Status: $payment_status\n");
        break;
      }
    }
    else if (strcmp ($res, "INVALID") == 0)
    {
      writeproc("ALERT!!! INVALID");
      @mail("elitescripts2000@yahoo.com", "pp_proctrans error", "ALERT!!! INVALID... $res");
      break;
    }
  }
}

@fclose ($fp);

if ($good_trans)
  writeproc("---=== END SUCCESSFUL TRANSACTION ===---\n");
else
{
  $db->Query("INSERT INTO trans_errors VALUES ('','$custom','$txn_id','$payment_status','$res')");
  writeproc("******** TRANS FAILED\n");
}

exit;

?>
