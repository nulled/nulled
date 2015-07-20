<?php
include("adminsecure/session/sessionsecureadmin.inc");
include("adminsecure/getsyssummary.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
<meta http-equiv="refresh" content="1000;URL=getsyssummary.php">
</head>
<body>
<table border="0" cellspacing="2" cellpadding="3" align="center" width="600">
  <tr>
    <td colspan="9" align="center"><h3>ELP System Summary</h3></td>
  </tr>
  <tr>
    <td bgcolor="lightblue"><b>ELP Name:</b></td>
    <td bgcolor="lightblue"><b>First:</b></td>
    <td bgcolor="lightblue"><b>Last:</b></td>
    <td bgcolor="lightblue"><b>Email:</b></td>
    <td bgcolor="lightblue"><b>Signup/Owed:</b></td>
    <td bgcolor="lightblue"><b>Monthly/Owed:</b></td>
    <td bgcolor="lightblue"><b>Blocked?</b></td>
    <td bgcolor="lightblue"><b>Mems:</b></td>
    <td bgcolor="lightblue"><b>Unver Mems:</b></td>
  </tr>
  <tr>
    <?php
      $i = 0;
      while(list($oname, $fname, $lname, $email, $price, $monthlyprice, $commission, $monthlycommission, $blocked) = mysqli_fetch_row($odata))
      {
        echo "<td bgcolor=\"beige\"><a href=\"getmembers.php?o=$oname\">$oname</a></td>\n";
        echo "<td bgcolor=\"beige\">$fname</td>\n";
        echo "<td bgcolor=\"beige\">$lname</td>\n";
        echo "<td bgcolor=\"beige\">$email</td>\n";
        echo "<td bgcolor=\"beige\">$price/$monthlyprice</td>\n";
        echo "<td bgcolor=\"beige\">$commission/$monthlycommission</td>\n";

        if ($blocked)
          $blocked = "Yes";
        else
          $blocked = "No";

        echo "<td bgcolor=\"beige\">$blocked</td>\n";
        echo "<td bgcolor=\"$alertLevel[$i]\">$numMem[$i]</td>\n";
        echo "<td bgcolor=\"beige\">$numUnver[$i]</td>\n</tr>\n";

        $i++;
        $totalMem += $numMem[$i];
        $totalUnverMem += $numUnver[$i];
      }
    ?>
  </tr>
  <tr>
    <td colspan="7" align="right"><b>Totals:</b></td>
    <td bgcolor="yellow"><b><?=$totalMem?></b></td>
    <td bgcolor="yellow"><b><?=$totalUnverMem?></b></td>
  </tr>
  <tr>
    <td colspan="9" align="center"><br><input type="button" value="Back to Main Menu" class="beigebutton" onClick="javascript:location.href='main.php'"></td>
  </tr>
</table>
</body>
<html>