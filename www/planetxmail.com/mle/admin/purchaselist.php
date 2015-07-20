<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/purchaselist.inc");
?>
<html>
<head>
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table width="300" cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <h4>Purchase a List</h4>
      <p>You have no more lists slots left.  You can purchase a new list by clicking the button below.
      Or you can clear a list you already own.  This how ever will destroy all users and their data!
      We advise you purchase a new list!</p>
      <p>Types of lists you can create after you purchase!
      <ul>
        <li><b>Safe List</b> [Open List]</li>
        <li><b>Newsletter</b> [Closed List]</li>
      </ul>
      <input type="button" value="Back to Main" class="beigebutton" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
    </td>
  </tr>
</table>
</body>
</html>