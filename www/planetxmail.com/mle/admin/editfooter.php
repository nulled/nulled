<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/editfooter.inc");
?>
<html>
<head>
<title><?=$program_name?> - Edit Footer</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
var focused = false;
function updateCount()
{
  if (focused) document.editfooter.countfooter.value = document.editfooter.footer.value.length;
}
function checkCount(formname)
{
  if (document.editfooter.footer.value.length > <?=$footer_length?>) alert('The maximum characters your footer can have is <?=$footer_length?> characters.');
  else formname.submit();
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
            <h4>Edit your footer message.</h4>
            <hr>
            <p>
              <b class="red">Important!!!</b> You MUST specify the <b>unsubscribe link</b>  somewhere in the Footer. Place this following in
              the footer message box: <b>[list_name]</b>, <b>[unsubscribe_link]</b>
            </p>
            <b class="red"><?php if ($notValid) echo "$notValid<br><br>"; ?><b>
          </td>
        </tr>
        <!-- Message segment -->
        <tr>
          <td align="right" valign="top">
            Footer Message:
            <form name="editfooter" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
          </td>
          <td>
            <textarea wrap="physical" rows="20" cols="80" name="footer" onFocus="focused=true;" onBlur="focused=false;"><?=$footer?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="countfooter" READONLY size="4">
          </td>
          <td>Maximum of <?=$footer_length?> characters.</td>
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