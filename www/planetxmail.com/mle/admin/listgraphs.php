<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecureadmin.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
?>
<html>
<head>
<title>Lists Graphs</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body background="../images/liststats_bg.jpg">
<table align="center" width="700" border="0" cellpadding="3" cellspacing="2">
<?php
  $pxm = 1;
  $dividor = 18;

  function array_qsort2(&$array, $column=0, $order=SORT_ASC, $first=0,$last= -2)
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

  $db = new MySQL_Access();

  $timefresh = 600; // seconds

  $time2 = (isset($_SESSION['time2'])) ? $_SESSION['time2'] : 0;

  if (! $time2 OR (time() - $time2) > $timefresh)
  {
    $_SESSION['time2'] = time();
    $getFromStorage = 0;
  }
  else
    $getFromStorage = 1;

  if ($getFromStorage) $dataState = "<br>Data From Storage";
  else
    $dataState = "<br>Data Was Refreshed";

  if ($pxm)
    echo "<tr><td align=center colspan=10><font size=4><b>Planet X Mail - List Size Bar Chart</b></font>$dataState<hr></td></tr>\n";
  else
    echo "<tr><td align=center colspan=10><font size=4><b>Global-Lists - List Size Bar Chart</b></font>$dataState<hr></td></tr>\n";

  if (! $sort) $sort = "SORT_ASC";
  if (! $by) $by = "num";

  // toggle order if sort by listname
  if ($sort=="SORT_DESC") $sort = "SORT_ASC";
  else if ($sort=="SORT_ASC") $sort = "SORT_DESC";

  echo "<tr><td align=center bgcolor=lightgrey><font size=2><a href=\"$_SERVER[PHP_SELF]?sort=$sort&by=listname&time2=$time2\"><b>List Name</b></a></font></td><td align=center bgcolor=lightgrey><a href=\"$_SERVER[PHP_SELF]?sort=$sort&by=num&time2=$time2\"><b>Total With a List Email / Total Members</b></a></td></tr>\n";

  if (! $getFromStorage)
  {
    $db->Query("DELETE FROM listgraphs");

    $db->Query("SELECT username, listownerID, email FROM listowner WHERE username!='demoit' AND username!='PlanetXMail' ORDER BY username");
    $listowners = $db->result;

    $i=0;
    $alllists = array();
    while (list($listownername, $listownerID, $listowneremail) = mysqli_fetch_row($listowners))
    {
      $db->Query("SELECT listname, listtype FROM listmanager WHERE created='1' AND listownerID='$listownerID' ORDER BY listname");
      $lists = $db->result;

      while (list($listname, $listtype) = mysqli_fetch_row($lists))
      {
        if ($listname=="ProWealth123DLC_News") continue;

        $db->Query("SELECT username FROM users WHERE listownerID='$listownerID' AND listname='$listname' AND verified='yes' AND listemail!='' AND listemail NOT LIKE '%unconfirmed'");
        $numMem = $db->rows;

        $db->Query("SELECT username FROM users WHERE listownerID='$listownerID' AND listname='$listname' AND verified='yes'");
        $numTotal = $db->rows;

        if ($numMem)
          $width = $numMem/$dividor;
        else
          $width = 0;

        if ($numTotal)
          $width2 = $numTotal/$dividor;
        else
          $width2 = 0;

        $parts = explode(".", $width);
        $width = $parts[0];

        $parts = explode(".", $width2);
        $width2 = $parts[0];

        $alllists[$i][0] = $listname;
        $alllists[$i][1] = $numMem;
        $alllists[$i][2] = $listownername;
        $alllists[$i][3] = $numTotal;
        $alllists[$i][4] = $width;
        $alllists[$i][5] = $width2;
        $i++;

        $db->Query("INSERT INTO listgraphs VALUES('$listname','$numMem','$listownername','$numTotal','$width','$width2')");
      }
    }
  }

  if ($getFromStorage)
  {
    $db->Query("SELECT * FROM listgraphs WHERE 1");

    $i=0;
    while(list($listname, $numMem, $listownername, $numTotal, $width, $width2) = $db->FetchRow())
    {
      $alllists[$i][0] = $listname;
      $alllists[$i][1] = $numMem;
      $alllists[$i][2] = $listownername;
      $alllists[$i][3] = $numTotal;
      $alllists[$i][4] = $width;
      $alllists[$i][5] = $width2;
      $i++;
    }
  }

  if ($by=="listname") $index = 0;
  else if ($by=="num") $index = 1;

  if ($sort=="SORT_ASC") array_qsort2($alllists, $index, SORT_ASC);
  else
    array_qsort2($alllists, $index, SORT_DESC);

  $numlists = count($alllists);
  for ($i=0; $i<$numlists; $i++)
  {
    $listname      = $alllists[$i][0];
    $numMem        = $alllists[$i][1];
    $listownername = $alllists[$i][2];
    $numTotal      = $alllists[$i][3];
    $width         = $alllists[$i][4];
    $width2        = $alllists[$i][5];

    if ($i%2==0)
      $bgcolor = "F4F4F7";
    else
      $bgcolor = "E9E9E9";

    $width2 -= $width;

    $showbar = "";
    if ($numMem)
      $showbar = "<img src=\"../images/vote_left.gif\" height=9 width=5><img src=\"../images/vote_middle.gif\" height=9 width=$width><img src=\"../images/vote_middle_2.gif\" height=9 width=$width2><img src=\"../images/vote_right_2.gif\" height=9 width=6>";
    else
      $numMem = "<i>empty</i>";

    echo "<tr><td align=right bgcolor=$bgcolor><b><font size=2>$listname</font></b></td><td bgcolor=$bgcolor><font size=1>$showbar $numMem / $numTotal</font></td></tr>\n";
  }
?>
  <tr>
    <td colspan=10 align=center>
      <br><br><input type="button" class="beigebutton" value="Back to Main" onClick="location.href='main.php'">
    </td>
  </tr>
</table>
</body>
</html>
