<?php
include ("adminsecure/session/sessionsecureelpowner.inc");
include ("adminsecure/transactions.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Transactions</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table align="center" cellpadding="1" cellspacing="1" border="0" width="620">
	<tr>
		<td align="center" colspan="8">
		<h2>All Transactions</h2>
		<hr>
		<font size="+1">Today is: <b><?=date("F j, Y")?></b></font>
		<br><br>
		<input type="button" class="beigebutton" value="Back to Main" onClick="location.href='main.php'">
		<br><br>
		</td>
	</tr>
	<tr>
		<td colspan="9" align="center">
			<form name="show" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
			<select size="5" name="show" size="1" onChange="form.submit()">
				<option value="billingperiods"<?php if ($show=="billingperiods") echo " SELECTED"; ?>>Billing Periods</option>
				<option>----------------------</option>
				<option value="mempaid"<?php if ($show=="mempaid") echo " SELECTED"; ?>>Members Paid</option>
				<option value="memnotpaid"<?php if ($show=="memnotpaid") echo " SELECTED"; ?>>Members Not Paid</option>
				<option value="showallmem"<?php if ($show=="showallmem") echo " SELECTED"; ?>>All Members</option>
			</select>
			</form>
		</td>
	</tr>
  <?php
  	if ($show=="billingperiods") include ("billingperiods.php");
  	else if ($show=="showbillingperiodtrans") include ("showbillingperiodtrans.php");
  	else if ($show=="memnotpaid" || $show=="mempaid" || $show=="showallmem") include ("showmemberpaid.php");
  ?>
  <tr>
  	<td colspan="9" align="center">
  		<a href="#" onClick="window.open('policy.php',0,'height=160,width=500,status=0,toolbar=0,menubar=0,resizable=0,location=0')">Read Policy</a><br><br>
  		<input type="button" class="beigebutton" value="Back to Main" onClick="location.href='main.php'">
    </td>
  </tr>
</table>
</body>
</html>