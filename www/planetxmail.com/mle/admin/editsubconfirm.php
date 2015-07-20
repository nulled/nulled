<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/editsubconfirm.inc');
?>
<html>
<head>
<title><?=$program_name?> - Edit subconfirm</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
var focused = false;
function updateCount()
{
  if (focused)
    document.editsubconfirm.countsubconfirm.value = document.editsubconfirm.subconfirm.value.length;
}
function checkCount(formname)
{
  if (document.editsubconfirm.subconfirm.value.length > <?=$subconfirm_length?>)
    alert('The maximum characters your subconfirm can have is <?=$subconfirm_length?> characters.');
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
            <h4>Edit your subconfirm message.</h4>
            <hr>
            <p>
              <b class="red">Important!!!</b> You MUST have the <b>subscribe link</b> somewhere in the subconfirm message box:
              <b>[list_name]</b>, <b>[admin_email_address]</b>, <b>[subscribe_link]</b>, <b>[user_name]</b>, <b>[program_name]</b>, <b>[password]</b>,
              <b>[first_name]</b>, <b>[last_name]</b>
            </p>
            <p>
              Note: The [password] tag will ONLY be used when the member initially signs-up to the list and NOT when they are confirming a new List Address
              which is used alternatively to the sign-up address.
            </p>
            <b class="red"><?php if ($notValid) echo "$notValid<br><br>"; ?><b>
          </td>
        </tr>
        <!-- Message segment -->
        <tr>
          <td align="right" valign="top">
            subconfirm Message:
            <form name="editsubconfirm" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
          </td>
          <td>
            <textarea wrap="physical" rows="20" cols="80" name="subconfirm" onFocus="focused=true;" onBlur="focused=false;"><?=$subconfirm?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="countsubconfirm" READONLY size="4">
          </td>
          <td>Maximum of <?=$subconfirm_length?> characters.</td>
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