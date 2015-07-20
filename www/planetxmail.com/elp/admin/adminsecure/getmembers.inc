<?php
include("../../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("elp");

$db->Query("SELECT username, fname, lname, email, blocked FROM users WHERE verified='1' AND ((UNIX_TIMESTAMP(NOW()) - 2160000) >= UNIX_TIMESTAMP(datesignedup) OR paid='1') AND username!='demo' AND elpownername='$o' ORDER BY username");
$udata = $db->result;

$memberindex  = 0;
$ipCount      = array();
$alertLevel   = array();
while (list($uname) = mysqli_fetch_row($udata))
{
  $db->Query("SELECT ip FROM ipaddresses WHERE username='$uname' AND elpownername='$o' ORDER BY ip");
  $ipCount[$memberindex] = $db->rows;

  $ipprev1 = "";
  $ipprev2 = "";
  $alertLevel[$memberindex] = "beige";

  if ($db->rows)
  {
    while (list($ip) = $db->FetchRow())
    {
      $ipsegments = explode(".", $ip);

      if ($ipprev1!="" && $ipprev1!=$ipsegments[0])
      {
        $alertLevel[$memberindex] = "pink";
        break;
      }
      if ($ipprev2!="" && $ipprev2!=$ipsegments[1])
      {
        $alertLevel[$memberindex] = "yellow";
      }

      $ipprev1 = $ipsegments[0];
      $ipprev2 = $ipsegments[1];
    }
  }

  $memberindex++;
}

@mysqli_data_seek($udata, 0);

?>