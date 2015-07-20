<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/soloadpaylinks.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title>Planet X Mail - SOLO AD PayLinks</title>
<link rel="stylesheet" type="text/css" href="x.css" />
<style>
body {
  background-image: url('images/<?=$bg?>');
  background-repeat: no-repeat;
  background-attachment: scroll;
  background-position: center;
  margin: 20px auto;
}
table, td {
  border: 1px solid #cccccc;
  padding: 5px;
  border-radius: 10px;
}
.or {
  font-size: 16px;
  font-weight: bold;
}
</style>
</head>
<?php flush(); ?>
<body>
<table align="center" width="640">

  <tr>
    <td colspan="2" align="center">
      <img src="images/<?=$img?>">
      <br />
      <b>Your AD will not be delivered until payment is received.</b>
    </td>
  </tr>

  <tr>
    <td width="50%" valign="top" align="left">
       <b>Your Solo Ad will <i>also</i> be mailed to <b>all</b> freeadplanet.com and targetedadplanet.com Members!</b>
       Free Ad Planet is another very active site totalling over <i>50,000 active members!</i> Now your Solo AD just got twice the lead
       generating power!
       <a href="http://freeadplanet.com" target="_blank">Click to visit Free Ad Planet.com</a> and decide for yourself.
    </td>
    <td align="left" valign="top">
      <font size="1">Stats queried <i>directly</i> from our database.</font>
      <ul>
        <li><?=$totalowners?> <b>List Owners</b>.</li>
        <li><?=$totallists?> <b>SafeLists</b>.</li>
        <li><?=$totalmembers?> <b>Active members</b>.</li>
      </ul>
      Since <i>October 2001</i> we are still growing strong!
    </td>
  </tr>

  <tr>
    <td valign="top" align="center" colspan="2">
      <b>Mailed to <font color="red"><u><b>Contact</b></u> Address</b></font>

      <br /><br />
      <div style="text-decoration: line-through">
       &nbsp;&nbsp;<b>Normally $59</b>&nbsp;&nbsp;
      </div>

      <br />
      <font size="+1" color="green"><b>Special Offer, <i>Only</i> $30</b> - 50% Off - Limited Time</font>
    </td>
  </tr>

  <tr>
    <td colspan="2">
      <br />
      <font color="red">Remember!</font> <u>Your</u> Solo AD will contain <u>Earnable Credit Links</u> which Direct Traffic to the website you specified.
      People earn 5 times the amount of credits normally earned, so <b>many seek out SOLO ADs</b> for this reason. Also, anytime a SafeList Member mails
      out their own Ads, the after page will display in full view <b>Your Website!</b>  We also showcase your Website on our <b>Link Exchange</b> and other various
      locations in and around out Vast SafeList Network!
      <br />

      <center>
        <h3>Choose Your Merchant</h3>
      </center>

      Merchants must own permits to handle Credit Cards or other Banking Details.  We are never given access to Your Personal Details.
      All the Merchants we use are Popular and take <b>Internet Security Seriously</b>. They have to, or they go out of Business very Quickly.
    </td>
  </tr>

  <?=$payforms?>

  <tr>
    <td valign="top" align="center" colspan="2">
      <br /><br />
      <b>Note:</b> We limit the number of ClickBank and 2Checkout orders we accept per day. If you find one or both of those payment options
      <i>missing</i>, please select Payza or Bitcoin.
    </td>
  </tr>

  <tr>
    <td align="center" valign="top" colspan="2">
      <i>Trusted</i> by the Internet Marketing Community, since July 2001.
      <br />
      All Rights Reserved &copy; 2001-<?php echo date('Y'); ?>
    </td>
  </tr>

</table>
</body>
</html>