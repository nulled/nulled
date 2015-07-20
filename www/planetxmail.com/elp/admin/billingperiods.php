	<tr>
		<td colspan="7" align="center">
			<a href="#" onClick="window.open('billinghelp.php',0,'height=180,width=500,status=0,toolbar=0,menubar=0,resizable=0,location=0')">Billing Periods Described</a><br><br>
		</td>
	</tr>
	<tr>
		<td bgcolor="beige" align="center"><b>Trans ID</b></td>
    <td bgcolor="beige" align="center"><b>Billing Period Ending</b></td>
		<td bgcolor="beige" align="center"><b>Earnings</b></td>
		<td bgcolor="beige" align="center"><b>Owed</b></td>
		<td bgcolor="beige" align="center"><b>Profits</b></td>
		<td bgcolor="#CCCC99" align="center"><b>Paid to Elite Scripts?</b></td>
		<td bgcolor="#CCCC99" align="center"><b>Date Paid</b></td>
  </tr>
  	<?php
  		while (list($id, $amountowned, $totalearned, $paid, $dateowed, $datepaid, $bypassed) = mysqli_fetch_row($billingperiods))
  		{
  			$profits = $totalearned - $amountowned;
  			$dateowed = mysql_datetime_to_humandate($dateowed);
  			$datepaidhuman = mysql_datetime_to_humandate($datepaid);

  			echo "<tr>\n<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\"><a href=\"$_SERVER[PHP_SELF]?show=showbillingperiodtrans&id=$id\">$id</a></font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\"><a href=\"$_SERVER[PHP_SELF]?show=showbillingperiodtrans&id=$id\">$dateowed</a></font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$totalearned.00</font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$amountowned.00</font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$profits.00</font></td>\n";

  			if ($paid)
  			{
  				$bgcolor = "lightblue";
  				$paid = "Yes";
  			}
  			else
  			{
  				$bgcolor = "pink";
  				$paid = "No";
  				$datepaid = "Payment DUE";
  			}

  			if ($bypassed)
  			{
  				$bgcolor = "lightgrey";
  				$paid = "No - Merged with next Period";
  				$datepaid = "OVER DUE";
  				$datepaidhuman = "-";
  			}

  			echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">$paid</font></td>\n";

  			if ($paid=="No")
  				echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\"><a href=\"http://www.planetxmail.com/elp/elpownerpaylinks.php?id=$id&o=$_SESSION[aaelp]ownername\" target=\"_blank\">$datepaid</a></font></td>\n</tr>\n";
  			else if (! $bypassed)
  				echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">$datepaidhuman</font></td>\n</tr>\n";
  			else if ($bypassed && ! $paid)
					echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">$datepaid</font></td>\n</tr>\n";
				else
					echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">$datepaidhuman</font></td>\n</tr>\n";

				if (! stristr($paid, "No - Merged"))
				{
	  			$totaltheyearned += $totalearned;
	  			$totalowed += $amountowned;
	  			$totaltheyprofitted += $profits;
	  		}
  		}
  	?>
  <tr>
		<td align="right" colspan="2"><b>Totals:</b></td>
		<td align="center" bgcolor="yellow"><font size="-1"><b><?="\$ $totaltheyearned.00"?></b></font></td>
		<td align="center" bgcolor="yellow"><font size="-1"><b><?="\$ $totalowed.00"?></b></font></td>
		<td align="center" bgcolor="yellow"><font size="-1"><b><?="\$ $totaltheyprofitted.00"?></b></font></td>
		<td></td>
		<td></td>
  </tr>
  <tr>
  	<td colspan="7" align="center"><br><?="<h3>Total Profits to Date: \$ $totaltheyprofitted.00 USD</h3>"?></td>
  </tr>