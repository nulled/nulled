<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/changelistname.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table width="300" cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <h4>Change List Name for: <?=$oldlistname?></h4>
      <center><?php if ($notValid) echo '<b class="red">' . $notValid . '</b><br />'; ?></b>
      <b>Note:</b> Changing your List Name will not effect the operation of the list.
      <br>
      <form name="changelistname" method="POST" action="/mle/admin/changelistname.php">
        <b>New List Name:</b><br />
        <input type="text" name="newlistname" value="<?=$newlistname?>" size="25" /><br /><br />
        <input type="hidden" name="submitted" value="change" />
        <input type="submit" class="greenbutton" value="Change List Name" /><br /><br />
        <input type="button" value="Back to Main" class="beigebutton" onClick="location.href='<?php if ($_SESSION['aaadminpsk']) echo 'main.php'; else echo 'mainlistowner.php'; ?>'" />
      </form>
      The Current List Name is:<br>
      <input type="text" name="oldlistname" value="<?=$oldlistname?>" size="25" READONLY>
    </td>
  </tr>
</table>
</body>
</html>

