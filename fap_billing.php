#!/usr/bin/php -q
<?php
require_once('/home/nulled/www/freeadplanet.com/secure/classes.inc');
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/datefunctions.inc');

$dayOfWeek = date('D');
$day       = date('d');
$onehour   = 3600;
$oneday    = $onehour * 24;

$dayNum = $numericDays[$dayOfWeek];

$midnight = mktime(0, 0, -1, date('m'), date('d'), date('y'));
$midnight = timestamp_to_mysql_timestamp($midnight);

$headers = 'From: Free AD Planet <do_not_reply@planetxmail.com>';
$subject = 'Free AD Planet - Renewal Notice';
$message = 'Hello [fname] [lname],

Your Free AD Planet subscription is due.

Simply login and goto Profile to renew your Pro account.

Username: [username]
Password: **********

http://freeadplanet.com/?c=memberlogin

Note: We use our own subscription system, seperate from that
of any merchant account you paid with. This means nothing is
auto-billed to credit cards because, you must click through
our paylink process.

----------- During the '.$days_grace_period.' Day Grace Period ----------

Any Commissions Earned during the Grace Period, will be
calculated at the Free Member rate. However, if you manage
to re-new in time, all commissions earned during the Grace
Period will be re-calculated at the Pro Member rate.

----------- After the '.$days_grace_period.' Day Grace Period -----------

If you do not re-new your Pro Membership after '.$days_grace_period.' days,
it will automatically DOWN GRADE itself to a Free Member.

Extra ADs created that go beyond Free Member privileges
will be deleted. Purchased ADs will *not* be effected.
Commissions Earned during the Grace Period will become
permanently calculated at the Free Member rate.

You will then have a Free Member account which you can
Upgrade again at a later date, if you so choose.

-----------------------------------------------------

So, re-new now! Ensure your Pro Member benefits are
calculated and owed to you like they should!

Thank You,
http://freeadplanet.com Staff
Open a Ticket: http://freeadplanet.com/openticket.php
';

$zero_credits_message = 'Hello [fname] [lname],

Your Free AD Planet account has 0 Open Credits.

Simply login and Earn Credits to keep your ADs visible.

Username: [username]
Password: **********

http://freeadplanet.com/?c=memberlogin

For details on how the Quota system works, why it is there
and what the requirements are please visit the URL below:

http://freeadplanet.com/policies.php

--------------------------------------
This Email Alert was turned on by you.
If you wish to turn future alerts like
this off, log into your Profile and
uncheck the appropriate Email Alert
checkbox and save your Profile Settings.

Thank You,
http://freeadplanet.com Staff
Open a Ticket: http://freeadplanet.com/openticket.php
';

$drain_credits_message = 'Hello [fname] [lname],

Your Free AD Planet account has not met minimum
AD viewing Quota.  Each day you have not met Quota
requirements your account will be deducted 5 Open
Credits. Once you reach Zero Open Credits some or
all of your ADs will become invisible and not able
to be viewed by others.

Simply login and View ADs to meet Quota requirements.

Username: [username]
Password: **********

http://freeadplanet.com/?c=memberlogin

Goto your Profile in the Members area to view your
Quota status and what needs to be done. Earn Credits
and help make Free AD Planet an effective place to
Advertise!

For details on how the Quota system works, why it is there
and what the requirements are please visit the URL below:

http://freeadplanet.com/policies.php

--------------------------------------
This Email Alert was turned on by you.
If you wish to turn future alerts like
this off, log into your Profile and
uncheck the appropriate Email Alert
checkbox then save your Profile Settings.

Thank You,
http://freeadplanet.com Staff
Open a Ticket: http://freeadplanet.com/openticket.php
';

$db = new MySQL_Access('mle');

$bademails = array();
if ($db->Query("SELECT bademail FROM bounced WHERE 1 ORDER BY bademail"))
  while (list($b) = $db->FetchRow()) $bademails[] = $b;

$db->SelectDB('fap');

