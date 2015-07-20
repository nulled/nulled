<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/enp.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title><?=$program_name?></title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<body>
<table align="center" width="600">
  <tr>
    <td align="center">
      <img src="<?php if ($titleIMG) echo 'admin/' . $titleIMG; else echo 'images/title.gif'; ?>" border="0" />
      <hr />

      <font color="red"><b><?=$notValid?></b></font>

      <form name="newpassword" action="/mle/enp.php" method="POST">
        <b>Enter new password:</b><br />
        <input type="password" name="password1"><br /><br />
        <b>Confirm password:</b><br />
        <input type="password" name="password2"><br /><br />
        <input type="hidden" name="submitted" value="changepassword" />
        <input type="hidden" name="v" value="<?=$v?>" />
        <input type="hidden" name="u" value="<?=$u?>" />
        <input type="hidden" name="e" value="<?=$e?>" />
        <input type="hidden" name="l" value="<?=$l?>" />
        <input type="submit" value="Submit" class="greenbutton" />
      </form>

      <br />

      <?php

        if ($bannerIMG)
          echo '<p><a href="' . $bannerLINK . '" target="_blank"><img src="admin/' . $bannerIMG . '" border="0"></a></p>';

      ?>

    </td>
  </tr>
</table>
</body>
</html>