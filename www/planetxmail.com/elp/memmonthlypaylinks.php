<?php
include("elpsecure/memmonthlypaylinks.inc");
?>
<html>
<head>
<title>Ezy-List Pro - Signup Paylinks</title>
<link rel="stylesheet" type="text/css" href="css_elp.css" />
<script language="javascript">
<!--
if (self != top) top.location.href = window.location.href;
//-->
</script>
</head>
<body>
<table width="513" align="center">
	<tr>
		<td colspan="2">
			<center><img src="images/elplogo.jpg"></center>
		</td>
	</tr>
	<tr>
	  <td colspan="2">
				<h4>Hi <?=$ufname?>, Monthly payment for your Ezy-List Pro account.</h4>
				Monthly Renewal Price: <b>$ <?=$monthlyprice?> USD</b>
				<br><br>
				That works out to a <i>mere</i> <?=$centsperday?> cents per day!
				<br><br>
				Ezy-List Pro will auto submit your Ad to all compatible safelists!  Saving you time and money!
		</td>
	</tr>
	<tr>
	  <td valign="top">
			<img src="images/elpbox.jpg">
		</td>
		<td>
		  <h4>Choose your method of payment.</h4>
		  <?=$monthlypaylinks?>
		</td>
	</tr>
</table>
</body>
</html>