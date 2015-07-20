<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
?>
<html>
<head>
<title><?=$program_name?> - Verification email sent</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<body>
<table align="center" width="300">
  <tr>
    <td align="center">
      <img src="<?php if ($titleIMG) echo "admin/$titleIMG"; else echo "images/title.gif"; ?>" border="0">
    </td>
  </tr>
  <tr>
    <td align="left" valign="top">
      <p>The information you requested has been sent to <b><?=$email?></b>.</p>
      <p>A temporary password has been assigned to you. You will be required to change your password after following the provided link.</p>
      <?php
        if ($bannerIMG)
          echo "<p><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a></p>\n";
      ?>
    </td>
  </tr>
</table>
</html>