<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');

define('TEST_MODE', 0);

$domain_name = 'freeadplanet';

$headers = "From: Free AD Planet <do_not_reply@freeadplanet.com>";

$show_email_confirmer = 0;

$earn_time_secs = 10;

$num_ad_broken = 3;

$master_affid = '11187448';

$banned_urls = array('freeadplanet.com',
                     'morecash123.com',
                     'youscoundrelyou.com',
                     'burkeshire-reports.com',
                     'joyfulnumerology.com',
                     'howtodiscovertheworld.com',
                     'gotraverustravel.com',
                     'sitesell.com',
                     'listbandit.com',
                     'newlightbiz.com',
                     'getyourspotnow.com',
                     'blastoffnetwork.com');

$illegal_content = array(' sex', 'adult site', 'porn ');

$upload_path = '/home/nulled/www/freeadplanet.com/_signs';
$keys_dir    = '/home/nulled/www/freeadplanet.com/keys';

$turing_key_timeout   = 60;
$targeted_num_display = 5;

$bb_max_head_chars = 25;
$bb_max_mess_chars = 125;

$ta_max_head_chars = 25;
$ta_max_mess_chars = 140;

$sl_max_head_chars = 25;
$sl_max_mess_chars = 140;

// mailer
$ml_max_head_chars = 70;
$ml_max_mess_chars = 5000;

// num ads allowed
$bb_max_ads_free = 0;
$ta_max_ads_free = 1;
$sl_max_ads_free = 1;
$ba_max_ads_free = 0;
$ea_max_ads_free = 0;

$bb_max_ads_pro = 1;
$ta_max_ads_pro = 2;
$sl_max_ads_pro = 2;
$ba_max_ads_pro = 1;
$ea_max_ads_pro = 1;

// purchased ads
$price_targeted  = 10;
$price_spotlight = 10;
$price_billboard = 12;
$price_banner    = 12;
$price_exit      = 8;
$price_soload    = 59;
$price_credits   = 10;

$price_subscription = 20;

$credits_targeted  = 500;
$credits_spotlight = 500;
$credits_billboard = 600;
$credits_banner    = 600;
$credits_exit      = 400;
$credits_soload    = 3500;

$max_credits_transferable = 3000;

$credits_earned_free = 1;
$credits_earned_pro  = 2;

$ref_credits_earned_free = 50;
$ref_credits_earned_pro  = 100;

$start_credits       = 10;
$start_lockedcredits = 0;

// % percentages earned
$commissions_subscription_free = 20;
$commissions_subscription_pro  = 30;

$commissions_purchases_free = 10;
$commissions_purchases_pro  = 20;

// days
$commissions_days_mature = 30;

$days_grace_period     = 21;
$days_purchases_expire = 30;

$numericDays = array('Mon' => 1, 'Tue' => 2, 'Wed' => 3, 'Thu' => 4, 'Fri' => 5, 'Sat' => 6, 'Sun' => 7);

$quotaDailyRequirement = array();
$quotaDailyRequirement[0] = 4;
$quotaDailyRequirement[1] = 2;
$quotaDailyRequirement[2] = 2;

// quota weekly
$quotaRequirement = array();
$quotaRequirement[0] = $quotaDailyRequirement[0] * 7;
$quotaRequirement[1] = $quotaDailyRequirement[1] * 7;
$quotaRequirement[2] = $quotaDailyRequirement[2] * 7;

$creds_earn_soload = 8; // times whatever would normally be earned
$creds_earn_regmail = 4; // times whatever would normally be earned
$creds_earn_free = 1;
$creds_earn_pro = 2;
$creds_earn_missed_week = 8;
$creds_deducted_daily = 20;
$creds_deducted_ad_view_free = 2;
$creds_deducted_ad_view_pro = 4;

$earn_buffer_time = 5; // secs to delay, to prevent ad view rushing

$porn_warning = '<b>Warning</b>: Any ADs containing any reference to Porn, Scams or Anti-Religious/Government material, will result in your Account being
deleted <i>without refund</i> <u>and</u> your IP Address added to our black list. We are strict on this policy, because 99% of our members
are extra sensitive to such subjects. We thank you for your cooperation.';

// have to redefine all border properties for some reason
$style_same_owner = 'border: lightblue; border-style: solid; border-top-width: 1px; border-bottom-width: 1px; border-left-width: 1px; border-right-width: 1px;';

$help_borders = '<br /><br /><hr /><br />
<i>Red Borders</i> indicate the AD as staying visible even after Open Credits run out. <b>Only PRO members
may set a Red Border AD.</b>
<br /><br />
<i>Dotted Borders</i> indicate a Purchased AD and will display even after Open Credits run out.
<br /><br />
<i>Solid Black Borders</i> indicate the AD as disappearing from member view when Open Credits run out.
';

$help_benefits = '
<center><a href="javascript:Toggle(\'help\')">-- Click to Toggle to Compare Benefits --</a></center>
<div id="help" class="helparea">
<center><h2>Compare the benefits of Free vs PRO.</h2></center>
<hr />
<table border="0" align="center" cellpadding="4" cellspacing="2">
  <tr>
    <td align="center"><b><u>Benefits</u></b></td>
    <td bgcolor="lightgreen" align="center"><b>Free</b></td>
    <td bgcolor="lightgreen" align="center"><b>PRO</b></td>
  </tr>

  <tr>
    <td align="right">Transfer Credits from your planetxmail.com Accounts</td>
    <td bgcolor="lightgrey" align="center">No</td>
    <td bgcolor="lightgrey" align="center"><b>Yes</b></td>
  </tr>

  <tr>
    <td align="right">Each AD View, Credits Earned</td>
    <td bgcolor="lightgrey" align="center">'.$credits_earned_free.'</td>
    <td bgcolor="lightgrey" align="center"><b>'.$credits_earned_pro.'</b></td>
  </tr>

  <tr>
    <td align="right">Daily AD View Quota</td>
    <td bgcolor="lightgrey" align="center">'.$quotaDailyRequirement[0].'</td>
    <td bgcolor="lightgrey" align="center"><b>'.$quotaDailyRequirement[1].'</b></td>
  </tr>

  <tr>
    <td align="right">Each Referral, Credits Earned</td>
    <td bgcolor="lightgrey" align="center">'.$ref_credits_earned_free.'</td>
    <td bgcolor="lightgrey" align="center"><b>'.$ref_credits_earned_pro.'</b></td>
  </tr>

  <tr>
    <td align="right">* SpotLight ADs</td>
    <td bgcolor="lightgrey" align="center">'.$sl_max_ads_free.'</td>
    <td bgcolor="lightgrey" align="center"><b>'.$sl_max_ads_pro.'</b></td>
  </tr>

  <tr>
    <td align="right">* Targeted ADs</td>
    <td bgcolor="lightgrey" align="center">'.$ta_max_ads_free.'</td>
    <td bgcolor="lightgrey" align="center"><b>'.$ta_max_ads_pro.'</b></td>
  </tr>

  <tr>
    <td align="right">* BillBoard ADs</td>
    <td bgcolor="lightgrey" align="center">'.$bb_max_ads_free.'</td>
    <td bgcolor="lightgrey" align="center"><b>'.$bb_max_ads_pro.'</b></td>
  </tr>

  <tr>
    <td align="right">* Banner ADs</td>
    <td bgcolor="lightgrey" align="center">'.$ba_max_ads_free.'</td>
    <td bgcolor="lightgrey" align="center"><b>'.$ba_max_ads_pro.'</b></td>
  </tr>

  <tr>
    <td align="right">* Exit ADs</td>
    <td bgcolor="lightgrey" align="center">'.$ea_max_ads_free.'</td>
    <td bgcolor="lightgrey" align="center"><b>'.$ea_max_ads_pro.'</b></td>
  </tr>

  <tr>
    <td align="right">Commission Earned Per Downline Subscription</td>
    <td bgcolor="lightgrey" align="center">'.$commissions_subscription_free.'%</td>
    <td bgcolor="lightgrey" align="center"><b>'.$commissions_subscription_pro.'%</b></td>
  </tr>

  <tr>
    <td align="right">Commission Earned Per Downline <i>Buy AD</i> Purchases</td>
    <td bgcolor="lightgrey" align="center">'.$commissions_purchases_free.'%</td>
    <td bgcolor="lightgrey" align="center"><b>'.$commissions_purchases_pro.'%</b></td>
  </tr>

  <tr>
    <td colspan="3" align="left">
    <hr />
    <font size="+1"><b>*</b></font> <u>Professional members</u> additionally get to set one AD per AD type to be displayed regardless if credits in the account run to 0 (zero)! They are identifiable by their Red Border.
    This is a good thing in case you run out of Open Credits, while away or too busy to Earn Credits during crunch times in your life.
    <br /><br />
    By contrast, <b>all</b> <u>Free member</u> ADs <i>will become hidden from other members</i> when credits in the Free account run to 0 (zero). With the exception of
    Purchased ADs, which are displayed until they expire.
    <br /><br />
    '.$porn_warning.'
    </td>
  </tr>

</table>
</div>
';

$help_commissions = '
  <center><a href="javascript:Toggle(\'help\')">-- Click to Toggle and View Commissions Explained --</a></center>
  <div id="help" class="helparea">
  <b>Free members earn...</b>
  <ul>
    <li>'.$commissions_subscription_free.'% commission on all Pro members you sponsor.</li>
    <li>'.$commissions_purchases_free.'% commission when your downline purchases from <a href="./?c=buyads">Buy ADs</a></li>
  </ul>

  <b>Pro members earn...</b>
  <ul>
    <li>'.$commissions_subscription_pro.'% commission on all Pro members you sponsor.
    <li>'.$commissions_purchases_pro.'% commission when your downline purchases from <a href="./?c=buyads">Buy ADs</a></li>
  </ul>

  <b>Note:</b> Maturity for each commission transaction will be '.$commissions_days_mature.' days from date of sale.
  This helps reduce fraud and dealing with refunds.
  Once the commission has Matured, it will be paid out to you.
  <br /><br />
  You <b>must</b> have an
  <a href="https://secure.payza.com/?VwPhQPpbqEhle2hgofIZ%2fA%3d%3d" target="_blank">Payza</a>
  account and assigned properly in
  <a href="?c=profile">Your Profile</a>. Payza is the only merchant that we use to do commission payouts. Signing up for
  Payza is free and you will notice it is a Paypal alternative, which works and looks almost identical to Paypal. However,
  Payza is Small Biz friendly, unlike Paypal. We are also trying to promote Alertpay, because Paypal in recent years has
  frozen accounts without warning.
  <br /><br />
    '.$porn_warning.'
  </div>
  ';

$help_downgrade = '
  <center><a href="javascript:Toggle(\'notice\')">-- Click to Toggle and View the results of a Down Grade --</a></center>
  <div id="notice" class="helparea">
  <b>If Down Graded...</b>
  <br /><br />
  Will not be able to Transfer Credits from planetxmail.com Safelist Accounts to your Free AD Planet Account.
  <br /><br />
  Any Commissions Earned <i>during</i> the Grace Period will be <i>permanently</i> held at the Free Member rate.
  <br /><br />
  Any ADs created that exceed Free Member count rates will be deleted.
  This includes; Spotlight, BillBoard, Targeted, Banner and Exit ADs.
  <br /><br />
  <i>Purchased ADs and current Credit counts <u>will not</u> be effected by the Down Grade.</i>
  <br /><br />
  You may continue as Free Member or Upgrade to Pro again at any time.
  <br /><br />
  You upgraded once before so, we do not have to tell you the awesome benefits you lose if you get Down Graded!
  <br /><br />
  <b>If <a href="?c=renew">Renew</a> <i>before</i> the Down Grade...</b>
  <br /><br />
  Any Commissions Earned during the Grace Period will be re-calculated at the
  Pro Member rate! Not to mention you keep your Pro Account just as it was.
  <br /><br />
  <center><a href="?c=renew">Click Here to Renew your Pro Membership</a></center>
  </div>
  ';

