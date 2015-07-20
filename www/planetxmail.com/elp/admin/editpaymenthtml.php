<?php
include("adminsecure/session/sessionsecureelpowner.inc");
include("adminsecure/editpaymenthtml.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Edit Payment Method HTML</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
<script language="javascript">
<!--
var focusedpro = false;
var focusedexe = false;
function updateCount()
{
  if (focusedpro) document.edithtml.countprohtml.value = document.edithtml.signuppaylinks.value.length;
  if (focusedexe) document.edithtml.countexehtml.value = document.edithtml.monthlypaylinks.value.length;
}
function checkCount(formname)
{
  if (document.edithtml.signuppaylinks.value.length > 5000) alert('The maximum characters your Professional upgrade HTML can have is 5000 characters.');
  else if (document.edithtml.monthlypaylinks.value.length > 5000) alert('The maximum characters your Executive upgrade HTML can have is 5000 characters.');
  else formname.submit();
}
document.onkeypress=updateCount;
//-->
</script>
</head>
<body>
<table  cellpadding="0" cellspacing="0" align="center" border="1">
  <tr>
    <td>
      <table width="500" cellpadding="3" cellspacing="0" align="center" border="0">
        <tr>
          <td colspan="2">
            <center><h4>Edit your HTML payment links.</h4></center>
            <p>
	            The HTML will be placed in between <b>&lt;td&gt;</b> <i>your HTML here</i> <b>&lt;&#047;td&gt;</b>
	            which is a table row.  Any valid HTML is legal.  This will then appear when your members signup and when
	            they are auto-billed monthly.  Place your Paypal, Click Bank, E-gold or any other payment methods or link HTML here.
            </p>
            <p>
            	Note: For Click Bank you need to set this: <b>http://www.planetxmail.com/elp/activatemember.php</b>
            	as the return link for that Click Bank link you use.  Place the <b>[click_bank_params]</b> tag after your link title.  This is
            	REQUIRED in order to log the payments correctly with ELP systems.  Example: http://www.clickbank.net/sell.cgi?cbusername/1/ELP[click_bank_params]
            </p>
            <p>
            <b>[price]</b>, <b>[payment_complete_link]</b>, <b>[payment_cancel_link]</b>, <b>[email_address]</b>, <b>[click_bank_params]</b><br><br>
            The above tags will be automatically replaced with the correct values base on your ELP Configuration.  Or you can choose to manually replace
            them yourself.
            </p>
            <hr>
            <center><font color="red"><b><?php if ($notValid) echo "$notValid<br><br>"; ?><b></font></center>
          </td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <b>Signup</b> Paylink HTML:
            <form name="edithtml" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
          </td>
          <td>
            <textarea wrap="OFF" rows="20" cols="60" name="signuppaylinks" onFocus="focusedpro=true;" onBlur="focusedpro=false;"><?=$signuppaylinks?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="countprohtml" READONLY size="4">
          </td>
          <td>Maximum of 5000 characters.</td>
        </tr>
        <tr>
        	<td colspan="2"><hr></td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <b>Monthly</b> Paylink HTML:
          </td>
          <td>
            <textarea wrap="OFF" rows="20" cols="60" name="monthlypaylinks" onFocus="focusedexe=true;" onBlur="focusedexe=false;"><?=$monthlypaylinks?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <input type="text" name="countexehtml" READONLY size="4">
          </td>
          <td>Maximum of 5000 characters.</td>
        </tr>
        <tr>
          <td><input type="button" class="greenbutton" value="Save" onClick="javascript:checkCount(this.form);"></td>
          <td align="right" valign="top"><input type="reset" value="Reset" class="redbutton"></td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td colspan="2" align="center"><input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
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