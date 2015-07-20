<?php
function make_links($text, $myLink)
{
  $text = preg_replace(
     array(
       '/<a([^>]*)href="?[^"\']+"?/i',
       '/<a([^>]+)>/i'
       ),
     array(
       '<a\\1',
       '<a\\1 href="'.$myLink.'">'
       ),
       $text
   );

   $text = preg_replace(
     array(
       '/<a([^>]*) target="?[^"\']+"?/i',
       '/<a([^>]+)>/i'
       ),
     array(
       '<a\\1',
       '<a\\1 target="_blank">'
       ),
       $text
   );

   return preg_replace(
     array(
       '/<form([^>]*) action="?[^"\']+"?/i',
       '/<form([^>]+)>/i'
       ),
     array(
       '<form\\1',
       '<form\\1 action="'.$myLink.'">'
       ),
       $text
   );
}
function reltoabs($text, $base)
{
  if (substr($base, -1, 1) != '/') $base .= '/';

  // <link href=
  // $pattern = "/<link([^>]*) href=\"(?!http|ftp|https)([^\"]*)\"/i";
  // $replace = "<link\${1} href=\"" . $base . "\${2}\"";
  $pattern = "/href=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "href=\"" . $base . "\${1}\"";
  $text = preg_replace($pattern, $replace, $text);

  // <table background=
  $pattern = "/<table([^>]*) background=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "<table\${1} background=\"" . $base . "\${2}\"";
  $text = preg_replace($pattern, $replace, $text);

  // <td background=
  $pattern = "/<td([^>]*) background=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "<td\${1} background=\"" . $base . "\${2}\"";
  $text = preg_replace($pattern, $replace, $text);

  // <img src=
  $pattern = "/<img([^>]*) src=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "<img\${1} src=\"" . $base . "\${2}\"";
  $text = preg_replace($pattern, $replace, $text);

  // <applet code=
  $pattern = "/<applet([^>]*) code=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "<applet\${1} code=\"" . $base . "\${2}\"";
  $text = preg_replace($pattern, $replace, $text);

  return $text;
}

$hoplinks = $labelurl = $reseller = array();

$hoplinks[] = 'http://nulled.fullsoft.hop.clickbank.net';
$labelurl[] = 'Full Software Download';
$reseller[] = 'http://www.fullsoftwaredownload.com';

$hoplinks[] = 'http://nulled.surveysc.hop.clickbank.net';
$labelurl[] = 'Survey Scout';
$reseller[] = 'http://www.surveyscout.com';

$hoplinks[] = 'http://nulled.shop4pay.hop.clickbank.net';
$labelurl[] = 'Shop 4 Pay';
$reseller[] = 'http://www.shoppingjobshere.com';

$hoplinks[] = 'http://nulled.regfix.hop.clickbank.net';
$labelurl[] = 'Registry Fix';
$reseller[] = 'http://www.registryfix.com';

$hoplinks[] = 'http://nulled.xoftspyse.hop.clickbank.net';
$labelurl[] = 'Revenue Wire';
$reseller[] = 'http://www.revenuewire.net';

$hoplinks[] = 'http://nulled.regsweep.hop.clickbank.net';
$labelurl[] = 'Registry Sweep';
$reseller[] = 'http://www.regsweep.com';

$hoplinks[] = 'http://nulled.noadware.hop.clickbank.net';
$labelurl[] = 'No Adware';
$reseller[] = 'http://www.noadware.net';

$hoplinks[] = 'http://nulled.shopuyd.hop.clickbank.net';
$labelurl[] = 'Earn Money';
$reseller[] = 'http://cashflowjoe.com';

$hoplinks[] = 'http://nulled.macrovirus.hop.clickbank.net';
$labelurl[] = 'Money Online Maker';
$reseller[] = 'http://cbadvance.com';

$hoplinks[] = 'http://nulled.imarichkid.hop.clickbank.net';
$labelurl[] = 'Cash Vault';
$reseller[] = 'http://www.ultimatewealthpackage.com';

$hoplinks[] = 'http://nulled.googlecash.hop.clickbank.net';
$labelurl[] = 'Google Cash';
$reseller[] = 'http://www.affiliatejackpot.com';

$hoplinks[] = 'http://nulled.gcv2005.hop.clickbank.net';
$labelurl[] = 'Instant Cash';
$reseller[] = 'http://www.affiliatecashvault.com';

$hoplinks[] = 'http://nulled.bfmscript.hop.clickbank.net';
$labelurl[] = 'Cash Manuscript';
$reseller[] = 'http://www.thebutterflymarketingmanuscript.com';

$hoplinks[] = 'http://nulled.richjerk.hop.clickbank.net';
$labelurl[] = 'Rich Jerk';
$reseller[] = 'http://www.therichjerk.com';

$hoplinks[] = 'http://nulled.legitonl.hop.clickbank.net';
$labelurl[] = 'Legal Online Jobs';
$reseller[] = 'http://www.legitonlinejobs.com';

$hoplinks[] = 'http://nulled.awmiracle.hop.clickbank.net';
$labelurl[] = 'AD Words Miracle';
$reseller[] = 'http://www.adwordsmiracle.com';

