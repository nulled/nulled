<?php
include("adminsecure/session/sessionsecureelpowner.inc");
include("adminsecure/editconfig.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Edit Configurations</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table  cellpadding="0" cellspacing="0" align="center" border="1">
  <tr>
    <td>
      <table width="600" cellpadding="1" cellspacing="1" align="center" border="0">
        <tr>
          <td colspan="2" align="center">
          	<h4>Your ELP Configurations</h4><hr>
          	<font color="red"><?="<b>$notValid</b>"?></font>
          	<form name="saveconfig" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
          </td>
        </tr>
        <tr>
          <td colspan="2" align="center">
            <h3>Pro Members</h3>
          </td>
        </tr>
        <tr>
          <td bgcolor="beige" align="right">Price for each <b>Sign up</b>: $</td>
          <td bgcolor="beige"><input type="text" name="price" value="<?=$price?>" size="3"></td>
        </tr>
        <tr>
	        <td bgcolor="beige" align="right">Owed to Elite Scripts for each <b>Sign up</b>: $</td>
	        <td bgcolor="beige"><input type="text" name="commission" value="<?=$commission?>" size="3" <?php if (! $_SESSION['aaadminpsk']) echo "READONLY"; ?>>&nbsp;Set by Elite Scripts</td>
        </tr>
		    <tr>
          <td align="right">Price for each <b>Monthly</b>: $</td>
          <td><input type="text" name="monthlyprice" value="<?=$monthlyprice?>" size="3"></td>
        </tr>
        <tr>
		      <td align="right">Owed to Elite Scripts for each <b>Monthly</b>: $</td>
		      <td><input type="text" name="monthlycommission" value="<?=$monthlycommission?>" size="3" <?php if (! $_SESSION['aaadminpsk']) echo "READONLY"; ?>>&nbsp;Set by Elite Scripts</td>
        </tr>
        <tr>
        	<td bgcolor="beige" align="right">Your <b>Contact/Billing Email</b>: </td>
        	<td bgcolor="beige"><input type="text" name="email" value="<?=$email?>" size="40"></td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td align="right" bgcolor="lightblue"><a href="#" onClick="window.open('clickbank.php',0,'height=600,width=590,status=0,toolbar=0,menubar=0,resizable=0,location=0,scrollbars=1')">Instructions</a>&nbsp;&nbsp;&nbsp;&nbsp;Use <b>ClickBank</b>?&nbsp;<input type="checkbox" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="useclickbank" value="1" <?php if ($useclickbank) echo "CHECKED"; ?>></td>
          <td bgcolor="lightblue">
          	ClickBank Account <b>Username</b>:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="text" name="clickbankaccount" value="<?=$clickbankaccount?>" size="13"><br>
          	ClickBank <b>CGI Key</b>:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="text" name="clickbankkey" value="<?=$clickbankkey?>" size="13"><br>
          	ClickBank Link Number for <b>Sign up</b>:&nbsp;&nbsp;<input type="text" name="clickbanklinknumbersignup" value="<?=$clickbanklinknumbersignup?>" size="2"><br>
          	ClickBank Link number for <b>Monthly</b>:&nbsp;&nbsp;<input type="text" name="clickbanklinknumbermonthly" value="<?=$clickbanklinknumbermonthly?>" size="2"></td>
        </tr>
        <tr>
          <td bgcolor="beige" align="right"><a href="#" onClick="window.open('paypal.php',0,'height=350,width=550,status=0,toolbar=0,menubar=0,resizable=0,location=0,scrollbars=1')">Instructions</a>&nbsp;&nbsp;&nbsp;&nbsp;Use <b>Paypal</b>?&nbsp;<input type="checkbox" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="usepaypal" value="1" <?php if ($usepaypal) echo "CHECKED"; ?>></td>
          <td bgcolor="beige">
          	Paypal Account <b>Email</b>:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="text" name="paypalaccount" value="<?=$paypalaccount?>" size="23">
          </td>
        </tr>
        <tr>
          <td bgcolor="pink" align="right"><a href="#" onClick="window.open('egold.php',0,'height=250,width=600,status=0,toolbar=0,menubar=0,resizable=0,location=0,scrollbars=1')">Instructions</a>&nbsp;&nbsp;&nbsp;&nbsp;Use <b>E-Gold</b>?&nbsp;<input type="checkbox" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="useegold" value="1" <?php if ($useegold) echo "CHECKED"; ?>></td>
          <td bgcolor="pink">
          	E-Gold Account <b>Number</b>:&nbsp;&nbsp;<input type="text" name="egoldaccount" value="<?=$egoldaccount?>" size="23"><br>
          	E-Gold Alternate <b>Phrase</b>:&nbsp;&nbsp;<input type="text" name="egoldaltphrase" value="<?=$egoldaltphrase?>" size="23">
          </td>
        </tr>
        <tr>
          <td colspan="2" align="center">
            <br><br>
            <h3>LITE Members</h3>
          </td>
        </tr>
        <tr>
          <td bgcolor="beige" align="right">Price for each <b>LITE Sign up</b>: $</td>
          <td bgcolor="beige"><input type="text" name="pricelite" value="<?=$pricelite?>" size="3"></td>
        </tr>
        <tr>
	        <td bgcolor="beige" align="right">Owed to Elite Scripts for each <b>LITE Sign up</b>: $</td>
	        <td bgcolor="beige"><input type="text" name="commissionlite" value="<?=$commissionlite?>" size="3" <?php if (! $_SESSION['aaadminpsk']) echo "READONLY"; ?>>&nbsp;Set by Elite Scripts</td>
        </tr>
        <tr>
          <td align="right" bgcolor="lightblue"><a href="#" onClick="window.open('clickbanklite.php',0,'height=600,width=590,status=0,toolbar=0,menubar=0,resizable=0,location=0,scrollbars=1')">Instructions</a>&nbsp;&nbsp;&nbsp;&nbsp;Use <b>ClickBank</b>?&nbsp;<input type="checkbox" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="useclickbanklite" value="1" <?php if ($useclickbanklite) echo "CHECKED"; ?>></td>
          <td bgcolor="lightblue">
          	ClickBank Link Number for <b>LITE Sign up</b>:&nbsp;&nbsp;<input type="text" name="clickbanklinknumberlite" value="<?=$clickbanklinknumberlite?>" size="2">
        </tr>
        <tr>
          <td bgcolor="pink" align="right" colspan="2">
            <b>Note:</b> Your <b>Paypal</b> and <b>e-gold</b> settings <b>above</b> <u>will be applied for the LITE Member signup paylinks.</u>
          </td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td valign="top"><input type="submit" class="greenbutton" value="Save Configuration"></td>
          <td align="right" valign="top">
          	<input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='main.php'">
          	<input type="hidden" name="submitted" value="save">
        		</form>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>