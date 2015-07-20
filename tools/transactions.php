<?php
$filename = "paypal2003.csv";

$fp = fopen($filename, "r");
$contents = fread($fp, filesize($filename));
fclose($fp);

$lines = explode("\n", $contents);

// 0Date, 1Time, 2Time Zone, 3Name, 4Type, 5Status, 6Subject, 7Gross, 8Fee,
// 9Net, 10From Email Address, 11To Email Address, 12Transaction ID, 13Payment Type,
// 14Item Title, 15Reference Txn ID, 16Receipt ID, 17Balance

$i=0;
foreach ($lines as $line)
{
  $line = trim($line);
  if (! $line) continue;

  $data = explode("\",", $line);

  $date[$i]    = str_replace("\"", "", trim($data[0]));
  $name[$i]    = str_replace("\"", "", trim($data[3]));
  $type[$i]    = str_replace("\"", "", trim($data[4]));
  $status[$i]  = str_replace("\"", "", trim($data[5]));
  $net[$i]     = str_replace("\"", "", trim($data[9]));
  $paytype[$i] = str_replace("\"", "", trim($data[13]));

  $i++;
}

?>
<html>
<head>
<title></title>
<link rel="stylesheet" type="text/css" href="x.css" />
</head>
<body>
<table cellspacing="1" cellpadding="1">
  <tr>
    <td bgcolor="beige">Date</td>
    <td bgcolor="beige">Name</td>
    <td bgcolor="beige">Type</td>
    <td bgcolor="beige">Status</td>
    <td bgcolor="beige">Net Gain</td>
    <td bgcolor="beige">Payment Type</td>
  </tr>
  <?php
    $totalnet = $totalwithdrawn = $totalpaid = 0;
    $num = count($date);
    $bgcolor = "lightblue";
    for ($i=0; $i<$num; $i++)
    {
      if (stristr($type[$i], "Withdraw Funds to a Bank Account")) continue;
      if (stristr($name[$i], "Cancelled Transfer")) continue;
      if (stristr($type[$i], "Update to eCheck Received")) continue;
      if (stristr($type[$i], "Payment Sent")) continue;
      if (stristr($status[$i], "Cancelled")) continue;

      // ensure these are negative numbers
      if (stristr($status[$i], "Reversed") || stristr($status[$i], "Refunded")) $net[$i] = "-".abs($net[$i]);

      echo "<tr>\n";
      echo "<td bgcolor=\"$bgcolor\">$date[$i]</td>\n";
      echo "<td bgcolor=\"$bgcolor\">$name[$i]</td>\n";
      echo "<td bgcolor=\"$bgcolor\">$type[$i]</td>\n";
      echo "<td bgcolor=\"$bgcolor\">$status[$i]</td>\n";
      echo "<td bgcolor=\"$bgcolor\">$net[$i]</td>\n";
      echo "<td bgcolor=\"$bgcolor\">$paytype[$i]</td>\n";
      echo "</tr>\n";

      $totalnet += $net[$i];
    }

    echo "<tr><td colspan=\"10\"><b>Total Net:</b> $totalnet</td></tr>\n";

    for ($i=0; $i<$num; $i++)
    {
      if (stristr($type[$i], "Withdraw Funds to a Bank Account"))
      {
        echo "<tr>\n";
        echo "<td bgcolor=\"$bgcolor\">$date[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$name[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$type[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$status[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$net[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$paytype[$i]</td>\n";
        echo "</tr>\n";

        //$totalwithdrawn += abs($net[$i]);
        echo "$net[$i]\n";
        $totalwithdrawn += $net[$i];
      }
    }

    echo "<tr><td colspan=\"10\"><b>Total Withdrawn:</b> $totalwithdrawn</td></tr>\n";

    for ($i=0; $i<$num; $i++)
    {
      if (stristr($type[$i], "Payment Sent"))
      {
        echo "<tr>\n";
        echo "<td bgcolor=\"$bgcolor\">$date[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$name[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$type[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$status[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$net[$i]</td>\n";
        echo "<td bgcolor=\"$bgcolor\">$paytype[$i]</td>\n";
        echo "</tr>\n";

        $totalpaid += abs($net[$i]);
      }
    }

     echo "<tr><td colspan=\"10\"><b>Total Paid:</b> $totalpaid</td></tr>\n";
  ?>
</table>
</body>
</html>