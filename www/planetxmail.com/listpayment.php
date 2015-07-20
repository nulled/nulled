<?php
require_once('phpsecure/listpayment.inc');
?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Planet X Mail - List Re-Newal payment</title>
<link rel="stylesheet" type="text/css" href="x.css" />
</head>
<body>
<table cellspacing="0" cellpadding="0" width="600" border="0" align="center">
  <tr>
    <td align="center">
      <img src="http://planetxmail.com/images/title.jpg">
      <hr>
      <h4>This will re-new your list hosted with www.planetxmail.com</h4>
      <b><font color="red">Important note!</font></b> Make sure you COMPLETE the payment by clicking on the payment confirm complete links.
      You will know you have completed the pay process when you get to a Thank You page, from Planet X Mail.

      <hr />

      <b><font size="+1">Click Bank</font><br>Pay using any major credit card.</b>
      <br><br>
      Amount: $<?php echo $p; ?><br><br>
      <a href="<?php echo "http://{$cblink}.nulled.pay.clickbank.net?vtid={$id}O{$ex}"; ?>"><img src="images/cblogo.jpg" border="0" /></a>

      <br><br>
    </td>
  </tr>
  <tr>
    <td align="center" valign="top">
      <hr>
      <font size="-1">All Rights Reserved &copy;2001-<?php echo date('Y'); ?><br>Multi-List Enterprise - Planet X Mail<br>
      Contact: <a href="openticket.php">Planet X Mail Support</a></font>
    </td>
  </tr>
</table>
</body>
</html>
