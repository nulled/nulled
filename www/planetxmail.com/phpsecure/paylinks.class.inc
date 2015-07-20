<?php

class PayLinks
{
  public $db;
  public $userID;
  public $listownerID;
  public $listname;
  public $listhash;
  public $fname;
  public $lname;
  public $email;
  public $status;
  public $username;

  public $eg;
  public $tc;
  public $cb;
  public $ap;
  public $pp;

  public $signupcostpro, $renewalcostpro, $upgradecostpro, $signupcostexe;
  public $renewalcostexe, $upgradecostexe, $commissionpro, $commissionexe;
  public $allowcommissions, $defaultstatus;

  public $paypal, $egold, $cbusername, $cbsignupprolink, $cbsignupexelink, $cbrenewalprolink, $cbrenewalexelink;
  public $cbupgradeprolink, $cbupgradeexelink, $egoldaltpass, $dobillingcheck;
  public $renewaltype, $testmode_username, $proupgradeform, $exeupgradeform;

  public $tcousername, $tcosignuppro, $tcosignupexe, $tcorenewalpro, $tcorenewalexe, $tcoupgradepro, $tcoupgradeexe, $tcocgikey;

  public $alertpay, $alertpaycgikey, $allowupgrades, $memberpaid;

  function PayLinks($userID)
  {
    if (strlen($userID) != 10) exit('FATAL ERROR: userID is not valid in PayLinks()');

    $this->db     = new MySQL_Access('mle');
    $this->userID = $userID;

    if ($notValid=$this->get_data()) exit($notValid);

    if ($this->testmode_username)
    {
      $ap_test = '&ap_test=1';
      $tc_test = '&demo=Y';
      $pp_test  = '<form name="paypal" action="https://www.sandbox.paypal.com/cgi-bin/webscr" method="POST">'."\n";
    }
    else
    {
      $ap_test = '';
      $tc_test = '';
      $pp_test = '<form name="paypal" action="https://secure.paypal.com/cgi-bin/webscr" method="POST">';
    }

// OLD way - http://www.clickbank.net/sell.cgi?link=[cb_username]/[cb_link]/[title]&id=[transaction_data]
// NEW way - http://ITEM.VENDOR.pay.clickbank.net?vtid=24CharAlphaNumericValue

    $this->cb = '
    <a href="http://[cb_link].nulled.pay.clickbank.net?tvid=[transaction_data]"><img src="http://planetxmail.com/images/cblogo.jpg" border="0" /><br /><img src="http://freeadplanet.com/images/cards.gif" border="0" /></a>
    ';

    $this->tc = '
    <a href="https://www.2checkout.com/2co/buyer/purchase?sid=[tco_username]&quantity=1&product_id=[tco_link]&merchant_order_id=[transaction_data]&pxm_data=[transaction_data]&fixed=Y'.$tc_test.'"><img src="http://planetxmail.com/images/2cocc06.gif" border="0" /></a>
    ';

    $this->ap = '
    <a href="https://www.alertpay.com/PayProcess.aspx?ap_purchasetype=Item&ap_merchant=[ap_account]&ap_itemname=[title]&ap_currency=USD&ap_returnurl='.urlencode('http://planetxmail.com/mle/processorder.php?pxm_data=').'[transaction_data]&ap_quantity=1&ap_amount=[price]&ap_cancelurl='.urlencode('http://planetxmail.com/mle/processorder.php?pxm_label=cancel').'&apc_1=[transaction_data]'.$ap_test.'"><img src="http://planetxmail.com/images/alertpay_icon.gif" border="0" /></a>
    ';

    $this->eg = '
    <form action="https://www.e-gold.com/sci_asp/payments.asp" method="POST" class="blankform">
      <input type="hidden" name="PAYEE_ACCOUNT" value="[egold_account]">
      <input type="hidden" name="PAYEE_NAME" value="[title]">
      <input type="hidden" name="PAYMENT_AMOUNT" value="[price]" size="4" readonly />
      <input type="hidden" name="PAYMENT_UNITS" value="1" />
      <input type="hidden" name="PAYMENT_METAL_ID" value="1">
      <input type="hidden" name="SUGGESTED_MEMO" value="[title]">
      <input type="hidden" name="STATUS_URL" value="http://planetxmail.com/mle/processorder.php?pxm_data=[transaction_data]">
      <input type="hidden" name="NOPAYMENT_URL" value="http://planetxmail.com/mle/processorder.php?pxm_label=cancel">
      <input type="hidden" name="NOPAYMENT_URL_METHOD" value="LINK">
      <input type="hidden" name="PAYMENT_URL" value="http://planetxmail.com/mle/processorder.php?pxm_data=[transaction_data]">
      <input type="hidden" name="PAYMENT_URL_METHOD" value="LINK">
      <input type="hidden" name="BAGGAGE_FIELDS" value="CUSTOMERID">
      <input type="hidden" name="CUSTOMERID" value="[transaction_data]">
      <input type="image" src="http://planetxmail.com/images/egold_logo.jpg">
    </form>
    ';

    $this->pp = '
    '.$pp_test.'
      <input type="hidden" name="cmd" value="_xclick">
      <input type="hidden" name="business" value="[paypal_account]">
      <input type="hidden" name="item_name" value="[title]">
      <input type="hidden" name="item_number" value="[item_data]">
      <input type="hidden" name="custom" value="[transaction_data]">
      <input type="hidden" name="amount" value="[price]">
      <input type="hidden" name="no_shipping" value="1">
      <input type="hidden" name="return" value="http://planetxmail.com/mle/processorder.php?pxm_data=[transaction_data]">
      <input type="hidden" name="cancel_return" value="http://planetxmail.com/mle/processorder.php?pxm_label=cancel">
      <input type="image" src="http://planetxmail.com/images/pp_verified.gif" name="I1"><br />
      <input type="image" src="http://planetxmail.com/images/pp_logo_creditcard.gif" name="I1"><br />
    </form>
    ';
  }

