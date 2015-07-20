<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/configdefaults.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

// check if a list slot is available if not logout user
$db = new MySQL_Access('mle');

$emptyLists = $db->Query("SELECT listownerID FROM listmanager WHERE listownerID='{$_SESSION['aalistownerID']}' AND created='0'");
$numLists   = $db->Query("SELECT listownerID FROM listmanager WHERE listownerID='{$_SESSION['aalistownerID']}'");

if (! $emptyLists)
{
  header('Location: index.php?notValid=' . urlencode('ERROR: No more slots left to create a list.');
  exit;
}

if ($submitted == 'create' AND $fromname AND $thelistname AND $adminemail)
{
  $thelistname = trim($thelistname);
  $fromname    = trim($fromname);
  $adminemail  = strtolower(trim($adminemail));
  $fromemail   = 'do_not_reply@planetxmail.com'; //strtolower(trim($fromemail));
  $bounceemail = 'do_not_reply@planetxmail.com'; // strtolower(trim($bounceemail));

  if (has_weird($thelistname))        $notValid = 'ERROR: List name may only contain Letters, Numbers and underscores (_).';
  else if (has_space($thelistname))   $notValid = 'ERROR: List name may not contain any Spaces.';
  else if (strlen($thelistname) > 20) $notValid = 'ERROR: List name may not exceed 20 Characters.';
  else if (has_weird($fromname))      $notValid = 'ERROR: From email name may only contain Letters, Numbers and underscores (_).';
  else if (has_space($fromname))      $notValid = 'ERROR: From email name may not contain any Spaces.';
  else if (strlen($fromname) > 20)    $notValid = 'ERROR: From email name may not be longer than 20 Characters.';
  else if ($notValid = EmailFormat($fromemail)) {}
  else if ($notValid = EmailFormat($adminemail)) {}
  else if ($notValid = EmailFormat($bounceemail)) {}
  else if ($db->Query("SELECT listname FROM listmanager WHERE listname='{$thelistname}' AND listownerID='{$_SESSION['aalistownerID']}' LIMIT 1"))
    $notValid = "ERROR: Listname <i>{$thelistname}</i> is already taken.";
  else
  {
    $db->Query("SELECT listname FROM listmanager WHERE created='0' AND listownerID='{$_SESSION['aalistownerID']}' LIMIT 1");
    list($listnameID) = $db->FetchRow();

    $subconfirm   = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/subconfirm.txt');
    $subsuccess   = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/subsuccess.txt');
    $unsubsuccess = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/unsubsuccess.txt');
    $footer       = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/footer.txt');
    $header       = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/header.txt');
    $paymenthtml  = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/paymenthtml.txt');

    $html         = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/html.txt');
    $html         = $html . '!N_T_W_S_4_0!' . $html . '!N_T_W_S_4_0!' . $html;

    $upgradeinfopro = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/upgradeinfopro.txt');
    $upgradeinfoexe = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/upgradeinfoexe.txt');

    $upgradeinfo    = $upgradeinfopro . '!N_T_W_S_4_0!' . $upgradeinfoexe;

    // build THREE list messages each with a subject and message body.
    // Safelist non-html, newsletter non-html, newsletter html
    $subject       = 'Enter subject line here';
    $message       = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/message.txt');

    $nlsubject     = 'Enter NON HTML newsletter subject line here.';
    $nlmessage     = 'Enter NON HTML message here.';
    $nlhtmlsubject = 'Enter HTML newsletter subject line here.';
    $nlhtmlmessage = 'Enter HTML newsletter message here.';

    $message = $subject . 'n!t!w_s!4!0' . $message . 'n!t!w_s!4!0' . $nlsubject . 'n!t!w_s!4!0' .
               $nlmessage . 'n!t!w_s!4!0' . $nlhtmlsubject . 'n!t!w_s!4!0' . $nlhtmlmessage;

    $db->Query("UPDATE listmanager SET listownerID='{$_SESSION['aalistownerID']}', listname='$thelistname', fromname='$fromname',
                                       fromemail='$fromemail', adminemail='$adminemail', bounceemail='$bounceemail', listtype='$listtype',
                                       message='$message', footer='$footer', header='$header', subconfirm='$subconfirm',
                                       subsuccess='$subsuccess', unsubsuccess='$unsubsuccess', paymenthtml='$paymenthtml', created='1',
                                       html='$html'
                                       WHERE listname='$listnameID' AND listownerID='{$_SESSION['aalistownerID']}'");

    $midnight = mktime(0, 0, -1, date('m'), date('d'), date('y'));
    $midnight = timestamp_to_mysql_timestamp($midnight);
    $db->Query("INSERT INTO system VALUES('{$_SESSION['aalistownerID']}','$thelistname',$midnight)");

    $db->Query("SELECT email FROM listowner WHERE listownerID='{$_SESSION['aalistownerID']}' LIMIT 1");
    list($admin_email_address) = $db->FetchRow();

    $db->Query("INSERT INTO listconfig VALUES('{$_SESSION['aalistownerID']}','$thelistname','$program_name','$commission',
                                              '','$admin_email_address','$logout_location','$upgradeinfo','$numurltrackersMem',
                                              '$numurltrackersPro','$numurltrackersExe','$mem_sendmail_times_week',
                                              '$pro_sendmail_times_week','$exe_sendmail_times_day','$mem_sendmail_times_week',
                                              '$pro_sendmail_times_week','$exe_sendmail_times_day',$cost_of_pro','$cost_of_exe',
                                              '$pro_upgradeform','$exe_upgradeform','','$defaultstatus','$allowupgrades',
                                              '$newmembernotice','0','0','0','0','0','0','0')");

    $_SESSION['aalistname'] = $thelistname;

    // make sure listhash is unique
    $i = 0;
    while (true)
    {
      if ($i > 1000)
        mail_debug_backtrace_exit();

      $i++;

      $listhash = substr(sha1(bin2hex(openssl_random_pseudo_bytes(20))), 0, 5);

      if ($db->Query("SELECT listhash FROM listurls WHERE listhash='{$listhash}' LIMIT 1"))
        continue;
      else
        break;
    }

    $db->Query("INSERT INTO listurls VALUES('{$_SESSION['aalistownerID']}','{$_SESSION['aalistname']}','{$listhash}')");

    header('Location: listcreated.php?isAdmin=1');
    exit;
  }
}
else if ($submitted == 'create')
  $notValid = 'ERROR: Missing required fields.';
else if ($submitted == 'delete')
{
  $db->Query("DELETE FROM listmanager WHERE listownerID='{$_SESSION['aalistownerID']}' AND created='0' LIMIT 1");

  header('Location: main.php');
  exit;
}

?>