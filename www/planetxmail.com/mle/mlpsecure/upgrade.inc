<?php
require_once("mlpsecure/config/config.inc");
require_once("mlpsecure/validationfunctions.php");
require_once('/home/nulled/www/planetxmail.com/phpsecure/paylinks.class.inc');

$paylinks = new PayLinks($_SESSION['aauserID']);

if ($cb_pro_link = $paylinks->get_paylink('clickbank', 'pro', 'upgrade')) $cb_pro_link .= '<hr />';
if ($cb_exe_link = $paylinks->get_paylink('clickbank', 'exe', 'upgrade')) $cb_exe_link .= '<hr />';
if ($eg_pro_link = $paylinks->get_paylink('egold', 'pro', 'upgrade')) $eg_pro_link .= '<hr />';
if ($eg_exe_link = $paylinks->get_paylink('egold', 'exe', 'upgrade')) $eg_exe_link .= '<hr />';
if ($tc_pro_link = $paylinks->get_paylink('twocheckout', 'pro', 'upgrade')) $tc_pro_link .= '<hr />';
if ($tc_exe_link = $paylinks->get_paylink('twocheckout', 'exe', 'upgrade')) $tc_exe_link .= '<hr />';
if ($ap_pro_link = $paylinks->get_paylink('alertpay', 'pro', 'upgrade')) $ap_pro_link .= '<hr />';
if ($ap_exe_link = $paylinks->get_paylink('alertpay', 'exe', 'upgrade')) $ap_exe_link .= '<hr />';
if ($pp_pro_link = $paylinks->get_paylink('paypal', 'pro', 'upgrade')) $pp_pro_link .= '<hr />';
if ($pp_exe_link = $paylinks->get_paylink('paypal', 'exe', 'upgrade')) $pp_exe_link .= '<hr />';

$pro_benefits = $paylinks->get_benefits('pro');
$exe_benefits = $paylinks->get_benefits('exe');

if ($paylinks->status == 'mem')
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
	    <font size="+1">Upgrade to Professional</font>
	  </td>
	  <td bgcolor="lightblue" align="center">
	   <font size="+1">Upgrade to Executive</font>
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
else if ($paylinks->status == 'pro')
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
	    <font size="+1">Upgrade to Executive</font>
	  </td>
	</tr>

	<tr>
	  <td bgcolor="beige" colspan="2" align="center">'.$upgradeexe.'</td>
	</tr>
	';
}
else
  $upgradehtml = '<tr><td align="center" colspan="2"><h3>You can not Upgrade any further.</h3></td></tr>';

?>