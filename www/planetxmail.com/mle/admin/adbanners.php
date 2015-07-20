<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/adbanners.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF=8" />
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<?php flush(); ?>
<body>
<table width="500" cellpadding="5" cellspacing="2" align="center">
  <tr>
    <td align="center" colspan="2">
      <p>
      <b class="red"><h3>Your AD Banners</h3></b><br>
      These banners will appear on the pop up sent mail window after a member sends mail.<br>
      Same with the Bill Board Ads you create.<br>
      The <b>Banner Link on Click</b> is where the user is taken when they click on the banner.
      </p>
      <?php if ($notValid) echo '<b class="red">' . $notValid . '</b><br />'; ?>
    </td>
  </tr>
  <tr>
    <td align="right"><form name="editbanners" action="/mle/admin/adbanners.php" enctype="multipart/form-data" method="post">Banner:</td>
    <td><input type="file" name="banner"></td>
  <tr>
  </tr>
    <td align="right">Banner Link on Click:</td>
    <td><font size="+2"></font><input type="text" name="bannerlink" value="<?php if ($bannerlink) echo $bannerlink; else echo 'http://'; ?>" size="32" /></td>
  </tr>
  <tr>
    <td><input type="submit" class="greenbutton" value="Submit" /></td>
    <td align="right">
      <input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION['aaadminpsk']) echo 'main.php?option=affstats'; else echo 'mainlistowner.php?option=affstats'; ?>'">
      <input type="hidden" name="submitted" value="1" />
    </form>
    </td>
</table>
</body>
</html>