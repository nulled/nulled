<?php
require_once('/home/nulled/www/freeadplanet.com/secure/classes.inc');
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/datefunctions.inc');

$allowed = array('home','faq','referring','downline','commissions','profile','upgrade','renew','sethelp',
'mailer','buyads','spotlightads','billboardads','targetedads','bannerads','exitads','logout');
if (! in_array($c, $allowed)) $c = 'home';

$db = new MySQL_Access('fap');

session_set_cookie_params(0, '/members', '.freeadplanet.com', 0, 1);
session_start();

if (isset($_SESSION['LAST_ACTIVITY']) AND (time() - $_SESSION['LAST_ACTIVITY'] > 1800)) // 15 mins
   $_SESSION['affid'] = '';
$_SESSION['LAST_ACTIVITY'] = time();

$affid  = $_SESSION['affid'];
$key    = $_SESSION['key'];
$vkey   = strrev(md5(sha1(strrev($affid))));

$ipaddress = $_SERVER['REMOTE_ADDR'];

if ($affid == '')
  logout_session('Your Session Has Timed Out.');
else if (! @is_numeric($affid))
  logout_session('affid is not numeric');
else if ($vkey != $key)
  logout_session('Session is invalid.');
else if (! $db->Query("SELECT status, categories, credits, lockedcredits, mailedtoday, weekadcount, weekadmissed FROM users WHERE affid='$affid' LIMIT 1"))
  logout_session('User not found.');
else
{
  list($status, $user_categories, $credits, $lockedcredits, $mailedtoday, $weekadcount, $weekadmissed) = $db->FetchRow();
  $db->Query("UPDATE users SET ipaddress='$ipaddress' WHERE affid='$affid' LIMIT 1");
}

// for security
unset($key, $vkey);

$downgrade_warning = check_status($affid, $db);

if ($status == 0) // free
{
  $allowed_bb = $bb_max_ads_free;
  $allowed_ta = $ta_max_ads_free;
  $allowed_sl = $sl_max_ads_free;
  $allowed_ba = $ba_max_ads_free;
  $allowed_ea = $ea_max_ads_free;

  $allowed_credits = $credits_earned_free;
}
else if ($status == 1 OR $status == 2) // pro
{
  $allowed_bb = $bb_max_ads_pro;
  $allowed_ta = $ta_max_ads_pro;
  $allowed_sl = $sl_max_ads_pro;
  $allowed_ba = $ba_max_ads_pro;
  $allowed_ea = $ea_max_ads_pro;

  $allowed_credits = $credits_earned_pro;
}
else
  logout_session('Your Status Level could not be determined.');

if (! $user_categories)
  $user_categories = array();
else
  $user_categories = explode(',', $user_categories);

