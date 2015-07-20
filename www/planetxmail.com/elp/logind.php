<?php
include("elpsecure/demoset.inc");
include("elpsecure/login.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Login</title>
<link rel="stylesheet" type="text/css" href="css_elp.css" />
<script language="javascript">
<!--
if (self != top) top.location.href = window.location.href;
//-->
</script>
</head>
<body>
<table align="center" border="0">
  <tr>
  	<td>
  		<center><img src="images/elplogo.jpg">
  		<br><br>
  		<font color="red"><b><?=$notValid?></b></font>
  		<form name="login" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
  		<b>Username:</b>
  		<br>
  		<input type="text" name="username" value="<?=$username?>" READONLY>
  		<br>
  		<br>
  		<b>Password:</b>
  		<br>
  		<input type="password" name="password" value="<?=$password?>" READONLY>
  		<br>
  		<br>
  		<b>ELP Owner Name:</b>
  		<br>
  		<input type="text" name="elpowner" value="<?=$elpowner?>" READONLY>
  		<br>
  		<br>
  		<input type="hidden" name="submitted" value="login">
  		<input type="hidden" name="access" value="yes">
  		<input type="submit" class="bluebutton" value="login"></center>
  		</form>
  	</td>
  </tr>
</table>
</body>