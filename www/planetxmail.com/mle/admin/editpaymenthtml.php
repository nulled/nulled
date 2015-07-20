<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/editpaymenthtml.inc");
?>
<html>
<head>
<title><?=$program_name?> - Edit Payment Method HTML</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
var focusedsignup  = false;
var focusedrenewal = false;
var focusedupgrade = false;
function updateCount()
{
  if (focusedsignup)
    document.edithtml.countsignuphtml.value  = document.edithtml.signuphtml.value.length;

  if (focusedrenewal)
    document.edithtml.countrenewalhtml.value = document.edithtml.renewalhtml.value.length;

  if (focusedupgrade)
    document.edithtml.countupgradehtml.value = document.edithtml.upgradehtml.value.length;
}
function checkCount(formname)
{
  if (document.edithtml.signuphtml.value.length > <?=$paylinkhtml_length?>)
    alert('The maximum characters your Sign up HTML can have is <?=$paylinkhtml_length?> characters.');
  else if (document.edithtml.renewalhtml.value.length > <?=$paylinkhtml_length?>)
    alert('The maximum characters your Renewal upgrade HTML can have is <?=$paylinkhtml_length?> characters.');
  else if (document.edithtml.upgradehtml.value.length > <?=$paylinkhtml_length?>)
    alert('The maximum characters your Upgrade upgrade HTML can have is <?=$paylinkhtml_length?> characters.');
  else
    formname.submit();
}

document.onkeyup=updateCount;
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
            <?php if ($allowupgrades==0) echo "<h3><b class=\"red\">Your allow upgrade switch is set to NO.  The HTML below will not be used.</b></h4>\n"; ?>
						<p>
						There are THREE (3) sections here.
						<ul>
							<li>SignUp</li>
							<li>ReNewal</li>
							<li>Upgrade</li>
						</ul>
						A member can pay you from these THREE (3) conditions.
						<br><br>
						It is currently MANDATORY that you use the LIST WIZARD to set up these pages.  We are in developement of
						a WHOLE NEW payment system. One that is AUTOMATIC and 100% SECURE from those that try to CHEAT.  In
						the VERY NEW future we will open this back up for manual editing for thats that know how.  So that you
						can add your own graphics and HTML.  Stay TUNED... for now goto <b>Main Options->List Wizard</b>
<!--
            <p>
            The HTML will be placed in between <b>&lt;td&gt;</b> <i>your HTML here</i> <b>&lt;&#047;td&gt;</b>
            which is a table row.  Any valid HTML is legal.  This will then appear when your members click on the
            upgrade buttons.  Place your FULL paypal, click bank, e-gold or any other payment methods or link HTML here.
            </p>
            <p>
            	Note: The Click Bank payment complete link is <b>specific</b> to Click Bank. You also need to use this: <b><http://www.planetxmail.com/mle/upgradecomplete.php</b>
            	as the return link for that Click Bank link you use.
            </p>
            <p>
            <b>[price]</b>, <b>[payment_complete_link]</b>, <b>[cancel_link]</b>, <b>[admin_email]</b>, <b>[program_name]</b>, <b>[item_name]</b>, <b>[item_number]</b>, <b>[clickbank_complete_link]</b><br><br>
            The above tags will be automatically replaced with the correct values base on your List Configuration.  Or you can choose to manually replace
            them yourself.
            </p>
//-->
            <hr>
            <?php if ($notValid) echo "<b class=\"red\"><center>$notValid</center></b>"; ?><b>
          </td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <b>SIGN UP</b> html:
            <form name="edithtml" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
          </td>
          <td>
            <textarea wrap="OFF" rows="20" cols="80" name="signuphtml" onFocus="focusedsignup=true;" onBlur="focusedsignup=false;"><?=$signuphtml?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="countsignuphtml" READONLY size="4">
          </td>
          <td>Maximum of <?=$paylinkhtml_length?> characters.</td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <b>RENEWAL</b> html:
          </td>
          <td>
            <textarea wrap="OFF" rows="20" cols="80" name="renewalhtml" onFocus="focusedrenewal=true;" onBlur="focusedrenewal=false;"><?=$renewalhtml?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <input type="text" name="countrenewalhtml" READONLY size="4">
          </td>
          <td>Maximum of <?=$paylinkhtml_length?> characters.</td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <b>UPGRADE</b> html:
            <form name="edithtml" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
          </td>
          <td>
            <textarea wrap="OFF" rows="20" cols="80" name="upgradehtml" onFocus="focusedupgrade=true;" onBlur="focusedupgrade=false;"><?=$upgradehtml?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="countupgradehtml" READONLY size="4">
          </td>
          <td>Maximum of <?=$paylinkhtml_length?> characters.</td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td><input type="button" class="greenbutton" value="Save" onClick="checkCount(this.form);"></td>
          <td align="right" valign="top"><input type="reset" value="Reset" class="redbutton"><input type="hidden" name="submitted" value="1"></td>
        </tr>
        <tr>
          <td colspan="2" align="center">
            <input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            <?php if ($a) echo "<input type=\"button\" class=\"beigebutton\" value=\"Back to Configurations\" onClick=\"location.href='editlistconfig.php'\">\n"; ?>
            </form>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>