if ($c == 'sethelp')
{
  $w = $_REQUEST['w'];
  $h = $_REQUEST['h'];
  $x = $_REQUEST['x'];
  $y = $_REQUEST['y'];
  $s = $_REQUEST['s'];

  // defaults
  if ($s != 'none' AND $s != 'block')
  {
    $w = 600;
    $h = 200;
    $x = 10;
    $y = 10;
    $s = $_SESSION['help_state'] = 'block';
  }

  // prevents IE from flickering
  if ($w != '')
  {
    $_SESSION['help_width']  = $w;
    $_SESSION['help_height'] = $h;
    $_SESSION['help_left']   = $x;
    $_SESSION['help_top']    = $y;
  }

  $_SESSION['help_state'] = $s;

  exit;
}
else if ($c == 'home')
{
  if (! $_SESSION['help_state'])
  {
    $_SESSION['help_width']  = 600;
    $_SESSION['help_height'] = 200;
    $_SESSION['help_top']    = 10;
    $_SESSION['help_left']   = 10;
    $_SESSION['help_state']  = 'normal';
  }

  session_write_close();

  $db->Query("SELECT username, fname, lname FROM users WHERE affid='$affid' LIMIT 1");
  list($username, $fname, $lname) = $db->FetchRow();

  $main_content = '
  <center><font size="+1">Welcome, <font color="red">'.$fname.' '.$lname.'</font></font>
  <br />
  You currently have <b>'.$credits.'</b> Open and <b>'.$lockedcredits.'</b> Locked Credits.
  </center>
  '.$downgrade_warning.'
  '.create_ads_browser($affid, $db);
}
else if ($c == 'upgrade' OR $c == 'renew')
{
  session_write_close();

  $in_test_mode = $ap_test = $tc_test = '';
  if (TEST_MODE)
  {
    $ap_test = '&ap_test=1';
    $tc_test = '&demo=Y';
    $in_test_mode = '<h3><font color="red">WARNING!!! In Test Mode</font></h3>';
  }

  $tc  = '<a href="https://www.2checkout.com/2co/buyer/purchase?sid=25344&quantity=1&product_id=9&merchant_order_id='.$affid.'&fixed=Y'.$tc_test.'"><img src="http://planetxmail.com/images/2cocc06.gif" border="0" /></a>';

  $cb  = '<a href="http://16.nulled.pay.clickbank.net?vtid='.$affid.'"><img src="http://planetxmail.com/images/clickbank_logo.jpg" border="0" /><br /><img src="http://freeadplanet.com/images/cards.gif" border="0" /></a>';

  $ap  = '<a href="https://www.alertpay.com/PayProcess.aspx?ap_purchasetype=Item&ap_merchant=freeadplanet@pxmb.com&ap_itemname=Free+AD+Planet+-+Membership&ap_currency=USD&ap_returnurl=http%3a%2f%2ffreeadplanet.com%2f?c=processorder%26fap_alertpay_thankyou%3D1&ap_quantity=1&ap_description=Free+AD+Planet+-+Membership&ap_amount=20.00&ap_cancelurl=http%3a%2f%2ffreeadplanet.com%2f?c=processorder&apc_1='.$affid.'&apc_2=subscription'.$ap_test.'"><img src="http://planetxmail.com/images/alertpay_icon.gif" border="0" /></a>';

  $pp = '<form name="paypal" action="https://www.paypal.com/cgi-bin/webscr" method="POST" class="blankform">
            <input type="hidden" name="cmd" value="_xclick">
            <input type="hidden" name="business" value="accounts@planetxmail.com">
            <input type="hidden" name="item_name" value="Free AD Planet">
            <input type="hidden" name="item_number" value="'.$affid.'">
            <input type="hidden" name="amount" value="20.00">
            <input type="hidden" name="custom" value="PXM-freeadplanet-'.$affid.'-1">
            <input type="hidden" name="no_shipping" value="1">
            <input type="hidden" name="return" value="http://freeadplanet.com/?c=processorder&m=thankyou">
            <input type="hidden" name="cancel_return" value="http://freeadplanet.com">
            <input type="image" src="http://planetxmail.com/images/pp_verified.gif" name="I1"><br />
            <input type="image" src="http://planetxmail.com/images/pp_logo_creditcard.gif" name="I1"><br />
          </form>
          ';

  if ($status == 1)
    $notValid = 'You are already at Professional Member.';
  else
  {
    $help = $help_benefits;

    $aform = '
    <table align="center" width="300" style="border-collapse: collapse" bordercolor="#000000" border="1" cellspacing="0" cellpadding="10">
      <tr>
        <td align="center" colspan="2">
          <h3>'.ucfirst($c).' to Professional</h3>
          '.$in_test_mode.'
          '.$help.'
          <h2>Methods of Payment are listed below:</h2>
          $20 / month for Pro Subscriptions.
        </td>
      </tr>

      <tr>
        <td align="center">'.$ap.'</td>
        <td align="center">'.$cb.'</td>
      </tr>

      <!--
      <tr>
        <td colspan="2" align="center">
          '.$pp.'
        </td>
      </tr>
      -->

    </table>
    ';
  }

  notValid($notValid);

  $main_content = '
  '.$notValid.'
  '.$aform.'
  ';

  if (TEST_MODE AND ! ($affid == '11187448' OR $affid == 'BLAHBLAH')) $main_content = '<center><h3>Upgrade to Professional</h3>Temporarily disabled...</center>';
}
else if ($c == 'faq')
{
  session_write_close();

  $main_content = '
  <a name="top"></a>
  <h3><font color="red">F</font>requently <font color="red">A</font>sk <font color="red">Q</font>uestions</h3>
  For more generalize questions about Free AD Planet <a href="http://freeadplanet.com/?c=home" target="_blank">Click Here</a>.

  <ul>
    <li><a href="#porn">Is porn or other such ADs allowed?</a></li>
    <li><a href="#xfer">Can I use this service with planetxmail.com (Planet X Mail)?</a></li>
    <li><a href="#fap_pxm">Does Free AD Planet and Planet X Mail use the same Credit System?</a></li>
    <li><a href="#quota">Why have a Quota Recommendation System for Viewing ADs?</a></li>
    <li><a href="#benefits">What are the differences between Free and Professional Member Status?</a></li>
    <li><a href="#adtypes">What are the different AD Types?</a></li>
    <li><a href="#disappear">Why do the ADs I Earn Credits from Disappear?</a></li>
    <li><a href="#anyads">Why don\'t I see any of my ADs?</a></li>
    <li><a href="#credits">What is the difference between Open and Locked Credits?</a></li>
    <li><a href="#borders">What do the AD Border types mean?</a></li>
    <li><a href="#purchased">If I Purchase an AD can I Edit, Delete and Re-Create it?</a></li>
  </ul>

  <hr />
  <a name="porn">Is porn or other such ADs allowed?</a> - <a href="#top">Top</a><br /><br />
  <b>No</b>. Porn, scams or anti-goverment or anti-religious Ads are forbidden from freeadplanet.com. This includes banners,
  text ads or ANY type of AD submitted to freeadplanet.com. If it is found you are trying to promote Porn or the mentioned forbidden
  subject material, you will be deleted and your IP Address added to our banned list.
  <br /><br />
  Such material is forbidden, because too many users of our AD network get very upset in seeing anything remotely related. So, please
  save yourself some time, and do not even try to do it. We thank you for your understanding and cooperation in this matter.

  <hr />
  <a name="xfer">Can I use this service with planetxmail.com (Planet X Mail)?</a> - <a href="#top">Top</a><br /><br />
  <b>Yes</b>. Free AD Planet and <i>Planet X Mail</i> were produced by the same company.  We have arranged it so PRO Members
  can easily Transfer Credits Earned at planetxmail.com to be used at freeadplanet.com. This means you can Advertise
  using effective Email Advertising (planetxmail.com) and compliment that with Classified Style Advertising
  (freeadplanet.com). <a href="?c=upgrade">Upgrade to Pro Today!</a>

  <hr />
  <a name="fap_pxm">Does Free AD Planet and Planet X Mail use the same Credit System?</a> - <a href="#top">Top</a><br /><br />
  <b>No</b>. Please, do not mistake Planet X Mail (planetxmail.com) with Free AD Planet (freeadplanet.com). We get
  a lot of confused folks that tend to mix the two sites up. Each site has it\'s <i>own</i> Credit System and
  Member Accounts! <i>As mentioned before it is possible to transfer Planet X Mail Credits to a Free AD Planet Account.</i>
  This is the only connection between the two sites. We think the mix up occurs because the word \'planet\' appears in both
  domain names. It is also true that both sites use similar styles with regards to how Credits are Earned and how the Earning
  System looks.

  <hr />
  <a name="quota">Why have a Quota Recommendation System for Viewing ADs?</a> - <a href="#top">Top</a><br /><br />
  Please, read your community, <a href="http://freeadplanet.com/policies.php" target="_blank">Quota Recommendation System Guide</a> for details.

  <hr />
  <a name="benefits">What are the differences between Free and Professional Member Status?</a> - <a href="#top">Top</a><br /><br />
  <center>'.$help_benefits.'</center>

  <hr />
  <a name="adtypes">What are the different AD Types?</a> - <a href="#top">Top</a><br /><br />
  There are 6 different ways to Advertise at Free AD Planet.
  <a href="?c=spotlightads">SpotLight</a>, <a href="?c=targetedads">Targeted</a>, <a href="?c=billboardads">BillBoard</a>, <a href="?c=bannerads">Banner</a>,
  <a href="?c=exitads">Exit</a> and <a href="?c=mailer">Email</a> ADs.
  Each AD type has its own section with a Howto Link in each. Use the Main Menu to navigate to each AD Type.

  <hr />
  <a name="disappear">Why do the ADs I Earn Credits from Disappear?</a> - <a href="#top">Top</a><br /><br />
  After you click on an AD and go through the 15 second pause period, that AD will not show up again
  until the Next Business Day. <b>12 midnight Eastern Time.</b> This is to prevent abuse of the Credit System
  and ensures that all ADs get their chance to be viewed!
  If, you saw an AD one day you will see it again the Next Business Day. As long as the owner of the AD has not
  run out of Credits and the AD conforms to the rules of its type.

  <hr />
  <a name="anyads">Why don\'t I see any of my ADs?</a> - <a href="#top">Top</a><br /><br />
  If you have a Free Member Account and you run out of <b>Open Credits</b>, <i>all</i> of your ADs will not display.
  To fix this, Earn Credits by viewing ADs, clicking on Earnable Credits Links in Emails or <a href="?c=profile&x=1">Transfer</a>
  some <b>Locked Credits into your Open Credits</b>. You can also Purchase large amounts of Credits in the <a href="?c=buyads">Buy ADs</a> section.

  <hr />
  <a name="credits">What is the difference between Open and Locked Credits?</a> - <a href="#top">Top</a><br /><br />
  There are two ways to store your Credits. Locked Credits or Open Credits.
  Credits that are Locked can not be drained when members are viewing your ADs. Open Credits, on the other hand,
  can be drained by Members viewing your ADs. When your Open Credits reach zero, this will effect your ADs differently depending
  on your Free or PRO status, if the AD is a Purchased AD or a Red Bordered AD. Use the <a href="?c=profile&x=1">Transfer Tool</a>
  to move Credits to and from Open and Locked. If you want to make sure your Credits do not get drained away, due
  to member AD viewing, you can Locked them so, you can use them to <a href="?c=buyads">Purchase</a> other ADs.
  The freedom is yours to explore.

  <hr />
  <a name="borders">What do the AD Border types mean?</a> - <a href="#top">Top</a><br /><br />
  When you create any AD it will have a Preview of it. Each AD will have a Border and there are 3 types of borders.
  These border types are only seen in the Section for Adding, Editing or Deleting each respective AD.

  <ul>
    <li>Black Border AD - Disappear when Open Credits are zero, regardless if Free or PRO.</li>
    <li><font color="red">Red Border AD</font> - NEVER disappear, regardless of Open Credits. <b>Pro Only</b>
        <br />One AD per AD type can be set as a Red Border AD, if your a Pro Member.</li>
    <li>Dashed Border AD - NEVER disappear, regardless of Open Credits. This is a Purchased AD which Free or Pro Members can Buy.</li>
  </ul>

  <hr />
  <a name="purchased">If I Purchase an AD can I Edit, Delete and Re-Create it?</a> - <a href="#top">Top</a><br /><br />
  <b>Yes.</b> You can Edit and Delete it as much as you like during the 30 days it is active. After 30 days it will expire
  and delete itself. Also, Purchased ADs will not disappear if your Open Credits run to zero. Purchased ADs are
  designated with a <i>Dotted Border</i> as seen in Preview area.

  <br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br />
  <br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br />
  ';
}
else if ($c == 'profile')
{
  // transfer credits
  if ($x)
  {
    if ($submitted == 'xfer')
    {
      $notValid = '';

      if (@is_numeric($xfercredits) AND $xfercredits)
      {
        $xfercredits = abs($xfercredits);

        if ($from == 'credits')
        {
          if ($xfercredits > $credits) $xfercredits = $credits;

          $db->Query("SELECT credits_transfered FROM users WHERE affid='$affid' LIMIT 1");
          list($credits_transfered) = $db->FetchRow();

          $transfer_check = $credits_transfered + $xfercredits;

          if ($credits == 0)
            $notValid = 'ERROR: You have 0 Open Credits to transfer.';
          else if ($credits_transfered >= $max_credits_transferable)
            $notValid = 'ERROR: Max of '.$max_credits_transferable.' open TO locked credits transferable per day.';
          else
          {
            if ($transfer_check > $max_credits_transferable)
            {
              $xfercredits = $xfercredits - ($transfer_check - $max_credits_transferable);
              $notValid .= 'Notice: Transfer modified to '.$xfercredits.'. Max per day reached.<br />';
            }

            $db->Query("UPDATE users SET credits=credits-$xfercredits, lockedcredits=lockedcredits+$xfercredits,
                                         credits_transfered=credits_transfered+$xfercredits WHERE affid='$affid' LIMIT 1");

            $db->Query("SELECT credits, lockedcredits FROM users WHERE affid='$affid' LIMIT 1");
            list($credits, $lockedcredits) = $db->FetchRow();
            $notValid .= 'Successfully Transfered '.$xfercredits.' Open Credits to Locked Credits.';
          }
        }
        else if ($from == 'lockedcredits')
        {
          if ($xfercredits > $lockedcredits) $xfercredits = $lockedcredits;

          if ($lockedcredits == 0)
            $notValid = 'ERROR: You have 0 Locked credits to transfer.';
          else
          {
            $db->Query("UPDATE users SET credits=credits+$xfercredits, lockedcredits=lockedcredits-$xfercredits WHERE affid='$affid' LIMIT 1");
            $db->Query("SELECT credits, lockedcredits FROM users WHERE affid='$affid' LIMIT 1");
            list($credits, $lockedcredits) = $db->FetchRow();
            $notValid = 'Successfully Transfered '.$xfercredits.' Locked Credits to Open Credits.';
          }
        }
        else
          $notValid = 'ERROR: from param is not valid.';
      }
      else
        $notValid = 'ERROR: Number credits to transfer must be numeric value.';

      $x = 1;
    } else if (($submitted == 'pxm_login' OR $submitted == 'pxm_xfer') AND $status == '1') {
      $pxm_username     = trim($_POST['pxm_username']);
      $pxm_password     = trim($_POST['pxm_password']);
      $pxm_listID       = trim($_POST['pxm_listID']);
      $pxm_xfer_credits = trim($_POST['pxm_xfer_credits']);

      $db->SelectDB('mle');

      if ($db->Query("SELECT listname, listownerID FROM listurls WHERE listhash='$pxm_listID'")) {
        list($pxm_listname, $pxm_listownerID) = $db->FetchRow();

        if ($db->Query("SELECT credits FROM users WHERE username='$pxm_username' AND password=MD5('$pxm_password') AND listname='$pxm_listname' AND listownerID='$pxm_listownerID'")) {
          list($pxm_credits) = $db->FetchRow();
          $_SESSION['pxm_credits'] = $pxm_credits;

          if ($submitted == 'pxm_xfer') {
            $trans_credits = 0;
            if (! is_numeric($pxm_credits) OR $pxm_credits <= 0) {
              $notValid = 'ERROR: Credits are Zero or negative number in your Safelist Account. No Credits transfered.';
            } else if (! is_numeric($pxm_xfer_credits) OR $pxm_xfer_credits <= 0) {
                $notValid = 'ERROR: Credits to transfer must be an above Zero numeric value.';
            } else {
              if ($pxm_xfer_credits > $pxm_credits) {
                $trans_credits = $pxm_credits;
                $notValid  = 'Warning: Requested Credit Transfer Amount was greater than what was in your Safelist Account.';
              } else {
                $trans_credits = $pxm_xfer_credits;
              }

              $db->Query("UPDATE users SET credits=credits-$trans_credits WHERE username='$pxm_username' AND listname='$pxm_listname' AND listownerID='$pxm_listownerID'");
              $db->SelectDB('fap');
              $db->Query("UPDATE users SET lockedcredits=lockedcredits+$trans_credits WHERE affid='$affid' LIMIT 1");
              $notValid .= 'Successfully transfered '.$trans_credits.' to your Free AD Planet Locked Credit Account.';

              $db->Query("SELECT credits, lockedcredits FROM users WHERE affid='$affid' LIMIT 1");
              list($credits, $lockedcredits) = $db->FetchRow();
              $_SESSION['pxm_credits'] = $pxm_credits - $trans_credits;

              //@mail('elitescripts2000@yahoo.com', 'FAP - Credit XFER', "Credits: $trans_credits\nPXM user: $pxm_username\naffid: $affid", $headers);
            }
          }
        } else {
          $notValid = 'ERROR: Username, Password and/or List ID are incorrect or not found in the planetxmail.com SafeList Database.';
          unset($_SESSION['pxm_credits'], $pxm_listname);
        }
      } else {
        $notValid = 'ERROR: List ID is not a valid SafeList login ID at planetxmail.com';
        unset($_SESSION['pxm_credits'], $pxm_listname);
      }

      $db->SelectDB('fap');
    }

    notValid($notValid);

    $main_content = '
    <center><h2>Transfer Credits</h3>
    '.$downgrade_warning.'
    <table border="0" align="center" cellpadding="2" cellspacing="0">
      <tr>
        <td align="right"><b>'.$credits.'</b></td><td>Open Credits</td>
      </tr>
      <tr>
        <td align="right"><b>'.$lockedcredits.'</b></td><td>Locked Credits</td>
      </tr>
      <tr><td colspan="2"><hr /></td></tr>
      <tr>
        <td align="right"><b>'.($credits + $lockedcredits).'</b></td><td>Total Credits (open + locked)</td>
      </tr>
    </table>
    <br />

    '.$notValid.'
    <form name="xfer" action="?c=profile" onsubmit="javascript:submitOnce();" method="POST">

    Transfer
    <input type="text" name="xfercredits" value="" size="6" />
    <select name="from" onchange="javascript:xferCredits(\'from\')">
      <option value="credits">Open Credits</option>
      <option value="lockedcredits">Locked Credits</option>
    </select>

    To:
    <select name="to" onchange="javascript:xferCredits(\'to\')">
      <option value="credits">Open Credits</option>
      <option value="lockedcredits">Locked Credits</option>
    </select>

    <input id="submit" type="submit" value="Issue Transfer" />

    <input type="hidden" name="x" value="2" />
    <input type="hidden" name="submitted" value="xfer" />
    <input type="hidden" name="num_credits" value="'.$credits.'" />
    <input type="hidden" name="num_lockedcredits" value="'.$lockedcredits.'" />
    </form>
    ';

    if ($status == '1') {
      $pxm_current_login = '';

      if (isset($_SESSION['pxm_credits']) AND $pxm_listname) {
        $pxm_current_login = '<font color="red"><b>You are currectly Logged into: <font size="+1">'.$pxm_listname.'</font></b></font><br /><br />';
      } else {
        unset($_SESSION['pxm_credits'], $pxm_listname);
      }

      $main_content .= '
      <br /><br />
      <form name="pxm_login" action="?c=profile" onsubmit="javascript:submitOnce();" method="POST">

      <table border="0" align="center" cellpadding="2" cellspacing="2" width="100%">
        <tr>
          <td colspan="2" align="center">
            <h2>Transfer Credits from a Planet X Mail SafeList Account to your Free AD Planet Account.</h2>
            '.$pxm_current_login.'
          </td>
        </tr>

        <tr>
          <td align="right">Username:</td>
          <td><input type="text" name="pxm_username" value="'.$pxm_username.'" size="10" maxlength="20" /></td>
        </tr>

        <tr>
          <td align="right">Password:</td>
          <td><input type="text" name="pxm_password" value="'.$pxm_password.'" size="10" maxlength="20" /></td>
        </tr>

        <tr>
          <td align="right">List ID:</td>
          <td><input type="text" name="pxm_listID" value="'.$pxm_listID.'" size="10" maxlength="20" /></td>
        </tr>

        <tr>
          <td colspan="2" align="center">
            <hr />
            <input type="submit" value="Log In to Planet X Mail SafeList" />
          </td>
        </tr>
      </table>

      <input type="hidden" name="x" value="1" />
      <input type="hidden" name="c" value="profile" />
      <input type="hidden" name="submitted" value="pxm_login" />

      </form>
      ';
    }

    if ($status == '1' AND isset($_SESSION['pxm_credits'])) {
      $main_content .= '
      <form name="pxm_xfer" action="?c=profile" onsubmit="javascript:submitOnce();" method="POST">

        Transfer
        <input type="text" name="pxm_xfer_credits" value="'.$_SESSION['pxm_credits'].'" size="6" />

        PXM Credits to your FAP Locked Credit Account

        <input id="submit" type="submit" value="Issue Transfer" />

        <input type="hidden" name="x" value="1" />
        <input type="hidden" name="pxm_username" value="'.$pxm_username.'" />
        <input type="hidden" name="pxm_password" value="'.$pxm_password.'" />
        <input type="hidden" name="pxm_listID" value="'.$pxm_listID.'" />
        <input type="hidden" name="submitted" value="pxm_xfer" />
      </form>';
    }

    $main_content .= '
    </center>

    <p align="left">
      <b>Note:</b> The actual Open Credit amount, may vary over time, while this page is left unattended.
      Remember, that as people view your ADs, your Open Credit amount goes down with each viewing.
      Locked Credits are unaffected by people viewing your ADs.
      <br /><br />
      <b>Additional Note:</b> A maximum of ' . $max_credits_transferable . ' Open credits can be transfered to Closed credits per day.
      You can transfer as many Closed credits to Open Credits as you like per day.
    </p>
    <center>
      <a href="?c=profile&x=1">-- Click to Refresh Page --</a>
    </center>
    ';
  }
  else
  {
    if ($submitted == 'changeprofile')
    {
      $username = trim($_REQUEST['username']);
      $pass     = trim($_REQUEST['pass']);
      $fname    = ucwords(strtolower(trim($_REQUEST['fname'])));
      $lname    = ucwords(strtolower(trim($_REQUEST['lname'])));
      $email    = strtolower(trim($_REQUEST['email']));
      $paypal   = strtolower(trim($_REQUEST['paypal']));
      $alertpay = strtolower(trim($_REQUEST['alertpay']));
      $egold    = trim($_REQUEST['egold']);
      $alert_no_credits = trim($_REQUEST['alert_no_credits']);
      $alert_no_ads     = trim($_REQUEST['alert_no_ads']);

      if (! $db->Query("SELECT username, email, verified FROM users WHERE affid='$affid' LIMIT 1"))
        logout_session('ERROR: Contact Support Team.  Report error code: 2');
      list($prev_username, $prev_email, $verified) = $db->FetchRow();

      if (has_weird($username)) $notValid = 'ERROR: Username contains illegal characters.';
      else if ($notValid=LengthUsername($username)) {}
      else if ($notValid=LengthRealname($fname)) {}
      else if ($notValid=LengthRealname($lname)) {}
      else if (has_space($pass)) $notValid = 'ERROR: Password may not contain spaces.';
      else if ($notValid=LengthPassword($pass)) {}
      else if ($notValid=EmailFormat($email)) {}
      else if ($paypal AND ($notValid=EmailFormat($paypal, 0))) {}
      else if ($alertpay AND ($notValid=EmailFormat($alertpay, 0))) {}
      else if ($egold AND ! is_numeric($egold)) $notValid = 'ERROR: Egold account must be a numeric value.';
      else if (strtolower($prev_username) != strtolower($username) AND $db->Query("SELECT username FROM users WHERE username='$username' LIMIT 1"))
        $notValid = 'ERROR: Username: <i>'.$username.'</i> is already taken.';
      else if (strtolower($prev_email) != strtolower($email) AND $db->Query("SELECT email FROM users WHERE email='$email' AND affid != '$affid' LIMIT 1"))
      {
        $notValid = 'ERROR: Email: <i>'.$email.'</i> is already registered with another account.';
        $email = $prev_email;
      }
      else
      {
        $cat_str = build_cat_str($cat);

        $email_needs_validation = '';
        if (strtolower($prev_email) != strtolower($email) OR $verified == 2)
        {
          $hash = substr(md5(strrev(md5($affid.$email))), 0, 5);
          $val_url = "http://freeadplanet.com/?c=validatechangedemail&affid=$affid&h=$hash&e=$email";

          $notValid = '<br /><u>An Email was sent to revalidate your Changed Contact Email.</u>';

          $email_needs_validation = ", verified='2'";
          @mail($email, 'Free AD Planet - Validate Email Change', "Hello $fname $lname,\n\nVisit the URL below to validate your Email Change Request.\n\n$val_url\n\nregards,\nhttp://freeadplanet.com staff", 'From: Free AD Planet <do_not_reply@freeadplanet.com>');
        }

        $emailalerts = '';
        $alert_no_credits = $alert_no_credits ? '1' : '0';
        $alert_no_ads     = $alert_no_ads     ? '1' : '0';
        $emailalerts = $alert_no_credits.','.$alert_no_ads;

        $db->Query("UPDATE users SET username='$username', pass='$pass', fname='$fname', lname='$lname', email='$email', paypal='$paypal', alertpay='$alertpay', egold='$egold', emailalerts='$emailalerts', categories='$cat_str'$email_needs_validation WHERE affid='$affid' LIMIT 1");

        $notValid = 'Successfully updated your Profile.'.$notValid;
      }
    }

    if ($submitted == 'delete')
    {
      $db->Query("SELECT pass, email, fname, lname, username FROM users WHERE affid='$affid' LIMIT 1");
      list($checkpass, $email, $fname, $lname, $username) = $db->FetchRow();

      if ($pass == $checkpass)
      {
        delete_user($affid, $db);
        @mail($email, 'Free AD Planet - Account Deleted', "Hello $fname $lname,\n\nYour Account has been Deleted.\n\nUsername: $username\n\nThank you for using our system.\n\nRegards,\nhttp://freeadplanet.com", "From: Free AD Planet <do_not_reply@freeadplanet.com>");
        logout_session('Your Account has been Deleted.');
     }
     else
        $notValid = 'ERROR: Password does not match.<br />Account was not Deleted.';
    }

    extract(get_user($affid, $db));

    list($alert_no_credits, $alert_no_ads) = explode(',', $emailalerts);
    $alert_no_credits_checked = $alert_no_credits ? 'CHECKED' : '';
    $alert_no_ads_checked     = $alert_no_ads     ? 'CHECKED' : '';

    if ($db->Query("SELECT fname, lname FROM users WHERE affid='$sponsor' LIMIT 1"))
    {
      list($_fname, $_lname) = $db->FetchRow();
      $yoursponsor = "$_fname ".$_lname[0].".";
    }
    else
      $yoursponsor = 'No one sponsored you.';

    $cats = build_cat_table($categories, $db);

    $category_summary = '
    Targeted ADs belonging to the Categories you choice here will be displayed.<br /><br />
    ';

    notValid($notValid);

    $email_changed_notice = '';
    if ($verified == 2) {
      $email_changed_notice = '<font color="red"><b>Note:</b> Revalidate your Contact Email,<br />vai Email we sent to the new Email.</font>';
    }

    if ($status == 1)
    {
      $status_level = 'Professional';
      $upgrade_url  = '';
    }
    else if ($status == 2)
    {
      $status_level = 'Professional - Bill is Due!';
      $upgrade_url  = '<tr><td colspan="2" align="center"><a href="?c=renew" class="url_upgrade">Renew your PRO Membership today!</a><br /><br /></td></tr>';
    }
    else
    {
      $status_level = 'Free Member';
      $upgrade_url  = '<tr><td colspan="2" align="center"><a href="?c=upgrade" class="url_upgrade">Upgrade to Pro today!</a><br /><br /></td></tr>';
    }

    // start quota code
    $dayNum      = $numericDays[date('D')];
    $expected    = ($weekadmissed * $quotaRequirement[$status]) + ($dayNum * $quotaDailyRequirement[$status]);
    $totalmissed = $expected - $weekadcount;
    $totalviewed = $expected - $totalmissed;

    $tableRowFullWeek = '';

    if ($totalmissed == 0)
      $totalmissed = 'Reached. Go for Weekly Quota for Bonuses!';
    else if ($totalmissed < 0)
      $totalmissed = '<i>Exceeded!</i> Go for Weekly Quota for Bonuses!';

    if (! is_numeric($totalmissed))
    {
      $weekRemaining = $quotaRequirement[$status] - $totalviewed;
      if ($weekRemaining == 0)
      {
        $weekRemaining = 'Reached. Double the Credits per AD View!';
        $totalmissed   = 'You are on fire! Read below...';
      }
      else if ($weekRemaining < 0)
      {
        $weekRemaining = '<i>Exceeded!</i> Double the Credits per AD View!';
        $totalmissed   = 'You are on fire! Read below...';
      }
      $tableRowFullWeek = '
      <tr>
        <td align="right" nowrap><b>Weekly Remaining:</b></td>
        <td nowrap><font color="red"><b>'.$weekRemaining.'</b></font></td>
      </tr>
      ';
    }

    if ($weekadmissed)
    {
      $tableRowFullWeek .= '
      <tr>
        <td align="right" nowrap><b>Week(s) passed Missed:</b></td>
        <td nowrap><font color="red"><b>'.$weekadmissed.'</b></font></td>
      </tr>
      ';
    }
    // end quota code

    $main_content = '
    <form name="signup" action="?c=profile" onsubmit="javascript:submitOnce();" method="POST">

    <table border="0" cellpadding="2" cellspacing="0" align="center">
      <tr>
        <td align="center" colspan="2">
          <font size="+1"><b>Your Profile</b></font>
          <br />
          '.$notValid.'
        </td>
      </tr>

      '.$upgrade_url.'

      <tr>
        <td align="right"><b>Your Sponsor:</b></td>
        <td nowrap><font color="red"><b>'.$yoursponsor.'</b></font></td>
      </tr>

      <tr>
        <td colspan="2">
          <hr />
        </td>
      </tr>

      <tr>
        <td align="right" nowrap><b>Open Credits:</b></td>
        <td nowrap><font color="red"><b>'.$credits.'</b></font></td>
      </tr>

      <tr>
        <td align="right" nowrap><b>Locked Credits:</b></td>
        <td nowrap><font color="red"><b>'.$lockedcredits.'</b></font> - <a href="?c=profile&x=1">Transfer Credits</a></td>
      </tr>

      <tr>
        <td align="right" nowrap><b>Status Level:</b></td>
        <td nowrap><font color="red"><b>'.$status_level.'</b></font></td>
      </tr>

      <tr>
        <td align="right" nowrap><b>Your Affiliate ID:</b></td>
        <td nowrap><font color="red"><b>'.$affid.'</b></font></td>
      </tr>

      <tr>
        <td align="center" colspan="2">
          <hr />
          <b>AD View Quota Stats</b>
        </td>
      </tr>

      <tr>
        <td align="right" nowrap><b>Expected:</b></td>
        <td nowrap><font color="red"><b>'.$expected.'</b></font> - <a href="http://freeadplanet.com/policies.php" target="_blank">Read Quota Policy</a></td>
      </tr>

      <tr>
        <td align="right" nowrap><b>Achieved:</b></td>
        <td nowrap><font color="red"><b>'.$totalviewed.'</b></font></td>
      </tr>

      <tr>
        <td align="right" nowrap><b>Remaining:</b></td>
        <td nowrap><font color="red"><b>'.$totalmissed.'</b></font></td>
      </tr>

      '.$tableRowFullWeek.'

      <tr>
        <td colspan="2">
          <hr />
        </td>
      </tr>

      <tr>
        <td align="right"><b>Username:</b></td>
        <td nowrap><input type="text" name="username" value="'.$username.'" size="20" maxlength="20" /></td>
      </tr>

      <tr>
        <td align="right"><b>Password:</b></td>
        <td nowrap><input type="text" name="pass" value="'.$pass.'" size="20" maxlength="32" /></td>
      </tr>

      <tr>
        <td align="right"><b>First Name:</b></td>
        <td nowrap><input type="text" name="fname" value="'.$fname.'" size="20" maxlength="20" /></td>
      </tr>

      <tr>
        <td align="right"><b>Last Name:</b></td>
        <td nowrap><input type="text" name="lname" value="'.$lname.'" size="20" maxlength="20" /></td>
      </tr>

      <tr>
        <td align="right"><b>Contact Email:</b></td>
        <td><input type="text" name="email" value="'.$email.'" size="35" maxlength="255" /><br />
        '.$email_changed_notice.'
        </td>
      </tr>

      <tr>
        <td colspan="2">
          <hr />
        </td>
      </tr>

      <tr>
        <td align="right"><b>Email Alert:</b></td>
        <td nowrap><input type="checkbox" name="alert_no_credits" value="1" '.$alert_no_credits_checked.'/> When Open Credits Reach Zero</td>
      </tr>

      <tr>
        <td align="right"><b>Email Alert:</b></td>
        <td nowrap><input type="checkbox" name="alert_no_ads" value="1" '.$alert_no_ads_checked.'/> When AD View Quota not Reached</td>
      </tr>

      <tr>
        <td align="center" colspan="2">
          <hr />
          <b>You must have a <a href="https://secure.payza.com/?VwPhQPpbqEhle2hgofIZ%2fA%3d%3d" target="_blank">Payza (formerly Alertpay)</a> account to receive Commissions Earned.</b>
        </td>
      </tr>

      <tr>
        <td align="right"><b>Payza Email:</b></td>
        <td nowrap><input type="text" name="alertpay" value="'.$alertpay.'" size="35" maxlength="255" /></td>
      </tr>

      <tr>
        <td colspan="2">
          <hr />
        </td>
      </tr>

      <tr>
      <td colspan="2" align="center">

      <table width="350" border="0" cellspacing="0" cellpadding="0">
      <tr><td colspan="4" align="center"><font size="+1"><b>Categories</b></font><br /><br />'.$category_summary.'</td></tr>
      '.$cats.'
      </table>
      <hr />
      <center><input id="submit" type="submit" value="Update Your Profile" /></center>

      <input type="hidden" name="c" value="profile" />
      <input type="hidden" name="submitted" value="changeprofile" />
      </form>
      </td>
      </tr>
    </table>

    <table border="0" cellpadding="2" cellspacing="0" align="center">
      <tr>
      <td>

      <br />

      <form name="delete" action="?c=profile" method="POST">
        <center>To Delete your Account use the form below:</center>
        <br />
        <b>Enter Password:</b> <input type="text" name="pass" size="20" maxlength="100" />
        <input type="button" value="Delete Your Account" onClick="javascript:if(confirm(\'Are you sure you want to Delete your Account?\')){this.form.submit();} else {this.form.pass.value=\'\'}" />

        <input type="hidden" name="c" value="profile" />
        <input type="hidden" name="submitted" value="delete" />
      </form>

      <br /><br />
      </td>
      </tr>

    </table>
    ';
  }
}
else if ($c == 'referring')
{
  session_write_close();

  extract(get_user($affid, $db));

  $using = $_REQUEST['using'];

  if ($using == 'banners')
  {
    $typeofad = '
    <font color="blue"><b>
    Copy n Paste the HTML code provided for each banner below into YOUR Webpages to display a Banner with YOUR Affiliate ID.
    This will signup people under YOUR name so you can Earn the rewards mentioned above.
    </b></font>
    <center>
      <h3>Banner AD #1</h3>
      <a href="http://freeadplanet.com/?affid='.$affid.'" target="_blank">
        <img src="http://freeadplanet.com/images/banner1.jpg" border="0" />
      </a>
      <br /><br />
      <textarea readonly id="banner1" name="banner1" cols="60" rows="3" wrap="on" onclick="javascript:var obj=document.getElementById(\'banner1\');obj.focus();obj.select();"><a href="http://freeadplanet.com/?affid='.$affid.'" target="_blank">
          <img src="http://freeadplanet.com/images/banner1.jpg" alt="FREE Advertising!" border="0" />
      </a></textarea>

      <h3>Banner AD #2</h3>
      <a href="http://freeadplanet.com/?affid='.$affid.'" target="_blank">
        <img src="http://freeadplanet.com/images/banner2.jpg" border="0" />
      </a>
      <br /><br />
      <textarea readonly id="banner2" name="banner2" cols="60" rows="3" wrap="on" onclick="javascript:var obj=document.getElementById(\'banner2\');obj.focus();obj.select();"><a href="http://freeadplanet.com/?affid='.$affid.'" target="_blank">
          <img src="http://freeadplanet.com/images/banner2.jpg" alt="FREE Advertising!" border="0" />
      </a></textarea>
    </center>
    ';
  }
  else if ($using == 'soloads')
  {
    $typeofad = '
    <font color="blue"><b>
    Copy n Paste these text ADs as a SOLO AD or any other Email Advertising method.  Submit to a SafeList, for example.  You are free to re-word, change or
    otherwise modify them however you like. They are there to use as a guideline to start with.
    </b></font>

    <center><h3>Solo AD #1</h3></center>
    <input type="text" id="soload1subject" name="soload1subject" value="'.$fname.', 100% Free Advertising" size="60" readonly onclick="javascript:var obj=document.getElementById(\'soload1subject\');obj.focus();obj.select();" />
    <br /><br />
    <textarea readonly id="soload1message" name="soload1message" cols="60" rows="21" wrap="on" onclick="javascript:var obj=document.getElementById(\'soload1message\');obj.focus();obj.select();" >Hi '.$fname.',

When I say FREE I mean... FREE Advertising.

Not to just any low traffic site either.  This system is
a Push-Pull Credit Based System that gets EVERYONE involved.

Best of all, FREE members earn commissions from those that do
decide to upgrade.

Either way everyone wins.

RESULTS ARE GUARENTEED because the people that do not participate
do not Earn Credits and therefore do not get their ADs displayed.

It is a Push Pull system that has never before been seen on the web.

You owe it to yourself...

http://freeadplanet.com/?affid='.$affid.'
</textarea>

    <center><h3>Solo AD #2</h3></center>
    <input type="text" id="soload2subject" name="soload2subject" value="Free Advertising - Hands Down" size="60" readonly onclick="javascript:var obj=document.getElementById(\'soload2subject\');obj.focus();obj.select();" />
    <br /><br />
    <textarea readonly id="soload2message" name="soload2message" cols="60" rows="10" wrap="on" onclick="javascript:var obj=document.getElementById(\'soload2message\');obj.focus();obj.select();">Hi '.$fname.',

I am not going to waste your time in reading yet another Email AD.

You get FREE ADVERTISING PLUS Earn cash when your Downline makes Purchases.

Seeing is believing...

http://freeadplanet.com/?affid='.$affid.'
</textarea>

    </center>
    ';
  }
  else // Distributed ADs
  {
    $typeofad = '
    <font color="blue"><b>
    Copy n Paste the code below to generate an AD Block on your Websites. They will randomly generate ADs from members at Free AD Planet
    for you to Earn Credits and Cash.
    </b></font>
    <center>
    <h3>Horizonal Distributed AD</h3>
    <textarea readonly id="da1" name="da1" cols="60" rows="3" wrap="on" onclick="javascript:var obj=document.getElementById(\'da1\');obj.focus();obj.select();"><iframe src="http://freeadplanet.com/?c=dah&affid='.$affid.'" marginheight="1" marginwidth="0" height="100" width="810" scrolling="no" frameborder="0" align="middle"></iframe></textarea>
    </center>
    ';
  }

  $main_content = '
  <center><h3>Referring People Will Earn You <font color="green">Cash Money</font></h3></center>

  <center>'.$help_commissions.'</center>
  <br />
  There are many ways to refer people under your sponsorship. Below are the main ways of going about it. We suggest using all of them to your advantage for the best results.
  <br /><br />
  <b>Note:</b> If, affid is not present in the URL when someone visits <b>freeadplanet.com</b>, then a <i>random member will be selected</i> as the sponsor!
  <br /><br />
  <font color="red"><b>Your Affiliate URL:</font>&nbsp;http://freeadplanet.com/?affid='.$affid.'</b>
  <br /><br />
  <center>
    <a href="?c=referring&using=banners" class="menumembers">Banner ADs</a> |
    <a href="?c=referring&using=soloads" class="menumembers">Solo ADs</a> |
    <a href="?c=referring&using=distributedads" class="menumembers">Distributed ADs</a>
  </center>
  <hr />
  '.$typeofad.'
  ';
}
else if ($c == 'buyads')
{
  session_write_close();

  if ($t)
  {
    $t = strtolower($t);

    list(, $credit_cost) = get_type_cost($t);

    if ($t == 'soload' AND $status != '1')
      $notValid = 'ERROR: You must be a Professional Member to purchase Solo Ads with credits. <a href="?c=upgrade" class="url_upgrade">Upgrade to Pro today!</a>';
    else if ($notValid=buy_ad_with_credits($credit_cost, $credits, $lockedcredits)) {}
    else
    {
      $db->Query("INSERT INTO ad_purchased VALUES('','$affid','$t','0',NOW())");
      $db->Query("UPDATE users SET credits=$credits, lockedcredits=$lockedcredits WHERE affid='$affid' LIMIT 1");
      $notValid = 'Successfully Purchased a '.ucfirst($t).'.';
    }
  }

  $in_test_mode = $ap_test = $tc_test = '';
  if (TEST_MODE)
  {
    //$ap_test = '&ap_test=1'; // ap removed it from their service
    $tc_test = '&demo=Y';
    $in_test_mode = '<h3><font color="red">WARNING!!! In Test Mode</font></h3>';
  }

  $tc  = '<input type="button" value="2Checkout" class="twocheckout" onclick="javascript:location.href=\'https://www.2checkout.com/2co/buyer/purchase?sid=25344&quantity=1&product_id=[productid]&merchant_order_id='.$affid.'&fixed=Y'.$tc_test.'\'" />';

  $cb  = '<input type="button" value="ClickBank/PayPal" class="clickbank" onclick="javascript:location.href=\'http://[productid].nulled.pay.clickbank.net?vtid='.$affid.'\'" />';

  $ap  = '<input type="button" value="Payza" class="alertpay" onclick="javascript:location.href=\'https://www.payza.com/PayProcess.aspx?ap_purchasetype=Item&ap_merchant=freeadplanet@pxmb.com&ap_itemname=Free+AD+Planet+-+[adtype]&ap_currency=USD&ap_returnurl=http%3a%2f%2ffreeadplanet.com%2f?c=processorder%26fap_alertpay_thankyou%3D1&ap_quantity=1&ap_description=Free+AD+Planet+-+[adtype]&ap_amount=[amount]&ap_cancelurl=http%3a%2f%2ffreeadplanet.com%2f?c=processorder&apc_1='.$affid.'&apc_2=[adtype]'.$ap_test.'\'" />';

  notValid($notValid);

  $main_content = '
  <center>
    <h3>Purchase ADs</h3>
    You have <b>'.($credits + $lockedcredits).'</b> Total Credit(s) Available. <i>(Open + Locked Credits)</i>
    <br /><br />
    '.$in_test_mode.'
  </center>
  '.$notValid.'
 <table align="center" border="0" cellpadding="2" cellspacing="2">
  <tr bgcolor="lightblue" align="center">
    <td><b>Item</b></td>
    <td><b>Price</b></td>
    <td colspan="5"><b>Method of Payment</b></td>
  </tr>

  <tr bgcolor="beige">
    <td nowrap>* 1 <b>Targeted</b> AD</td>
    <td><b>$'.$price_targeted.'</b> or <b>'.$credits_targeted.'</b> Credits</td>
    <!-- <td>'.str_replace(array('[productid]'),array('10'),$tc).'</td> -->
    <td>'.str_replace(array('[productid]','[adtype]'),array('9','Targeted+AD'),$cb).'</td>
    <td>'.str_replace(array('[adtype]','[amount]'),array('targeted',$price_targeted),$ap).'</td>
    <!-- <td>'.str_replace(array('[adtype]','[amount]'),array('targeted',$price_targeted),$eg).'</td> -->
    <td><input type="button" value="Credits" class="credits" onclick="javascript:doubleCheck(\'targeted\');" /></td>
  </tr>

  <tr bgcolor="beige">
    <td nowrap>* 1 <b>SpotLight</b> AD</td>
    <td><b>$'.$price_spotlight.'</b> or <b>'.$credits_spotlight.'</b> Credits</td>
    <!-- <td>'.str_replace(array('[productid]'),array('11'),$tc).'</td> -->
    <td>'.str_replace(array('[productid]','[adtype]'),array('10','SpotLight+AD'),$cb).'</td>
    <td>'.str_replace(array('[adtype]','[amount]'),array('spotlight',$price_spotlight),$ap).'</td>
    <!-- <td>'.str_replace(array('[adtype]','[amount]'),array('spotlight',$price_spotlight),$eg).'</td> -->
    <td><input type="button" value="Credits" class="credits" onclick="javascript:doubleCheck(\'spotlight\');" /></td>
  </tr>

  <tr bgcolor="beige">
    <td>* 1 <b>BillBoard</b> AD</td>
    <td><b>$'.$price_billboard.'</b> or <b>'.$credits_billboard.'</b> Credits</td>
    <!-- <td>'.str_replace(array('[productid]'),array('12'),$tc).'</td> -->
    <td>'.str_replace(array('[productid]','[adtype]'),array('11','BillBoard+AD'),$cb).'</td>
    <td>'.str_replace(array('[adtype]','[amount]'),array('billboard',$price_billboard),$ap).'</td>
    <!-- <td>'.str_replace(array('[adtype]','[amount]'),array('billboard',$price_billboard),$eg).'</td> -->
    <td><input type="button" value="Credits" class="credits" onclick="javascript:doubleCheck(\'billboard\');" /></td>
  </tr>

  <tr bgcolor="beige">
    <td>* 1 <b>Banner</b> AD</td>
    <td><b>$'.$price_banner.'</b> or <b>'.$credits_banner.'</b> Credits</td>
    <!-- <td>'.str_replace(array('[productid]'),array('13'),$tc).'</td> -->
    <td>'.str_replace(array('[productid]','[adtype]'),array('12','Banner+AD'),$cb).'</td>
    <td>'.str_replace(array('[adtype]','[amount]'),array('banner',$price_banner),$ap).'</td>
    <!-- <td>'.str_replace(array('[adtype]','[amount]'),array('banner',$price_banner),$eg).'</td> -->
    <td><input type="button" value="Credits" class="credits" onclick="javascript:doubleCheck(\'banner\');" /></td>
  </tr>

  <tr bgcolor="beige">
    <td>* 1 <b>Exit</b> AD</td>
    <td><b>$'.$price_exit.'</b> or <b>'.$credits_exit.'</b> Credits</td>
    <!-- <td>'.str_replace(array('[productid]'),array('14'),$tc).'</td> -->
    <td>'.str_replace(array('[productid]','[adtype]'),array('13','Exit+AD'),$cb).'</td>
    <td>'.str_replace(array('[adtype]','[amount]'),array('exit',$price_exit),$ap).'</td>
    <!-- <td>'.str_replace(array('[adtype]','[amount]'),array('exit',$price_exit),$eg).'</td> -->
    <td><input type="button" value="Credits" class="credits" onclick="javascript:doubleCheck(\'exit\');" /></td>
  </tr>

  <tr bgcolor="beige">
   <td>** 1 <b>Solo</b> AD</td>
    <td nowrap><b>$'.$price_soload.'</b> or <b>'.$credits_soload.'</b> Credits</td>
    <!-- <td>'.str_replace(array('[productid]'),array('15'),$tc).'</td> -->
    <td>'.str_replace(array('[productid]','[adtype]'),array('14','Solo+AD'),$cb).'</td>
    <td>'.str_replace(array('[adtype]','[amount]'),array('soload',$price_soload),$ap).'</td>
    <!-- <td>'.str_replace(array('[adtype]','[amount]'),array('soload',$price_soload),$eg).'</td> -->
    <td><input type="button" value="Credits" class="credits" onclick="javascript:doubleCheck(\'soload\');" /></td>
  </tr>

  <tr bgcolor="beige">
    <td>Buy 500 <b>Credits</b></td>
    <td><b>$'.$price_credits.'</b></td>
    <!-- <td>'.str_replace(array('[productid]'),array('16'),$tc).'</td> -->
    <td>'.str_replace(array('[productid]','[adtype]'),array('15','500+Credits'),$cb).'</td>
    <td>'.str_replace(array('[adtype]','[amount]'),array('credits',$price_credits),$ap).'</td>
    <!-- <td align="left" colspan="2">'.str_replace(array('[adtype]','[amount]'),array('credits',$price_credits),$eg).'</td> -->
  </tr>

  </table>
  <br />
  <b>Purchases using Credits:</b> Locked Credits will be drawn from <i>First</i> and then from Open Credits,
  if not enough Locked Credits are available.
  <br />
  <br />
  <b>* Targeted, SpotLight, BillBoard, Banner and Exit ADs</b> expire after 30 days from date of purchase.
  During that time you can Modify or Recreate the AD as much as you like.
  <br /><br />
  <b>** Solo ADs</b> are mailed to the Contact Address of all Free <i>and</i> Professional members. Solo ADs also contain Earnable Credit Links which are
  highly sought after by members. This increases the chance of your AD and Website being read! You must also be a Professional member status to purchase
  Solo Ads with credits.
  ';

  if (TEST_MODE AND ! ($affid == '11187448' OR $affid == 'BLAHBLAH')) $main_content = '<center><h3>Buy ADs</h3>Temporarily disabled...</center>';
}
else if ($c == 'downline')
{
  session_write_close();

  $downline = '<table align="center" cellpadding="4" cellspacing="1"><tr bgcolor="lightblue" align="center" nowrap><td><b>User Name</b></td><td><b>First Name</b></td><td><b>Last Name</b></td><td><b>Status</b></td><td><b>Date Signed Up</b></td></tr>'."\n";

  if ($num_downline=$db->Query("SELECT username, fname, lname, status, datesignedup FROM users WHERE sponsor='$affid' AND verified != '0' ORDER BY fname"))
  {
    $i = 0;
    while (list($username, $fname, $lname, $status, $datesignedup) = $db->FetchRow())
    {
      $status = $status ? 'Pro' : 'Free';

      $datesignedup = mysql_datetime_to_humandate($datesignedup);

      $i++;

      if ($i % 2)
        $bgcolor = '#FFFFFF';
      else
        $bgcolor = '#EEEEEE';

      $downline .= '<tr bgcolor="'.$bgcolor.'" nowrap>';
      $downline .= '<td>'.$username.'</td>';
      $downline .= '<td>'.$fname.'</td>';
      $downline .= '<td>'.$lname[0].'.</td>';
      $downline .= '<td>'.$status.'</td>';
      $downline .= '<td>'.$datesignedup.'</td></tr>'."\n";
    }
  }
  else
    $downline = '<b>You have No Downline at this time.</b>';

  $downline .= '</table>'."\n";

  $main_content = '
  <center>
    <h3>Your DownLine</h3>
    Total People in your Downline: <b>'.$num_downline.'</b>
  </center>
  <br />
  '.$downline.'
  '.create_ads_browser($affid, $db).'
  ';
}
else if ($c == 'commissions')
{
  session_write_close();

  $commissions_table = '
  <table align="center" border="0" cellpadding="2" cellspacing="1">
    <tr align="center" bgcolor="lightblue" nowrap>
      <td><b>Member</b></td>
      <td><b>Earned</b></td>
      <td><b>Order Type</b></td>
      <td><b>Sale Date</b></td>
      <td><b>Matures In</b></td>
      <td><b>Paid Out?</b></td></tr>
  ';

  $downline = array();
  if ($db->Query("SELECT affid FROM users WHERE sponsor='$affid' ORDER BY fname"))
    while(list($_downline) = $db->FetchRow()) $downline[] = $_downline;

  if (count($downline))
  {
    $i = 0;
    foreach ($downline as $dl)
    {
      if ($db->Query("SELECT amount, type, id_paid, matured, dateofsale FROM commissions WHERE sponsor='$dl' ORDER BY dateofsale DESC"))
      {
        $result = $db->result;
        while (list($amount, $type, $id_paid, $matured, $dateofsale) = mysqli_fetch_row($result))
        {
          $db->Query("SELECT fname, lname FROM users WHERE affid='$dl' LIMIT 1");
          list($_fname, $_lname) = $db->FetchRow();

          $paid = $id_paid ? 'Yes' : 'No';

          if (! $matured)
          {
            $num_days = DateDiff(mysql_datetime_to_timestamp($dateofsale), time(), 'd');
            $num_days = round($num_days);
            if ($num_days < 0)
              $num_days = 'Matured';
            else
              $num_days = $commissions_days_mature - $num_days.' Days';
          }
          else
            $num_days = 'Matured';

          $dateofsale = mysql_datetime_to_humandate($dateofsale);

          $i++;

          if ($i % 2)
            $bgcolor = '#FFFFFF';
          else
            $bgcolor = '#EEEEEE';

          $commissions_table .= '
          <tr bgcolor="'.$bgcolor.'" nowrap>
            <td>'.$_fname.' '.$_lname[0].'.</td>
            <td>'.$amount.'</td>
            <td>'.ucfirst($type).'</td>
            <td>'.$dateofsale.'</td>
            <td align="center">'.$num_days.'</td>
            <td align="center">'.$paid.'</td>
          </tr>
          ';
        }
      }
    }
  }
  else
    $commissions_table = '<tr><td colspan="10" align="center"><b>No Commissions on Record at this time.</b></td></tr>';
  $commissions_table .= '</table>';

  $help = $help_commissions;

  $main_content = '
  <center><h3>Commissions Generated by Your Downline</h3></center>
  '.$help.'
  <br />
  '.$downgrade_warning.'
  '.$commissions_table.'
  <br />
  '.create_ads_browser($affid, $db).'
  ';
}
else if ($c == 'mailer')
{
  session_write_close();

  $num_downline = $db->Query("SELECT username FROM users WHERE sponsor='$affid' AND verified='1'");
  $num_soloads  = $db->Query("SELECT id FROM ad_purchased WHERE affid='$affid' AND type='soload'");

  if ($_POST['submitted'] == 'sendmail' OR $_POST['submitted'] == 'save')
  {
    $heading = substr(trim($_POST['heading']), 0, $ml_max_head_chars);
    $message = substr(trim($_POST['message']), 0, $ml_max_mess_chars);
    $crediturl  = trim($_POST['crediturl']);
    $sendsoload = $_POST['sendsoload'];
    $usecredits = trim($_POST['usecredits']);

    $heading = ucwords(strtolower($heading));

    $soload_txt = '';
    $is_soload = 0;
    if (@is_numeric($sendsoload) AND $num_soloads)
      $is_soload = 1;
    else
      $soload_txt = '<br />However, you have <b>'.$num_soloads.' Purchased Solo AD(s)</b> available.<br />Check the <i>Send as Solo AD</i> Box to mail one!';

    if ($heading == '' OR $message == '')
      $notValid = 'ERROR: Missing Subject and/or Message.';
    else if ($notValid=valid_url($crediturl)) {}
    else if ($notValid=valid_mail_content($heading, $message)) {}
    else if ($_POST['submitted'] == 'save')
    {
      $soload_txt = '';
      $is_soload = 0;
      $db->Query("UPDATE users SET heading='$heading', message='$message', crediturl='$crediturl' WHERE affid='$affid' LIMIT 1");
      $notValid = 'Successfully Saved.<br />Nothing was Mailed Out.';
    }
    else if (! $is_soload AND ! $lockedcredits)          $notValid = 'ERROR: You have 0 (zero) Locked Credits.'.$soload_txt;
    else if (! $is_soload AND $mailedtoday)              $notValid = 'ERROR: You already Emailed Out today.'.$soload_txt;
    else if (! $is_soload AND ! is_numeric($usecredits)) $notValid = 'ERROR: Credits entered was not numerical.';
    else if (! $is_soload AND ! $num_downline)           $notValid = 'ERROR: You have no Downline to Email.';
    else
    {
      $db->Query("SELECT username FROM users WHERE affid='$affid' LIMIT 1");
      list($username) = $db->FetchRow();

      if ($is_soload)
      {
        $type = 9;
        $from_name = 'FAP - SOLO AD';
        $earn_more = '5 times the normal ';
        $num_to_mail = $db->Query("SELECT fname, email, affid FROM users WHERE verified='1'");
      }
      else
      {
        $type = 0;
        $from_name = 'Free AD Planet';
        $earn_more = '';
        $num_to_mail = $db->Query("SELECT fname, email, affid FROM users WHERE sponsor='$affid' AND verified='1' LIMIT $usecredits");
      }

      $mail_was_submitted = 0;

      if ($num_to_mail)
      {
        if (! $is_soload)
          $db->Query("UPDATE users SET heading='$heading', message='$message', crediturl='$crediturl', mailedtoday='1', lockedcredits=lockedcredits-$num_to_mail WHERE affid='$affid' LIMIT 1");
        else if ($is_soload)
        {
          $db->Query("UPDATE users SET heading='$heading', message='$message', crediturl='$crediturl' WHERE affid='$affid' LIMIT 1");
          $db->Query("DELETE FROM ad_purchased WHERE affid='$affid' AND type='soload' LIMIT 1");
        }

        $db->Query("INSERT INTO mailqueue (affid,    subject,    message,     crediturl,    usecredits,   soload,      datesubmitted)
                                   VALUES ('$affid', '$heading', '$message', '$crediturl', '$usecredits', '$is_soload', NOW())");

        //@mail('elitescripts2000@yahoo.com', 'FAP Admin Alert - '.$heading, $messageQueue, $headers);

        fap_log("user:$username mailed out - soload:$is_soload creditsused:$usecredits");

        // use below until more members signup for solo ads
        $soload_txt = '';
        if ($is_soload)
          $notValid = 'Your Solo AD has been queued for delivery.';
        else
          $notValid = 'Your mailing to <b>'.$num_mailed.'</b> Downline Member(s) has been queued for delivery.';

        $mail_was_submitted = 1;
      }
      else {
        $notValid = 'Unable to find any downline to mail.';
      }
    }
  }
  else
  {
    $db->Query("SELECT heading, message, crediturl FROM users WHERE affid='$affid' LIMIT 1");
    list($heading, $message, $crediturl) = $db->FetchRow();
  }

  // get downline
  if ($num_downline=$db->Query("SELECT username FROM users WHERE sponsor='$affid' AND verified='1'"))
    $state = 'You have <b>'.$num_downline.'</b> Member(s) in your Downline.<br />';
  else
    $state = '<font color="red"><b>You have no Downline.</b></font><br /><a href="?c=referring">-- Click Here for Instructions on how to increase your Downline. --</a><br />';

  // get credits
  $db->Query("SELECT credits, lockedcredits, mailedtoday FROM users WHERE affid='$affid' LIMIT 1");
  list($credits, $lockedcredits, $mailedtoday) = $db->FetchRow();
  if ($mailedtoday) $str_mailedtoday = 'Mailed Today.'; else $str_mailedtoday = '<b>not</b> Mailed Today.';
  $state .= '<br />You have <b>'.$lockedcredits.'</b> Locked Credit(s) available.';

  // get soloads
  $soloads = array();
  if ($num_soloads=$db->Query("SELECT id FROM ad_purchased WHERE affid='$affid' AND type='soload'"))
    while (list($_id) = $db->FetchRow()) $soloads[] = $_id;
  $state .= '<br /><br />You have <b>'.$num_soloads.'</b> Purchased Solo AD(s) available.';
  $soload_checkbox = '';
  if ($num_soloads) $soload_checkbox = '<input type="checkbox" name="sendsoload" value="1" /> Send as a Solo AD - <i>No Credits will be used.</i><br /><br />'."\n";
  $state .= '<br /><br />You have '.$str_mailedtoday;

  if ($lockedcredits > $num_downline) {
    $usecredits = $num_downline;
  } else if ($lockedcredits <= $num_downline) {
    $usecredits = $lockedcredits;
  }

  $mailer_form = '';
  if (! $mail_was_submitted)
  {
    if (($lockedcredits AND $num_downline AND ! $mailedtoday) OR $num_soloads)
    {
      $mailer_form = '
      <br /><br />
      Customize your AD using <b>[fname]</b>, which gets replaced by each member\'s First Name.
      <br /><br />
      <form name="mailer" action="?c=mailer" method="POST">
        <b>Subject:</b><br />
        <input type="text" name="heading" size="60" value="'.stripslashes(htmlentities($heading)).'" maxlength="'.$ml_max_head_chars.'" onFocus="focus_heading=true" onBlur="focus_heading=false" />
        <br />
        <input type="text" name="counter_heading" size="2" readonly /> Remaining Characters
        <br /><br />
        <b>Message:</b><br />
        <textarea name="message" rows="15" cols="60" wrap="physical" onFocus="focus_message=true" onBlur="focus_message=false">'.stripslashes(htmlentities($message)).'</textarea>
        <br />
        <input type="text" name="counter_message" size="3" readonly /> Remaining Characters
        <br /><br />
        <b>Credit URL:</b> <i>Example: http://yoursite.com</i><br />
        <input type="text" name="crediturl" value="'.$crediturl.'" size="60" />
        <hr />
        Use <input type="text" name="usecredits" value="'.$usecredits.'" size="3" maxlength="5" /> of <b>'.$lockedcredits.'</b> Locked Credits. <i>One credit equates to one Member.</i>
        <br />
        <hr />
        <center>
          '.$soload_checkbox.'
          <input type="submit" value="Send Mail" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          <input type="button" value="Save Only" onclick="javascript:saveOnly();" />
          <br /><br />
          <b>Note:</b> Pages/Links designed to break out of browser frames,<br />preventing Member Credit Earning, will be deleted and banned.
        </center>

        <input type="hidden" name="c" value="mailer" />
        <input id="submitted" type="hidden" name="submitted" value="sendmail" />
      </form>
      ';
    }
    else
      $notValid = 'ERROR: Unable to Mail because...<br />1) You may have no Locked Credits.<br />2) You may have no Downline.<br />3) You may have already mailed out today.<br />4) You may have Purchased no Solo ADs.';
  }

  $db->Query("SELECT username FROM users WHERE affid='$affid' LIMIT 1");
  list($username) = $db->FetchRow();

  notValid($notValid);
  fap_log($username.': ' . trim(strip_tags($notValid)) );

  $notes = '
  <hr /><b>Credit Draw:</b> <i>Locked Credits are used when mailing out.</i> Except Purchased Solo ADs.<br />
  You may need to <a href="?c=profile&x=1">Transfer</a> some Open Credits to Locked Credits to mail out.
  <br /><br />
  <b>Purchased Solo ADs:</b> All contain <i>Earnable Credit URLs</i> worth <u>5 times</u> the normal amount.
  The result is that members aggressively seek them out, hense, read the Solo ADs and visit your Web Site at an increased rate!
  Solo ADs are mailed to <i>every</i> member currently registered at Free AD Planet, not just to your Downline. You can obtain one in the
  <a href="?c=buyads">Buy ADs</a> section, either with Credits or Money.
  Once your order is received, you will see a <i>Send as Solo AD</i> checkbox, which you click on, <i>before</i> clicking on the Send Mail button.
  This will trigger a Solo AD mailing, instead of a regular Downline mail out.
  <br /><br />
  '.$porn_warning.'
  ';

  $main_content = '
  <center><h3>Email Your Downline, or send a Purchased Solo AD.</h3></center>
  '.$downgrade_warning.'
  '.$notValid.'
  '.$state.'
  '.$mailer_form.'
  '.$notes.'
  ';
}
else if ($c == 'spotlightads')
{
  session_write_close();

  $allowed_modes = array('add','edit','delete','show');
  if (! in_array($mode, $allowed_modes)) $mode = 'show';

  list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_sl, $affid, $db);

  if ($mode == 'add')
  {
    $add_url = '';

    if ($notValid=ads_max($c, $allowed_sl, $num_ads, $num_purchased_ads_created, $num_purchased_ads, $p))
      $mode = 'show';
    else if ($submitted == 'save')
    {
      $heading = substr(strip_tags(trim($heading)), 0, $sl_max_head_chars);
      $message = substr(strip_tags(trim($message)), 0, $sl_max_mess_chars);
      $url     = trim($url);
      $active  = trim($active);

      if ($notValid=valid_url($url)) {}
      else if ($notValid=ad_content_illegal($heading.$message)) {}
      else if ($notValid=longest_word($message)) {}
      else
      {
        ads_active_check_add($c, $num_ads, $active, $status, $p, $affid, $db);

        $id_ad = get_available_ad_id($affid, 'spotlight', $db);
        $db->Query("INSERT INTO ad_spotlights VALUES('$id_ad','$affid','$heading','$message','$url','$active',NOW(),NOW())");
        if (! $id_ad)
          $id_ad = $db->GetLastID();
        else
          remove_available_ad_id($affid, $id_ad, 'spotlight', $db);

        if ($p) $db->Query("UPDATE ad_purchased SET id_ad='$id_ad' WHERE id='$active' AND affid='$affid'");
        $notValid = 'Successfully added your SpotLight AD.';
        $mode = 'show';
      }
    }
  }

  if ($mode == 'edit')
  {
    $add_url = '';

    $id = trim($id);

    if (! @is_numeric($id))
      $notValid = 'ERROR: Invalid id parameter found.';
    else if (! $db->Query("SELECT heading, message, url, active FROM ad_spotlights WHERE affid='$affid' AND id='$id' LIMIT 1"))
    {
      $notvalid = 'ERROR: This SpotLight AD does not belong to you.';
      $mode = 'show';
    }
    else
    {
      if ($submitted != 'save') // load from mysql
      {
        list($heading, $message, $url, $active) = $db->FetchRow();
        $prev_active = $active;
      }
      else
      {
        $heading = substr(strip_tags(trim($heading)), 0, $sl_max_head_chars);
        $message = substr(strip_tags(trim($message)), 0, $sl_max_mess_chars);
        $url     = trim($url);
        $active  = trim($active);

        if ($notValid=valid_url($url)) {}
        else if ($notValid=ad_content_illegal($heading.$message)) {}
        else if ($notValid=longest_word($message)) {}
        else
        {
          ads_active_check_edit($c, $id, $num_ads, $active, $prev_active, $status, $notValid, $affid, $db);

          $db->Query("UPDATE ad_spotlights SET heading='$heading', message='$message', url='$url', active='$active', datemodified=NOW() WHERE id='$id' LIMIT 1");
         $notValid .= 'Successfully updated your SpotLight AD.';
        }
      }
    }
  }

  if ($mode == 'delete')
  {
    $notValid = ads_delete($c, $id, $affid, $status, $db);
    $mode = 'show';
  }

  if ($mode == 'show')
  {
    $preview = '
    <table align="center" border="0" cellpadding="2" cellspacing="0">
    <tr><td align="center" colspan="2">
    <font size="1"><b>SpotLight AD(s) Shown Below:</b></font>
    </td></tr>
    ';

    if ($db->Query("SELECT id, heading, message, url, active FROM ad_spotlights WHERE affid='$affid' ORDER BY id"))
    {
      $i = 0;
      while (list($id, $heading, $message, $url, $active) = $db->FetchRow())
      {
        if ($i % 2 == 0) $head = '<tr valign="top"><td>'; else $head = '<td>';
        if ($i % 2 == 0) $tail = '</td>'; else $tail = '</td></tr>';

        $style = ads_get_style($active);

        $preview .= $head.'
        <div class="spotlight"'.$style.'>
        <a href="'.$url.'" target="_blank" class="spotlight_links">'.stripslashes(htmlentities($heading)).'</a>
        <br />
        '.stripslashes(htmlentities($message)).'
        </div>
        <center>
        <a href="?c=spotlightads&mode=edit&id='.$id.'">Edit</a> |
        <a href="javascript:void(0)" onClick="javascript:if(confirm(\'Are you sure you want to delete?\'))location.href=\'?c=spotlightads&mode=delete&id='.$id.'\'">Delete</a>
        </center>
        '.$tail.'
        ';

        $i++;
      }
    }
    else
      $preview .= '<tr><td align="center" colspan="2"><b>None Created.</b></td></tr>';

    $preview .= '
    </table>
    ';

    $preview .= '<hr />'.create_ads_browser($affid, $db);

    list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_sl, $affid, $db);
  }

  $adform = $active_radios = '';
  if ($mode == 'add' OR $mode == 'edit')
  {
    list($active_radios, $p_title) = ads_active_radios($status, $active, $p);

    $adform = '
    <center><b>'.ucfirst($mode).' a '.$p_title.'SpotLight AD</b></center>
    <form name="spotlightad" action="?c=spotlightads" onsubmit="javascript:submitOnce();" method="POST">
    <b>AD Heading:</b>
    <br />
    <input type="text" name="heading" value="'.stripslashes(htmlentities($heading)).'" size="25" maxlength="'.$sl_max_head_chars.'" onFocus="focus_heading=true" onBlur="focus_heading=false" />
    <br />
    <input type="text" name="counter_heading" size="2" readonly /> Remaining Characters
    <br /><br />
    <b>AD Message:</b>
    <br />
    <input type="text" name="message" value="'.stripslashes(htmlentities($message)).'" size="60" maxlength="'.$sl_max_mess_chars.'" onFocus="focus_message=true" onBlur="focus_message=false" />
    <br />
    <input type="text" name="counter_message" size="2" readonly /> Remaining Characters
    <br /><br />
    <b>AD URL/Link:</b>
    <br />
    <input type="text" name="url" value="'.$url.'" size="60" maxlength="255" />
    '.$active_radios.'
    <br /><hr />
    <center>
    <input id="submit" type="submit" value="'.ucfirst($mode).' Spotlight AD" />
    <br /><br />
    <b>Note:</b> Pages/Links designed to break out of browser frames,<br />preventing Member Credit Earning, will be deleted and banned.
    </center>

    <input type="hidden" name="id" value="'.$id.'" />
    <input type="hidden" name="mode" value="'.$mode.'" />
    <input type="hidden" name="prev_active" value="'.$prev_active.'" />
    <input type="hidden" name="p" value="'.$p.'" />
    <input type="hidden" name="c" value="spotlightads" />
    <input type="hidden" name="submitted" value="save" />
    </form>
    ';
  }

  $help = '
  <center><a href="javascript:Toggle(\'help\')">-- Click to Toggle - How SpotLight ADs Work --</a></center>
  <div id="help" class="helparea">
  Spotlight ADs contain a Heading and Message.
  Clicking on the Heading redirects your prospect to your Website.
  These ADs appear in the AD Browser, in the Left Panel of Public Access and in <a href="?c=referring&using=distributedads">Distributed ADs</a>.
  '.$help_borders.'
  </div>
  ';

  notValid($notValid);

  $purchased_count = '';
  if ($num_purchased_ads) $purchased_count = "<br />$num_purchased_ads_created of $num_purchased_ads Purchased ADs created.\n";

  $standard_count = $num_ads.' of '.$allowed_sl.' created.';

  $main_content = '
  '.$downgrade_warning.'
  <center>
    <h3>SpotLight ADs - '.$standard_count.'<br /></h3>
    '.$help.'
    '.$purchased_count.'
    <br />
  </center>
  '.$notValid.'
  '.$add_url.'
  '.$adform.'
  '.$preview.'
  ';
}
else if ($c == 'billboardads')
{
  session_write_close();

  $allowed_modes = array('add','edit','delete','show');
  if (! in_array($mode, $allowed_modes)) $mode = 'show';

  list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_bb, $affid, $db);

  if ($mode == 'add' AND ($status == 1 OR $num_purchased_ads))
  {
    $add_url = '';

    if ($notValid=ads_max($c, $allowed_bb, $num_ads, $num_purchased_ads_created, $num_purchased_ads, $p))
      $mode = 'show';
    else if ($submitted == 'save')
    {
      $heading  = substr(strip_tags(trim($heading)), 0, $bb_max_head_chars);
      $message  = substr(strip_tags(trim($message)), 0, $bb_max_mess_chars);
      $img_pos  = trim($img_pos);
      $curr_img = trim($curr_img);
      $url      = trim($url);
      $id       = trim($id);
      $active   = trim($active);

      if ($notValid=valid_url($url)) {}
      else if ($notValid=ad_content_illegal($heading.$message)) {}
      else if ($notValid=longest_word($message)) {}
      else
      {
        list($notValid, $rand_image_name) = check_uploaded_image('uploadedfile', 'billboard', $curr_img);

        if (! stristr($notValid, 'ERROR:'))
        {
          ads_active_check_add($c, $num_ads, $active, $status, $p, $affid, $db);

          if ($img_pos) $img_pos = 1; else $img_pos = 0;

          $id_ad = get_available_ad_id($affid, 'billboard', $db);
          $db->Query("INSERT INTO ad_billboards VALUES('$id_ad','$affid','$heading','$message','$url','$rand_image_name','$img_pos','$active',NOW(),NOW())");
          if (! $id_ad)
            $id_ad = $db->GetLastID();
          else
            remove_available_ad_id($affid, $id_ad, 'billboard', $db);

          if ($p) $db->Query("UPDATE ad_purchased SET id_ad='$id_ad' WHERE id='$active' AND affid='$affid'");
          $notValid .= 'Successfully added your BillBoard AD.';
          $mode = 'show';
        }
      }
    }
  }

  if ($mode == 'edit')
  {
    $add_url = '';

    $id = trim($id);

    if (! @is_numeric($id))
      $notValid = 'ERROR: Invalid id parameter found.';
    else if (! $db->Query("SELECT heading, message, url, image, img_pos, active FROM ad_billboards WHERE affid='$affid' AND id='$id' LIMIT 1"))
    {
      $notValid = 'ERROR: This BillBoard AD does not belong to you.';
      $mode = 'show';
    }
    else
    {
      if ($submitted != 'save') // load from mysql
      {
        list($heading, $message, $url, $image, $img_pos, $active) = $db->FetchRow();
        $prev_active = $active;
      }
      else
      {
        $heading = substr(strip_tags(trim($heading)), 0, $bb_max_head_chars);
        $message = substr(strip_tags(trim($message)), 0, $bb_max_mess_chars);
        $url     = trim($url);
        $image   = trim($curr_img);
        $img_pos = trim($img_pos);
        $active  = trim($active);
      }

      list($img_form1, $img_form2, $img_preview) = load_image($image, $img_pos);

      if ($submitted == 'save')
      {
        if ($notValid=valid_url($url)) {}
        else if ($notValid=ad_content_illegal($heading.$message)) {}
        else if ($notValid=longest_word($message)) {}
        else
        {
          if ($deleteimage)
          {
            $db->Query("SELECT image FROM ad_billboards WHERE affid='$affid' AND id='$id'");
            list($del_img) = $db->FetchRow();
            if (@is_file("$upload_path/$del_img")) @unlink("$upload_path/$del_img");
            $notValid = 'Successfully deleted Image.<br />';
            $img_pos = '0';
          }
          else
          {
            list($notValid, $image) = check_uploaded_image('uploadedfile', 'billboard', $curr_img);

            if (! stristr($notValid, 'Keeping your previous') AND ! stristr($notValid, 'ERROR:'))
            {
              // delete old image
              $db->Query("SELECT image FROM ad_billboards WHERE affid='$affid' AND id='$id' LIMIT 1");
              list($del_img) = $db->FetchRow();
              if (@is_file("$upload_path/$del_img")) @unlink("$upload_path/$del_img");
              $img_pos = '0';
            }
          }

          list($img_form1, $img_form2, $img_preview) = load_image($image, $img_pos);

          ads_active_check_edit($c, $id, $num_ads, $active, $prev_active, $status, $notValid, $affid, $db);

          $db->Query("UPDATE ad_billboards SET heading='$heading', message='$message', url='$url', image='$image', img_pos='$img_pos', active='$active', datemodified=NOW() WHERE affid='$affid' AND id='$id'");
          $notValid .= 'Successfully updated your BillBoard AD.';
        }
      }
    }
  }

  if ($mode == 'delete')
  {
    $notValid = ads_delete($c, $id, $affid, $status, $db);
    $mode = 'show';
  }

  if ($mode == 'show')
  {
    $preview = '
    <table align="center" border="0" cellpadding="2" cellspacing="0">
    <tr><td align="center" colspan="2">
    <h2>BillBoard AD(s) Shown Below:</h2>
    </td></tr>
    ';

    if ($db->Query("SELECT id, heading, message, url, image, img_pos, active FROM ad_billboards WHERE affid='$affid' ORDER BY id"))
    {
      $i = 0;
      while (list($id, $heading, $message, $url, $image, $img_pos, $active) = $db->FetchRow())
      {
        $img_preview = '';
        if (@is_file("$upload_path/$image"))
        {
          list(,,,$attr) = getimagesize("$upload_path/$image");
          if ($img_pos == '0') $float = 'floatLeft';
          else $float = 'floatRight';
          $img_preview = '<img src="http://freeadplanet.com/_signs/'.$image.'" '.$attr.' border="0" class="'.$float.'" />';
        }

        if ($i % 2 == 0) $head = '<tr valign="top"><td>'; else $head = '<td>';
        if ($i % 2 == 0) $tail = '</td>'; else $tail = '</td></tr>';

        $style = ads_get_style($active);

        //echo "style=$style active=$active<br />";

        $preview .= $head.'
        <div class="billboard"'.$style.'>
        '.$img_preview.'
        <a href="'.$url.'" target="_blank" class="billboard_links">'.stripslashes(htmlentities($heading)).'</a>
        <br />
        '.stripslashes(htmlentities($message)).'
        </div>
        <center>
        <a href="?c=billboardads&mode=edit&id='.$id.'">Edit</a> |
        <a href="javascript:void(0)" onClick="javascript:if(confirm(\'Are you sure you want to delete?\'))location.href=\'?c=billboardads&mode=delete&id='.$id.'\'">Delete</a>
        </center>
        '.$tail.'
        ';

        $i++;
      }
    }
    else
     $preview .= '<tr><td align="center" colspan="2"><b>None Created.</b></td></tr>';

    $preview .= '
    </table>
    ';

    $preview .= create_ads_browser($affid, $db);

    list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_bb, $affid, $db);
  }

  $adform = $active_radios = '';
  if ($mode == 'add' OR $mode == 'edit')
  {
    list($active_radios, $p_title) = ads_active_radios($status, $active, $p);

    $adform = '
    <center><b>'.ucfirst($mode).' a '.$p_title.'BillBoard AD</b></center>
    <form name="billboardad" action="?c=billboardads" enctype="multipart/form-data" onsubmit="javascript:submitOnce();" method="POST">
    <table border="0" cellpadding="4" cellspacing="1">

      <tr>
        <td colspan="3">
          <b>AD Heading:</b>
          <br />
          <input type="text" name="heading" value="'.stripslashes(htmlentities($heading)).'" size="25" maxlength="'.$bb_max_head_chars.'" onFocus="focus_heading=true" onBlur="focus_heading=false" />
          <br />
          <input type="text" name="counter_heading" size="2" readonly /> Remaining Characters
        </td>
      </tr>

      <tr>
        <td colspan="3">
          <hr />
          <b>AD Message:</b>
          <br />
          <input type="text" name="message" value="'.stripslashes(htmlentities($message)).'" size="60" maxlength="'.$bb_max_mess_chars.'" onFocus="focus_message=true" onBlur="focus_message=false" />
          <br />
          <input type="text" name="counter_message" size="2" readonly /> Remaining Characters
          <hr />
        </td>
      </tr>

      <tr>
        <td width="10" nowrap><b>AD Image:</b><br /><i>Max Dimensions: 50 x 50<br />Max File Size: 10 k</i></td>
        <td align="left" valign="top" nowrap>'.$img_form1.'</td>
        <td align="left" valign="top" nowrap>'.$img_form2.'</td>
      </tr>

      <tr>
        <td colspan="3">
          <input type="file" name="uploadedfile" size="40" />&nbsp;
        </td>
      </tr>

      <tr>
        <td colspan="3">
          <hr />
          <b>AD URL/Link:</b>
          <br />
          <input type="text" name="url" value="'.$url.'" size="60" maxlenght="255" />
        </td>
      </tr>

      <tr>
        <td align="center" colspan="3">
          '.$active_radios.'
          <br /><hr />
          <input type="submit" value="'.ucfirst($mode).' BillBoard AD" />
          <br /><br />
          <b>Note:</b> Pages/Links designed to break out of browser frames,<br />preventing Member Credit Earning, will be deleted and banned.
        </td>
      </tr>

    </table>

    <input type="hidden" name="curr_img" value="'.$image.'" />
    <input type="hidden" name="id" value="'.$id.'" />
    <input type="hidden" name="mode" value="'.$mode.'" />
    <input type="hidden" name="prev_active" value="'.$prev_active.'" />
    <input type="hidden" name="p" value="'.$p.'" />
    <input type="hidden" name="c" value="billboardads" />
    <input type="hidden" name="submitted" value="save" />
    </form>
    ';
  }

  $help = '
  <center><a href="javascript:Toggle(\'help\')">-- How Billboard ADs Work --</a></center>
  <div id="help" class="helparea">
  BillBoard ADs are unique in that you can assign a small Image or Logo as well as the usual
  Heading and Message. You can position the Image to the Left or Right. These ADs will appear
  in the AD Browser and in the Left Panel of Public Access.
  '.$help_borders.'
  </div>
  ';

  notValid($notValid);

  $purchased_count = '';
  if ($num_purchased_ads) $purchased_count = "<br />$num_purchased_ads_created of $num_purchased_ads Purchased ADs created.\n";

  $standard_count = $num_ads.' of '.$allowed_bb.' Standard ADs created.';

  if ($status == 0 AND ! $num_purchased_ads)
  {
    $main_content = '
    <center>
      <h3>BillBoard ADs</h3>
      <a href="?c=upgrade" class="url_upgrade">Upgrade to Pro today!</a>
      <br /><br />
      '.$help_benefits.'
    </center>
    ';
  }
  else
  {
    if ($status == 0) $standard_count = '<div class="distributed"><center>Pro Members get '.$bb_max_ads_pro.' of these ADs with membership.<br /><a href="?c=upgrade" class="url_upgrade">Upgrade to Pro today!</a></center></div>';

    $main_content = '
    '.$downgrade_warning.'
    <center>
      <h3>BillBoard ADs<br /></h3>
      '.$help.'
      <br />
      '.$standard_count.'
      '.$purchased_count.'
      <br /><br />
    </center>
    '.$notValid.'
    '.$add_url.'
    '.$adform.'
    '.$preview.'
    ';
  }
}
else if ($c == 'targetedads')
{
  session_write_close();

  $allowed_modes = array('add','edit','delete','show');
  if (! in_array($mode, $allowed_modes)) $mode = 'show';

  list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_ta, $affid, $db);

  if ($mode == 'add')
  {
    $add_url = '';

    $cat_str = build_cat_str($cat);
    $cats    = build_cat_table($cat_str, $db);

    if ($notValid=ads_max($c, $allowed_ta, $num_ads, $num_purchased_ads_created, $num_purchased_ads, $p))
      $mode = 'show';
    else if ($submitted == 'save')
    {
      $heading = substr(strip_tags(trim($heading)), 0, $ta_max_head_chars);
      $message = substr(strip_tags(trim($message)), 0, $ta_max_mess_chars);
      $url     = trim($url);
      $active  = trim($active);

      if ($notValid=valid_url($url)) {}
      else if ($notValid=ad_content_illegal($heading.$message)) {}
      else if ($notValid=longest_word($message)) {}
      else
      {
        ads_active_check_add($c, $num_ads, $active, $status, $p, $affid, $db);

        $id_ad = get_available_ad_id($affid, 'targeted', $db);
        $db->Query("INSERT INTO ad_targeted VALUES('$id_ad','$affid','$heading','$message','$url','$cat_str','$active',NOW(),NOW())");
        if (! $id_ad)
          $id_ad = $db->GetLastID();
        else
          remove_available_ad_id($affid, $id_ad, 'targeted', $db);

        if ($p) $db->Query("UPDATE ad_purchased SET id_ad='$id_ad' WHERE id='$active' AND affid='$affid' LIMIT 1");
        $notValid = 'Successfully added your Targeted AD.';
        $mode = 'show';
      }
    }
  }

  if ($mode == 'edit')
  {
    $add_url = '';

    $id = trim($id);

    if (! @is_numeric($id))
      $notValid = 'ERROR: Invalid id parameter found.';
    else if (! $db->Query("SELECT heading, message, url, categories, active FROM ad_targeted WHERE affid='$affid' AND id='$id' LIMIT 1"))
    {
      $notvalid = 'ERROR: This Targeted AD does not belong to you.';
      $mode = 'show';
    }
    else
    {
      if ($submitted != 'save') // load from mysql
      {
        list($heading, $message, $url, $cat_str, $active) = $db->FetchRow();
        $prev_active = $active;
      }
      else
      {
        $heading = substr(strip_tags(trim($heading)), 0, $ta_max_head_chars);
        $message = substr(strip_tags(trim($message)), 0, $ta_max_mess_chars);
        $url     = trim($url);
        $active  = trim($active);

        if ($notValid=valid_url($url)) {}
        else if ($notValid=ad_content_illegal($heading.$message)) {}
        else if ($notValid=longest_word($message)) {}
        else
        {
          ads_active_check_edit($c, $id, $num_ads, $active, $prev_active, $status, $notValid, $affid, $db);

          $cat_str = build_cat_str($cat);

          $db->Query("UPDATE ad_targeted SET heading='$heading', message='$message', url='$url', categories='$cat_str', active='$active', datemodified=NOW() WHERE id='$id' LIMIT 1");
          $notValid .= 'Successfully updated your Targeted AD.';
        }
      }
    }

    $cats = build_cat_table($cat_str, $db);
  }

  if ($mode == 'delete')
  {
    $notValid = ads_delete($c, $id, $affid, $status, $db);
    $mode = 'show';
  }

  if ($mode == 'show')
  {
    $preview = '
    <table align="center" border="0" cellpadding="2" cellspacing="0">
    <tr><td align="center" colspan="2">
    <font size="1"><b>Targeted AD(s) Shown Below:</b></font>
    </td></tr>
    ';

    if ($db->Query("SELECT id, heading, message, url, active FROM ad_targeted WHERE affid='$affid' ORDER BY id"))
    {
      $i = 0;
      while (list($id, $heading, $message, $url, $active) = $db->FetchRow())
      {
        if ($i % 2 == 0) $head = '<tr valign="top"><td>'; else $head = '<td>';
        if ($i % 2 == 0) $tail = '</td>'; else $tail = '</td></tr>';

        $style = ads_get_style($active);

        $preview .= $head.'
        <div class="targeted"'.$style.'>
        <a href="'.$url.'" target="_blank" class="targeted_links">'.stripslashes(htmlentities($heading)).'</a>
        <br />
        '.stripslashes(htmlentities($message)).'
        </div>
        <center>
        <a href="?c=targetedads&mode=edit&id='.$id.'">Edit</a> |
        <a href="javascript:void(0)" onClick="javascript:if(confirm(\'Are you sure you want to delete?\'))location.href=\'?c=targetedads&mode=delete&id='.$id.'\'">Delete</a>
        </center>
        '.$tail.'
        ';

        $i++;
      }
    }
    else
      $preview .= '<tr><td align="center" colspan="2"><b>None Created.</b></td></tr>';

    $preview .= '
    </table>
    ';

    $preview .= '<hr />'.create_ads_browser($affid, $db);

    list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_ta, $affid, $db);
  }

  $adform = $active_radios = '';
  if ($mode == 'add' OR $mode == 'edit')
  {
    list($active_radios, $p_title) = ads_active_radios($status, $active, $p);

    $adform = '
    <center><b>'.ucfirst($mode).' a '.$p_title.'Targeted AD</b></center>
    <form name="spotlightad" action="?c=targetedads" onsubmit="javascript:submitOnce();" method="POST">
    <b>AD Heading:</b>
    <br />
    <input type="text" name="heading" value="'.stripslashes(htmlentities($heading)).'" size="25" maxlength="'.$ta_max_head_chars.'" onFocus="focus_heading=true" onBlur="focus_heading=false" />
    <br />
    <input type="text" name="counter_heading" size="2" readonly /> Remaining Characters
    <br /><br />
    <b>AD Message:</b>
    <br />
    <input type="text" name="message" value="'.stripslashes(htmlentities($message)).'" size="60" maxlength="'.$ta_max_mess_chars.'" onFocus="focus_message=true" onBlur="focus_message=false" />
    <br />
    <input type="text" name="counter_message" size="2" readonly /> Remaining Characters
    <br /><br />
    <b>AD URL/Link:</b>
    <br />
    <input type="text" name="url" value="'.$url.'" size="60" maxlength="255" />
    <br />
    <center><h2>Categories</h2></center>
    '.$cats.'
    <center>
      '.$active_radios.'
      <hr />
      <input id="submit" type="submit" value="'.ucfirst($mode).' Targeted AD" />
      <br /><br />
      <b>Note:</b> Pages/Links designed to break out of browser frames,<br />preventing Member Credit Earning, will be deleted and banned.
    </center>

    <input type="hidden" name="id" value="'.$id.'" />
    <input type="hidden" name="mode" value="'.$mode.'" />
    <input type="hidden" name="prev_active" value="'.$prev_active.'" />
    <input type="hidden" name="p" value="'.$p.'" />
    <input type="hidden" name="c" value="targetedads" />
    <input type="hidden" name="submitted" value="save" />
    </form>
    ';
  }

  $help = '
  <center><a href="javascript:Toggle(\'help\')">-- Click to Toggle - How Targeted ADs Work --</a></center>
  <div id="help" class="helparea">
  Targeted ADs are formatted just like SpotLight ADs except you can choose which Category your AD will belong
  to. Members having at least one matching Category, set from their Profile, will see your Targeted AD.
  Targeted ADs have an advantage in that they appear on every page of the
  Members Area on the Left Panel and like the same states, targets more interested prospects.
  Additionally, these ADs appear in Distributed ADs which others have placed on their own Websites.
  '.$help_borders.'
  </div>
  ';

  notValid($notValid);

  $purchased_count = '';
  if ($num_purchased_ads) $purchased_count = "<br />$num_purchased_ads_created of $num_purchased_ads Purchased ADs created.\n";

  $standard_count = $num_ads.' of '.$allowed_ta.' created.';

  $main_content = '
  '.$downgrade_warning.'
  <center>
    <h3>Targeted ADs - '.$standard_count.'<br /></h3>
    '.$help.'
    '.$purchased_count.'
    <br />
  </center>
  '.$notValid.'
  '.$add_url.'
  '.$adform.'
  '.$preview.'
  ';
}
else if ($c == 'bannerads')
{
  session_write_close();

  $allowed_modes = array('add','edit','delete','show');
  if (! in_array($mode, $allowed_modes)) $mode = 'show';

  list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_ba, $affid, $db);

  if ($mode == 'add' AND ($status == 1 OR $num_purchased_ads))
  {
    $add_url = '';

    if ($notValid=ads_max($c, $allowed_ba, $num_ads, $num_purchased_ads_created, $num_purchased_ads, $p))
      $mode = 'show';
    else if ($submitted == 'save')
    {
      $url    = trim($url);
      $active = trim($active);

      if ($notValid=valid_url($url)) {}
      else
      {
        list($upload_check, $rand_banner_name) = check_uploaded_image('uploadedfile');

        if (strstr($upload_check, 'ERROR:'))
          $notValid = $upload_check;
        else
        {
          ads_active_check_add($c, $num_ads, $active, $status, $p, $affid, $db);

          $id_ad = get_available_ad_id($affid, 'banner', $db);
          $db->Query("INSERT INTO ad_banners (id,       affid,   image,              url,   active, datemodified, datecreated)
                                       VALUES('$id_ad','$affid','$rand_banner_name','$url','$active',NOW(),NOW())");
          if (! $id_ad)
            $id_ad = $db->GetLastID();
          else
            remove_available_ad_id($affid, $id_ad, 'banner', $db);

          if ($p) $db->Query("UPDATE ad_purchased SET id_ad='$id_ad' WHERE id='$active' AND affid='$affid' LIMIT 1");
          $notValid = 'Successfully uploaded your Banner.';
          $mode = 'show';
        }
      }
    }
  }

  if ($mode == 'edit')
  {
    $add_url = '';

    $id = trim($id);

    if (! @is_numeric($id))
      $notValid = 'ERROR: Invalid id parameter found.';
    else if (! $db->Query("SELECT url, image, active FROM ad_banners WHERE affid='$affid' AND id='$id' LIMIT 1"))
    {
      $notValid = 'ERROR: This Banner AD does not belong to you.';
      $mode = 'show';
    }
    else
    {
      if ($submitted != 'save') // load from mysql
      {
        list($url, $image, $active) = $db->FetchRow();
        $prev_active = $active;
      }
      else
      {
        $url     = trim($url);
        $image   = trim($curr_img);
        $active  = trim($active);

        list(, , $img_preview, $width, $height, $filesize) = load_image($image, $img_pos, 1);
        if ($img_preview) $img_preview = '<br /><br /><b>Current Banner:</b> <i>'.$width.' x '.$height.'</i> of <i>'.$filesize.'</i> KiloBytes<br /><br />'.$img_preview.'<br /><input type="checkbox" name="deleteimage" value="1" />&nbsp;Delete Image<br />';

        if ($notValid=valid_url($url)) {}
        else
        {
          if ($deleteimage)
          {
            $db->Query("SELECT image FROM ad_banners WHERE affid='$affid' AND id='$id' LIMIT 1");
            list($del_img) = $db->FetchRow();
            if (@is_file("$upload_path/$del_img")) @unlink("$upload_path/$del_img");
            $notValid = 'Successfully deleted Image.<br />';
          }
          else
          {
            list($notValid, $image) = check_uploaded_image('uploadedfile', 'banner', $curr_img);

            if (! stristr($notValid, 'Keeping your previous') AND ! stristr($notValid, 'ERROR:'))
            {
              // delete old image
              $db->Query("SELECT image FROM ad_banners WHERE affid='$affid' AND id='$id' LIMIT 1");
              list($del_img) = $db->FetchRow();
              if (@is_file("$upload_path/$del_img")) @unlink("$upload_path/$del_img");
            }
          }

          list(, , $img_preview, $width, $height, $filesize) = load_image($image, $img_pos, 1);

          if ($img_preview) $img_preview = '<br /><br /><b>Current Banner:</b> <i>'.$width.' x '.$height.'</i> of <i>'.$filesize.'</i> KiloBytes<br /><br />'.$img_preview.'<br /><input type="checkbox" name="deleteimage" value="1" />&nbsp;Delete Image<br />';

          ads_active_check_edit($c, $id, $num_ads, $active, $prev_active, $status, $notValid, $affid, $db);

          $db->Query("UPDATE ad_banners SET url='$url', image='$image', active='$active', datemodified=NOW() WHERE affid='$affid' AND id='$id' LIMIT 1");
          $notValid .= 'Successfully updated your Banner AD.';
        }
      }
    }
  }

  if ($mode == 'delete')
  {
    $notValid = ads_delete($c, $id, $affid, $status, $db);
    $mode = 'show';
  }

  if ($mode == 'show')
  {
    $preview = '
    <center><h2>Banner AD(s) Shown Below:</h2>
    ';

    if ($db->Query("SELECT id, image, url, active FROM ad_banners WHERE affid='$affid' ORDER BY id"))
    {
      while (list($id, $image, $url, $active) = $db->FetchRow())
      {
        $style = ads_get_style($active);

        $preview .= '
        <div class="banner"'.$style.'>
        <a href="'.$url.'" target="_blank">
          <img src="http://freeadplanet.com/_signs/'.$image.'" width="468" height="60" border="0" />
        </a>
        </div>
        <a href="?c=bannerads&mode=edit&id='.$id.'">Edit</a> |
        <a href="javascript:void(0)" onClick="javascript:if(confirm(\'Are you sure you want to delete?\'))location.href=\'?c=bannerads&mode=delete&id='.$id.'\'">Delete</a>
        <br /><br />
        ';
      }
    }
    else
      $preview .= '<b>None Created.</b>';

    $preview .= '
    </center>
    ';

    $preview .= create_ads_browser($affid, $db);

    list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_ba, $affid, $db);
  }

  $adform = $active_radios = '';
  if ($mode == 'add' OR $mode == 'edit')
  {
    list($active_radios, $p_title) = ads_active_radios($status, $active, $p);

    $adform = '
    <center><b>'.ucfirst($mode).' a '.$p_title.'Banner AD</b></center>
    <form name="uploadbanner" action="?c=bannerads" enctype="multipart/form-data" onsubmit="javascript:submitOnce();" method="POST">

    <b>Website visited when clicked:</b>
    <br />
    <input type="text" name="url" value="'.$url.'" size="50" maxlength="255" />
    <br /><br />
    <b>Banner Upload:</b><br /><i>Max Dimensions: 468 x 60<br />Max File Size: 50 k</i>
    <br />
    <input type="file" name="uploadedfile" size="50" />
    '.$img_preview.'
    <center>
    '.$active_radios.'
    <br /><hr />
    <input id="submit" type="submit" value="'.ucfirst($mode).' Banner AD" />
    <br /><br />
    <b>Note:</b> Pages/Links designed to break out of browser frames,<br />preventing Member Credit Earning, will be deleted and banned.
    </center>

    <input type="hidden" name="curr_img" value="'.$image.'" />
    <input type="hidden" name="id" value="'.$id.'" />
    <input type="hidden" name="mode" value="'.$mode.'" />
    <input type="hidden" name="prev_active" value="'.$prev_active.'" />
    <input type="hidden" name="p" value="'.$p.'" />
    <input type="hidden" name="c" value="bannerads" />
    <input type="hidden" name="submitted" value="save" />
    </form>
    ';
  }

  $help = '
  <center><a href="javascript:Toggle(\'help\')">-- How Banner ADs Work --</a></center>
  <div id="help" class="helparea">
  Banner ADs of standard size are assigned more web space due to their size. Banners can
  be made to be colorful, eye catching and even animated, such as a .gif file. Banners will
  appear at the very top and bottom of every page in the Members and Public Access. Keep in
  mind that Banners will be <i>stretched</i> to standard banner size if uploaded as a smaller
  sized banner.
  '.$help_borders.'
  </div>
  ';

  notValid($notValid);

  $purchased_count = '';
  if ($num_purchased_ads) $purchased_count = "<br />$num_purchased_ads_created of $num_purchased_ads Purchased ADs created.\n";

  $standard_count = $num_ads.' of '.$allowed_ba.' Standard ADs created.';

  if ($status == 0 AND ! $num_purchased_ads)
  {
    $main_content = '
    <center>
      <h3>Banner ADs</h3>
      <a href="?c=upgrade" class="url_upgrade">Upgrade to Pro today!</a>
      <br /><br />
      '.$help_benefits.'
    </center>
    ';
  }
  else
  {
    if ($status == 0) $standard_count = '<div class="distributed"><center>Pro Members get '.$bb_max_ads_pro.' of these ADs with membership.<br /><a href="?c=upgrade" class="url_upgrade">Upgrade to Pro today!</a></center></div>';

    $main_content = '
    '.$downgrade_warning.'
    <center>
      <h3>Banner ADs<br /></h3>
      '.$help.'
      <br />
      '.$standard_count.'
      '.$purchased_count.'
      <br /><br />
    </center>
    '.$notValid.'
    '.$add_url.'
    '.$adform.'
    '.$preview.'
    ';
  }
}
else if ($c == 'exitads')
{
  session_write_close();

  $allowed_modes = array('add','delete','edit','show');
  if (! in_array($mode, $allowed_modes)) $mode = 'show';

  list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_ea, $affid, $db);

  if ($mode == 'add' AND ($status == 1 OR $num_purchased_ads))
  {
    $add_url = '';

    if ($notValid=ads_max($c, $allowed_ea, $num_ads, $num_purchased_ads_created, $num_purchased_ads, $p))
      $mode = 'show';
    else if ($submitted == 'save')
    {
      $url    = trim($url);
      $type   = trim($type);
      $active = trim($active);

      if ($notValid=valid_url($url)) {}
      else
      {
        ads_active_check_add($c, $num_ads, $active, $status, $p, $affid, $db);

        $id_ad = get_available_ad_id($affid, 'exit', $db);
        $db->Query("INSERT INTO ad_exits VALUES('$id_ad','$affid','$url','$type','$active',NOW(),NOW())");
        if (! $id_ad)
          $id_ad = $db->GetLastID();
        else
          remove_available_ad_id($affid, $id_ad, 'exit', $db);

        if ($p) $db->Query("UPDATE ad_purchased SET id_ad='$id_ad' WHERE id='$active' AND affid='$affid' LIMIT 1");
        $notValid = 'Successfully added your Exit AD.';
        $mode = 'show';
      }
    }
  }

  if ($mode == 'edit')
  {
    $add_url = '';

    $id = trim($id);

    if (! @is_numeric($id))
      $notValid = 'ERROR: Invalid id parameter found.';
    else if (! $db->Query("SELECT url, type, active FROM ad_exits WHERE affid='$affid' AND id='$id' LIMIT 1"))
    {
      $notvalid = 'ERROR: This Exit AD does not belong to you.';
      $mode = 'show';
    }
    else
    {
      if ($submitted != 'save') // load from mysql
      {
        list($url, $type, $active) = $db->FetchRow();
        $prev_active = $active;
      }
      else
      {
        $url    = trim($url);
        $type   = trim($type);
        $active = trim($active);

        if ($notValid=valid_url($url)) {}
        else
        {
          ads_active_check_edit($c, $id, $num_ads, $active, $prev_active, $status, $notValid, $affid, $db);

          $db->Query("UPDATE ad_exits SET url='$url', type='$type', active='$active', datemodified=NOW() WHERE id='$id' LIMIT 1");
          $notValid = 'Successfully updated your Exit AD.';
        }
      }
    }
  }

  if ($mode == 'delete')
  {
    $notValid = ads_delete($c, $id, $affid, $status, $db);
    $mode = 'show';
  }

  if($mode == 'show')
  {
    $preview = '
    <center><h2>Exit AD(s) Shown Below:</h2>
    ';

    if ($db->Query("SELECT id, url, type, active FROM ad_exits WHERE affid='$affid' ORDER BY id"))
    {
      while (list($id, $url, $type, $active) = $db->FetchRow())
      {
        if ($type == 'logout')  $type_of_exit_ad = 'After Logging Out';
        else if ($type == 'mailout') $type_of_exit_ad = 'After Mailing Out';
        else
          exit('FATAL ERROR: Exit AD type unknown.');

        $style = ads_get_style($active);

        $preview .= '
        <div class="exitad"'.$style.'>
        <b>Type: <font color="blue">'.$type_of_exit_ad.'</font></b>
        <br />
        <input type="text" value="'.$url.'" size="40" readonly />
        <br />
        <!-- <a href="javascript:void(0)" onclick="javascript:location.href=\''.$url.'\'">Click to Test</a> | -->
        <a href="?c=exitads&mode=edit&id='.$id.'">Edit</a> |
        <a href="javascript:void(0)" onClick="javascript:if(confirm(\'Are you sure you want to delete?\'))location.href=\'?c=exitads&mode=delete&id='.$id.'\'">Delete</a>
        </div>
        <br />
        ';
      }
    }
    else
      $preview .= '<b>None Created.</b>';

    $preview .= '
    </center>
    ';

    $preview .= create_ads_browser($affid, $db);

    list($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url) = ads_get_num_url($c, $allowed_ea, $affid, $db);
  }

  $adform = $active_radios = '';
  if ($mode == 'add' OR $mode == 'edit')
  {
    list($active_radios, $p_title) = ads_active_radios($status, $active, $p);

    $is_checked1 = $is_checked2 = '';
    if ($type == 'logout' OR $type == '')
      $is_checked1 = 'CHECKED ';
    else if ($type == 'mailout')
      $is_checked2 = 'CHECKED ';
    else
      exit('FATAL ERROR: Exit AD type unknown.');

    $adform = '
    <center><b>'.ucfirst($mode).' a '.$p_title.'Exit AD</b></center>
    <form name="exitad" action="?c=exitads" onsubmit="javascript:submitOnce();" method="POST">
    <b>Exit AD Type:</b>
    <br /><br />
    <input type="radio" name="type" value="logout" '.$is_checked1.'/> After Logging Out
    <input type="radio" name="type" value="mailout" '.$is_checked2.'/> After Mailing Out
    <br /><br />
    <b>Website to Visit:</b>
    <br />
    <input type="text" name="url" value="'.$url.'" size="50" maxlength="255" />
    '.$active_radios.'
    <br /><hr />
    <center>
    <input id="submit" type="submit" value="'.ucfirst($mode).' Exit AD" />
    <br /><br />
    <b>Note:</b> Pages/Links designed to break out of browser frames,<br />preventing Member Credit Earning, will be deleted and banned.
    </center>

    <input type="hidden" name="id" value="'.$id.'" />
    <input type="hidden" name="mode" value="'.$mode.'" />
    <input type="hidden" name="prev_active" value="'.$prev_active.'" />
    <input type="hidden" name="p" value="'.$p.'" />
    <input type="hidden" name="c" value="exitads" />
    <input type="hidden" name="submitted" value="save" />
    </form>
    ';
  }

  $help = '
  <center><a href="javascript:Toggle(\'help\')">-- How Exit ADs Work --</a></center>
  <div id="help" class="helparea">
  Exit ADs are simply Links to your Website accessed when a Member does one of two things.
  A Member Logs Out and is taken to your Exit AD. A Member is taken to your Exit AD after
  a successful Mail Out. It is always a good idea to Log out for security reasons as this
  will destroy any session and cookie data related to your Membership. This applies to
  any Website on the Internet for which you Log into with Username and Password.
  '.$help_borders.'
  </div>
  ';

  notValid($notValid);

  $purchased_count = '';
  if ($num_purchased_ads) $purchased_count = "<br />$num_purchased_ads_created of $num_purchased_ads Purchased ADs created.\n";

  $standard_count = $num_ads.' of '.$allowed_bb.' Standard ADs created.';

  if ($status == 0 AND ! $num_purchased_ads)
  {
    $main_content = '
    <center>
      <h3>Exit ADs</h3>
      <a href="?c=upgrade" class="url_upgrade">Upgrade to Pro today!</a>
      <br /><br />
      '.$help_benefits.'
    </center>
    ';
  }
  else
  {
    if ($status== 0) $standard_count = '<div class="distributed"><center>Pro Members get '.$ea_max_ads_pro.' of these ADs with membership.<br /><a href="?c=upgrade" class="url_upgrade">Upgrade to Pro today!</a></center></div>';

    $main_content = '
    '.$downgrade_warning.'
    <center>
      <h3>Exit ADs<br /></h3>
      '.$help.'
      <br />
      '.$standard_count.'
      '.$purchased_count.'
      <br /><br />
    </center>
    '.$notValid.'
    '.$add_url.'
    '.$adform.'
    '.$preview.'
    ';
  }
}

