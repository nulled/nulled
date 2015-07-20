<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$notValid = '';

$db = new MySQL_Access('mle');

$db->Query("SELECT email, listemail FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
list($_email, $_listemail) = $db->FetchRow();

$ebanned = ($db->Query("SELECT count FROM bounced WHERE bademail='{$_email}' AND count > 4 LIMIT 1")) ? 'Bounced!' : '';
$efull   = ($db->Query("SELECT bademail FROM bounced WHERE bademail='{$_email}' AND mailboxfull > 0 LIMIT 1")) ? 'Over Quota!' : '';
$lbanned = ($db->Query("SELECT count FROM bounced WHERE bademail='{$_listemail}' AND count > 4 LIMIT 1")) ? 'Bounced!' : '';
$lfull   = ($db->Query("SELECT bademail FROM bounced WHERE bademail='{$_listemail}' AND mailboxfull > 0 LIMIT 1")) ? 'Over Quota!' : '';

$ebanned = ($efull) ? $efull : $ebanned;
$lbanned = ($lfull) ? $lfull : $lbanned;

if ($submitted)
{
  if ($submitted == 'delete')
  {
    if ($password AND $_SESSION['aausername'] != 'demo_account')
    {
      if (! $db->Query("SELECT password FROM users WHERE userID='{$_SESSION['aauserID']}' AND password=MD5('$password') LIMIT 1"))
        $notValid = 'ERROR: Password invalid.';
      else
      {
      	$usr = strrev($_SESSION['aauserID']);
      	$validator = strrev(substr(md5($_SESSION['aauserID']), 0, 5));
        header("Location: rl.php?u={$usr}&v={$validator}&submitted=removeall");
        exit;
      }
    }
    else
      $notValid = 'ERROR: Password missing.';
  }

  if ($fname AND $lname AND $notValid == '')
  {
    $fname = trim($fname);
    $lname = trim($lname);

    if ($passwordnew AND $passwordold)
    {
      if (! $db->Query("SELECT password FROM users WHERE userID='{$_SESSION['aauserID']}' AND password=MD5('$passwordold') LIMIT 1"))
        $notValid = 'ERROR: Old Password incorrect. No changes made to Password.';
      else if ($passwordnew != $passwordnewconfirm)
        $notValid = 'ERROR: New Passwords do not match. No changes made to Password.';
      else if (has_space($passwordnew))
        $notValid = 'ERROR: Passwords can not have any spaces. No changes made to Password.';
      else if ($notValid = LengthPassword($passwordnew)) {}
      else
        $notValid = '';
    }

    if ($notValid == '')
    {
      if ($notValid      = LengthRealname($fname)) {}
      else if ($notValid = LengthRealname($lname)) {}
      else
        $notValid = '';
    }

    if ($notValid == '')
    {
      $db->Query("SELECT vacation FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
      list($checkvacation) = $db->FetchRow();

      if (! $vacation) $vacation = '0';

      // they are turning off vacation
      if ($checkvacation == 1 AND ! $vacation)
      {
        $lastvacation = mktime(0, 0, -1, date("m"), date("d")+1, date("y"));
        $lastvacation = timestamp_to_mysql_timestamp($lastvacation);
      }
      else
        $lastvacation = 0;

      $db->Query("UPDATE users SET fname='$fname', lname='$lname', vacation='$vacation', lastvacation='$lastvacation'
                  WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");

      $notValid = 'Member data successfully updated.';

      if ($passwordnew AND $passwordold)
      {
        $db->Query("UPDATE users SET password=MD5('$passwordnew') WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
        $notValid .= ' Password was Updated to New One.';
      }
      else
        $notValid .= ' Password was Not Updated.';
    }
  }
  else if ($submitted != 'delete')
    $notValid = 'Missing required fields.  Make sure First and Last Names are entered as well.';
}

$db->Query("SELECT listhash FROM listurls WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}' LIMIT 1");
list($listhash) = $db->FetchRow();

$affid = strrev($_SESSION['aauserID']) . "|$listhash";

$db->Query("SELECT * FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
$memberdata = $db->FetchArray();

// used after member upgrades so they do not have to log in and out
$_SESSION['aastatus'] = $memberdata['status'];

$db->Query("SELECT adminemail FROM listmanager WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");
list($adminemail) = $db->FetchRow();

if ($memberdata['status'] == 'mem')
{
  $mailweekly        = $listData['memsendmailweek'];
  $mailcreditsweekly = $listData['memsendmailcreditsweek'];
}
else if ($memberdata['status'] == 'pro')
{
  $mailweekly        = $listData['prosendmailweek'];
  $mailcreditsweekly = $listData['prosendmailcreditsweek'];
}
else if ($memberdata['status'] == 'exe')
{
  $mailweekly        = 7;
  $mailcreditsweekly = 7;
}

if ($memberdata['referer'])
{
  list($uid, $lh) = explode('|', $memberdata['referer']);
  $uid = strrev($uid);

  if ($db->Query("SELECT fname, lname FROM users WHERE userID='$uid' LIMIT 1"))
  {
    list($fname, $lname) = $db->FetchRow();
    $sponsor = "$fname $lname";
  }
  else
    $sponsor = 'None';
}
else
  $sponsor = 'None';

?>