  function get_data()
  {
    if ($this->db->Query("SELECT username, fname, lname, email, status, listname, listownerID, memberpaid FROM users WHERE userID='{$this->userID}'"))
      list($this->username, $this->fname, $this->lname, $this->email, $this->status, $this->listname, $this->listownerID, $this->memberpaid) = $this->db->FetchRow();
    else
      return 'ERROR: Unable to find userID in get_data()';

    if ($this->db->Query("SELECT listhash FROM listurls WHERE listownerID='{$this->listownerID}' AND listname='{$this->listname}'"))
      list($this->listhash) = $this->db->FetchRow();
    else
      return 'ERROR: Unable to find listhash in get_data()';

    if ($this->db->Query("SELECT defaultstatus, allowupgrades, proupgradeform, exeupgradeform, testmode_username, numurltrackerspro, numurltrackersexe, costofpro, costofexe, commission, memsendmailweek, prosendmailweek, memsendmailcreditsweek, prosendmailcreditsweek, freestartcredits, prostartcredits, exestartcredits, freeearnedcredits, proearnedcredits, exeearnedcredits FROM listconfig WHERE listname='{$this->listname}' AND listownerID='{$this->listownerID}'"))
      list($this->defaultstatus, $this->allowupgrades, $this->proupgradeform, $this->exeupgradeform, $this->testmode_username, $this->numurltrackerspro, $this->numurltrackersexe, $costofpro, $costofexe, $commission, $this->memsendmailweek, $this->prosendmailweek, $this->memsendmailcreditsweek, $this->prosendmailcreditsweek, $this->freestartcredits, $this->prostartcredits, $this->exestartcredits, $this->freeearnedcredits, $this->proearnedcredits, $this->exeearnedcredits) = $this->db->FetchRow();

    // check test mode
    if ($this->testmode_username && strcasecmp($this->testmode_username, $this->username)) exit('<center><b>Billing System is Under Test Mode... stay tuned.</b><br /><br /><input type="button" value="Go Back" onclick="javascript:history.back()" /></center>');

    list($this->signupcostpro, $this->renewalcostpro, $this->upgradecostpro) = explode('|', $costofpro);
    list($this->signupcostexe, $this->renewalcostexe, $this->upgradecostexe) = explode('|', $costofexe);
    list($this->commissionpro, $this->commissionexe, $this->allowcommissions) = explode('|', $commission);

    // fetch the lists prices and paylink params
    $this->db->Query("SELECT paylinkparams FROM listmanager WHERE listname='{$this->listname}' AND listownerID='{$this->listownerID}'");
    list($paylinkparams) = $this->db->FetchRow();

    list($this->paypal, $this->egold, $this->cbusername, $this->cbsignupprolink, $this->cbsignupexelink, $this->cbrenewalprolink, $this->cbrenewalexelink,
         $this->cbupgradeprolink, $this->cbupgradeexelink, $this->egoldaltpass, $this->dobillingcheck, $renewaltype, $clickbankcgikey, $cleanmembers,
         $this->tcousername, $this->tcosignuppro, $this->tcosignupexe, $this->tcorenewalpro, $this->tcorenewalexe, $this->tcoupgradepro, $this->tcoupgradeexe, $this->tcocgikey,
         $this->alertpay, $this->alertpaycgikey) = explode('|', $paylinkparams);

    if ($renewaltype=='0')      $this->renewaltype = 'Monthly';
    else if ($renewaltype=='1') $this->renewaltype = 'Bi-Monthly';
    else if ($renewaltype=='2') $this->renewaltype = 'Quarterly';
    else if ($renewaltype=='3') $this->renewaltype = 'Yearly';
    else if ($renewaltype=='4') $this->renewaltype = 'Lifetime';
    else
      exit('FATAL ERROR: Unable to determine renewaltype in get_data() PayLinks');
  }

  function get_paylink($merchant, $status, $type)
  {
    $allowed_types = array('signup','renew','upgrade');
    if (! in_array($type, $allowed_types)) exit('FATAL ERROR: type unknown in PayLinks()');
    $allowed_merchants = array('clickbank','twocheckout','egold','alertpay','paypal');
    if (! in_array($merchant, $allowed_merchants)) exit('FATAL ERROR: Unable to determine merchant in get_paylink() PayLinks.');

    if ($this->allowupgrades == 0 && $type == 'upgrade')
    {
      header('Location: main.php?option=memberprofile&notValid='.urlencode('The Listowner has disabled Upgrades! Notify your Listowner your interest in Upgrading. They must enable this feature.'));
      exit;
    }

    if ($this->memberpaid == 1 && $type == 'renew')
    {
      header('Location: login.php?l='.$this->listhash.'&notValid='.urlencode('This account is already paid. You can log in.'));
      exit;
    }

    if ($type == 'upgrade')
    {
      $title = 'Upgrade Membership to '.ucfirst($status);
      $cblinkpro  = $this->cbupgradeprolink;
      $cblinkexe  = $this->cbupgradeexelink;
      $tcolinkpro = $this->tcoupgradepro;
      $tcolinkexe = $this->tcoupgradeexe;
      $price_pro  = $this->upgradecostpro;
      $price_exe  = $this->upgradecostexe;
      $transaction_data_pro = $this->mixup_data(strtoupper($this->userID.'pro'.$type));
      $transaction_data_exe = $this->mixup_data(strtoupper($this->userID.'exe'.$type));
    }
    else if ($type == 'renew')
    {
      $title = 'Renew '.ucfirst($status).' Membership';
      $cblinkpro = $this->cbrenewalprolink;
      $cblinkexe = $this->cbrenewalexelink;
      $tcolinkpro = $this->tcorenewalpro;
      $tcolinkexe = $this->tcorenewalexe;
      $price_pro  = $this->renewalcostpro;
      $price_exe  = $this->renewalcostexe;
      $transaction_data_pro = $this->mixup_data(strtoupper($this->userID.'pro'.$type));
      $transaction_data_exe = $this->mixup_data(strtoupper($this->userID.'exe'.$type));
    }
    else if ($type == 'signup')
    {
      $title = 'Signup Membership as '.ucfirst($status);
      $cblinkpro = $this->cbsignupprolink;
      $cblinkexe = $this->cbsignupexelink;
      $tcolinkpro = $this->tcosignuppro;
      $tcolinkexe = $this->tcosignupexe;
      $price_pro  = $this->signupcostpro;
      $price_exe  = $this->signupcostexe;
      $transaction_data_pro = $this->mixup_data(strtoupper($this->userID.'pro'.$type));
      $transaction_data_exe = $this->mixup_data(strtoupper($this->userID.'exe'.$type));
    }
    else
      exit('FATAL ERROR: Unable to determined type in get_paylink() PayLinks.');

    $paypal_html_pro = $paypal_html_exe = $ap_html_pro = $ap_html_exe = $tco_html_pro = $tco_html_exe = $egold_html_pro = $egold_html_exe = $clickbank_html_pro = $clickbank_html_exe = '';

    if ($this->cbusername && $this->cbupgradeprolink && $this->cbupgradeexelink)
    {
    	if (($type == 'renew' && $this->status == 'pro') || $type == 'signup' || ($type == 'upgrade' && $this->status == 'mem'))
    	{
      	$clickbank_html_pro = str_replace("[title]", $title, $this->cb);
      	$clickbank_html_pro = str_replace("[cb_username]", $this->cbusername, $clickbank_html_pro);
      	$clickbank_html_pro = str_replace("[cb_link]", $cblinkpro, $clickbank_html_pro);
      	$clickbank_html_pro = str_replace("[transaction_data]", $transaction_data_pro, $clickbank_html_pro);
    	}

    	if (($type == 'renew' && $this->status != 'mem') || $type == 'signup' || ($type == 'upgrade' && ($this->status == 'mem' || $this->status == 'pro')))
    	{
      	$clickbank_html_exe = str_replace("[title]", $title, $this->cb);
      	$clickbank_html_exe = str_replace("[cb_username]", $this->cbusername, $clickbank_html_exe);
      	$clickbank_html_exe = str_replace("[cb_link]", $cblinkexe, $clickbank_html_exe);
      	$clickbank_html_exe = str_replace("[transaction_data]", $transaction_data_exe, $clickbank_html_exe);
    	}
    }

    if ($this->paypal)
    {
    	if (($type == 'renew' && $this->status == 'pro') || $type == 'signup' || ($type == 'upgrade' && $this->status == 'mem'))
    	{
      	$paypal_html_pro = str_replace("[title]", $title, $this->pp);
      	$paypal_html_pro = str_replace("[paypal_account]", $this->paypal, $paypal_html_pro);
      	$paypal_html_pro = str_replace("[price]", $price_pro, $paypal_html_pro);
      	$paypal_html_pro = str_replace("[item_data]", "{$this->listname} {$this->username}", $paypal_html_pro);
      	$paypal_html_pro = str_replace("[transaction_data]", $transaction_data_pro, $paypal_html_pro);
    	}

    	if (($type == 'renew' && $this->status != 'mem') || $type == 'signup' || ($type == 'upgrade' && ($this->status == 'mem' || $this->status == 'pro')))
    	{
      	$paypal_html_exe = str_replace("[title]", $title, $this->pp);
      	$paypal_html_exe = str_replace("[paypal_account]", $this->paypal, $paypal_html_exe);
     	  $paypal_html_exe = str_replace("[price]", $price_exe, $paypal_html_exe);
      	$paypal_html_exe = str_replace("[item_data]", "{$this->listname} {$this->username}", $paypal_html_exe);
      	$paypal_html_exe = str_replace("[transaction_data]", $transaction_data_exe, $paypal_html_exe);
    	}
    }

    if ($this->egold && $this->egoldaltpass)
    {
      if (($type == 'renew' && $this->status == 'pro') || $type == 'signup' || ($type == 'upgrade' && $this->status == 'mem'))
      {
      	$egold_html_pro = str_replace("[title]", $title, $this->eg);
      	$egold_html_pro = str_replace("[egold_account]", $this->egold, $egold_html_pro);
      	$egold_html_pro = str_replace("[price]", $price_pro, $egold_html_pro);
      	$egold_html_pro = str_replace("[transaction_data]", $transaction_data_pro, $egold_html_pro);
      }

      if (($type == 'renew' && $this->status != 'mem') || $type == 'signup' || ($type == 'upgrade' && ($this->status == 'mem' || $this->status == 'pro')))
      {
      	$egold_html_exe = str_replace("[title]", $title, $this->eg);
      	$egold_html_exe = str_replace("[egold_account]", $this->egold, $egold_html_exe);
      	$egold_html_exe = str_replace("[price]", $price_exe, $egold_html_exe);
      	$egold_html_exe = str_replace("[transaction_data]", $transaction_data_pro, $egold_html_exe);
      }
    }

    if ($this->tcousername && $this->tcocgikey)
    {
      if (($type == 'renew' && $this->status == 'pro') || $type == 'signup' || ($type == 'upgrade' && $this->status == 'mem'))
      {
      	$tco_html_pro = str_replace("[tco_username]", $this->tcousername, $this->tc);
      	$tco_html_pro = str_replace("[tco_link]", $tcolinkpro, $tco_html_pro);
      	$tco_html_pro = str_replace("[transaction_data]", $transaction_data_pro, $tco_html_pro);
      }

      if (($type == 'renew' && $this->status != 'mem') || $type == 'signup' || ($type == 'upgrade' && ($this->status == 'mem' || $this->status == 'pro')))
      {
      	$tco_html_exe = str_replace("[tco_username]", $this->tcousername, $this->tc);
      	$tco_html_exe = str_replace("[tco_link]", $tcolinkexe, $tco_html_exe);
      	$tco_html_exe = str_replace("[transaction_data]", $transaction_data_exe, $tco_html_exe);
      }
    }

    if ($this->alertpay && $this->alertpaycgikey)
    {
      if (($type == 'renew' && $this->status == 'pro') || $type == 'signup' || ($type == 'upgrade' && $this->status == 'mem'))
      {
      	$ap_html_pro = str_replace("[title]", $title, $this->ap);
      	$ap_html_pro = str_replace("[ap_account]", $this->alertpay, $ap_html_pro);
      	$ap_html_pro = str_replace("[price]", $price_pro, $ap_html_pro);
      	$ap_html_pro = str_replace("[transaction_data]", $transaction_data_pro, $ap_html_pro);
      }

      if (($type == 'renew' && $this->status != 'mem') || $type == 'signup' || ($type == 'upgrade' && ($this->status == 'mem' || $this->status == 'pro')))
      {
      	$ap_html_exe = str_replace("[title]", $title, $this->ap);
      	$ap_html_exe = str_replace("[ap_account]", $this->alertpay, $ap_html_exe);
      	$ap_html_exe = str_replace("[price]", $price_exe, $ap_html_exe);
      	$ap_html_exe = str_replace("[transaction_data]", $transaction_data_exe, $ap_html_exe);
      }
    }

    if ($merchant == 'clickbank' && $status == 'pro') return $clickbank_html_pro;
    if ($merchant == 'clickbank' && $status == 'exe') return $clickbank_html_exe;

    if ($merchant == 'egold' && $status == 'pro') return $egold_html_pro;
    if ($merchant == 'egold' && $status == 'exe') return $egold_html_exe;

    if ($merchant == 'twocheckout' && $status == 'pro') return $tco_html_pro;
    if ($merchant == 'twocheckout' && $status == 'exe') return $tco_html_exe;

    if ($merchant == 'alertpay' && $status == 'pro') return $ap_html_pro;
    if ($merchant == 'alertpay' && $status == 'exe') return $ap_html_exe;

    if ($merchant == 'paypal' && $status == 'pro') return $paypal_html_pro;
    if ($merchant == 'paypal' && $status == 'exe') return $paypal_html_exe;

    return '';
  }

