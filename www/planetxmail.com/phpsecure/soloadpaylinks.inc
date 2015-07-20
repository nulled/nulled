<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');

$hash = substr(sha1($id . 'sahfme845jdkdhf87hff'), 0, 5);
if ($hash != $h) exit('ERROR: Invalid ID.');

if ($type == 'html')
{
  $img = "htmlsolo_ad_title.jpg";
  $bg = "bg_htmlsoloads.jpg";
}
else
{
  $img = "solo_ad_title.jpg";
  $bg = "sun30.jpg";
}

$ipaddress = $_SERVER['REMOTE_ADDR'];

if (! is_numeric($id))
  exit('ERROR: Invalid ID.');

$db = new MySQL_Access('mle');

if ($db->Query("SELECT name, email FROM soloads WHERE id='$id' AND receipt != '' LIMIT 1"))
  exit('Order already processed.');
list($name, $email) = $db->FetchRow();

// calc member totals
$totalmembers = $db->Query("SELECT username FROM users WHERE 1");
$totalowners  = $db->Query("SELECT username FROM listowner WHERE 1");
$totallists   = $db->Query("SELECT listname FROM listconfig WHERE 1");

$totalmembers += 240000;
$totalowners  += 195;
$totallists   += 235;

// calc solo ads for the day for each pay processor
$soloads = array();

$db->SelectDB('pxm');

$db->Query("SELECT CURDATE()");
list($cur_date) = $db->FetchRow();

$soloads['clickbank']   = $db->Query("SELECT mop FROM transactions WHERE product='soload' AND mop='clickbank' AND dateofsale LIKE '$cur_date %'");
$soloads['twocheckout'] = $db->Query("SELECT mop FROM transactions WHERE product='soload' AND mop='twocheckout' AND dateofsale LIKE '$cur_date %'");

$payforms = '';

if ($soloads['twocheckout'] < 3)
{
  $payforms .= '
<tr><td valign="top" align="center" colspan="2">
<br />
<a href="https://www.2checkout.com/2co/buyer/purchase?sid=25344&quantity=1&product_id=1&merchant_order_id=' . $id . '&fixed=Y">
<font size="+1">2CheckOut accepts PayPal</font><br />
<img src="https://www.2checkout.com/upload/images/paymentlogoshorizontal.png" border="0" />
</a>
<br /><span class="or">OR</span><br /><br />
</td></tr>
';
}

if ($soloads['clickbank'] < 6)
{
  $payforms .= '
<tr><td valign="top" align="center" colspan="2">
<a href="http://47.nulled.pay.clickbank.net?vtid=' . $id . '"><img src="images/clickbank_logo.jpg" border="0" /></a>
<br /><br /><span class="or">OR</span><br /><br />
</td></tr>
';
}

$payforms .= '
<tr><td valign="top" align="center" colspan="2">
<a href="https://www.alertpay.com/PayProcess.aspx?ap_purchasetype=Item&ap_merchant=elitescripts2000%40yahoo.com&ap_itemname=Contact+AD&ap_currency=USD&ap_returnurl=http%3a%2f%2fplanetxmail.com%2fsoloadthankyou.php&ap_quantity=1&ap_description=To+-+Contact+Address&ap_amount=30.00&ap_cancelurl=http%3a%2f%2fplanetxmail.com%2fcancellorder.php&apc_1='.$id.'"><img src="/images/payza-checkout.png" border="0" /></a>
<br />
<a href="https://secure.payza.com/?VwPhQPpbqEhle2hgofIZ%2fA%3d%3d" target="_blank">Get a Payza Account</a>
<br /><br /><span class="or">OR</span><br /><br />
</td></tr>
';
/*
$payforms .= '
<tr><td valign="top" align="center" colspan="2">
<a class="coinbase-button" data-code="585eca49e08ecd97f0c9c3a8c95c0aeb" data-button-style="buy_now_small" data-custom="'.$id.'" href="https://coinbase.com/checkouts/585eca49e08ecd97f0c9c3a8c95c0aeb">
  Pay With Bitcoin</a><script src="https://coinbase.com/assets/button.js" type="text/javascript"></script>
</td></tr>
';
*/

?>

