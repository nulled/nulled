<?php
include("mlpsecure/sessionsecure.inc");
include("mlpsecure/upgradecomplete.inc");
?>
<html>
<head>
<title><?=$program_name?></title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<body>
<table align="center">
  <tr>
    <td align="center">
      <img src="<?php if ($titleIMG) echo "admin/$titleIMG"; else echo "images/title.gif"; ?>" border="0">
      <hr>
      <b>Thank you for your order!</b><br><br>
      Upgrade complete. Please <b>log off</b> <?=$program_name?> then log back on for changes to take effect.
      <br><br>
      If you need to contact us for any reason: <b><?=$admin_email_address?></b>
      <br><br>
      <input type="button" class="redbutton" value="Close Window" onClick="javascript:window.close()">
    </td>
  </tr>
</table>
</body>
</html>