<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/viewtransactions.inc");
?>
<html>
<head>
<title>View Billing Transactions</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table align="center" width="700" cellspacing="1" cellpadding="1" border="0">
	<tr>
		<td colspan="15" align="center">
			<h3>Transaction History</h3>
		</td>
	</tr>
	<tr>
		<td bgcolor=lightblue><b>User&nbsp;Name</b></td><td bgcolor=lightblue><b>Product</b></td><td bgcolor=lightblue><b>Amount</b></td><td bgcolor=lightblue><b>Commission</b></td><td bgcolor=lightblue><b>Commission&nbsp;Paid?</b></td><td bgcolor=lightblue><b>M.O.P.</b></td><td bgcolor=lightblue><b>Receipt</b></td><td bgcolor=lightblue><b>Date&nbsp;of&nbsp;Sale</b></td>
	</tr>
	<?php
		$i=0;
		while (list($userID, $product, $amount, $commissionamount, $commissionpaid, $mop, $receipt, $dateofsale) = mysqli_fetch_row($transactions))
		{
			$db->Query("SELECT username FROM users WHERE userID='$userID'");
			list($username) = $db->FetchRow();

			$parts = preg_split("/[: ]/", $dateofsale);
			$dateofsale = "$parts[0]&nbsp;$parts[1]:$parts[2]";

			if ($i%2==0)
	      $bgcolor = "F4F4F7";
	    else
	      $bgcolor = "E9E9E9";

			if ($commissionamount > 0)
			{
				if ($commissionpaid) $commissionpaid = "Yes";
				else
					$commissionpaid = "No";
			}
			else
				$commissionpaid = "N/A";

			echo "<tr><td bgcolor=$bgcolor>$username</td><td bgcolor=$bgcolor>$product</td><td bgcolor=$bgcolor>$amount</td><td bgcolor=$bgcolor>$commissionamount</td><td align=center bgcolor=$bgcolor>$commissionpaid</td><td bgcolor=$bgcolor>$mop</td><td bgcolor=$bgcolor>$receipt</td><td bgcolor=$bgcolor>$dateofsale</td></tr>\n";

			$i++;
		}
	?>
	<tr>
		<td colspan="15" align="center">
			<br><hr>
			<input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
		</td>
	</tr>
</table>
</body>
</html>

