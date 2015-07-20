<?php
include("phpsecure/lists4sale.inc");
?>
<html>
<head>
<title>Planet X Mail Safelists 4 Sales</title>
<link rel="stylesheet" type="text/css" href="x.css" />
</head>
<body>
<table align="center" width="700">
	<tr>
		<td>
			<center>
			<img src="../mle/images/pxm_title.jpg" border="0">
			<hr>
			<h3>Pre-Owned SafeLists 4 Sale!</h3>
			</center>
			These Safelists 4 sale are <u>Premium Planet X Mail Safelists</u>! They were abandoned by their previous List Owners.
			Meaning they did not continue to pay their List subscription.
			<br><br>
			<i>Now</i> is YOUR chance to become a <b>List Owner</b> YOURSELF <i>starting with a Safelist that has members already loaded!</i>
			These Safelists were not deleted because I do not think it is fair to simply delete a list where people have potentially paid a
			fee to join.  So, passing it on to a NEW OWNER ( YOU ) is only fair, in my book.
			<br><br>
			<li><b>Active member</b> means they have a Contact and List Address set.</li>
			<li><b>InActive member</b> means they have their Contact Address set but not the List Address.</li>
			<br><br>
			Below is a list of Safelists we have that are ready for a <i>New Owner</i> ( YOU ) !
			Make one YOUR own today! INSTANTLY obtain HUNDREDS OF LEADS!
			<br><br>
			Remember, once purchased, you will get FULL CONTROL of the List.  You BUY the rights to run the Safelist from
			our servers. Change the name, title graphic, headers etc!
			<br><br>
			Also, many List Owners that ran these lists spent a lot of money to advertise on the web.  Now YOU can take the
			list name which is already promoted on the same level!
			<br><br>
			<i>All Planet X Mail Safelists are <b>PACKED</b> with List Admin features!!!</i>
			<ul>
				<li>Built-in Admin mailer to all members.</li>
				<li>Banner rotator.  Unlimited Banner uploads.</li>
				<li>One-of-a-Kind Bill Board AD system. Seen by all members of the Safelist.</li>
				<li>Member status control. User account management.</li>
				<li>Three status levels: Free, Pro, Executive.</li>
				<li>Home page edit system per status level.</li>
				<li>Integrated Paylink system.</li>
				<li>Built-in Affilaite system.</li>
				<li>AD system for designing the page members see after they mail.</li>
				<li>and much MUCH more.</li>
			</ul>
			To fully experience a <i>Planet X Mail Safelist</i> and what it has to offer, we suggest you try a
			<a href="http://www.planetxmail.com/mle/admin/indexlistowner.php?username=demoit&password=222222" target="_BLANK">Fully Functional Demo</a>
			before buying!
			<ul>
				<li>User Name: demoit</li>
				<li>Password: 222222</li>
			</ul>
			<center><h2>SafeLists 4 Sale</h2></center>
		</td>
	</tr>
	<tr>
		<td>
			<table align="center" cellpadding="2" cellspacing="0" style="border-collapse: collapse" bordercolor="#000000" border="1">
				<tr>
					<td></td>
					<td colspan="4" align="center">
						<font size="+1">Members</font><br><font size="1">Free, Professional and Executive</font>
					</td>
					<td></td>
				</tr>
				<tr>
					<td bgcolor="lightblue"><center>* List Name</center></td>
					<td bgcolor="lightblue">Active <b>Free</b> / InActive <b>Free</b></td>
					<td bgcolor="lightblue">Active <b>Pro</b> / InActive <b>Pro</b></td>
					<td bgcolor="lightblue">Active <b>Exec</b> / InActive <b>Exec</b></td>
					<td bgcolor="lightblue"><b>Total</b> Active / InActive</td>
					<td bgcolor="lightblue">**&nbsp;$&nbsp;Price</td>
					<td bgcolor="lightblue"></td>
				</tr>
				<?php
					for ($i=0; $i<count($listnames); $i++)
					{
						if ($i%2)
							$bgcolor = "#FFFFFF";
						else
							$bgcolor = "#EFEEEA";

						echo "<tr><td bgcolor=\"$bgcolor\">$listnames[$i]</td>\n";
						echo "<td bgcolor=\"$bgcolor\">$nummemactive[$i] / $nummeminactive[$i]</td>\n";
						echo "<td bgcolor=\"$bgcolor\">$numproactive[$i] / $numproinactive[$i]</td>\n";
						echo "<td bgcolor=\"$bgcolor\">$numexeactive[$i] / $numexeinactive[$i]</td>\n";
						echo "<td bgcolor=\"$bgcolor\">$totalmemactive[$i] / $totalmeminactive[$i]</td>\n";
						echo "<td bgcolor=\"$bgcolor\" align=\"right\">$price[$i].00</td>\n";
						echo "<td bgcolor=\"$bgcolor\"><a href=\"$_SERVER[PHP_SELF]?id=$listids[$i]&submitted=buylist\" target=\"_BLANK\">Buy&nbsp;It!</a></td></tr>\n";
					}

					if (! count($listnames))
						echo "<tr><td colspan=\"7\"><br><center>All Lists are currently SOLD OUT!  Try back again later!</center><br></td></tr>";
				?>
				</td>
			</tr>
		</table>
	</td>
	</tr>
	<tr>
		<td>
			<br>
			<font size="-2">
			<b>*</b> List Name can be changed at any time once you purchase the List.
			<br>
			<b>**</b> Price includes 1 month hosting.  After 1 month cost is $30 / month per list for no less than 3 months.
			<br>
			<b>- </b><b>Active member</b> means they have a Contact and List Address set.
			<br>
			<b>- </b><b>InActive member</b> means they have their Contact Address set but not the List Address.
			</font>
		</td>
	</tr>
	<tr>
    <td align="center" valign="top">
      <hr>
      <font size="-1">All Rights Reserved &copy;2001-<?php echo date("Y"); ?><br>Multi-List Enterprise - Planet X Mail<br>
      Contact: <a href="openticket.php">Planet X Mail Support</a></font>
    </td>
  </tr>
</table>
</body>
</html>