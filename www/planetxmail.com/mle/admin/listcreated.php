<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/listcreated.inc");
?>
<html>
<head>
<title><?=$program_name?>- Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table align="center" cellpadding="3" cellspacing="0" border="1" width="300">
  <tr>
    <td align="center">
      <p align="center"><b>Your new list has been created.</b></p>
      <b>Your list named:</b> <b class="red"><?=$listData['listname']?></b><br><br>
      <b>Administator Email:</b> <b class="red"><?=$listData['adminemail']?></b><br><br>
      <b>From Email:</b> <b class="red"><?=$listData['fromemail']?></b><br><br>
      <b>List Type:</b> <b class="red"><?=$listData['listtype']?></b><br><br>
      <form><input type="button" value="Administrate List" class="beigebutton" onClick="javascript:location.href='<?php if ($isAdmin) echo "main.php"; else echo "mainlistowner.php"; ?>'"></form>
    </td>
  </tr>
</table>
</body>
</html>