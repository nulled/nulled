<?php
/*
// Get the surfer's ip address
$addr = getenv("REMOTE_ADDR");
echo "Your IP, IPv4: " . $addr . "<br />\n";

$ip = sprintf("%u", ip2long($addr));
echo "Your IP, numerical: " . $ip . "<br /><br />\n";

// Initiate the timer
$time_start = microtime_float();

// Open the csv file for reading
$handle = fopen("/home/nulled/www/planetxmail.com/ip2country.csv", "r");

// Load array with start ips
$row = 1;
while (($buffer = fgets($handle, 4096)) !== FALSE) {
  $array[$row] = substr($buffer, 1, strpos($buffer, ",") - 1);
  $row++;
}

// Time loading
$time_end = microtime_float();
$time = substr($time_end - $time_start, 0, 7);
echo "Array with " . $row . " start ips loaded in $time seconds<br /><br />\n";

// Locate the row with our ip using bisection
$row_lower = '0';
$row_upper = $row;
while (($row_upper - $row_lower) > 1) {
  $row_midpt = (int) (($row_upper + $row_lower) / 2);
  if ($ip >= $array[$row_midpt]) {
    $row_lower = $row_midpt;
  } else {
    $row_upper = $row_midpt;
  }
}

// Time locating
$time_end = microtime_float();
$time = substr($time_end - $time_start, 0, 7);
echo "Row with your ip (# " . $row_lower . ") located after $time seconds<br /><br />\n";

// Read the row with our ip
rewind($handle);
$row = 1;
while ($row <= $row_lower) {
  $buffer = fgets($handle, 4096);
  $row++;
}
$buffer = str_replace("\"", "", $buffer);
$ipdata = explode(",", $buffer);
echo "Data retrieved from the csv file:<br />\n";
echo "ipstart = " . $ipdata[0] . "<br />\n";
echo "ipend = " . $ipdata[1] . "<br />\n";
echo "registry = " . $ipdata[2] . "<br />\n";
echo "assigned = " . date('j.n.Y', $ipdata[3]) . "<br />\n";
echo "iso2 = " . $ipdata[4] . "<br />\n";
echo "iso3 = " . $ipdata[5] . "<br />\n";
echo "country = " . $ipdata[6] . "<br /><br />\n";

// Close the csv file
fclose($handle);

// Total execution time
$time_end = microtime_float();
$time = substr($time_end - $time_start, 0, 7);
echo "Executing the whole script took $time seconds\n";

function microtime_float()
{
   list($usec, $sec) = explode(" ", microtime());
   return ((float)$usec + (float)$sec);
}
*/


?>
<html>
<head>
<title>tests</title>
<script>
//window.scrollBy(0,50); // horizontal and vertical scroll increments
//setInterval(window.scrollTo(0, document.body.scrollHeight), 20000);
</script>
</head>
<body>
<?php

$len = 0;

for ($i=0; $i < 1000; $i++)
{
  $strRepeat = str_repeat(" ", 3515);
  $str = " Mailed to blah$i".$strRepeat."<br />\n";
  $len += strlen($str);
  echo $len.$str;
  flush();
  usleep(20000);
}

?>
</body>
</html>
