<?php
function array_qsort2(&$array, $column=0, $order=SORT_ASC, $first=0, $last=-2)
{
  if($last == -2) $last = count($array) - 1;

  if($last > $first)
  {
    $alpha = $first;
    $omega = $last;
    $guess = strtolower($array[$alpha][$column]);

    while($omega >= $alpha)
    {
      if($order == SORT_ASC)
      {
        while(strtolower($array[$alpha][$column]) < $guess) $alpha++;
        while(strtolower($array[$omega][$column]) > $guess) $omega--;
      }
      else
      {
        while(strtolower($array[$alpha][$column]) > $guess) $alpha++;
        while(strtolower($array[$omega][$column]) < $guess) $omega--;
      }

      if($alpha > $omega) break;

      $temporary = $array[$alpha];
      $array[$alpha++] = $array[$omega];
      $array[$omega--] = $temporary;
    }

    array_qsort2($array, $column, $order, $first, $omega);
    array_qsort2($array, $column, $order, $alpha, $last);
  }
}

$filename = "/home/remote/in/scsi.info";

if ($fp = @fopen($filename, "rt"))
{
  $text = fread($fp, filesize($filename));
	fclose($fp);
}
else
{
	echo "ERROR: Unable to open file: $filename for reading.";
  exit;
}

$labels = array('ip','host','channel','id','lun','vendor','model','rev','type','ansi_rev');

$lines = explode("\n", $text);
$lines = array_map("trim", $lines);

for ($i=0; $i<count($lines); $i++)
{
	if (! $lines[$i]) continue;

	$parts = explode(" ", $lines[$i]);

	for ($j=0; $j<count($parts); $j++)
	{
		$segments = explode("=", $parts[$j]);
		$segments = array_map("trim", $segments);

		$disks["DISK_$i"][$labels[$j]] = $segments[1];
	}
}

// get IP addresses
for ($i=0; $i<count($disks); $i++)
{
	if ($prev==$disks["DISK_$i"]["ip"]) continue;

	$ipaddresses[] = $disks["DISK_$i"]["ip"];

	$prev = $disks["DISK_$i"]["ip"];
}

?>
<html>
<head>
<meta http-equiv="refresh" content="120; URL=<?=$PHP_SELF?>">
<title>Server Disk Status/Locations</title>
<link rel="stylesheet" type="text/css" href="x.css" />
</head>
<body>
<table border=0 width=400 cellpadding=3 cellspacing=1>
	<tr>
		<td colspan=2 align=center>
			<img src="http://205.252.89.252/images/ss.jpg">
		</td>
	</tr>
	<?php
		//IP=205.252.89.252 Host=scsi0 Channel=00 Id=05 Lun=00 Vendor=IBM Model=IC35L018UCPR15-0 Rev=S70H Type=Direct-Access ANSI_Rev=03

		for ($i=0, $scsi_inc=0; $i<count($ipaddresses); $i++, $scsi_inc=0)
		{
			$scsi = array();

			if ($ipaddresses[$i]=="205.252.89.252") { $server = "WEB"; $mc = "MC100891"; }
			else if ($ipaddresses[$i]=="205.252.89.253") { $server = "PXMM1"; $mc = "MC100892"; }
			else if ($ipaddresses[$i]=="205.252.89.254") { $server = "PXMBS2"; $mc = "MC100893"; }
			else if ($ipaddresses[$i]=="205.177.28.18") { $server = "HYG"; $mc = "MC100840"; }
			else if ($ipaddresses[$i]=="205.252.89.16") { $server = "PXMBS1"; $mc = "MC100681"; }

			echo "<tr><td colspan=2 align=center bgcolor=lightgrey><font size=2><b>$server</b>&nbsp;&nbsp;&nbsp;&nbsp;$ipaddresses[$i]&nbsp;&nbsp;&nbsp;&nbsp;$mc</font></td></tr>\n";

			// get all disks for current IP address
			for ($j=0; $j<count($disks); $j++)
			{
				if ($disks["DISK_$j"]["ip"]==$ipaddresses[$i])
				{
					$scsi[$scsi_inc][0] = $disks["DISK_$j"]["id"];
					$scsi[$scsi_inc][1] = $disks["DISK_$j"]["vendor"];
					$scsi[$scsi_inc][2] = $disks["DISK_$j"]["model"];

					if (! $scsi[$scsi_inc][1]) $scsi[$scsi_inc][1] = "unknown";
					if (! $scsi[$scsi_inc][2]) $scsi[$scsi_inc][2] = "unknown";

					if ($disks["DISK_$j"]["model"]=="IC35L018UCPR15-0" || ! $disks["DISK_$j"]["model"]) $scsi[$scsi_inc][3] = "18 Gig";
					else if ($disks["DISK_$j"]["model"]=="IC35L073UCDY10-0") $scsi[$scsi_inc][3] = "74 Gig";
					else if ($disks["DISK_$j"]["model"]=="IC35L146UCDY10-0") $scsi[$scsi_inc][3] = "146 Gig";

					$scsi_inc++;
				}
			}

			array_qsort2($scsi,0);

			// do loop 3 times to produce 3 columns
			for ($j=0; $j<3; $j++)
			{
				echo "<tr>\n";

				// do loop 2 times to produce 2 rows
				for ($l=0; $l<2; $l++)
				{
					// find scsi id that matches current slot, if there is one
					for ($k=0, $found=0; $k<count($scsi); $k++)
					{
						if ($scsi[$k][0]=="0".$j+$l*3) { $found = 1; break; }
					}

					if ($found) echo "<td bgcolor=lightblue>ID: ".$scsi[$k][0]."<br>Vendor: ".$scsi[$k][1]."<br>Size: ".$scsi[$k][3]."<br>Model: ".$scsi[$k][2]."</td>\n";
					else
						echo "<td align=center bgcolor=pink>EMPTY ID: 0".($j+$l*3)."</td>\n";
				}
				echo "</tr>\n";
			}
			echo "<tr><td colspan=2><br></td></tr>\n";
		}
		?>
</table>
</body>
</html>