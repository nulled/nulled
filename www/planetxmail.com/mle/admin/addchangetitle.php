<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/addchangetitle.inc');
?>
<!DOCTYPE html>
<html>
<head>
<title><?=$program_name?> - Add\Change Title Graphics</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<?php flush(); ?>
<table width="500" cellpadding="5" cellspacing="2" align="center">
  <tr>
    <td align="center" colspan="2">
      <p><h4>Your Title Graphic</h4><br>
      This graphic <b>jpeg</b> or <b>gif</b> will appear as the title graphic for your list.  On the signup\login and members area pages.<br>
      If left blank will default to the one provided by the system.</p>
      <b class="red"><? if ($notValid) echo $notValid."<br>"; ?></b>
    </td>
  </tr>
  <tr>
    <td align="center" colspan="2"><img src="<?=$titleIMG?>" border="0"></td>
  </tr>
  <tr>
    <td align="right"><form name="edittitle" action="/mle/admin/adchangetitle.php" ENCTYPE="multipart/form-data" method="POST">Title Image:</td>
    <td><input type="file" name="title">&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" style="border-width:0px;" name="useDefault" value="1">Use Default Title Image</td>
  <tr>
  <tr>
    <td><input type="submit" class="greenbutton" value="Submit"></td>
    <td align="right"><input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION['aaadminpsk']) echo 'main.php'; else echo 'mainlistowner.php'; ?>';">
    <input type="hidden" name="submitted" value="1">
    </form></td>
</table>
</body>
</html>