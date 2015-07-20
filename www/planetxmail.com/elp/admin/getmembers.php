<?php
include("adminsecure/session/sessionsecureadmin.inc");
include("adminsecure/getmembers.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Get Members</title>
<link rel="stylesheet" type="text/css" href="../css_elp.css" />
</head>
<body>
<table border="0" cellspacing="2" cellpadding="3" align="center" width="600">
  <tr>
    <td colspan="6" align="center"><h3>Member IP summary For ELP Partner: <font color="red"><?=$o?></font></h3></td>
  </tr>
  <tr>
    <td bgcolor="lightblue"><b>User Name:</b></td>
    <td bgcolor="lightblue"><b>First:</b></td>
    <td bgcolor="lightblue"><b>Last:</b></td>
    <td bgcolor="lightblue"><b>Email:</b></td>
    <td align="center" bgcolor="lightblue"><b>Blocked?</b></td>
    <td align="center" bgcolor="lightblue"><b>IPs</b></td>
  </tr>
  <?php
    $i = 0;
    while(list($uname, $fname, $lname, $email, $blocked, $numIPs) = mysqli_fetch_row($udata))
    {
      echo "<tr>\n<td bgcolor=\"beige\">$uname</a></td>\n";
      echo "<td bgcolor=\"beige\">$fname</td>\n";
      echo "<td bgcolor=\"beige\">$lname</td>\n";
      echo "<td bgcolor=\"beige\">$email</td>\n";

      if ($blocked)
        $blocked = "Yes";
      else
        $blocked = "No";

      echo "<td align=\"center\" bgcolor=\"beige\">$blocked</td>\n";
      echo "<td align=\"center\" bgcolor=\"$alertLevel[$i]\"><a href=\"getipaddresses.php?u=$uname&o=$o\">$ipCount[$i]</a></td>\n</tr>\n";

      $i++;
    }
  ?>
  <tr>
    <td colspan="6" align="center"><br><input type="button" value="Back to Sys Summary" class="beigebutton" onClick="javascript:location.href='getsyssummary.php'">&nbsp;&nbsp;&nbsp;&nbsp;<input type="button" value="Back to Main Menu" class="beigebutton" onClick="javascript:location.href='main.php'"></td>
  </tr>
</table>
</body>
<html>

        