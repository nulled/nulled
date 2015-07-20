<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/createlistlistowner.inc");
?>
<html>
<head>
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table width="300" cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <h4>Create a New List</h4>
      <center><b class="red"><?=$notValid?></b></center><br>
      <form name="createlist" method="POST" action="<?=$_SERVER[PHP_SELF]?>">
      <b>List Name:</b><br>
      <input type="text" name="thelistname" value="<?=$thelistname?>" size="25">
      <br>
      <br>
      <b>Administator Email Address:</b><br>
      <input type="text" name="adminemail" value="<?=$adminemail?>" size="25">
      <br>
      <p align="left">
      <b>From Name &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;From Email Address:</b><br>
      <input type="text" name="fromname" value="<?=$fromname?>" size="10"><input type="text" name="fromemail" value="<?=$fromemail?>" size="25" READONLY></p>
      <b>Bounce Email Address:</b><br>
      <input type="text" name="bounceemail" value="<?=$bounceemail?>" size="25" READONLY>
      <br>
      <br>
      <b>List Type:</b><br>
  		<select size="1" name="listtype">
  		  <option<?php if ($listtype=="Safelist [openlist]") echo " SELECTED"; ?>>Safelist [openlist]</option>
  		  <option<?php if ($listtype=="Newsletter [closedlist]") echo " SELECTED"; ?>>Newsletter [closedlist]</option>
  		</select>
      <br>
      <br>
      <input type="hidden" name="submitted" value="create">
      <input type="submit" class="greenbutton" value="Create list">
      <input type="button" value="Cancel" class="beigebutton" onClick="javascript:location.href='<?php if ($firstList=="1") echo "logout.php"; else echo "mainlistowner.php"; ?>'">
      <input type="hidden" name="listowner" value="<?=$listowner?>">
      </form>
    </td>
  </tr>
</table>
</body>
</html>

