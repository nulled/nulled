<html>
<head>
<title>Billing Check System Help</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table cellpadding="2" cellspacing="0" align="left">
	<tr>
		<td>
			<center><font size="+1">Automated Billing System</font></center>
			<hr />
			<b>Automate and secure your online signup, renew and upgrade transactions.</b> With just a few minutes you can turn your
			SafeList into a fully automatic billing collection system.
			<ul>
			  <li>Goto <b>List Wizard</b> and set your prices, URL trackers, credits earned, commissions per status level.</li>
			  <li><b>Turn ON</b> Allow Upgrading.</li>
			  <li><b>Turn ON</b> Billing Check System.</li>
			  <li>Configure each Merchant, see below.</li>
			  <li>Specify a Test Mode Username that you use to test while blocking all others out during test.</li>
			  <li>Once the test is complete, Erase the Test Mode Username.</li>
			</ul>
			Your SafeList will then be ready to take orders.  All you do from then on is read notification emails, monitor each sale is properly
			working or just sit back and do nothing!
			<br /><br />
			<b>The system has these following advantages:</b>
			<ol>
			  <li>Automatically Upgrades, Renews and Signs up Members.</li>
			  <li>Emails and redirects them to the correct page after payment and non-payment.</li>
			  <li>Order price tamper detection and prevention system!</li>
			  <li>Utilizes each Merchant Accounts unique way of verifing your incoming orders are authentic!</li>
			  <li>Automatically calculates and records Commissions Owned to affiliates.</li>
			</ol>

			<center><font size="+1">Setting up Each Merchant in Detail</font></center>
      <hr />
			<a name="top"></a>
			<ul>
			  <li><a href="#paypal"><font size="3" color="green"><b>Paypal Setup</b></font></a></li>
			  <li><a href="#twocheckout"><font size="3" color="green"><b>2Checkout Setup</b></font></a></li>
			  <li><a href="#egold"><font size="3" color="green"><b>Egold Setup</b></font></a></li>
			  <li><a href="#clickbank"><font size="3" color="green"><b>Clickbank Setup</b></font></a></li>
			  <li><a href="#alertpay"><font size="3" color="green"><b>Alertpay Setup</b></font></a></li>
			  <li><a href="#testmode"><font size="3" color="green"><b>Test Mode Username Usage</b></font></a></li>
			</ul>
      <hr />
			<a name="paypal"><font size="3" color="green"><b>Paypal Setup</b></font></a> - <a href="#top">Top</a>
			<br /><br />
			Paypal has it's own Testing Grounds called <a href="https://developer.paypal.com" target="_blank">Paypal Developer Central</a>. You need to create a Paypal Developer Central account,
			then within the Paypal Developer Central, set up two accounts ( one used as a  customer, the other used as the payment receiver ).
			These two accounts look just like real Paypal accounts, complete with bank accounts, email notifications and IPN but are just used for testing.
			<br /><br />
			Goto <a href="https://developer.paypal.com" target="_blank">https://developer.paypal.com</a> and create an account. Requires a REAL Email Address.

			<ol>
			  <li>Log into <a href="https://developer.paypal.com" target="_blank">https://developer.paypal.com</a>. Create an account if needed.</li>
			  <li><b>Goto SANDBOX tab.</b></li>
			  <li><b>Create TWO accounts</b>, the Emails can be ANYTHING as it will ONLY be used in this SANDBOX.</li>
			  <li><b>Goto EMAIL tab</b> and <i>verify</i> the two accounts you just created.</li>
			  <li>Go Back to SANDBOX select an account and <b>LAUNCH SANDBOX</b> button.</li>
			  <li>Add a Bank account, verify it, Add funds, verify Email in Profile, setup the IPN.</li>
			  <li><b>Goto EMAIL tab in Paypal Developer</b> and <i>verify</i> anything sent by clicking on the validation urls.</li>
			  <li>Set IPN to: <font color="red"><b>http://planetxmail.com/mle/processorder.php</b></font> and <b>Turn IPN ON.</b></li>
			  <li>Log out, Goto SANDBOX tab select the second account you created, <b>LAUNCH SANDBOX</b> button.</li>
			  <li><i>Repeat the setup steps</i> as you did with the first one. Add bank, funds, verifiy email, IPN, etc.</li>
			  <li><b>In List Wizard set Paypal account to one of the FAKE accounts you created.</b></li>
			</ol>

			<b>Note:</b> The two accounts you created exist only in the Paypal Developer Central SANDBOX test environment, complete with Bank funds and using the EMAIL
			tab to receive fake Email Notifications. <i>At no time will you check a real Email Box! Use the EMAIL tab in the Paypal Developer Central instead!</i>
			<br /><br />
			<b>Now enter in a Test Mode Username</b> in the List Wizard. This will create Paypal payforms that will use the Paypal Developer Central SANDBOX
			instead of the regular Paypal.

			<ol>
			  <li>In <b>List Wizard</b> set your Paypal Email Account to a fake one from the Paypal Developer Central.</li>
			  <li>Set the <b>Test Mode Username</b> to a SafeList username you will use to test with.</li>
			  <li>Log into your SafeList with the Test Mode Username and do Upgrade, Renew, Signup tests...</li>
			  <li>Once the tests are satisfactory, Erase the Test Mode Username to make your site LIVE.</li>
			</ol>

			<b>Trouble Shooting:</b> Problems are usually as a result of the improper setup of the two fake Paypal accounts in the SANDBOX. You must Validate all Bank Accounts,
			Emails using the EMAIL TAB ( within the Paypal Developer Central SANDBOX ) in order for the IPN to work etc.
			<br /><br />
			The Paypal Developer Central is a <b>simulation of the real Paypal</b>.
			<b>Double check you properly verified each of the two fake Paypal accounts BANK, Added funds, validated Email from the EMAIL tab!</b>
			<hr />

			<a name="twocheckout"><font size="3" color="green"><b>2Checkout Setup</b></font></a> - <a href="#top">Top</a>
			<br /><br />
			2Checkout setup requires you to Add 6 (six) Products, ( Pro signup, Pro Renew, Pro Upgrade, Exec signup, Exec Renew, Exec Upgrade ).
			<ul>
			  <li>Log into your 2checkout Account.</li>
			  <li>Goto <b>Setup Products</b> Section</li>
			    <ol>
			      <li>Set <b>Your Product ID</b>. <b><u>Product ID</u></b> is what you <i>actually</i> enter in List Wizard.</li>
    			  <li>Set <b>Name</b> (Example: Pro Member Signup), the Price, non-tangible, no-shipping.</li>
    			  <li>Set <b>Pending/Approval URLs</b> both to <font color="red"><b>http://planetxmail.com/mle/processorder.php</b></font></li>
    			</ol>
			  <li>Goto <b>Look and Feel</b> Section</li>
			    <ol>
			      <li>Set <b>Direct Return</b> to YES</li>
			      <li>Set <b>Secret Word</b> to something random. <u><i>List Wizard must have this same Secret Word!</i></u></li>
			      <li>Optional: Upload a pretty logo you have which will be displayed when they checkout.</li>
			      <li>Optional: Approval/Pending URLs here are used as defaults. However, remember we set them for each Product earlier? You can set this if you have other things you are selling.</li>
			    </ol>
			</ul>
			Once, you have Added your 6 products, set the Pending/Approval URLs, Direct Return and Secret Word. All of this information needs to be entered
			into List Wizard!
			<br /><br />
			<font color="red"><b>Important:</b> <u>Enter 2Checkout <b>Product ID</b></u> NOT, 2Checkout's <b><i>Your Product ID</i></b> into the List Wizard.</font>
			<br /><br />
			<b>To test</b>, enter in a Test Mode Username in the List Wizard. You do not need to do anything to your 2checkout account to Test. Once, all works as it should,
			Erase the Test Mode Username to make your site LIVE!
			<hr />

			<a name="egold"><font size="3" color="green"><b>E-Gold Setup</b></font></a> - <a href="#top">Top</a>
			<br /><br />
			Egold requires you to set a Secret Word ( Alternate Pass Phrase ) and your ready to go.
			<ol>
			  <li>Log into your Egold Account.</li>
			  <li>Set <b>Alternate Pass Phrase</b> to something random.</li>
			</ol>
			Your Egold Account is ready. Now set up your SafeList.

			<ul>
			  <li>In <b>List Wizard</b> enter your <b>Egold Account</b> and <b>Alternate Pass Phrase</b>. <i>It is case sensitive!</i></li>
			  <li>Save settings...</li>
			</ul>
			<b>Important:</b> Do not confuse your Pass Phrase with <i>Alternate Pass Phrase</i>. The <i>Alternate Pass Phrase</i> is a secret Word used to authenticate
			Egold transactions. The Pass Phrase is the password to access your Egold account. Why didn't they just call it Secret Key? Beats me.
			<br /><br />
		  It is still a good idea to <b>Test by setting the Test Mode Username</b> in the List Wizard. It is possible to Pay yourself
			using your own Egold account to do the test. However, you will need some funds to do this. You can always temporarily set your Prices to something like
			$1.00, do the test, then set the price back.
			<hr />

			<a name="clickbank"><font size="3" color="green"><b>Clickbank Setup</b></font></a> - <a href="#top">Top</a>
			<br /><br />
			Clickbank uses one link per product, so we will need to create 6 (six) different ones in your Clickbank account. Then tell the SafeList script
			each Link ID Number in the List Wizard.
			<ul>
			  <li>Log into your Clickbank account.</li>
			  <li>Goto <b>Account Settings</b> Tab then <b>My Info</b> Section.</li>
			    <ol>
			      <li>Set your <b>Secret Key</b> to something random.</li>
			      <li>Save Settings...</li>
			    </ol>
			  <li>Goto <b>Account Settings</b> Tab then <b>My Products</b> Section.</li>
			  <li>You can either enter a NEW link or edit an existing one.</li>
			    <ol>
			      <li>Set <b>Thank You URL</b> to: <font color="red"><b>http://planetxmail.com/mle/processorder.php</b></font></li>
			      <li>Set the <b>Price</b></li>
			      <li>Save...</li>
			      <li>Repeat 5 (five) times for a total of 6 (six) Product Links created.</li>
			    </ol>
			</ul>
			<b>Optional:</b> To distinguish between each URL you can <i>append</i> the <b>pxm_label</b> parameter to each URL.
			<br />
			<u>Example:</u> <b><font color="green">http://planetxmail.com/mle/processorder.php?pxm_label=pro_signup</font></b>
			<br />
			<i>Do not use <b>pxm_label=cancel</b> as this is reserved for Canceled Order Return URLs.</i>
			<br /><br />
			Once your Clickbank account has 6 (six) Product URLs...
			<ul>
			  <li>Goto <b>List Wizard</b> in SafeList Admin</li>
			  <li>Enter the correct Clickbank URL Number for <u>each</u> Item.</li>
			  <li><u><b>Double Check</u> the numbers entered match your Clickbank Account Link numbers!</b></li>
			  <li>Enter the <b>Secret Key</b> you set in your Clickbank Account. <i>It is case sensitive!</i>
			  <li>Save List Wizard Settings!</li>
      </ul>
      Finally, done! Well not exactly. You should test everything out first! No matter how good you think your Data Entry skills are. To test Clickbank
      a few things need to happen.
      <ol>
        <li>In your Clickbank Account set the price for each link to test to <b>0.00</b></li>
        <li>In List Wizard set the Test Mode Username to a username you can use to test with.</li>
        <li>Once done testing, go back to Clickbank Account and set Prices to normal again.</li>
        <li>Erase Test Mode Username to make your SafeList LIVE.</li>
      </ol>
      <b>Note:</b> Setting any Products Price to 0.00 means you plan on testing it. It will not generate a transaction or care about what credit card
      number you enter while in test.
      <hr />

      <a name="alertpay"><font size="3" color="green"><b>Alertpay Setup</b></font></a> - <a href="#top">Top</a>
			<br /><br />
			Alertpay uses an IPN just like Paypal.

			<ol>
			  <li>Log into your Alerpay Account.</li>
			  <li>Goto <b>Sell Online</b> tab.</li>
			  <li>Goto <b>IPN Setup Process</b> link.</li>
			  <li><b>Enable IPN checkbox.</b></li>
			  <li>Set <b>Default Alert URL</b>: <b><font color="red">http://planetxmail.com/mle/processorder.php</font></b></li>
			  <li>Enter <b>Security Code</b> and Submit.</li>
			  <li>You will then see your <b>Encrypted Security Code</b>.</li>
		  </ol>

			<b>Note:</b> It is possible to set a different IPN URL per Email Address by clicking on <b>Advanced Options</b> Link in the IPN Setup
			section. You create additional Alertpay Email Addresses in Your Profile and Email Section. All Alert URLs will use the same Encrypted Security Code.

			<ol>
			  <li>In <b>List Wizard</b> enter your <b>Alertpay Email Account</b>.</li>
			  <li>Then enter the <b>Encrypted Security Code</b>.</li>
			</ol>

			<b>Testing Alertpay</b> is easy. In the <b>List Wizard</b> enter the </b>Test Mode Username</b>. Create another Alertpay Email Address from within
			your Alertpay Account to use as a Customer Email. You will notice Test mode in red letters on the Alertpay forms to ensure you are in
			Test mode and will not actually be charged anything. Once satisfied with the test erase the Test Mode Username to make your SafeList LIVE.
      <hr />

      <a name="testmode"><font size="3" color="green"><b>Test Mode Username Usage</b></font></a> - <a href="#top">Top</a>
			<br /><br />
			Testing your Paylinks is critical and thankfully, easy!

			<ol>
			  <li>In <b>List Wizard</b> set <b>Test Mode Username</b> to any username you want.</li>
			  <li>Enter a non-existant or pre-existing Username.</li>
			  <li>All other Users trying to load the Payforms will be given a friendly, <b>'We are in Test Mode.'</b>, message.</li>
			  <li>Being in Test Mode means <b>ALL Merchants</b> will be in this testing state.</li>
			  <li>A <font color="red"><b>red blicking, 'In Test Mode'</b></font>, message at each Payform, indicates you are the correct Test User.</li>
			  <li><u>Erase</u> the <b>Test Mode Username</b> from the List Wizard once testing is done to start taking LIVE Orders!</li>
			</ol>

			<b>Should I Enter a New or Existing Username?</b>
			If, testing the Upgrade / Renew process then using an existing Username may be the order-of-the-day.
			If, testing the Signup process then entering a non-existant username must be done so, you can sign up as a New Member would.

			<ul>
			  <li><b>Testing the Signup Process</b></li>
			    <ol>
			      <li>If you set your Default signup member to Free there is no point in testing this!</li>
			      <li>If Step 1 is not the case then signup the Test User and validate the Payforms.</li>
			      <li>If you need to test again, simply Delete the Test User Account in SafeList Admin.</li>
			      <li>Once, Account is Deleted, start again using the same Test Mode Username to signup.</li>
			    </ol>
			  <li><b>Testing the Upgrade Process</b></li>
			    <ol>
			      <li>You can use an existing User as long as you know the password for the account.</li>
			      <li>Goto the user Profile and click on the Upgrade button.</li>
			      <li>Test to make sure you get upgraded after the Test Payment.</li>
			      <li>I recommend you test a Pro and then Exec upgrade checking the Prices are correct.</li>
			      <li>If you need to start over, go into SafeList Admin and downgrade the Test User to Free.</li>
			    </ol>
			  <li><b>Testing the Renew Process</b></li>
			    <ol>
			      <li>You can use an existing User as long as you know the password for the account.</li>
			      <li>You can set the Test User as Bill is Due in the SafeList Admin.</li>
			      <li>Then log in the Test User and you should be given a Link to click to Pay the Bill.</li>
			      <li>If you need to test again, simply goto SafeList Admin, set the Test user as Bill Due.</li>
			    </ol>
			</ul>

			<b>Remember:</b> <font color="green"><b>While in test mode, no other users will be able to access the payforms. <b>Do not get in a panic
			while testing.</b> You have as much time as you need to get the job done right.</b></font>  Make sure the data in your Merchant Accounts match the
			data you have entered in your List Wizard. A common head ache is when Prices and/or Product/Link numbers get accidentally swapped with one another,
			causing a confusing situation while testing.
			<br /><br />
			<b>Along the way read the Notification Emails you may receive. Check for Spelling and Format errors.</b>
			<br /><br />
			<font color="red"><b>Once Testing is completed, goto <u>List Wizard and Erase the Test Mode Username.</u><br />
			Or, you will forever block anyone that trys to place an order.</b></font>



      <br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br />
      <br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br />
      <br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br />
			Enjoy,<br />
			<img src="http://205.252.89.252/mle/images/signature.jpg" border="0"><br />
			CEO - Matt K<br />
			<i>Planet X Mail</i> - Mailing List Services
  	</td>
  </tr>
</table>
</body>
</html>