<?php
include("../mlpsecure/sessionsecurelistowner.inc");
?>
<html>
<head>
<title><?=$program_name?> - Menu Personalize Graphics and Banners</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table  cellpadding="0" cellspacing="0" align="center" border="1">
  <tr>
    <td>
      <table width="500" cellpadding="3" cellspacing="0" align="center" border="0">
        <tr>
          <td align="center" valign="top">
          	<font size="+1"><b>Personalize Graphics and Banners:</b>
          	<br><br>
			      <select onChange="window.location.href=this.options[this.selectedIndex].value">
			      	<option>Choose One:</option>
			      	<option value="addchangetitle.php">Add/Change List Title</option>
			      	<option value="addpersonalbanner.php">Add Banner Ad</option>
			      	<option value="listbannerads.php">Edit/View Banner Ads</option>
			      </select>
			      <br><br>
			      <input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>';">
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>