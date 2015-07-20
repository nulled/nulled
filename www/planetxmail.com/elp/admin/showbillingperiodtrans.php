	<tr>
		<td colspan="8" align="center">
			<b>Billing Period Ending: <font size="+1"><?php $dateowed = mysql_datetime_to_humandate($dateowed); echo $dateowed; ?></font></b><br>
			<b>Period Transaction ID: <font size="+1"><?=$billingperiodid?></font></b><br>
			<?php if ($periodbypassed) echo "<br><font color=\"red\"><b>Note:</b> This Billing Period was merged with the next one because you missed the payment due date.</font>\n"; ?>
			<br><br>
		</td>
	</tr>
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
  		for ($i=0; $i<count($username); $i++)
  		{
  			echo "<tr>\n<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\"><a href=\"#\" onClick=\"window.open('memtranshistory.php?u=$username[$i]&o=$_SESSION[aaelp]ownername',0,'height=300,width=630,status=0,toolbar=0,menubar=0,resizable=1,scrollbars=1,location=0')\">$username[$i]</a></font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$transtype[$i]</font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$amount[$i].00</font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$receipt[$i]</font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$mop[$i]</font></td>\n";

  			$datepaidhuman = mysql_datetime_to_humandate($datepaid[$i]);
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$datepaidhuman</font></td>\n";

  			if ($paid[$i])
  			{
  				$bgcolor = "lightblue";
  				$answer = "Yes";
  			}
  			else
  			{
  				$bgcolor = "pink";
  				$answer = "No";
  			}

				echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">$commissionowed[$i].00</font></td>\n";
  			echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">$answer</font></td>\n</tr>\n";

  			$totalearned += $amount[$i];
  			$totalowed += $commissionowed[$i];
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
  	<td colspan="8" align="center">
	  	<br><?="<h3>Total Profits: \$ $profits.00 USD</h3>"?><br>
	  	<input type="button" class="greenbutton" value="Back to Billing Periods" onClick="location.href='<?="$_SERVER[PHP_SELF]?show=billingperiods"?>'">
	  	<br><br>
  	</td>
  </tr>