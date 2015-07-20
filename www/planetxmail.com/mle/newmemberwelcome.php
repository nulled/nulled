<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/newmemberwelcome.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title><?=$program_name?> - New member welcome.</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<?php flush(); ?>
<body>
<table align="center" cellpadding="5">
  <tr>
    <td align="center">
      <img src="<?php if ($titleIMG) echo "admin/$titleIMG"; else echo "images/title.gif"; ?>" border="0"><br>
      <hr>
      <h2>You are now activated.</h2>

      <?php
        if ($listtype!="Newsletter [closedlist]") echo "<a href=\"login.php?l=$listhash\"><font color=\"red\"><b>Click here</b></font></a> to login.\n";
        if ($bannerIMG) echo "<p><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a></p>\n";
      ?>
      <?php echo str_replace('[location]','newmemberwelcome', $ads_ads_ads); ?>
    </td>
  </tr>
</table>
</body>
</html>