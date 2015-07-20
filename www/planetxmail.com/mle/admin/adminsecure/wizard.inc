<?php
include("../mlpsecure/config/classes.inc");
include("../mlpsecure/validationfunctions.php");

$db = new MySQL_Access();

if ($submitted=="save")
{
	if ($emailformembers && $admin_email_address && $logout_location && $numurltrackersMem!="" && $numurltrackersPro!="" &&
		  $numurltrackersExe!="" && $mem_sendmail_times_week && $pro_sendmail_times_week)
	{
    if ($notValid = EmailFormat($emailformembers = trim($emailformembers),0)) {}
    else if (has_weird($fromname = trim($fromname))) $notValid = "ERROR: From email name can only have a-z, A-Z, 0-9 or _ in it.";
    else if ($notValid = has_space($fromname)) {}
    else if (strlen($fromname)>20) $notValid = "ERROR: FROM name for your outgoing email must be 3-20 chars.";
    else if (strlen($fromname)<3) $notValid = "ERROR: FROM name for your outgoing email must be 3-20 chars.";
    else if ($notValid = EmailFormat($admin_email_address = trim($admin_email_address),0)) {}
    else if ($paypal!="" && $notValid = EmailFormat($paypal = trim($paypal),0)) {}
    else if ($alertpay!="" && $notValid = EmailFormat($alertpay = trim($alertpay),0)) {}
    else if (!is_numeric($mem_sendmail_times_week = floor(trim($mem_sendmail_times_week)))) $notValid = "ERROR: mem_sendmail_times_week not a number.";
    else if (!is_numeric($pro_sendmail_times_week = floor(trim($pro_sendmail_times_week)))) $notValid = "ERROR: pro_sendmail_times_week not a number.";

    else if (!is_numeric($mem_sendmailcredits_times_week = floor(trim($mem_sendmailcredits_times_week)))) $notValid = "ERROR: mem_sendmailcredits_times_week not a number.";
    else if (!is_numeric($pro_sendmailcredits_times_week = floor(trim($pro_sendmailcredits_times_week)))) $notValid = "ERROR: pro_sendmailcredits_times_week not a number.";

    else if (!is_numeric($numurltrackersMem = floor(trim($numurltrackersMem)))) $notValid = "ERROR: numurltrackersMem not a number.";
    else if (!is_numeric($numurltrackersPro = floor(trim($numurltrackersPro)))) $notValid = "ERROR: numurltrackersPro not a number.";
    else if (!is_numeric($numurltrackersExe = floor(trim($numurltrackersExe)))) $notValid = "ERROR: numurltrackersExe not a number.";

    else if (!is_numeric($freestartcredits = floor(trim($freestartcredits)))) $notValid = "ERROR: freestartcredits not a number.";
    else if (!is_numeric($prostartcredits = floor(trim($prostartcredits)))) $notValid = "ERROR: prostartcredits not a number.";
    else if (!is_numeric($exestartcredits = floor(trim($exestartcredits)))) $notValid = "ERROR: exestartcredits not a number.";

    else if (!is_numeric($freeearnedcredits = floor(trim($freeearnedcredits)))) $notValid = "ERROR: freeearnedcredits not a number.";
    else if (!is_numeric($proearnedcredits = floor(trim($proearnedcredits)))) $notValid = "ERROR: proearnedcredits not a number.";
    else if (!is_numeric($exeearnedcredits = floor(trim($exeearnedcredits)))) $notValid = "ERROR: exeearnedcredits not a number.";

    else if ($freestartcredits > 50) $notValid = "ERROR: free start credits can not exceed 50.";
    else if ($prostartcredits > 50) $notValid = "ERROR: pro start credits can not exceed 50.";
    else if ($exestartcredits > 50) $notValid = "ERROR: exe start credits can not exceed 50.";

    else if ($freeearnedcredits > 5) $notValid = "ERROR: free earned credits can not exceed 5.";
    else if ($proearnedcredits > 5) $notValid = "ERROR: pro earned credits can not exceed 5.";
    else if ($exeearnedcredits > 5) $notValid = "ERROR: exe earned credits can not exceed 5.";

    else if (!is_numeric($cost_of_pro = number_format(trim($cost_of_pro), 2, '.', ''))) $notValid = "ERROR: cost_of_pro_signup not a number.";
    else if (!is_numeric($cost_of_exe = number_format(trim($cost_of_exe), 2, '.', ''))) $notValid = "ERROR: cost_of_exe_signup not a number.";
    else if (!is_numeric($cost_of_pro_renewal = number_format(trim($cost_of_pro_renewal), 2, '.', ''))) $notValid = "ERROR: cost_of_pro_renewal not a number.";
    else if (!is_numeric($cost_of_exe_renewal = number_format(trim($cost_of_exe_renewal), 2, '.', ''))) $notValid = "ERROR: cost_of_exe_renewal not a number.";
    else if (!is_numeric($cost_of_pro_upgrade = number_format(trim($cost_of_pro_upgrade), 2, '.', ''))) $notValid = "ERROR: cost_of_pro_upgrade not a number.";
    else if (!is_numeric($cost_of_exe_upgrade = number_format(trim($cost_of_exe_upgrade), 2, '.', ''))) $notValid = "ERROR: cost_of_exe_upgrade not a number.";
    else if ($commission_pro!="" && ! is_numeric($commission_pro = str_replace("%", "", trim($commission_pro)))) $notValid = "ERROR: commission_pro not a number.";
    else if ($commission_exe!="" && ! is_numeric($commission_exe = str_replace("%", "", trim($commission_exe)))) $notValid = "ERROR: commission_exe not a number.";
    else if ($commission_pro!="" && $commission_pro > 75) $notValid = "ERROR: commission_pro can not be greater then 75 percent.";
    else if ($commission_exe!="" && $commission_exe > 75) $notValid = "ERROR: commission_exe can not be greater then 75 percent.";

    else if ($egold!="" && !is_numeric($egold = floor(trim($egold)))) $notValid = "ERROR: egold not a number.";
    else if ($tcousername!="" && !is_numeric($tcousername = floor(trim($tcousername)))) $notValid = "ERROR: tcousername not a number.";

    else if ($clickbanksignuppro!="" && ! is_numeric($clickbanksignuppro = floor(trim($clickbanksignuppro)))) $notValid = "ERROR: clickbanksignuppro not a number.";
    else if ($clickbanksignupexe!="" && ! is_numeric($clickbanksignupexe = floor(trim($clickbanksignupexe)))) $notValid = "ERROR: clickbanksignupexe not a number.";
    else if ($clickbankrenewalpro!="" && ! is_numeric($clickbankrenewalpro = floor(trim($clickbankrenewalpro)))) $notValid = "ERROR: clickbankrenewalpro not a number.";
    else if ($clickbankrenewalexe!="" && ! is_numeric($clickbankrenewalexe = floor(trim($clickbankrenewalexe)))) $notValid = "ERROR: clickbankrenewalexe not a number.";
    else if ($clickbankupgradepro!="" && ! is_numeric($clickbankupgradepro = floor(trim($clickbankupgradepro)))) $notValid = "ERROR: clickbankupgradepro not a number.";
    else if ($clickbankupgradeexe!="" && ! is_numeric($clickbankupgradeexe = floor(trim($clickbankupgradeexe)))) $notValid = "ERROR: clickbankupgradeexe not a number.";

    else if ($tcosignuppro!="" && ! is_numeric($tcosignuppro = floor(trim($tcosignuppro)))) $notValid = "ERROR: tcosignuppro not a number.";
    else if ($tcosignupexe!="" && ! is_numeric($tcosignupexe = floor(trim($tcosignupexe)))) $notValid = "ERROR: tcosignupexe not a number.";
    else if ($tcorenewalpro!="" && ! is_numeric($tcorenewalpro = floor(trim($tcorenewalpro)))) $notValid = "ERROR: tcorenewalpro not a number.";
    else if ($tcorenewalexe!="" && ! is_numeric($tcorenewalexe = floor(trim($tcorenewalexe)))) $notValid = "ERROR: tcorenewalexe not a number.";
    else if ($tcoupgradepro!="" && ! is_numeric($tcoupgradepro = floor(trim($tcoupgradepro)))) $notValid = "ERROR: tcoupgradepro not a number.";
    else if ($tcoupgradeexe!="" && ! is_numeric($tcoupgradeexe = floor(trim($tcoupgradeexe)))) $notValid = "ERROR: tcoupgradeexe not a number.";

    else
    {
      $testmode_username = trim($testmode_username);

      $alertpaycgikey  = urldecode(trim($alertpaycgikey));
      $tcocgikey       = trim($tcocgikey);
    	$clickbankcgikey = trim($clickbankcgikey);
    	$referer         = trim($referer);
	    $logout_location = trim($logout_location);
	    $pro_upgradeform = trim($pro_upgradeform);
	    $exe_upgradeform = trim($exe_upgradeform);

    	if (! $commission_pro) $commission_pro = '0';
	    if (! $commission_exe) $commission_exe = '0';
	    if (! is_numeric($allowrenewalcommission)) $allowrenewalcommission = '0';
	    if (! is_numeric($cleanmembers))  $cleanmembers   = '0';
	    if (! is_numeric($renewaltype))   $renewaltype    = '0';
	  	if (! is_numeric($dobillingcheck))$dobillingcheck = '0';

	    if ($cost_of_pro < 0) $cost_of_pro = 0;
	    if ($cost_of_exe < 0) $cost_of_exe = 0;
	    if ($cost_of_pro_renewal < 0) $cost_of_pro_renewal = 0;
	    if ($cost_of_exe_renewal < 0) $cost_of_exe_renewal = 0;
	    if ($cost_of_pro_upgrade < 0) $cost_of_pro_upgrade = 0;
	    if ($cost_of_exe_upgrade < 0) $cost_of_exe_upgrade = 0;

	    $cost_of_pro_all = "$cost_of_pro|$cost_of_pro_renewal|$cost_of_pro_upgrade";
	    $cost_of_exe_all = "$cost_of_exe|$cost_of_exe_renewal|$cost_of_exe_upgrade";

	    $commission = floor($commission_pro)."|".floor($commission_exe)."|".floor($allowrenewalcommission);

	    if ($mem_sendmail_times_week>7) $mem_sendmail_times_week = 7;
	  	if ($pro_sendmail_times_week>7) $pro_sendmail_times_week = 7;

	  	if ($mem_sendmailcredits_times_week>7) $mem_sendmailcredits_times_week = 7;
	  	if ($pro_sendmailcredits_times_week>7) $pro_sendmailcredits_times_week = 7;

	  	$paylinkparams = "$paypal|$egold|$clickbankusername|$clickbanksignuppro|$clickbanksignupexe|$clickbankrenewalpro|$clickbankrenewalexe|$clickbankupgradepro|$clickbankupgradeexe|$egoldaltpass|$dobillingcheck|$renewaltype|$clickbankcgikey|$cleanmembers|$tcousername|$tcosignuppro|$tcosignupexe|$tcorenewalpro|$tcorenewalexe|$tcoupgradepro|$tcoupgradeexe|$tcocgikey|$alertpay|$alertpaycgikey";

	    $db->Query("UPDATE listmanager SET paylinkparams='$paylinkparams', fromname='$fromname', adminemail='$emailformembers' WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");

	  	$db->Query("UPDATE listconfig SET defaultstatus='$defaultstatus',
	  	                                  referer='$referer',
	  	                                  commission='$commission',
	  	                                  adminemailaddress='$admin_email_address',
	  	                                  logoutlocation='$logout_location',
	  	                                  numurltrackersMem='$numurltrackersMem',
	  	                                  numurltrackersPro='$numurltrackersPro',
	  	                                  numurltrackersExe='$numurltrackersExe',
	  	                                  memsendmailweek='$mem_sendmail_times_week',
	  	                                  prosendmailweek='$pro_sendmail_times_week',
	  	                                  memsendmailcreditsweek='$mem_sendmailcredits_times_week',
	  	                                  prosendmailcreditsweek='$pro_sendmailcredits_times_week',
	  	                                  exesendmailday='1',
	  	                                  exesendmailcreditsday='1',
	  	                                  costofpro='$cost_of_pro_all',
	  	                                  costofexe='$cost_of_exe_all',
	  	                                  proupgradeform='$pro_upgradeform',
	  	                                  exeupgradeform='$exe_upgradeform',
	  	                                  testmode_username='$testmode_username',
	  	                                  allowupgrades='$allowupgrades',
	  	                                  newmembernotice='$newmembernotice',
  	                                    programname='$program_name',
	  	                                  freestartcredits='$freestartcredits',
	  	                                  prostartcredits='$prostartcredits',
	  	                                  exestartcredits='$exestartcredits',
	  	                                  freeearnedcredits='$freeearnedcredits',
	  	                                  proearnedcredits='$proearnedcredits',
	  	                                  exeearnedcredits='$exeearnedcredits'
	  	                                  WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");

			$db->Query("UPDATE listowner SET email='$admin_email_address' WHERE listownerID='$_SESSION[aalistownerID]'");

			$db->SelectDB("pxm");
			$db->Query("UPDATE orders SET listowneremail='$admin_email_address', email='$admin_email_address' WHERE listname='$_SESSION[aalistname]' AND listownername='$_SESSION[aalistownername]'");
			$db->SelectDB("mle");

			$notValid = "List Configuration settings updated.";
		}
	}
	else
		$notValid = "ERROR: Missing required params.";
}

include("../mlpsecure/config/config.inc");

$db->Query("SELECT adminemail, paylinkparams, fromname FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
list($emailformembers, $paylinkparams, $fromname) = $db->FetchRow();

list($paypal, $egold, $clickbankusername, $clickbanksignuppro, $clickbanksignupexe, $clickbankrenewalpro, $clickbankrenewalexe, $clickbankupgradepro, $clickbankupgradeexe, $egoldaltpass, $dobillingcheck, $renewaltype, $clickbankcgikey, $cleanmembers, $tcousername, $tcosignuppro, $tcosignupexe, $tcorenewalpro, $tcorenewalexe, $tcoupgradepro, $tcoupgradeexe, $tcocgikey, $alertpay, $alertpaycgikey) = explode('|', $paylinkparams);

?>