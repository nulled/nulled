<html>
<head>
<title>Mulit-List Pro - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table align="center" border="0" width="500" cellspacing="2" cellpadding="5">
  <tr>
    <td>
      <b><p>Change password e-mail sent.</b><br><br>
      <li>User Name: <b class="red"><?=$username?></b></li>
      <li>E-mail address: <b class="red"><?=$email?></b>.</li>
      <br><br><br>
      <p>The user will receive the email which contains a link for them to reset a new password.</p>
      <br>
      <input type="button" class="beigebutton" value="Back to Members Profile" onClick="javascript:location.href='showmember.php?aauserID=<?=$_SESSION[aauserID]?>'">
    </td>
  </tr>
</table>
</body>
</html>