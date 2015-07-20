<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("../mlpsecure/config/config.inc");

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

if (! $sort) $sort = "SORT_DESC";
if (! $by) $by = "listname";

// toggle order
if ($sort=="SORT_DESC") $sort = "SORT_ASC";
else if ($sort=="SORT_ASC") $sort = "SORT_DESC";

// find out how to sort data
if ($by=="listname") $index = 3;
else if ($by=="username") $index = 0;
else if ($by=="status") $index = 2;
else if ($by=="listownerID") $index = 4;
else if ($by=="userID") $index = 1;
else if ($by=="elp") $index = 5;
else if ($by=="ipaddress") $index = 6;

if ($dir = @opendir("/tmp"))
{
  $j = 0;
  $allUsers = array();

  while($file = readdir($dir))
  {
    if (strstr($file, "sess_"))
    {
      $refp = popen("cat /tmp/$file", "r");
      $userdata = trim(fread($refp, 1024));
      pclose($refp);

      if (! $userdata) continue;

      $parts = explode(";", $userdata);

      if (($counter = count($parts))<5) continue;

      for ($i=0; $i < $counter-1; $i++)
      {
        $moreparts = explode("|", $parts[$i]);

        $param = $moreparts[0];

        if (substr($moreparts[1], 0, 1)=="s")
          list($tmp, $data) = explode("\"", $moreparts[1]);
        else if (substr($moreparts[1], 0, 1)=="i")
          list($tmp, $data) = explode(":", $moreparts[1]);

        $param = trim($param);
        $data  = trim($data);

        if ($param=="aausername")
          $allUsers[$j][0] = $data;
        else if ($param=="aauserID")
          $allUsers[$j][1] = $data;
        else if ($param=="aastatus")
          $allUsers[$j][2] = $data;
        else if ($param=="aalistname")
          $allUsers[$j][3] = $data;
        else if ($param=="aalistownerID")
          $allUsers[$j][4] = $data;
        else if ($param=="aaelp")
          $allUsers[$j][5] = $data;
        else if ($param=="aaipaddress")
          $allUsers[$j][6] = $data;
      }
      $j++;
    }
  }
  closedir($dir);
}

// sort the data
if ($sort=="SORT_ASC")
  array_qsort2($allUsers, $index, SORT_ASC);
else
  array_qsort2($allUsers, $index, SORT_DESC);

?>
<html>
<head>
<title>Member Monitor System</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table align="center" cellpadding="2" cellspacing="2" width="640" border="0">
  <tr>
    <td colspan="11" align="center">
      <font size="+1"><h3>Current Members Logged In</h3></font>
    </td>
  </tr>
  <tr>
    <td bgcolor="lightblue"><a href="<?=$_SERVER[PHP_SELF]?>?sort=<?=$sort?>&by=username"><b>Username</b></a></td><td bgcolor="lightblue"><a href="<?=$_SERVER[PHP_SELF]?>?sort=<?=$sort?>&by=userID"><b>UserID</b></a></td><td bgcolor="lightblue"><a href="<?=$_SERVER[PHP_SELF]?>?sort=<?=$sort?>&by=status"><b>Status</b></a></td><td bgcolor="lightblue"><a href="<?=$_SERVER[PHP_SELF]?>?sort=<?=$sort?>&by=listname"><b>List Name</b></a></td><td bgcolor="lightblue"><a href="<?=$_SERVER[PHP_SELF]?>?sort=<?=$sort?>&by=listownerID"><b>ListOwnerID</b></a></td><td bgcolor="lightblue"><a href="<?=$_SERVER[PHP_SELF]?>?sort=<?=$sort?>&by=elp"><b>Using&nbsp;ELP?</b></a></td><td bgcolor="lightblue"><a href="<?=$_SERVER[PHP_SELF]?>?sort=<?=$sort?>&by=ipaddress"><b>IP&nbsp;Address</b></a></td>
  </tr>
  <?php
    $num = count($allUsers);
    for ($i=0, $j=0; $i < $num; $i++)
    {
    	if (! $_SESSION[aaadminpsk]) if ($allUsers[$i][4]!=$_SESSION[aalistownerID]) continue;
			if (! $allUsers[$i][0]) continue;

      if ($i%2==0)
        $bgcolor = "F4F4F7";
      else
        $bgcolor = "E9E9E9";

      if ($allUsers[$i][5])
        $elp = "Yes";
      else
        $elp = "No";

      echo "<tr><td bgcolor=\"$bgcolor\">".$allUsers[$i][0]."</td><td bgcolor=\"$bgcolor\">".$allUsers[$i][1]."</td><td bgcolor=\"$bgcolor\">".$allUsers[$i][2]."</td><td bgcolor=\"$bgcolor\">".$allUsers[$i][3]."</td><td bgcolor=\"$bgcolor\">".$allUsers[$i][4]."</td><td align=\"center\" bgcolor=\"$bgcolor\">$elp</td><td bgcolor=\"$bgcolor\">".$allUsers[$i][6]."</td></tr>\n";
    	$j++;
    }
  ?>
  <tr>
    <td colspan="11" align="center">
      <br>Total Members Currently Logged in: <b><?=$j?></b>
    </td>
  </tr>
  <tr>
    <td colspan="11" align="center">
      <br><input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
    </td>
  </tr>
</table>
</body>