<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/editheader.inc");
?>
<html>
<head>
<title><?=$program_name?> - Edit Header</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
var focused = false;
function updateCount()
{
  if (focused)
    document.editheader.countheader.value = document.editheader.header.value.length;
}
function checkCount(formname)
{
  if (document.editheader.header.value.length > <?=$header_length?>)
    alert('The maximum characters your header can have is <?=$header_length?> characters.');
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
            <h4>Edit your header message.</h4>
            <hr>
            <p>
              Place the following somewhere in the header message box: <b>[list_name]</b>
            </p>
            <b class="red"><?php if ($notValid) echo "$notValid<br><br>"; ?><b>
          </td>
        </tr>
        <!-- Message segment -->
        <tr>
          <td align="right" valign="top">
            header Message:
            <form name="editheader" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
          </td>
          <td>
            <textarea wrap="physical" rows="20" cols="80" name="header" onFocus="focused=true;" onBlur="focused=false;"><?=$header?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="countheader" READONLY size="4">
          </td>
          <td>Maximum of <?=$header_length?> characters.</td>
        </tr>
        <tr>
          <td><input type="button" class="greenbutton" value="Submit" onClick="javascript:checkCount(this.form);"></td>
          <td align="right"><input type="reset" value="Reset" class="redbutton"></td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td><input type="button" class="beigebutton" value="Back to Edit Menu" onClick="javascript:location.href='editmessages.php'"></td>
          <td align="right"><input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
          <input type="hidden" name="submitted" value="1">
          </form>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>