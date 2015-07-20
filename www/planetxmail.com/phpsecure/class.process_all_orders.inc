<?php

class ProcessOrder
{
  public $db;
  public $listownerID;
  public $listname;
  public $label;

  public $userID;
  public $status;
  public $type;

  public $merchant;
  public $cgikey;
  public $merchantID;
  public $testmode_username;
  public $headers;
  public $username;
  public $useremail;
  public $referer;
  public $listhash;
  public $adminemail;

  public $writelog_start;
  public $logfile;
  public $date;

  public $egold, $tcousername;

  function ProcessOrder($label)
  {
    $this->db = new MySQL_Access('mle');

    $this->listownerID = '';
    $this->listname    = '';
    $this->label       = $label;

    $this->userID      = '';
    $this->status      = '';
    $this->type        = '';

    $this->merchant    = '';
    $this->cgikey      = '';
    $this->merchantID  = '';
    $this->headers     = '';
    $this->username    = '';
    $this->useremail   = '';
    $this->referer     = '';
    $this->listhash    = '';
    $this->adminemail  = '';

    $this->writelog_start = 0;
    $this->logfile     = '/home/nulled/www/planetxmail.com/mle/processorderALL_log';
    $this->date = date('F j, Y, g:i a');
  }

  function get_ids($id)
  {
    if (strlen($id) < 15)
      return 'ERROR: id too short or non-existant get_ids()';

    $id = strtolower($this->unmix_data($id));

    $this->userID = substr($id, 0, 10);
    $this->status = substr($id, 10, 3);
    $this->type   = substr($id, 13);

    $this->writelog("get_ids() userID={$this->userID} status={$this->status} type={$this->type}");

    if (! $this->userID || ! $this->status || ! $this->type)
      return 'ERROR: Unable to find user based on transaction_data get_ids()';

    if ($this->db->Query("SELECT username, email, referer, listownerID, listname FROM users WHERE userID='{$this->userID}'"))
      list($this->username, $this->useremail, $this->referer, $this->listownerID, $this->listname) = $this->db->FetchRow();
    else
      return 'ERROR: Unable to find user based on userID get_ids()';

    if (! $this->db->Query("SELECT listhash FROM listurls WHERE listownerID='{$this->listownerID}' AND listname='{$this->listname}'"))
      return 'ERROR: Unable to determine listhash from Order information.';
    list($this->listhash) = $this->db->FetchRow();

    $this->db->Query("SELECT testmode_username FROM listconfig WHERE listownerID='{$this->listownerID}' AND listname='{$this->listname}'");
    list($this->testmode_username) = $this->db->FetchRow();

    $this->db->Query("SELECT paylinkparams, fromname, adminemail FROM listmanager WHERE listownerID='{$this->listownerID}' AND listname='{$this->listname}'");
    list($paylinkparams, $fromname, $this->adminemail) = $this->db->FetchRow();

    $this->headers = "From: $fromname <{$this->adminemail}>";

    list($this->paypal, $this->egold, $clickbankusername, $clickbanksignuppro, $clickbanksignupexe, $clickbankrenewalpro, $clickbankrenewalexe,
          $clickbankupgradepro, $clickbankupgradeexe, $egoldaltpass, $dobillingcheck, $renewaltype, $clickbankcgikey, $cleanmembers,
          $this->tcousername, $tcosignuppro, $tcosignupexe, $tcorenewalpro, $tcorenewalexe, $tcoupgradepro, $tcoupgradeexe, $tcocgikey,
          $alertpay, $alertpaycgikey) = explode('|', $paylinkparams);

    if ($this->merchant == 'clickbank')
      $this->cgikey = $clickbankcgikey;
    else if ($this->merchant == 'egold')
      $this->cgikey = $egoldaltpass;
    else if ($this->merchant == 'alertpay')
      $this->cgikey = $alertpaycgikey;
    else if ($this->merchant == 'twocheckout')
      $this->cgikey = $tcocgikey;
    else if ($this->merchant == 'paypal' || $this->merchant == 'notapplicable')
      $this->cgikey = '';
    else
      return 'ERROR: merchant unknown in get_ids()';

    return '';
  }

