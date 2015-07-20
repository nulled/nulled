<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/sastatus.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title>Planet X Mail - Solo AD Status</title>
<style type="text/css">
a:link { color: #000; text-decoration: none; }
a:visited { color: #000; text-decoration: none; }
a:hover { color: #FF0000; text-decoration: underline; }
a:active { color: #000; text-decoration: none; }

body {
  font-family: verdana;
  font-size: 12px;
  margin: 15px 0;
  padding 0;
  text-align: center;
  background-image: url('images/sun30.jpg');
  background-repeat: no-repeat;
  background-attachment: scroll;
  background-position: center;
}

.main {
  margin: 0 auto;
  width: 700px;
  border: 1px solid #BFBFBF;
  padding: 5px;
  text-align: left;
  border-radius: 7px;
}

.heading {
  font-size: 20px;
  font-weight: bold;
  text-align: center;
}

.footer {
  margin: 15px 0;
  font-size: 10px;
  text-align: center;
}

b {
  font-size: 14px;
}
</style>
</head>
<body>

<div class="main">

  <h2 class="heading">
    <img src="/mle/images/pxm_title.jpg" border="0" />
    <br />
    SOLO AD Status: <font color="red"><b><?=$notValid?></b></font>
  </h2>

	<b><?=$datesubmitted?></b> Date Submitted <i>Eastern Time</i>
	<br />
	<b><?=$datemailed?></b> Date that Mailing was Completed

	<br /><br /><br />

  <b>Credit URL:</b>
  <pre>
  <?=$crediturl?>
  </pre>
  <br />

  <b>Subject:</b>
  <pre>
  <?=stripslashes($subject)?>
  </pre>
  <br />

  <b>Body:</b>
  <?=(strstr($type, 'HTMLSOLOAD')) ? '<div>' : '<pre>';?>
  <?=wordwrap(stripslashes($message), 70)?>
  <?=(strstr($type, 'HTMLSOLOAD')) ? '</div>' : '</pre>';?>

  <hr />

  <div class="footer">
    <a href="/" target="_blank">Planet X Mail</a> -
    All Rights Reserved &copy; 2001 - <?=date('Y')?> -
    <a href="openticket.php" target="_blank">Open Support Ticket</a>
  </div>

</div>
</body>
</html>