<?php
require_once('phpsecure/classes.inc');

$db = new MySQL_Access('mle');

if (! is_numeric($id)) exit('ERROR: id param not numeric.');
if (! ctype_alpha($page)) exit('ERROR: page param not correct.');

if ($db->Query("SELECT id FROM directads WHERE id='$id' AND page='$page'"))
{
  switch($numDays)
  {
    case 1:
      $amount = 15;
      $cblink = 36;
      break;
    case 2:
      $amount = 30;
      $cblink = 37;
      break;
    case 3:
      $amount = 40;
      $cblink = 38;
      break;
    case 4:
      $amount = 55;
      $cblink = 39;
      break;
    case 5:
      $amount = 70;
      $cblink = 40;
      break;
    case 6:
      $amount = 80;
      $cblink = 41;
      break;
    case 7:
      $amount = 90;
      $cblink = 42;
      break;
    case 8:
      $amount = 96;
      $cblink = 43;
      break;
    case 9:
      $amount = 98;
      $cblink = 44;
      break;
    case 10:
      $amount = 100;
      $cblink = 45;
      break;
    default:
      echo "Error: numDays param error. Admins have been contacted.";
      @mail("elitescripts2000@yahoo.com", "ERROR PXM Direct Ads", "ID = $id\n\nNum days not a valid param for directadpaylink.inc");
      exit;
  }

  $db->Query("UPDATE directads SET numDays='$numDays', amount='$amount' WHERE id='$id' AND page='$page'");
}
else
  exit("Error: ID not found.  Please Open a Ticket for further assistance.");

?>
