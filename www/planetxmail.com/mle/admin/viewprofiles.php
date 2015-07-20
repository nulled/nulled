<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecurelistowner.inc');
require_once('/home/nulled/www/planetxmail.com/mle/admin/adminsecure/viewprofiles.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<style>
.atable {
  border: 1px solid #000000;
}
</style>
</head>
<body>
<table class="atable" align="center" cellpadding="3" cellspacing="0" border="0" width="500">
  <tr>
    <td align="center">
      <img src="../images/title.gif" border="0" />
      <hr>
    </td>
  </tr>
  <tr>
    <td background="../images/profiles_bg_twirl.jpg" align="center">
      <font size="3"><b>Ordered by status.</b></font><br>
      <h4>List Owner: <b class="red"><i><?php echo $_SESSION['aalistownername'] . "</i></b><br />\n";

      echo 'List Name: <b class="red"><i>' . $_SESSION['aalistname'] . '</i></b></h4>';

      echo 'Total members for all status: <b>' . $totalAll . '</b><br /><br />';

      if ($memNum)
      {
        echo '
        <form action="showmember.php" method="POST">
        <font size="+1"><b>Free Member:</b></font><select name="user" size="1">
        ';
        while ($row = mysqli_fetch_array($memData))
          echo '<option value="' . $row['userID'] . '">' . $row['username'] . '</option>
          ';
        echo '</select>
              <input type="submit" class="greenbutton" value="Get Profile">&nbsp;&nbsp;' . $memNum .
              '<input type="hidden" name="submitted" value="getprofile"></form>
              ';
      }
      else
        echo '<b><font size="+1">Free Member:</font></b><i>None</i><br />';

      if ($proNum)
      {
        echo '
        <form action="showmember.php" method="POST">
        <font size="+1"><b>Professional Member:</b></font><select name="user" size="1">
        ';
        while ($row = mysqli_fetch_array($proData))
          echo '<option value="' . $row['userID'] . '">' . $row['username'] . '</option>
          ';
        echo '</select>
              <input type="submit" class="greenbutton" value="Get Profile">&nbsp;&nbsp;' . $proNum .
              '<input type="hidden" name="submitted" value="getprofile"></form>
              ';
      }
      else
        echo '<b><font size="+1">Professional:</font></b><i>None</i><br />
             ';

      if ($exeNum)
      {
        echo '
        <form action="showmember.php" method="POST">
        <font size="+1"><b>Executive Member:</b></font><select name="user" size="1">
        ';
        while ($row = mysqli_fetch_array($exeData))
          echo '<option value="' . $row['userID'] . '">' . $row['username'] . '</option>
          ';
        echo '</select>
              <input type="submit" class="greenbutton" value="Get Profile" />&nbsp;&nbsp;' . $exeNum .
              '<input type="hidden" name="submitted" value="getprofile" /></form>
              ';
      }
      else
        echo '<font size="+1"><b>Executive:</b></font><i>None</i><br />
             ';

      if ($unvNum)
      {
        echo '<form action="showmember.php" method="POST">
              <font size="+1"><b>Unverified:</b></font><select name="user" size="1">
              ';
        while ($row = mysqli_fetch_array($unvData))
          echo '<option value="' . $row['userID'] . '">"' . $row['username'] . '"</option>
               ';
        echo '</select>
              <input type="button" class="redbutton" value="Delete" onClick="javascript: if (confirm(\'Are you sure you want to delete?\')) this.form.submit();">&nbsp;&nbsp;' . $unvNum . '
              <input type="hidden" name="submitted" value="deleteunverifiedmember"></form>
              ';
      }
      else
        echo '<font size="+1"><b>Unverified:</b></font><i>None</i>
             ';

      ?>

      <p>
        Unverified members will be AUTOMATICALLY re-mailed the confirmation link everyday until the 3rd day. After that, the Unverified will be deleted automatically.<br>
      </p>
      <br><br>
      <input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION['aaadminpsk']) echo 'main.php'; else echo 'mainlistowner.php'; ?>';">
    </td>
  </tr>
</table>
</body>
</html>

?>