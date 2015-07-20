<?php
include("../mlpsecure/sessionsecureadmin.inc");
include("adminsecure/createlistowner.inc");
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
      <h4>Create a New List Owner Account</h4>
      <center><b class="red"><?=$notValid?></b></center><br>
      <form name="createlistowner" method="POST" action="<?=$_SERVER[PHP_SELF]?>">
      <b>List Owner Name:</b><br>
      <input type="text" name="thelistownername" value="<?=$thelistownername?>" size="25">
      <br>
      <br>
      <b>List Owner Email Address:</b><br>
      <input type="text" name="adminemail" value="<?=$adminemail?>" size="25">
      <br>
      <br>
      <b>Number of Lists:</b><br>
      <input type="text" name="numLists" value="<?=$numLists?>" size="4"><br><br>
      <input type="hidden" name="submitted" value="create">
      <input type="submit" class="greenbutton" value="Create List Owner">
      <input type="button" value="Log Off" class="beigebutton" onClick="javascript:location.href='logout.php'">
      </form>
    </td>
  </tr>
</table>
</body>
</html>

