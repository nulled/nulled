<?php
include("adminsecure/session/sessionsecureelpowner.inc");
include("adminsecure/showmember.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
<script language="javascript">
<!--
function resetpassword(formname)
{
  if (document.userdata.pass1.value < 1) alert('Missing Required Fields.');
  else if (document.userdata.pass2.value < 1) alert('Missing Required Fields.');
  else if (document.userdata.pass1.value != document.userdata.pass2.value) alert('Passwords do not match.');
  else
  {
    if (confirm('Are you sure?\nAn email will be sent to the member.'))
    {
  		document.userdata.todo.value = 'resetpassword';
  		formname.submit();
  	}
	}
}
function confirmDelete(formname)
{
  if (confirm('Are you sure you want to erase member?  Including all URL data for this member?')) formname.submit();
}
//-->
</script>
</head>
<body>
<table align="center" cellpadding="3" cellspacing="1" border="0" width="500">
  <tr>
    <td align="center" colspan="2">
      <font size="+1">Profile for</font> <font color="red" size="+2"><b><?=$username?></b></font><br><br>
      <font color="red"><b><?php if ($notValid!="") echo $notValid."<br><br>" ?></b></font>
    </td>
  </tr>
  <tr>
    <td align="right" bgcolor="#EFEEEA">
      <form name="userdata" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      First Name:&nbsp;&nbsp;</td>
    <td bgcolor="#EFEEEA">
      <p align="left"><b><input type="text" size="30" name="fname" value="<?=$fname?>"></b></td>
  </tr>
  <tr>
    <td bgcolor="#F4F4F4">
      <p align="right">Last Name:&nbsp;</td>
    <td bgcolor="#F4F4F4">
      <p align="left"><b><input type="text" size="30" name="lname" value="<?=$lname?>"></b></td>
  </tr>
  <tr>
    <td bgcolor="#EFEEEA">
      <p align="right">Email Address:&nbsp;</td>
    <td bgcolor="#EFEEEA">
      <p align="left"><b><input type="text" size="30" name="email" value="<?=$email?>"></b></td>
  </tr>
  <tr>
    <td bgcolor="#F4F4F4">
      <p align="right">Blocked?&nbsp;</td>
    <td bgcolor="#F4F4F4">
      <p align="left"><b><?php if ($blocked) echo "Yes"; else echo "No"; ?></b>&nbsp;&nbsp;&nbsp;<input type="checkbox" name="blocked" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" value="1" <?php if ($blocked) echo "CHECKED"; ?>>Check to BLOCK</td>
  </tr>
  <tr>
    <td colspan="2">
      <p>You can edit any of the fields above and hit the <b>Apply Changes</b> button below.</p>
      <p><b>Note:</b> If the member is blocked this means they will not be able to login and use ELP.</p>
      <input type="hidden" name="todo" value="changememberdata">
      <input type="hidden" name="elpmember" value="<?=$elpmember?>">
      <center><input type="submit" class="greenbutton" value="Apply Changes"></center>
    </td>
  </tr>
  <tr>
  	<td colspan="2"><hr></td>
  </tr>
	<tr>
		<td colspan="2" bgcolor="beige">
			<p><font color="red"><b>Important!</b></font> Use this if a member has paid you vai your paylinks and/or through your affiliate system. Or if for some reason their transaction was not completed after they paid.</p>
		</td>
	</tr>
  <tr>
    <td bgcolor="beige" valign="top">
      <p align="right">Paid Bill?&nbsp;</td>
    <td bgcolor="beige">
	    <b><?php if ($paid) echo "Yes</b>&nbsp;&nbsp;&nbsp;&nbsp;"; else echo "No</b>&nbsp;&nbsp;&nbsp;&nbsp;"; if (! $paid){ echo "</b><input type=\"button\" class=\"greenbutton\" value=\"Generate Manual Transaction\" onClick=\"location.href='manualtrans.php?elpmember=$elpmember&memtype=$memtype'\">"; } ?>
     </td>
  </tr>
  <tr>
    <td align="center" colspan="2">
    	<hr>
    	New Password:<br>
    	<input type="text" name="pass1" value="<?=$pass1?>"><br>
    	Confirm Password:<br>
    	<input type="text" name="pass2" value="<?=$pass2?>"><br><br>
      <input type="button" class="bluebutton" value="Change Member Password" onClick="resetpassword(this.form)">
      </form>
      <hr>
    </td>
  </tr>
  <tr>
    <td colspan="2" align="center">
      Deleting this member will remove all records of him\her!
    </td>
  </tr>
  <tr>
    <td colspan="2" align="center">
      <form name="delete" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
	      <input type="hidden" name="todo" value="deletemember">
	      <input type="hidden" name="elpmember" value="<?=$elpmember?>">
	      <input type="button" value="Delete Member" class="redbutton" onClick="confirmDelete(this.form)">
      </form>
    </td>
  </tr>
  <tr>
    <td align="center" colspan="2">
      <hr>
      <?php if ($fromtrans) echo "<input type=\"button\" value=\"Back to Transactions\" class=\"beigebutton\" onClick=\"location.href='transactions.php?show=$fromtrans'\">&nbsp;&nbsp;&nbsp;&nbsp;\n"; ?>
      <input type="button" value="Back to Main Menu" class="beigebutton" onClick="javascript:location.href='main.php'">
    </td>
  </tr>
</body>
</html>