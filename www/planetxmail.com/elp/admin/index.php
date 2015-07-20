<?php
include("adminsecure/index.inc");

header("Cache-Control: must-revalidate");
$ExpireString = "Expires: " . gmdate("D, d M Y H:i:s", time()) . " GMT";
Header($ExpireString);
?>
<html>
<head>
<title>Administrator Log In</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <img src="../images/elplogo.jpg">
      <hr>
      <b>Administrator Log In</b>
      <hr>
      <?php if ($notValid) echo "<font color=\"red\"><b>$notValid</b></font>"; ?>
      <form name="login" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <b>User Name:</b><br>
      <input type="text" name="username" value="<?=$username?>"><br><br>
      <b>Password:</b><br>
      <input type="password" name="password" value="<?=$password?>"><br><br>
      <?php //echo "<input type=\"checkbox\" style=\"border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;\" name=\"createelpowner\" value=\"1\""; if ($createelpowner=="1"||$newadmin) echo "CHECKED"; echo ">&nbsp;&nbsp;<b>Check to create a new ELP Owner.</b><br><br>\n"; ?>
      <b>ELP Owner Name:</b><br>
      <select name="elpowner" size="1">
      <?php
        while (list($elpownername) = mysqli_fetch_row($elpowners))
        {
          echo "<option value=\"$elpownername\""; if ($elpowner==$elpownername) echo "SELECTED"; echo ">$elpownername</option>\n";
        }
      ?>
      </select>&nbsp;&nbsp;<?=$numOwners?><br><br>
      <input type="submit" class="greenbutton" value="Log-In">
      <input type="hidden" name="submitted" value="login">
      </form>
    </td>
  </tr>
</table>
</body>
</html>