  function auth_clickbank()
  {
    $cbreceipt = $_GET['cbreceipt'];
    $id        = $_GET['id'];

    if ($notValid=$this->get_ids($id)) return $notValid;

    if (! $this->testmode_username && substr($cbreceipt, 0, 4) == 'TEST')
    {
      $notValid = 'ERROR: Not in TEST_MODE yet TEST receipt was provided.';
      @mail("elitescripts2000@yahoo.com", "Planet X Mail - cbValid() FAILED", "Not in TEST_MODE yet got a TEST cbreceipt\n\nid=$id cbpop=$cbpop cbreceipt=$cbreceipt item=$item time=$time testmode_username=$testmode_username", $headers);
    }
    else if (! $this->cbValid())
    {
      $notValid = 'ERROR: Unable to validate this ClickBank transaction.';
      @mail("elitescripts2000@yahoo.com", "Planet X Mail - cbValid() FAILED", "id=$id cbpop=$cbpop cbreceipt=$cbreceipt item=$item time=$time t=$type", $headers);
    }
    else
      $notValid = $this->process_order($cbreceipt);

    return $notValid;
  }

  function auth_alertpay()
  {
    $ap_custfirstname    = $_POST['ap_custfirstname'];
    $ap_custlastname     = $_POST['ap_custlastname'];
    $ap_custemailaddress = $_POST['ap_custemailaddress'];
    $ap_itemname         = $_POST['ap_itemname'];
    $ap_quantity         = $_POST['ap_quantity'];
    $ap_amount           = $_POST['ap_amount'];
    $ap_totalamount      = $_POST['ap_totalamount'];
    $ap_referencenumber  = $_POST['ap_referencenumber'];
    $ap_status           = $_POST['ap_status'];
    $apc_1               = $_POST['apc_1'];
    $ap_securitycode     = $_POST['ap_securitycode'];

    $id = $apc_1;

    if ($notValid=$this->get_ids($id)) return $notValid;

    if ($this->testmode_username)
    {
      $ap_referencenumber = 'TEST'.rand();
      @mail('elitescripts2000@yahoo.com', 'alertpay POST', print_r($_POST, 1));
    }

    // comment out if not testing
    if ($_POST['ap_test'] && ! $this->testmode_username)
    {
      $notValid = 'ERROR: AlertPay transaction must not be in Test Mode.';
      @mail("elitescripts2000@yahoo.com", "Free AD Planet - AlertPay in Test mode", "It should not be in Test Mode.");
    }
    else if ($this->cgikey == $ap_securitycode)
      $notValid = $this->process_order($ap_referencenumber, $ap_totalamount);
    else
    {
      $notValid = 'ERROR: Unable to validate AlertPay transaction.';
      @mail("elitescripts2000@yahoo.com", "Free AD Planet - AlertPay Hash keys do not match", "ap_securitycode=$ap_securitycode");
    }

    return $notValid;
  }

  function auth_2checkout()
  {
    $merchant_order_id 		 = $_POST['merchant_order_id'];
  	$order_number 				 = $_POST['order_number'];
  	$credit_card_processed = $_POST['credit_card_processed'];
  	$email 								 = $_POST['email'];
  	$key 									 = $_POST['key'];
  	$total 								 = $_POST['total'];

  	$id = $merchant_order_id;

  	if ($notValid=$this->get_ids($id)) return $notValid;

  	// uncomment when demo=Y
    if ($_POST['demo'] && $this->testmode_username)
    {
      $order_number = 1;
  	  @mail('elitescripts2000@yahoo.com', '2co POST', print_r($_POST, 1));
  	}

  	if ($_POST['demo'] && ! $this->testmode_username)
  	{
  	  @mail('elitescripts2000@yahoo.com', '2co demo=Y but test mode username is not set', "listhash={$this->listhash} demo={$_POST['demo']} testmode_username={$this->testmode_username}");
  	  $notValid = 'ERROR: Security violation in the use of the test mode facility.';
  	}
  	else if ($credit_card_processed != 'Y' && $credit_card_processed != 'K') // Y=creditcard OK, K=check but 2-3 days to clear
  		$notValid = 'ERROR: twocheckout: Credit card not processed. credit_card_processed='.$credit_card_processed;
    else
    {
      $uniquekey = strtoupper(md5($this->cgikey.$this->tcousername.$order_number.$total));

      if ($this->testmode_username) $order_number = 'TEST'.$id.rand();

      // make sure key is valid
    	if (strcmp($key, $uniquekey) != 0)
    	{
    		@mail("elitescripts2000@yahoo.com", "Planet X Mail - 2checkout Hash keys do not match", "uniquekey=$uniquekey key=$key t={$this->label}", $headers);
        $notValid = 'ERROR: Unable to validated this 2checkout transaction.';
    	}
    	else
    	  $notValid = $this->process_order($order_number, $total);
    }

    return $notValid;
  }

