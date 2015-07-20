<?php
include("../mlpsecure/sessionsecureadmin.inc");
include("adminsecure/listownercreated.inc");
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
      <b>List Owner Name:</b> <b class="red"><?=$listownerData['username']?></b><br><br>
      <b>List Owner Email:</b> <b class="red"><?=$listownerData['email']?></b><br><br>
      <form><input type="button" value="Log into List Owner" class="beigebutton" onClick="javascript:location.href='logout.php?aaadminpsk=1'"></form>
    </td>
  </tr>
</table>
</body>
</html>