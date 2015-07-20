<?php
include("phpsecure/classes.inc");

$db = new MySQL_Access("mle");
$months = array("","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec");
$db->Query("SELECT datesubmitted FROM soloads WHERE mop!='' ORDER BY datesubmitted DESC");

$i = 0;
while (list($date) = $db->FetchRow())
{
  list($year[$i], $month[$i], $day[$i]) = preg_split("/[- ]/", $date);
  $i++;
}
$numAds = count($year);
$db->Query("SELECT datesubmitted FROM soloads WHERE mop!='' AND mailed='0'");
$newAd = $db->rows;
?>
<html>
<head>
<title>Solo AD Totals</title>
<link rel="stylesheet" type="text/css" href="x.css" />
<meta http-equiv="refresh" content="300;URL=satotal.php">
</head>
<body>
<table border="0" width="120" align="center" cellspacing="2" cellpadding="1">
  <tr>
    <td bgcolor="lightblue">Date:</td>
    <td bgcolor="lightblue">SoloAds</td>
  </tr>
    <?php
      if ($newAd)
        echo "<tr><td align=\"center\" colspan=\"2\" bgcolor=\"yellow\" align=\"right\"><font size=\"+1\">New AD!</font></td></tr>";

      for ($i=0, $counter=0; $i<$numAds; $i++)
      {
        if (substr($month[$i], 0, 1)=="0") $month[$i] = substr($month[$i], 1, 1);

        if ($tyear==$year[$i] && $tmonth==$month[$i] && $tday==$day[$i])
        {
          $counter++;

          if ($i==$numAds-1)
          {
            $numDays++;
            echo "<td bgcolor=\"beige\"><b>$counter</b></td></tr>\n";
          }

          continue;
        }
        else if (! $counter)
        {
          $counter = 1;
          echo "<tr><td bgcolor=\"beige\">".$months[$month[$i]].", $day[$i]</td>\n";

          if ($i==$numAds-1)
          {
            $numDays++;
            echo "<td bgcolor=\"beige\"><b>$counter</b></td></tr>\n";
          }
        }
        else
        {
          echo "<td bgcolor=\"beige\"><b>$counter</b></td></tr>\n";
          $counter = 0;
          $i--;
          $numDays++;
        }

        $tyear  = $year[$i];
        $tmonth = $month[$i];
        $tday   = $day[$i];
      }
    ?>
