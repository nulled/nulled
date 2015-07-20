<html>
<head>
<title>Ezy-List Pro - ELP Owner Paylinks</title>
<link rel="stylesheet" type="text/css" href="css_elp.css" />
<script language="javascript">
<!--
if (self != top) top.location.href = window.location.href;
//-->
</script>
</head>
<body>
<table width="513" align="center">
	<tr>
		<td>
			<center><img src="images/elplogo.jpg"></center>
			<hr>
			<?php
				include("elpsecure/elpownerpaylinks.inc");
				if ($good)
				{
					echo "<p><b>$fname $lname,</b><br>\n";
					echo "Your Bi-Weekly Bill is due for your Ezy-List Pro Partnership.\n";
					echo "<br><br>\n";
					echo "Amount Owed: <b>\$ $amountowed USD</b>\n";
					echo "<br><br>\n";
					echo "Billing Period Ending: <b>$billingdate</b><br>\n";
					echo "Transaction ID: <b>$id</b>\n";
					echo "<br><br>\n";
					echo "Please review the Email we sent and/or the ELP Admin Control area for details on every transaction billed.\n";
					echo "<br>\n";
					echo "<h3>Choose from the payment options below.</h3></p>\n";
					echo "$billpaylinks\n";
				}
			?>
		</td>
	</tr>
</table>
</body>
</html>