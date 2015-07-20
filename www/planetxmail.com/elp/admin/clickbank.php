<html>
<head>
<title>Ezy-List Pro - ClickBank setup</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table cellpadding="0" cellspacing="0" align="left">
	<tr>
		<td>
			<p>
			<h3>ClickBank setup</h3>
			Log into your ClickBank account. Goto <b>modify your account</b> (twice).  In the <b>Thank-you pages</b> section pick TWO links.<br><br>
			Set one to: <b>http://www.planetxmail.com/elp/mempaidsignupthankyou.php</b>
			<br><br>
			And the other: <b>http://www.planetxmail.com/elp/memmonthlythankyou.php</b>
			<br><br>
			The first link is the sign up return URL on payment success.  The second link is the monthly payment re-newal URL thank you page.
			<br><br>
			Still in ClickBank set the price for the <b>Sign up</b> link to be the Sign-up fee PLUS first Months fee.  ( Ex: signup $47 + first months $20 = $67 )
			$67 is the price you set for your ClickBank sign-up link.
			<br><br>
			Then set the <b>Monthly Re-Newal</b> link fee to what you want to charge per month.
			<br><br>
			Now at the bottom of the Click Bank account page enter in the CGI Validation key ( a random alpha-numeric key of your choice. )
			<br><br>
			Now in your ELP Configuration set the proper link numbers corrisponding to what you just set in Clickbank.  The link number and price. And your GCI Secret Key
			is entered the SAME in both your click bank account AND in ELP config! <i>Make certain</i> that ELP Config and ClickBank Config match-up!!!
			<br><br>
			Finally, in ELP Config, set your ClickBank username.
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