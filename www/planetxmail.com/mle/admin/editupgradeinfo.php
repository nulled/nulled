<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/editupgradeinfo.inc");
?>
<html>
<head>
<title><?=$program_name?> - Edit Upgrade Info HTML</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
var focusedpro = false;
var focusedexe = false;
function updateCount()
{
  if (focusedpro)
    document.edithtml.countprohtml.value = document.edithtml.prohtml.value.length;

  if (focusedexe)
    document.edithtml.countexehtml.value = document.edithtml.exehtml.value.length;
}
function checkCount(formname)
{
  if (document.edithtml.prohtml.value.length > <?=$paylinkhtml_length?>)
    alert('The maximum characters your Professional Upgrade Info HTML can have is <?=$paylinkhtml_length?> characters.');
  else if (document.edithtml.exehtml.value.length > <?=$paylinkhtml_length?>)
    alert('The maximum characters your Executive Upgrade Info HTML can have is <?=$paylinkhtml_length?> characters.');
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
          <td colspan="2" align="center">
            <h4>Edit your Upgrade Info HTML.</h4>
            <?php if ($allowupgrades==0) echo "<h3><b class=\"red\">Your allow upgrade switch is set to NO.  The HTML below will not be used.</b></h4>\n"; ?>
            <p>
            The HTML will be placed in between <b>&lt;td&gt;</b> <i>your HTML here</i> <b>&lt;&#047;td&gt;</b>
            which is a table row.  Any valid HTML is legal.  This will then appear when your members click on the
            upgrade buttons.  Place your Upgrade Benefits and information here.
            </p>
            <p>
            <b>[mem_sendmail_times_week]</b>, <b>[pro_sendmail_times_week]</b>, <b>[num_urltrackers_mem]</b>, <b>[num_urltrackers_pro]</b>, <b>[num_urltrackers_exe]</b>, <b>[cost_of_pro]</b>, <b>[cost_of_exe]</b><br><br>
            The above tags will be automatically replaced with the correct values base on your List Configuration.  Or you can choose to manually enter them yourself.
            </p>
            <hr>
            <b class="red"><?php if ($notValid) echo "$notValid<br><br>"; ?><b>
          </td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <b>Professional</b> Upgrade Info:
            <form name="edithtml" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
          </td>
          <td>
            <textarea wrap="OFF" rows="20" cols="80" name="prohtml" onFocus="focusedpro=true;" onBlur="focusedpro=false;"><?=$prohtml?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="countprohtml" READONLY size="4">
          </td>
          <td>Maximum of <?=$paylinkhtml_length?> characters.</td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <b>Executive</b> Upgrade Info:
          </td>
          <td>
            <textarea wrap="OFF" rows="20" cols="80" name="exehtml" onFocus="focusedexe=true;" onBlur="focusedexe=false;"><?=$exehtml?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right" valign="top">
            <input type="text" name="countexehtml" READONLY size="4">
          </td>
          <td>Maximum of <?=$paylinkhtml_length?> characters.</td>
        </tr>
        <tr>
          <td><input type="button" class="greenbutton" value="Save" onClick="checkCount(this.form);"></td>
          <td align="right" valign="top"><input type="reset" value="Reset" class="redbutton"><input type="hidden" name="submitted" value="1"></td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
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