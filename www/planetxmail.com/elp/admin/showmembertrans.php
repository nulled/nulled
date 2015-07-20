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

				echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">\$ $commissionowed.00</font></td>\n";
  			echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\">$paid</font></td>\n</tr>\n";
  		}
  	?>