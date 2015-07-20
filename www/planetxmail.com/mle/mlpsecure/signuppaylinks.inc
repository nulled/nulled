<?php
require_once('mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/phpsecure/paylinks.class.inc');

$db = new MySQL_Access();

if (! $u OR ! $v) exit('ERROR: User and/or v param missing.');

$userID = strrev($u);

$validator = strrev(substr(sha1(md5($userID)), 0, 5));

if ($validator != $v) exit('ERROR: Unable to validate as authentic.');

// check user exists

if ($db->Query("SELECT status, fname, lname, email, verified, listname, listownerID FROM users WHERE userID='$userID'"))
	list($status, $fname, $lname, $email, $verified, $listname, $listownerID) = $db->FetchRow();
else
  exit('ERROR: Unable to find user.');

// check list exists
if ($db->Query("SELECT listhash FROM listurls WHERE listownerID='$listownerID' AND listname='$listname'"))
	list($listhash) = $db->FetchRow();
else
  exit('ERROR: Unable to find listhash.');

// if member is free then redirect to validate them
if ($status == 'mem')
{
	$validator = strrev(substr(md5($userID.$email), 0, 5));
	header ("Location: http://planetxmail.com/mle/au.php?u=$u&v=$validator");
	exit;
}

if ($verified == 'yes')	exit("This account is already Signed up! If you wish to UPGRADE this account you can do so by logging in to the safelist and using the upgrade link.");

// get title graphic for list
$db->Query("SELECT banner FROM banners WHERE listownerID='$listownerID' AND listname='$listname' AND bannerlink='TITLE_GRAPHIC'");
list($titleIMG) = $db->FetchRow();

$paylinks = new PayLinks($userID);

if ($cb_pro_link = $paylinks->get_paylink('clickbank', 'pro', 'signup')) $cb_pro_link .= '<hr />';
if ($cb_exe_link = $paylinks->get_paylink('clickbank', 'exe', 'signup')) $cb_exe_link .= '<hr />';
if ($eg_pro_link = $paylinks->get_paylink('egold', 'pro', 'signup')) $eg_pro_link .= '<hr />';
if ($eg_exe_link = $paylinks->get_paylink('egold', 'exe', 'signup')) $eg_exe_link .= '<hr />';
if ($tc_pro_link = $paylinks->get_paylink('twocheckout', 'pro', 'signup')) $tc_pro_link .= '<hr />';
if ($tc_exe_link = $paylinks->get_paylink('twocheckout', 'exe', 'signup')) $tc_exe_link .= '<hr />';
if ($ap_pro_link = $paylinks->get_paylink('alertpay', 'pro', 'signup')) $ap_pro_link .= '<hr />';
if ($ap_exe_link = $paylinks->get_paylink('alertpay', 'exe', 'signup')) $ap_exe_link .= '<hr />';
if ($pp_pro_link = $paylinks->get_paylink('paypal', 'pro', 'upgrade')) $pp_pro_link .= '<hr />';
if ($pp_exe_link = $paylinks->get_paylink('paypal', 'exe', 'upgrade')) $pp_exe_link .= '<hr />';

$pro_benefits = $paylinks->get_benefits('pro');
$exe_benefits = $paylinks->get_benefits('exe');

if ($paylinks->defaultstatus == 'pro')
{
  $upgradepro  = "{$cb_pro_link}{$eg_pro_link}{$tc_pro_link}{$ap_pro_link}{$pp_pro_link}";
  $upgradeexe  = "{$cb_exe_link}{$eg_exe_link}{$tc_exe_link}{$ap_exe_link}{$pp_exe_link}";

	$upgradehtml = '
	<tr>
	  <td width="50%">'.$pro_benefits.'</td>
	  <td width="50%">'.$exe_benefits.'</td>
	</tr>

	<tr>
	  <td colspan="2" align="center"><hr /><h2>Method of Payments</h2></td>
	</tr>

	<tr>
	  <td bgcolor="beige" align="center">
	    <font size="+1">Signup as Professional</font>
	  </td>
	  <td bgcolor="lightblue" align="center">
	   <font size="+1">Signup as Executive</font>
	  </td>
	</tr>

	<tr>
	  <td bgcolor="beige"><hr /></td>
	  <td bgcolor="lightblue"><hr /></td>
	</tr>

	<tr>
	  <td bgcolor="beige" align="center">'.$upgradepro.'</td>
	  <td bgcolor="lightblue" align="center">'.$upgradeexe.'</td>
	</tr>
	';
}
else if ($paylinks->defaultstatus == 'exe')
{
  $upgradeexe  = "{$cb_exe_link}{$eg_exe_link}{$tc_exe_link}{$ap_exe_link}{$pp_exe_link}";

	$upgradehtml = '
	<tr>
	  <td colspan="2">'.$exe_benefits.'</td>
	</tr>

	<tr>
	  <td colspan="2" align="center"><hr /><h2>Method of Payments</h2></td>
	</tr>

	<tr bgcolor="beige">
	  <td colspan="2" align="center" bgcolor="beige">
	    <font size="+1">Signup as Executive</font>
	  </td>
	</tr>

	<tr>
	  <td bgcolor="beige" colspan="2" align="center">'.$upgradeexe.'</td>
	</tr>
	';
}

?>