function reltoabs($text, $base)
{
  if (substr($base, -1, 1) != '/') $base .= '/';

  // <link href=
  // $pattern = "/<link([^>]*) href=\"(?!http|ftp|https)([^\"]*)\"/i";
  // $replace = "<link\${1} href=\"" . $base . "\${2}\"";
  $pattern = "/href=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "href=\"" . $base . "\${1}\"";
  $text = preg_replace($pattern, $replace, $text);

  $pattern = "/background=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "background=\"" . $base . "\${1}\"";
  $text = preg_replace($pattern, $replace, $text);

  // <table background=
  $pattern = "/<table([^>]*) background=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "<table\${1} background=\"" . $base . "\${2}\"";
  $text = preg_replace($pattern, $replace, $text);

  // <td background=
  $pattern = "/<td([^>]*) background=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "<td\${1} background=\"" . $base . "\${2}\"";
  $text = preg_replace($pattern, $replace, $text);

  // <img src=
  $pattern = "/<img([^>]*) src=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "<img\${1} src=\"" . $base . "\${2}\"";
  $text = preg_replace($pattern, $replace, $text);

  // <form action=
  $pattern = "/<form([^>]*) action=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "<form\${1} action=\"" . $base . "\${2}\"";
  $text = preg_replace($pattern, $replace, $text);

  // <applet code=
  $pattern = "/<applet([^>]*) code=\"(?!http|ftp|https)([^\"]*)\"/i";
  $replace = "<applet\${1} code=\"" . $base . "\${2}\"";
  $text = preg_replace($pattern, $replace, $text);

  return $text;
}

function valid_mail_content($heading, $message)
{
  if (stristr($heading, 'received') OR
      stristr($heading, 'notification') OR
      stristr($heading, 'of payment') OR
      stristr($heading, 'recieved'))
    return 'ERROR: Subject contains deceptive content.<br />Nothing was mailed.';

  return '';
}

function buy_ad_with_credits($credit_cost, &$credits, &$lockedcredits)
{
  $_credits       = $credits;
  $_lockedcredits = $lockedcredits;

  $_lockedcredits = $_lockedcredits - $credit_cost;

  if ($_lockedcredits < 0)
  {
    $_credits = $_credits - abs($_lockedcredits);
    $_lockedcredits = 0;
  }

  if ($_credits < 0 OR ! $credit_cost)
    return 'ERROR: You do not have enough credits.';
  else
  {
    $credits       = $_credits;
    $lockedcredits = $_lockedcredits;
    return '';
  }
}

function longest_word($str)
{
  $words = explode(' ', $str);
  if (! count($words)) return '';
  foreach ($words as $word) if (strlen($word) > 20) return 'ERROR: A word in your message exceeds the allowed length.';
}

function make_hash($str) // do not change tied to fap/tap
{
  return substr(sha1('BL8H87dhqKd7' . $str . 'hsDhsjASJDf7'), 0, 5);
}

function make_seed($length) // do not change tied to fap/tap
{
  $key = '';
  $pattern = '1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  for ($i=0; $i < $length; $i++) $key .= $pattern{mt_rand(0, 35)};
  return $key;
}

function make_url($affid, $urlID, $db, $type=0) // do not change tied to fap/tap
{
  // make sure urlID is valid
  if ($urlID == '')
    return 0;
  if (($type == 0 OR $type == 9) AND ! $db->Query("SELECT id FROM urls WHERE id='$urlID' LIMIT 1"))
    return 0;

  $i = 0;
  while (true)
  {
    $i++;
    if ($i > 5000)
    {
      @mail('elitescripts2000@yahoo.com', 'make_url() error fap', 'ERROR: Unable to make_url() fap');
      exit("FATAL ERROR: Unable to make_url() Admins have been contacted");
    }

    $seed = make_seed(10);
    $url  = $seed.$affid.$urlID.$type;
    $hash = make_hash($url);

    if (! $db->Query("SELECT url FROM earnedurls WHERE url='$url' LIMIT 1"))
      return 'u=' . mixup_link($url) . "&h=$hash";
  }
}

function convert_url($affid, $url, $urlaffid, $db, $type=0) // do not change tied to fap/tap
{
  global $domain_name, $master_affid;

  if ($affid == $urlaffid AND $master_affid != $affid) return $url;

  // generate credit url if affid
  if (is_numeric($affid) AND $url AND is_numeric($urlaffid))
  {
    // check affid is valid
    if ($db->Query("SELECT affid FROM users WHERE affid='$affid' LIMIT 1"))
    {
      // check url has urlID
      if ($db->Query("SELECT id FROM urls WHERE url='$url' AND affid='$urlaffid' LIMIT 1"))
        list($urlID) = $db->FetchRow();
      else
      {
        $db->Query("INSERT INTO urls VALUES('','$urlaffid','$url')");
        $urlID = $db->GetLastID();
      }

      if ($url_code=make_url($affid, $urlID, $db, $type))
        $new_url = 'http://' . $domain_name . '.com/earn.php?' . $url_code;
      else
        $new_url = $url;
    }
    else
      $new_url = $url;
  }
  else
    $new_url = $url;

  return $new_url;
}

function load_image($image, $img_pos, $banner=0)
{
  global $upload_path;

  $img_form1 = $img_form2 = $img_preview = '';
  if (@is_file("$upload_path/$image"))
  {
    list($width, $height, $type, $attr) = getimagesize("$upload_path/$image");
    if ($filesize=filesize("$upload_path/$image"))
      $filesize = number_format($filesize / 1024, 2, '.', '');

    if (! $img_pos)
    {
      $radio1 = 'CHECKED ';
      $radio2 = '';
      $float = 'floatLeft';
    }
    else
    {
      $radio1 = '';
      $radio2 = 'CHECKED ';
      $float = 'floatRight';
    }

    if ($banner) $float = '';

    $img_form1 = '<b>Current&nbsp;Image:</b><br /><br /><center><img src="http://freeadplanet.com/_signs/'.$image.'" '.$attr.' border="0" /></center>';
    $img_form2 = '<b>Position&nbsp;Image:</b><br /><input type="radio" name="img_pos" value="0" '.$radio1.'/>&nbsp;Left&nbsp;<input type="radio" name="img_pos" value="1" '.$radio2.'/>&nbsp;Right<br /><br /><input type="checkbox" name="deleteimage" value="1" />&nbsp;Delete Image';
    $img_preview = '<img src="http://freeadplanet.com/_signs/'.$image.'" '.$attr.' border="0" class="'.$float.'" />';
  }

  return array($img_form1, $img_form2, $img_preview, $width, $height, $filesize);
}

function is_purchased_ad($active)
{
  if ($active > 1) return 1;
  return 0;
}

function check_uploaded_image($img, $type='banner', $curr_img='')
{
  global $upload_path;

  // echo '<pre>'.print_r($_FILES, 1).'</pre>';

  // if current image and no file was uploaded, then keep current
  if ($curr_img AND $_FILES[$img]['error']) return array('Keeping your previous Image.<br />', $curr_img);
  if ($type == 'banner' AND $curr_img == '' AND $_FILES[$img]['error'] == 4) return array('ERROR: Image is missing.<br />', $curr_img);
  if ($_FILES[$img]['error'] == 4) return array('No image was uploaded.<br />', $curr_img);

  if ($type == 'banner')
  {
    $size   = 51200;
    $width  = 468;
    $height = 60;
  }
  else if ($type == 'billboard')
  {
    $size   = 10240;
    $width  = 50;
    $height = 50;
  }
  else
    exit('FATAL ERROR: in check_uploaded_image() type invalid.');

  if ($_FILES[$img]['error'])             $notValid = 'ERROR: Unable to upload file.';
  else if ($_FILES[$img]['size'] > $size) $notValid = 'ERROR: File size too large. '.$size.' bytes Max.';
  else if ($_FILES[$img]['size'] < 1)     $notValid = 'ERROR: File size can not be 0.';
  else
  {
    list($_width, $_height, $_type) = getimagesize($_FILES[$img]['tmp_name']);

    if ($_width > $width)        $notValid = 'ERROR: Image width exceeds '.$width.' pixels.';
    else if ($_height > $height) $notValid = 'ERROR: Image height exceeds '.$height.' pixels.';
    else if ($_type != 1 AND $_type != 2 AND $_type != 3) $notValid = 'ERROR: Image must be jpg, gif or png format.';
    else
    {
      if ($_type == 1)      $extention = 'gif';
      else if ($_type == 2) $extention = 'jpg';
      else if ($_type == 3) $extention = 'png';

      // rand image name
      $i = 0;
      while (1)
      {
        $rand_image_name = rand();
        if (! @file_exists("$upload_path/$rand_image_name.$extention")) break;
        if ($i > 5000) exit('FATAL ERROR: Unable to make rand image name.');
        $i++;
      }

      if (@move_uploaded_file($_FILES[$img]['tmp_name'], "$upload_path/$rand_image_name.$extention"))
        $notValid = 'Successfully uploaded your image.';
      else
      {
        // on failed upload delete current image as well if exists
        if ($curr_img AND @is_file("$upload_path/$curr_img")) @unlink("$upload_path/$curr_img");
        $curr_img = '';
        $notValid = 'ERROR: move_uploaded_file() failed.';
      }
    }
  }

  if (! stristr($notValid, 'ERROR:'))
    return array($notValid.'<br />', "$rand_image_name.$extention");
  else
    return array($notValid.'<br />', $curr_img);
}

function build_cat_str($cat)
{
  $cat_str = '';
  if (@is_array($cat))
  {
    foreach ($cat as $acat) if (@is_numeric($acat)) $cat_str .= $acat.',';
    if ($cat_str) $cat_str = substr($cat_str, 0, strlen($cat_str)-1);
  }

  return $cat_str;
}

function build_cat_table($cat_str, $db)
{
  // categories - build the table
  $categories  = explode(',', $cat_str);
  $_categories = array();
  $db->Query("SELECT id, name FROM categories WHERE 1 ORDER BY id");
  while (list($_id, $name) = $db->FetchRow()) $_categories[$_id] = $name;

  $cats = '<table>';
  $i = 0;
  foreach ($_categories as $_id => $name)
  {
    $is_checked = '';
    if (is_array($categories)) if (@in_array($_id, $categories)) $is_checked = 'CHECKED ';

    if ($i % 2 == 0)
      $cats .= '<tr><td width="5" nowrap><input type="checkbox" name="cat[]" value="'.$_id.'" '.$is_checked.'/></td><td align="left" nowrap>'.$name.'</td>'."\n";
    else
      $cats .= '<td width="5" nowrap><input type="checkbox" name="cat[]" value="'.$_id.'" '.$is_checked.'/></td><td align="left" nowrap>'.$name.'</td></tr>'."\n";

    $i++;
  }
  $cats .= '</table>';

  return $cats;
}

function logout_session($why, $affid='', $db='')
{
  if (@is_array($why))
  {
    $db->Query("SELECT adstoday FROM users WHERE affid='$affid' LIMIT 1");
    list($adstoday) = $db->FetchRow();
    if ($adstoday != '') $adstoday = unserialize($adstoday);
    else $adstoday = array();

    $id       = $why[0]['id'];
    $urlaffid = $why[0]['affid'];

    // do not display ads already clicked today
    if (is_array($adstoday[$urlaffid]['exit']) AND @in_array($id, $adstoday[$urlaffid]['exit']))
      $url = 'http://freeadplanet.com';
    else if ($url_code=make_url($affid, $id, $db, 5))
      $url = 'http://freeadplanet.com/earn.php?'.$url_code.'&b=1';
    else
      $url = 'http://freeadplanet.com';

    // exit($url_code);
  }
  else if (@is_string($why))
  {
    if ($affid == 1)
      $url = 'http://freeadplanet.com/admin/?c=login&notValid='.urlencode($why);
    else
      $url = 'http://freeadplanet.com/?c=memberexit&why='.urlencode($why);
  }
  else
    $url = 'http://freeadplanet.com';

  $_SESSION = array();
  if (ini_get('session.use_cookies')) {
    $p = session_get_cookie_params();
    setcookie(session_name(), '', time() - 42000, $p['path'], $p['domain'], $p['secure'], $p['httponly']);
  }
  session_destroy();

  header('Location: '.$url);
  exit;
}

function notValid(&$notValid)
{
  $round_top   = '<b class="rtop"><b class="r1"></b> <b class="r2"></b> <b class="r3"></b> <b class="r4"></b></b>';
  $round_bot   = '<b class="rbottom"><b class="r4"></b> <b class="r3"></b> <b class="r2"></b> <b class="r1"></b></b>';
  $round_topOK = '<b class="rtopOK"><b class="r1"></b> <b class="r2"></b> <b class="r3"></b> <b class="r4"></b></b>';
  $round_botOK = '<b class="rbottomOK"><b class="r4"></b> <b class="r3"></b> <b class="r2"></b> <b class="r1"></b></b>';

  if ($notValid)
  {
    if (strstr($notValid, 'ERROR:'))
      $notValid = '<div id="notvalid_err">'.$round_top.$notValid.$round_bot.'</div><br />'."\n";
    else
      $notValid = '<div id="notvalid_ok">'.$round_topOK.$notValid.$round_botOK.'</div><br />'."\n";
  }
}

