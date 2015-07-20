<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/changelistownername.inc");
?>
<html>
<head>
<title><?=$program_name?> - Change List Owner Name</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table width="300" cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <h4>Change Your List Owner User Name: <?=$oldlistownername?></h4>
      <center><?php if ($notValid) echo "<b class=\"red\">$notValid</b><br>"?></b>
      <b>Note:</b> Changing your List Owner User Name does NOT effect the operation of your list other than, after you change it,
      you will have to use the new name when you try to login to your Admin Control Panel.<br>
      <form name="changelistownername" method="POST" action="<?=$_SERVER[PHP_SELF]?>">
      <b>New List Owner User Name:</b><br>
      <input type="text" name="listownername" value="<?=$listownername?>" size="25"><br><br>
      <input type="hidden" name="submitted" value="change">
      <input type="submit" class="greenbutton" value="Change List Owner User Name"><br><br>
      <input type="button" value="Back to Main" class="beigebutton" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
      </form>
      The Current List Owner User Name is:<br>
      <input type="text" name="oldlistownername" value="<?=$oldlistownername?>" size="20" READONLY>
    </td>
  </tr>
</table>
</body>
</html>

