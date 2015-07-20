<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

$listname    = $_SESSION['aalistname'];
$listownerID = $_SESSION['aalistownerID'];

if (! ctype_alnum($user) OR ! $db->Query("SELECT * FROM users WHERE userID='$user' AND listname='$listname' AND listownerID='$listownerID'"))
{
  if ($_SESSION['aaadminpsk'])
    header('Location: main.php');
  else
    header('Location: mainlistowner.php');
  exit;
}

if ($todo == 'changestatus' AND $user)
{
  $db->Query("SELECT numurltrackerspro, numurltrackersexe, memsendmailweek, prosendmailweek, memsendmailcreditsweek, prosendmailcreditsweek, freestartcredits, prostartcredits, exestartcredits FROM listconfig WHERE listname='$listname' AND listownerID='$listownerID'");
  list($numurltrackerspro, $numurltrackersexe, $memsendmailweek, $prosendmailweek, $memsendmailcreditsweek, $prosendmailcreditsweek, $freestartcredits, $prostartcredits, $exestartcredits) = $db->FetchRow();

  $db->Query("UPDATE users SET status='$newstatus' WHERE userID='$user' LIMIT 1");

  $notValid = 'Member status successfully updated.';
}
else if ($todo == 'deletemember' AND $user)
{
  $db->Query("DELETE FROM urldata WHERE userID='$user'");
  $db->Query("DELETE FROM urlmanager WHERE userID='$user'");
  $db->Query("DELETE FROM users WHERE userID='$user' LIMIT 1");

  // logdate, logins, signup, mails, adminmail
  $today = date('F j, Y');
  $db->Query("INSERT INTO hitcounter (logdate, signup) VALUES('$today','-1') ON DUPLICATE KEY UPDATE signup = signup - 1");

  if ($_SESSION['aaadminpsk'])
    header('Location: main.php');
  else
    header('Location: mainlistowner.php');
  exit;
}
else if ($todo == 'changememberdata' AND $user)
{
  if ($fname AND $lname)
  {
    $fname    = trim($fname);
    $lname    = trim($lname);
    $credits  = abs(trim($credits));
    $password = trim($password);

    if ($notValid      = LengthRealname($fname)) {}
    else if ($notValid = LengthRealname($lname)) {}
    else if (! ctype_alpha($fname))                  $notValid = 'First name may only contain letters.';
    else if (! ctype_alpha($lname))                  $notValid = 'Last name may only contain letters.';
    else if (! ctype_digit($credits))                $notValid = 'Credits must be a number amount.';
    else if ($password AND ! ctype_graph($password)) $notValid = 'ERROR: Password may not contain spaces.';
    else if ($password AND strstr($password, '"'))   $notValid = 'ERROR: Password may not contain quotation marks.';
    else if ($password AND strstr($password, "'"))   $notValid = 'ERROR: Password may not contain quotation marks.';
    else if ($password AND ! ($notValid = LengthPassword($password))) {}
    else
    {
      if ($password)
      {
        $db->Query("UPDATE users SET fname='$fname', lname='$lname', credits='$credits', password=MD5('$password') WHERE userID='$user' LIMIT 1");
        $notValid = 'Member data successfully updated and Password changed.';
      }
      else
      {
        $db->Query("UPDATE users SET fname='$fname', lname='$lname', credits='$credits' WHERE userID='$user' LIMIT 1");
        $notValid = 'Member data successfully updated.';
      }
    }
  }
  else
    $notValid = 'ERROR: Missing required fields.';
}
else if ($todo == 'setimmune')
{
	$db->Query("UPDATE users SET memberpaid='$immune' WHERE userID='$user' LIMIT 1");
}
else if ($todo == 'generatetransaction')
{
	header("Location: manualtrans.php?u=$user&transtype=upgrade&s=$s");
	exit;
}
else if ($todo == 'setpaid')
{
	$db->Query("UPDATE users SET memberpaid='$paid' WHERE userID='$user' LIMIT 1");
	$notValid = 'Members PAID status updated.';
}

$db->Query("SELECT * FROM users WHERE userID='$user' LIMIT 1");
$userData = $db->FetchArray();

$numURLs = $db->Query("Select userID FROM urlmanager WHERE userID='$user' LIMIT 1");

$db->Query("SELECT listtype, paylinkparams FROM listmanager WHERE listname='$listname' AND listownerID='$listownerID'");
list($listtype, $paylinkparams) = $db->FetchRow();

list($paypal, $egold, $cbusername, $cbsignupprolink, $cbsignupexelink, $cbrenewalprolink, $cbrenewalexelink,
     $cbupgradeprolink, $cbupgradeexelink, $egoldaltpass, $checkbilling, $renewaltype) = explode('|', $paylinkparams);

if ($renewaltype == '0')      $subtype = 'Monthly';
else if ($renewaltype == '1') $subtype = 'Bi-Monthly';
else if ($renewaltype == '2') $subtype = 'Quarterly';
else if ($renewaltype == '3') $subtype = 'Yearly';
else if ($renewaltype == '4') $subtype = 'Lifetime';

$email 				= $userData['email'];
$listemail 		= $userData['listemail'];
$lastloggedin = $userData['lastloggedin'];
$vacation 		= $userData['vacation'];

if ($db->Query("SELECT count, mailboxfull FROM bounced WHERE bademail='$email' LIMIT 1"))
{
	list($count, $mailboxfull) = $db->FetchRow();

	if ($count)
		$emailbounce = 'bounce';
	else if ($mailboxfull)
		$emailbounce = 'mailboxfull';
}

if ($db->Query("SELECT count, mailboxfull FROM bounced WHERE bademail='$listemail' LIMIT 1"))
{
  list($count, $mailboxfull) = $db->FetchRow();

  if ($count)
    $listemailbounce = 'bounce';
  else if ($mailboxfull)
    $listemailbounce = 'mailboxfull';
}

$db->Query("SELECT DATEDIFF(NOW(), '$lastloggedin')");
list($numDays) = $db->FetchRow();

$vacation = ($vacation) ? 'ON' : 'OFF';

?>
