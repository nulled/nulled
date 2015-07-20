<?php
include("../../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("elp");

$numMem = array();
$numUnver = array();

$db->Query("SELECT elpownername, fname, lname, email, price, monthlyprice, commission, monthlycommission, blocked FROM elpowners ORDER BY elpownername");
$odata = $db->result;

$ownerindex = 0;
$alertLevel = array();
while (list($currentowner) = mysqli_fetch_row($odata))
{
  $db->Query("SELECT username FROM users WHERE verified='1' AND ((UNIX_TIMESTAMP(NOW()) - 2160000) >= UNIX_TIMESTAMP(datesignedup) OR paid='1') AND username!='demo' AND username!='test_me' AND elpownername='$currentowner' ORDER BY username");
  $users = $db->result;
  array_push($numMem, $db->rows);

  $alertLevel[$ownerindex] = "beige";

  while (list($uname) = mysqli_fetch_row($users))
  {
    $db->Query("SELECT ip FROM ipaddresses WHERE username='$uname' AND elpownername='$currentowner' ORDER BY ip");
    $ips = $db->result;

    $ipprev1 = "";
    $ipprev2 = "";

    if ($db->rows)
    {
      while (list($ip) = mysqli_fetch_row($ips))
      {
        $ipsegments = explode(".", $ip);

        if ($ipprev1!="" && $ipprev1!=$ipsegments[0])
        {
          $alertLevel[$ownerindex] = "pink";
          break;
        }
        if ($ipprev2!="" && $ipprev2!=$ipsegments[1])
        {
          $alertLevel[$ownerindex] = "yellow";
        }

        $ipprev1 = $ipsegments[0];
        $ipprev2 = $ipsegments[1];
      }

      if ($alertLevel[$ownerindex] == "pink")
        break;
    }
  }

  $db->Query("SELECT username FROM users WHERE verified='0' AND username!='test_me' AND username!='demo' AND elpownername='$currentowner'");
  array_push($numUnver, $db->rows);

  $ownerindex++;
}

@mysqli_data_seek($odata, 0);

?>