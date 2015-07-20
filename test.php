#!/usr/bin/php -q
<?php
set_time_limit(0);

$_SKIP_FORCED_REGISTER_GLOBALS = 1;

require_once('/home/nulled/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

die;

// $test = true;

$today = date('Y-m-d');

$db = new MySQL_Access('mle');

$bademails = array();
$db->Query("SELECT bademail, reason FROM bounced WHERE count > 0 AND reason LIKE '%Name service error%' ORDER BY reason");
while(list($e, $r) = $db->FetchRow()) $bademails[$e] = $r;

foreach ($bademails as $email => $reason)
{
  if ($notValid = EmailFormat($email)) echo "$email - $notValid\n";

  $db->Query("UPDATE users SET email='' WHERE email='$email'");
  $db->Query("UPDATE users SET listemail='' WHERE listemail='$email'");
  $db->Query("UPDATE listmanager SET adminemail='' WHERE adminemail='$email'");
  $db->Query("UPDATE listowner SET email='' WHERE email='$email'");
  $db->Query("UPDATE listconfig SET adminemailaddress='' WHERE adminemailaddress='$email'");

  $db->SelectDB('pxm');
  $db->Query("UPDATE orders SET email='' WHERE email='$email'");
  $db->SelectDB('fap');
  $db->Query("UPDATE users SET email='' WHERE email='$email' LIMIT 1");
  $db->SelectDB('tap');
  $db->Query("UPDATE users SET email='' WHERE email='$email' LIMIT 1");

  $db->SelectDB('mle');

  echo "$email\n";

  //usleep(600000);
}

die;

/*
$listowneremail = 'admin.email@planetxmail.com';

$headers = "From: [listname] <{$listowneremail}>";
$subject = "[listname] - Final Delete Notice - Act Soon";
$message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/deletenotice.txt');
$message = wordwrap($message, 70);
*/

$i = 1;

$total = $db->Query("SELECT userID, email, fname, username, listname, listownerID, lastloggedin FROM users
                     WHERE email = ''
                     AND listemail = ''
                     AND verified='yes'
                     AND lastloggedin < DATE_SUB(NOW(), INTERVAL 30 DAY) ORDER BY email");

$result = $db->result;
while (list($userID, $email, $fname, $username, $listname, $listownerID, $lastloggedin) = mysqli_fetch_row($result))
{
  $db->Query("DELETE FROM urldata WHERE userID='$userID'");
  $db->Query("DELETE FROM urlmanager WHERE userID='$userID'");
  $db->Query("DELETE FROM users WHERE userID='$userID' LIMIT 1");

  $db->Query("SELECT DATEDIFF(NOW(), '$lastloggedin')");
  list($numDays) = $db->FetchRow();

  // just get date and trim out the time
  list($lastloggedin) = explode(' ', $lastloggedin);

  //$db->Query("SELECT listhash FROM listurls WHERE listownerID='{$listownerID}' AND listname='{$listname}' LIMIT 1");
  //list($listhash) = $db->FetchRow();

  // login hash
  $loginlink = "http://planetxmail.com/mle/login.php?l={$listhash}";

  // enter new password hash method
  $hash    = substr(sha1($userID . 'skdH76Sdh76Ma' . $email), 0, 5);
  $enco    = urlencode($email);
  $enplink = "http://planetxmail.com/mle/enp.php?u={$userID}&v={$hash}&e={$enco}&l={$listhash}";

  // remove user hash method
  $validator = strrev(substr(md5($userID), 0, 5));
  $usr       = strrev($userID);
  $unsublink = "http://planetxmail.com/mle/rl.php?u={$usr}&v={$validator}";

  // put them on vacation and clear any saved messages
  //$db->Query("UPDATE users SET vacation='1', lastvacation=NOW(), message='', messagecredit='' WHERE userID='$userID' LIMIT 1");

  $head = str_replace('[listname]', $listname, $headers);
  $subj = str_replace('[listname]', $listname, $subject);

  $mess = str_replace(array('[user_name]','[fname]','[date_loggedin]','[login_link]','[change_password_link]','[num_days_inactive]','[remove_link]','[list_name]','[date_today]','[list_owner_email]'),
                      array($username,      $fname,  $lastloggedin,    $loginlink,     $enplink,               $numDays,            $unsublink,      $listname,      $today,        $listowneremail),
                      $message);

  echo "{$i}/{$total} - email:{$email} lastloggedin:{$lastloggedin} daysInactive:{$numDays}\n";

  //if ($test AND $i < 3) $email = $listowneremail; else exit("done\n"); // comment out this line, when ready to go live

  //@mail($email, $subj, $mess, $head);

  $i++;
  //usleep(250000);

}

?>