<?php
include("mlpsecure/mrl.inc");
?>
<html>
<head>
<title><?=$program_name?></title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
<script language="javascript">
<!--
if (self != top) top.location.href = window.location.href;
//-->
</script>
</head>
<body>
<table align="center" cellpadding="5" cellspacing="0" width="370" border="1">
  <tr>
    <td align="center" colspan="2">
      <img src="images/title.gif">
      <hr>
      <h3>Remove from ALL SafeLists and NewsLetters</h3>
    </td>
  </tr>
  <tr>
  	<td>
  		<br>
      <center><b class="red"><?php if ($notValid) echo "$notValid<br><br>"; ?></b></center>
      <b class="red">Remove completely</b> will COMPLETELY remove you from ALL Lists.  All your URL Tracking will be
      deleted and the ability to Log In.</b>
      <form name="removeall" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <center><input type="submit" class="redbutton" value="I Authorize Removal"></center>
      <input type="hidden" name="submitted" value="removeall">
      <input type="hidden" name="uID" value="<?=$uID?>">
      <input type="hidden" name="p" value="<?=$p?>">
      </form>
      <br>
    </td>
  </tr>
</table>
</body>
</html>
