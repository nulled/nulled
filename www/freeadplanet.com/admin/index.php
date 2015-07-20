<?php
require_once('/home/nulled/www/freeadplanet.com/secure/admin.inc');
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html>
<head>
<META HTTP-EQUIV="CONTENT-TYPE" CONTENT="text/html; charset=UTF-8">
<title>Free AD Planet - Admin</title>
<link rel="stylesheet" type="text/css" href="../x.css" />
<script>
<!--
function updateTotal(id)
{
  var box = document.getElementById(id);
  var amount = Number(box.value);
  var el = document.getElementById('total');
  var total = Number(el.value);
  if (box.checked == true)
    total += amount;
  else
    total -= amount;

  total = total.toFixed(2);
  el.value = total;
}
function payOut(updateURL)
{
  var inc = 0;
  var ids = '';

  var el = document.getElementById('total');
  var total = Number(el.value);
  if (total < 1)
  {
    alert('Please select amounts to Pay Out.');
    return;
  }

  var pp = document.getElementById('paypal');
  var ap = document.getElementById('alertpay');
  var eg = document.getElementById('egold');

  if (pp == null && ap == null && eg == null)
  {
    alert('Please select a Method of Payment.');
    return;
  }

  if (document.myform.amount.length)
  {
    for (i=0; i < document.myform.amount.length; i++)
    {
      if (document.myform.amount[i].checked)
      {
        if (inc == 0)
          ids = document.myform.amount[i].id;
        else
          ids += '.' + document.myform.amount[i].id;

        inc++;
      }
    }
  }
  else
  {
    if (document.myform.amount.checked)
      ids = document.myform.amount.id;
  }

  // alert(ids); return;

  if (ids == '')
  {
    alert('ERROR: No ids. This code should never execute.');
    return;
  }

  // var eg_url = 'http://<?php echo $egold; ?>-USD'+ total + '.00-Gold.e-gold.com';
  // var pp_url = 'https://www.paypal.com/cgi-bin/webscr?cmd=_xclick&business=<?php echo $paypal; ?>&item_name=Free+AD+Planet&item_number=' + ids + '&amount=' + total + '&no_shipping=1&merchant_return_link=<?php echo urlencode("http://freeadplanet.com/admin/?c=payout_return&mop=paypal&sponsor=$sponsor&ids="); ?>' + ids + '&cancel_return=<?php echo urlencode("http://freeadplanet.com/admin/?c=payout&sponsor=$sponsor"); ?>&no_note=1&currency_code=USD&lc=US&bn=PP%2dBuyNowBF&charset=UTF%2d8';

  var return_url       = '<?php echo urlencode("http://freeadplanet.com/admin/?c=payout_return&mop=alertpay&sponsor=$sponsor&ids="); ?>' + ids;
  var return_url_plain = '<?php echo "http://freeadplanet.com/admin/?c=payout_return&mop=alertpay&sponsor=$sponsor&ids="; ?>' + ids;

  var ap_url = 'https://www.alertpay.com/PayProcess.aspx?ap_purchasetype=Item&ap_merchant=<?php echo $alertpay; ?>&ap_itemname=Free+AD+Planet&ap_returnurl=<?php echo urlencode("http://freeadplanet.com/admin/?c=payout_return"); ?>&ap_currency=USD&ap_quantity=1&ap_description=' + ids + '&ap_amount=' + total;
  // var ap_url = 'https://www.alertpay.com/PayProcess.aspx?ap_purchasetype=Item&ap_merchant=<?php echo $alertpay; ?>&ap_itemname=Free+AD+Planet&ap_currency=USD&ap_returnurl='+ return_url + '&ap_quantity=1&ap_description=' + ids + '&ap_amount=' + total;
  // + '&ap_cancelurl=<?php echo urlencode("http://freeadplanet.com/admin/?c=payout&sponsor=$sponsor"); ?>;

  if (updateURL)
  {
    document.getElementById('returnURL').value = return_url_plain;
    return;
  }

  // alert(ap_url); return;

  if (ap) if (ap.checked) { location.href=ap_url; return; }
  // if (pp) if (pp.checked) { location.href=pp_url; return; }
  // if (eg) if (eg.checked) { location.href=eg_url; return; }

  alert('Please select a Method of Payment.');
}
function saveOnly()
{
  document.getElementById('submitted').value = 'save';
  document.forms[0].submit();
}
-->
</script>
</head>
<?php flush(); ?>
<body>
<table bgcolor="white" align="center" width="600" style="border-collapse: collapse" bordercolor="#000000" border="1" cellspacing="0" cellpadding="0"><tr><td>
<table bgcolor="white" align="left" border="0" width="600" cellpadding="0" cellspacing="0">
  <tr>
    <td>
      <?php echo $main_content; ?>
    </td>
  </tr>
</table>
</td></tr></table>
<script type="text/javascript">
<!--
  document.forms[0].username.focus();
-->
</script>
</body>
</html>