  function get_benefits($status)
  {
    $test = '';
    if ($this->testmode_username) $test = ' <blink>Test mode is ON</blink>';

    if ($status == 'pro')
    {
      return "
      <font color=red><h2><u>Professional</u> Benefits$test</h2></font>

      <b>Create Credit URLs in Credit Mailer.</b><br />
      <b>{$this->numurltrackerspro}</b> URL Trackers<br />
      <b>{$this->prosendmailweek}</b> Regular Mailer mailings per week.<br />
      <b>{$this->prosendmailcreditsweek}</b> Credit Mailer mailings per week.<br />
      <b>{$this->prostartcredits}</b> credits awarded after upgrade.<br />
      <b>{$this->proearnedcredits}</b> credits earned per creditlink clicked.<br />
      <b>\$ {$this->upgradecostpro}</b> Low Price.
      ";
    }
    else if ($status == 'exe')
    {
      return "
      <font color=red><h2><u>Executive</u> Benefits$test</h2></font>

      <b>Create Credit URLs in Credit <u>and</u> Regular Mailers.</b><br />
      <b>{$this->numurltrackersexe}</b> URL Trackers<br />
      <b>7</b> Regular Mailer mailings per week.<br />
      <b>7</b> Credits Mailer mailings per week.<br />
      <b>{$this->exestartcredits}</b> credits awarded after upgrade.<br />
      <b>{$this->exeearnedcredits}</b> credits earned per creditlink clicked.<br />
      <b>\$ {$this->upgradecostexe}</b> Low Price.
      ";
    }
    else
      exit('FATAL ERROR: Unknown status in get_benefits() PayLinks.');
  }

