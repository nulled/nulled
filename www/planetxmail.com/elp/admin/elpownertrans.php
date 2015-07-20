<?php
include ("adminsecure/session/sessionsecureelpowner.inc");
include ("adminsecure/elpownertrans.inc");
?>
<html>
<head>
<title>Ezy-List Pro - ELP Owner Transactions</title>
</head>
<body>
<table align="center" cellpadding="1" cellspacing="3" border="0" width="500">
	<tr>
		<td align="center" colspan="3"><h2>ELP Owner Transactions</h2></td>
	</tr>
  <tr>
		<td bgcolor="beige" align="center"><b>Amount USD</b></td>
		<td bgcolor="beige" align="center"><b>Receipt</b></td>
		<td bgcolor="beige" align="center"><b>Date Paid</b></td>
  </tr>
  <tr>
  	<?php
  		while (list($amount, $receipt, $datepaid) = mysqli_fetch_row($elpownertrans))
  		{
  			echo "<td bgcolor=\"lightblue\" align=\"center\">$amount</td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\">$receipt</td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\">$datepaid</td>\n";
  		}
  	?>
  </tr>
  <tr>
  	<td colspan="4" align="center"><br><br><input type="button" value="Back to Main" onClick="location.href='main.php'"></td>
  </tr>
</table>
</body>
</html>