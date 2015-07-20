<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/phpsecure/cbvalid.php');

$headers = 'From: PXM <do_not_reply@planetxmail.com>';

if ($_GET['cbreceipt'])
{
  if (! cbValid())
  {
    echo "<h2>Error: Invalid ClickBank transaction!</h2>";
    @mail("elitescripts2000@yahoo.com", "PXM listpayment thankyou CB Error", "id: $id", $headers);
    exit;
  }

  $vtid = trim($_GET['vtid']);

  list($id, $ex) = explode('Z', $vtid);

  $db = new MySQL_Access('pxm');

	// handle EXTENDED and FIRST TIME orders
	if ($ex=="1")
	{
	  // first check if EXTENDED order has not been verified, if so cancel.
	  if (! $db->Query("SELECT listtype, importlist, listownername, price, nummembers, listname, howheard FROM extended WHERE id='$id'"))
	  {
	    echo "There has been a problem setting up your account.  Admins have been notified as we speak.  Their email addres is <b>elitescripts2000@yahoo.com</b> if you do not hear from us in 24 hours.";
	    @mail("elitescripts2000@yahoo.com", "PXM List Order error", "The ID was not found in database when the THANK YOU page tried to complete the order.\nID: $id\n");
	    exit;
	  }
	  list($listtype, $importlist, $listownername, $price, $nummembers, $listname, $howheard) = $db->FetchRow();
	  $db->Query("UPDATE extended SET paid='1', verified='yes' WHERE id='$id'");
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
	    @mail($email, $subject, $message, $headers);
	    $db->SelectDB("mle");
	    $db->Query("SELECT listownerID FROM listowner WHERE username='$listownername'");
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
	    	$listhash = substr(md5($listownerID.$listname.microtime(true).mt_rand()), 0, 5);
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
	    include("mle/mlpsecure/config/configdefaults.inc");
	    $db->Query("UPDATE listmanager SET listownerID='$listownerID', listname='$listname', fromname='$listname', fromemail='$bounceemail', adminemail='$listowneremail', bounceemail='$bounceemail', listtype='$listtype', message='$message', footer='$footer', header='$header', subconfirm='$subconfirm', subsuccess='$subsuccess', unsubsuccess='$unsubsuccess', paymenthtml='$paymenthtml', created='1', html='$html' WHERE listname='$listname' AND listownerID='$listownerID'");
	    $midnight = mktime(0, 0, -1, date("m"), date("d"), date("y"));
	    $midnight = timestamp_to_mysql_timestamp($midnight);
	    $db->Query("INSERT INTO system VALUES('$listownerID','$listname',$midnight)");
	    $db->Query("INSERT INTO listconfig VALUES('$listownerID','$listname','$program_name','$commission','','$admin_email_address','$logout_location','$upgradeinfo','$numurltrackersMem','$numurltrackersPro','$numurltrackersExe','$mem_sendmail_times_week','$pro_sendmail_times_week','$exe_sendmail_times_day','$cost_of_pro','$cost_of_exe','$pro_upgradeform','$exe_upgradeform','','$defaultstatus','$allowupgrades','$newmembernotice','0')");
	  }
	}
	else
	{
	  // first check if order has already been verified, if so cancel. And get date
	  if (! $db->Query("SELECT id FROM orders WHERE id='$id'"))
	  {
	    echo "There has been a problem setting up your account.  Admins have been notified as we speak.  Our email address is <b>elitescripts2000@yahoo.com</b> if you do not hear from us in 24 hours.";
	    @mail("elitescripts2000@yahoo.com", "PXM List Order error", "The ID was not found in database when the THANK YOU page tried to complete the order.\nID: $id\n");
	    exit;
	  }

	  $db->Query("UPDATE orders SET verified='yes', paid='yes' WHERE id='$id'");

	  if ($db->Query("SELECT name, state, email, listname, howheard, address, country, nummembers, listowneremail, organization, zipcode, listtype, listownername, price, city, phone, importlist FROM orders WHERE id='$id'"))
	  {
	  	list($name, $state, $email, $listname, $howheard, $address, $country, $nummembers, $listowneremail, $organization, $zipcode, $listtype, $listownername, $price, $city, $phone, $importlist) = $db->FetchRow();

	    $orderdate = date("F j, Y");

	    // Send Receipt to customer
	    $subject = "Planet X Mail - List Order Receipt $id";
			$message = file_get_contents('/home/nulled/www/planetxmail.com/messages/listsignupreceipt.txt');

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

	    @mail($email, $subject, $message, $headers);
	    @mail('elitescripts2000@yahoo.com', $subject, $message, $headers);


	    $db->SelectDB("mle");

	    // generate new listownerID making sure not to generate an existing one
	    $i = 0;
	    while (true)
	    {
	      $i++;

        if ($i > 5000)
        {
          @mail('elitescripts2000@yahoo.com', 'error in paymentthankyou.inc', 'paymentthankyou.inc', $headers);
          exit('FATAL ERROR: Unable to generateID() in paymentthankyou.inc');
        }

	      $listownerID = generateID();

	      if ($db->Query("SELECT listownerID FROM listowner WHERE listownerID='$listownerID'"))
	        continue;
	      else
	        break;
	    }

	    $db->Query("INSERT INTO listowner VALUES('$listownerID','$listownername','96e79218965eb72c92a549dd5a330112','$listowneremail','0',NOW())");
	    $db->Query("INSERT INTO listmanager VALUES('$listownerID','$listname','','','','','','','','','','','','','','0','0','')");

	    //////////// Create List /////////////////////////////
	    if ($listtype=="safelist") $listtype = "Safelist [openlist]";
	    else if ($listtype=="newsletter") $listtype = "Newsletter [closedlist]";

	    $subconfirm   = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/subconfirm.txt');
	    $subsuccess   = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/subsuccess.txt');
	    $unsubsuccess = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/unsubsuccess.txt');
	    $footer       = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/footer.txt');
	    $header       = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/header.txt');
	    $paymenthtml  = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/paymenthtml.txt');
	    $html         = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/html.txt');
	    $html = $html."!N_T_W_S_4_0!".$html."!N_T_W_S_4_0!".$html;

      $i = 0;
	    while(true)
			{
			  $i++;

        if ($i > 5000)
        {
          @mail('elitescripts2000@yahoo.com', 'error in paymentthankyou.inc', 'paymentthankyou.inc location:2', $headers);
          exit('FATAL ERROR: Unable to generateID() in paymentthankyou.inc');
        }

	    	$listhash = substr(md5($listownerID.$listname.microtime(true).mt_rand()), 0, 5);
	    	if ($db->Query("SELECT listhash FROM listurls WHERE listhash='$listhash' LIMIT 1"))
	    		continue;
	    	else
	    		break;
	    }

	    $db->Query("INSERT INTO listurls VALUES('$listownerID','$listname','$listhash')");

	    // build THREE list messages each with a subject and message body.
	    // Safelist non-html, newsletter non-html, newsletter html
	    $subject       = "Enter subject line here";
	    $message       = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/message.txt');
	    $nlsubject     = "Enter NON HTML newsletter subject line here.";
	    $nlmessage     = "Enter NON HTML message here.";
	    $nlhtmlsubject = "Enter HTML newsletter subject line here.";
	    $nlhtmlmessage = "Enter HTML newsletter message here.";

	    $message = $subject."n!t!w_s!4!0".$message."n!t!w_s!4!0".$nlsubject."n!t!w_s!4!0".$nlmessage."n!t!w_s!4!0".$nlhtmlsubject."n!t!w_s!4!0".$nlhtmlmessage;

	    include("/home/nulled/www/planetxmail.com/mle/mlpsecure/config/configdefaults.inc");
	    $db->Query("UPDATE listmanager SET listownerID='$listownerID', listname='$listname', fromname='$listname', fromemail='$bounceemail', adminemail='$listowneremail', bounceemail='$bounceemail', listtype='$listtype', message='$message', footer='$footer', header='$header', subconfirm='$subconfirm', subsuccess='$subsuccess', unsubsuccess='$unsubsuccess', paymenthtml='$paymenthtml', created='1', html='$html' WHERE listname='$listname' AND listownerID='$listownerID'");
	    $midnight = mktime(0, 0, -1, date("m"), date("d"), date("y"));
	    $midnight = timestamp_to_mysql_timestamp($midnight);
	    $db->Query("INSERT INTO system VALUES('$listownerID','$listname',$midnight)");
	    $db->Query("INSERT INTO listconfig VALUES('$listownerID','$listname','$program_name','$commission','','$admin_email_address','$logout_location','$upgradeinfo','$numurltrackersMem','$numurltrackersPro','$numurltrackersExe','$mem_sendmail_times_week','$pro_sendmail_times_week','$exe_sendmail_times_day','$cost_of_pro','$cost_of_exe','$pro_upgradeform','$exe_upgradeform','','$defaultstatus','$allowupgrades','$newmembernotice','0')");
		}
	}

	$price -= 1;
	$fees = $price * .075;
	$price -= $fees;
	$profits = number_format($price, 2, '.', '');

	$db->SelectDB('pxm');
	$db->Query("INSERT INTO transactions VALUES('','pxm_signup','{$profits}','clickbank','{$cbreceipt}',NOW())");
}

?>
