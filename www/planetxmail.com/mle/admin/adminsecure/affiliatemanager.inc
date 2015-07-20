<?php
include("../mlpsecure/config/classes.inc");
include("../mlpsecure/config/config.inc");
include("../mlpsecure/validationfunctions.php");

$db = new MySQL_Access();

// get all users that have referred someone that is pro or exe
$db->Query("SELECT userID, username FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]' AND verified='yes'");
$allUsers = $db->result;

$db->Query("SELECT listhash FROM listurls WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
list($listhash) = $db->FetchRow();

// get all users
$i = 0;
while (list($userID, $username) = mysqli_fetch_row($allUsers))
{
  $affid = strrev($userID)."|$listhash";

  // get all users that current user referer
  $db->Query("SELECT COUNT(*) FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]' AND referer='$affid' AND verified='yes'");
  list($counttotal) = $db->FetchRow();

  if ($counttotal)
  {
    // get all users that current user referer not paid
    $db->Query("SELECT COUNT(*) FROM users WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]' AND referer='$affid' AND paid='0' AND (status='pro' OR status='exe') AND verified='yes'");
    list($countnotpaid) = $db->FetchRow();

    if ($i%2==0)
      $bgcolor = "F4F4F7";
    else
      $bgcolor = "E9E9E9";

    if ($countnotpaid) $bgcolor = "pink";

    $html .= "<tr><td bgcolor=\"$bgcolor\"><a href=\"adminmemberaffview.php?u=$userID\">$username</a></td><td bgcolor=\"$bgcolor\" align=\"center\">$countnotpaid</td><td bgcolor=\"$bgcolor\" align=\"center\">$counttotal</td></tr>\n";
    $i++;
  }
}

?>