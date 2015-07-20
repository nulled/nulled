<html>
<head>
<title>Ezy-List LITE - ClickBank setup</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table cellpadding="0" cellspacing="0" align="left">
	<tr>
		<td>
			<p>
			<h3>ClickBank setup for LITE members</h3>
			Log into your ClickBank account. Goto <b>modify your account</b>.  In the <b>Thank-you pages</b> section pick a link.<br><br>
			Set it to: <b>http://www.planetxmail.com/elp/mempaidsignuplitethankyou.php</b>
			<br><br>
			The first link is the sign up return URL on payment success.  The second link is the monthly payment re-newal URL thank you page.
			<br><br>
			Still in ClickBank set the price for the <b>LITE Sign up</b> link to be the LITE Sign-up fee.
			<br><br>
			Now in your ELP Configuration set the proper link numbers corrisponding to what you just set in Clickbank.  The link number and price.
			<i>Make certain</i> that ELP Config and ClickBank Config match-up!!!
			<br><br>
			Now at the bottom of the Click Bank account page enter in the CGI Validation key ( a random alpha-numeric key of your choice. )
			<br><br>
			Finally, in ELP Config, set your ClickBank username. (Which is set in the TOP ClickBank Link used for PRO signups.)
			<br><br>
			<b>Special Note:</b> ClickBank does not allow <i>instant</i> transaction verification like Paypal and e-gold.  Meaning that in order for
			Elite Scripts servers to know a member pays is by waiting until they click continue until they get to <b>OUR</b> thank you pages.  At
			which time they are automatically recorded as paid by our systems.  <i>Unfortunety, sometimes once a member pays they close the browser
			or surf on to another location before closing the sale completely.  This means they paid and you got an email notice, but the ELP
			systems didnt record it.  We have posted a notice by the Click Bank link that they will see if they choose ClickBank as a method of payment.
			But, if they do mess up or forget to close the sale completely, you can go into their profile section in ELP Admin and use the
			<b>Generate Transaction</b> button that will record them as paid and allow them to log into ELP.
			</p>
  	</td>
  </tr>
</table>
</body>
</html>