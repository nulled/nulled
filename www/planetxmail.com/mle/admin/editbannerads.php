<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/editbannerads.inc");
?>
<html>
<head>
<title><?=$program_name?> - Edit Banner ADs</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table width="500" cellpadding="5" cellspacing="2" align="center">
  <tr>
    <td align="center" colspan="2">
      <p>
      <font color="#005F8C"><b>Your AD Banners</b></font><br>
      Click on your banner to test that the link applied to it works properly.<br>
      These banners will appear on the signup, login, validation and removal pages the members will see.
      </p>
      <b class="red"><? if ($notValid) echo $notValid."<br>"; ?></b>
      <hr>
      <?php
        if ($banners[0]!="none") echo "<b>Banner:</b><br><a href=\"$bannerlinks[0]\" target=\"_blank\"><img src=\"$banners[0]\" border=\"0\"></a><br><br>\n"; else echo "<b>BANNER EMPTY</b><br><br>\n";
      ?>
    </td>
  </tr>
  <tr>
    <td align="right"><form name="editbanners" action="/mle/admin/editbannerads.php" ENCTYPE="multipart/form-data" method="POST">Banner:</td>
    <td><input type="file" name="banner">&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" style="border-width:0px" name="deletebanner" value="1">Check To Delete.</td>
  <tr>
  </tr>
    <td align="right">Banner Link:</td>
    <td><input type="text" name="bannerlink" value="<?php if ($bannerlink!="") echo $bannerlink; else echo $bannerlinks[0]; ?>" size="32"></td>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td><input type="submit" class="greenbutton" value="Submit"></td>
    <td align="right"><input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='<?php if ($_SESSION['aaadminpsk']) echo 'main.php'; else echo 'mainlistowner.php'; ?>'">
    <input type="hidden" name="bannerID" value="<?=$bannerID?>">
    <input type="hidden" name="submitted" value="1">
    </form></td>
  </tr>
</table>
</body>
</html>