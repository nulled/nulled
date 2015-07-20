<html>
<head>
<title>Ezy-List Pro - ELP Owner Thank You</title>
<link rel="stylesheet" type="text/css" href="css_elp.css" />
<script language="javascript">
<!--
if (self != top) top.location.href = window.location.href;
//-->
</script>
</head>
<body>
<table width="500" align="center" border="0">
  <tr>
  	<td align="center">
  		<img src="images/elplogo.jpg">
  		<hr>
  		<?php
				include("elpsecure/elpownerthankyou.inc");
				if ($good)
				{
					echo "<font size=\"+1\"><b>$fname $lname,</b></font><br><br>\n";
		  		echo "Thank you for your payment of \$ <b>$amountpaid</b> USD.\n";
		  		echo "<br><br>\n";
		  		echo "Your records have been updated.\n";
		  	}
			?>
  	</td>
  </td>
 </table>
 </body>
 </html>
  		