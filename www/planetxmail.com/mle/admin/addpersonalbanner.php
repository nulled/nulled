<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/addpersonalbanner.inc');
?>
<html>
<head>
<title><?=$program_name?> - AD Personal Banner</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table width="500" cellpadding="5" cellspacing="2" align="center">
  <tr>
    <td align="center" colspan="2">
      <p>
        <h3>Your Personalized AD Banners</h3>
        These banners will appear on the signup, login, validation and removal pages.<br>
        The <b>Banner Link on Click</b> is where the user is taken when they click on the banner.
      </p>
      <b class="red"><? if ($notValid) echo $notValid."<br>"; ?></b>
    </td>
  </tr>
  <tr>
    <td align="right"><form name="addbanners" action="/mle/admin/addpersonalbanner.php" ENCTYPE="multipart/form-data" method="POST">Banner:</td>
    <td><input type="file" name="banner"></td>
  <tr>
  </tr>
    <td align="right">Banner Link When Clicked:</td>
    <td><font size="+2"></font><input type="text" name="bannerlink" value="<?php if ($bannerlink) echo $bannerlink; else echo 'http://'; ?>" size="32"></td>
  </tr>
  <tr>
    <td><input type="submit" class="greenbutton" value="Submit"></td>
    <td align="right"><input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION['aaadminpsk']) echo 'main.php'; else echo 'mainlistowner.php'; ?>';">
    <input type="hidden" name="submitted" value="1">
    </form></td>
  </tr>
</table>
</body>
</html>