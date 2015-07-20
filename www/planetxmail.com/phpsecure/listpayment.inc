<?php
require_once('phpsecure/classes.inc');

$id = trim($_GET['id']);
$ex = trim($_GET['ex']);

if ($ex == '') $ex = '0';

if (is_numeric($id))
{
	$db = new MySQL_Access('pxm');

	if (! $ex)
	{
		$db->Query("SELECT price, paid FROM orders WHERE id='$id'");
		list($p, $paid) = $db->FetchRow();

		$p -= 25;
	}
	else
	{
		$db->Query("SELECT price, paid FROM extended WHERE id='$id'");
		list($p, $paid) = $db->FetchRow();
	}

	if (! $db->rows)
	{
		echo "<h2>Error: User can not be found.  Please contact: elitescripts2000@yahoo.com</h2>";
		@mail("elitescripts2000@yahoo.com", "PXM listpayment.inc error", "Error: User can not be found.\nid: $id");
		exit;
	}

	if ($paid == '1' OR $paid == 'yes')
		exit("<h2>This list is up-to-date and paid for!  Please wait until the next billing cycle. We will email you the bill.</h2>");

  switch ($p)
  {
    case 20:
      $cblink = 18;
      break;
    case 25:
      $cblink = 19;
      break;
    case 30:
      $cblink = 20;
      break;
    case 35:
      $cblink = 21;
      break;
    case 40:
      $cblink = 22;
      break;
    case 45:
      $cblink = 23;
      break;
    case 50:
      $cblink = 24;
      break;
    case 55:
      $cblink = 25;
      break;
    case 60:
      $cblink = 26;
      break;
    case 65:
      $cblink = 27;
      break;
    case 70:
      $cblink = 28;
      break;
    case 75:
      $cblink = 29;
      break;
    case 80:
      $cblink = 30;
      break;
    case 85:
      $cblink = 31;
      break;
    case 90:
      $cblink = 32;
      break;
    case 95:
      $cblink = 33;
      break;
    default:
      exit("File: paylinks.inc  The price switch could not find a price in its case. Please Open a Ticket if you need assistance.  Thank You.");
  }
}
else
  exit("ERROR: Missing id parameter. Please Open a Ticket if you need assistance.  Thank You.");

?>