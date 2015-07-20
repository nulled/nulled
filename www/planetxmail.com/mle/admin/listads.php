<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/listads.inc");
?>
<html>
<head>
<title>Mulit-List Pro - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table align="center" border="0" width="500" cellspacing="2" cellpadding="5">
  <tr>
    <td>
      <center>
      <h4>List of Bill Board Ads</h4>
      These Bill Board Ads will appear after a member sends their AD.
      <br></center>
      <hr>
      <?php if ($notValid) echo "<center><b class=\"red\">$notValid</b></center><br>\n"; ?>
       <center><font color="#005F8C"><b>Posted Ads: <?=$numAds?></b></font></center>
       <?php
         if (mysqli_num_rows($ads)==0)
           echo "<center><h3>No Ads Created.</h3></center>\n";

         while ($row = mysqli_fetch_row($ads))
         {
           echo "<b>Title:</b> ".stripslashes($row[1])."<br>\n";
           echo "<b>Description:</b> ".stripslashes($row[4])."<br>\n";
           if ($row[3]!="none") echo "<img src=\"$row[3]\" border=\"0\"><br>\n";
           echo "<img src=\"../images/arrow.jpg\">&nbsp;&nbsp;<a href=\"editad.php?adID=$row[0]\"><b class=\"red\">Click Here To Edit</b></a><hr>\n";
         }
       ?>
       <br><br>
       <center><input type="button" class="beigebutton" value="Back to Main" onClick="javascript:location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'"></center>
    </td>
  </tr>
</table>
</body>
</html>
