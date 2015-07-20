<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/soloadthankyou.inc');

@mail('elitescripts2000@yahoo.com', 'twocheckout.php post', print_r($_POST, 1), $headers);

if ($_POST['message_type'] == 'FRAUD_STATUS_CHANGED')
{
  $cgikey     = 'ntws40ntws40';
  $merchantID = '25344';

  $receipt    = trim($_POST['sale_id']);
  $vendor_id  = trim($_POST['vendor_id']); // $merchantID is same thing
  $invoice_id = trim($_POST['invoice_id']);
  $status     = trim($_POST['invoice_status']); // approved, deposited
  $id         = trim($_POST['vendor_order_id']);
  $fraud      = trim($_POST['fraud_status']); // pass, wait, fail
  $ipaddress  = trim($_POST['customer_ip']);
  $key        = trim($_POST['md5_hash']);
  $item_name  = trim($_POST['item_name_1']);

  $hash = strtoupper(md5($receipt.$vendor_id.$invoice_id.$cgikey));

  if ($key != $hash)
    @mail("elitescripts2000@yahoo.com", "SOLOAD 2co Hash bad", "hash:$hash key:$key id:$id receipt:$receipt fraud:$fraud", $headers);
  else if ($fraud != 'pass')
    @mail("elitescripts2000@yahoo.com", "SOLOAD 2co fraud",    "item_name:$item_name id:$id receipt:$receipt fraud:$fraud", $headers);
  else if ($item_name != 'Contact SoloAD')
    @mail("elitescripts2000@yahoo.com", "SOLOAD 2co bad item", "item_name:$item_name id:$id receipt:$receipt fraud:$fraud", $headers);
  else
    process_soload($id, 'twocheckout', $receipt, $fraud);
}

?>
