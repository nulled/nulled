<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecureadmin.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/datefunctions.inc');

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
?>
<html>
<head>
<title>Lists Stats</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body background="../images/liststats_bg.jpg">
<table align="center" width="600" cellpadding="3" cellspacing="2" border="0">
<?php
  set_time_limit(0);
  $db = new MySQL_Access();

  $timefresh = 3600; // seconds

  $numTotalMembers = $countTotal = $filterMem = $filterPro = $filterExe = $numListowners = $numLists = $entry = 0;

  $data = array();
  $totalMem = array();
  $totalPro = array();
  $totalExe = array();
  $totalMembers = array();
	$numpaid 			= 0;
	$numdue 			= 0;
	$numfree 			= 0;
	$numcancelled = 0;

  $atime = (isset($_SESSION['atime'])) ? $_SESSION['atime'] : 0;

  if (! $sort) $sort = "SORT_ASC";
  if (! $by) $by = "listowner";

  if (! $atime OR (time() - $atime) > $timefresh)
  {
    $_SESSION['atime'] = time();
    $getFromStorage = 0;
  }
  else
    $getFromStorage = 1;

  // toggle order
  if ($sort=="SORT_DESC") $sort = "SORT_ASC";
  else if ($sort=="SORT_ASC") $sort = "SORT_DESC";

  // find out how to sort data
  if ($by=="listowner") $index = 0;
  else if ($by=="listname") $index = 3;
  else if ($by=="total") $index = 4;
  else if ($by=="mem") $index = 5;
  else if ($by=="pro") $index = 6;
  else if ($by=="exe") $index = 7;
  else if ($by=="paidstatus") $index = 8;

  if (! $getFromStorage)
  {
    // new query so delete old
    $db->Query("DELETE FROM liststats");

    $db->Query("SELECT username, listownerID, email FROM listowner WHERE username!='demoit' AND username!='PlanetXMail' ORDER BY username");
    $listowners = $db->result;
    $numListowners = $db->rows;

    while (list($listownername, $listownerID, $listowneremail) = mysqli_fetch_row($listowners))
    {
      $db->Query("SELECT listname, listtype FROM listmanager WHERE created='1' AND listownerID='$listownerID' ORDER BY listname");
      $lists = $db->result;

      while (list($listname, $listtype) = mysqli_fetch_row($lists))
      {
        if ($listtype!="Newsletter [closedlist]") $emailquery = " AND listemail!='' AND listemail NOT LIKE '%unconfirmed'";
        else
          $emailquery = "";

        $db->Query("SELECT listemail FROM users WHERE status='mem' AND listownerID='$listownerID' AND listname='$listname' AND verified='yes'$emailquery");
        $numMem = $db->rows;
        if ($numMem)
        {
          while (list($mem) = $db->FetchRow())
            $totalMem[] = strtolower($mem);
        }

        $db->Query("SELECT listemail FROM users WHERE status='pro' AND listownerID='$listownerID' AND listname='$listname' AND verified='yes'$emailquery");
        $numPro = $db->rows;
        if ($numPro)
        {
          while (list($mem) = $db->FetchRow())
            $totalPro[] = strtolower($mem);
        }

        $db->Query("SELECT listemail FROM users WHERE status='exe' AND listownerID='$listownerID' AND listname='$listname' AND verified='yes'$emailquery");
        $numExe = $db->rows;
        if ($numExe)
        {
          while (list($mem) = $db->FetchRow())
            $totalExe[] = strtolower($mem);
        }

        $numMembers = $numMem + $numPro + $numExe;

        include("adminsecure/billing.inc");

        if ($paid=="yes" || $paid=="1")
          $paidstatus = "<b>$timestr_next_bill</b> until next billing.\n";
        else if ($paid=="no" || $paid=="0")
          $paidstatus =  "<a href=\"http://www.planetxmail.com/listpayment.php?id=$orderID&listtype=$type&p=$price&ex=$ex\" target=\"_BLANK\">Click Here To Pay</a> $timestr_late_bill late.";
        else if ($paid=="free2months")
          $paidstatus =  "This List is Free for 1 month. <b>$days_free_left</b> day(s) left.";
        else if ($paid=="cancelled")
          $paidstatus =  "This List is cancelled, but active.";
        else if ($paid=="notlisted")
          $paidstatus = "Not Listed";

        $data[$entry][0] = $listownername;
        $data[$entry][1] = $listowneremail;
        $data[$entry][2] = $listownerID;
        $data[$entry][3] = $listname;
        $data[$entry][4] = $numMembers;
        $data[$entry][5] = $numMem;
        $data[$entry][6] = $numPro;
        $data[$entry][7] = $numExe;
        $data[$entry][8] = $paidstatus;

        // record to database
        $db->Query("INSERT INTO liststats VALUES('$listownername','$listowneremail','$listownerID','$listname','$numMembers','$numMem','$numPro','$numExe','$paidstatus')");

        $entry++;

        $numTotalMembers += $numMembers;
        $numLists++;
      }
    }

    // generate total member counts and filter
    sort($totalMem); sort($totalPro); sort($totalExe);
    $countMem = count($totalMem); $countPro = count($totalPro); $countExe = count($totalExe);

    for ($i=0, $prev=""; $i<$countMem; $i++)
    {
      $mem = $totalMem[$i];
      $totalMembers[] = $mem;
      $totalMem[$i] = "";
      if ($prev==$mem) continue;
      $prev = $mem;
      $filterMem++;
    }

    unset($totalMem);

    for ($i=0, $prev=""; $i<$countPro; $i++)
    {
      $mem = $totalPro[$i];
      $totalMembers[] = $mem;
      $totalPro[$i] = "";
      if ($prev==$mem) continue;
      $prev = $mem;
      $filterPro++;
    }

    unset($totalPro);

    for ($i=0, $prev=""; $i<$countExe; $i++)
    {
      $mem = $totalExe[$i];
      $totalMembers[] = $mem;
      $totalExe[$i] = "";
      if ($prev==$mem) continue;
      $prev = $mem;
      $filterExe++;
    }

    unset($totalExe);

    sort($totalMembers);
    $countTotal = count($totalMembers);

    for ($i=0, $prev=""; $i<$countTotal; $i++)
    {
      $mem = $totalMembers[$i];
      $totalMembers[$i] = "";
      if ($prev==$mem) continue;
      $prev = $mem;
      $allFiltered[] = $mem;
      $filterTotal++;
    }

    $totalFiltered = $filterMem + $filterPro + $filterExe;
    unset($totalMembers);
  }

  if ($getFromStorage)
  {
    $db->Query("SELECT listownername, listowneremail, listownerID, listname, numMembers, numMem, numPro, numExe, paidstatus FROM liststats WHERE 1");

    $i=0;
    while (list($listownername, $listowneremail, $listownerID, $listname, $numMembers, $numMem, $numPro, $numExe, $paidstatus) = $db->FetchRow())
    {
      if ($listownername=="TOTALS")
      {
        $totalparts = explode("|", $paidstatus);
        $numTotalMembers = $totalparts[0];
        $totalFiltered   = $totalparts[1];
        $filterTotal     = $totalparts[2];
        $numListowners   = $totalparts[3];
        $numLists        = $totalparts[4];
        $filterMem       = $totalparts[5];
        $filterPro       = $totalparts[6];
        $filterExe       = $totalparts[7];
        $countMem        = $totalparts[8];
        $countPro        = $totalparts[9];
        $countExe        = $totalparts[10];
      }
      else
      {
        $data[$i][0] = $listownername;
        $data[$i][1] = $listowneremail;
        $data[$i][2] = $listownerID;
        $data[$i][3] = $listname;
        $data[$i][4] = $numMembers;
        $data[$i][5] = $numMem;
        $data[$i][6] = $numPro;
        $data[$i][7] = $numExe;
        $data[$i][8] = $paidstatus;
        $i++;
      }
    }
  }

  // sort the data
  if ($sort=="SORT_ASC")
    array_qsort2($data, $index, SORT_ASC);
  else
    array_qsort2($data, $index, SORT_DESC);

  if ($getFromStorage) $dataState = "<br>Data From Storage";
  else
    $dataState = "<br>Data Was Refreshed";

  // display data head
  echo "<tr><td align=center colspan=10><font size=4><b>Planet X Mail System Overview</b></font>$dataState<hr></td></tr>\n";
  echo "<tr><td align=center bgcolor=lightgrey><font size=3><a href=\"$_SERVER[PHP_SELF]?sort=$sort&by=listowner\"><b>List Owner</b></a></font></td>";
  echo "<td align=center bgcolor=lightgrey><font size=3><a href=\"$_SERVER[PHP_SELF]?sort=$sort&by=listname\"><b>List Name</b></a></font></td>";
  echo "<td align=center bgcolor=lightgrey><font size=3><a href=\"$_SERVER[PHP_SELF]?sort=$sort&by=total\"><b>Total</b></a></font></td>";
  echo "<td align=center bgcolor=lightgrey><font size=3><a href=\"$_SERVER[PHP_SELF]?sort=$sort&by=mem\"><b>Mem</b></a></font></td>";
  echo "<td align=center bgcolor=lightgrey><font size=3><a href=\"$_SERVER[PHP_SELF]?sort=$sort&by=pro\"><b>Pro</b></a></font></td>";
  echo "<td align=center bgcolor=lightgrey><font size=3><a href=\"$_SERVER[PHP_SELF]?sort=$sort&by=exe\"><b>Exe</b></a></font></td>";
  echo "<td align=center bgcolor=lightgrey><font size=3><a href=\"$_SERVER[PHP_SELF]?sort=$sort&by=paidstatus\"><b>Bill Status</b></a></font></td>\n";

  // display each list
  $counter = count($data);
  for ($i=0; $i<$counter; $i++)
  {
    $listownername  = $data[$i][0];
    $listowneremail = $data[$i][1];
    $listownerID    = $data[$i][2];
    $listname       = $data[$i][3];
    $numMembers     = $data[$i][4];
    $numMem         = $data[$i][5];
    $numPro         = $data[$i][6];
    $numExe         = $data[$i][7];
    $paidstatus     = $data[$i][8];

    if (stristr($paidstatus, "next billing")) $numpaid++;
    else if (stristr($paidstatus, "listpayment.php")) $numdue++;
    else if (stristr($paidstatus, "List is Free")) $numfree++;
    else if (stristr($paidstatus, "cancelled")) $numcancelled++;

    if ($i%2==0)
      $bgcolor = "F4F4F7";
    else
      $bgcolor = "E9E9E9";

    echo "<tr><td bgcolor=$bgcolor><font size=3><b>$listownername</b></font><br><font size=1>$listowneremail</font></td>";
    echo "<td bgcolor=$bgcolor><font color=darkblue><b>$listname</b></td>";
    echo "<td bgcolor=$bgcolor><font color=maroon><b>$numMembers</b></font></td>";
    echo "<td bgcolor=$bgcolor>$numMem</td>";
    echo "<td bgcolor=$bgcolor>$numPro</td>";
    echo "<td bgcolor=$bgcolor>$numExe</td>";
    echo "<td bgcolor=$bgcolor><font size=1>$paidstatus</font></td></tr>\n";
  }

  // display filtered counts information
  echo "<tr><td colspan=2 align=right><font color=blue><i>Totals:</i></td>";
  echo "<td bgcolor=$bgcolor><font color=maroon><b>$numTotalMembers</b></font></td>";
  echo "<td bgcolor=$bgcolor>$countMem</td>";
  echo "<td bgcolor=$bgcolor>$countPro</td>";
  echo "<td bgcolor=$bgcolor>$countExe</td>";
  echo "<td></td></tr>\n";

  echo "<tr><td colspan=2 align=right><font color=blue><i>Totals After Filtering Duplicates:</i></td>";
  echo "<td bgcolor=$bgcolor><font color=maroon><b>$totalFiltered</b></font></td>";
  echo "<td bgcolor=$bgcolor>$filterMem</td>";
  echo "<td bgcolor=$bgcolor>$filterPro</td>";
  echo "<td bgcolor=$bgcolor>$filterExe</td>";
  echo "<td></td></tr>\n";

  echo "<tr><td colspan=2 align=right><font color=blue><i>Total individual emails:</i></td>";
  echo "<td bgcolor=$bgcolor><font color=maroon><b>$filterTotal</b></font></td>";
  echo "<td colspan=3></td>";
  echo "<td></td></tr>\n";

  echo "<tr><td colspan=2 align=right><font color=blue><i>Total List Owners:</i></td>";
  echo "<td bgcolor=$bgcolor><font color=maroon><b>$numListowners</b></font></td>";
  echo "<td colspan=3></td>";
  echo "<td></td></tr>\n";

  echo "<tr><td colspan=2 align=right><font color=blue><i>Total Lists:</i></td>";
  echo "<td bgcolor=$bgcolor><font color=maroon><b>$numLists</b></font></td>";
  echo "<td colspan=3></td>";
  echo "<td></td></tr>\n";

  echo "<tr><td colspan=2 align=right><font color=blue><i>Paid:</i></td>";
  echo "<td bgcolor=$bgcolor><font color=maroon><b>$numpaid</b></font></td>";
  echo "<td colspan=3></td>";
  echo "<td></td></tr>\n";

  echo "<tr><td colspan=2 align=right><font color=blue><i>Due:</i></td>";
  echo "<td bgcolor=$bgcolor><font color=maroon><b>$numdue</b></font></td>";
  echo "<td colspan=3></td>";
  echo "<td></td></tr>\n";

  echo "<tr><td colspan=2 align=right><font color=blue><i>Free:</i></td>";
  echo "<td bgcolor=$bgcolor><font color=maroon><b>$numfree</b></font></td>";
  echo "<td colspan=3></td>";
  echo "<td></td></tr>\n";

  echo "<tr><td colspan=2 align=right><font color=blue><i>Cancelled:</i></td>";
  echo "<td bgcolor=$bgcolor><font color=maroon><b>$numcancelled</b></font></td>";
  echo "<td colspan=3></td>";
  echo "<td></td></tr>\n";

  $totaldata = "$numTotalMembers|$totalFiltered|$filterTotal|$numListowners|$numLists|$filterMem|$filterPro|$filterExe|$countMem|$countPro|$countExe";

  if (! $getFromStorage) $db->Query("INSERT INTO liststats VALUES('TOTALS','TOTALS','TOTALS','TOTALS','','','','','$totaldata')");
