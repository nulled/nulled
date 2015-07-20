#!/usr/bin/php -q
<?php
set_time_limit(0);

$_SKIP_FORCED_REGISTER_GLOBALS = 1;

require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$today   = date('F j, Y');
$onehour = 3600;
$oneday  = 86400;
$email_debug = 'tap2@planetxmail.com';

echo "Start date: $today\n\n";

$db = new MySQL_Access('mle');

// check if system needs cleaning
$midnight = mktime(0, 0, -1, date('m'), date('d'), date('y'));
$midnight = timestamp_to_mysql_timestamp($midnight);

if ($db->Query("SELECT datelastreset FROM resetdate WHERE datelastreset < DATE_SUB(NOW(), INTERVAL 1 DAY)"))
{
  $db->Query("UPDATE resetdate SET datelastreset='{$midnight}' WHERE 1");

  echo "Starting pxm_resetlists.php: Updated mle.resetdate.datelastreset:{$midnight}\n";

  // turn vacation switch OFF, after set time period, to avoid 'vacation cheating'
  // (vacationing in order to not receive mail, then turn off in order to mail, this is a cheat)
  $db->Query("UPDATE users SET lastvacation='0000-00-00 00:00:00', vacation='0' WHERE lastvacation != '0000-00-00 00:00:00' AND vacation != '1' AND lastvacation < DATE_SUB(NOW(), INTERVAL 12 HOUR)");

  // reset mail week limits
  $db->Query("UPDATE users SET mailweek='0', mailcreditsweek='0', lastmailweek='{$midnight}' WHERE verified='yes' AND lastmailweek < DATE_SUB(NOW(), INTERVAL 7 DAY)");

  // reset mailing settings per user
  $db->Query("UPDATE users SET mailtoday='0', mailcreditstoday='0' WHERE verified='yes'");

  // delete unverified users after 3 days
  $db->Query("DELETE FROM users WHERE verified='no' AND datesignedup < DATE_SUB(NOW(), INTERVAL 3 DAY)");

  $db->Query("SELECT listownerID, username, email FROM listowner WHERE username != 'demoit' ORDER BY username");
  $result_owners = $db->result;
  while (list($listownerID, $listowner_username, $listowneremail_1) = mysqli_fetch_row($result_owners))
  {
    echo "Working with listowner_username:{$listowner_username} listownerID:{$listownerID}\n";

    $db->Query("SELECT listname, fromname, adminemail, subconfirm FROM listmanager WHERE created='1' AND listownerID='$listownerID' ORDER BY listname");
    $result_lists = $db->result;
    while (list($listname, $fromname, $listowneremail_2, $subconfirm) = mysqli_fetch_row($result_lists))
    {
      echo "Working with listname:{$listname}\n";

      if ($listowneremail_1)
        $listowneremail = $listowneremail_1;
      else if ($listowneremail_2)
        $listowneremail = $listowneremail_2;
      else
        $listowneremail = 'admin.email@planetxmail.com';

      $headers = "From: {$fromname} <do_not_reply@planetxmail.com>";

      $listID = "listname='{$listname}' AND listownerID='{$listownerID}'";

      $db->Query("SELECT listhash FROM listurls WHERE {$listID} LIMIT 1");
      list($listhash) = $db->FetchRow();

      $db->Query("UPDATE listconfig SET adminmailcount='0' WHERE {$listID} LIMIT 1");

      // determine if newsletter or not
      $newsletter = 1;
      if ($db->Query("SELECT paylinkparams FROM listmanager WHERE listtype='Safelist [openlist]' AND {$listID} LIMIT 1"))
      {
         $newsletter = 0;

         list($paylinkparams) = $db->FetchRow();

         list($paypal, $egold, $clickbankusername, $clickbanksignuppro, $clickbanksignupexe, $clickbankrenewalpro, $clickbankrenewalexe,
         $clickbankupgradepro, $clickbankupgradeexe, $egoldaltpass, $dobillingcheck, $renewaltype, $clickbankcgikey, $cleanmembers) =
         explode('|', $paylinkparams);
      }

      // delete members that have not logged in
      // after 3, 6, 9, 12 months or 0 = never delete
      $months_inactive = 0;
      if (! $newsletter)
      {
        switch ($cleanmembers)
        {
          case 0: $months_inactive = 0;  break;
          case 1: $months_inactive = 3;  break;
          case 2: $months_inactive = 6;  break;
          case 3: $months_inactive = 9;  break;
          case 4: $months_inactive = 12; break;
          default:
            @mail('elitescripts2000@yahoo.com',
                  "{$listname} - pxm_resetlists.php FATAL ERROR",
                  "Stagnant Members switch({$cleanmembers}) failed",
                  $headers);
        }

        if ($months_inactive)
        {
          $num_deleted = 0;
          $deleted_members = '';

          $db->Query("SELECT userID, username, status, lastloggedin FROM users WHERE {$listID} AND verified='yes' AND lastloggedin < DATE_SUB(NOW(), INTERVAL {$months_inactive} MONTH)");
          $result_delete = $db->result;
          while (list($userID, $username, $status, $lastloggedin) = mysqli_fetch_row($result_delete))
          {
            $db->Query("DELETE FROM urldata WHERE userID='$userID'");
            $db->Query("DELETE FROM urlmanager WHERE userID='$userID'");
            $db->Query("DELETE FROM users WHERE userID='$userID' LIMIT 1");

            $db->Query("SELECT DATEDIFF(NOW(), '$lastloggedin')");
            list($days_inactive) = $db->FetchRow();

            echo "DELETED username:{$username} from listname:{$listname}\n";

            $deleted_members .= "username:{$username}\nstatus:$status\nlastloggedin:{$lastloggedin}\nDays Inactive:{$days_inactive}\n\n";
            $num_deleted++;
          }

          $message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/deleted_stagnant_members.txt');

          $message = str_replace(array('[listowner_username]', '[months_inactive]', '[list_name]'),
                                 array($listowner_username,     $months_inactive,     $listname),
                                 $message);

          $message .= "\n\n" . $deleted_members;

          $subject = "{$listname} - {$num_deleted} Members Purged for Inactivity";

          if ($num_deleted)
          {
            // logdate, logins, signup, mails, adminmail
            $db->Query("INSERT INTO hitcounter (logdate, signup) VALUES('$today', '-{$num_deleted}') ON DUPLICATE KEY UPDATE signup = signup - {$num_deleted}");

            if ($listowneremail)
              @mail($listowneremail, $subject, $message, $headers);

            if ($email_debug)
              @mail($email_debug, $subject, $message, $headers);
          }
        }
      }

      // mail to unverified users
      $subject = "{$listname} - Email Confirmation Required";

      $message = str_replace(array('[list_name]','[program_name]','[admin_email_address]'),
                             array($listname,     $program_name,   $listowneremail),
                             $subconfirm);

      $message = wordwrap($message, 70);
      $message = stripslashes($message);

      $db->Query("SELECT fname, lname, userID, email, username FROM users WHERE {$listID} AND verified='no' AND datesignedup < DATE_SUB(NOW(), INTERVAL 2 DAY)");
      while (list($fname, $lname, $userID, $email, $username) = $db->FetchRow())
      {
        echo "Unverified member was mailed: userID:{$userID} username:{$username} email:{$email}\n";

        $hash = substr(sha1($userID.$email), 0, 5);
        $emailenc = urlencode($email);
        $subscribelink = "http://planetxmail.com/mle/au.php?u={$userID}&e={$emailenc}&v={$hash}";

        $mess = str_replace(array('[subscribe_link]', '[user_name]', '[first_name]', '[last_name]'),
                            array($subscribelink,     $username,      $fname,          $lname),
                            $message);

        if ($email)
          @mail($email, $subject, $mess, $headers);

        if ($email_debug)
          @mail($email_debug, $subject, $mess, $headers);
      }
/*
      // send mail to inactive members after (30-32), (60-62), (90-92), (120-122) days
      if (! $newsletter)
      {
        $bad_emails = array();
        $db->Query("SELECT bademail FROM bounced WHERE count > 0 OR mailboxfull > 0 ORDER BY bademail");
        while (list($e) = $db->FetchRow())
          $bad_emails[] = strtolower($e);

        $subject = "{$listname} - Inactivity Notice!";
        $message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/deletenotice.txt');
        $message = wordwrap($message, 70);
        $loginlink = "http://planetxmail.com/mle/login.php?l={$listhash}";

        $message = str_replace(array('[list_name]','[date_today]','[list_owner_email]'),
                               array($listname,      $today,         $listowneremail),
                               $message);

        $timetomail = '(DAYOFMONTH(NOW()) = 1 OR DAYOFMONTH(NOW()) = 9) AND lastloggedin < DATE_SUB(NOW(), INTERVAL 45))';

        $i = 0;
        $debug_message = '';

        $db->Query("SELECT userID, email, fname, username, lastloggedin FROM users WHERE email != '' AND {$listID} AND {$timetomail} ORDER BY email");
        $result = $db->result;
        while (list($userID, $email, $fname, $username, $lastloggedin) = mysqli_fetch_row($result))
        {
          if (@in_array($email, $bad_emails))
          {
            echo "Skipping mle.bounced.bademail:{$email} ...\n";
            continue;
          }

          $db->Query("SELECT DATEDIFF(NOW(), '$lastloggedin')");
          list($numDays) = $db->FetchRow();

          echo "Inactive member was mailed: userID:{$userID} email:{$email} dayslastloggin:{$numDays}\n";

          // enter new password hash method
          $hash    = substr(sha1($userID . 'skdH76Sdh76Ma' . $email), 0, 5);
          $enco    = urlencode($email);
          $enplink = "http://planetxmail.com/mle/enp.php?u={$userID}&v={$hash}&e={$enco}&l={$listhash}";

          // remove user hash method
          $validator = strrev(substr(md5($userID), 0, 5));
          $usr       = strrev($userID);
          $unsublink = "http://planetxmail.com/mle/rl.php?u={$usr}&v={$validator}";

          // put them on vacation and clear any saved messages
          $db->Query("UPDATE users SET vacation='1', lastvacation=NOW(), message='', messagecredit='' WHERE userID='$userID' LIMIT 1");

          $mess = str_replace(array('[user_name]','[fname]','[date_loggedin]','[login_link]','[change_password_link]','[num_days_inactive]','[remove_link]'),
                              array($username,      $fname,  $lastloggedin,    $loginlink,     $enplink,               $numDays,            $unsublink),
                              $message);

          if ($email)
            @mail($email, $subject, $mess, $headers);

          if ($email_debug) @mail($email_debug, $subject, $mess, $headers);

          $debug_message .= "username:{$username}\nlastloggedin:{$lastloggedin}\ntoday:{$today} dayslastloggin:{$numDays}\n\n";
          $i++;

          usleep(250000);
        }

        if ($debug_message AND $email_debug)
          @mail($email_debug, $subject . ' num:' . $i, trim($debug_message), $headers);
        /////// END SEND mail to inactive members ///////
      }
*/
    }
  }

  // save to master ip table that skips the dups
  echo "Updating mle.iptotal\n";
  $db->Query("SELECT ip FROM ips WHERE 1");
  while (list($ip) = $db->FetchRow())
    $db->Query("INSERT IGNORE INTO iptotal VALUES('{$ip}')");

  echo "TRUNCATE TABLE ips\n";
  $db->Query("TRUNCATE TABLE ips");

/* Done from calc_mail.php hourly, from CRON
  echo "Optimize mle Tables...";
  $db->OptimizeTables(1);
  echo "done\n";
*/
}
else
  echo "Already updated for today...\n";

?>