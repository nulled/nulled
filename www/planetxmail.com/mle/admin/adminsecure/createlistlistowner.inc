<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/configdefaults.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

// check if a list slot is available if not logout user
$db = new MySQL_Access();

$db->Query("SELECT listownerID FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' AND created='0'");
$emptyLists = $db->rows;
$db->Query("SELECT listownerID FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]'");
$numLists = $db->rows;

if (! $emptyLists)
{
  $notValid = urlencode("ERROR:  No more slots left to create a list.");

  header("Location: index.php?notValid=$notValid");
  exit;
}

if ($submitted=="create" AND $thelistname AND $fromemail AND $adminemail AND $bounceemail)
{
  $thelistname = trim($thelistname);
  $fromname 	 = trim($fromname);
  $fromemail   = trim($fromemail);
  $adminemail  = trim($adminemail);
  $bounceemail = trim($bounceemail);

  if (has_weird($thelistname)) $notValid = "ERROR: List name can only have a-z, A-Z, 0-9 or _ in it. Please re-enter.";
  else if (strlen($thelistname)>20) $notValid = "ERROR: List name can not exceed 20 characters.";
  else if (has_space($thelistname)) $notValid = "ERROR: List name can not have any spaces. Please re-enter.";
  else if (has_space($fromname)) $notValid = "ERROR: From name can not have any spaces. Please re-enter.";
  else if (strlen($fromname)>20) $notValid = "ERROR: From email name can not be longer than 20 characters.";
  else if ($notValid = EmailFormat($fromemail,0)) {}
  else if ($notValid = EmailFormat($adminemail,0)) {}
  else if ($db->Query("SELECT listname FROM listmanager WHERE listname='$thelistname' AND listownerID='$_SESSION[aalistownerID]'")) $notValid = "ERROR: Listname <i>$thelistname</i> is already taken.";
  else
  {
    $db->Query("SELECT listname FROM listmanager WHERE created='0' AND listownerID='$_SESSION[aalistownerID]' LIMIT 1");
    $data = $db->FetchRow();
    $listnameID = $data[0];

    $subconfirm = file_get_contents("../messages/subconfirm.txt");
    $subsuccess = file_get_contents("../messages/subsuccess.txt");
    $unsubsuccess = file_get_contents("../messages/unsubsuccess.txt");
    $footer = file_get_contents("../messages/footer.txt");
    $header = file_get_contents("../messages/header.txt");
    $message = file_get_contents("../messages/message.txt");
    $paymenthtml = file_get_contents("../messages/paymenthtml.txt");

    $html = file_get_contents("../messages/html.txt");
    $html = $html."!N_T_W_S_4_0!".$html."!N_T_W_S_4_0!".$html;

    $upgradeinfopro = file_get_contents("../messages/upgradeinfopro.txt");
    $upgradeinfoexe = file_get_contents("../messages/upgradeinfoexe.txt");
    $upgradeinfo    = $upgradeinfopro."!N_T_W_S_4_0!".$upgradeinfoexe;

    $db->Query("UPDATE listmanager SET listownerID='$_SESSION[aalistownerID]', listname='$thelistname', fromname='$fromname', fromemail='$fromemail', adminemail='$adminemail', bounceemail='$bounceemail', listtype='$listtype', message='$message', footer='$footer', header='$header', subconfirm='$subconfirm', subsuccess='$subsuccess', unsubsuccess='$unsubsuccess', paymenthtml='$paymenthtml', created='1', html='$html' WHERE listname='$listnameID' AND listownerID='$_SESSION[aalistownerID]'");
    $midnight = mktime(0, 0, -1, date("m"), date("d"), date("y"));
    $midnight = timestamp_to_mysql_timestamp($midnight);
    $db->Query("INSERT INTO system VALUES('$_SESSION[aalistownerID]','$thelistname',$midnight)");

    include("../mlpsecure/config/configdefaults.inc");
    $db->Query("SELECT email FROM listowner WHERE listownerID='$_SESSION[aalistownerID]'");
    list($admin_email_address) = $db->FetchRow();
    $db->Query("INSERT INTO listconfig VALUES('$_SESSION[aalistownerID]','$thelistname','$program_name','$commission','','$admin_email_address','$logout_location','$upgradeinfo','$numurltrackersMem','$numurltrackersPro','$numurltrackersExe','$mem_sendmail_times_week','$pro_sendmail_times_week','$exe_sendmail_times_day','$cost_of_pro','$cost_of_exe','$pro_upgradeform','$exe_upgradeform','','$defaultstatus','$allowupgrades','$newmembernotice','0','0','0','0','0','0','0')");

    $_SESSION['aalistname'] = $thelistname;

    // make sure listhash is unique
		while (true)
		{
    	$listhash = substr(md5($_SESSION['aalistownerID'].$_SESSION['aalistname'].microtime().rand()), 0, 5);
    	if ($db->Query("SELECT listhash FROM listurls WHERE listhash='$listhash' LIMIT 1"))
    		continue;
    	else
    		break;
    }

    $db->Query("INSERT INTO listurls VALUES('$_SESSION[aalistownerID]','$_SESSION[aalistname]','$listhash')");

    header("Location: listcreated.php");
    exit;
  }
}
else if ($submitted=="create")
  $notValid = "Error: Missing required fields.";
else if ($submitted=="delete")
{
  $db->Query("DELETE FROM listmanager WHERE listownerID='$_SESSION[aalistownerID]' AND created='0' LIMIT 1");

  header("Location: main.php");
  exit;
}

?>
