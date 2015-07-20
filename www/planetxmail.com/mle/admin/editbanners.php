<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/editbanners.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<?php flush(); ?>
<body>
<table width="500" cellpadding="5" cellspacing="2" align="center">
  <tr>
    <td align="center" colspan="2">
      <p><font color="#005F8C"><b>Your AD Banners</b></font><br>
      Click on your banner to test that the link applied to it works properly.</p>
      <?php if ($notValid) echo '<b class="red">' . $notValid . '</b><br />'; ?>
      <hr />
      <?php
        if ($banners[0] != 'none') echo '<b>Banner:</b><br /><a href="' . $bannerlinks[0] . '" target="_blank"><img src="' . $banners[0] . '" border="0"></a><br /><br />'."\n"; else echo '<b>BANNER EMPTY</b><br /><br />'."\n";
      ?>
    </td>
  </tr>
  <tr>
    <td align="right"><form name="editbanners" action="/mle/admin/editbanners.php" ENCTYPE="multipart/form-data" method="POST">Banner:</td>
    <td><input type="file" name="banner"><input type="checkbox" name="deletebanner" value="1" />Check To Delete.</td>
  <tr>
  </tr>
    <td align="right">Banner Link:</td>
    <td><input type="text" name="bannerlink" value="<?php if ($bannerlink) echo $bannerlink1; else echo $bannerlinks[0]; ?>" size="32" /></td>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td><input type="submit" class="greenbutton" value="Submit" /></td>
    <td align="right"><input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION['aaadminpsk']) echo 'main.php'; else echo 'mainlistowner.php'; ?>'">
    <input type="hidden" name="bannerID" value="<?=$bannerID?>" />
    <input type="hidden" name="submitted" value="1" />
    </form></td>
</table>
</body>
</html>