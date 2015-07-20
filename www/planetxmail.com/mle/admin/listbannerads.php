<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/listbannerads.inc");
?>
<html>
<head>
<title><?=$program_name?> - List Personalized AD Banners</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table align="center" width="500" cellspacing="2" cellpadding="5" border="0">
  <tr>
    <td align="center">
      <h4>List of Rotating Ad Banners</h4>
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
          echo "<a href=\"editbannerads.php?bannerID=$row[0]\"><img src=\"$row[1]\" border=\"0\"></a><br><br>\n";
        }
        if (mysqli_num_rows($banners)==0)
        {
          echo "<b>No personalized banners to edit.</b>\n";
        }
      ?>
      <br><br>
      <input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>';">
    </td>
  </tr>
</table>
</body>
</html>
