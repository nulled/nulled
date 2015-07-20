<?php
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/mleadminindexloginonly.inc');
?>
<html>
<head>
<title>Administrator Log In</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table width="300" cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <img src="../images/title.gif">
      <hr>
      <b>Administrator Log In</b>
      <hr>
      <?php if ($notValid) echo "<b class=\"red\">$notValid</b>"; ?>
      <form action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <b>User Name:</b><br>
      <input type="text" name="username" value="<?=$username?>"><br><br>
      <b>Password:</b><br>
      <input type="password" name="password" value="<?=$password?>"><br><br>
      <?php echo "<input type=\"checkbox\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"createlistowner\" value=\"1\""; if ($createlistowner=="1"||$newadmin) echo "CHECKED"; echo ">&nbsp;&nbsp;<b>Check to create a new List Owner.</b><br><br>\n"; ?>
      <b>List Owner Name:</b><br>
      <select name="listowner" size="10">
      <?php
        while ($row = mysqli_fetch_row($listowners))
        {
          echo "<option value=\"$row[1]\""; if ($listowner==$row[1]) echo "SELECTED"; echo ">$row[0]</option>\n";
        }
      ?>
      </select>&nbsp;&nbsp;<?=$numOwners?><br><br>
      <input type="submit" class="greenbutton" value="Log-In">
      <input type="hidden" name="submitted" value="login">
      </form>
      <b>Note:</b> Do not log in to Admin control AND as a List MEMBER at the same time.  Even in seperate browsers this will cause
      conflicts.  Simply login and out occordingly.
    </td>
  </tr>
</table>
</body>
</html>