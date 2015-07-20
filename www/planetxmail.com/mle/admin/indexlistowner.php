<?php
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/indexlistowner.inc');
if ($noList)
{
  header("Location: createlist.php");
  exit;
}
?>
<html>
<head>
<title>List Owner - Administrator Log In</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table width="300" cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <img src="../images/title.gif" border="0" />
      <hr />
      <b>List Owner - Administrator Log In</b>
      <hr />
      <?php if ($notValid) echo '<b class="red">' . $notValid . '</b>'; ?>
      <form action="/mle/admin/indexlistowner.php" method="POST">
        <b>User Name:</b><br />
        <input type="text" name="username" value="<?=$username?>" /><br /><br />
        <b>Password:</b><br />
        <input type="password" name="password" value="<?=$password?>" /><br /><br />
        <input type="submit" class="greenbutton" value="Login" />
        <input type="hidden" name="submitted" value="login" />
      </form>
    </td>
  </tr>
</table>
</body>
</html>