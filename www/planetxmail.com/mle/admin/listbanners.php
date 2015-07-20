<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/listbanners.inc");
?>
<html>
<head>
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table align="center" width="500" cellspacing="2" cellpadding="5" border="0">
  <tr>
    <td align="center">
      <h4>List of Banners</h4>
      These banners will appear after a member sends their AD.
      <br><br>
      Click on the banner to edit its properties.
      <hr>
      <font color="red"><b><?php if ($notValid) echo "$notValid<br><br>"; ?></b></font>
    </td>
  </tr>
  <tr>
    <td align="center">
      <?php
        while ($row = mysqli_fetch_row($banners))
        {
          echo "<a href=\"editbanners.php?bannerID=$row[0]\"><img src=\"$row[1]\" border=\"0\"></a><br><br>\n";
        }
        if (mysqli_num_rows($banners)==0)
        {
          echo "<b>No banners to edit.</b>\n";
        }
      ?>
      <br><br>
      <input type="button" value="Back To Main" class="beigebutton" onClick="javascript:location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
    </td>
  </tr>
</table>
</body>
</html>