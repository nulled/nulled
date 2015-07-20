<?php
include ("adminsecure/session/sessionsecureelpowner.inc");
include("adminsecure/memtranshistory.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Member <?=$u?> Transaction History</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table align="center" cellpadding="1" cellspacing="1" border="0" width="590">
	<tr>
		<td align="center" colspan="8"><h3>Transaction History For <?=$u?></h3></td>
	</tr>
	<tr>
		<td>
			<tr>
		    <td bgcolor="beige" align="center"><b>Username</b></td>
		    <td bgcolor="beige" align="center"><b>Trans Type</b></td>
				<td bgcolor="beige" align="center"><b>Amount Earned</b></td>
				<td bgcolor="beige" align="center"><b>Receipt</b></td>
				<td bgcolor="beige" align="center"><b>M.O.P.</b></td>
				<td bgcolor="beige" align="center"><b>Date Member Paid</b></td>
				<td bgcolor="#CCCC99" align="center"><b>Amount Owed</b></td>
				<td bgcolor="#CCCC99" align="center"><b>Paid to Elite Scripts?</b></td>
		  </tr>
		  	<?php
		  		while (list($username, $transtype, $amount, $receipt, $mop, $datepaid, $paid, $commissionowed) = mysqli_fetch_row($membertrans))
		  		{
		  			echo "<tr>\n<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$username</font></td>\n";
		  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$transtype</font></td>\n";
		  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$amount.00</font></td>\n";
		  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$receipt</font></td>\n";
		  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$mop</font></td>\n";

		  			$datepaidhuman = mysql_datetime_to_humandate($datepaid);
		  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$datepaidhuman</font></td>\n";

		  			if ($paid)
		  			{
		  				$bgcolor = "lightblue";
		  				$paid = "Yes";
		  			}
		  			else
		  			{
		  				$bgcolor = "pink";
		  				$paid = "No";
		  			}

						echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">$commissionowed.00</font></td>\n";
		  			echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">$paid</font></td>\n</tr>\n";

		  			$totalearned += $amount;
		  			$totalowed += $commissionowed;
		  		}
		  		$profits = $totalearned - $totalowed;
		  	?>
	<tr>
		<td align="right" colspan="2"><b>Total:</b></td>
		<td align="center" bgcolor="yellow"><font size="-1"><b><?="\$ $totalearned.00"?></b></font></td>
		<td align="right" colspan="3"><b>Total:</b></td>
		<td align="center" bgcolor="yellow"><font size="-1"><b><?="\$ $totalowed.00"?></b></font></td>
		<td></td>
  </tr>
  <tr>
  	<td colspan="8" align="center"><br><?="<h4>Total Profits from this Member: \$ $profits.00 USD</h4>"?></td>
  </tr>
	<tr>
	  <td colspan="8" align="center"><input type="button" class="beigebutton" value="Close Window" onClick="window.close()"></td>
	</tr>
</table>
</body>
</html>