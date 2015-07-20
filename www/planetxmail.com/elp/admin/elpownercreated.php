<?php
include("adminsecure/session/sessionsecureadmin.inc");
include("adminsecure/elpownercreated.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table align="center" cellpadding="3" cellspacing="0" border="1" width="300">
  <tr>
    <td align="center">
      <p align="center"><b>Your new ELP Owner has been created.</b></p>
      <b>ELP Owner Name:</b> <b class="red"><?=$elpownerData['elpownername']?></b><br><br>
      <b>ELP Owner Email:</b> <b class="red"><?=$elpownerData['email']?></b><br><br>
      <form><input type="button" value="Log into List Owner" class="beigebutton" onClick="javascript:location.href='logout.php?aaadminpsk=1'"></form>
    </td>
  </tr>
</table>
</body>
</html>