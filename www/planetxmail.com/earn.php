<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

$credits_mem_to_pro = 20000;
$headers = 'From: Planet X Mail <do_not_reply@planetxmail.com>';

$h1 = '<table width="100%" height="100%"><tr><td height="100%" width="100%" bgcolor="yellow"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><b><font color="#FF0000">&nbsp;<font face="Courier New, Courier, mono">&nbsp;<b>';
$_h1 = '</b>&nbsp;<a href="http://planetxmail.com/soloads.php?list=cred" target="_blank">Send a SOLO AD to 135,000+</a></font></font></td></tr></table>';
$_h2 = '</b>&nbsp;<a href="http://targetedadplanet.com" target="_blank">New! Launch! Earn Cash/Advertise YOUR Offerings - Click Here</a></font></font></td></tr></table>';

$h2 = (mt_rand() % 2) ? $_h1 : $_h2;

// we have this here for the tor effect
if (! ctype_alnum($c.$h))
  exit($h1 . 'Parameters not alpha numeric' . $h2);
if ($e AND $t AND $db->Query("SELECT link FROM earnedlinks WHERE link='$c' LIMIT 1"))
  exit($h1 . 'This credit link was already earned.' . $h2);

$unmixup = unmixup($c);

$seed   = substr($unmixup, 0, 10);
$userID = substr($unmixup, 10, 10);
$raw    = substr($unmixup, 20);
$urlID  = substr($raw, 0, strlen($raw)-1);
$type   = substr($raw, strlen($raw)-1);

$f = 0;
if ($h != makehash($unmixup))
{
  $f = 1;
  $userlink = 'http://planetxmail.com/soloads.php?list=cred';
}
else if ($db->Query("SELECT url FROM userlinks WHERE id='$urlID' LIMIT 1"))
  list($userlink) = $db->FetchRow();

if ($e)
{
  if ($f) 
    exit($h1 . '<b>Hash check failed.</a> Make sure you copy and paste the link properly.' . $h2);

  if ($e != makehash($unmixup.$h))
    exit($h1 . 'Earn Hash check FAILED.' . $h2);

  if ($db->Query("SELECT link FROM earnedlinks WHERE link='$c' LIMIT 1"))
    exit($h1 . 'This credit link was already earned.' . $h2);

  if (! $db->Query("SELECT status, listname, listownerID, username, email, listemail FROM users WHERE userID='$userID' LIMIT 1"))
    exit($h1 . 'user ID not found.' . $h2);
  list($status, $listname, $listownerID, $username, $email, $listemail) = $db->FetchRow();

  if (! $db->Query("SELECT freeearnedcredits, proearnedcredits, exeearnedcredits FROM listconfig WHERE listownerID='$listownerID' AND listname='$listname' LIMIT 1"))
    exit($h1 . 'listowner ID or list name not found.' . $h2);
  list($mem_earned_credits, $pro_earned_credits, $exe_earned_credits) = $db->FetchRow();

       if ($status == 'mem') $earncredits = ($mem_earned_credits) ? $mem_earned_credits : 2;
  else if ($status == 'pro') $earncredits = ($pro_earned_credits) ? $pro_earned_credits : 3;
  else if ($status == 'exe') $earncredits = ($exe_earned_credits) ? $exe_earned_credits : 4;
  else exit('member status level could not be determined. Contact: <a href="http://planetxmail.com/openticket.php">Open a Ticket</a>');

  $db->Query("REPLACE INTO earnedlinks VALUES('$c', NOW())");

  if ($type == 2) // contact soload
  {
    // setting lastloggedin=NOW() so we know which users are still using the system
    $earncredits *= 10;

    system("/bin/echo '$status $earncredits' >> /home/nulled/pxm_credits_log");

    if ($email)
    {
      $db->Query("UPDATE users SET credits=credits+$earncredits, lastloggedin=NOW() WHERE email='$email'");

      if ($status == 'mem' AND $db->Query("SELECT credits, username, fname, listname, listownerID FROM users WHERE userID='$userID' LIMIT 1"))
      {
        list($creds, $username, $fname, $listname, $listownerID) = $db->FetchRow();

        if ($creds >= $credits_mem_to_pro)
        {
          $db->Query("UPDATE users SET status='pro' WHERE userID='$userID' LIMIT 1");

          if ($db->Query("SELECT listhash FROM listurls WHERE listname='$listname' AND listownerID='$listownerID' LIMIT 1"))
            list($listhash) = $db->FetchRow();

          $listlogin = 'http://planetxmail.com/mle/login.php?l=' . $listhash;

          $message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/mem_to_pro_congrats_upgrade_notice.txt');
          $message = str_replace(array('[username]','[listname]','[fname]','[credits]','[listlogin]'), 
                                 array($username,    $listname,   $fname,   $creds,     $listlogin), $message);

          @mail($email,                       'Congrats! You are now Pro', $message, $headers);
          @mail('elitescripts2000@yahoo.com', 'Congrats! You are now Pro', $message, $headers);

          exit($h1 . $earncredits . " Credits Earned. Congrats! Your Free Account is now Upgraded to Pro! {$credits_mem_to_pro} Reached!" . $h2);
        }
      }

      $msg_mem = '';
      if ($status == 'mem')
        $msg_mem = '<a href="http://planetxmail.com/what_to_do_credits.php" target="_blank">Go Pro 4 Free!</a> ';

      exit($h1 . $earncredits . ' Credits Earned! ' . $msg_mem . '<u>For All Accounts</u> matching your <b>Contact Address</b>!' . $h2);
    }
    else
    {
      $db->Query("UPDATE users SET credits=credits+$earncredits, lastloggedin=NOW() WHERE userID='$userID' LIMIT 1");

      exit($h1 . $earncredits . ' Credits Earned for User: ' . $username . ' Only. Fix your Contact Address, to Earn more.' . $h2);
    }
  }
  else // mailed from user mailers
  {
    // system("/bin/echo '$status $earncredits' >> /home/nulled/pxm_credits_log");

    $db->Query("UPDATE users SET credits=credits+$earncredits, lastloggedin=NOW() WHERE userID='$userID' LIMIT 1");
    exit($h1 . $earncredits . ' Credits Earned for User: ' . $username . ' List: ' . $listname . $h2);
  }
}

?>
<frameset rows="30,*" border="0" frameborder="1" framespacing="0">
<frame name="header" scrolling="no" noresize marginheight="1" marginwidth="1" target="main" src="http://planetxmail.com/earnframe.php?c=<?=$c?>&h=<?=$h?>&t=<?=$t?>">
<frame name="main" src="<?=$userlink?>">
</frameset>
