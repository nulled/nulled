<?php
require_once('phpsecure/directadpaylinks.inc');
?>
<head>
<title>Direct Exposure AD PayLinks</title>
<link rel="stylesheet" type="text/css" href="x.css" />
</head>
<body background="images/directexposure_bg.jpg">
<table align="center" width="550">
  <tr>
    <td align="left">
      <center>
      <img src="images/directexposure_title.jpg">
      <h3>Choose your method of payment.</h3>
      </center>
      Your AD <b>will not</b> be displayed until payment is received.</b>
      <h4>Choose Number of Days to display your AD:</h4>
	    <select onChange="window.location.href=this.options[this.selectedIndex].value">
	    	<option value="directadpaylinks.php?id=<?=$id?>&numDays=1&page=<?=$page?>" <?php if ($numDays==1) echo "SELECTED" ?>>1 Day  - $15</option>
	    	<option value="directadpaylinks.php?id=<?=$id?>&numDays=2&page=<?=$page?>" <?php if ($numDays==2) echo "SELECTED" ?>>2 Days - $30</option>
	    	<option value="directadpaylinks.php?id=<?=$id?>&numDays=3&page=<?=$page?>" <?php if ($numDays==3) echo "SELECTED" ?>>3 Days - $40</option>
	    	<option value="directadpaylinks.php?id=<?=$id?>&numDays=4&page=<?=$page?>" <?php if ($numDays==4) echo "SELECTED" ?>>4 Days - $55</option>
	    </select> - <font color="red"><b>Wait for page to reload on each new selection.</b></font>

	    <h4>You AD will be displayed for <?=$numDays?> day(s).  Price: $ <?=$amount?></h4>
	    <center>

<!--
	<option value="directadpaylinks.php?id=<?=$id?>&numDays=5&page=<?=$page?>" <?php if ($numDays==5) echo "SELECTED" ?>>5 Days - $70</option>
	<option value="directadpaylinks.php?id=<?=$id?>&numDays=6&page=<?=$page?>" <?php if ($numDays==6) echo "SELECTED" ?>>6 Days - $80</option>
	<option value="directadpaylinks.php?id=<?=$id?>&numDays=7&page=<?=$page?>" <?php if ($numDays==7) echo "SELECTED" ?>>7 Days - $90</option>
	<option value="directadpaylinks.php?id=<?=$id?>&numDays=8&page=<?=$page?>" <?php if ($numDays==8) echo "SELECTED" ?>>8 Days - $96</option>
	<option value="directadpaylinks.php?id=<?=$id?>&numDays=9&page=<?=$page?>" <?php if ($numDays==9) echo "SELECTED" ?>>9 Days - $98</option>
	<option value="directadpaylinks.php?id=<?=$id?>&numDays=10&page=<?=$page?>" <?php if ($numDays==10) echo "SELECTED" ?>>10 Days - $100</option>
-->
      <hr />

      <a href="<?php echo "http://{$cblink}.nulled.pay.clickbank.net?vtid={$id}O{$page}"; ?>">CLICK BANK<br />
        <img src="images/cblogo.jpg" border="0">
      </a>

      <br /><br /><br /><b>OR</b><br /><br /><br />

      <a href="https://www.payza.com/PayProcess.aspx?ap_purchasetype=Item&ap_merchant=accounts2%40pxmb.com&ap_itemname=Direct+AD+<?=$numDays?>+Days&ap_currency=USD&ap_returnurl=http%3a%2f%2fplanetxmail.com%2fdirectadthankyou.php&ap_quantity=1&ap_description=PlanetXMail_DirectAD_Days:<?=$numDays?>_id:<?=$id?>&ap_amount=<?=$amount?>&ap_cancelurl=http%3a%2f%2fplanetxmail.com%2fcancellorder.php&apc_1=<?=$id?>&apc_2=<?=$page?>">
        <img src="http://planetxmail.com/images/payza-checkout.png" border="0" />
      </a><br />
      <a href="http://www.payza.com/?102032" target="_blank">Get a Payza Account</a>

      <br /><hr />

      <font color="red"><b>Very Important!</b></font> - You need to click ALL the way to *MY* Thank you page after paying.  DO NOT
      close the browser at Click Banks Thank you page!  Your order WILL NOT be recorded until you see *MY* thank you page.

      <hr>
      Your Direct Exposure AD will be displayed within minutes of receipt. You will be emailed a receipt.
      </center>
    </td>
  </tr>
  <tr>
    <td align="center" valign="top">
      <br><font size="-1">All Rights Reserved &copy;2001-<?php echo date('Y'); ?><br>Multi-List Enterprise - Planet X Mail<br>
      Contact: <a href="openticket.php">SUPPORT</a></font>
    </td>
  </tr>
</table>
</body>
</html>