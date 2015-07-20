<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/soloadthankyou.inc');
?>
<head>
<title>Solo Ads Thank you</title>
<link rel="stylesheet" type="text/css" href="x.css" />
</head>
<body background="images/solo_ad_bg.jpg">
<table align="center">
  <tr>
    <td align="center"><img src="images/solo_ad_title.jpg">
      <br>
      <h3>Thank you for your SOLO AD order</h3>
      Your AD will be sent to our networks and Safelists within minutes.
<?php

if ($h AND ! stristr($notValid, "ERROR:"))
{
  echo '
      <br /><br />
      Please <b>copy the link below and save it</b> as your Receipt and to track your AD\'s progress through our system.
      <br />
      <input type="text" name="link" value="http://planetxmail.com/sastatus.php?v=' . $id . '&h=' . $h . '" size="55" READONLY>
      <br /><br />
      <a href="http://planetxmail.com/sastatus.php?v=' . $id . '&h=' . $h . '" target="_BLANK">Click here to view</a>
      ';
}

?>
      <br />
      <div style="text-align: left">
        <ul>
          <li>Over 150+ <b>List Owners</b>.</li>
          <li>Over 250+ <b>Safelists</b>.</li>
          <li>Over 135,000+ <b>active members</b>.</li>
        </ul>
      </div>
      <?php
        // echo str_replace('[location]', 'soloadthankyou', $ads_ads_ads);
      ?>
    </td>
  </tr>
</table>
</body>
</html>
