<?php
// activate user
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

if (! $u OR ! $e OR ! $v)
{
  header("Location: notfound.php?error=missing_params");
  exit;
}

$userID = trim($u);
$email  = urldecode(trim($e));
$v_chk  = trim($v);

$hash   = substr(sha1($userID.$email), 0, 5);

//$subscribelink = "http://planetxmail.com/mle/au.php?u={$userID}&email={$emailenc}&v={$hash}";

$db = new MySQL_Access('mle');

if ($v_chk == $hash)
{
  if ($db->Query("SELECT email, username, fname, lname, listname, listownerID, verified, status, referer FROM users WHERE userID='{$userID}' LIMIT 1"))
  {
    list($email, $username, $fname, $lname, $list, $id, $verified, $status, $referer) = $db->FetchRow();

    require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');

    $db->Query("SELECT listhash FROM listurls WHERE listname='$list' AND listownerID='$id' LIMIT 1");
    list($listhash) = $db->FetchRow();

    if ($verified == 'yes') {}
    else
    {
      $db->Query("UPDATE users SET verified='yes' WHERE userID='$userID' LIMIT 1");

      // send new member a sub success email
      $db->Query("SELECT fromname, adminemail, subsuccess FROM listmanager WHERE listname='$list' AND listownerID='$id' LIMIT 1");
      list($fromname, $adminemail, $message) = $db->FetchRow();

      $validator = strrev(substr(md5($userID), 0, 5));
      $usr       = strrev($userID);

      $unsublink = "http://planetxmail.com/mle/rl.php?u={$usr}&v={$validator}";
      $loginlink = "http://planetxmail.com/mle/login.php?l={$listhash}";

      $subject = "$list - New Member Confirmed";

      $message = wordwrap($message, $email_wordwrap_length);

      $message = str_replace("[login_link]", $loginlink, $message);
      $message = str_replace("[list_name]", $list, $message);
      $message = str_replace("[program_name]", $program_name, $message);
      $message = str_replace("[admin_email_address]", $adminemail, $message);
      $message = str_replace("[unsubscribe_link]", "$unsublink\n", $message);
      $message = str_replace("[user_name]", $username, $message);
      $message = str_replace("[first_name]", $fname, $message);
      $message = str_replace("[last_name]", $lname, $message);

      @mail($email, $subject, $message, "From: $fromname <do_not_reply@planetxmail.com>");

      // logdate, logins, signup, mails, adminmail
      $today = date('F j, Y');
      $db->Query("INSERT INTO hitcounter (logdate, signup) VALUES('$today', '1') ON DUPLICATE KEY UPDATE signup = signup +1");

      if ($newmembernotice)
      {
        $nummem = $db->Query("SELECT username FROM users WHERE status='mem' AND listownerID='$id' AND listname='$list' AND verified='yes'");
        $numpro = $db->Query("SELECT username FROM users WHERE status='pro' AND listownerID='$id' AND listname='$list' AND verified='yes'");
        $numexe = $db->Query("SELECT username FROM users WHERE status='exe' AND listownerID='$id' AND listname='$list' AND verified='yes'");

        $totalmembers = $nummem + $numpro + $numexe;

        // fetch referer data if needed and get user name that referered the new sign up
        $refererON = '';
        if ($db->Query("SELECT referer FROM listconfig WHERE listname='$list' AND listownerID='$id' LIMIT 1"))
          list($refererON) = $db->FetchRow();

        if ($refererON)
        {
          if ($referer)
          {
            // OLD VERSION referrer
            $parts = explode('.', $referer);
            $affid = strrev($parts[0]);
            $refereruserID = substr($affid, 0, 10);

            // NEW VERSION referrer
            if (count($parts) < 2)
            {
              $parts  = explode('|', $referer);
              $refereruserID = strrev(trim($parts[0]));
            }

            if ($db->Query("SELECT username FROM users WHERE listname='$list' AND listownerID='$id' AND userID='$refereruserID' LIMIT 1"))
              list($referer) = $db->FetchRow();

            $referer = "This New Member was referred by the Member: {$referer}";
          }
          else
            $referer = 'This Member was not referred.';
        }
        else
          $referer = 'Affiliate System is: OFF';

        $subject = "$list - New member sign up notice";

        $message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/newmembernotice.txt');

        $message = wordwrap($message, $email_wordwrap_length);

        $message = str_replace("[user_name]", $username, $message);
        $message = str_replace("[referer]", $referer, $message);
        $message = str_replace("[ipaddress]", $_SERVER['REMOTE_ADDR'], $message);
        $message = str_replace("[first_name]", $fname, $message);
        $message = str_replace("[last_name]", $lname, $message);
        $message = str_replace("[list_name]", $list, $message);
        $message = str_replace("[status]", $status, $message);
        $message = str_replace("[number_members]", $nummem, $message);
        $message = str_replace("[number_professionals]", $numpro, $message);
        $message = str_replace("[number_executives]", $numexe, $message);
        $message = str_replace("[number_total]", $totalmembers, $message);
        $message = str_replace("[date]", mysql_timestamp_to_humandatetime(timestamp_to_mysql_timestamp(time())), $message);

        if ($adminemail)
          @mail($adminemail, $subject, $message, "From: {$fromname} <do_not_reply@planetxmail.com>");

        @mail('elitescripts2000@yahoo.com', $subject, $message, "From: {$fromname} <do_not_reply@planetxmail.com>");
      }
    }
  }
  else
  {
    header("Location: notfound.php?error=user_not_found");
    exit;
  }
}
else
{
  header("Location: notfound.php?error=validator_incorrect");
  exit;
}

?>