  function auth_egold()
  {
    $payee_account          = $_POST['PAYEE_ACCOUNT'];
    $v2_hash                = $_POST['V2_HASH'];
    $timestampgmt           = $_POST['TIMESTAMPGMT'];
    $feeweight              = $_POST['FEEWEIGHT'];
    $usd_per_ounce          = $_POST['USD_PER_OUNCE'];
    $handshake_hash         = $_POST['HANDSHAKE_HASH'];
    $payer_account          = $_POST['PAYER_ACCOUNT'];
    $payment_batch_num      = $_POST['PAYMENT_BATCH_NUM'];
    $payment_metal_id       = $_POST['PAYMENT_METAL_ID'];
    $payment_units          = $_POST['PAYMENT_UNITS'];
    $payment_amount         = $_POST['PAYMENT_AMOUNT'];
    $payment_id 			      = $_POST['PAYMENT_ID'];
    $actual_payment_ounces  = $_POST['ACTUAL_PAYMENT_OUNCES'];
    $CUSTOMERID             = $_POST['CUSTOMERID'];

    $id = $CUSTOMERID;

    if ($notValid=$this->get_ids($id)) return $notValid;

    if ($this->testmode_username) @mail('elitescripts2000@yahoo.com', 'egold POST', print_r($_POST, 1));

    $altpassphrasehash = strtoupper(md5($this->cgikey));
    $hashkey = strtoupper(md5("$payment_id:$payee_account:$payment_amount:$payment_units:$payment_metal_id:$payment_batch_num:$payer_account:$altpassphrasehash:$actual_payment_ounces:$usd_per_ounce:$feeweight:$timestampgmt"));

    if ($v2_hash != $hashkey)
    {
      @mail("elitescripts2000@yahoo.com", "Planet X Mail - Egold Hash keys do not match - ProcessOrder class", "v2_hash=$v2_hash != hashkey=$hashkey cgikey={$this->cgikey}", $headers);
      $notValid = 'ERROR: Unable to validate this egold transaction.';
    }
    else
      $notValid = $this->process_order($payment_batch_num, $payment_amount);

    return $notValid;
  }

