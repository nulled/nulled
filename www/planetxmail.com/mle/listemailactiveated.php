<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/listemailactiveated.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title><?=$program_name?> - List Email activation successful</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<?php flush(); ?>
<body>
<table width="590" cellpadding="3" cellspacing="0" align="center" border="0">
  <tr>
    <td align="center">
      <img src="<?php if ($titleIMG) echo "admin/$titleIMG"; else echo "images/title.gif"; ?>">
      <hr>
      <h4>Your List Email address has been activated.  You may now send emails to list members!</h4>
      <a href="login.php?l=<?=$listhash?>"><font color="red"><b>Click here</b></font></a> to login.
      <?php echo str_replace('[location]','listemailactivated', $ads_ads_ads); ?>
      <?php
        if ($bannerIMG)
          echo "<p><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a></p>\n";
      ?>
    </td>
  </tr>
</table>
</body>
</html>