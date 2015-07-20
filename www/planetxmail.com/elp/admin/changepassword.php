<?php
include("adminsecure/session/sessionsecureelpowner.inc");
include("adminsecure/changepassword.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Change Password</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <img src="../images/elplogo.jpg">
      <hr>
      <b>Administrator Change Password</b><br>
      You are required to change your password once from factory install.
      <hr><?php if ($notValid) echo "<font color=\"red\"><b>$notValid</b></font><br><br>\n"; ?>
      <form action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <b>New Password:</b><br>
      <input type="password" name="password1"><br><br>
      <b>Confirm Password:</b><br>
      <input type="password" name="password2"><br><br>
      <input type="submit" class="greenbutton" value="Submit">
      <input type="hidden" name="submitted" value="change">
      <input type="hidden" name="createelpowner" value="<?=$createelpowner?>">
      </form>
    </td>
  </tr>
</table>
</body>
</html>