?>
  <tr>
    <td colspan="10" align="center">
      <br><br><input type="button" class="beigebutton" value="Back to Main" onClick="location.href='main.php'">
    </td>
  </tr>
  <tr>
  	<td colspan="10">
  		<pre>
  		<?php
  			if (! $getFromStorage)
  			{
	  			$domains = array();
	  			$count = count($allFiltered);

	  			// check if domain needs to be added to list else increment existing
					for ($i=0; $i<$count; $i++)
					{
						list(, $domain) = explode("@", $allFiltered[$i]);
						if (! strcasecmp($domain, 'pxmb.com') || ! strcasecmp($domain, 'planetxmailbox.com'))
							$domain = 'planetxmailbox.com';

						if ($domains[$domain]) $domains[$domain]++;
						else
							$domains[$domain] = 1;
					}

					arsort($domains);
					$keys = array_keys($domains);
					$count = count($keys);

					$topdomains = 100;

					echo "\n<b>Total Domains</b> = $count\n\n";
					echo "Top $topdomains domains used listed below.\n\n";

					// display top 100 domains
					for ($i=0; $i<$topdomains; $i++)
					{
						if ($keys[$i] == 'planetxmailbox.com')
							echo $domains[$keys[$i]]." - <b>".$keys[$i]."</b>\n";
						else
							echo $domains[$keys[$i]]." - ".$keys[$i]."\n";
					}

				}
  		?>
  		</pre>
  	</td>
  </tr>
</table>
</body>
</html>