<tr><td bgcolor="beige">Mar, 14</td>
<td bgcolor="beige"><b>12</b></td></tr>
<tr><td bgcolor="beige">Mar, 13</td>
<td bgcolor="beige"><b>17</b></td></tr>
<tr><td bgcolor="beige">Mar, 12</td>
<td bgcolor="beige"><b>8</b></td></tr>
<tr><td bgcolor="beige">Mar, 11</td>
<td bgcolor="beige"><b>14</b></td></tr>
<tr><td bgcolor="beige">Mar, 10</td>
<td bgcolor="beige"><b>9</b></td></tr>
<tr><td bgcolor="beige">Mar, 09</td>
<td bgcolor="beige"><b>10</b></td></tr>
<tr><td bgcolor="beige">Mar, 08</td>
<td bgcolor="beige"><b>18</b></td></tr>
<tr><td bgcolor="beige">Mar, 07</td>
<td bgcolor="beige"><b>25</b></td></tr>
<tr><td bgcolor="beige">Mar, 06</td>
<td bgcolor="beige"><b>15</b></td></tr>
<tr><td bgcolor="beige">Mar, 05</td>
<td bgcolor="beige"><b>13</b></td></tr>
<tr><td bgcolor="beige">Mar, 04</td>
<td bgcolor="beige"><b>10</b></td></tr>
<tr><td bgcolor="beige">Mar, 03</td>
<td bgcolor="beige"><b>15</b></td></tr>
<tr><td bgcolor="beige">Mar, 02</td>
<td bgcolor="beige"><b>27</b></td></tr>
<tr><td bgcolor="beige">Mar, 01</td>
<td bgcolor="beige"><b>14</b></td></tr>
<tr><td bgcolor="beige">Feb, 28</td>
<td bgcolor="beige"><b>9</b></td></tr>
<tr><td bgcolor="beige">Feb, 27</td>
<td bgcolor="beige"><b>11</b></td></tr>
<tr><td bgcolor="beige">Feb, 26</td>
<td bgcolor="beige"><b>9</b></td></tr>
<tr><td bgcolor="beige">Feb, 25</td>
<td bgcolor="beige"><b>15</b></td></tr>
<tr><td bgcolor="beige">Feb, 24</td>
<td bgcolor="beige"><b>13</b></td></tr>
<tr><td bgcolor="beige">Feb, 23</td>
<td bgcolor="beige"><b>9</b></td></tr>
<tr><td bgcolor="beige">Feb, 22</td>
<td bgcolor="beige"><b>17</b></td></tr>
<tr><td bgcolor="beige">Feb, 21</td>
<td bgcolor="beige"><b>12</b></td></tr>
<tr><td bgcolor="beige">Feb, 20</td>
<td bgcolor="beige"><b>14</b></td></tr>
<tr><td bgcolor="beige">Feb, 19</td>
<td bgcolor="beige"><b>17</b></td></tr>
<tr><td bgcolor="beige">Feb, 18</td>
<td bgcolor="beige"><b>11</b></td></tr>
<tr><td bgcolor="beige">Feb, 17</td>
<td bgcolor="beige"><b>13</b></td></tr>
<tr><td bgcolor="beige">Feb, 16</td>
<td bgcolor="beige"><b>14</b></td></tr>
<tr><td bgcolor="beige">Feb, 15</td>
<td bgcolor="beige"><b>9</b></td></tr>
<tr><td bgcolor="beige">Feb, 14</td>
<td bgcolor="beige"><b>8</b></td></tr>
<tr><td bgcolor="beige">Feb, 13</td>
<td bgcolor="beige"><b>14</b></td></tr>
<tr><td bgcolor="beige">Feb, 12</td>
<td bgcolor="beige"><b>17</b></td></tr>
<tr><td bgcolor="beige">Feb, 11</td>
<td bgcolor="beige"><b>16</b></td></tr>
<tr><td bgcolor="beige">Feb, 10</td>
<td bgcolor="beige"><b>17</b></td></tr>
<tr><td bgcolor="beige">Feb, 09</td>
<td bgcolor="beige"><b>19</b></td></tr>
<tr><td bgcolor="beige">Feb, 08</td>
<td bgcolor="beige"><b>27</b></td></tr>
<tr><td bgcolor="beige">Feb, 07</td>
<td bgcolor="beige"><b>15</b></td></tr>
<tr><td bgcolor="beige">Feb, 06</td>
<td bgcolor="beige"><b>14</b></td></tr>
<tr><td bgcolor="beige">Feb, 05</td>
<td bgcolor="beige"><b>19</b></td></tr>
<tr><td bgcolor="beige">Feb, 04</td>
<td bgcolor="beige"><b>17</b></td></tr>
<tr><td bgcolor="beige">Feb, 03</td>
<td bgcolor="beige"><b>6</b></td></tr>
<tr><td bgcolor="beige">Feb, 02</td>
<td bgcolor="beige"><b>12</b></td></tr>
<tr><td bgcolor="beige">Feb, 01</td>
<td bgcolor="beige"><b>16</b></td></tr>
<tr><td bgcolor="beige">Jan, 31</td>
<td bgcolor="beige"><b>15</b></td></tr>
<tr><td bgcolor="beige">Jan, 30</td>
<td bgcolor="beige"><b>17</b></td></tr>
    <?php
      $numDays += 44;
      $numAds  += 629;
      $profits = $numAds * 20;
      $average = substr((string)$numAds/$numDays, 0, 4);

      echo "<tr><td bgcolor=\"pink\" align=\"right\">Total:</td><td bgcolor=\"pink\"><b>$numAds</b></td></tr>";
      echo "<tr><td bgcolor=\"pink\" align=\"right\">Profits:</td><td bgcolor=\"pink\"><b>$profits</b></td></tr>";
      echo "<tr><td bgcolor=\"pink\" align=\"right\">Average:</td><td bgcolor=\"pink\"><b>$average</b></td></tr>";

      // DELETE FROM `soloads` WHERE datesubmitted NOT LIKE '2002-03-15%' AND datesubmitted NOT LIKE '0%';
    ?>
  </td>
</table>
</body>
</html>
