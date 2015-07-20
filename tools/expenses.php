<?php
$file = "checking.csv";
$fp = fopen($file, "r");
$checking = fread($fp, filesize($file));
fclose($fp);

/*
$file = "savings.csv";
$fp = fopen($file, "r");
$savings = fread($fp, filesize($file));
fclose($fp);
*/

$lines = explode("\n", $checking);

$i=0;
foreach ($lines as $line)
{
  $line = trim($line);

  if (! $line) continue;

  $line = str_replace("\"", "", $line);
  $parts = explode(",", $line);

  $parts[0] = trim($parts[0]);
  $parts[1] = trim($parts[1]);
  $parts[2]  = trim($parts[2]);

  $dates[$i] = $parts[0];
  $money[$i] = $parts[1];
  $info[$i]  = $parts[2];

  $i++;
}

$apr_profits=$apr_profits=$mar_costs=$apr_costs=0;

for ($i=0; $i<count($dates); $i++)
{
  list ($month, $day, $year) = explode("/", $dates[$i]);
  if ($month=="03")
  {
    if ($money[$i]>0) $mar_profits += $money[$i];
    else if ($money[$i]<0) $mar_costs += $money[$i];
    else
    {
      if (stristr($info[$i], "Check Cashed for"))
      {
        $p = explode(" ", trim($info[$i]));
        $checkamt = $p[count($p)-1];
        $mar_profits += $checkamt;
      }
      else
      {
        echo "Error: $dates[$i] $money[$i]";
        exit;
      }
    }
  }


  if ($month=="04")
  {
    if ($money[$i]>0) $apr_profits += $money[$i];
    else if ($money[$i]<0) $apr_costs += $money[$i];
    else
    {
      if (stristr($info[$i], "Check Cashed for"))
      {
        $p = explode(" ", trim($info[$i]));
        $checkamt = $p[count($p)-1];
        $apr_profits += $checkamt;
      }
      else
      {
        echo "Error: $dates[$i] $money[$i]";
        exit;
      }
    }
  }
}

echo "March: $mar_profits / $mar_costs<br>\n";
echo "April: $apr_profits / $apr_costs<br>\n";

?>