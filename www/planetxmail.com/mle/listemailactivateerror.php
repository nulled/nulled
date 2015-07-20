<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/listemailactivateerror.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title><?=$program_name?> - List Email activation ERROR</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<?php flush(); ?>
<body>
<table width="600" cellpadding="3" cellspacing="0" align="center" border="0">
  <tr>
    <td>
      <h4>There was an error activating this email account.</h4>
      <b>Possible reasons listed below:</b>
      <br>
      <li>You <b class="red">already activated</b> your List Email Address.</li>
      <li>You didn't correctly copy the <b>entire</b> URL from the mail to your browser.</li>
      <li>You are using a confirmation link from a previous attempt confirming a different email.</li>
      <br>
      <hr>
      <?php
        if ($bannerIMG) echo "<p><center><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a></center></p>\n";
      ?>
      <?php echo str_replace('[location]','listemailactivateerror', $ads_ads_ads); ?>
    </td>
  </tr>
</table>
</body>
</html>