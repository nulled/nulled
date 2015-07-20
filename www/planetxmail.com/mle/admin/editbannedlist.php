<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/editbannedlist.inc");
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
          <td align="center">
            <font color="blue"><h4>Edit Banned List for List Name: <?=$_SESSION[aalistname]?></h4></font>
            <hr>
            <b class="red"><?php if ($notValid) echo "$notValid<br>" ?></b>
            <p>
            These email addresses are <b>banned</b> from being able to be used as a listmail address.  An address
            you add to the list that are already in use by a user will be denied further mailing privlidges.
            </p>
            <form name="bannedlist" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
            <select name="email" size="15">
            <?php
              while ($row = mysqli_fetch_row($bannedlist))
                echo "<option value=\"$row[0]\">$row[0]</option>\n";
            ?>
            </select><br>
            <input type="submit" class="redbutton" value="Delete Email">
            <input type="hidden" name="deleteemail" value="1">
            </form>
            <hr>
            <form name="addemail" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
            <b>Add Email address or domain.</b><br>
            <input type="text" name="email" size="35"><br>
            <input type="submit" class="greenbutton" value="Add Email">
            <input type="hidden" name="addemail" value="1">
            </form>
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