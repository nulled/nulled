<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("../mlpsecure/config/classes.inc");
include("../mlpsecure/config/config.inc");
include("adminsecure/searchresults.inc");
?>
<html>
<head>
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table style="border-left: solid 1px #000000;border-bottom: solid 1px #000000;border-top: solid 1px #000000;border-right: solid 1px #000000;" align="center" cellpadding="3" cellspacing="1" border="0" width="500">
  <tr>
    <td align="left">
    	<center><h3>Search came up with <?=$numMatches?> Result(s)</h3></center>
      <?php
      	for ($i=0; $i<count($userMatches); $i++)
      	{
      		$uname = $userMatches[$i][0];
					$fname = $userMatches[$i][1];
					$lname = $userMatches[$i][2];
					$uID 	 = $userMatches[$i][3];

      		echo "<b>Name:</b> <a href=showmember.php?user=$uID>$fname $lname</a> - <b>Username:</b> <a href=showmember.php?user=$uID>$uname</a><br><br>\n";
      	}
      ?>
      <hr>
      <center>
      <input type="button" value="Back to Main Menu" class="beigebutton" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
      </center>
    </td>
  </tr>
</body>
</html>