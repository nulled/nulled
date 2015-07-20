<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');

if (! $id OR ! $mop)
{
  header("Location: index.php");
  exit;
}

session_start();

$db = new MySQL_Access('pxm');

if ($ex == '1')
{
  if (! $listownername)
    exit("ERROR: code 3 error, please contact <b>elitescripts2000@yahoo.com</b> stating you got an Error Code 3");

  $db->Query("SELECT price, listtype FROM extended WHERE id='$id' AND verified='no'");
}
else
  $db->Query("SELECT price, listtype FROM orders WHERE id='$id' AND verified='no'");

if (! $db->rows)
  exit("ERROR: code 2 error, please contact <b>elitescripts2000@yahoo.com</b> stating you got an Error Code 2");

list($price, $listtype) = $db->FetchRow();

if ($listtype=="safelist")        $listtype = "SafeList";
else if ($listtype=="newsletter") $listtype = "NewsLetter";

switch ($price)
{
  case 20:
    $cblink = 1;
    break;
  case 25:
    $cblink = 2;
    break;
  case 30:
    $cblink = 3;
    break;
  case 35:
    $cblink = 4;
    break;
  case 40:
    $cblink = 5;
    break;
  case 45:
    $cblink = 6;
    break;
  case 50:
    $cblink = 7;
    break;
  case 55:
    $cblink = 8;
    break;
  case 60:
    $cblink = 9;
    break;
  case 65:
    $cblink = 10;
    break;
  case 70:
    $cblink = 11;
    break;
  case 75:
    $cblink = 12;
    break;
  case 80:
    $cblink = 13;
    break;
  case 85:
    $cblink = 14;
    break;
  case 90:
    $cblink = 15;
    break;
  case 95:
    $cblink = 16;
    break;
  default:
    exit("File: paylinks.inc The price switch could not find a price in its case. <a href=\"http://planetxmail.com/openticket.php\">Open Ticket</a>");
}

if ($mop=="clickbank")
{
  // <a href="http://47.nulled.pay.clickbank.net?vtid=' . $id . '"><img src="images/clickbank_logo.jpg" border="0" /></a>
  header("Location: http://{$cblink}.nulled.pay.clickbank.net?vtid={$id}Z{$ex}");
  exit;
}

?>