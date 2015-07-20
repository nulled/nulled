<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');

function check_for($id, $list, $printout=0)
{
  global $lists;

  foreach ($lists as $listownerID => $arr)
  {
    foreach ($arr as $listname => $username)
    {
      if ($printout)
        echo "id=$listownerID, list=$listname, user=$username\n";
      else
      {
        if ($listownerID == $id && strtolower($listname) == strtolower($list))
          return 1;
      }
    }
  }

  return 0;
}

$db = new MySQL_Access('mle');

$lists = array();

$db->Query("SELECT listownerID, username FROM listowner WHERE 1 ORDER BY username");
$listowners = $db->result;
while(list($listownerID, $username) = mysqli_fetch_row($listowners))
{
  if (! $db->Query("SELECT listname FROM listconfig WHERE listownerID='$listownerID' ORDER BY listname"))
    exit("ERROR: listconfig does not have a list for listowner=$username listownerID=$listownerID\n");

  $data = $db->result;
  while(list($listname) = mysqli_fetch_row($data))
  {
    if (! $db->Query("SELECT listname FROM listmanager WHERE listownerID='$listownerID' AND listname='$listname'"))
      exit("ERROR: listmanager does not have listname=$listname yet listconfig does\n");
    else if (! $db->Query("SELECT listname FROM system WHERE listownerID='$listownerID' AND listname='$listname'"))
      exit("ERROR: system does not have listname=$listname listownerID=$listownerID\n");
    else if (! $db->Query("SELECT listname FROM listurls WHERE listownerID='$listownerID' AND listname='$listname'"))
      exit("ERROR: listurls does not have listname=$listname listownerID=$listownerID\n");
    else
      $lists[$listownerID][$listname] = $username;
  }
}

// check all users belong to a listownerID and listname
$db->Query("SELECT listownerID, listname, userID FROM users WHERE 1 ORDER BY userID");
$users = $db->result;
while(list($listownerID, $listname, $userID) = mysqli_fetch_row($users))
{
  echo "Checking userID=$userID\n";

  if (! check_for($listownerID, $listname))
  {
    check_for('', '', 1);
    exit("ERROR: userID=$userID does not belong to a known listownerID=$listownerID and listname=$listname\n");
  }
}

// PlanetXMail id = 4032668343

?>
