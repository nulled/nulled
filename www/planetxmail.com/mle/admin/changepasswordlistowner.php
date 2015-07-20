<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/changepasswordlistowner.inc");
?>
<html>
<head>
<title>List Owner - Change Password</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <img src="../images/title.gif">
      <hr>
      <h4>List Owner - <font color="red">Change Password</font></h4>
      You are <b>REQUIRED</b> to <b>CHANGE</b> your <b>PASSWORD</b>, please write it down somewhere <b>SAFE</b>.
      <hr><?php if ($notValid) echo "<b class=\"red\">$notValid</b><br><br>\n"; ?>
      <form action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <b>New Password:</b><br>
      <input type="password" name="password1"><br><br>
      <b>Confirm Password:</b><br>
      <input type="password" name="password2"><br><br>
      <input type="submit" class="greenbutton" value="Submit">
      <input type="hidden" name="submitted" value="1">
      <input type="hidden" name="createlistowner" value="<?=$createlistowner?>">
      </form>
    </td>
  </tr>
</table>
</body>
</html>