<?php
include("adminsecure/indexelpowner.inc");
?>
<html>
<head>
<title>ELP Owner - Administrator Log In</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
<script language="javascript">
<!--
if (self != top) top.location.href = window.location.href;
//-->
</script>
</head>
<body>
<table cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <img src="../images/elplogo.jpg">
      <hr>
      <b>ELP Owner - Administrator Log In</b>
      <hr>
      <font color="red"><b><?=$notValid?></b></font>
      <form name="login" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <b>ELP Owner Name:</b><br>
      <input type="text" name="username" value="<?=$username?>"><br><br>
      <b>Password:</b><br>
      <input type="password" name="password" value="<?=$password?>"><br><br>
      <input type="submit" class="greenbutton" value="Log-In">
      <input type="hidden" name="submitted" value="login">
      </form>
    </td>
  </tr>
</table>
</body>
</html>