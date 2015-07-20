<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

if ($l)    $l    = trim($l);
if ($id)   $id   = trim($id);
if ($list) $list = trim($list);

if (! $_CONFIG_SET)
{
  $_CONFIG_SET = 1;

  $_IS_SESSION = 0;

  $mletime     = time();
  $domainroot  = 'http://planetxmail.com/mle';

  $headers = 'From: Planet X Mail <do_not_reply@planetxmail.com>';

  $dbconfig = new MySQL_Access('mle');

  // default is user is logged in and thus has _SESSION set for which list their logged into
  if ($_SESSION['aalistownerID'] AND $_SESSION['aalistname'])
  {
    $_listID = "listownerID='{$_SESSION['aalistownerID']}' AND listname='{$_SESSION['aalistname']}'";
    if ($dbconfig->Query("SELECT listhash FROM listurls WHERE {$_listID} LIMIT 1"))
    {
      list($listhash) = $dbconfig->FetchRow();
      $_IS_SESSION = 1;
    }
    else
      mail_debug_backtrace_exit();
  }

  // if not logged in (coming from login or signup page)
  if (! $_IS_SESSION)
  {
    $_HASH_FOUND = 0;

    // l=listhash which is perferred so check it first
    if (@ctype_alnum($l))
    {
      if ($dbconfig->Query("SELECT listownerID, listname FROM listurls WHERE listhash='{$l}' LIMIT 1"))
      {
        list($id, $list) = $dbconfig->FetchRow();
        $_listID = "listownerID='$id' AND listname='$list'";
        $listhash = $l;
        $_HASH_FOUND = 1;
      }
    }

    // last case is old way where list and id must be present, if this fails everything else stops
    if (! $_HASH_FOUND AND @is_numeric($id) AND ! has_weird($list))
    {
      $_listID = "listownerID='{$id}' AND listname='{$list}'";
      if ($dbconfig->Query("SELECT listhash FROM listurls WHERE {$_listID} LIMIT 1"))
      {
        list($listhash) = $dbconfig->FetchRow();
        $l = $listhash;
      }
      else if ($dbconfig->Query("SELECT listownerID FROM listurls WHERE listname='{$list}' LIMIT 1"))
      {
        // maybe the listownerID was changed, but listname remains, so check for that ...
        list($id) = $dbconfig->FetchRow();
        $_listID = "listownerID='{$id}' AND listname='{$list}'";

        if ($dbconfig->Query("SELECT listhash FROM listurls WHERE {$_listID} LIMIT 1"))
          list($listhash) = $dbconfig->FetchRow();
      }
      else
        $_listID = '';
    }
  }

  // is $_listID is set we can get list configs
  if ($_listID)
  {
    if ($dbconfig->Query("SELECT * FROM listconfig WHERE {$_listID} LIMIT 1"))
      $listData = $dbconfig->FetchArray();
  }
  else {
    mail_debug_backtrace_exit('Either URL/Link was copy/pasted wrong or the List no longer Exists.',
                              'http://planetxmail.com/mle/requestlists.php?notValid=', null);
  }

  $paylinkhtml_length    = 20000;
  $header_length         = 500;
  $footer_length         = 500;
  $subconfirm_length     = 2000;
  $subsuccess_length     = 2000;
  $unsubsuccess_length   = 2000;
  $html_length           = 20000;
  $email_length          = 5000;
  $admin_email_length    = 5000;
  $email_subject_length  = 80;
  $ad_subject_length     = 100;
  $ad_description_length = 500;
  $banner_size           = 30000; // size is in bytes
  $banner_width          = 468;   // standard size for banners is 468 by 60
  $banner_height         = 60;
  $image_size            = 30000; // size is in bytes
  $logo_max_width        = 468;   // standard size for banners is 468 by 60
  $logo_max_height       = 60;
  $email_wordwrap_length = 70;
  $title_width           = 500;
  $title_height          = 150;
  $title_size            = 30000; // size is in bytes

  $program_name = $listData['programname'];

  list($commission_pro, $commission_exe, $allowrenewalcommission) = explode('|', $listData['commission']);

  $logout_location = $listData['logoutlocation'];

  $numurltrackersMem = $listData['numurltrackersmem'];
  $numurltrackersPro = $listData['numurltrackerspro'];
  $numurltrackersExe = $listData['numurltrackersexe'];

  $freestartcredits = $listData['freestartcredits'];
  $prostartcredits  = $listData['prostartcredits'];
  $exestartcredits  = $listData['exestartcredits'];

  $freeearnedcredits = $listData['freeearnedcredits'];
  $proearnedcredits  = $listData['proearnedcredits'];
  $exeearnedcredits  = $listData['exeearnedcredits'];

  $mem_sendmail_times_week = $listData['memsendmailweek'];
  $pro_sendmail_times_week = $listData['prosendmailweek'];
  $exe_sendmail_times_day  = $listData['exesendmailday'];

  $mem_sendmailcredits_times_week = $listData['memsendmailcreditsweek'];
  $pro_sendmailcredits_times_week = $listData['prosendmailcreditsweek'];
  $exe_sendmailcredits_times_day  = $listData['exesendmailcreditsday'];

  list($cost_of_pro, $cost_of_pro_renewal, $cost_of_pro_upgrade) = explode('|', $listData['costofpro']);
  list($cost_of_exe, $cost_of_exe_renewal, $cost_of_exe_upgrade) = explode('|', $listData['costofexe']);

  $admin_email_address   = $listData['adminemailaddress'];

  $testmode_username = $listData['testmode_username'];
  $defaultstatus     = $listData['defaultstatus'];
  $allowupgrades     = $listData['allowupgrades'];
  $newmembernotice   = $listData['newmembernotice'];

  $pro_upgradeform = $listData['proupgradeform'];
  $exe_upgradeform = $listData['exeupgradeform'];

  // get custom title graphic and random banner
  if ($_listID)
  {
    if ($dbconfig->Query("SELECT banner FROM banners WHERE {$_listID} AND bannerlink = 'TITLE_GRAPHIC' LIMIT 1"))
    {
      list($titleIMG) = $dbconfig->FetchRow();

      $_filename = '/home/nulled/www/planetxmail.com/mle/admin/_signs/' . basename($titleIMG);

      if (! is_file($_filename))
        $titleIMG = '';
    }

    if ($dbconfig->Query("SELECT banner, bannerlink FROM banners WHERE {$_listID} AND LEFT(bannerlink, 3) = 'PER' ORDER BY MD5(RAND()) LIMIT 1"))
    {
      list($bannerIMG, $bannerLINK) = $dbconfig->FetchRow();
      $bannerLINK = substr($bannerLINK, 3);

      $_filename = '/home/nulled/www/planetxmail.com/mle/admin/_signs/' . basename($bannerIMG);

      if (! is_file($_filename))
        $bannerIMG = '';
    }

    // determine if affiliate system is used
    if ($dbconfig->Query("SELECT referer FROM listconfig WHERE {$_listID} LIMIT 1"))
    {
      list($referer) = $dbconfig->FetchRow();
      $referer = trim($referer);
    }
  }
}

?>