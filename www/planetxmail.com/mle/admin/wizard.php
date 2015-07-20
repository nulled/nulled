<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/wizard.inc");
?>
<html>
<head>
<title>PayLink Setup Wizard</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script>
<!--
function checkpaylinks(formname)
{
	if (formname.clickbankusername.value!='')
	{
		if (formname.clickbanksignuppro.value=='' || formname.clickbanksignupexe.value=='' || formname.clickbankrenewalpro.value=='' || formname.clickbankrenewalexe.value=='' || formname.clickbankupgradepro.value=='' || formname.clickbankupgradeexe.value=='')
		{
			alert('You have your Click Bank user name set but\nare missing 1 or more of your click bank links!');
			return;
		}
		else if (formname.clickbankcgikey.value=='')
		{
			alert('Your ClickBank CGI Key is missing!');
			return;
		}
	}

	if (formname.egold.value!='' && formname.egoldaltpass.value=='')
	{
		alert('You forgot to set your e-gold alternate passphrase!');
		return;
	}

	formname.submit();
}
//-->
</script>
</head>
<body>
<table width="640" cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td colspan="2">
			<center><h3>PayLink/SafeList Setup Wizard</h3></center>
			This tool will set up your SafeList and Paylinks in an easy to use Wizard. Just answer it's questions
			as you go and your SafeList will be setup occordinly to accept Payments for upgrading. This replaces
			the manual method which is still available to you.
			<hr />
			<?php if ($notValid) echo "<br /><center><b class=\"red\">$notValid</b></center><br />"; ?>
			<form name="wizard" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
			<input type="text" name="admin_email_address" value="<?=$admin_email_address?>" size="30"> What email address do you want us to send your Monthly bill to?
			<br />
			<input type="text" name="emailformembers" value="<?=$emailformembers?>" size="30"> What do you want your Member Support email address to be?
			<br /><br />
			What will the <b>FROM</b> text to be in outgoing emails? Example: <b>FROM:</b> &lt;do_not_reply@planetxmail.com&gt<br />
			<input type="text" name="fromname" value="<?=$fromname?>" size="20"> &lt;do_not_reply@planetxmail.com&gt
			<br />Note: We use <i>do_not_reply@planetxmail.com</i> to keep member email addresses confidential.
			<br /><br />
			What do you want the Title of the Web Browser to say?
			<br />
			<input type="text" name="program_name" value="<?=$program_name?>" size="20">
			<br /><br />
			What URL do you want members to be taken to after they log off?
			<input type="text" name="logout_location" value="<?=$logout_location?>" size="80">
			<br /><br />
			<input type="text" name="numurltrackersMem" value="<?=$numurltrackersMem?>" size="2" maxlength="3"> How many URL Trackers will <b>Free</b> Members be Allowed?
			<br />
			<input type="text" name="numurltrackersPro" value="<?=$numurltrackersPro?>" size="2" maxlength="3"> How many URL Trackers will <b>Professional</b> Members be Allowed?
			<br />
			<input type="text" name="numurltrackersExe" value="<?=$numurltrackersExe?>" size="2" maxlength="3"> How many URL Trackers will <b>Executive</b> Members be Allowed?
			<hr />
      <b>Regular Mailer Options:</b>
      <br /><br />
			<input type="text" name="mem_sendmail_times_week" value="<?=$mem_sendmail_times_week?>" size="2" maxlength="1"> How many times per week can <b>Free</b> Members Regular Mailer? ( 7 Max, 1 a Day )
			<br />
			<input type="text" name="pro_sendmail_times_week" value="<?=$pro_sendmail_times_week?>" size="2" maxlength="1"> How many times per week can <b>Professional</b> Members Regular Mailer? ( 7 Max, 1 a Day )
			<br />
			Note: <b>Executive</b> Members can Regular Mailer 1 time per day ( 7 times per week by default )
			<br /><br />
			<hr />
      <b>Credit Mailer Options:</b>
      <br /><br />
      <input type="text" name="mem_sendmailcredits_times_week" value="<?=$mem_sendmailcredits_times_week?>" size="2" maxlength="1"> How many times per week can <b>Free</b> Members Credit Mailer? ( 7 Max, 1 a Day )
			<br />
			<input type="text" name="pro_sendmailcredits_times_week" value="<?=$pro_sendmailcredits_times_week?>" size="2" maxlength="1"> How many times per week can <b>Professional</b> Members Credit Mailer? ( 7 Max, 1 a Day )
			<br />
			Note: <b>Executive</b> Members can Credit Mailer 1 time per day ( 7 times per week by default )
			<br /><br />
      <input type="text" name="freestartcredits" value="<?=$freestartcredits?>" size="6" maxlength="4"> How many Credits will <b>Free</b> Members start with?
			<br />
			<input type="text" name="prostartcredits" value="<?=$prostartcredits?>" size="6" maxlength="4"> How many Credits will <b>Professional</b> Members start with?
			<br />
			<input type="text" name="exestartcredits" value="<?=$exestartcredits?>" size="6" maxlength="4"> How many Credits will <b>Executive</b> Members start with?
			<br /><br />
			<input type="text" name="freeearnedcredits" value="<?=$freeearnedcredits?>" size="3" maxlength="3"> How many Credits will <b>Free</b> Members earn per Email read?
			<br />
			<input type="text" name="proearnedcredits" value="<?=$proearnedcredits?>" size="3" maxlength="3"> How many Credits will <b>Professional</b> Members earn per Email read?
			<br />
			<input type="text" name="exeearnedcredits" value="<?=$exeearnedcredits?>" size="3" maxlength="3"> How many Credits will <b>Executive</b> Members earn per Email read?
			<br /><br />
      <hr />
			If you wish to enable the <b>Affiliate System</b>, simply enter in the URL you want all Affiliates to be taken to, below.  This is
			typically your SALES PAGES where they read about what you have to offer and your paylinks.  If you leave the URL below
			BLANK then the Affiliate System will be turned OFF. <a href="#" onClick="window.open('refererhelp.php',0,'height=500,width=640,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1')"><b>More Info.</b></a><br />
			<input type="text" name="referer" value="<?=$referer?>" size="80">
			<br /><br />
		<input type="text" name="commission_pro" value="<?=$commission_pro?>" size="2"> % Commission earned per <b>Professional</b> Signup/Renewal/Upgrade. ( Max is 75% commission )
			<br />
			<input type="text" name="commission_exe" value="<?=$commission_exe?>" size="2"> % Commission earned per <b>Executive</b> Signup/Renewal/Upgrade. ( Max is 75% commission )
			<br /><br />
			<select name="allowrenewalcommission" size="1">
	      <option value="0"<?php if ($allowrenewalcommission=="0") echo " SELECTED"; ?>>No Renewal - No Upgrade</option>
				<option value="1"<?php if ($allowrenewalcommission=="1") echo " SELECTED"; ?>>Yes Renewal - NO Upgrade</option>
				<option value="2"<?php if ($allowrenewalcommission=="2") echo " SELECTED"; ?>>No Renewal - YES Upgrade</option>
				<option value="3"<?php if ($allowrenewalcommission=="3") echo " SELECTED"; ?>>Yes Renewal - YES Upgrade</option>
	    </select>  Do you want to issue Commissions for RENEWAL and/or UPGRADE payments you receive? There are FOUR (4) possiblies.
	    Commissions go to the user that initally referered the member that is upgrading or renewing. <b>Note:</b> That if your Check Billing
	    is NOT turned on or your ALLOW Upgrade is NOT turned on then the respective Renewal/Upgrade may not apply.  Also if your
	    Affililate URL director is NOT turned on then none of this will apply.
	    <i>Affiliate URL Director is set above.</i>.
	    <br /><br />
			<select name="cleanmembers" size="1">
	      <option value="0"<?php if ($cleanmembers=="0" || ! $cleanmembers) echo " SELECTED"; ?>>Never Remove</option>
				<option value="1"<?php if ($cleanmembers=="1") echo " SELECTED"; ?>>After 3 Months</option>
				<option value="2"<?php if ($cleanmembers=="2") echo " SELECTED"; ?>>After 6 Months</option>
				<option value="3"<?php if ($cleanmembers=="3") echo " SELECTED"; ?>>After 9 Months</option>
				<option value="4"<?php if ($cleanmembers=="4") echo " SELECTED"; ?>>After 1 Year</option>
	    </select>  Do you want to remove <b>Inactive Members</b>? Inactive means, if they do not log in.  Members only need to LOG IN
	    to be considered Active.  This feature is recommened since, if the member has NOT logged in past 3+ months they are most
	    likely bouncing, not reachable or quit participating all together, therefore making your list cluttered with "dead accounts".
			<br /><br />
			<select name="newmembernotice" size="1">
	      <option value="0"<?php if ($newmembernotice=="0") echo " SELECTED"; ?>>No</option>
				<option value="1"<?php if ($newmembernotice=="1") echo " SELECTED"; ?>>Yes</option>
	    </select>  Do you want to receive <b>New Member</b> Signup notices?
      <br /><br />
			<select name="allowupgrades" size="1">
        <option value="0"<?php if ($allowupgrades=="0") echo " SELECTED"; ?>>No</option>
        <option value="1"<?php if ($allowupgrades=="1") echo " SELECTED"; ?>>Yes</option>
      </select> Allow upgrading? No, hides the upgrade buttons and no one can upgrade.
      <br /><br />
      <select name="defaultstatus" size="1">
        <option value="mem"<?php if ($defaultstatus=="mem") echo " SELECTED"; ?>>Free Member</option>
        <option value="pro"<?php if ($defaultstatus=="pro") echo " SELECTED"; ?>>Professional</option>
        <option value="exe"<?php if ($defaultstatus=="exe") echo " SELECTED"; ?>>Executive</option>
      </select> What do you want your default member status to be upon sign up? Setting it to Pro or Exec will make your list a PAID list only.
      <br /><br />
			$ <input type="text" name="cost_of_pro" value="<?=$cost_of_pro?>" size="6"> How much do you charge to <i>SIGN UP</i> as <b>Professional</b> Member?
			<br />
			$ <input type="text" name="cost_of_exe" value="<?=$cost_of_exe?>" size="6"> How much do you charge to <i>SIGN UP</i> as <b>Executive</b> Member?
			<br /><br />
			$ <input type="text" name="cost_of_pro_renewal" value="<?=$cost_of_pro_renewal?>" size="6"> How much do you charge to <i>RENEW</i> as a <b>Professional</b> Member?
			<br />
			$ <input type="text" name="cost_of_exe_renewal" value="<?=$cost_of_exe_renewal?>" size="6"> How much do you charge to <i>RENEW</i> as an <b>Executive</b> Member?
			<br /><br />
			$ <input type="text" name="cost_of_pro_upgrade" value="<?=$cost_of_pro_upgrade?>" size="6"> How much do you charge to <i>UPGRADE</i> to a <b>Professional</b> Member?
			<br />
			$ <input type="text" name="cost_of_exe_upgrade" value="<?=$cost_of_exe_upgrade?>" size="6"> How much do you charge to <i>UPGRADE</i> to an <b>Executive</b> Member?
			<br /><br />

      <center><h2>Merchant Billing Setup</h2>
      <hr />
			<a href="#" onClick="window.open('billingcheck.php',0,'height=600,width=750,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1,top=100,left=100')">How Billing Check System Works - MUST READ</a>
			</center>
			<br /><br />
			<select name="dobillingcheck" size="1">
        <option value="0"<?php if ($dobillingcheck=="0") echo " SELECTED"; ?>>No</option>
        <option value="1"<?php if ($dobillingcheck=="1") echo " SELECTED"; ?>>Yes</option>
      </select> Active The Billing Check System?
      <br /><br />
      <select name="renewaltype" size="1">
        <option value="0"<?php if ($renewaltype=="0") echo " SELECTED"; ?>>Monthly</option>
        <option value="1"<?php if ($renewaltype=="1") echo " SELECTED"; ?>>Bi-Monthly</option>
        <option value="2"<?php if ($renewaltype=="2") echo " SELECTED"; ?>>Quarterly</option>
        <option value="3"<?php if ($renewaltype=="3") echo " SELECTED"; ?>>Yearly</option>
        <option value="4"<?php if ($renewaltype=="4") echo " SELECTED"; ?>>Lifetime</option>
      </select> What increment do you want to rebill your members?  Will ONLY work if the <b>Billing Check System</b> is set to Yes (on).

      <hr />

      <input type="text" name="testmode_username" value="<?=$testmode_username?>" size="15" maxlength="20" />
			<font color="red"><b>Test Mode Username</b> - Leave Blank to turn OFF test mode.</font> Then log in / sign up
			using this Username to test the Payment System. All others that try to Upgrade or Renew will be given a notice
			that you are testing the system. Once you see all is working then ERASE the test mode username from here and this
			will make your List live for processing orders.
			<br /><br />

      <hr />
      <center><a href="#" onClick="window.open('billingcheck.php',0,'height=600,width=750,status=0,toolbar=0,menubar=0,resizable=1,location=0,scrollbars=1,top=100,left=100')"><font size="3" color="red"><b>How to Set up each Merchant Account</b></font></a></center>

		</td>
	</tr>

	<tr>
		<td colspan="2">
			<br />
			Whats your <b>Paypal</b> Email Account?
			<br />
			<input type="text" name="paypal" value="<?=$paypal?>" size="25">

			<br /><br /><hr />
			Whats your <b>egold</b> number?
			<br />
			<input type="text" name="egold" value="<?=$egold?>" size="15">
			<br />
			Whats your <b>egold</b> Alternate Passphrase?
			<br />
			<input type="text" name="egoldaltpass" value="<?=$egoldaltpass?>" size="25">

			<br /><br /><hr />

			<br />
			Whats your <b>2Checkout</b> Account Number? <input type="text" name="tcousername" value="<?=$tcousername?>" size="15">
			<br />
			Whats your 2Checkout <b>Secret Word</b>? <input type="text" name="tcocgikey" value="<?=$tcocgikey?>" size="20">
			<br />
			<input type="text" name="tcosignuppro" value="<?=$tcosignuppro?>" size="2"> 2Checkout prod ID for <b>Pro</b> Signups.
			<br />
			<input type="text" name="tcosignupexe" value="<?=$tcosignupexe?>" size="2"> 2Checkout prod ID for <b>Exec</b> Signups.
			<br />
			<input type="text" name="tcorenewalpro" value="<?=$tcorenewalpro?>" size="2"> 2Checkout prod ID for <b>Pro</b> Renewals.
			<br />
			<input type="text" name="tcorenewalexe" value="<?=$tcorenewalexe?>" size="2"> 2Checkout prod ID for <b>Exec</b> Renewals.
			<br />
			<input type="text" name="tcoupgradepro" value="<?=$tcoupgradepro?>" size="2"> 2Checkout prod ID for <b>Pro</b> Upgrades.
			<br />
			<input type="text" name="tcoupgradeexe" value="<?=$tcoupgradeexe?>" size="2"> 2Checkout prod ID for <b>Exec</b> Upgrades.
      <br /><br /><hr />

      <br />
			Whats your <b>AlertPay</b> Email Address?
			<br />
			<input type="text" name="alertpay" value="<?=$alertpay?>" size="35">
			<br />
			Whats your <b>AlertPay</b> Security Code?
			<br />
			<input type="text" name="alertpaycgikey" value="<?=$alertpaycgikey?>" size="35">

			<br /><br /><hr />

			<br />
			Whats your <b>ClickBank</b> User Name? <input type="text" name="clickbankusername" value="<?=$clickbankusername?>" size="15">
			<br />
			Whats your ClickBank <b>Secret Key</b>? <input type="text" name="clickbankcgikey" value="<?=$clickbankcgikey?>" size="20">
			<br />
		  <input type="text" name="clickbanksignuppro" value="<?=$clickbanksignuppro?>" size="2"> ClickBank link # for <b>Pro</b> Signups.
			<br />
			<input type="text" name="clickbanksignupexe" value="<?=$clickbanksignupexe?>" size="2"> ClickBank link # for <b>Exec</b> Signups.
			<br />
			<input type="text" name="clickbankrenewalpro" value="<?=$clickbankrenewalpro?>" size="2"> ClickBank link # for <b>Pro</b> Renewals.
			<br />
			<input type="text" name="clickbankrenewalexe" value="<?=$clickbankrenewalexe?>" size="2"> ClickBank link # for <b>Exec</b> Renewals.
			<br />
			<input type="text" name="clickbankupgradepro" value="<?=$clickbankupgradepro?>" size="2"> ClickBank link # for <b>Pro</b> Upgrades.
			<br />
			<input type="text" name="clickbankupgradeexe" value="<?=$clickbankupgradeexe?>" size="2"> ClickBank link # for <b>Exec</b> Upgrades.
			<br /><br />
			<b>Note:</b> Payment methods that you do not have just <i>leave blank</i> and the system will not configure your list to use them.
		</td>
  </tr>

	<tr>
    <td>
    	<input type="hidden" name="submitted" value="save">
    	<input type="button" class="greenbutton" value="Save Configuration" onClick="checkpaylinks(this.form)">
    </td>
    <td align="right">
    	<input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
    </td>
  </tr>

  </form>
</table>
</body>
</html>