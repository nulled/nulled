<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title><?=$program_name?></title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<?php flush(); ?>
<body>
<table align="center" cellpadding="5" cellspacing="0" width="370" border="0">
  <tr>
    <td align="center">
      <img src="<?php if ($titleIMG) echo 'admin/' . $titleIMG; else echo 'images/title.gif'; ?>" border="0">
    </td>
  </tr>
  <tr>
    <td align="center">
      <hr>
      <b>Your email has been changed.</b>
      <?php echo str_replace('[location]', 'emailchanged', $ads_ads_ads); ?>
    </td>
  </tr>
</table>
</body>
</html>