function get_user($affid, $db)
{
  if (! $db->Query("SELECT username, pass, fname, lname, email, paypal, alertpay, egold, sponsor, categories, emailalerts, verified, credits, lockedcredits, datelastbilled FROM users WHERE affid='$affid' LIMIT 1"))
    exit('FATAL ERROR: Contact Support. CODE: 1');
  return $db->FetchArray();
}

function get_ad_breakers($db)
{
  // get ad breakers
  $ad_breakers = array();
  $db->Query("SELECT ad_type, ad_id FROM ad_breakers WHERE 1");
  while (list($ad_type, $ad_id) = $db->FetchRow())
  {
    //echo "$id, $clickerID, $ownerID, $ad_type, $ad_id, $dateinserted\n";

    if ($ad_breakers[$ad_type][$ad_id])
      $ad_breakers[$ad_type][$ad_id]++;
    else
      $ad_breakers[$ad_type][$ad_id] = 1;
  }

  return $ad_breakers;
}

function get_targeted_ads($status, $user_categories, $db, $affid='')
{
  global $targeted_num_display, $num_ad_broken;

  //return array();

  if ($affid)
  {
    $db->Query("SELECT adstoday FROM users WHERE affid='$affid' LIMIT 1");
    list($adstoday) = $db->FetchRow();
    if ($adstoday != '') $adstoday = unserialize($adstoday);
    else $adstoday = array();

    // $where = "affid != '$affid'";
    $where = '1';
  }
  else
    $where = '1';

  // echo '<pre>'.print_r($adstoday, 1).'</pre>';

  $ad_breakers = get_ad_breakers($db);

  $i = 0;
  $ads = array();
  if ($db->Query("SELECT id, affid, heading, message, url, categories, active FROM ad_targeted WHERE $where ORDER BY MD5(RAND()) LIMIT 2000"))
  {
    $result = $db->result;
    while(list($_id, $_affid, $_heading, $_message, $_url, $_categories, $_active) = mysqli_fetch_row($result))
    {
      // do not display ad breakers
      // targeted, 8078, 10 (type, ad_ID, num_times_broke_frame)
      if (isset($ad_breakers['targeted'][$_id]) AND $ad_breakers['targeted'][$_id] > $num_ad_broken)
      {
        //mail('elitescripts2000@yahoo.com', "type=targeted, ad_id=$_id, num=".$ad_breakers['targeted'][$_id], "content");
        continue;
      }

      if (@is_numeric($status))
      {
        // do not display ads already clicked today
        if (is_array($adstoday[$_affid]['targeted'])) if (in_array($_id, $adstoday[$_affid]['targeted'])) continue;

        if (! $db->Query("SELECT status, credits FROM users WHERE status='$status' AND affid='$_affid' LIMIT 1"))
          continue;
        list($_status, $credits) = $db->FetchRow();

        // active 0 so check if user has credits, if not do not display ad
        if ($_active == 0 AND $credits == 0) continue;
      }

      $_categories = explode(',', $_categories);

      // check to see if current user cat match any cat for this AD
      // is user_categories = '' then skip the check, used in distributed ads
      $found = 0;
      if ($user_categories == '')
        $found = 1;
      else
      {
        foreach ($user_categories as $_cat)
        {
          if (in_array($_cat, $_categories))
          {
            $found = 1;
            break;
          }
        }
      }
      if (! $found) continue;

      $ads[$i]['id']      = $_id;
      $ads[$i]['heading'] = $_heading;
      $ads[$i]['message'] = $_message;
      $ads[$i]['url']     = $_url;
      $ads[$i]['affid']   = $_affid;
      $i++;

      if ($i >= $targeted_num_display) break;
    }
  }
  else
    $ads = array();

  return $ads;
}

function get_ads($status, $type, $limit, $db, $affid='')
{
  global $num_ad_broken;

  $where = '';

  if ($type == 'spotlight')
  {
    $table  = 'ad_spotlights';
    $fields = 'affid, active, id, heading, message, url';
  }
  else if ($type == 'billboard')
  {
    $table  = 'ad_billboards';
    $fields = 'affid, active, id, heading, message, url, image, img_pos';
  }
  else if ($type == 'banner')
  {
    $table  = 'ad_banners';
    $fields = 'affid, active, id, image, url';
  }
  else if ($type == 'exitad_logout')
  {
    $table  = 'ad_exits';
    $fields = 'affid, active, id, url';
    $where  = "type='logout' AND ";
  }
  else if ($type == 'exitad_mailout')
  {
    $table  = 'ad_exits';
    $fields = 'affid, active, id, url';
    $where  = "type='mailout' AND ";
  }
  else
    exit('FATAL ERROR: type='.$type.' unknown in get_ads()');

  if ($affid)
  {
    $db->Query("SELECT adstoday FROM users WHERE affid='$affid' LIMIT 1");
    list($adstoday) = $db->FetchRow();
    if ($adstoday != '') $adstoday = unserialize($adstoday);
    else $adstoday = array();

    // $where .= "affid != '$affid'";
    $where = '1';
  }
  else
    $where = '1';

  $ad_breakers = get_ad_breakers($db);

  $i = 0;
  $ads = array();
  if ($db->Query("SELECT $fields FROM $table WHERE $where ORDER BY MD5(RAND()) LIMIT 2000"))
  {
    $result = $db->result;
    while(list($a, $b, $c, $d, $e, $f, $g, $h) = mysqli_fetch_row($result))
    {
      // do not display ad breakers
      // spotlight, 8078, 10 (type, ad_ID, num_times_broke_frame)
      $_type = (strstr($type, 'exitad')) ? 'exit' : $type;
      if (isset($ad_breakers[$_type][$c]) AND $ad_breakers[$_type][$c] > $num_ad_broken)
      {
        //mail('elitescripts2000@yahoo.com', "type=$_type, ad_id=$c, num={$ad_breakers[$_type][$c]}", "content");
        continue;
      }

      // do not display ads already clicked today
      if (is_array($adstoday[$a][$type]) AND @in_array($c, $adstoday[$a][$type])) continue;

      if (! $db->Query("SELECT status, credits FROM users WHERE affid='$a'")) continue;
      list($_status, $credits) = $db->FetchRow();

      // convert to 1 for grace period members
      if ($_status == 2) $_status = 1;

      // if status is '' ignore else only allow ads for specified status
      if (@is_numeric($status) AND $_status != $status) continue;

      // b = active 0 so check if user has credits, if not do not display ad
      if ($b == 0 AND $credits == 0) continue;

      // echo "type=$type _status=$_status status=$status credits=$credits b=$b<br />\n";

      if ($type == 'spotlight')
      {
        // echo "a=$a b=$b c=$c f=$f<br />\n";

        $ads[$i]['affid']   = $a;
        $ads[$i]['active']  = $b;
        $ads[$i]['id']      = $c;
        $ads[$i]['heading'] = $d;
        $ads[$i]['message'] = $e;
        $ads[$i]['url']     = $f;
      }
      else if ($type == 'billboard')
      {
        $ads[$i]['affid']   = $a;
        $ads[$i]['active']  = $b;
        $ads[$i]['id']      = $c;
        $ads[$i]['heading'] = $d;
        $ads[$i]['message'] = $e;
        $ads[$i]['url']     = $f;
        $ads[$i]['image']   = $g;
        if ($h) $ads[$i]['img_pos'] = 'floatRight'; else $ads[$i]['img_pos'] = 'floatLeft';
      }
      else if ($type == 'banner')
      {
        $ads[$i]['affid']   = $a;
        $ads[$i]['active']  = $b;
        $ads[$i]['id']      = $c;
        $ads[$i]['image']   = $d;
        $ads[$i]['url']     = $e;
      }
      else if ($type == 'exitad_logout' OR $type == 'exitad_mailout')
      {
        $ads[$i]['affid']   = $a;
        $ads[$i]['active']  = $b;
        $ads[$i]['id']      = $c;
        $ads[$i]['url']     = $d;
      }

      $i++;
      if ($i >= $limit) break;
    }
  }

  return $ads;
}

function display_ad($type, $ads, $db, $affid='', $index='all')
{
  global $upload_path, $style_same_owner;

  // 0 reg mail
  // 1 spotlight
  // 2 billboard
  // 3 targeted
  // 4 banner
  // 5 exit
  // 9 soload

  $ad_data = '';

  $da_style = 'style="text-align:left;font-family:verdana,arial;font-size:11px;background:white;border:1px solid lightgrey;padding:2px;width:195px;"';

  if ($type == 'spotlight')
  {
   for ($i=0; $i < count($ads); $i++)
    {
      // display only a specific index, used in distributed ads
      if (@is_numeric($index) AND $index != $i) continue;

      if (@mysqli_ping($db->link)) // if db = '' then skip make_url, used in distributed ads
      {
        if ($url_code=make_url($affid, $ads[$i]['id'], $db, 1))
          $url = 'http://freeadplanet.com/earn.php?'.$url_code;
        else
          $url = $ads[$i]['url'];

        $style = 'class="targeted"';
        $br = '<br />';
      }
      else if ($db == 'public')
      {
        $br = '<br />';
        $style = 'class="targeted"';
        $url = $ads[$i]['url'];
      }
      else
      {
        $style = $da_style;
        $br = '';
        $url = $ads[$i]['url'];
      }

      $ad_data .= '
      <div '.$style.'>
        <a href="'.$url.'" target="_blank" class="spotlight_links">'.$ads[$i]['heading'].'</a>
        <br />
        '.$ads[$i]['message'].'
      </div>
      '.$br.'
      ';
    }
  }
  else if ($type == 'billboard')
  {
    for ($i=0; $i < count($ads); $i++)
    {
      // display only a specific index, used in distributed ads
      if (@is_numeric($index) AND $index != $i) continue;

      $img = '';
      if (@is_file("$upload_path/".$ads[$i]['image']))
      {
        list(,,,$attr) = getimagesize("$upload_path/".$ads[$i]['image']);
        $img = '<img src="http://freeadplanet.com/_signs/'.$ads[$i]['image'].'" '.$attr.' border="0" class="'.$ads[$i]['img_pos'].'" />';
      }

      if (@mysqli_ping($db->link)) // if db = '' then skip make_url, used in distributed ads
      {
        if ($url_code=make_url($affid, $ads[$i]['id'], $db, 2))
          $url = 'http://freeadplanet.com/earn.php?'.$url_code;
        else
          $url = $ads[$i]['url'];

        $style = 'class="targeted"';
        $br = '<br />';
      }
      else if ($db == 'public')
      {
        $br = '<br />';
        $style = 'class="targeted"';
        $url = $ads[$i]['url'];
      }
      else
      {
        $style = $da_style;
        $br = '';
        $url = $ads[$i]['url'];
      }

      $ad_data .= '
      <div '.$style.'>
        '.$img.'
        <a href="'.$url.'" target="_blank" class="billboard_links">'.$ads[$i]['heading'].'</a>
        <br />
        '.$ads[$i]['message'].'
      </div>
      '.$br.'
      ';
    }
  }
  else if ($type == 'targeted')
  {
    for ($i=0; $i < count($ads); $i++)
    {
      // display only a specific index, used in distributed ads
      if (@is_numeric($index) AND $index != $i) continue;

     if ($affid == $ads[$i]['affid']) // do not allow the ad owner to earn credits off their own ads
      {
        $style = 'style="'.$style_same_owner.'" class="targeted"';
        $br = '<br />';
        $url = $ads[$i]['url'];
      }
      else if (@mysqli_ping($db->link)) // if db = '' then skip make_url, used in distributed ads
      {
        if ($url_code=make_url($affid, $ads[$i]['id'], $db, 3))
          $url = 'http://freeadplanet.com/earn.php?'.$url_code;
        else
          $url = $ads[$i]['url'];

        $style = 'class="targeted"';
        $br = '<br />';
      }
      else if ($db == 'public')
      {
        $br = '<br />';
        $style = 'class="targeted"';
        $url = $ads[$i]['url'];
      }
      else
      {
        $style = $da_style;
        $br = '';
        $url = $ads[$i]['url'];
      }

      $ad_data .= '
      <div '.$style.'>
        <a href="'.$url.'" target="_blank" class="targeted_links">'.$ads[$i]['heading'].'</a>
        <br />
        '.$ads[$i]['message'].'
      </div>
      '.$br.'
      ';
    }
  }
  else
    exit('FATAL ERROR: type='.$type.' unknown in display_ad()');

  return $ad_data;
}