$hoplinks[] = 'http://nulled.bryxen1.hop.clickbank.net';
$labelurl[] = 'Search Engine Domination';
$reseller[] = 'http://www.seoelite.com';

$hoplinks[] = 'http://nulled.bryxen2.hop.clickbank.net';
$labelurl[] = 'Press Release';
$reseller[] = 'http://www.pressreleasefire.com';

$hoplinks[] = 'http://nulled.bryxen3.hop.clickbank.net';
$labelurl[] = 'Fool-Proof Weight Loss';
$reseller[] = 'http://www.dietplannerplus.com';

$hoplinks[] = 'http://nulled.bryxen4.hop.clickbank.net';
$labelurl[] = 'AD Sense Keywords';
$reseller[] = 'http://www.keywordelite.com/index2.htm';

$hoplinks[] = 'http://nulled.ipoddl.hop.clickbank.net';
$labelurl[] = 'Unlimited iPod Downloads';
$reseller[] = 'http://www.myipodownloads.com';

$hoplinks[] = 'http://nulled.sharedm.hop.clickbank.net';
$labelurl[] = 'Share Movies';
$reseller[] = 'http://sharedmovies.com';

$hoplinks[] = 'http://nulled.movadvance.hop.clickbank.net';
$labelurl[] = 'Movie Downloads';
$reseller[] = 'http://www.movieadvanced.com';

$hoplinks[] = 'http://nulled.cauction.hop.clickbank.net';
$labelurl[] = 'Car Auction';
$reseller[] = 'http://www.car-auction.com';

if (is_numeric($c) === false || $hoplinks[$c] == '')
  $c = 0;
else
{
  if ($data = @file_get_contents($reseller[$c]))
  {
    $data = make_links($data, $hoplinks[$c]);

    // check if points to a page or directly to domain
    if (count(explode('/', $reseller[$c])) > 3)
      $reseller = dirname($reseller[$c]);
    else
      $reseller = $reseller[$c];

    $data = reltoabs($data, $reseller);
    exit($data);
  }
  else
    exit('invalid id');
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>Wonder Sites</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<script>
var loading_txt = '<br /><br /><br /><h1><center>Loading Page...</center></h1>';
function createXMLHttpRequest()
{
  try { return new ActiveXObject("Msxml2.XMLHTTP"); } catch (e) {}
  try { return new ActiveXObject("Microsoft.XMLHTTP"); } catch (e) {}
  try { return new XMLHttpRequest(); } catch (e) {}
  alert('XMLHttpRequest not supported.');
  return null;
}
function $(id)
{
  return document.getElementById(id);
}
function submitPage(page)
{
  var xhr = createXMLHttpRequest();
  xhr.onreadystatechange = function()
  {
    if (xhr.readyState==4)
    {
      if (xhr.status==200)
      {
        var rt = xhr.responseText;
        $('progress').className = 'notWaiting';
        $('results').innerHTML = rt;
      }
      else
        alert('An error occured.');
    }
  }
  xhr.open('GET', page, true);
  xhr.send(null);
}
</script>
<style type="text/css">
<!--
body {
margin: 0;
padding:0;
position: absolute;
width: 100%;
height: 100%;
font-family: verdana, arial, sans-serif;
}
.heading {
width: auto;
height: 30px;
background-color: white;
color: black;
font-size: 28px;
padding: 10px;
text-align: center;
}
.content {
height: 338px;
width: 100%;
}
.menu {
position: absolute;
left: 0;
width: 180px;
height: 600px;
background-color: white;
color: black;
font-size: 12px;
}
.frame {
width: auto;
margin-left: 180px;
height: 600px;
overflow: auto;
font-size: 14px;
}
ul, li {margin: 0; padding: 0; list-style-type: none;}
ul {float: left; margin-top: 10px; margin-left: 10px;}
.waiting {
  visibility: visible;
}
.notWaiting {
  visibility: hidden;
}
-->
</style>
</head>

<body onload="<?php if ($c == 0) echo "javascript:submitPage('wondersites.php?c=0')"; ?>">

<div class="heading">Featured Site is shown below:<img id="progress" src="images/ajax-loader.gif" class="notWaiting" border="0" /></div>

<div class="content">
  <div class="menu">
    <br />
    <b><u>Control&nbsp;+&nbsp;D</u></b>&nbsp;to&nbsp;Bookmark&nbsp;page.
    <br /><br />
    <font color="red"><b>Click the Links Below<br />to view on the Right.</a></font>
    <br />

  	<ul>

<?php

    for ($i=0; $i < count($hoplinks); $i++)
      echo '<li><a href="javascript:void(0)" class="a_class" onclick="javascript:$(\'progress\').className=\'waiting\';$(\'results\').innerHTML=loading_txt;submitPage(\'wondersites.php?c='.$i.'\');">'.str_replace(' ', '&nbsp;', $labelurl[$i]).'</a></li>'."\n";

?>

  	</ul>
    <br /><br />
  	<b>All of these sites have been<br /><u>tested</u> and <u>proven</u> to work.</b>

  </div>

  <div class="frame">
    <div id="results"></div>
  </div>

</div>

</body>
</html>

