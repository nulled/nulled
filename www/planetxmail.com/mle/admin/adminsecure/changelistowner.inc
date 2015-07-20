<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if (! @is_numeric($id) OR has_weird($list))
{
  header('Location: main.php?firstList=1');
  exit;
}

$_SESSION['aalistownerID']   = $id;
$_SESSION['aalistownername'] = $list;

$db = new MySQL_Access('mle');

if (! $db->Query("SELECT listname FROM listmanager WHERE listownerID='{$id}' AND created='1' LIMIT 1"))
{
  header("Location: createlist.php?firstList={$firstList}");
  exit;
}

list($_SESSION['aalistname']) = $db->FetchRow();

header('Location: main.php?firstList=1');
exit;

?>