function process_fees($mop, $amount)
{
  if ($mop == 'clickbank')
  {
    $amount -= 1;
    $fees = $amount * .075;
    $amount -= $fees;
    $profits = number_format($amount, 2, '.', '');
  }
  else if ($mop == 'twocheckout')
  {
    $amount -= 0.45;
    $fees = $amount * .055;
    $amount -= $fees;
    $profits = number_format($amount, 2, '.', '');
  }
  else if ($mop == 'payza')
  {
    $amount -= 0.59;
    $fees = $amount * .039;
    $amount -= $fees;
    $profits = number_format($amount, 2, '.', '');
  }
  else
    $profits = number_format($amount, 2, '.', '');

  return $profits;
}

function get_type_cost($type)
{
  global $price_subscription, $price_targeted, $price_spotlight, $price_billboard, $price_banner, $price_exit, $price_soload, $price_credits;
  global $credits_targeted, $credits_spotlight, $credits_billboard, $credits_banner, $credits_exit, $credits_soload;

  switch ($type)
  {
    case 'subscription':
      $price = $price_subscription;
      $credits = '';
      break;
    case 'targeted':
      $price = $price_targeted;
      $credits = $credits_targeted;
      break;
    case 'spotlight':
      $price = $price_spotlight;
      $credits = $credits_spotlight;
      break;
    case 'billboard':
      $price = $price_billboard;
      $credits = $credits_billboard;
      break;
    case 'banner':
      $price = $price_banner;
      $credits = $credits_banner;
      break;
    case 'exit':
      $price = $price_exit;
      $credits = $credits_exit;
      break;
    case 'soload':
      $price = $price_soload;
      $credits = $credits_soload;
      break;
    case 'credits':
      $price = $price_credits;
      $credits = '';
      break;
    default:
      exit("ERROR: get_type_cost() Unable to determine type=$type");
  }

  return array($price, $credits);
}

