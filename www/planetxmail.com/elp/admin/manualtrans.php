<?php
include ("adminsecure/session/sessionsecureelpowner.inc");
include ("adminsecure/manualtrans.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Generate a Manual Transaction</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
<script language="javascript">
<!--
var price = <?=$price?> + <?=$monthlyprice?>;
var monthlyprice = <?=$monthlyprice?>;

function setAmount()
{
	if (document.transaction.transtype[0].checked) document.transaction.amount.value = price;
	if (document.transaction.transtype[1].checked) document.transaction.amount.value = monthlyprice;
}
//-->
</script>
</head>
<body<?php if ($memtype=="pro") echo " onLoad='setAmount()'";?>>
<table align="center" cellpadding="1" cellspacing="1" border="0" width="450">
	<tr>
		<td colspan="2" align="center">
			<font size="+1"><b>Generate a Manual Transaction for: </b><font color="red"><?=$elpmember?></font></b></font>
			<hr>
			<font color="red"><b><?=$notValid?></b></font>
			<form name="transaction" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
		</td>
	</tr>
	<?php
	  if ($memtype=="pro")
	  {
    	echo "<tr>\n";
    	echo "	<td colspan=\"2\" align=\"center\"><b>Transaction Type:</b></td>\n";
    	echo "</tr>\n";
    	echo "<tr>\n";
    	echo "	<td align=\"right\" bgcolor=\"beige\">\n";
    	echo "		<input type=\"radio\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"transtype\" value=\"signup\" onClick='setAmount()'";
    	if ($transtype=="signup" || ! $transtype)
    	  echo " CHECKED";
    	echo ">\n";
    	echo "	</td>\n";
    	echo "	<td bgcolor=\"beige\">&nbsp;<b>Sign-up</b></td>\n";
    	echo "</tr>\n";
    	echo "<tr>\n";
		  echo "  <td align=\"right\" bgcolor=\"beige\">\n";
			echo "    <input type=\"radio\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"transtype\" value=\"monthly\" onClick='setAmount()'";
			if ($transtype=="monthly")
			  echo "CHECKED";
			echo ">\n";
		  echo "  </td>\n";
		  echo "  <td bgcolor=\"beige\">&nbsp;<b>Monthly</b></td>\n";
	    echo "</tr>\n";
    }
    else if ($memtype=="lite")
    {
      echo "<tr>\n";
    	echo "	<td bgcolor=\"beige\" align=\"right\"><b>Member Type:</b></td>\n";
    	echo "	<td bgcolor=\"beige\">\n";
    	echo "		<input type=\"text\" value=\"lite\" READONLY>\n";
    	echo "	</td>\n";
    	echo "</tr>\n";
    }
  ?>
	<tr>
		<td colspan="2" align="center"><br><br><b>Method of Payment:</b></td>
	</tr>
	<tr>
		<td align="right" bgcolor="lightblue">
			<input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="Paypal" <?php if ($mop=="Paypal" || $mop=="") echo "CHECKED"; ?>>
		</td>
		<td bgcolor="lightblue">&nbsp;<b>Paypal</b></td>
	</tr>
	<tr>
		<td align="right" bgcolor="lightblue">
			<input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="e-gold" <?php if ($mop=="e-gold") echo "CHECKED"; ?>>
		</td>
		<td bgcolor="lightblue">&nbsp;<b>E-gold</b></td>
	</tr>
	<tr>
		<td align="right" bgcolor="lightblue">
			<input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="ClickBank" <?php if ($mop=="ClickBank") echo "CHECKED"; ?>>
		</td>
		<td bgcolor="lightblue">&nbsp;<b>ClickBank</b></td>
	</tr>
	<tr>
		<td align="right" bgcolor="lightblue">
			<input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="mop" value="Other" <?php if ($mop=="Other" || $mop=="") echo "CHECKED"; ?>>
		</td>
		<td bgcolor="lightblue">&nbsp;<b>Other</b></td>
	</tr>
	<tr>
		<td align="right"><br><b>Receipt:</b></td>
		<td>
			<br><input type="text" name="receipt" value="<?=$receipt?>" size="22">
		</td>
	</tr>
	<tr>
		<td align="right"><br><b>Amount Paid: $</b></td>
		<td>
			<br><input type="text" name="amount" value="<?=$amount?>" size="3" READONLY>
		</td>
	</tr>
	<?php
	  if ($memtype=="pro")
	  {
    	echo "<tr>\n";
    	echo "	<td colspan=\"2\">\n";
    	echo "		<hr><br>\n";
    	echo "		Manually generating a transaction will allow the new member to log into their account and will generate a transaction for your bi-weekly bill.  Or";
    	echo "    use this to manually add a transaction that did not get activated. Or if you run an affilaite system you use this to manually enter your sales to create useable member accounts.";
    	echo "		<br><br>\n";
    	echo "    And a billing transaction will be generated which will appear in your Bi-Weekly Billing reports we generate for you.\n";
    	echo "		Please, email me at: <b>accounts@planetxmail.com</b> for help on how to correctly set up your paylinks.\n";
    	echo "	</td>\n";
    	echo "</tr>\n";
   }
   else if ($memtype=="lite")
   {
      echo "<tr>\n";
    	echo "	<td colspan=\"2\">\n";
    	echo "		<hr><br>\n";
    	echo "		Only use this once your Ezy-List LITE member has paid you. Once you generate this transaction this member will be allowed to Activate Ezy-List LITE\n";
    	echo "    And a billing transaction will be generated which will appear in your Bi-Weekly Billing reports we generate for you.\n";
    	echo "		Please, email me at: <b>accounts@planetxmail.com</b> for additional help.\n";
    	echo "	</td>\n";
    	echo "</tr>\n";
   }
  ?>
	<tr>
		<td colspan="2">
			<br>
			<hr>
			<input type="hidden" name="elpmember" value="<?=$elpmember?>">
			<input type="hidden" name="memtype" value="<?=$memtype?>">
			<input type="hidden" name="submitted" value="generate">
			<input type="submit" class="greenbutton" value="Generate">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<input type="button" class="redbutton" value="Cancel" onClick="location.href='showmember.php?elpmember=<?=$elpmember?>'">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<input type="button" class="beigebutton" value="Back to Main Menu" onClick="javascript:location.href='main.php'">
			</form>
		</td>
	</tr>
</table>
</body>
</html>