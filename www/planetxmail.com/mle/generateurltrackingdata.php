<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');

$db = new MySQL_Access();

if ($mode=="all")
  $db->Query("SELECT ipaddress FROM urldata WHERE userID='$uID' AND name='$tracker' ORDER BY ipaddress");
else
{
  if ($mode=="year")  $db->Query("SELECT ipaddress FROM urldata WHERE userID='$uID' AND name='$tracker' AND ($mletime - 29030400) <= UNIX_TIMESTAMP(hitdate) ORDER BY ipaddress");
  if ($mode=="month") $db->Query("SELECT ipaddress FROM urldata WHERE userID='$uID' AND name='$tracker' AND ($mletime - 2419200) <= UNIX_TIMESTAMP(hitdate) ORDER BY ipaddress");
  if ($mode=="week")  $db->Query("SELECT ipaddress FROM urldata WHERE userID='$uID' AND name='$tracker' AND ($mletime - 604800) <= UNIX_TIMESTAMP(hitdate) ORDER BY ipaddress");
  if ($mode=="day")   $db->Query("SELECT ipaddress FROM urldata WHERE userID='$uID' AND name='$tracker' AND ($mletime - 86400) <= UNIX_TIMESTAMP(hitdate) ORDER BY ipaddress");
  if ($mode=="hour")  $db->Query("SELECT ipaddress FROM urldata WHERE userID='$uID' AND name='$tracker' AND ($mletime - 3600) <= UNIX_TIMESTAMP(hitdate) ORDER BY ipaddress");
}

$ipprev = "";
$unique = 0;
$total = $db->rows;
while (list($ipaddress) = $db->FetchRow())
{
  if ($ipaddress!=$ipprev)
    $unique++;

  $ipprev = $ipaddress;
}

?>
<html>
<head>
<title>Url Tracking Statistics</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<body bgcolor="#FFFFFF">
<table width="300" border="0" cellspacing="0" cellpadding="5">
  <tr>
    <?php
      if ($mode=="all")
        $title = "Summary of all hits from begin date.";
      else if ($mode=="year")
        $title = "Summary of all hits from the past year.";
      else if ($mode=="month")
        $title = "Summary of all hits from the past month.";
      else if ($mode=="week")
        $title = "Summary of all hits from the past week.";
      else if ($mode=="day")
        $title = "Summary of all hits from the past day.";
      else if ($mode=="hour")
        $title = "Summary of all hits from the past hour.";

      echo "<td><b>".$title."</b><hr><br><b>Hits:</b><table border=\"1\" cellpadding=\"5\" cellspacing=\"1\"><tr><td bgcolor=\"#EDEDED\">Unique Hits</td><td bgcolor=\"#EDEDED\">Total Hits</td></tr>\n";
      echo "    <tr><td bgcolor=\"beige\">".$unique."</td><td bgcolor=\"beige\">".$total."</td></tr></table></td></tr></table></td>\n";

    ?>
  </tr>
  <tr>
  	<td align="center">
  		<?php if ($bannerIMG) echo "<br><br><a href=\"$bannerLINK\" target=\"_blank\"><img src=\"admin/$bannerIMG\" border=\"0\"></a>\n"; ?>
		</td>
	</tr>
</table>
</body>
</html>
