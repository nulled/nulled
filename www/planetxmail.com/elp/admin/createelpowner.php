<?php
include("adminsecure/session/sessionsecureadmin.inc");
include("adminsecure/createelpowner.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table width="300" cellspacing="0" cellpadding="5" align="center" border="1">
  <tr>
    <td align="center">
      <h4>Create a New ELP Owner Account</h4>
      <center><font color="red"><b><?=$notValid?></b></font></center><br>
      <form name="createelpowner" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <b>ELP Owner Name:</b><br>
      <input type="text" name="theelpownername" value="<?=$theelpownername?>" size="25">
      <br>
      <br>
      <b>Real First Name:</b><br>
      <input type="text" name="fname" value="<?=$fname?>" size="25">
      <br>
      <br>
      <b>Real Last Name:</b><br>
      <input type="text" name="lname" value="<?=$lname?>" size="25">
      <br>
      <br>
      <b>ELP Owner Email Address:</b><br>
      <input type="text" name="adminemail" value="<?=$adminemail?>" size="25">
      <br>
      <br>
      <b>Price for EXE:</b><br>
      $<input type="text" name="price" value="<?php if (! $price) echo "47"; else echo $price; ?>" size="3">
      <br>
      <br>
      <b>Commission for EXE:</b><br>
      $<input type="text" name="commission" value="<?php if (! $commission) echo "20"; else echo $commission; ?>" size="3">
      <br>
      <br>
      <b>Price for monthly:</b><br>
      $<input type="text" name="monthlyprice" value="<?php if (! $monthlyprice) echo "20"; else echo $monthlyprice; ?>" size="3">
      <br>
      <br>
      <b>Commission for monthly:</b><br>
      $<input type="text" name="monthlycommission" value="<?php if (! $monthlycommission) echo "5"; else echo $monthlycommission; ?>" size="3">
      <br>
      <br>
      <input type="hidden" name="submitted" value="create">
      <input type="submit" class="greenbutton" value="Create ELP Owner">
      <input type="button" value="Log Off" class="beigebutton" onClick="javascript:location.href='logout.php'">
      </form>
    </td>
  </tr>
</table>
</body>
</html>

