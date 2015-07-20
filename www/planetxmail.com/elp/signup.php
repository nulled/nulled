<?php
include("elpsecure/signup.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Signup</title>
<link rel="stylesheet" type="text/css" href="css_elp.css" />
<script language="javascript">
<!--
if (self != top) top.location.href = window.location.href;
//-->
</script>
</head>
<body>
<table align="center" border="0" width="400">
  <tr>
  	<td colspan="2" align="center">
  		<center><img src="images/elplogo.jpg">
  		<hr>
  		<font color="red"><b><?=$notValid?></b></font>
  	</td>
  </tr>
  <tr>
  	<form name="signup" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
  	<td align="right"><b>First Name:</b></td>
  	<td><input type="text" name="fname" value="<?=$fname?>"></td>
  </tr>
  <tr>
  	<td align="right"><b>Last Name:</b></td>
  	<td><input type="text" name="lname" value="<?=$lname?>"></td>
  </tr>
  <tr>
  	<td align="right"><b>Username:</b></td>
  	<td><input type="text" name="username" value="<?=$username?>"></td>
  </tr>
  <tr>
  	<td align="right"><b>Password:</b></td>
  	<td><input type="password" name="password1" value="<?=$password1?>"></td>
  </tr>
  <tr>
  	<td align="right"><b>Password Confirm:</b></td>
  	<td><input type="password" name="password2" value="<?=$password2?>"></td>
  </tr>
  <tr>
  	<td align="right"><b>Contact Email:</b></td>
  	<td><input type="text" name="email" value="<?=$email?>"></td>
  </tr>
  <tr>
  	<td colspan="2" align="left">
  		<br>
  		<p>
  			Please make sure your Contact Email address is an email you know you will not miss messages sent to it.
  			This address will be used to send you the monthly billings.  So, <b>do not</b> use an address that you have
  			Safe-List mailings sent to it.
  		</p>
  	</td>
  </tr>
<?php
  /*
  <tr>
  	<td align="right"><b>Referred By:</b></td>
  	<td><input type="text" name="r" value="<?=$r?>"></td>
  </tr>
 */
?>
 	<tr>
  	<td align="center" colspan="2">
  		<br>
  		<input type="hidden" name="o" value="<?=$o?>">
		  <input type="hidden" name="submitted" value="signup">
  		<input type="submit" class="beigebutton" value="Sign me up!">
  	</td>
  </tr>
  </form>
</table>
</body>
</html>
  