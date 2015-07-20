<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/manualtrans.inc");
?>
<html>
<head>
<title>Generate Manual Transaction</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script>
<!--
function load(s)
{
	if (s=='pro' || s=='exe')
	{
		document.manualtrans.transtype[0].disabled=1;
		document.manualtrans.transtype[1].disabled=1;
	}
}
//-->
</script>
</head>
<body onLoad="load('<?=$s?>')">
<table bgcolor="#FFFFFF" border="0" width="400" cellspacing="1" cellpadding="1" align="center">
	<tr>
		<td colspan="2" align="center">
			<h3>Generate a Manual Transaction</h3>
			This will simply add a Transaction to your <b>Main Options->View Transactions</b> List for your records.
			<hr>
			<?php if ($notValid) echo "<b class=red>$notValid</b><br>\n"; ?>
			<form name="manualtrans" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
		</td>
	</tr>
	<tr>
		<td colspan="2" align="center" bgcolor="lightblue"><b>Type of Transaction</b></td>
	</tr>
	<tr>
		<td bgcolor="lightblue" align="right"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="transtype" value="signup"<?php if ($transtype=="signup" || ! $transtype) echo " CHECKED"; ?>></td>
		<td bgcolor="lightblue">Sign up</td>
	</tr>
	<tr>
		<td bgcolor="lightblue" align="right"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="transtype" value="renewal"<?php if ($transtype=="renewal") echo " CHECKED"; ?>></td>
		<td bgcolor="lightblue">Renewal</td>
	</tr>
	<tr>
		<td bgcolor="lightblue" align="right"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="transtype" value="upgrade"<?php if ($transtype=="upgrade") echo " CHECKED"; ?>>
		<td bgcolor="lightblue">Upgrade</td>
	</tr>
	<tr>
		<td colspan="2"><br></b></td>
	</tr>
	<tr>
		<td align="right">Amount Paid: </td>
		<td><input type="text" name="amount" value="<?=$amount?>" size="10"></td>
	</tr>
	<tr>
		<td colspan="2"><br></b></td>
	</tr>
	<tr>
		<td colspan="2" align="center" bgcolor="beige"><b>Method of Payment (M.O.P.)</b></td>
	</tr>
	<tr>
		<td bgcolor="beige" align="right"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="paypal"<?php if ($mop=="paypal" || ! $mop) echo " CHECKED"; ?>></td>
		<td bgcolor="beige">Paypal</td>
	</tr>
	<tr>
		<td bgcolor="beige" align="right"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="egold"<?php if ($mop=="egold") echo " CHECKED"; ?>></td>
		<td bgcolor="beige">e-gold</td>
	</tr>
	<tr>
		<td bgcolor="beige" align="right"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="clickbank"<?php if ($mop=="clickbank") echo " CHECKED"; ?>></td>
		<td bgcolor="beige">ClickBank</td>
	</tr>
	<tr>
		<td bgcolor="beige" align="right"><input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="other"<?php if ($mop=="other") echo " CHECKED"; ?>></td>
		<td bgcolor="beige">Other</td>
	</tr>
	<tr>
		<td colspan="2"><br></b></td>
	</tr>
	<tr>
		<td align="right">Order Receipt/Number: </td>
		<td><input type="text" name="receipt" value="<?=$receipt?>" size="25"></td>
	</tr>
	<tr>
		<td colspan="2" align="center">
			<br>
			<input type="submit" value="Submit Transaction">
			<input type="hidden" name="submitted" value="generate">
			<input type="hidden" name="s" value="<?=$s?>">
			<input type="hidden" name="u" value="<?=$u?>">
			</form>
		</td>
	</tr>
	<tr>
		<td colspan="2" align="center">
			<input type="button" value="Cancel Back to Main" class="beigebutton" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
			<br><br>
			<input type="button" value="Cancel Back to Members Profile" class="redbutton" onClick="location.href='showmember.php?user=<?=$u?>'">
		</td>
	</tr>
	</table>
</body>
</html>