if ($db->Query("SELECT datelastreset FROM reset WHERE datelastreset < DATE_SUB(NOW(), INTERVAL 1 DAY)"))
{
  $db->Query("UPDATE reset SET datelastreset='$midnight' LIMIT 1");

  echo "Begin new fap_billing day midnight=$midnight\n";

  // downgrade after grace period - or mail bill
  $db->Query("SELECT email, fname, lname, username, pass, affid, datelastbilled FROM users WHERE status='2'");
  $users = $db->result;
  while (list($email, $fname, $lname, $username, $password, $affid, $datelastbilled) = mysqli_fetch_row($users))
  {
    $num_days = DateDiff(mysql_datetime_to_timestamp($datelastbilled), time(), 'd');
    $num_days = round($num_days);
    if ($num_days >= $days_grace_period)
      downgrade_member($email, $fname, $lname, $username, $password, $affid, $datelastbilled, $headers, $db);
    else
    {
      // mail bill every 3rd day
      if ($day % 3) continue;

      $mess = str_replace(array('[username]','[fname]','[lname]'),
                          array($username,    $fname,   $lname), $message);

      $header_hash = substr(sha1('jd93JdmAz3hF1' . $affid), 0, 5);
      $head = $headers . "\nX-FAP-UID X{$affid} {$header_hash} Report: http://freeadplanet.com/openticket.php";

      if ($email) @mail($email, $subject, $mess, $head);
      // @mail('elitescripts2000@yahoo.com', $subject, $mess, $headers);
      echo "affid=$affid was mailed a bill\n";
    }
  }

  // reset to status=2 - Grace Period - bill is due
  $db->Query("SELECT email, fname, lname, username, pass, affid, datelastbilled FROM users WHERE status='1'");
  $users = $db->result;
  while (list($email, $fname, $lname, $username, $password, $affid, $datelastbilled) = mysqli_fetch_row($users))
  {
    $months = DateDiff(mysql_datetime_to_timestamp($datelastbilled), time(), 'm');

    if ($months > 0)
    {
      $db->Query("UPDATE users SET status='2', datelastbilled=NOW() WHERE affid='$affid' LIMIT 1");
      echo "affid=$affid was set to status=2\n";

      $mess = str_replace(array('[username]','[fname]','[lname]'),
                          array($username,    $fname,   $lname), $message);

      $header_hash = substr(sha1('jd93JdmAz3hF1' . $affid), 0, 5);

      $head = $headers . "\nX-FAP-UID X{$affid} {$header_hash} Report: http://freeadplanet.com/openticket.php";

      if ($email) @mail($email, $subject, $mess, $head);
      // @mail('elitescripts2000@yahoo.com', $subject, $mess, $headers);
      echo "affid=$affid was mailed a bill\n";
    }
  }

  // mature commissions
  $db->Query("SELECT id, dateofsale FROM commissions WHERE matured='0'");
  $commissions = $db->result;
  while (list($id, $dateofsale) = mysqli_fetch_row($commissions))
  {
      $num_days = DateDiff(mysql_datetime_to_timestamp($dateofsale), time(), 'd');
      $num_days = round($num_days);
      if ($num_days >= $commissions_days_mature) {
        $db->Query("UPDATE commissions SET matured='1' WHERE id='$id' LIMIT 1");
        echo "commission id=$id matured=1\n";
      }
  }

  // delete expired purchased ads - except soloads
  $db->Query("SELECT id, affid, type, id_ad, datecreated FROM ad_purchased WHERE type != 'soload' ORDER BY datecreated");
  $ads = $db->result;
  while (list($id, $affid, $type, $id_ad, $datecreated) = mysqli_fetch_row($ads))
  {
    $num_days = DateDiff(mysql_datetime_to_timestamp($datecreated), time(), 'd');
      if ($num_days > $days_purchases_expire) {
        if ($id_ad) {
          if ($type == 'banner') {
        $db->Query("SELECT image FROM ad_banners WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
        list($img) = $db->FetchRow();
        if ($img) @unlink("$upload_path/$img");
        $db->Query("DELETE FROM ad_banners WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
      } else if ($type == 'billboard') {
        $db->Query("SELECT image FROM ad_billboards WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
        list($img) = $db->FetchRow();
        if ($img) @unlink("$upload_path/$img");
        $db->Query("DELETE FROM ad_billboards WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
          } else if ($type == 'spotlight') {
            $db->Query("DELETE FROM ad_spotlights WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
          }
          else if ($type == 'targeted') {
            $db->Query("DELETE FROM ad_targeted WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
          }
          else if ($type == 'exit') {
            $db->Query("DELETE FROM ad_exits WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
          }
        }

        $db->Query("DELETE FROM ad_purchased WHERE id='$id' AND affid='$affid' LIMIT 1");
        echo "affid=$affid deleted purchased ad id=$id type=$type\n";
      }
  }

  // delete unverified signups after 3 days
  $db->Query("SELECT affid, username, pass, fname, lname, email, datesignedup FROM users WHERE verified='0'");
  $result = $db->result;
  while (list($affid, $username, $pass, $fname, $lname, $email, $datesignedup) = mysqli_fetch_row($result))
  {
    $num_days = DateDiff(mysql_datetime_to_timestamp($datesignedup), time(), 'd');
    $num_days = round($num_days);

        if ($num_days > 3) {
          $db->Query("DELETE FROM users WHERE affid='$affid' LIMIT 1");
        } else {
      $hash = substr(md5(strrev(sha1($affid))), 0, 5);
      $val_url = "http://freeadplanet.com/?c=validatesignup&affid=$affid&h=$hash";
      @mail($email, 'Free AD Planet - Validate Account Notice', "Hello $fname $lname,\n\nVisit the URL below to Validate your Account.\n\n$val_url\n\nUsername: $username\nPassword: $pass\n\nRegards,\nhttp://freeadplanet.com Staff", $headers);
      //@mail('elitescripts2000@yahoo.com', 'Free AD Planet - Validate Account Notice', "Hello $fname $lname,\n\nVisit the URL below to Validate your Account.\n\n$val_url\n\nUsername: $username\nPassword: $pass\n\nRegards,\nhttp://freeadplanet.com Staff", $headers);
    }
  }

  // calculate new Quota Week
  if ($dayOfWeek == 'Mon')
  {
    echo "\n** dayOfWeek=$dayOfWeek which is new quota week\n";

    $db->Query("SELECT affid, status, weekadcount, weekadmissed FROM users WHERE verified != '0' ORDER BY affid");
    $result = $db->result;
    while (list($affid, $status, $weekadcount, $weekadmissed) = mysqli_fetch_row($result))
    {
      if ($weekadcount >= $quotaRequirement[$status] AND $weekadmissed == 0) {
        $db->Query("UPDATE users SET weekadcount='0' WHERE affid='$affid' LIMIT 1");
        echo "affid=$affid weekadcount=0\n";
      } else if ($weekadmissed < 4) { // do not allow over 4 weeks missed, otherwise users may never catch back up
        $weekadmissed = $weekadmissed + 1;
        $db->Query("UPDATE users SET weekadmissed='$weekadmissed' WHERE affid='$affid' LIMIT 1");
        echo "affid=$affid weekadmissed=weekadmissed+1\n";
      }
      else
        echo "affid=$affid quotaweek reset had no effected\n";
    }
  }

  // drain credits for those that do not meet quota
  // also run email alerts
  // reset credits_transfered to 0
  $db->Query("SELECT affid, username, pass, fname, lname, email, credits, emailalerts, status, weekadcount, weekadmissed FROM users WHERE verified != '0'");
  $result = $db->result;
  while (list($affid, $username, $pass, $fname, $lname, $email, $credits, $emailalerts, $status, $weekadcount, $weekadmissed) = mysqli_fetch_row($result))
  {
    $credit_drain = 0;

    // (week ad missed) + (today's ad requirement)
    $expected = ($weekadmissed * $quotaRequirement[$status]) + ($dayNum * $quotaDailyRequirement[$status]);
    $totalmissed = $expected - $weekadcount;

    // echo "affid=$affid - dayOfWeek=$dayOfWeek - expected=$expected - totalmissed=$totalmissed - Formula expected = ($weekadmissed * {$quotaRequirement[$status]}) + ($dayNum * {$quotaDailyRequirement[$status]});\n";

    // determine if credit drain will happen
    if ($dayOfWeek == 'Mon' OR $dayOfWeek == 'Tue' OR $dayOfWeek == 'Wed') // grace period days
    {
      // but grace period is void if passed weeks quota was not satisfied
      if ($weekadmissed)
        $credit_drain = 1;
    }
    else if ($weekadmissed)
      $credit_drain = 1;
    else if ($totalmissed > 0)
      $credit_drain = 1;

    if ($credit_drain AND $credits > 0)
    {
      $credits = $credits - $creds_deducted_daily;
      if ($credits < 1) $credits = 0;
      $db->Query("UPDATE users SET credits='$credits' WHERE affid='$affid' LIMIT 1");
      echo "affid=$affid was deducted, $creds_deducted_daily credits\n";
    }

    // mail alerts on the 15th
    if ($day % 15 OR
        $email == '' OR
        in_array($email, $bademails)) continue;

    list($alert_credits_zero, $alert_quota_unreached) = explode(',', $emailalerts);

    $look = array('[username]','[password]','[fname]','[lname]');
    $repl = array($username,$pass,$fname,$lname);

    $mess1 = str_replace($look, $repl, $zero_credits_message);
    $mess2 = str_replace($look, $repl, $drain_credits_message);

    $header_hash = substr(sha1('jd93JdmAz3hF1' . $affid), 0, 5);
    $head = $headers . "\nX-FAP-UID X{$affid} {$header_hash} Report: http://freeadplanet.com/openticket.php";

    if ($alert_credits_zero AND $credits < 1)
    {
      @mail($email, 'FAP Alert - Zero Open Credits in your Account', $mess1, $head);
      echo "affid=$affid was mailed an alert for having 0 credits\n";
    }
    else if ($alert_quota_unreached AND $credit_drain)
    {
      @mail($email, 'FAP Alert - AD View Quota not Reached for your Account', $mess2, $head);
      echo "affid=$affid was mailed an alert for not meeting quota\n";
    }
  }

  // delete orphaned banners/images.
  foreach (glob("$upload_path/*") as $filename)
  {
    $img = basename($filename);
    if ($db->Query("SELECT image FROM ad_banners WHERE image='$img'")) continue;
    if ($db->Query("SELECT image FROM ad_billboards WHERE image='$img'")) continue;
    @unlink($filename);
    echo "deleted orphaned banner=$filename\n";
  }

  // prevent earnedurls db table from growing out of control
  $db->Query("DELETE FROM earnedurls WHERE dateearned < DATE_SUB(NOW(), INTERVAL 180 DAY)");

  // reset everything else
  $db->Query("UPDATE users SET adstoday='', mailedtoday='0', credits_transfered='0' WHERE 1");

  echo "---------- FINISHED FAP_BILLING ----------\n";
}
else {
  echo "nothing done...\n";
}

?>