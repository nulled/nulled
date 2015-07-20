<?php
include("adminsecure/session/sessionsecureelpowner.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Edit Messages</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table  cellpadding="0" cellspacing="0" align="center" border="1">
  <tr>
    <td>
      <table width="500" cellpadding="3" cellspacing="0" align="center" border="0">
        <tr>
          <td align="center" valign-"top">
            <font color="blue"><h4>Editable Messages</h4></font>
            <hr>
            <p>These messages are messages that appear in the appropriate email messages you send
            and the system sends.  Pick from the menu below.
            </p>
            <h3>Menu:</h3>
            <input type="button" value="Edit Paylink HTML" class="bluebutton" onClick="javascript:location='editpaymenthtml.php'"><br><br>
            <hr>
            <input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='main.php'">
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>