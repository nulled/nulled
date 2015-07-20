<?php
include("../mlpsecure/sessionsecurelistowner.inc");
?>
<html>
<head>
<title><?=$program_name?> - Edit Messages</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
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
            <font size="+1"><b>Edit Messages:</b><br>
            <select onChange="window.location.href=this.options[this.selectedIndex].value">
      				<option>Choose One:</option>
      				<option value="editheader.php">Header</option>
      				<option value="editfooter.php">Footer</option>
      				<option value="editsubconfirm.php">Subscribe Confirm</option>
      				<option value="editsubsuccess.php">Subscribe Success</option>
      				<option value="editunsubsuccess.php">Unsubscribe Success</option>
						</select>
            <hr>
            <input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>';">
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>