  function get_shuffle($i)
  {
    $shuffles[0] = 'a:36:{i:0;s:1:"H";i:1;s:1:"4";i:2;s:1:"R";i:3;s:1:"W";i:4;s:1:"5";i:5;s:1:"J";i:6;s:1:"X";i:7;s:1:"N";i:8;s:1:"M";i:9;s:1:"1";i:10;s:1:"3";i:11;s:1:"S";i:12;s:1:"T";i:13;s:1:"C";i:14;s:1:"K";i:15;s:1:"B";i:16;s:1:"E";i:17;s:1:"Y";i:18;s:1:"Q";i:19;s:1:"F";i:20;s:1:"V";i:21;s:1:"I";i:22;s:1:"2";i:23;s:1:"G";i:24;s:1:"D";i:25;s:1:"9";i:26;s:1:"U";i:27;s:1:"7";i:28;s:1:"A";i:29;s:1:"P";i:30;s:1:"0";i:31;s:1:"Z";i:32;s:1:"6";i:33;s:1:"O";i:34;s:1:"8";i:35;s:1:"L";}';
    $shuffles[1] = 'a:36:{i:0;s:1:"R";i:1;s:1:"6";i:2;s:1:"W";i:3;s:1:"H";i:4;s:1:"I";i:5;s:1:"C";i:6;s:1:"Q";i:7;s:1:"A";i:8;s:1:"L";i:9;s:1:"J";i:10;s:1:"8";i:11;s:1:"1";i:12;s:1:"F";i:13;s:1:"Y";i:14;s:1:"V";i:15;s:1:"3";i:16;s:1:"X";i:17;s:1:"D";i:18;s:1:"K";i:19;s:1:"T";i:20;s:1:"7";i:21;s:1:"U";i:22;s:1:"0";i:23;s:1:"Z";i:24;s:1:"N";i:25;s:1:"O";i:26;s:1:"P";i:27;s:1:"S";i:28;s:1:"4";i:29;s:1:"9";i:30;s:1:"2";i:31;s:1:"E";i:32;s:1:"B";i:33;s:1:"G";i:34;s:1:"M";i:35;s:1:"5";}';
    $shuffles[2] = 'a:36:{i:0;s:1:"R";i:1;s:1:"Q";i:2;s:1:"3";i:3;s:1:"L";i:4;s:1:"W";i:5;s:1:"P";i:6;s:1:"G";i:7;s:1:"S";i:8;s:1:"Y";i:9;s:1:"M";i:10;s:1:"N";i:11;s:1:"9";i:12;s:1:"H";i:13;s:1:"Z";i:14;s:1:"X";i:15;s:1:"T";i:16;s:1:"8";i:17;s:1:"2";i:18;s:1:"B";i:19;s:1:"4";i:20;s:1:"J";i:21;s:1:"E";i:22;s:1:"0";i:23;s:1:"6";i:24;s:1:"7";i:25;s:1:"C";i:26;s:1:"1";i:27;s:1:"A";i:28;s:1:"F";i:29;s:1:"V";i:30;s:1:"D";i:31;s:1:"I";i:32;s:1:"5";i:33;s:1:"U";i:34;s:1:"O";i:35;s:1:"K";}';
    $shuffles[3] = 'a:36:{i:0;s:1:"I";i:1;s:1:"9";i:2;s:1:"Z";i:3;s:1:"0";i:4;s:1:"7";i:5;s:1:"L";i:6;s:1:"6";i:7;s:1:"2";i:8;s:1:"P";i:9;s:1:"C";i:10;s:1:"J";i:11;s:1:"3";i:12;s:1:"B";i:13;s:1:"D";i:14;s:1:"4";i:15;s:1:"U";i:16;s:1:"Y";i:17;s:1:"E";i:18;s:1:"V";i:19;s:1:"W";i:20;s:1:"O";i:21;s:1:"5";i:22;s:1:"N";i:23;s:1:"8";i:24;s:1:"M";i:25;s:1:"H";i:26;s:1:"R";i:27;s:1:"1";i:28;s:1:"S";i:29;s:1:"Q";i:30;s:1:"A";i:31;s:1:"X";i:32;s:1:"F";i:33;s:1:"K";i:34;s:1:"G";i:35;s:1:"T";}';
    $shuffles[4] = 'a:36:{i:0;s:1:"A";i:1;s:1:"J";i:2;s:1:"P";i:3;s:1:"9";i:4;s:1:"T";i:5;s:1:"M";i:6;s:1:"5";i:7;s:1:"L";i:8;s:1:"Z";i:9;s:1:"Q";i:10;s:1:"E";i:11;s:1:"D";i:12;s:1:"3";i:13;s:1:"R";i:14;s:1:"V";i:15;s:1:"0";i:16;s:1:"W";i:17;s:1:"8";i:18;s:1:"I";i:19;s:1:"B";i:20;s:1:"S";i:21;s:1:"F";i:22;s:1:"H";i:23;s:1:"O";i:24;s:1:"6";i:25;s:1:"U";i:26;s:1:"Y";i:27;s:1:"G";i:28;s:1:"2";i:29;s:1:"7";i:30;s:1:"K";i:31;s:1:"1";i:32;s:1:"N";i:33;s:1:"C";i:34;s:1:"X";i:35;s:1:"4";}';
    $shuffles[5] = 'a:36:{i:0;s:1:"K";i:1;s:1:"M";i:2;s:1:"Y";i:3;s:1:"B";i:4;s:1:"L";i:5;s:1:"N";i:6;s:1:"3";i:7;s:1:"G";i:8;s:1:"D";i:9;s:1:"R";i:10;s:1:"I";i:11;s:1:"6";i:12;s:1:"X";i:13;s:1:"O";i:14;s:1:"2";i:15;s:1:"8";i:16;s:1:"1";i:17;s:1:"A";i:18;s:1:"F";i:19;s:1:"5";i:20;s:1:"H";i:21;s:1:"U";i:22;s:1:"C";i:23;s:1:"4";i:24;s:1:"W";i:25;s:1:"J";i:26;s:1:"S";i:27;s:1:"Q";i:28;s:1:"E";i:29;s:1:"P";i:30;s:1:"V";i:31;s:1:"9";i:32;s:1:"0";i:33;s:1:"7";i:34;s:1:"T";i:35;s:1:"Z";}';
    $shuffles[6] = 'a:36:{i:0;s:1:"Q";i:1;s:1:"D";i:2;s:1:"4";i:3;s:1:"L";i:4;s:1:"M";i:5;s:1:"8";i:6;s:1:"3";i:7;s:1:"B";i:8;s:1:"C";i:9;s:1:"1";i:10;s:1:"G";i:11;s:1:"Y";i:12;s:1:"U";i:13;s:1:"5";i:14;s:1:"A";i:15;s:1:"0";i:16;s:1:"V";i:17;s:1:"P";i:18;s:1:"N";i:19;s:1:"9";i:20;s:1:"H";i:21;s:1:"S";i:22;s:1:"T";i:23;s:1:"F";i:24;s:1:"J";i:25;s:1:"O";i:26;s:1:"E";i:27;s:1:"6";i:28;s:1:"X";i:29;s:1:"I";i:30;s:1:"K";i:31;s:1:"W";i:32;s:1:"Z";i:33;s:1:"R";i:34;s:1:"2";i:35;s:1:"7";}';
    $shuffles[7] = 'a:36:{i:0;s:1:"O";i:1;s:1:"T";i:2;s:1:"8";i:3;s:1:"M";i:4;s:1:"5";i:5;s:1:"I";i:6;s:1:"H";i:7;s:1:"R";i:8;s:1:"2";i:9;s:1:"K";i:10;s:1:"X";i:11;s:1:"P";i:12;s:1:"6";i:13;s:1:"N";i:14;s:1:"Q";i:15;s:1:"V";i:16;s:1:"Y";i:17;s:1:"W";i:18;s:1:"G";i:19;s:1:"A";i:20;s:1:"F";i:21;s:1:"E";i:22;s:1:"4";i:23;s:1:"1";i:24;s:1:"7";i:25;s:1:"S";i:26;s:1:"Z";i:27;s:1:"C";i:28;s:1:"B";i:29;s:1:"L";i:30;s:1:"0";i:31;s:1:"J";i:32;s:1:"9";i:33;s:1:"D";i:34;s:1:"U";i:35;s:1:"3";}';
    $shuffles[8] = 'a:36:{i:0;s:1:"1";i:1;s:1:"L";i:2;s:1:"X";i:3;s:1:"V";i:4;s:1:"P";i:5;s:1:"J";i:6;s:1:"B";i:7;s:1:"U";i:8;s:1:"9";i:9;s:1:"K";i:10;s:1:"T";i:11;s:1:"C";i:12;s:1:"I";i:13;s:1:"E";i:14;s:1:"0";i:15;s:1:"Y";i:16;s:1:"Z";i:17;s:1:"R";i:18;s:1:"G";i:19;s:1:"W";i:20;s:1:"7";i:21;s:1:"F";i:22;s:1:"8";i:23;s:1:"D";i:24;s:1:"S";i:25;s:1:"Q";i:26;s:1:"2";i:27;s:1:"3";i:28;s:1:"A";i:29;s:1:"H";i:30;s:1:"4";i:31;s:1:"N";i:32;s:1:"6";i:33;s:1:"O";i:34;s:1:"5";i:35;s:1:"M";}';
    $shuffles[9] = 'a:36:{i:0;s:1:"D";i:1;s:1:"1";i:2;s:1:"S";i:3;s:1:"V";i:4;s:1:"M";i:5;s:1:"H";i:6;s:1:"4";i:7;s:1:"0";i:8;s:1:"I";i:9;s:1:"G";i:10;s:1:"P";i:11;s:1:"Q";i:12;s:1:"K";i:13;s:1:"T";i:14;s:1:"L";i:15;s:1:"X";i:16;s:1:"A";i:17;s:1:"7";i:18;s:1:"F";i:19;s:1:"U";i:20;s:1:"R";i:21;s:1:"6";i:22;s:1:"W";i:23;s:1:"5";i:24;s:1:"O";i:25;s:1:"8";i:26;s:1:"E";i:27;s:1:"Y";i:28;s:1:"2";i:29;s:1:"N";i:30;s:1:"Z";i:31;s:1:"C";i:32;s:1:"3";i:33;s:1:"B";i:34;s:1:"9";i:35;s:1:"J";}';
    $shuffles['A'] = 'a:36:{i:0;s:1:"U";i:1;s:1:"Y";i:2;s:1:"J";i:3;s:1:"B";i:4;s:1:"K";i:5;s:1:"E";i:6;s:1:"H";i:7;s:1:"5";i:8;s:1:"W";i:9;s:1:"7";i:10;s:1:"D";i:11;s:1:"T";i:12;s:1:"R";i:13;s:1:"F";i:14;s:1:"O";i:15;s:1:"L";i:16;s:1:"2";i:17;s:1:"C";i:18;s:1:"M";i:19;s:1:"I";i:20;s:1:"1";i:21;s:1:"N";i:22;s:1:"4";i:23;s:1:"9";i:24;s:1:"V";i:25;s:1:"Q";i:26;s:1:"8";i:27;s:1:"G";i:28;s:1:"6";i:29;s:1:"S";i:30;s:1:"Z";i:31;s:1:"X";i:32;s:1:"0";i:33;s:1:"A";i:34;s:1:"3";i:35;s:1:"P";}';
    $shuffles['B'] = 'a:36:{i:0;s:1:"1";i:1;s:1:"K";i:2;s:1:"D";i:3;s:1:"S";i:4;s:1:"7";i:5;s:1:"6";i:6;s:1:"R";i:7;s:1:"O";i:8;s:1:"F";i:9;s:1:"8";i:10;s:1:"V";i:11;s:1:"E";i:12;s:1:"X";i:13;s:1:"0";i:14;s:1:"5";i:15;s:1:"P";i:16;s:1:"9";i:17;s:1:"3";i:18;s:1:"U";i:19;s:1:"I";i:20;s:1:"B";i:21;s:1:"2";i:22;s:1:"J";i:23;s:1:"Y";i:24;s:1:"Q";i:25;s:1:"G";i:26;s:1:"C";i:27;s:1:"4";i:28;s:1:"N";i:29;s:1:"T";i:30;s:1:"L";i:31;s:1:"A";i:32;s:1:"Z";i:33;s:1:"M";i:34;s:1:"W";i:35;s:1:"H";}';
    $shuffles['C'] = 'a:36:{i:0;s:1:"V";i:1;s:1:"H";i:2;s:1:"W";i:3;s:1:"X";i:4;s:1:"B";i:5;s:1:"J";i:6;s:1:"F";i:7;s:1:"U";i:8;s:1:"T";i:9;s:1:"O";i:10;s:1:"L";i:11;s:1:"Z";i:12;s:1:"Q";i:13;s:1:"N";i:14;s:1:"6";i:15;s:1:"E";i:16;s:1:"G";i:17;s:1:"4";i:18;s:1:"7";i:19;s:1:"A";i:20;s:1:"Y";i:21;s:1:"C";i:22;s:1:"3";i:23;s:1:"5";i:24;s:1:"R";i:25;s:1:"I";i:26;s:1:"9";i:27;s:1:"D";i:28;s:1:"1";i:29;s:1:"P";i:30;s:1:"K";i:31;s:1:"S";i:32;s:1:"2";i:33;s:1:"0";i:34;s:1:"8";i:35;s:1:"M";}';
    $shuffles['D'] = 'a:36:{i:0;s:1:"Y";i:1;s:1:"S";i:2;s:1:"H";i:3;s:1:"M";i:4;s:1:"G";i:5;s:1:"O";i:6;s:1:"9";i:7;s:1:"I";i:8;s:1:"Q";i:9;s:1:"D";i:10;s:1:"Z";i:11;s:1:"J";i:12;s:1:"T";i:13;s:1:"P";i:14;s:1:"A";i:15;s:1:"B";i:16;s:1:"F";i:17;s:1:"6";i:18;s:1:"V";i:19;s:1:"4";i:20;s:1:"0";i:21;s:1:"E";i:22;s:1:"W";i:23;s:1:"R";i:24;s:1:"N";i:25;s:1:"3";i:26;s:1:"L";i:27;s:1:"5";i:28;s:1:"X";i:29;s:1:"7";i:30;s:1:"U";i:31;s:1:"2";i:32;s:1:"8";i:33;s:1:"C";i:34;s:1:"1";i:35;s:1:"K";}';
    $shuffles['E'] = 'a:36:{i:0;s:1:"7";i:1;s:1:"H";i:2;s:1:"E";i:3;s:1:"R";i:4;s:1:"Z";i:5;s:1:"O";i:6;s:1:"P";i:7;s:1:"M";i:8;s:1:"5";i:9;s:1:"T";i:10;s:1:"X";i:11;s:1:"Q";i:12;s:1:"G";i:13;s:1:"8";i:14;s:1:"9";i:15;s:1:"4";i:16;s:1:"V";i:17;s:1:"L";i:18;s:1:"3";i:19;s:1:"1";i:20;s:1:"K";i:21;s:1:"W";i:22;s:1:"S";i:23;s:1:"J";i:24;s:1:"I";i:25;s:1:"U";i:26;s:1:"F";i:27;s:1:"B";i:28;s:1:"D";i:29;s:1:"A";i:30;s:1:"Y";i:31;s:1:"N";i:32;s:1:"C";i:33;s:1:"0";i:34;s:1:"2";i:35;s:1:"6";}';
    $shuffles['F'] = 'a:36:{i:0;s:1:"G";i:1;s:1:"B";i:2;s:1:"N";i:3;s:1:"2";i:4;s:1:"F";i:5;s:1:"K";i:6;s:1:"A";i:7;s:1:"9";i:8;s:1:"P";i:9;s:1:"M";i:10;s:1:"5";i:11;s:1:"8";i:12;s:1:"I";i:13;s:1:"L";i:14;s:1:"Y";i:15;s:1:"4";i:16;s:1:"Z";i:17;s:1:"S";i:18;s:1:"O";i:19;s:1:"W";i:20;s:1:"6";i:21;s:1:"3";i:22;s:1:"D";i:23;s:1:"Q";i:24;s:1:"J";i:25;s:1:"X";i:26;s:1:"E";i:27;s:1:"R";i:28;s:1:"T";i:29;s:1:"0";i:30;s:1:"1";i:31;s:1:"C";i:32;s:1:"7";i:33;s:1:"H";i:34;s:1:"V";i:35;s:1:"U";}';
    $shuffles['G'] = 'a:36:{i:0;s:1:"5";i:1;s:1:"P";i:2;s:1:"A";i:3;s:1:"8";i:4;s:1:"W";i:5;s:1:"0";i:6;s:1:"J";i:7;s:1:"4";i:8;s:1:"K";i:9;s:1:"2";i:10;s:1:"S";i:11;s:1:"U";i:12;s:1:"6";i:13;s:1:"Q";i:14;s:1:"9";i:15;s:1:"F";i:16;s:1:"V";i:17;s:1:"L";i:18;s:1:"M";i:19;s:1:"C";i:20;s:1:"7";i:21;s:1:"E";i:22;s:1:"R";i:23;s:1:"1";i:24;s:1:"Y";i:25;s:1:"3";i:26;s:1:"D";i:27;s:1:"N";i:28;s:1:"T";i:29;s:1:"I";i:30;s:1:"O";i:31;s:1:"B";i:32;s:1:"G";i:33;s:1:"Z";i:34;s:1:"H";i:35;s:1:"X";}';
    $shuffles['H'] = 'a:36:{i:0;s:1:"L";i:1;s:1:"8";i:2;s:1:"M";i:3;s:1:"I";i:4;s:1:"T";i:5;s:1:"E";i:6;s:1:"B";i:7;s:1:"C";i:8;s:1:"U";i:9;s:1:"3";i:10;s:1:"4";i:11;s:1:"Y";i:12;s:1:"H";i:13;s:1:"5";i:14;s:1:"A";i:15;s:1:"O";i:16;s:1:"G";i:17;s:1:"0";i:18;s:1:"S";i:19;s:1:"D";i:20;s:1:"6";i:21;s:1:"P";i:22;s:1:"2";i:23;s:1:"F";i:24;s:1:"N";i:25;s:1:"Z";i:26;s:1:"9";i:27;s:1:"K";i:28;s:1:"X";i:29;s:1:"Q";i:30;s:1:"V";i:31;s:1:"J";i:32;s:1:"7";i:33;s:1:"1";i:34;s:1:"W";i:35;s:1:"R";}';
    $shuffles['I'] = 'a:36:{i:0;s:1:"5";i:1;s:1:"E";i:2;s:1:"U";i:3;s:1:"F";i:4;s:1:"C";i:5;s:1:"6";i:6;s:1:"P";i:7;s:1:"H";i:8;s:1:"1";i:9;s:1:"8";i:10;s:1:"2";i:11;s:1:"9";i:12;s:1:"D";i:13;s:1:"X";i:14;s:1:"3";i:15;s:1:"A";i:16;s:1:"V";i:17;s:1:"G";i:18;s:1:"K";i:19;s:1:"Y";i:20;s:1:"W";i:21;s:1:"L";i:22;s:1:"N";i:23;s:1:"7";i:24;s:1:"S";i:25;s:1:"B";i:26;s:1:"R";i:27;s:1:"I";i:28;s:1:"T";i:29;s:1:"Q";i:30;s:1:"O";i:31;s:1:"Z";i:32;s:1:"M";i:33;s:1:"J";i:34;s:1:"0";i:35;s:1:"4";}';
    $shuffles['J'] = 'a:36:{i:0;s:1:"M";i:1;s:1:"K";i:2;s:1:"E";i:3;s:1:"L";i:4;s:1:"7";i:5;s:1:"I";i:6;s:1:"A";i:7;s:1:"Y";i:8;s:1:"1";i:9;s:1:"O";i:10;s:1:"0";i:11;s:1:"T";i:12;s:1:"Z";i:13;s:1:"2";i:14;s:1:"D";i:15;s:1:"H";i:16;s:1:"R";i:17;s:1:"8";i:18;s:1:"9";i:19;s:1:"Q";i:20;s:1:"F";i:21;s:1:"5";i:22;s:1:"4";i:23;s:1:"6";i:24;s:1:"U";i:25;s:1:"X";i:26;s:1:"G";i:27;s:1:"P";i:28;s:1:"3";i:29;s:1:"J";i:30;s:1:"C";i:31;s:1:"S";i:32;s:1:"W";i:33;s:1:"B";i:34;s:1:"N";i:35;s:1:"V";}';
    $shuffles['K'] = 'a:36:{i:0;s:1:"Y";i:1;s:1:"W";i:2;s:1:"B";i:3;s:1:"I";i:4;s:1:"R";i:5;s:1:"7";i:6;s:1:"9";i:7;s:1:"L";i:8;s:1:"6";i:9;s:1:"A";i:10;s:1:"3";i:11;s:1:"K";i:12;s:1:"Z";i:13;s:1:"P";i:14;s:1:"O";i:15;s:1:"F";i:16;s:1:"J";i:17;s:1:"2";i:18;s:1:"H";i:19;s:1:"N";i:20;s:1:"G";i:21;s:1:"V";i:22;s:1:"U";i:23;s:1:"0";i:24;s:1:"T";i:25;s:1:"4";i:26;s:1:"5";i:27;s:1:"1";i:28;s:1:"S";i:29;s:1:"C";i:30;s:1:"E";i:31;s:1:"X";i:32;s:1:"8";i:33;s:1:"D";i:34;s:1:"Q";i:35;s:1:"M";}';
    $shuffles['L'] = 'a:36:{i:0;s:1:"6";i:1;s:1:"C";i:2;s:1:"8";i:3;s:1:"Y";i:4;s:1:"B";i:5;s:1:"X";i:6;s:1:"7";i:7;s:1:"V";i:8;s:1:"I";i:9;s:1:"3";i:10;s:1:"G";i:11;s:1:"K";i:12;s:1:"Z";i:13;s:1:"N";i:14;s:1:"T";i:15;s:1:"U";i:16;s:1:"0";i:17;s:1:"Q";i:18;s:1:"P";i:19;s:1:"5";i:20;s:1:"F";i:21;s:1:"D";i:22;s:1:"H";i:23;s:1:"M";i:24;s:1:"1";i:25;s:1:"E";i:26;s:1:"2";i:27;s:1:"L";i:28;s:1:"S";i:29;s:1:"R";i:30;s:1:"4";i:31;s:1:"J";i:32;s:1:"A";i:33;s:1:"W";i:34;s:1:"9";i:35;s:1:"O";}';
    $shuffles['M'] = 'a:36:{i:0;s:1:"6";i:1;s:1:"R";i:2;s:1:"7";i:3;s:1:"K";i:4;s:1:"H";i:5;s:1:"3";i:6;s:1:"M";i:7;s:1:"A";i:8;s:1:"5";i:9;s:1:"B";i:10;s:1:"O";i:11;s:1:"Y";i:12;s:1:"8";i:13;s:1:"J";i:14;s:1:"F";i:15;s:1:"N";i:16;s:1:"V";i:17;s:1:"G";i:18;s:1:"Q";i:19;s:1:"E";i:20;s:1:"1";i:21;s:1:"2";i:22;s:1:"Z";i:23;s:1:"9";i:24;s:1:"W";i:25;s:1:"S";i:26;s:1:"L";i:27;s:1:"I";i:28;s:1:"4";i:29;s:1:"U";i:30;s:1:"D";i:31;s:1:"T";i:32;s:1:"0";i:33;s:1:"C";i:34;s:1:"X";i:35;s:1:"P";}';
    $shuffles['N'] = 'a:36:{i:0;s:1:"G";i:1;s:1:"P";i:2;s:1:"S";i:3;s:1:"I";i:4;s:1:"E";i:5;s:1:"Y";i:6;s:1:"O";i:7;s:1:"Z";i:8;s:1:"B";i:9;s:1:"J";i:10;s:1:"K";i:11;s:1:"H";i:12;s:1:"8";i:13;s:1:"A";i:14;s:1:"M";i:15;s:1:"C";i:16;s:1:"R";i:17;s:1:"1";i:18;s:1:"2";i:19;s:1:"Q";i:20;s:1:"5";i:21;s:1:"L";i:22;s:1:"D";i:23;s:1:"4";i:24;s:1:"7";i:25;s:1:"0";i:26;s:1:"F";i:27;s:1:"U";i:28;s:1:"9";i:29;s:1:"6";i:30;s:1:"T";i:31;s:1:"W";i:32;s:1:"3";i:33;s:1:"X";i:34;s:1:"V";i:35;s:1:"N";}';
    $shuffles['O'] = 'a:36:{i:0;s:1:"S";i:1;s:1:"G";i:2;s:1:"N";i:3;s:1:"F";i:4;s:1:"9";i:5;s:1:"E";i:6;s:1:"J";i:7;s:1:"B";i:8;s:1:"1";i:9;s:1:"L";i:10;s:1:"R";i:11;s:1:"C";i:12;s:1:"T";i:13;s:1:"Y";i:14;s:1:"H";i:15;s:1:"X";i:16;s:1:"K";i:17;s:1:"Z";i:18;s:1:"6";i:19;s:1:"D";i:20;s:1:"2";i:21;s:1:"O";i:22;s:1:"A";i:23;s:1:"3";i:24;s:1:"0";i:25;s:1:"5";i:26;s:1:"7";i:27;s:1:"8";i:28;s:1:"I";i:29;s:1:"4";i:30;s:1:"M";i:31;s:1:"V";i:32;s:1:"Q";i:33;s:1:"W";i:34;s:1:"P";i:35;s:1:"U";}';
    $shuffles['P'] = 'a:36:{i:0;s:1:"6";i:1;s:1:"9";i:2;s:1:"H";i:3;s:1:"J";i:4;s:1:"Q";i:5;s:1:"B";i:6;s:1:"G";i:7;s:1:"1";i:8;s:1:"4";i:9;s:1:"K";i:10;s:1:"D";i:11;s:1:"C";i:12;s:1:"I";i:13;s:1:"Y";i:14;s:1:"S";i:15;s:1:"2";i:16;s:1:"E";i:17;s:1:"O";i:18;s:1:"0";i:19;s:1:"8";i:20;s:1:"X";i:21;s:1:"3";i:22;s:1:"L";i:23;s:1:"W";i:24;s:1:"5";i:25;s:1:"V";i:26;s:1:"T";i:27;s:1:"A";i:28;s:1:"R";i:29;s:1:"7";i:30;s:1:"M";i:31;s:1:"Z";i:32;s:1:"U";i:33;s:1:"N";i:34;s:1:"F";i:35;s:1:"P";}';
    $shuffles['Q'] = 'a:36:{i:0;s:1:"R";i:1;s:1:"E";i:2;s:1:"N";i:3;s:1:"X";i:4;s:1:"O";i:5;s:1:"8";i:6;s:1:"Q";i:7;s:1:"T";i:8;s:1:"M";i:9;s:1:"7";i:10;s:1:"P";i:11;s:1:"U";i:12;s:1:"K";i:13;s:1:"I";i:14;s:1:"Y";i:15;s:1:"F";i:16;s:1:"B";i:17;s:1:"5";i:18;s:1:"3";i:19;s:1:"D";i:20;s:1:"H";i:21;s:1:"9";i:22;s:1:"C";i:23;s:1:"0";i:24;s:1:"W";i:25;s:1:"2";i:26;s:1:"4";i:27;s:1:"G";i:28;s:1:"S";i:29;s:1:"A";i:30;s:1:"J";i:31;s:1:"V";i:32;s:1:"1";i:33;s:1:"L";i:34;s:1:"6";i:35;s:1:"Z";}';
    $shuffles['R'] = 'a:36:{i:0;s:1:"2";i:1;s:1:"A";i:2;s:1:"7";i:3;s:1:"E";i:4;s:1:"4";i:5;s:1:"R";i:6;s:1:"3";i:7;s:1:"K";i:8;s:1:"H";i:9;s:1:"Q";i:10;s:1:"U";i:11;s:1:"F";i:12;s:1:"T";i:13;s:1:"M";i:14;s:1:"G";i:15;s:1:"X";i:16;s:1:"B";i:17;s:1:"J";i:18;s:1:"P";i:19;s:1:"C";i:20;s:1:"D";i:21;s:1:"0";i:22;s:1:"8";i:23;s:1:"W";i:24;s:1:"Y";i:25;s:1:"V";i:26;s:1:"S";i:27;s:1:"L";i:28;s:1:"N";i:29;s:1:"Z";i:30;s:1:"9";i:31;s:1:"O";i:32;s:1:"6";i:33;s:1:"I";i:34;s:1:"1";i:35;s:1:"5";}';
    $shuffles['S'] = 'a:36:{i:0;s:1:"Q";i:1;s:1:"1";i:2;s:1:"L";i:3;s:1:"M";i:4;s:1:"Z";i:5;s:1:"I";i:6;s:1:"P";i:7;s:1:"8";i:8;s:1:"N";i:9;s:1:"X";i:10;s:1:"T";i:11;s:1:"7";i:12;s:1:"G";i:13;s:1:"V";i:14;s:1:"9";i:15;s:1:"O";i:16;s:1:"S";i:17;s:1:"J";i:18;s:1:"K";i:19;s:1:"F";i:20;s:1:"3";i:21;s:1:"U";i:22;s:1:"W";i:23;s:1:"H";i:24;s:1:"B";i:25;s:1:"6";i:26;s:1:"A";i:27;s:1:"5";i:28;s:1:"R";i:29;s:1:"Y";i:30;s:1:"E";i:31;s:1:"C";i:32;s:1:"0";i:33;s:1:"2";i:34;s:1:"4";i:35;s:1:"D";}';
    $shuffles['T'] = 'a:36:{i:0;s:1:"3";i:1;s:1:"1";i:2;s:1:"Q";i:3;s:1:"S";i:4;s:1:"O";i:5;s:1:"L";i:6;s:1:"V";i:7;s:1:"A";i:8;s:1:"D";i:9;s:1:"R";i:10;s:1:"I";i:11;s:1:"E";i:12;s:1:"P";i:13;s:1:"T";i:14;s:1:"4";i:15;s:1:"Y";i:16;s:1:"8";i:17;s:1:"F";i:18;s:1:"B";i:19;s:1:"5";i:20;s:1:"0";i:21;s:1:"H";i:22;s:1:"7";i:23;s:1:"X";i:24;s:1:"G";i:25;s:1:"M";i:26;s:1:"W";i:27;s:1:"Z";i:28;s:1:"K";i:29;s:1:"9";i:30;s:1:"2";i:31;s:1:"C";i:32;s:1:"U";i:33;s:1:"6";i:34;s:1:"N";i:35;s:1:"J";}';
    $shuffles['U'] = 'a:36:{i:0;s:1:"1";i:1;s:1:"D";i:2;s:1:"B";i:3;s:1:"6";i:4;s:1:"K";i:5;s:1:"Z";i:6;s:1:"I";i:7;s:1:"8";i:8;s:1:"T";i:9;s:1:"W";i:10;s:1:"Y";i:11;s:1:"V";i:12;s:1:"S";i:13;s:1:"G";i:14;s:1:"J";i:15;s:1:"X";i:16;s:1:"2";i:17;s:1:"P";i:18;s:1:"R";i:19;s:1:"4";i:20;s:1:"9";i:21;s:1:"U";i:22;s:1:"5";i:23;s:1:"E";i:24;s:1:"F";i:25;s:1:"O";i:26;s:1:"C";i:27;s:1:"L";i:28;s:1:"H";i:29;s:1:"7";i:30;s:1:"M";i:31;s:1:"A";i:32;s:1:"0";i:33;s:1:"3";i:34;s:1:"Q";i:35;s:1:"N";}';
    $shuffles['V'] = 'a:36:{i:0;s:1:"V";i:1;s:1:"J";i:2;s:1:"O";i:3;s:1:"Y";i:4;s:1:"4";i:5;s:1:"Z";i:6;s:1:"6";i:7;s:1:"T";i:8;s:1:"G";i:9;s:1:"7";i:10;s:1:"Q";i:11;s:1:"D";i:12;s:1:"U";i:13;s:1:"S";i:14;s:1:"8";i:15;s:1:"C";i:16;s:1:"5";i:17;s:1:"F";i:18;s:1:"N";i:19;s:1:"E";i:20;s:1:"H";i:21;s:1:"M";i:22;s:1:"B";i:23;s:1:"P";i:24;s:1:"X";i:25;s:1:"2";i:26;s:1:"3";i:27;s:1:"R";i:28;s:1:"9";i:29;s:1:"K";i:30;s:1:"I";i:31;s:1:"1";i:32;s:1:"0";i:33;s:1:"A";i:34;s:1:"L";i:35;s:1:"W";}';
    $shuffles['W'] = 'a:36:{i:0;s:1:"L";i:1;s:1:"4";i:2;s:1:"H";i:3;s:1:"I";i:4;s:1:"K";i:5;s:1:"2";i:6;s:1:"C";i:7;s:1:"Q";i:8;s:1:"E";i:9;s:1:"V";i:10;s:1:"M";i:11;s:1:"U";i:12;s:1:"0";i:13;s:1:"B";i:14;s:1:"Z";i:15;s:1:"T";i:16;s:1:"D";i:17;s:1:"9";i:18;s:1:"6";i:19;s:1:"Y";i:20;s:1:"8";i:21;s:1:"3";i:22;s:1:"O";i:23;s:1:"S";i:24;s:1:"X";i:25;s:1:"5";i:26;s:1:"N";i:27;s:1:"R";i:28;s:1:"A";i:29;s:1:"F";i:30;s:1:"W";i:31;s:1:"P";i:32;s:1:"1";i:33;s:1:"7";i:34;s:1:"J";i:35;s:1:"G";}';
    $shuffles['X'] = 'a:36:{i:0;s:1:"D";i:1;s:1:"R";i:2;s:1:"T";i:3;s:1:"N";i:4;s:1:"6";i:5;s:1:"Q";i:6;s:1:"5";i:7;s:1:"C";i:8;s:1:"U";i:9;s:1:"K";i:10;s:1:"W";i:11;s:1:"H";i:12;s:1:"1";i:13;s:1:"F";i:14;s:1:"2";i:15;s:1:"M";i:16;s:1:"9";i:17;s:1:"Z";i:18;s:1:"E";i:19;s:1:"0";i:20;s:1:"G";i:21;s:1:"4";i:22;s:1:"I";i:23;s:1:"O";i:24;s:1:"B";i:25;s:1:"3";i:26;s:1:"7";i:27;s:1:"S";i:28;s:1:"A";i:29;s:1:"Y";i:30;s:1:"V";i:31;s:1:"P";i:32;s:1:"L";i:33;s:1:"8";i:34;s:1:"J";i:35;s:1:"X";}';
    $shuffles['Y'] = 'a:36:{i:0;s:1:"C";i:1;s:1:"H";i:2;s:1:"U";i:3;s:1:"4";i:4;s:1:"7";i:5;s:1:"D";i:6;s:1:"3";i:7;s:1:"Z";i:8;s:1:"M";i:9;s:1:"W";i:10;s:1:"L";i:11;s:1:"I";i:12;s:1:"O";i:13;s:1:"T";i:14;s:1:"Q";i:15;s:1:"0";i:16;s:1:"G";i:17;s:1:"K";i:18;s:1:"F";i:19;s:1:"2";i:20;s:1:"S";i:21;s:1:"J";i:22;s:1:"P";i:23;s:1:"E";i:24;s:1:"1";i:25;s:1:"Y";i:26;s:1:"N";i:27;s:1:"B";i:28;s:1:"9";i:29;s:1:"V";i:30;s:1:"A";i:31;s:1:"R";i:32;s:1:"8";i:33;s:1:"6";i:34;s:1:"X";i:35;s:1:"5";}';
    $shuffles['Z'] = 'a:36:{i:0;s:1:"0";i:1;s:1:"Z";i:2;s:1:"6";i:3;s:1:"L";i:4;s:1:"4";i:5;s:1:"B";i:6;s:1:"N";i:7;s:1:"K";i:8;s:1:"R";i:9;s:1:"C";i:10;s:1:"S";i:11;s:1:"F";i:12;s:1:"Q";i:13;s:1:"U";i:14;s:1:"Y";i:15;s:1:"D";i:16;s:1:"I";i:17;s:1:"M";i:18;s:1:"7";i:19;s:1:"V";i:20;s:1:"8";i:21;s:1:"2";i:22;s:1:"O";i:23;s:1:"T";i:24;s:1:"W";i:25;s:1:"5";i:26;s:1:"E";i:27;s:1:"J";i:28;s:1:"G";i:29;s:1:"1";i:30;s:1:"A";i:31;s:1:"H";i:32;s:1:"X";i:33;s:1:"9";i:34;s:1:"3";i:35;s:1:"P";}';

    // exit('<pre>'.$i.''.print_r($shuffles[$i], 1).'</pre>');

    return $shuffles[$i];
  }

