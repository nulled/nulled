<html>
<head>
<title>Ezy-List Pro - Paypal setup</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table cellpadding="0" cellspacing="0" align="left">
	<tr>
		<td>
			<p>
			<h3>Paypal setup</h3>
			You need to log into your Paypal account, goto <b>Profile</b>, goto <b>Instant Payment Notification Preferences</b> ( under
			the Selling Preferences section ) and Edit your IPN URL.. and turn it ON.
			<br><br>
			Set the IPN URL to: <b>http://www.planetxmail.com/proctrans/pp_proctrans.php</b>
			<br><br>
			Be sure to turn it ON as well.
			<br><br>
			Finally, set your PRIMARY Paypal account email in ELP Config.
			<br><br>
			<font color="red"><b>Important!!!</b></font>  You must set your ELP Config Paypal address to the PRIMARY!!!  You are allowed to have Multiple address in your Paypal
			configurations BUT ELP MUST be set to use the PRIMARY or your transactons will fail!!!
			<br><br>
			Now, everytime someone buys something this script is ran and we use it to verify transactions and auto update member accounts
			so you dont have to.  If you want to use the Paypal option you MUST set the IPN.
			<br><br>
			Also, note that if you have other <b>NON-ELP</b> payments going to this Paypal account that <b>this is <i>NOT</i> a problem</b>.  ELP knows to
			not process any transactions that are NON-ELP specific.  Your NON-ELP transactions to this Paypal account are <b>uneffected</b>.
			</p>
  	</td>
  </tr>
</table>
</body>
</html>