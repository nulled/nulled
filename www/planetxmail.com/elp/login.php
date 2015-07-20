<?php
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
<table align="center" border="0" width="300">
  <tr>
  	<td>
  		<center><img src="images/elplogo.jpg">
  		<br><br>
  		<font color="red"><b><?=$notValid?></b></font>
  		<form name="login" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
  		<b>Username:</b>
  		<br>
  		<input type="text" name="username" value="<?=$username?>">
  		<br>
  		<br>
  		<b>Password:</b>
  		<br>
  		<input type="password" name="password" value="<?=$password?>">
  		<br>
  		<br>
  		<b>ELP Owner Name:</b>
  		<br>
  		<input type="text" name="elpowner" value="<?=$elpowner?>">
  		<br>
  		<br>
  		<input type="hidden" name="submitted" value="login">
  		<input type="hidden" name="access" value="yes">
  		<input type="submit" class="beigebutton" value="Login In"></center>
  		</form>
  		<p>
  		  All <b>IP addresses</b> are <i>logged</i> and <i>monitored</i>.  If
  		  the system detects that an account is <b>sharing</b> accounts with
  		  others, it will be <b>blocked</b> from being able to log in any further
  		  and placed <i>under investigation</i>.  We reserve the right to <b>delete</b> any
  		  account that is found to be giving out login information to others and not
  		  using it for <b>their</b> personal use.
  		</p>
  		<p>
  		  At no time will any account be deleted until contact with the account owner has been
  		  established within a <b>reasonable</b> time frame, vai email.
  	  </p>
      <center><img border="0" src="http://fastcounter.bcentral.com/fastcounter?2893585+5787177"></center>
  	</td>
  </tr>
</table>
</body>