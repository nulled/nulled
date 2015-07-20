<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');

$ids = $ex_ids = array();

$db = new MySQL_Access("mle");

$db->Query("SELECT listownerID, username FROM listowner WHERE username != 'demoit' ORDER BY username");
$result = $db->result;
while (list($listownerID, $listownername) = mysqli_fetch_row($result))
{
  $db->SelectDB("mle");
  if (! $db->Query("SELECT listname FROM listconfig WHERE listownerID='$listownerID'")) exit("ERROR: listownerID=$listownerID NOT FOUND\n");
  $result2 = $db->result;
  while (list($listname) = mysqli_fetch_row($result2))
  {
    $db->SelectDB("pxm");
    if ($db->Query("SELECT id FROM orders WHERE listname='$listname' AND listownername='$listownername'"))
    {
      if ($db->rows > 1)
        echo "------> DUP FOUND: $listname, $listownername\n";
      else
      {
        list($ids[]) = $db->FetchRow();
        echo "OK: $listname, $listownername\n";
      }
    }
    else if ($db->Query("SELECT id FROM extended WHERE listname='$listname' AND listownername='$listownername'"))
    {
      list($ex_ids[]) = $db->FetchRow();
      echo "OK EX: $listname, $listownername\n";
    }
    else
      echo "-------------------------> NOT FOUND: $listname, $listownername\n";
  }
}

$db->SelectDB("pxm");

$db->Query("SELECT id FROM orders WHERE 1 ORDER BY id");
while (list($id) = $db->FetchRow()) if (! in_array($id, $ids)) echo "-------------------------> STRAY ORDER: $id\n";

$db->Query("SELECT id FROM extended WHERE 1 ORDER BY id");
while (list($id) = $db->FetchRow()) if (! in_array($id, $ex_ids)) echo "-------------------------> STRAY ORDER EX: $id\n";

?>