  function auth_paypal()
  {
    $fname 					= $_POST['first_name'];
    $lname 					= $_POST['last_name'];
    $receiver_email = $_POST['receiver_email'];
    $item_name      = $_POST['item_name'];
    $item_number    = $_POST['item_number'];
    $custom         = $_POST['custom'];
    $payment_status = $_POST['payment_status'];
    $payment_gross  = $_POST['payment_gross'];
    $payment_fee 	  = $_POST['payment_fee'];
    $txn_id         = $_POST['txn_id'];
    $test_ipn       = $_POST['test_ipn'];
    $payer_email    = $_POST['payer_email'];
    $complete_url   = $_POST['option_selection1'];

    $id = $custom;

    $this->writelog('Start paypal');

    //@mail('elitescripts2000@yahoo.com', 'post auth_paypal', print_r($_POST, 1));
    //@mail('elitescripts2000@yahoo.com', 'get auth_paypal', print_r($_GET, 1));

    if ($notValid=$this->get_ids($id)) return $notValid;

    if ($this->testmode_username && $test_ipn)
    {
      $txn_id = 'TEST'.$txn_id;
      $post_to = 'www.sandbox.paypal.com';
    }
    else if ($this->testmode_username && ! $test_ipn)
      return 'ERROR: testmode_username is set but test_ipn is not set.';
    else if (! $this->testmode_username && $test_ipn)
      return 'ERROR: testmode_username is not set but test_ipn is set.';
    else
      $post_to = 'www.paypal.com';

    $this->writelog("post_to=$post_to");

    $req = 'cmd=_notify-validate';

    foreach ($_POST as $key => $value)
    {
      $value = urlencode(stripslashes($value));
      $req .= "&$key=$value";
    }

    $header  = "POST /cgi-bin/webscr HTTP/1.0\r\n";
    $header .= "Content-Type: application/x-www-form-urlencoded\r\n";
    $header .= "Content-Length: " . strlen($req) . "\r\n\r\n";

    if (! $fp = @fsockopen($post_to, 80, $errno, $errstr, 30))
      return "ERROR: Paypal order fsockopen() $errstr ($errno)";
    else
    {
      fputs($fp, $header.$req);

      while (! feof($fp))
      {
        $res = fgets($fp, 1024);

        if (strcmp($res, 'VERIFIED') == 0)
        {
          $this->writelog("res=$res");

          if ($payment_status == 'Completed' || $payment_status == 'Pending')
          {
            $this->writelog("payment_status=$payment_status");
            $notValid = $this->process_order($txn_id, $payment_gross, $payment_fee);
            break;
          }
          $notValid = 'ERROR: Paypal order status is not Completed or Pending. payment_status='.$payment_status;
          break;
        }
        else if (strcmp($res, 'INVALID') == 0)
        {
          $this->writelog("res=$res");
          $notValid = 'ERROR: Paypal order is INVALID.';
          break;
        }
      }
    }

    @fclose($fp);

    return $notValid;
  }

  function process_merchant()
  {
    if ($_GET['cbreceipt'])
    {
      $this->merchant = 'clickbank';
      $notValid = $this->auth_clickbank();
    }
    else if ($_POST['merchant_order_id'])
    {
      $this->merchant = 'twocheckout';
      $notValid = $this->auth_2checkout();
    }
    else if ($_POST['V2_HASH'])
    {
      $this->merchant = 'egold';
      $notValid = $this->auth_egold();
    }
    else if ($_POST['ap_securitycode'])
    {
      $this->merchant = 'alertpay';
      $notValid = $this->auth_alertpay();
    }
    else if ($_POST['txn_id'])
    {
      $this->merchant = 'paypal';
      $notValid = $this->auth_paypal();
    }
    else if ($_GET['pxm_label'] == 'cancel')
      $notValid = 'NOTICE: You cancelled the Order.';
    else if ($_GET['pxm_data'])
    {
      @mail('elitescripts2000@yahoo.com', 'after payment2', print_r($_GET, 1));

      $this->merchant = 'notapplicable';
      if ($notValid=$this->get_ids($_GET['pxm_data'])) {}
      else
        $notValid = 'Your Order should have been Processed.';
    }
    else
      $notValid = 'ERROR: There may have been an error processing your Order.';

    return $notValid;
  }

  function cbValid()
  {
    $key = $this->cgikey;

    $rcpt=$_REQUEST['cbreceipt'];
    $time=$_REQUEST['time'];
    $item=$_REQUEST['item'];
    $cbpop=$_REQUEST['cbpop'];

    $xxpop=sha1("$key|$rcpt|$time|$item");
    $xxpop=strtoupper(substr($xxpop,0,8));

    if ($cbpop==$xxpop)
    {
      // check time is valid
      $timeallowed = (60*60*6);
      $timediff = abs(time()-$time);
      if ($timediff > $timeallowed)
      {
        @mail('elitescripts2000@yahoo.com', 'Clickbank FRAUD cbValid time param ProcessOrder class', "time=$time\ntimediff=$timediff\ntimeallowed=$timeallowed\nrcpt=$rcpt");
        return 0;
      }
      else
        return 1;
    }
    else
      return 0;
  }

