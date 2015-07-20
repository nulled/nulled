<?php
include("elpsecure/memsignuppaylinks.inc");
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
		<td align="center" colspan="2"><img src="images/elplogo.jpg"></td>
	</tr>
	<tr>
		<td colspan="2">
			<hr>
				<center><h2>Hi <?=$ufname?> - Purchasing Ezy-List Pro.</h2>
				<h3>One time Sign up Fee</h3></center>
				Price: <b>$ <?=$price?></b> Setup and ELP program install.<br>
				Price: <b>$ <?=$monthlyprice?></b> First month of ELP service.</br>
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;----<br>
				Total: <b>$ <?=$total?></b> USD
				<br><br>
				Ezy-List Pro will auto submit your AD to ALL Safe-Lists!  In <b>ONE MOUSE CLICK</b>! Saving you <i>time</i> and <i>money</i>!
		</td>
	</tr>
	<tr>
	  <td valign="top">
			<img src="images/elpbox.jpg">
		</td>
		<td>
			<h4>Choose your method of payment.</h4>
		  <?=$signuppaylinks?>
		</td>
	</tr>
</table>
</body>
</html>