if ($c == 'logout')
  logout_session(get_ads('', 'exitad_logout', 1, $db, $affid), $affid, $db);
else
{
  @session_write_close();

  // placed at end to reflect changes made by user ads
  $ta_free = get_targeted_ads(0, $user_categories, $db, $affid);
  $ta_pro  = get_targeted_ads(1, $user_categories, $db, $affid);

  $bb = get_ads('', 'billboard', 5, $db, $affid);
  $sl = get_ads('', 'spotlight', 5, $db, $affid);
  $ba = get_ads('', 'banner', 2, $db, $affid);
}

$bannerad_top =  $bannerad_bot = '';
if ($ba[0])
{
  if ($affid == $ba[0]['affid']) $url = $ba[0]['url'];
  else $url = 'http://' . $domain_name . '.com/earn.php?' . make_url($affid, $ba[0]['id'], $db, 4);
  $bannerad_top = '<a href="' . $url . '" target="_blank"><img src="http://' . $domain_name . '.com/_signs/'.$ba[0]['image'] . '" width="468" height="60" border="0" /></a>';
}
if ($ba[1])
{
  if ($affid == $ba[1]['affid']) $url = $ba[1]['url'];
  else $url = 'http://' . $domain_name . '.com/earn.php?' . make_url($affid, $ba[1]['id'], $db, 4);
  $bannerad_bot = '<a href="' . $url . '" target="_blank"><img src="http://' . $domain_name . '.com/_signs/'.$ba[1]['image'] . '" width="468" height="60" border="0" /></a>';
}

?>