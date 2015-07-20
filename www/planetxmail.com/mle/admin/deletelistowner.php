<?php
include("../mlpsecure/sessionsecureadmin.inc");
include("adminsecure/deletelistowner.inc");
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
      The List owner: <b><?=$_SESSION[aalistownername]?></b><br><br>
      Has been removed from the system.<br><br>
      <input type="button" class="beigebutton" value="Back to Login" onClick="javascript:location='logout.php';">
    </td>
  </tr>
</table>
</body>
</html>