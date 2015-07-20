<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

if (! $referer)
{
  header('Location: main.php');
  exit;
}

if ($submitted == 'affmop')
{
  $affiliatemop = trim($affiliatemop);

  if ($affiliatemop AND $notValid = EmailFormat($affiliatemop, 0)) {}
  else
    $db->Query("UPDATE users SET affiliatemop='$affiliatemop' WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
}

$db->Query("SELECT listhash FROM listurls WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}' LIMIT 1");
list($listhash) = $db->FetchRow();

$affid = strrev($_SESSION['aauserID']) . "|$listhash";

$db->Query("SELECT affiliatemop FROM users WHERE userID='{$_SESSION['aauserID']} LIMIT 1'");
list($affiliatemop) = $db->FetchRow();

$db->Query("SELECT username, datesignedup, paid, status FROM users WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}' AND referer='$affid'");
$affiliates = $db->result;

if (! $affiliatemop) $notValid = 'Warning! Your Paypal address is not set!';

if ($commission_pro) $owed_pro = $cost_of_pro * ($commission_pro / 100); else $owed_pro = 0;
if ($commission_exe) $owed_exe = $cost_of_exe * ($commission_exe / 100); else $owed_exe = 0;

$db->Query("SELECT listemail, vacation, lastvacation FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
list($listemail, $vacation, $lastvacation) = $db->FetchRow();

$banned      = ($db->Query("SELECT count FROM bounced WHERE count > 0 AND bademail='{$listemail}' LIMIT 1")) ? 1 : 0;
$mailboxfull = ($db->Query("SELECT bademail FROM bounced WHERE mailboxfull > 0 AND bademail='$listemail' LIMIT 1")) ? 1 : 0;

/*
if (! $listemail)
{
  header('Location: main.php?option=enterlistemail');
  exit;
}
else if (substr($listemail, (strlen($listemail)-11), 11) == 'unconfirmed')
{
  header('Location: main.php?option=enterlistemailunconfirmed');
  exit;
}
else if ($banned)
{
  header('Location: main.php?option=bannedmessage');
  exit;
}
else if ($mailboxfull)
{
  header('Location: main.php?option=mailboxfull');
  exit;
}
else if ($vacation)
{
  header('Location: main.php?option=vacationnotice&notValid=' .
         urlencode('<center><h5><font color=red>You can not view Affiliate Stats! Your vacation switch is ON! Goto your profile to turn it off.</font></h4></center>'));
  exit;
}
else if (substr($lastvacation, 0, 1) == '2')
{
  header('Location: main.php?option=vacationnotice&notValid=' .
         urlencode('<center><h5><font color=red>You can not view Affiliate Stats! Your vacation switch is OFF, but you need to wait until the next day for it to reset!</font></h4></center>'));
  exit;
}
*/

?>
