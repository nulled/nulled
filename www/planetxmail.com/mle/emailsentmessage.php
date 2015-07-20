<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Verification e-mail sent</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<?php flush(); ?>
<body>
<table align="center" width="500">
  <tr>
    <td align="center">
      <img src="<?php if ($titleIMG) echo "admin/$titleIMG"; else echo "images/title.gif"; ?>" border="0">
    </td>
  </tr>
  <tr>
    <td valign="top" align="center">
      <hr>
      <p><i>Thank you</i> for signing up with us.  An email was sent to <b><?=$email?></b> for validation.
      Once you get the mail please follow the link provided in the mail to activate your account.
      </p>
      <p>If you do not respond within 3 days you will have to re-apply.</p>
      <p>And again, <b>Thank you</b> for signing up to <i>the</i> most user friendly and sophisticated mailing list and newsletter tool on the web!</p>
      <?php
        if ($bannerIMG)
          echo "<hr><p><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a></p>\n";
      ?>
      <?php echo str_replace('[location]','emailsentmessage', $ads_ads_ads); ?>
    </td>
  </tr>
</table>
</body>
</html>