  function get_cost()
  {
    if (! $this->db->Query("SELECT costofpro, costofexe, commission, referer, testmode_username FROM listconfig WHERE listownerID='{$this->listownerID}' AND listname='{$this->listname}'"))
      return 'ERROR: Unable to determine listname based on listhash provided.';
    list($costofpro, $costofexe, $commission, $refererON, $this->testmode_username) = $this->db->FetchRow();
    list($commissionpro, $commissionexe, $allowcommissions) = explode('|', $commission);
    list($cost_signup_pro, $cost_renew_pro, $cost_upgrade_pro) = explode('|', $costofpro);
    list($cost_signup_exe, $cost_renew_exe, $cost_upgrade_exe) = explode('|', $costofexe);

    return array($refererON, $commissionpro, $commissionexe, $allowcommissions, $cost_signup_pro, $cost_renew_pro, $cost_upgrade_pro, $cost_signup_exe, $cost_renew_exe, $cost_upgrade_exe);
  }

  function merchant_fees($amount, $fees=0)
  {
    if ($this->merchant == 'clickbank')
    {
      $amount -= 1;
    	$fees = $amount * .075;
    	$amount -= $fees;
    	$profits = number_format($amount, 2, '.', '');
    }
    else if ($this->merchant == 'paypal')
    {
      $amount = $amount - $fees;
    	$profits = number_format($amount, 2, '.', '');
    }
    else if ($this->merchant == 'twocheckout')
    {
      $amount -= 0.45;
    	$fees = $amount * .055;
    	$amount -= $fees;
    	$profits = number_format($amount, 2, '.', '');
    }
    else if ($this->merchant == 'alertpay')
    {
      $amount -= 0.59;
    	$fees = $amount * .039;
    	$amount -= $fees;
    	$profits = number_format($amount, 2, '.', '');
    }
    else if ($this->merchant == 'egold')
    {
      $amount -= 0.50;
    	$profits = number_format($amount, 2, '.', '');
    }
    else
      $profits = number_format($amount, 2, '.', '');

    return $profits;
  }

