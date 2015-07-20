<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');

if (! isset($classloaded_MySQL_Access))
{
  $classloaded_MySQL_Access = 1;

  require_once('/home/nulled/config.inc');
}

// place outside the check include because phpsecure/classes.inc may be set...
$ads_ads_ads = '
<center>
  <hr /><br />
  <a href="http://planetxmail.com/soloads.php?list=[location]" target="_blank">Send a SOLO AD to 135,000+ members!</a>
  <br /><br  >

  <a href="http://targetedadplanet.com" target="_blank">
    <img src="http://targetedadplanet.com/images/tap_mini.jpg" border="0" />
    <br />
    <i>100% Free ADs - 50% Commission Payouts</i>
  </a>
</center>
';

?>
