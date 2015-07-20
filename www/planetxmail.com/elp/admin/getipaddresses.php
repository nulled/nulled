<?php
include("adminsecure/session/sessionsecureadmin.inc");
include("adminsecure/getipaddresses.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Get Members</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table border="0" cellspacing="2" cellpadding="3" align="center" width="600">
  <tr>
    <td colspan="3" align="center"><h3>IP addresses for Owner: <font color="red"><?=$o?></font> Member: <font color="red"><?=$u?></font></h3></td>
  </tr>
  <tr>
    <td></td>
    <td bgcolor="lightblue"><b>IP Addresses:</b></td>
    <td></td>
  </tr>
  <?php
    while(list($ipaddress) = mysqli_fetch_row($ipdata))
      echo "<tr>\n<td></td>\n<td bgcolor=\"beige\">$ipaddress</a></td>\n<td></td>\n</tr>";
  ?>
  <tr>
    <td><br></td>
    <td><br></td>
    <td><br></td>
  </tr>
  <tr>
    <td align="center"><input type="button" value="Back to IP Summary" class="beigebutton" onClick="javascript:location.href='getmembers.php?o=<?=$o?>&u=<?=$u?>'"></td>
    <td align="center"><input type="button" value="Back to Sys Summary" class="beigebutton" onClick="javascript:location.href='getsyssummary.php'"></td>
    <td align="center"><input type="button" value="Back to Main Menu" class="beigebutton" onClick="javascript:location.href='main.php'"></td>
  </tr>
</table>
</body>
<html>