  function writelog($str)
  {
    if (! $this->writelog_start)
    {
      $redirect = '>';
      $this->writelog_start = 1;
    }
    else
      $redirect = '>>';

    $p = popen("/bin/echo '{$this->date} - $str' $redirect {$this->logfile}", 'r');
    pclose($p);
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

  function process_order($receipt, $amount=0, $fees=0)
  {
    $today = $this->date;

    $allowed_status = array('pro','exe');
    $allowed_types  = array('signup','renew','upgrade');

    $this->writelog("process_order() status={$this->status} type={$this->type} receipt=$receipt amount=$amount fees=$fees");

    if (! @in_array($this->status, $allowed_status))
      return 'ERROR: Unable to determine status from Order information.';

    if (! @in_array($this->type, $allowed_types))
      return 'ERROR: Unable to determine type from Order information.';

    if (is_string($notValid=$this->get_cost())) return $notValid;

    list($refererON,      $commissionpro,    $commissionexe,   $allowcommissions, $cost_signup_pro,
         $cost_renew_pro, $cost_upgrade_pro, $cost_signup_exe, $cost_renew_exe,   $cost_upgrade_exe) = $notValid;

    $this->writelog("process_order() after get_cost()");

    // calculate commissions and expected amounts
    $commissionowed = 0;
    if ($this->type == 'upgrade')
    {
    	if ($refererON && $this->status != 'mem' && $this->referer && ($allowcommissions == '2' || $allowcommissions == '3'))
    	{
    		if ($this->status == 'pro' && $commissionpro)
    			$commissionowed = number_format(($cost_upgrade_pro*($commissionpro / 100)), '2', '.', '');
    		else if ($commissionexe)
    			$commissionowed = number_format(($cost_upgrade_exe*($commissionexe / 100)), '2', '.', '');
    	}

    	if ($this->status == 'pro') $expected_amount = $cost_upgrade_pro;
      else if ($this->status == 'exe') $expected_amount = $cost_upgrade_exe;
    }
    else if ($this->type == 'renew')
    {
    	if ($refererON && $this->status != 'mem' && $this->referer && ($allowcommissions == '1' || $allowcommissions == '3'))
    	{
    		if ($this->status == 'pro' && $commissionpro)
    			$commissionowed = number_format(($cost_renew_pro*($commissionpro / 100)), '2', '.', '');
    		else if ($commissionexe)
    			$commissionowed = number_format(($cost_renew_exe*($commissionexe / 100)), '2', '.', '');
    	}

    	if ($this->status == 'pro') $expected_amount = $cost_renew_pro;
      else if ($this->status == 'exe') $expected_amount = $cost_renew_exe;
    }
    else if ($this->type == 'signup')
    {
    	if ($refererON && $this->status != 'mem' && $this->referer)
    	{
    		if ($this->status == 'pro' && $commissionpro)
    			$commissionowed = number_format(($cost_signup_pro*($commissionpro / 100)), '2', '.', '');
    		else if ($commissionexe)
    			$commissionowed = number_format(($cost_signup_exe*($commissionexe / 100)), '2', '.', '');
    	}

    	if ($this->status == 'pro') $expected_amount = $cost_signup_pro;
      else if ($this->status == 'exe') $expected_amount = $cost_signup_exe;
    }

    $this->writelog("process_order() expected_amount=$expected_amount");

    // check for duplicate receipt
    if ($this->db->Query("SELECT receipt FROM transactions WHERE mop='{$this->merchant}' AND receipt='$receipt' LIMIT 1"))
    	return "ERROR: Receipt already present in upgrade - receipt: $receipt";

   $this->writelog("process_order() after duplicate receipt check");

    // clickbank does not return amount... so get it
    if ($this->merchant == 'clickbank')
    {
      if ($this->type == 'upgrade')
      {
        if ($this->status == 'pro') $amount = $cost_upgrade_pro;
        else if ($this->status == 'exe') $amount = $cost_upgrade_exe;
      }
      else if ($this->type == 'renew')
      {
        if ($this->status == 'pro') $amount = $cost_renew_pro;
        else if ($this->status == 'exe') $amount = $cost_renew_exe;
      }
      else if ($this->type == 'signup')
      {
        if ($this->status == 'pro') $amount = $cost_signup_pro;
        else if ($this->status == 'exe') $amount = $cost_signup_exe;
      }
    }

    // check for price tampering
    $profits = $this->merchant_fees($expected_amount, $fees);
    $fees = $expected_amount - $profits;
    $this->writelog("profits=$profits amount=$amount expected_amount=$expected_amount fees=$fees");
    if ($amount < ($expected_amount-$fees-1))
    {
      @mail('elitescripts2000@yahoo.com', 'Planet X Mail - PRICE FRAUD - ProcessOrder class', "userID={$this->userID} amount=$amount mop={$this->merchant} receipt=$receipt type={$this->type}");
      return 'ERROR: Invalid amount give in transaction.';
    }
    $profits = $amount - $fees;

    $this->writelog("profits=$profits");

    if ($this->type == 'upgrade')
    {
      $this->writelog("type=upgrade");

      $this->db->Query("UPDATE users SET memberpaid='1', status='{$this->status}', datelastbilled=NOW() WHERE userID='{$this->userID}'");

    	@mail($adminemail, "{$this->listname} - Member Upgrade", "Member Upgrade\n\nList Name: {$this->listname}\nUsername: {$this->username}\nStatus: {$this->status}\nMerchant: {$this->merchant}\nAmount: $profits\nReceipt: $receipt\nDate: $today\n\nRegards,\nPlanet X Mail Staff", $this->headers);
    	@mail('elitescripts2000@yahoo.com', "{$this->listname} - Member Upgrade", "Member Upgrade\n\nList Name: {$this->listname}\nUsername: {$this->username}\nStatus: {$this->status}\nMerchant: {$this->merchant}\nAmount: $profits\nReceipt: $receipt\nDate: $today\n\nRegards,\nPlanet X Mail Staff", $this->headers);

    	// add to transactions
    	$this->db->Query("INSERT INTO transactions VALUES('','{$this->listhash}','{$this->userID}','upgrade','$profits','$commissionowed','0','{$this->merchant}','$receipt',NOW())");
      if ($this->listownerID == '4032668343' && ! $this->testmode_username)
      {
        $this->db->SelectDB('pxm');
        $this->db->Query("INSERT INTO transactions VALUES('','pxm_member','$profits','{$this->merchant}','$receipt',NOW())");
        $this->db->SelectDB('mle');
      }
      $this->writelog("return=Successfully Upgraded Your Account");
      return 'Successfully Upgraded Your Account.';
    }
    else if ($this->type == 'renew')
    {
      $this->db->Query("UPDATE users SET memberpaid='1', status='{$this->status}' WHERE userID='{$this->userID}'");

    	@mail($adminemail, "{$this->listname} - Member Renewed", "Member Renewed their Membership\n\nList Name: {$this->listname}\nUsername: {$this->username}\nStatus: {$this->status}\nMerchant: {$this->merchant}\nAmount: $profits\nReceipt: $receipt\nDate: $today\n\nRegards,\nPlanet X Mail Staff", $this->headers);
    	@mail('elitescripts2000@yahoo.com', "{$this->listname} - Member Renewed", "Member Renewed their Membership\n\nList Name: {$this->listname}\nUsername: {$this->username}\nStatus: {$this->status}\nMerchant: {$this->merchant}\nAmount: $profits\nReceipt: $receipt\nDate: $today\n\nRegards,\nPlanet X Mail Staff", $this->headers);

    	// add to transactions
    	$this->db->Query("INSERT INTO transactions VALUES('','{$this->listhash}','{$this->userID}','renew','$profits','$commissionowed','0','{$this->merchant}','$receipt',NOW())");
      if ($this->listownerID == '4032668343' && ! $this->testmode_username)
      {
        $this->db->SelectDB('pxm');
        $this->db->Query("INSERT INTO transactions VALUES('','pxm_member','$profits','{$this->merchant}','$receipt',NOW())");
        $this->db->SelectDB('mle');
      }
      return 'Successfully Renewed Your Account.';
    }
    else if ($this->type == 'signup')
    {
      $this->db->Query("UPDATE users SET memberpaid='1', verified='yes', status='{$this->status}', datelastbilled=NOW() WHERE userID='{$this->userID}'");

    	@mail($adminemail, "{$this->listname} - Member Paid Signup", "Member Paid Signup Membership\n\nList Name: {$this->listname}\nUsername: {$this->username}\nStatus: {$this->status}\nMerchant: {$this->merchant}\nAmount: $profits\nReceipt: $receipt\nDate: $today\n\nRegards,\nPlanet X Mail Staff", $this->headers);
    	@mail('elitescripts2000@yahoo.com', "{$this->listname} - Member Paid Signup", "Member Paid Signup Membership\n\nList Name: {$this->listname}\nUsername: {$this->username}\nStatus: {$this->status}\nMerchant: {$this->merchant}\nAmount: $profits\nReceipt: $receipt\nDate: $today\n\nRegards,\nPlanet X Mail Staff", $this->headers);

    	// add to transactions
    	$this->db->Query("INSERT INTO transactions VALUES('','{$this->listhash}','{$this->userID}','signup','$profits','$commissionowed','0','{$this->merchant}','$receipt',NOW())");
      if ($this->listownerID == '4032668343' && ! $this->testmode_username)
      {
        $this->db->SelectDB('pxm');
        $this->db->Query("INSERT INTO transactions VALUES('','pxm_member','$profits','{$this->merchant}','$receipt',NOW())");
        $this->db->SelectDB('mle');
      }
      return 'Successfully Signed up Your Account. You may now Login.';
    }
    else
      return 'ERROR: Type in Order information is unknown.';
  }
}

?>