function process_sponsor($sponsor, $profits, $mop, $receipt, $type, $db)
{
  global $commissions_subscription_free, $commissions_subscription_pro, $commissions_purchases_free, $commissions_purchases_pro;

  $commissions = 0;
  $id_pxm = '';

  list($price) = get_type_cost($type);

  if (@is_numeric($sponsor))
  {
    if ($db->Query("SELECT fname, lname, email, status FROM users WHERE affid='$sponsor' LIMIT 1"))
    {
      list($fname, $lname, $email, $status) = $db->FetchRow();

      if ($type == 'subscription')
      {
        if ($status == 0 OR $status == 2) $commissions = number_format(($price * ($commissions_subscription_free / 100)), 2, '.', '');
        else                              $commissions = number_format(($price * ($commissions_subscription_pro / 100)), 2, '.', '');
      }
      else
      {
        if ($status == 0 OR $status == 2) $commissions = number_format(($price * ($commissions_purchases_free / 100)), 2, '.', '');
        else                              $commissions = number_format(($price * ($commissions_purchases_pro / 100)), 2, '.', '');
      }

      $db->SelectDB('pxm');
      $db->Query("INSERT INTO transactions VALUES('','fap','$profits','$mop','$receipt',NOW())");
      $id_pxm = $db->GetLastID();

      $commissions = 0; // do not issue out commissions...

      if ($commissions)
      {
        $db->SelectDB('fap');
        $db->Query("INSERT INTO commissions (id,  sponsor,    amount,         type,    status,    id_pxm,   dateofsale)
                                      VALUES('', '$sponsor', '$commissions', '$type', '$status', '$id_pxm', NOW())");
      }

      $notValid = 'Your sponsor has been credited as well.<br />';
    }
  }

  if ($id_pxm == '')
  {
    $db->SelectDB("pxm");
    $db->Query("INSERT INTO transactions VALUES('','fap','$profits','$mop','$receipt',NOW())");
  }

  return $notValid;
}

function process_order($db, $affid, $type, $mop, $receipt, $headers, $amount)
{
  global $commissions_subscription_free, $commissions_subscription_pro, $commissions_purchases_free, $commissions_purchases_pro;

  $date = date('F j, Y');

  // check and reject duplicate receipts
  if ($db->Query("SELECT id FROM receipts WHERE mop='$mop' AND receipt='$receipt' LIMIT 1"))
  {
    list($id) = $db->FetchRow();
    @mail("elitescripts2000@yahoo.com", "Free AD Planet - DUP RECEIPT", "fap.receipts.id=$id affid=$affid amount=$amount mop=$mop receipt=$receipt type=$type", $headers);
    return "ERROR: This Transaction has already been processed.";
  }

  list($price) = get_type_cost($type);
  $profits = process_fees($mop, $amount);
  $fees = $amount - $profits;
  if ($amount < ($price-$fees-1))
  {
    @mail("elitescripts2000@yahoo.com", "Free AD Planet - PRICE FRAUD", "affid=$affid amount=$amount mop=$mop receipt=$receipt type=$type", $headers);
    return "ERROR: Invalid transaction.";
  }

  if (! @is_numeric($affid))
  {
    @mail("elitescripts2000@yahoo.com", "Free AD Planet - affid not numeric", "affid=$affid amount=$amount mop=$mop receipt=$receipt type=$type", $headers);
    return "ERROR: Invalid affid. Transaction unable to complete.";
  }

  if (! $db->Query("SELECT username, pass, fname, lname, email, sponsor, status FROM users WHERE affid='$affid' LIMIT 1"))
  {
    @mail("elitescripts2000@yahoo.com", "Free AD Planet - affid not found", "affid=$affid amount=$amount mop=$mop receipt=$receipt", $headers);
    return "ERROR: Invalid transaction!<br />Unable to find affid type=$type in process_order()";
  }
  list($username, $pass, $fname, $lname, $email, $sponsor, $status) = $db->FetchRow();

  if ($type == 'subscription')
  {
    if ($status == 1)
      return 'ERROR: Account is already status=1. It should be 0 or 2.';
    else if ($status == 0) // if 0 status then set datelastbilled=NOW() else they are just renewing
      $db->Query("UPDATE users SET status='1', datelastbilled=NOW() WHERE affid='$affid' LIMIT 1");
    else // should be status=2
    {
      // convert all grace period commissions back to pro levels
      $db->Query("SELECT id, type FROM commissions WHERE status='2' AND sponsor='$affid' LIMIT 1");
      $result = $db->result;
      while (list($_id, $_type) = $db->FetchRow())
      {
        list($_price) = get_type_cost($_type);

        if ($_type == 'subscription')
          $new_commissions = number_format(($_price * ($commissions_subscription_pro / 100)), 2, '.', '');
        else
          $new_commissions = number_format(($_price * ($commissions_purchases_pro / 100)), 2, '.', '');

        $db->Query("UPDATE commissions SET amount='$new_commissions', status='1' WHERE id='$_id' LIMIT 1");
      }

      $db->Query("UPDATE users SET status='1' WHERE affid='$affid' LIMIT 1");
    }

    $db->Query("INSERT INTO receipts VALUES('','$mop','$receipt',NOW())");

    $subj = 'Free AD Planet - Order Receipt';
    $mess = "Hello $fname $lname,\n\nYour account has been updated.\n\nYou may log in as a Professional Member.\n\nUsername: $username\n\nMethod of Payment: $mop\nReceipt: $receipt\nAmount: \$$amount\n\nThank You,\nhttp://freeadplanet.com Staff";

    @mail($email, $subj, $mess, $headers);
    @mail('elitescripts2000@yahoo.com', $subj, $mess, $headers);

    $notValid = process_sponsor($sponsor, $profits, $mop, $receipt, $type, $db);

    $notValid .= 'Successfully updated your Account Subscription as Paid.';
  }
  else if ($type == 'targeted' OR $type == 'spotlight' OR $type == 'billboard' OR $type == 'banner' OR $type == 'exit' OR $type == 'soload' OR $type == 'credits')
  {
    if ($type == 'credits')
    {
      $db->Query("UPDATE users SET lockedcredits=lockedcredits+500 WHERE affid='$affid' LIMIT 1");
      $notValid = 'Successfully Purchased 500 Credits.<br />';
    }
    else
    {
      $db->Query("INSERT INTO ad_purchased VALUES('','$affid','$type','0',NOW())");
      $notValid = 'Successfully Purchased a '.ucfirst($type).' AD.<br />';
    }

    $subj = 'Free AD Planet - Ordered: '.ucfirst($type).' Receipt: '.$receipt;
    $mess = "Hello $fname $lname,

You ordered: ".ucfirst($type)." AD
Processor: $mop
Receipt: $receipt
Amount: \$$amount

Questions about your Order?
http://freeadplanet.com/openticket.php

------------------------ About Your Order ------------------------

If you ordered a Solo AD, goto the Mailer Section and you will see
a checkbox labeled Solo AD which you need to mark as checked before
submitting the mail out.

If you ordered a SpotLight, Targeted, BillBoard, Banner or Exit AD,
goto that ADs section in the members area and Create the AD and save
or upload the banner etc. These types of ADs can be Edited and recreated
for up to 30 days from date of purchase. When they expire the system
simply deletes them. Also, purchased ADs of these types will always be
visible to Members, even if your Open Credits reach 0.

If you ordered Credits, you will see them as added to your Locked
Credits Account. (Not Open Credits).

Thank You,
http://freeadplanet.com staff
";

    @mail($email, $subj, $mess, $headers);
    @mail('elitescripts2000@yahoo.com', $subj, $mess, $headers);

    $db->Query("INSERT INTO receipts VALUES('','$mop','$receipt',NOW())");

    $notValid .= process_sponsor($sponsor, $profits, $mop, $receipt, $type, $db);
  }
  else
    $notValid = "ERROR: type=$type unknown. Unable to process order in process_order().";

  return $notValid;
}

function ads_get_num_url($type, $allowed_ads, $affid, $db)
{
  if ($type == 'spotlightads')
  {
    $table = 'ad_spotlights';
    $ad_type = 'spotlight';
    $title_reg = 'Click to Create your SpotLight AD';
    $title_pur = 'Click to Create your Purchased SpotLight AD';
  }
  else if ($type == 'billboardads')
  {
    $table = 'ad_billboards';
    $ad_type = 'billboard';
    $title_reg = 'Click to Create your BillBoard AD';
    $title_pur = 'Click to Create your Purchased BillBoard AD';
  }
  else if ($type == 'targetedads')
  {
    $table = 'ad_targeted';
    $ad_type = 'targeted';
    $title_reg = 'Click to Create your Targeted AD';
    $title_pur = 'Click to Create your Purchased Targeted AD';
  }
  else if ($type == 'bannerads')
  {
    $table = 'ad_banners';
    $ad_type = 'banner';
    $title_reg = 'Click to Create your Banner AD';
    $title_pur = 'Click to Create your Purchased Banner AD';
  }
  else if ($type == 'exitads')
  {
    $table = 'ad_exits';
    $ad_type = 'exit';
    $title_reg = 'Click to Create your Exit AD';
    $title_pur = 'Click to Create your Purchased Exit AD';
  }
  else
    exit('FATAL ERROR: type unknown in ads_get_num_url()');

  $num_ads                   = $db->Query("SELECT id FROM $table WHERE active < 2 AND affid='$affid'");
  $num_purchased_ads         = $db->Query("SELECT id FROM ad_purchased WHERE type='$ad_type' AND affid='$affid'");
  $num_purchased_ads_created = $db->Query("SELECT id FROM ad_purchased WHERE id_ad > 0 AND type='$ad_type' AND affid='$affid'");

  $add_url = '';
  if ($num_ads < $allowed_ads)
    $add_url = '<center><input type="submit" onclick="javascript:location.href=\'?c='.$type.'&mode=add\'" value="'.$title_reg.'" /></center>';

  if ($num_purchased_ads_created < $num_purchased_ads)
  {
    if ($add_url) $add_url .= '<br />';
    $add_url .= '<center><a href="?c='.$type.'&mode=add&p=1"><blink>--- '.$title_pur.' ---</blink></a></center>';
  }

  return array($num_ads, $num_purchased_ads, $num_purchased_ads_created, $add_url);
}

function ads_active_check_edit($type, $id, $num_ads, &$active, &$prev_active, $status, &$notValid, $affid, $db)
{
  if ($type == 'spotlightads')
    $table = 'ad_spotlights';
  else if ($type == 'billboardads')
    $table = 'ad_billboards';
  else if ($type == 'targetedads')
    $table = 'ad_targeted';
  else if ($type == 'bannerads')
    $table = 'ad_banners';
  else if ($type == 'exitads')
    $table = 'ad_exits';
  else
    exit('FATAL ERROR: type unknown in ads_active_check()');

  // check if is a purchased ad, do not allow modification of active id if it is
  $db->Query("SELECT active FROM $table WHERE affid='$affid' AND id='$id'");
  list($active_check) = $db->FetchRow();

  if (is_purchased_ad($active_check))
   $active = $active_check;
  else
  {
    if ($active) $active = 1; else $active = 0;

    if ($status)
    {
      // ensure we can only have 1 active AD per AD type
      if ($active AND $num_ads > 1)   $db->Query("UPDATE $table SET active='0' WHERE active < 2 AND affid='$affid'");
      if (! $active AND $prev_active AND $num_ads > 1)
      {
        $db->Query("UPDATE $table SET active='1' WHERE affid='$affid' AND id!='$id' LIMIT 1");
        $notValid .= 'Notice: Another AD has been set as Default instead of this one.<br />';
      }

      $prev_active = $active;

      // if only one ad created it will forcibly become default
      if ($num_ads == 1)
      {
        $active = $prev_active = 1;
        $notValid .= 'Notice: One AD is created. It was set as Default.<br />';
      }
    }
    else
      $active = 0;
  }
}

function ads_active_radios($status, $active, $p)
{
  if ($status AND ! $p AND ! is_purchased_ad($active))
  {
    $active0selected = $active1selected = '';
    if (! $active) $active0selected = 'CHECKED ';
    if ($active)   $active1selected = 'CHECKED ';

    $active_radios = '
    <hr />
    <b>Set as Default AD:</b>
    <br />
    <input type="radio" name="active" value="0" '.$active0selected.'/> No
    <input type="radio" name="active" value="1" '.$active1selected.'/> Yes
    ';
  }

  $p_title = '';
  if ($p OR is_purchased_ad($active)) $p_title = 'Purchased ';

  return array($active_radios, $p_title);
}

function ads_active_check_add($type, $num_ads, &$active, $status, $p, $affid, $db)
{
  if ($type == 'spotlightads')
  {
    $table = 'ad_spotlights';
    $ad_type = 'spotlight';
  }
  else if ($type == 'billboardads')
  {
    $table = 'ad_billboards';
    $ad_type = 'billboard';
  }
  else if ($type == 'targetedads')
  {
    $table = 'ad_targeted';
    $ad_type = 'targeted';
  }
  else if ($type == 'bannerads')
  {
    $table = 'ad_banners';
    $ad_type = 'banner';
  }
  else if ($type == 'exitads')
  {
    $table = 'ad_exits';
    $ad_type = 'exit';
  }
  else
    exit('FATAL ERROR: type unknown in ads_active_check_add()');

  if ($p)
  {
    if ($db->Query("SELECT id FROM ad_purchased WHERE id_ad='0' AND type='$ad_type' AND affid='$affid' LIMIT 1"))
      list($active) = $db->FetchRow();
    else
      exit('FATAL ERROR: No open records found table ad_purchased in ads_active_check_add()');
  }
  else
  {
    if ($active OR $num_ads == 0) $active = 1; else $active = 0;

    if ($status == 0) $active = 0;

    // ensure we can only have 1 active AD per AD type
    if ($active AND $num_ads) $db->Query("UPDATE $table SET active='0' WHERE active < 2 AND affid='$affid'");
  }
}

function ads_get_style($active)
{
  $style = '';
  if ($active == 1)                  $style = ' style="border-color: red; height: auto"';
  else if (is_purchased_ad($active)) $style = ' style="border-style: dashed; height: auto"';
  else $style = ' style="height: auto"';

  return $style;
}

function ads_delete($type, $id, $affid, $status, $db)
{
  global $upload_path;

  if ($type == 'spotlightads')
  {
    $table = 'ad_spotlights';
    $fields = 'active';
    $title = 'SpotLight';
    $_type = 'spotlight';
  }
  else if ($type == 'billboardads')
  {
    $table = 'ad_billboards';
    $fields = 'active, image';
    $title = 'BillBoard';
    $_type = 'billboard';
  }
  else if ($type == 'targetedads')
  {
    $table = 'ad_targeted';
    $fields = 'active';
    $title = 'Targeted';
    $_type = 'targeted';
  }
  else if ($type == 'bannerads')
  {
    $table = 'ad_banners';
    $fields = 'active, image';
    $title = 'Banner';
    $_type = 'banner';
  }
  else if ($type == 'exitads')
  {
    $table = 'ad_exits';
    $fields = 'active';
    $title = 'Exit';
    $_type = 'exit';
  }
  else
    exit('FATAL ERROR: type unknown in ads_delete()');

  if (! @is_numeric($id))
    $notValid = 'ERROR: Invalid id parameter found.';
  else if (! $db->Query("SELECT $fields FROM $table WHERE affid='$affid' AND id='$id' LIMIT 1"))
    $notValid = 'ERROR: This '.$title.' AD does not belong to you.';
  else
  {
    list($a, $b) = $db->FetchRow();
    if ($b)
    {
      $b = "$upload_path/$b";
      if (@is_file($b)) @unlink($b);
    }
    $db->Query("DELETE FROM $table WHERE id='$id'");
    if (is_purchased_ad($a)) $db->Query("UPDATE ad_purchased SET id_ad='0' WHERE affid='$affid' AND id='$a' LIMIT 1");
    if ($a == 1 AND $status) $db->Query("UPDATE $table SET active='1' WHERE active = 0 AND affid='$affid' LIMIT 1");
    set_available_ad_id($affid, $id, $_type, $db);
    $notValid = 'Successfully deleted a '.$title.' AD.';
  }

  return $notValid;
}

function ads_max($type, $allowed_ads, $num_ads, $num_purchased_ads_created, $num_purchased_ads, $p)
{
  if ($type == 'spotlightads')
    $title = 'SpotLight';
  else if ($type == 'billboardads')
    $title = 'BillBoard';
  else if ($type == 'targetedads')
    $title = 'Targeted';
  else if ($type == 'bannerads')
    $title = 'Banner';
  else if ($type == 'exitads')
    $title = 'Exit';
  else
    exit('FATAL ERROR: type unknown in ads_max()');

  $notValid = '';

  if (! $p AND $num_ads >= $allowed_ads)
    $notValid = 'ERROR: Allowed maximum of '.$allowed_ads.' '.$title.' AD(s).';
  else if ($p AND $num_purchased_ads_created >= $num_purchased_ads)
    $notValid = 'ERROR: Allowed maximum of '.$num_purchased_ads.' Purchased '.$title.' AD(s).';

  return $notValid;
}

function create_ads_browser($affid, $db)
{
  global $upload_path, $style_same_owner;

  $bb_free = get_ads(0, 'billboard', 6, $db, $affid);
  $bb_pro  = get_ads(1, 'billboard', 6, $db, $affid);

  $sl_free = get_ads(0, 'spotlight', 6, $db, $affid);
  $sl_pro  = get_ads(1, 'spotlight', 6, $db, $affid);

  // exit('<pre>'.print_r($bb_pro, 1).'</pre>');

  $pro_title = '';
  if (count($bb_pro) OR count($sl_pro))
    $pro_title = '<br /><br /><b><font color="red">PRO</font> Member ADs</b> - <i>SpotLight and BillBoard</i></td></tr>';

  $table = '
  <table align="center" border="0" cellpadding="2" cellspacing="0">
  <tr><td align="center" colspan="2">
  <a href=""><b>-- Click to Refresh AD Browser --</b></a>
  <br /><i>Light Blue Bordered ADs are your ADs.</i>
  <br />
  <a href="http://freeadplanet.com/openticket.php" target="_blank">Report</a> ADs that break the Earn Credits page/frame.
  '.$pro_title.'
  ';

  $range = range(0, 5);
  shuffle($range);

  $phase = 1;
  $ads_bb = $bb_pro;
  $ads_sl = $sl_pro;
  $bb_counter = $sl_counter = 0;
  for ($i=0, $counter=0; $i < 6; $i++)
  {
    $style   = '';
    $heading = '';
    $message = '';
    $url     = '';
    $image   = '';
    $img_pos = '';
    $target  = '';

    $rand_num = $range[$i];

    // billboard
    if ($rand_num > 2 AND $ads_bb[$rand_num-3])
    {
      $rand_num -= 3;

      $type = 'billboard';

      if ($ads_bb[$rand_num])
      {
        if ($affid == $ads_bb[$rand_num]['affid'])
        {
          $style = $style_same_owner;
          $url = $ads_bb[$rand_num]['url'];
        }
        else
          $url = 'http://freeadplanet.com/earn.php?'.make_url($affid, $ads_bb[$rand_num]['id'], $db, 2);

        $heading = $ads_bb[$rand_num]['heading'];
        $message = $ads_bb[$rand_num]['message'];
        $image   = $ads_bb[$rand_num]['image'];
        $img_pos = $ads_bb[$rand_num]['img_pos'];
        $target  = 'target="_blank"';
      }
      else
      {
        $style = 'border-style: none;background: white;';
        //$url = ' ';
        //$url     = 'http://freeadplanet.com/members/?c=buyads';
        //$heading = '<center>Your AD Here';
        //$message = 'Advertise using BillBoard ADs</center>';
      }
    }
    else
    {
      $type = 'spotlight';

      if ($ads_sl[$rand_num])
      {
        if ($affid == $ads_sl[$rand_num]['affid'])
        {
          $style = $style_same_owner;
          $url = $ads_sl[$rand_num]['url'];
        }
        else
          $url = 'http://freeadplanet.com/earn.php?'.make_url($affid, $ads_sl[$rand_num]['id'], $db, 1);

        $heading = $ads_sl[$rand_num]['heading'];
        $message = $ads_sl[$rand_num]['message'];
        $target  = 'target="_blank"';
      }
      else
      {
        $style = 'border-style: none;background: white;';
        //$url = ' ';
        //$url     = 'http://freeadplanet.com/members/?c=buyads';
        //$heading = '<center>Your AD Here';
        //$message = 'Advertise using SpotLight ADs</center>';
      }
    }

    if ($phase == 2) $style .= 'background: white;';

    if (strlen($url))
    {
      if ($counter % 2 == 0)
      {
        $head = '<tr valign="top"><td>';
        $tail = '</td>';
      }
      else
      {
        $head = '<td>';
        $tail = '</td></tr>';
      }

      $counter++;

      if ($type == 'billboard')
      {
        $img_preview = '';
        if (@is_file("$upload_path/$image"))
        {
          list(,,,$attr) = getimagesize("$upload_path/$image");
          if ($img_pos == '0') $float = 'floatLeft';
          else $float = 'floatRight';
          $img_preview = '<img src="http://freeadplanet.com/_signs/'.$image.'" '.$attr.' border="0" class="'.$float.'" />';
        }

        $table .= $head.'
        <div id="ad_'.$phase.'_'.$counter.'" class="billboard" style="'.$style.'">
        '.$img_preview.'
        <a href="'.$url.'" '.$target.' class="billboard_links">'.$heading.'</a>
        <br />
        '.$message.'
        </div>
        '.$tail.'
        ';
      }
      else if ($type == 'spotlight')
      {
        $table .= $head.'
        <div id="ad_'.$phase.'_'.$counter.'" class="spotlight" style="'.$style.'">
        <a href="'.$url.'" '.$target.' class="spotlight_links">'.$heading.'</a>
        <br />
        '.$message.'
        </div>
        '.$tail.'
        ';
      }
    }

    if ($i == 5 AND $phase == 1)
    {
      shuffle($range);
      $i = -1;
      $phase = 2;
      $bb_counter = $sl_counter = $counter = 0;
      $ads_bb = $bb_free;
      $ads_sl = $sl_free;

      $ad_notice = '';
      if (! count($ads_bb) AND ! count($ads_sl)) $ad_notice = '<br /><br /><b>No ADs Found of this Type.</b>';

      // if tail was not closed, close it properly here
      if (substr(trim($table), strlen($table)-5) != '</tr>') $table .= '</tr>';

      $table .= '
      <tr><td align="center" colspan="2">
      <br /><b><font color="green">Free</font> Member ADs</b> - <i>SpotLight and BillBoard</i>
      '.$ad_notice.'
      ';
    }
  }

  $table .= '
  </table>
  ';

  return $table;
}

function turing_key_create()
{
  global $keys_dir, $turing_key_timeout;

  // create image and colors
  $im    = ImageCreate(50, 25);
  $white = ImageColorAllocate($im, 255, 255, 255);
  $black = ImageColorAllocate($im, 0, 0, 0);

  // fill image
  ImageFill($im, 0, 0, $white);

  $codekey = substr(rand(), 0, 3);
  $time_proof = time() + $turing_key_timeout;
  $validate = strrev(md5(sha1(strrev($time_proof.$codekey)))).$time_proof.'S'.strlen($time_proof);

  // write string in black
  ImageTTFText($im, 20, 0, 0, 22, $black, '/home/nulled/www/planetxmail.com/mle/images/font.ttf', $codekey);

  if ($dir = @opendir($keys_dir))
  {
    while($file = readdir($dir))
    {
      if ($file != '.' AND $file != '..')
      {
        $deletetime = time() - 60;
        $modified = stat("$keys_dir/$file");
        if ($modified[9] < $deletetime)
          @unlink("$keys_dir/$file");
      }
    }
    closedir($dir);
  }

  while (1)
  {
    $keyfilename = rand().'.jpg';
    if (@file_exists("$keys_dir/$keyfilename"))
      continue;
    else
      break;
  }

  $fp = @fopen("$keys_dir/$keyfilename", 'w');
  @fclose($fp);

  // create image
  chmod("$keys_dir/$keyfilename", 0664);
  ImageJPEG($im, "$keys_dir/$keyfilename");

  return array($validate, $keyfilename);
}

function get_cryptogram($i, $all=0)
{
  $shuffles = array(
      "0" => array(0 => "H", 1 => "4", 2 => "R", 3 => "W", 4 => "5", 5 => "J", 6 => "X", 7 => "N", 8 => "M", 9 => "1", 10 => "3", 11 => "S", 12 => "T", 13 => "C", 14 => "K", 15 => "B", 16 => "E", 17 => "Y", 18 => "Q", 19 => "F", 20 => "V", 21 => "I", 22 => "2", 23 => "G", 24 => "D", 25 => "9", 26 => "U", 27 => "7", 28 => "A", 29 => "P", 30 => "0", 31 => "Z", 32 => "6", 33 => "O", 34 => "8", 35 => "L"),
      "1" => array(0 => "R", 1 => "6", 2 => "W", 3 => "H", 4 => "I", 5 => "C", 6 => "Q", 7 => "A", 8 => "L", 9 => "J", 10 => "8", 11 => "1", 12 => "F", 13 => "Y", 14 => "V", 15 => "3", 16 => "X", 17 => "D", 18 => "K", 19 => "T", 20 => "7", 21 => "U", 22 => "0", 23 => "Z", 24 => "N", 25 => "O", 26 => "P", 27 => "S", 28 => "4", 29 => "9", 30 => "2", 31 => "E", 32 => "B", 33 => "G", 34 => "M", 35 => "5"),
      "2" => array(0 => "R", 1 => "Q", 2 => "3", 3 => "L", 4 => "W", 5 => "P", 6 => "G", 7 => "S", 8 => "Y", 9 => "M", 10 => "N", 11 => "9", 12 => "H", 13 => "Z", 14 => "X", 15 => "T", 16 => "8", 17 => "2", 18 => "B", 19 => "4", 20 => "J", 21 => "E", 22 => "0", 23 => "6", 24 => "7", 25 => "C", 26 => "1", 27 => "A", 28 => "F", 29 => "V", 30 => "D", 31 => "I", 32 => "5", 33 => "U", 34 => "O", 35 => "K"),
      "3" => array(0 => "I", 1 => "9", 2 => "Z", 3 => "0", 4 => "7", 5 => "L", 6 => "6", 7 => "2", 8 => "P", 9 => "C", 10 => "J", 11 => "3", 12 => "B", 13 => "D", 14 => "4", 15 => "U", 16 => "Y", 17 => "E", 18 => "V", 19 => "W", 20 => "O", 21 => "5", 22 => "N", 23 => "8", 24 => "M", 25 => "H", 26 => "R", 27 => "1", 28 => "S", 29 => "Q", 30 => "A", 31 => "X", 32 => "F", 33 => "K", 34 => "G", 35 => "T"),
      "4" => array(0 => "A", 1 => "J", 2 => "P", 3 => "9", 4 => "T", 5 => "M", 6 => "5", 7 => "L", 8 => "Z", 9 => "Q", 10 => "E", 11 => "D", 12 => "3", 13 => "R", 14 => "V", 15 => "0", 16 => "W", 17 => "8", 18 => "I", 19 => "B", 20 => "S", 21 => "F", 22 => "H", 23 => "O", 24 => "6", 25 => "U", 26 => "Y", 27 => "G", 28 => "2", 29 => "7", 30 => "K", 31 => "1", 32 => "N", 33 => "C", 34 => "X", 35 => "4"),
      "5" => array(0 => "K", 1 => "M", 2 => "Y", 3 => "B", 4 => "L", 5 => "N", 6 => "3", 7 => "G", 8 => "D", 9 => "R", 10 => "I", 11 => "6", 12 => "X", 13 => "O", 14 => "2", 15 => "8", 16 => "1", 17 => "A", 18 => "F", 19 => "5", 20 => "H", 21 => "U", 22 => "C", 23 => "4", 24 => "W", 25 => "J", 26 => "S", 27 => "Q", 28 => "E", 29 => "P", 30 => "V", 31 => "9", 32 => "0", 33 => "7", 34 => "T", 35 => "Z"),
      "6" => array(0 => "Q", 1 => "D", 2 => "4", 3 => "L", 4 => "M", 5 => "8", 6 => "3", 7 => "B", 8 => "C", 9 => "1", 10 => "G", 11 => "Y", 12 => "U", 13 => "5", 14 => "A", 15 => "0", 16 => "V", 17 => "P", 18 => "N", 19 => "9", 20 => "H", 21 => "S", 22 => "T", 23 => "F", 24 => "J", 25 => "O", 26 => "E", 27 => "6", 28 => "X", 29 => "I", 30 => "K", 31 => "W", 32 => "Z", 33 => "R", 34 => "2", 35 => "7"),
      "7" => array(0 => "O", 1 => "T", 2 => "8", 3 => "M", 4 => "5", 5 => "I", 6 => "H", 7 => "R", 8 => "2", 9 => "K", 10 => "X", 11 => "P", 12 => "6", 13 => "N", 14 => "Q", 15 => "V", 16 => "Y", 17 => "W", 18 => "G", 19 => "A", 20 => "F", 21 => "E", 22 => "4", 23 => "1", 24 => "7", 25 => "S", 26 => "Z", 27 => "C", 28 => "B", 29 => "L", 30 => "0", 31 => "J", 32 => "9", 33 => "D", 34 => "U", 35 => "3"),
      "8" => array(0 => "1", 1 => "L", 2 => "X", 3 => "V", 4 => "P", 5 => "J", 6 => "B", 7 => "U", 8 => "9", 9 => "K", 10 => "T", 11 => "C", 12 => "I", 13 => "E", 14 => "0", 15 => "Y", 16 => "Z", 17 => "R", 18 => "G", 19 => "W", 20 => "7", 21 => "F", 22 => "8", 23 => "D", 24 => "S", 25 => "Q", 26 => "2", 27 => "3", 28 => "A", 29 => "H", 30 => "4", 31 => "N", 32 => "6", 33 => "O", 34 => "5", 35 => "M"),
      "9" => array(0 => "D", 1 => "1", 2 => "S", 3 => "V", 4 => "M", 5 => "H", 6 => "4", 7 => "0", 8 => "I", 9 => "G", 10 => "P", 11 => "Q", 12 => "K", 13 => "T", 14 => "L", 15 => "X", 16 => "A", 17 => "7", 18 => "F", 19 => "U", 20 => "R", 21 => "6", 22 => "W", 23 => "5", 24 => "O", 25 => "8", 26 => "E", 27 => "Y", 28 => "2", 29 => "N", 30 => "Z", 31 => "C", 32 => "3", 33 => "B", 34 => "9", 35 => "J"),
      "A" => array(0 => "U", 1 => "Y", 2 => "J", 3 => "B", 4 => "K", 5 => "E", 6 => "H", 7 => "5", 8 => "W", 9 => "7", 10 => "D", 11 => "T", 12 => "R", 13 => "F", 14 => "O", 15 => "L", 16 => "2", 17 => "C", 18 => "M", 19 => "I", 20 => "1", 21 => "N", 22 => "4", 23 => "9", 24 => "V", 25 => "Q", 26 => "8", 27 => "G", 28 => "6", 29 => "S", 30 => "Z", 31 => "X", 32 => "0", 33 => "A", 34 => "3", 35 => "P"),
      "B" => array(0 => "1", 1 => "K", 2 => "D", 3 => "S", 4 => "7", 5 => "6", 6 => "R", 7 => "O", 8 => "F", 9 => "8", 10 => "V", 11 => "E", 12 => "X", 13 => "0", 14 => "5", 15 => "P", 16 => "9", 17 => "3", 18 => "U", 19 => "I", 20 => "B", 21 => "2", 22 => "J", 23 => "Y", 24 => "Q", 25 => "G", 26 => "C", 27 => "4", 28 => "N", 29 => "T", 30 => "L", 31 => "A", 32 => "Z", 33 => "M", 34 => "W", 35 => "H"),
      "C" => array(0 => "V", 1 => "H", 2 => "W", 3 => "X", 4 => "B", 5 => "J", 6 => "F", 7 => "U", 8 => "T", 9 => "O", 10 => "L", 11 => "Z", 12 => "Q", 13 => "N", 14 => "6", 15 => "E", 16 => "G", 17 => "4", 18 => "7", 19 => "A", 20 => "Y", 21 => "C", 22 => "3", 23 => "5", 24 => "R", 25 => "I", 26 => "9", 27 => "D", 28 => "1", 29 => "P", 30 => "K", 31 => "S", 32 => "2", 33 => "0", 34 => "8", 35 => "M"),
      "D" => array(0 => "Y", 1 => "S", 2 => "H", 3 => "M", 4 => "G", 5 => "O", 6 => "9", 7 => "I", 8 => "Q", 9 => "D", 10 => "Z", 11 => "J", 12 => "T", 13 => "P", 14 => "A", 15 => "B", 16 => "F", 17 => "6", 18 => "V", 19 => "4", 20 => "0", 21 => "E", 22 => "W", 23 => "R", 24 => "N", 25 => "3", 26 => "L", 27 => "5", 28 => "X", 29 => "7", 30 => "U", 31 => "2", 32 => "8", 33 => "C", 34 => "1", 35 => "K"),
      "E" => array(0 => "7", 1 => "H", 2 => "E", 3 => "R", 4 => "Z", 5 => "O", 6 => "P", 7 => "M", 8 => "5", 9 => "T", 10 => "X", 11 => "Q", 12 => "G", 13 => "8", 14 => "9", 15 => "4", 16 => "V", 17 => "L", 18 => "3", 19 => "1", 20 => "K", 21 => "W", 22 => "S", 23 => "J", 24 => "I", 25 => "U", 26 => "F", 27 => "B", 28 => "D", 29 => "A", 30 => "Y", 31 => "N", 32 => "C", 33 => "0", 34 => "2", 35 => "6"),
      "F" => array(0 => "G", 1 => "B", 2 => "N", 3 => "2", 4 => "F", 5 => "K", 6 => "A", 7 => "9", 8 => "P", 9 => "M", 10 => "5", 11 => "8", 12 => "I", 13 => "L", 14 => "Y", 15 => "4", 16 => "Z", 17 => "S", 18 => "O", 19 => "W", 20 => "6", 21 => "3", 22 => "D", 23 => "Q", 24 => "J", 25 => "X", 26 => "E", 27 => "R", 28 => "T", 29 => "0", 30 => "1", 31 => "C", 32 => "7", 33 => "H", 34 => "V", 35 => "U"),
      "G" => array(0 => "5", 1 => "P", 2 => "A", 3 => "8", 4 => "W", 5 => "0", 6 => "J", 7 => "4", 8 => "K", 9 => "2", 10 => "S", 11 => "U", 12 => "6", 13 => "Q", 14 => "9", 15 => "F", 16 => "V", 17 => "L", 18 => "M", 19 => "C", 20 => "7", 21 => "E", 22 => "R", 23 => "1", 24 => "Y", 25 => "3", 26 => "D", 27 => "N", 28 => "T", 29 => "I", 30 => "O", 31 => "B", 32 => "G", 33 => "Z", 34 => "H", 35 => "X"),
      "H" => array(0 => "L", 1 => "8", 2 => "M", 3 => "I", 4 => "T", 5 => "E", 6 => "B", 7 => "C", 8 => "U", 9 => "3", 10 => "4", 11 => "Y", 12 => "H", 13 => "5", 14 => "A", 15 => "O", 16 => "G", 17 => "0", 18 => "S", 19 => "D", 20 => "6", 21 => "P", 22 => "2", 23 => "F", 24 => "N", 25 => "Z", 26 => "9", 27 => "K", 28 => "X", 29 => "Q", 30 => "V", 31 => "J", 32 => "7", 33 => "1", 34 => "W", 35 => "R"),
      "I" => array(0 => "5", 1 => "E", 2 => "U", 3 => "F", 4 => "C", 5 => "6", 6 => "P", 7 => "H", 8 => "1", 9 => "8", 10 => "2", 11 => "9", 12 => "D", 13 => "X", 14 => "3", 15 => "A", 16 => "V", 17 => "G", 18 => "K", 19 => "Y", 20 => "W", 21 => "L", 22 => "N", 23 => "7", 24 => "S", 25 => "B", 26 => "R", 27 => "I", 28 => "T", 29 => "Q", 30 => "O", 31 => "Z", 32 => "M", 33 => "J", 34 => "0", 35 => "4"),
      "J" => array(0 => "M", 1 => "K", 2 => "E", 3 => "L", 4 => "7", 5 => "I", 6 => "A", 7 => "Y", 8 => "1", 9 => "O", 10 => "0", 11 => "T", 12 => "Z", 13 => "2", 14 => "D", 15 => "H", 16 => "R", 17 => "8", 18 => "9", 19 => "Q", 20 => "F", 21 => "5", 22 => "4", 23 => "6", 24 => "U", 25 => "X", 26 => "G", 27 => "P", 28 => "3", 29 => "J", 30 => "C", 31 => "S", 32 => "W", 33 => "B", 34 => "N", 35 => "V"),
      "K" => array(0 => "Y", 1 => "W", 2 => "B", 3 => "I", 4 => "R", 5 => "7", 6 => "9", 7 => "L", 8 => "6", 9 => "A", 10 => "3", 11 => "K", 12 => "Z", 13 => "P", 14 => "O", 15 => "F", 16 => "J", 17 => "2", 18 => "H", 19 => "N", 20 => "G", 21 => "V", 22 => "U", 23 => "0", 24 => "T", 25 => "4", 26 => "5", 27 => "1", 28 => "S", 29 => "C", 30 => "E", 31 => "X", 32 => "8", 33 => "D", 34 => "Q", 35 => "M"),
      "L" => array(0 => "6", 1 => "C", 2 => "8", 3 => "Y", 4 => "B", 5 => "X", 6 => "7", 7 => "V", 8 => "I", 9 => "3", 10 => "G", 11 => "K", 12 => "Z", 13 => "N", 14 => "T", 15 => "U", 16 => "0", 17 => "Q", 18 => "P", 19 => "5", 20 => "F", 21 => "D", 22 => "H", 23 => "M", 24 => "1", 25 => "E", 26 => "2", 27 => "L", 28 => "S", 29 => "R", 30 => "4", 31 => "J", 32 => "A", 33 => "W", 34 => "9", 35 => "O"),
      "M" => array(0 => "6", 1 => "R", 2 => "7", 3 => "K", 4 => "H", 5 => "3", 6 => "M", 7 => "A", 8 => "5", 9 => "B", 10 => "O", 11 => "Y", 12 => "8", 13 => "J", 14 => "F", 15 => "N", 16 => "V", 17 => "G", 18 => "Q", 19 => "E", 20 => "1", 21 => "2", 22 => "Z", 23 => "9", 24 => "W", 25 => "S", 26 => "L", 27 => "I", 28 => "4", 29 => "U", 30 => "D", 31 => "T", 32 => "0", 33 => "C", 34 => "X", 35 => "P"),
      "N" => array(0 => "G", 1 => "P", 2 => "S", 3 => "I", 4 => "E", 5 => "Y", 6 => "O", 7 => "Z", 8 => "B", 9 => "J", 10 => "K", 11 => "H", 12 => "8", 13 => "A", 14 => "M", 15 => "C", 16 => "R", 17 => "1", 18 => "2", 19 => "Q", 20 => "5", 21 => "L", 22 => "D", 23 => "4", 24 => "7", 25 => "0", 26 => "F", 27 => "U", 28 => "9", 29 => "6", 30 => "T", 31 => "W", 32 => "3", 33 => "X", 34 => "V", 35 => "N"),
      "O" => array(0 => "S", 1 => "G", 2 => "N", 3 => "F", 4 => "9", 5 => "E", 6 => "J", 7 => "B", 8 => "1", 9 => "L", 10 => "R", 11 => "C", 12 => "T", 13 => "Y", 14 => "H", 15 => "X", 16 => "K", 17 => "Z", 18 => "6", 19 => "D", 20 => "2", 21 => "O", 22 => "A", 23 => "3", 24 => "0", 25 => "5", 26 => "7", 27 => "8", 28 => "I", 29 => "4", 30 => "M", 31 => "V", 32 => "Q", 33 => "W", 34 => "P", 35 => "U"),
      "P" => array(0 => "6", 1 => "9", 2 => "H", 3 => "J", 4 => "Q", 5 => "B", 6 => "G", 7 => "1", 8 => "4", 9 => "K", 10 => "D", 11 => "C", 12 => "I", 13 => "Y", 14 => "S", 15 => "2", 16 => "E", 17 => "O", 18 => "0", 19 => "8", 20 => "X", 21 => "3", 22 => "L", 23 => "W", 24 => "5", 25 => "V", 26 => "T", 27 => "A", 28 => "R", 29 => "7", 30 => "M", 31 => "Z", 32 => "U", 33 => "N", 34 => "F", 35 => "P"),
      "Q" => array(0 => "R", 1 => "E", 2 => "N", 3 => "X", 4 => "O", 5 => "8", 6 => "Q", 7 => "T", 8 => "M", 9 => "7", 10 => "P", 11 => "U", 12 => "K", 13 => "I", 14 => "Y", 15 => "F", 16 => "B", 17 => "5", 18 => "3", 19 => "D", 20 => "H", 21 => "9", 22 => "C", 23 => "0", 24 => "W", 25 => "2", 26 => "4", 27 => "G", 28 => "S", 29 => "A", 30 => "J", 31 => "V", 32 => "1", 33 => "L", 34 => "6", 35 => "Z"),
      "R" => array(0 => "2", 1 => "A", 2 => "7", 3 => "E", 4 => "4", 5 => "R", 6 => "3", 7 => "K", 8 => "H", 9 => "Q", 10 => "U", 11 => "F", 12 => "T", 13 => "M", 14 => "G", 15 => "X", 16 => "B", 17 => "J", 18 => "P", 19 => "C", 20 => "D", 21 => "0", 22 => "8", 23 => "W", 24 => "Y", 25 => "V", 26 => "S", 27 => "L", 28 => "N", 29 => "Z", 30 => "9", 31 => "O", 32 => "6", 33 => "I", 34 => "1", 35 => "5"),
      "S" => array(0 => "Q", 1 => "1", 2 => "L", 3 => "M", 4 => "Z", 5 => "I", 6 => "P", 7 => "8", 8 => "N", 9 => "X", 10 => "T", 11 => "7", 12 => "G", 13 => "V", 14 => "9", 15 => "O", 16 => "S", 17 => "J", 18 => "K", 19 => "F", 20 => "3", 21 => "U", 22 => "W", 23 => "H", 24 => "B", 25 => "6", 26 => "A", 27 => "5", 28 => "R", 29 => "Y", 30 => "E", 31 => "C", 32 => "0", 33 => "2", 34 => "4", 35 => "D"),
      "T" => array(0 => "3", 1 => "1", 2 => "Q", 3 => "S", 4 => "O", 5 => "L", 6 => "V", 7 => "A", 8 => "D", 9 => "R", 10 => "I", 11 => "E", 12 => "P", 13 => "T", 14 => "4", 15 => "Y", 16 => "8", 17 => "F", 18 => "B", 19 => "5", 20 => "0", 21 => "H", 22 => "7", 23 => "X", 24 => "G", 25 => "M", 26 => "W", 27 => "Z", 28 => "K", 29 => "9", 30 => "2", 31 => "C", 32 => "U", 33 => "6", 34 => "N", 35 => "J"),
      "U" => array(0 => "1", 1 => "D", 2 => "B", 3 => "6", 4 => "K", 5 => "Z", 6 => "I", 7 => "8", 8 => "T", 9 => "W", 10 => "Y", 11 => "V", 12 => "S", 13 => "G", 14 => "J", 15 => "X", 16 => "2", 17 => "P", 18 => "R", 19 => "4", 20 => "9", 21 => "U", 22 => "5", 23 => "E", 24 => "F", 25 => "O", 26 => "C", 27 => "L", 28 => "H", 29 => "7", 30 => "M", 31 => "A", 32 => "0", 33 => "3", 34 => "Q", 35 => "N"),
      "V" => array(0 => "V", 1 => "J", 2 => "O", 3 => "Y", 4 => "4", 5 => "Z", 6 => "6", 7 => "T", 8 => "G", 9 => "7", 10 => "Q", 11 => "D", 12 => "U", 13 => "S", 14 => "8", 15 => "C", 16 => "5", 17 => "F", 18 => "N", 19 => "E", 20 => "H", 21 => "M", 22 => "B", 23 => "P", 24 => "X", 25 => "2", 26 => "3", 27 => "R", 28 => "9", 29 => "K", 30 => "I", 31 => "1", 32 => "0", 33 => "A", 34 => "L", 35 => "W"),
      "W" => array(0 => "L", 1 => "4", 2 => "H", 3 => "I", 4 => "K", 5 => "2", 6 => "C", 7 => "Q", 8 => "E", 9 => "V", 10 => "M", 11 => "U", 12 => "0", 13 => "B", 14 => "Z", 15 => "T", 16 => "D", 17 => "9", 18 => "6", 19 => "Y", 20 => "8", 21 => "3", 22 => "O", 23 => "S", 24 => "X", 25 => "5", 26 => "N", 27 => "R", 28 => "A", 29 => "F", 30 => "W", 31 => "P", 32 => "1", 33 => "7", 34 => "J", 35 => "G"),
      "X" => array(0 => "D", 1 => "R", 2 => "T", 3 => "N", 4 => "6", 5 => "Q", 6 => "5", 7 => "C", 8 => "U", 9 => "K", 10 => "W", 11 => "H", 12 => "1", 13 => "F", 14 => "2", 15 => "M", 16 => "9", 17 => "Z", 18 => "E", 19 => "0", 20 => "G", 21 => "4", 22 => "I", 23 => "O", 24 => "B", 25 => "3", 26 => "7", 27 => "S", 28 => "A", 29 => "Y", 30 => "V", 31 => "P", 32 => "L", 33 => "8", 34 => "J", 35 => "X"),
      "Y" => array(0 => "C", 1 => "H", 2 => "U", 3 => "4", 4 => "7", 5 => "D", 6 => "3", 7 => "Z", 8 => "M", 9 => "W", 10 => "L", 11 => "I", 12 => "O", 13 => "T", 14 => "Q", 15 => "0", 16 => "G", 17 => "K", 18 => "F", 19 => "2", 20 => "S", 21 => "J", 22 => "P", 23 => "E", 24 => "1", 25 => "Y", 26 => "N", 27 => "B", 28 => "9", 29 => "V", 30 => "A", 31 => "R", 32 => "8", 33 => "6", 34 => "X", 35 => "5"),
      "Z" => array(0 => "0", 1 => "Z", 2 => "6", 3 => "L", 4 => "4", 5 => "B", 6 => "N", 7 => "K", 8 => "R", 9 => "C", 10 => "S", 11 => "F", 12 => "Q", 13 => "U", 14 => "Y", 15 => "D", 16 => "I", 17 => "M", 18 => "7", 19 => "V", 20 => "8", 21 => "2", 22 => "O", 23 => "T", 24 => "W", 25 => "5", 26 => "E", 27 => "J", 28 => "G", 29 => "1", 30 => "A", 31 => "H", 32 => "X", 33 => "9", 34 => "3", 35 => "P")
        );

  return $shuffles[$i];
}

function mixup_link($link)
{
  // use first char as cryptogram generation 0-9 A-Z, tack it on the end to know how to decrypt

  $alphabet = array_flip(array_merge(range('0', '9'), range('A', 'Z')));

  $first = $link[0];

  //exit($first);

  $cryptogram = get_cryptogram($first);

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

function unmix_link($link)
{
  // last char tells us how to decrypt 0-9 A-Z, remove it from final result

  $alphabet = array_flip(array_merge(range('0', '9'), range('A', 'Z')));

  $last = $link[(strlen($link)-1)];

  $cryptogram = get_cryptogram($last);

  if (! is_array($cryptogram)) {
    return;
  }

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

function get_available_ad_id($affid, $type, $db)
{
  $db->Query("SELECT ad_ids FROM users WHERE affid='$affid' LIMIT 1");
  list($ad_ids) = $db->FetchRow();

  if ($ad_ids == '') return '';

  $ad_ids = unserialize($ad_ids);

  $ad_ids = $ad_ids[$type];

  if (@count($ad_ids) AND @is_array($ad_ids)) if ($ad_ids[0]) return $ad_ids[0];

  return '';
}

function set_available_ad_id($affid, $id_ad, $type, $db)
{
  $db->Query("SELECT ad_ids FROM users WHERE affid='$affid' LIMIT 1");
  list($ad_ids) = $db->FetchRow();

  $ad_ids = unserialize($ad_ids);

  if (! @count($ad_ids) OR ! @is_array($ad_ids))
  {
    $ad_ids = array();
    $ad_ids[$type] = array($id_ad);
  }
  else
  {
    if (is_array($ad_ids[$type]))
    {
      if (! in_array($id_ad, $ad_ids[$type]))
      {
        $ad_ids[$type] = array_merge($ad_ids[$type], array($id_ad));
        sort($ad_ids[$type]);
      }
    }
    else
      $ad_ids[$type] = array($id_ad);
  }

  // echo '<pre>'.print_r($ad_ids, 1).'</pre>';

  $ad_ids = serialize($ad_ids);
  $db->Query("UPDATE users SET ad_ids='$ad_ids' WHERE affid='$affid' LIMIT 1");
}

function remove_available_ad_id($affid, $id_ad, $type, $db)
{
  $db->Query("SELECT ad_ids FROM users WHERE affid='$affid' LIMIT 1");
  list($ad_ids) = $db->FetchRow();

  if ($ad_ids == '') return;

  $ad_ids = unserialize($ad_ids);

  if (! @count($ad_ids) OR ! @is_array($ad_ids))
    $ad_ids = array();
  else
  {
    $remove = $ad_ids[$type];
    $remove = array_flip($remove);
    unset($remove[$id_ad]);
    $remove = array_flip($remove);
    //echo '<pre>'.print_r($remove, 1).'</pre>';
    if (! count($remove))
      unset($ad_ids[$type]);
    else
    {
      sort($remove);
      $ad_ids[$type] = $remove;
    }
  }

  //echo '<pre>'.print_r($ad_ids, 1).'</pre>';

  if (! count($ad_ids))
    $ad_ids = '';
  else
    $ad_ids = serialize($ad_ids);

  $db->Query("UPDATE users SET ad_ids='$ad_ids' WHERE affid='$affid' LIMIT 1");
}

function set_earned_ads($affid, $urlaffid, $type, $id, $db)
{
  $db->Query("SELECT adstoday FROM users WHERE affid='$affid' LIMIT 1");
  list($adstoday) = $db->FetchRow();

  if ($adstoday == '')
  {
    $adstoday = array();
    $adstoday[$urlaffid][$type] = array($id);
  }
  else
  {
    $adstoday = unserialize($adstoday);

    if (is_array($adstoday[$urlaffid][$type]))
    {
      $check = $adstoday[$urlaffid][$type];
      if (! in_array($id, $check))
      {
        $adstoday[$urlaffid][$type] = array_merge($adstoday[$urlaffid][$type], array($id));
        sort($adstoday[$urlaffid][$type]);
      }
    }
    else
      $adstoday[$urlaffid][$type] = array($id);
  }

  $adstoday = serialize($adstoday);

  $db->Query("UPDATE users SET adstoday='$adstoday' WHERE affid='$affid' LIMIT 1");
}

function valid_url($url)
{
  global $banned_urls;

  /*
     parse_url('http://username:password@hostname/path?arg=value#anchor');
     [scheme] => http
     [host] => hostname
     // joyfulnumerology.burkeshire-reports.com
  */
  if (! $parts = parse_url($url)) return 'ERROR: URL is not valid.';

  extract($parts);

  list($host1, $host2) = explode('.', strrev($host));
  $host = strrev($host1.'.'.$host2);

  if (substr($url, 0, 7) != 'http://' AND substr($url, 0, 8) != 'https://')
    return 'ERROR: URL must begin with http:// or https://';
  else if (in_array($host, $banned_urls))
    return 'ERROR: Domain in URL is not allowed.<br />Maybe because the website contains frame breaking javascript code which prevents users from earning credits when they read your AD.<br />Open a ticket with us to resolve this issue.';
}

function check_status($affid, $db)
{
  global $help_downgrade, $days_grace_period;

  if (! $db->Query("SELECT status, datelastbilled FROM users WHERE affid='$affid' LIMIT 1")) exit('FATAL ERROR: affid unknown in check_status()');
  extract($db->FetchArray());

  $num_days_left = DateDiff(mysql_datetime_to_timestamp($datelastbilled), time(), 'd');
  $num_days_left = $days_grace_period - round($num_days_left);

  $help = $help_downgrade;

  $message = '
  <center>
  <font color="red"><b>Notice:</font> Your Pro Membership has expired and needs to be <a href="?c=renew">Renewed</a>!</b>
  <br />
  In <font size="+1"><b>'.$num_days_left.'</b> Days</font> your Pro Membership will be Down Graded to Free Member Status!
  <br />
  '.$help.'
  </center>
  ';

  if ($status == 2)
    return $message;
  else
    return '';
}

function downgrade_member($email, $fname, $lname, $username, $password, $affid, $datelastbilled, $headers, $db)
{
  global $ba_max_ads_free, $bb_max_ads_free, $ea_max_ads_free, $sl_max_ads_free, $ta_max_ads_free;
  global $upload_path, $days_grace_period;

  // banners
  if ($ba_max_ads_free) $where = "active='0'"; else $where = "(active='0' OR active='1')";
  $db->Query("SELECT id, image FROM ad_banners WHERE $where AND affid='$affid'");
  $result = $db->result;
  while (list($id, $img) = mysqli_fetch_row($result))
  {
    set_available_ad_id($affid, $id, 'banner', $db);
    @unlink("$upload_path/$img");
  }
  $db->Query("DELETE FROM ad_banners WHERE $where AND affid='$affid'");

  // billboards
  if ($bb_max_ads_free) $where = "active='0'"; else $where = "(active='0' OR active='1')";
  $db->Query("SELECT id, image FROM ad_billboards WHERE $where AND affid='$affid'");
  $result = $db->result;
  while (list($id, $img) = mysqli_fetch_row($result))
  {
    set_available_ad_id($affid, $id, 'billboard', $db);
    @unlink("$upload_path/$img");
  }
  $db->Query("DELETE FROM ad_billboards WHERE $where AND affid='$affid'");

  // exits
  if ($ea_max_ads_free) $where = "active='0'"; else $where = "(active='0' OR active='1')";
  $db->Query("SELECT id FROM ad_exits WHERE $where AND affid='$affid'");
  $result = $db->result;
  while (list($id) = mysqli_fetch_row($result))
    set_available_ad_id($affid, $id, 'exit', $db);
  $db->Query("DELETE FROM ad_exits WHERE $where AND affid='$affid'");

  // spotlights
  if ($sl_max_ads_free) $where = "active='0'"; else $where = "(active='0' OR active='1')";
  $db->Query("SELECT id FROM ad_spotlights WHERE $where AND affid='$affid'");
  $result = $db->result;
  while (list($id) = mysqli_fetch_row($result))
    set_available_ad_id($affid, $id, 'spotlight', $db);
  $db->Query("DELETE FROM ad_spotlights WHERE $where AND affid='$affid'");

  // targeted
  if ($ta_max_ads_free) $where = "active='0'"; else $where = "(active='0' OR active='1')";
  $db->Query("SELECT id FROM ad_targeted WHERE $where AND affid='$affid'");
  $result = $db->result;
  while (list($id) = mysqli_fetch_row($result))
    set_available_ad_id($affid, $id, 'targeted', $db);
  $db->Query("DELETE FROM ad_targeted WHERE $where AND affid='$affid'");

  // user
  $db->Query("UPDATE users SET status='0' WHERE affid='$affid' LIMIT 1");

  // commissions
  $db->Query("UPDATE commissions SET status='0' WHERE status='2' AND sponsor='$affid'");

  $message = "Hello $fname $lname,

We are sorry to inform you that, the $days_grace_period day Grace Period
has expired, and your account was Down Graded from Pro, to a Free Member.

Your account is still very much useable, and can be re-upgraded at anytime!

http://freeadplanet.com/?c=memberlogin

Username: $username
Password: $password

Thank You,
http://freeadplanet.com staff";

  @mail($email,
        'Down Grade Notice',
        $message,
        $headers);

  @mail('elitescripts2000@yahoo.com',
        'Down Grade Notice',
        $message,
        $headers);
}

function delete_user($affid, $db)
{
  global $upload_path;

  // banners and images
  $db->Query("SELECT image FROM ad_banners WHERE affid='$affid'");
  while (list($img) = $db->FetchRow()) @unlink("$upload_path/$img");
  $db->Query("DELETE FROM ad_banners WHERE affid='$affid'");

  // billboards and images
  $db->Query("SELECT image FROM ad_billboards WHERE affid='$affid'");
  while (list($img) = $db->FetchRow()) @unlink("$upload_path/$img");
  $db->Query("DELETE FROM ad_billboards WHERE affid='$affid'");

  // exits, spotlights, targeted, puchased, urls
  $db->Query("DELETE FROM ad_exits WHERE affid='$affid'");
  $db->Query("DELETE FROM ad_spotlights WHERE affid='$affid'");
  $db->Query("DELETE FROM ad_targeted WHERE affid='$affid'");
  $db->Query("DELETE FROM ad_purchased WHERE affid='$affid'");
  $db->Query("DELETE FROM urls WHERE affid='$affid'");

  $db->Query("DELETE FROM ad_breakers WHERE ownerID='$affid'");

  // user
  $db->Query("DELETE FROM users WHERE affid='$affid'");

  // track affid from never being able to be used again, due to possible commissions table conflicts
  $db->Query("REPLACE INTO pastaffs VALUES('$affid')");
}

function turing_key_valid($turing_key_timeout)
{
  // see if turing key is within time limits
  $time_good = 0;
  $current_time = time();
  $parts = explode('S', $_POST['v']);
  $time_sent = substr($parts[0], strlen($parts[0]) - $parts[1], $parts[1]);
  $validate = substr($parts[0], 0, strlen($parts[0]) - $parts[1]);
  $time_max = $current_time + $turing_key_timeout;
  if ($current_time <= $time_sent AND $time_sent <= $time_max)
    $time_good = 1;

  if (strrev(md5(sha1(strrev($time_sent.$_POST['tkey'])))) == $validate AND $time_good)
    return 1;
  else
    return 0;
}

function fap_log($str)
{
  $date = date('M j G:i:s');

  $out = $date . ' - ' . $str;

  //system('echo "' . $out . '" >> /home/nulled/www/freeadplanet.com/secure/fap_log');
}

function ad_content_illegal($str)
{
  global $illegal_content;

  if (strstr($str, "'"))
    return "ERROR: Single Quotes not allowed.";

  foreach ($illegal_content as $ill)
  {
    if (stristr($str, $ill))
      return "ERROR: Do not submit porn or sexual content of any kind.";
  }

  return '';
}

?>