<?php
include("elpsecure/memsignuplitepaylinks.inc");
?>
<html>
<head>
<title>Ezy-List LITE - Signup Paylinks</title>
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
		<td align="center" colspan="2"><img src="images/elllogo.jpg"></td>
	</tr>
	<tr>
		<td colspan="2">
			<hr>
				<center><h2>Hi <?=$ufname?> - Purchasing Ezy-List LITE.</h2>
				<h3>One time Sign up Fee</h3></center>
				Total: <b>$ <?=$pricelite?></b> USD
				<br><br>
				Ezy-List LITE will auto submit your AD to ALL Safe-Lists!  In <b>ONE MOUSE CLICK</b>! Saving you <i>time</i> and <i>money</i>!
		</td>
	</tr>
	<tr>
	  <td valign="top">
			<img src="images/ell_box.jpg">
		</td>
		<td>
			<h4>Choose your method of payment.</h4>
		  <?=$signuppaylinks?>
		</td>
	</tr>
</table>
</body>
</html>