  function mixup_data($link)
  {
    // use first char as cryptogram generation 0-9 A-Z, tack it on the end to know how to decrypt

    $range = array_merge(range('0', '9'), range('A', 'Z'));

    $alphabet = array_flip($range);

    shuffle($range);

    $first = $range[0];

    $cryptogram = unserialize($this->get_shuffle($first));

    // exit('<pre>first='.$first.''.print_r($cryptogram, 1).'</pre>');

    $decryptogram = array_flip($cryptogram);
    $dealphabet   = array_flip($alphabet);

    $encoded = '';

    for ($i=0; $i < strlen($link); $i++)
    {
      $char = $link[$i];

      if (! in_array($char, $cryptogram))
        $encoded .= $char;
      else
        $encoded .= $cryptogram[$alphabet[$char]];
    }

    return $encoded.$first;
  }

  function unmix_data($link)
  {
    // last char tells us how to decrypt 0-9 A-Z, remove it from final result

    $alphabet = array_flip(array_merge(range('0', '9'), range('A', 'Z')));

    $last = $link[(strlen($link)-1)];

    $cryptogram = unserialize($this->get_shuffle($last));

    $decryptogram = array_flip($cryptogram);
    $dealphabet   = array_flip($alphabet);

    $decoded = '';

    for ($i=0; $i < (strlen($link)-1); $i++)
    {
      $char = $link[$i];

      if (! in_array($char, $cryptogram))
        $decoded .= $char;
      else
        $decoded .= $dealphabet[$decryptogram[$char]];
    }

    return $decoded;
  }
}

?>
