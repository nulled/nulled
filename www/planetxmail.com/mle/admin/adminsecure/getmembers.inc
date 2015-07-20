<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access('mle');

$_listID = "listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'";

if ($getData)
{
  $db->Query("SELECT * FROM users WHERE verified='yes' AND status='mem' AND {$_listID} ORDER BY username");
  $memData = $db->result;
  $memNum = $db->rows;

  $db->Query("SELECT * FROM users WHERE verified='yes' AND status='pro' AND {$_listID} ORDER BY username");
  $proData = $db->result;
  $proNum = $db->rows;

  $db->Query("SELECT * FROM users WHERE verified='yes' AND status='exe' AND {$_listID} ORDER BY username");
  $exeData = $db->result;
  $exeNum = $db->rows;

  $db->Query("SELECT * FROM users WHERE verified='no' AND {$_listID} ORDER BY username");
  $unvData = $db->result;
  $unvNum = $db->rows;
}
else
{
  $db->Query("SELECT COUNT(*) FROM users WHERE verified='yes' AND status='mem' AND {$_listID} ORDER BY username");
  list($memNum) = $db->FetchRow();

  $db->Query("SELECT COUNT(*) FROM users WHERE verified='yes' AND status='pro' AND {$_listID} ORDER BY username");
  list($proNum) = $db->FetchRow();

  $db->Query("SELECT COUNT(*) FROM users WHERE verified='yes' AND status='exe' AND {$_listID} ORDER BY username");
  list($exeNum) = $db->FetchRow();

  $db->Query("SELECT COUNT(*) FROM users WHERE verified='no' AND {$_listID} ORDER BY username");
  list($unvNum) = $db->FetchRow();
}

$totalAll = $memNum + $proNum + $exeNum;

?>