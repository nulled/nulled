	<tr>
    <td bgcolor="beige" align="center"><b>Username</b></td>
    <td bgcolor="beige" align="center"><b>First Name</b></td>
		<td bgcolor="beige" align="center"><b>Last Name</b></td>
		<td bgcolor="beige" align="center"><b>Status</b></td>
  </tr>
  	<?php
  		while (list($username, $fname, $lname, $paid) = mysqli_fetch_row($membertrans))
  		{
  			echo "<tr>\n<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\"><a href=\"showmember.php?elpmember=$username&fromtrans=$show\">$username</a></font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$fname</font></td>\n";
  			echo "<td bgcolor=\"lightblue\" align=\"center\"><font size=\"-1\">$lname</font></td>\n";

  			if ($paid)
  			{
  				$bgcolor = "lightblue";
  				$status = "Paid";
  			}
  			else
  			{
  				$bgcolor = "pink";
  				$status = "Not Paid";
  			}

  			echo "<td bgcolor=\"$bgcolor\" align=\"center\"><font size=\"-1\"><a href=\"#\" onClick=\"window.open('memtranshistory.php?u=$username&o=$_SESSION[aaelp]ownername',0,'height=300,width=630,status=0,toolbar=0,menubar=0,resizable=1,scrollbars=1,location=0')\">$status</a></font></td>\n";
  		}
  	?>