<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/phpsecure/cbvalid.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

function process_soload($id, $mop, $receipt, $fraud = '')
{
  global $headers, $ipaddress; // $ipaddress must be global cuz in twocheckout.php we get ip from POST data

  $db = new MySQL_Access('mle');

  $price = '30'; // needed for inset into pxm.transactions

  $date = date('F j, Y');

  $soload_type = 'Contact Address';

  if (! is_numeric($id))
    exit('<h2>Your Order was Already Processed. C1</h2>');

  // temp, to prevent clickbank cbValid() from multiple receipts, in future will want to
  // use clickbanks IPN to stop this.
  if ($receipt)
  {
    if ($db->Query("SELECT receipt FROM soloads WHERE receipt='$receipt' LIMIT 1"))
      exit("<h2>Your Order was Already Processed. C2</h2>");
  }
  else
    exit("<h2>Your Order was Already Processed. C3</h2>");

  if ($db->Query("SELECT name, email, subject, message, listname, crediturl FROM soloads WHERE id='$id' AND receipt = '' LIMIT 1"))
  {
    list($name, $email, $adsubject, $admessage, $type, $crediturl) = $db->FetchRow();

    if ($mop == 'twocheckout' AND $fraud != 'pass') // pass, wait, fail
    {
      if ($fraud == 'wait')
        $message = file_get_contents('/home/nulled/www/planetxmail.com/messages/soload_2co_pending_notice.txt');
      else if ($fraud != 'pass')
        $message = file_get_contents('/home/nulled/www/planetxmail.com/messages/soload_2co_fraud_notice.txt');

      $message = str_replace(array('[name]','[receipt]'), array($name, $receipt), $message);

      mail($email, 'PXM Solo Ad Order - ' . strtoupper($fraud), $message, $headers);
      //mail('elitescripts2000@yahoo.com', 'soloadthankyou.inc', "twocheckout - id:$id receipt:$receipt name:$name email:$email", $headers);
      exit;
    }

    $db->Query("UPDATE soloads SET receipt='$receipt', mop='$mop' WHERE id='$id' LIMIT 1");

    if (is_numeric($crediturl))
    {
      if ($db->Query("SELECT url FROM userlinks WHERE id='$crediturl' LIMIT 1"))
        list($crediturl) = $db->FetchRow();
      else
        $crediturl = 'Was not Supplied.';
    }
    else
      $crediturl = 'Was not Supplied.';

    // mail buyer
    $subject = 'Planet X Mail SOLO AD Receipt';
    $message = file_get_contents('/home/nulled/www/planetxmail.com/messages/soloadreceipt.txt');

    if (strstr($type, 'HTMLSOLOAD'))
    {
      //$message = str_replace("\n", "<br />\n", $message);
      //$headers .= "\nContent-Type: text/html; charset=iso-8859-1";
      $content_format = 'HTML';
    }
    else
      $content_format = 'Plain Text';

    $hash = substr(sha1($id . sha1('jfHdf8745JfhfdjdiLuaQ')), 0, 5);

    $sastatuslink = "http://planetxmail.com/sastatus.php?v=$id&h=$hash";

    $message = str_replace(
    array("[subject]","[message]","[mop]","[date]","[ipaddress]","[sastatus_link]","[name]","[content_format]","[soload_type]","[receipt_id]","[credit_url]"),
    array($adsubject,   $admessage,$mop,   $date,   $ipaddress,   $sastatuslink,    $name,   $content_format,   $soload_type,   $receipt,      $crediturl),
    $message);

    $message = wordwrap($message, 70);

    mail($email, $subject, $message, $headers);
    mail('elitescripts2000@yahoo.com', $subject, $message, $headers);

    if ($mop == 'clickbank')
    {
      $fees = $price * .075;
      $price -= 1;
      $price -= $fees;
      $profits = number_format($price, 2, '.', '');
    }
    else if ($mop == 'twocheckout')
    {
      $fees = $price * .055;
      $price -= 0.45;
      $price -= $fees;
      $profits = number_format($price, 2, '.', '');
    }
    else if ($mop == 'payza')
    {
      $fees = $price * .059;
      $price -= 0.39;
      $price -= $fees;
      $profits = number_format($price, 2, '.', '');
    }
    else
      $profits = number_format($price, 2, '.', '');

    if ($crediturl === 'Was not Supplied.')
      $crediturl = 'http://planetxmail.com/soloads.php';

    $adsubject = addslashes($adsubject);
    $admessage = addslashes($admessage);

    $adtype = (strstr($type, 'HTMLSOLOAD')) ? '2' : '1'; // 2 means HTML 1 means Plain Text Solo Ad

    $db->SelectDB('fap');
    $db->Query("INSERT INTO mailqueue (affid, subject, message, crediturl, usecredits, soload, datesubmitted)
                                VALUES('11187448','$adsubject', '$admessage', '$crediturl', '0', '$adtype', NOW())");

    $db->SelectDB('tap');
    $db->Query("INSERT INTO mailqueue (affid, subject, message, crediturl, usecredits, soload, datesubmitted)
                                VALUES('99999','$adsubject', '$admessage', '$crediturl', '0', '$adtype', NOW())");

    $db->SelectDB('pxm');
    
    // size of sha1 is 40 chars, so we know this was a tripped FREE soload, do not make transaction for it ...
    if (strlen($receipt) != 40)  
    {
      $db->Query("INSERT INTO transactions (product, amount, mop, receipt, dateofsale)
                                   VALUES('soload','$profits','$mop','$receipt',NOW())");
    }
  }
  else
    exit("<h2>Your Order was Already Processed. C5</h2>");
}

$headers   = 'From: Planet X Mail Solo AD <do_not_reply@planetxmail.com>';
$ipaddress = $_SERVER['REMOTE_ADDR'];

// used to generate a FREE soload, the GET must be the soload ID
// this will create solo ad for MLE, FAP and TAP
if (is_numeric($_GET['jjdhdiaFS87WF3hdj']))
{
  mail('elitescripts2000@yahoo.com', 'soloadthankyou free was tripped', $ipaddress);

  $id = trim($_GET['jjdhdiaFS87WF3hdj']);
  $receipt = sha1(mt_rand().rand().time().microtime(true)); 
  process_soload($id, 'clickbank', $receipt);
}
else if ($_GET['cbreceipt'])
{
  $id      = $_GET['vtid'];
  $receipt = $_GET['cbreceipt'];

  if (! cbValid())
  {
    $time  = $_GET['time'];
    $item  = $_GET['item'];
    $cbpop = $_GET['cbpop'];

    echo '<h2>Order Already Processed!</h2>';
    echo '<a href="http://planetxmail.com/openticket.php">Open Support Ticket</a>';
    //@mail('elitescripts2000@yahoo.com', 'SOLOAD cbValid fail', "id:$vtid cbpop:$cbpop cbreceipt:$receipt item:$item time:$time", $headers);
  }
  else
    process_soload($id, 'clickbank', $receipt);
}
else if ($_POST['ap_securitycode']) // payza
{
  $ap_itemname         = $_POST['ap_itemname'];
  $ap_amount           = $_POST['ap_amount'];
  $ap_totalamount      = $_POST['ap_totalamount'];
  $receipt             = $_POST['ap_referencenumber'];
  $id                  = $_POST['apc_1'];
  $ap_securitycode     = $_POST['ap_securitycode'];

  if ('lk7f53bPo/6P7oF5QgR6wQ' == $ap_securitycode)
    process_soload($id, 'payza', $receipt);
  else
    @mail('elitescripts2000@yahoo.com', 'SOLO AD Payza Hash keys do not match', "ap_securitycode={$ap_securitycode}", $headers);
}
else if ($_POST['merchant_order_id']) // 2checkout
{
  //@mail('elitescripts2000@yahoo.com', '2co soloadthankyou', print_r($_POST, 1), $headers);

  $id                    = $_POST['merchant_order_id'];
  $receipt               = $_POST['order_number'];
  $card_processed        = $_POST['credit_card_processed'];
  $email                 = $_POST['email'];
  $key                   = $_POST['key'];
  $total                 = $_POST['total'];

  $cgikey     = 'ntws40ntws40';
  $merchantID = '25344';

  // Y=creditcard OK, K=check but 2-3 days to clear
  if ($card_processed != 'Y' AND $card_processed != 'K')
    exit('twocheckout: Credit card not processed. credit_card_processed=' . $card_processed);

  $hash = strtoupper(md5($cgikey.$merchantID.$receipt.$total));

  if ($key != $hash)
  {
    @mail('elitescripts2000@yahoo.com', 'SOLO AD 2checkout Hash keys do not match', "hash={$hash}\nkey={$key}", $headers);
    exit('2checkout Hash keys do not match');
  }
  else
    process_soload($id, 'twocheckout', $receipt, 'wait');
}
else if ($_GET['obi'] == 'dHye683Jjdoeb7shd6') // coinbase (bitcoin)
{
  $json  = file_get_contents('php://input');
  $order = json_decode($json, 1);

  if ($order['order']['status'] == 'completed')
  {
    $receipt = $order['order']['id'];
    $id      = $order['order']['custom'];

    process_soload($id, 'coinbase', $receipt);

    @mail('elitescripts2000@yahoo.com', 'coinbase', print_r($order, 1), $headers);
    exit('200');
  }
}

// used for sastatus.php
$h = substr(sha1($id . sha1('jfHdf8745JfhfdjdiLuaQ')), 0, 5);

?>
