<?php
$upload_path = '/home/nulled/www/freeadplanet.com/banners';

$date = date('F j, Y');

$bb_max_head_chars = 25;
$bb_max_mess_chars = 50;

$ta_max_head_chars = 25;
$ta_max_mess_chars = 50;

$sl_max_head_chars = 25;
$sl_max_mess_chars = 50;

$bb_max_ads_free = 0;
$ta_max_ads_free = 1;
$sl_max_ads_free = 1;
$ba_max_ads_free = 1;
$ea_max_ads_free = 1;

$bb_max_ads_pro = 2;
$ta_max_ads_pro = 1;
$sl_max_ads_pro = 2;
$ba_max_ads_pro = 2;
$ea_max_ads_pro = 2;

$credits_earned_free = 1;
$credits_earned_pro  = 2;

function load_image($image, $img_pos)
{
  global $upload_path;

  $img_form1 = $img_form2 = $img_preview = '';
  if (@is_file("$upload_path/$image"))
  {
    list(,,,$attr) = getimagesize("$upload_path/$image");

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

    $img_form1 = '<b>Current&nbsp;Image:</b><br /><br /><center><img src="http://freeadplanet.com/banners/'.$image.'" '.$attr.' border="0" /></center>';
    $img_form2 = '<b>Position&nbsp;Image:</b><br /><input type="radio" name="img_pos" value="0" '.$radio1.'/>&nbsp;Left&nbsp;<input type="radio" name="img_pos" value="1" '.$radio2.'/>&nbsp;Right<br /><br /><input type="checkbox" name="deleteimage" value="1" />&nbsp;Delete Image';
    $img_preview = '<img src="http://freeadplanet.com/banners/'.$image.'" '.$attr.' border="0" class="'.$float.'" />';
  }

  return array($img_form1, $img_form2, $img_preview);
}

function check_uploaded_image($img, $type='banner', $curr_img='')
{
  global $upload_path;

  //echo '<pre>'.print_r($_FILES,1).'</pre>';

  // if current image and no file was uploaded, then keep current
  if ($curr_img && $_FILES[$img]['error']) return array('Keeping your previous Image.', $curr_img);

  if ($_FILES[$img]['error'] == 4) return array('No image was uploaded.', $curr_img);

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
    else if ($_type != 1 && $_type != 2 && $_type != 3) $notValid = 'ERROR: Image must be jpg, gif or png format.';
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
        if ($curr_img && @is_file("$upload_path/$curr_img")) @unlink("$upload_path/$curr_img");
        $curr_img = '';
        $notValid = 'ERROR: move_uploaded_file() failed.';
      }
    }
  }

  if (! stristr($notValid, 'ERROR:'))
    return array($notValid, "$rand_image_name.$extention");
  else
    return array($notValid, $curr_img);
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
      $cats .= '<tr><td width="5" nowrap><input type="checkbox" name="cat[]" value="'.$_id.'" '.$is_checked.'/></td><td nowrap>'.$name.'</td>'."\n";
    else
      $cats .= '<td width="5" nowrap><input type="checkbox" name="cat[]" value="'.$_id.'" '.$is_checked.'/></td><td nowrap>'.$name.'</td></tr>'."\n";

    $i++;
  }
  $cats .= '</table>';

  return $cats;
}

function logout_session($why)
{
  session_destroy();
  header('Location: http://freeadplanet.com/?c=memberexit&why='.urlencode($why));
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
  if (! $db->Query("SELECT username, pass, fname, lname, email, paypal, alertpay, egold, sponsor, categories, verified, credits, paidcredits, status  FROM users WHERE affid='$affid'"))
    exit('FATAL ERROR: Contact Support. CODE: 1');
  return $db->FetchRow();
}

function get_targeted_ads($status, $user_categories, $db)
{
  $i = 0;
  $ads = array();
  if ($db->Query("SELECT id, affid, heading, message, url, categories FROM ad_targeted WHERE 1"))
  {
    $result = $db->result;
    while(list($_id, $_affid, $_heading, $_message, $_url, $_categories) = mysqli_fetch_row($result))
    {
      // check if status of user owning the AD is FREE
      if (! $db->Query("SELECT affid FROM users WHERE status='$status' AND affid='$_affid'")) continue;

      $_categories = explode(',', $_categories);

      // check to see if current user cat match any cat for this AD
      $found = 0;
      foreach ($user_categories as $_cat)
      {
        if (in_array($_cat, $_categories))
        {
          $found = 1;
          break;
        }
      }
      if (! $found) continue;

      $ads[$i]['id']      = $_id;
      $ads[$i]['heading'] = $_heading;
      $ads[$i]['message'] = $_message;
      $ads[$i]['url']     = $_url;
      $i++;
    }
  }
  else
    $ads = array();

  return $ads;
}

function get_ads($type, $db)
{
  if ($type == 'spotlight')
  {
    $table  = 'ad_spotlights';
    $fields = 'id, heading, message, url';
  }
  else if ($type == 'billboard')
  {
    $table  = 'ad_billboards';
    $fields = 'id, heading, message, url, image, img_pos';
  }
  else if ($type == 'banner')
  {
    $table  = 'ad_banners';
    $fields = 'id, image, url';
  }
  else
    exit('FATAL ERROR: type='.$type.' unknown in get_billboard_ads()');

  $i = 0;
  $ads = array();
  $db->Query("SELECT $fields FROM $table WHERE 1");
  while(list($a, $b, $c, $d, $e, $f) = $db->FetchRow())
  {
    if ($type == 'spotlight')
    {
      $ads[$i]['id']      = $a;
      $ads[$i]['heading'] = $b;
      $ads[$i]['message'] = $c;
      $ads[$i]['url']     = $d;
    }
    else if ($type == 'billboard')
    {
      $ads[$i]['id']      = $a;
      $ads[$i]['heading'] = $b;
      $ads[$i]['message'] = $c;
      $ads[$i]['url']     = $d;
      $ads[$i]['image']   = $e;
      if ($f) $ads[$i]['img_pos'] = 'floatRight'; else $ads[$i]['img_pos'] = 'floatLeft';
    }
    else if ($type == 'banner')
    {
      $ads[$i]['id']      = $a;
      $ads[$i]['image']   = $b;
      $ads[$i]['url']     = $c;
    }
    $i++;
  }

  return $ads;
}

?>