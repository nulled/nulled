<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

$db->Query("SELECT * FROM urlmanager WHERE userID='{$_SESSION['aauserID']}' ORDER BY name");

$results = $db->result;
$numurls = $db->rows;

if ($submittedaddurltracker == '1')
{
  $newurltotrack  = trim($newurltotrack);
  $newnametotrack = trim($newnametotrack);

  if (has_space($newurltotrack))          $notValid = "ERROR: URL can not have any spaces.";
  else if (! $newnametotrack)             $notValid = "ERROR: Missing Tracker name.";
  else if (! $newurltotrack)              $notValid = "ERROR: Missing URL to track.";
  else if (has_urlunsafe($newurltotrack)) $notValid = "ERROR: Url contains unsafe characters and was not added to your tracker list.";
  else if (has_space($newnametotrack))    $notValid = "ERROR: Tracker name can not have any spaces in it.";
  else if (has_weird($newnametotrack))    $notValid = "ERROR: Tracker name can only use A-Z, a-z, 0-9 or _ in the name.";
  else if (substr($newurltotrack, 0, 7) != 'http://' OR substr($newurltotrack, 0, 8) != 'https://')
    $notValid = 'ERROR: URL must start with <b>http://</b> or <b>https://</b>';
  else if ($newurltotrack == 'http://' OR $newurltotrack == 'https://')
    $notValid = 'ERROR: URL to track missing.';
  else
    require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/addurltracker.php');
}
else if ($submitteddelview == '2')
{
  require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/deleteurltracker.php');
  exit;
}
else if ($submitteddelview == '1')
{
  header('Location: main.php?option=viewurltracker');
  exit;
}

$db->Query("SELECT listemail, vacation, lastvacation FROM users WHERE userID='{$_SESSION['aauserID']}' LIMIT 1");
list($listemail, $vacation, $lastvacation) = $db->FetchRow();

$banned      = ($db->Query("SELECT count FROM bounced WHERE count > 0 AND bademail='{$listemail}' LIMIT 1")) ? 1 : 0;
$mailboxfull = ($db->Query("SELECT bademail FROM bounced WHERE bademail='{$listemail}' AND mailboxfull > 0 LIMIT 1")) ? 1 : 0;

/*
if ($listemail)
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
         urlencode('<center><h5><font color=red>You can not view URL Trackers! Your vacation switch is ON! Goto your profile to turn it off.</font></h4></center>'));
  exit;
}
else if (substr($lastvacation, 0, 1) == '2')
{
  header('Location: main.php?option=vacationnotice&notValid=' .
         urlencode('<center><h5><font color=red>You can not view URL Trackers! Your vacation switch is OFF, but you need to wait until the mext day for it to reset!</font></h4></center>'));
  exit;
}
*/

?>
