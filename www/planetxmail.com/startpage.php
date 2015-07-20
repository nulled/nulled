<?php

// alert me when my IP Address changes, so I can update
// fail2ban
// nginx me_only
// tcpwrappers

$ip_changed = false;
$current_ip = '50.159.62.87';

if ($current_ip != $_SERVER['REMOTE_ADDR'])
{
  $ip_changed = true;
  @mail('elitescripts2000@yahoo.com', 'IP Address Changed!', "IP address changed from: {$current_ip}\n\nto: {$_SERVER['REMOTE_ADDR']}");
}
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8" />
<title>Speed Dial</title>
<style type="text/css">
body {
  margin: 0;
  padding: 0;
  font-family: verdana, arial, helvetica, sans-serif;
  font-size: 12px;
}
a {
  color: #076DBC;
  text-decoration: none
}
a:hover {
  color: #000000;
  text-decoration: underline;
}
.container {
  margin: 10px auto;
  padding: 0;
  width: 400px;
}
.header {
  margin: 10px auto;
  text-align: center;
  font-size: 16px;
  font-weight: bolder;
}
.left_content,
.right_content {
  margin: 0;
  padding: 0;
  text-align: left;
}
.left_content {
  float: left;
}
.right_content {
  float: right;
}
.footer {
  clear: both;
}
.ipchanged {
  margin: 40px auto;
  text-align: center;
  padding: 10px;
  border: 1px solid red;
  background-color: pink;
  border-radius: 10px;
  width: 350px;
}
</style>
</head>
<?php flush(); ?>
<body>

<div class="container">

    <div class="header">
      Speed Dial CALL ADT (800)662-5378 
    </div>

    <a title='national debt' name="7839" rel="
 titleBgClr = #009; titleColor = #FFF; titleBold = 1;
 type = 3; size = L; title = 2;
" href="http://zfacts.com/p/318.html" id="zf26_1">national debt</a>
<script type="text/javascript">(function() { var s = document.createElement('script');
s.async = true; s.src = "http://zfacts.com/giz/G26/GND.php?id=1";
var x = document.getElementsByTagName('script')[0];
x.parentNode.insertBefore(s, x); })();</script>

    <?php if ($ip_changed) echo '<div class="ipchanged">IP Address has changed to: ' . $_SERVER['REMOTE_ADDR'] . '</div>'; ?>

    <div class="left_content">
      <a href="https://yahoo.com">Yahoo (Mail)</a><br /><br />
      <a href="https://startpage.com">Startpage (Search)</a><br /><br />
      <a href="https://planetxmail.com/3p1m4a5/">PXM (pma)</a><br /><br />
      <a href="https://planetxmail.com/tickets/main.php">PXM (Tickets)</a><br /><br />
      <a href="https://planetxmail.com/mail/">PXM (Mail)</a><br /><br />
      <a href="https://planetxmail.com/mle/admin/mleadminindexloginonly.php">PXM (List Management)</a><br /><br />
      <a href="https://planetxmail.com/tools/vnstat/">BandWidth</a><br /><br />
      <a href="https://planetxmail.com/tools/minimail/">MiniMail</a><br /><br />
      <a href="https://planetxmail.com/tools/apc.php">APC</a><br /><br />
      <a href="https://planetxmail.com/tools/phpinfo.php">PHPinfo</a><br /><br />
      <a href="https://planetxmail.com">PXM</a><br /><br />
      <a href="http://freeadplanet.com/?c=memberlogin">FAP</a><br /><br />
      <a href="http://targetedadplanet.com/?c=memberlogin">TAP</a><br /><br />
      <a href="https://google.com/analytics">Google Analytics</a><br /><br />
      <a href="https://quantcast.com/planetxmail.com">Quantcast</a><br /><br />
      <a href="https://youtube.com">Youtube</a><br /><br />
      <a href="https://planetxmail.com/mle/login.php?l=42ba8">PXM Safelist</a><br /><br />
    </div>

    <div class="right_content">
      <a href="https://www.nationstarmtg.com/MyAccount/Default.aspx/">Mortgage</a><br /><br />
      <a href="https://servicing.capitalone.com/c1/Login.aspx">HB Card</a><br /><br />
      <a href="https://wireless.att.com">A.T.T Wireless</a><br /><br />
      <a href="http://wm.com">Waste Management</a><br /><br />
      <a href="http://comcast.com">ComCast</a><br /><br />
      <a href="https://www.progressive.com/">Progressive</a><br /><br />
      <a href="http://www.lakehaven.org">Lake Haven</a><br /><br />
      <a href="https://mycheckfree.com/br/wps?sp=10001&rq=home&esc=41152601">Puget Sound Energy</a><br /><br />
      <a href="https://www.alaskausa.org">Alaska USA</a><br /><br />
      <a href="https://www.paypal.com">Paypal</a><br /><br />
      <a href="https://www.payza.com">Payza</a><br /><br />
      <a href="https://www.2checkout.com">2CheckOut</a><br /><br />
      <a href="https://www.clickbank.com">ClickBank</a><br /><br />
      <a href="http://10.0.0.1">Link Sys</a><br /><br />
    </div>

    <div class="footer"></div>
</div>

</body>
</html>
