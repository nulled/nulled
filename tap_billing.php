#!/usr/bin/php -q
<?php

require_once('/home/nulled/www/targetedadplanet.com/secure/params.inc');
require_once('/home/nulled/www/targetedadplanet.com/secure/functions.inc');
require_once('/home/nulled/www/targetedadplanet.com/secure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/datefunctions.inc');

$dayOfWeek  = date('D'); // Mon through Sun
$dayNumWeek = date('N'); // 1 (for Monday) through 7 (for Sunday)
$onehour    = 3600;
$oneday     = $onehour * 24;

$midnight = mktime(0, 0, -1, date('m'), date('d'), date('y'));
$midnight = timestamp_to_mysql_timestamp($midnight);

$headers = 'From: ' . $site_name . ' <do_not_reply@' . $domain_name . '.com>';

$db = new MySQL_Access('tap');

if ($db->Query("SELECT lastreset FROM admin WHERE lastreset < DATE_SUB(NOW(), INTERVAL 1 DAY)"))
{
  $db->Query("UPDATE admin SET lastreset='$midnight' LIMIT 1");

  echo "Begin new {$site_abbr} Billing day midnight=$midnight\n";

  $renew_notice          = file_get_contents('/home/nulled/www/' . $domain_name . '.com/messages/renew_notice.txt');
  $validate_account      = file_get_contents('/home/nulled/www/' . $domain_name . '.com/messages/validate_account.txt');
  $zero_credits_message  = file_get_contents('/home/nulled/www/' . $domain_name . '.com/messages/zero_credits_notice.txt');
  $drain_credits_message = file_get_contents('/home/nulled/www/' . $domain_name . '.com/messages/drain_credits_notice.txt');
  $down_grade_notice     = file_get_contents('/home/nulled/www/' . $domain_name . '.com/messages/down_grade_notice.txt');

  // downgrade after grace period - or mail bill
  $db->Query("SELECT email, fname, lname, username, pass, affid, datelastbilled FROM users WHERE status='2'");
  $users = $db->result;
  while (list($email, $fname, $lname, $username, $password, $affid, $datelastbilled) = mysqli_fetch_row($users))
  {
    $num_days = DateDiff(mysql_datetime_to_timestamp($datelastbilled), time(), 'd');
    $num_days = round($num_days);
    if ($num_days >= $days_grace_period)
      downgrade_member($email, $fname, $lname, $username, $password, $affid, $datelastbilled);
    else
    {
      // 1=mon, 2=tue, 3=wed ...6=sat, 7=sun
      if ($dayNumWeek != 3 AND $dayNumWeek != 6) continue;

      $subj = $site_name . ' - Renewal Notice';

      $mess = str_replace(array('[username]','[fname]','[lname]','[domain_name]','[days_grace_period]','[site_name]'),
                          array($username,    $fname,   $lname,   $domain_name,   $days_grace_period,   $site_name),
                          $renew_notice);

      if ($email) @mail($email, $subj, $mess, $headers);

      @mail('elitescripts2000@yahoo.com', $subj, $mess, $headers);
      echo "{$site_abbr} affid:{$affid} was mailed a bill\n";
    }
  }

  // reset to status=2 - Grace Period - bill is due
  $db->Query("SELECT email, fname, lname, username, pass, affid FROM users WHERE status='1' AND datelastbilled < DATE_SUB(NOW(), INTERVAL 1 MONTH)");
  $users = $db->result;
  while (list($email, $fname, $lname, $username, $password, $affid) = mysqli_fetch_row($users))
  {
    $db->Query("UPDATE users SET status='2', datelastbilled=NOW() WHERE affid='$affid' LIMIT 1");

    $subj = $site_name . ' - Renewal Notice';

    $mess = str_replace(array('[username]','[fname]','[lname]','[domain_name]','[days_grace_period]','[site_name]'),
                        array($username,    $fname,   $lname,   $domain_name,   $days_grace_period,   $site_name),
                        $renew_notice);

    if ($email) @mail($email, $subj, $mess, $headers);

    @mail('elitescripts2000@yahoo.com', $subj, $mess, $headers);
    echo "{$site_abbr} affid={$affid} was set to status=2 and mailed a bill\n";
  }

  // mature commissions
  $db->Query("SELECT id, dateofsale FROM commissions WHERE matured='0' AND dateofsale < DATE_SUB(NOW(), INTERVAL {$commissions_days_mature} DAY)");
  $commissions = $db->result;
  while (list($id, $dateofsale) = mysqli_fetch_row($commissions))
  {
    $db->Query("UPDATE commissions SET matured='1' WHERE id='$id' LIMIT 1");
    echo "{$site_abbr} commission id:{$id} matured=1\n";
  }

  // delete expired purchased ads - except soloads
  $db->Query("SELECT id, affid, type, id_ad FROM ad_purchased WHERE type != 'soload' AND datecreated < DATE_SUB(NOW(), INTERVAL {$days_purchases_expire} DAY) ORDER BY datecreated");
  $ads = $db->result;
  while (list($id, $affid, $type, $id_ad) = mysqli_fetch_row($ads))
  {
    if ($type == 'banner')
    {
      $db->Query("SELECT image FROM ad_banners WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
      list($img) = $db->FetchRow();
      if ($img) @unlink("$upload_path/$img");
      $db->Query("DELETE FROM ad_banners WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
    }
    else if ($type == 'billboard')
    {
      $db->Query("SELECT image FROM ad_billboards WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
      list($img) = $db->FetchRow();
      if ($img) @unlink("$upload_path/$img");
      $db->Query("DELETE FROM ad_billboards WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
    }
    else if ($type == 'spotlight')
      $db->Query("DELETE FROM ad_spotlights WHERE id='$id_ad' AND affid='$affid' LIMIT 1");
    else if ($type == 'exit')
      $db->Query("DELETE FROM ad_exits WHERE id='$id_ad' AND affid='$affid' LIMIT 1");

    $_type = $type . 's'; // needs an 's', maybe one day will make ALL database and type names uniform

    $db->Query("DELETE FROM cats WHERE ad_id='{$id_ad}' AND adtype='{$_type}' AND affid='{$affid}'");
    $db->Query("DELETE FROM ad_purchased WHERE id='{$id}' AND affid='{$affid}' LIMIT 1");
    echo "{$site_abbr} affid={$affid} deleted purchased ad id={$id} type={$type}\n";
  }

  // delete unverified signups
  $db->Query("SELECT affid, username, fname, lname, email, datesignedup FROM users WHERE verified='0'");
  $result = $db->result;
  while (list($affid, $username, $fname, $lname, $email, $datesignedup) = mysqli_fetch_row($result))
  {
    $num_days = DateDiff(mysql_datetime_to_timestamp($datesignedup), time(), 'd');
    $num_days = round($num_days);

    if ($num_days > 2)
      $db->Query("DELETE FROM users WHERE affid='$affid' LIMIT 1");
    else
    {
      $hash = substr(sha1('d82Odh27dSjd' . $_affid . 'sgDjk287dskS'), 0, 5);
      $val_url = "http://{$domain_name}.com/?c=validatesignup&affid={$affid}&h={$hash}";

      $mess = str_replace(array('[fname]','[lname]','[val_url]','[username]','[domain_name]'),
                          array($fname,    $lname,   $val_url,   $username,   $domain_name),
                          $validate_account);

      @mail($email, $site_name . ' - Validate Account Notice', $mess, $headers);

    }
  }

  // calculate new Quota Week
  if ($dayOfWeek == 'Mon' AND $quota_coach)
  {
    echo "\n** {$site_abbr} dayOfWeek={$dayOfWeek} which is new quota week\n";

    $db->Query("SELECT affid, status, weekadcount, weekadmissed FROM users WHERE verified != '0' ORDER BY affid");
    $result = $db->result;
    while (list($affid, $status, $weekadcount, $weekadmissed) = mysqli_fetch_row($result))
    {
      if ($weekadcount >= $quotaRequirement[$status] AND $weekadmissed == 0)
      {
        $db->Query("UPDATE users SET weekadcount='0' WHERE affid='$affid' LIMIT 1");
        echo "{$site_abbr} affid:{$affid} weekadcount:0\n";

      }
      else if ($weekadmissed < 4)
      { // do not allow over 4 weeks missed, otherwise users may never catch back up
        $weekadmissed = $weekadmissed + 1;
        $db->Query("UPDATE users SET weekadmissed='$weekadmissed' WHERE affid='$affid' LIMIT 1");
        echo "{$site_abbr} affid:{$affid} weekadmissed=weekadmissed+1\n";
      }
      else
        echo "{$site_abbr} affid:{$affid} quotaweek reset had no effected\n";
    }
  }

  // drain credits for those that do not meet quota
  // also run email alerts
  // reset credits_transfered to 0
  $db->Query("SELECT affid, username, pass, fname, lname, email, verified, credits, emailalerts, status, weekadcount, weekadmissed FROM users WHERE credits != '0' AND verified != '0'");
  $result = $db->result;
  while (list($affid, $username, $pass, $fname, $lname, $email, $verified, $credits, $emailalerts, $status, $weekadcount, $weekadmissed) = mysqli_fetch_row($result))
  {
    $credit_drain = 0;

    if ($quota_coach)
    {
      // (week ad missed) + (today's ad requirement)
      $expected = ($weekadmissed * $quotaRequirement[$status]) + ($dayNumWeek * $quotaDailyRequirement[$status]);
      $totalmissed = $expected - $weekadcount;

      // echo "affid=$affid - dayOfWeek=$dayOfWeek - expected=$expected - totalmissed=$totalmissed - Formula expected = ($weekadmissed * {$quotaRequirement[$status]}) + ($dayNumWeek * {$quotaDailyRequirement[$status]});\n";

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
    }

    // not using quotaCoach, but credits deducted daily (regular) anyways
    // when using quotaCoach, more is deducted if quota not met

    $creds_to_deduct = ($quota_coach AND $credit_drain) ? $creds_deducted_daily : $creds_deducted_daily_regular;
    $credits = $credits - $creds_to_deduct;
    if ($credits < 0) $credits = 0;

    $db->Query("UPDATE users SET credits='{$credits}' WHERE affid='{$affid}' LIMIT 1");
    echo "{$site_abbr} affid:{$affid} deducted_credits:{$creds_to_deduct}, quota_coach:{$quota_coach}\n";

    if ($dayOfWeek != 'Mon' OR $verified != 1 OR $email == '')
      continue;

    list($alert_credits_zero, $alert_quota_unreached) = explode(',', $emailalerts);

    $look = array('[username]','[fname]','[lname]','[site_credits]','[domain_name]','[site_name]');
    $repl = array($username,    $fname,   $lname,   $site_credits,   $domain_name,   $site_name);

    $mess1 = str_replace($look, $repl, $zero_credits_message);
    $mess2 = str_replace($look, $repl, $drain_credits_message);

    $firstMail = 0;
    if ($alert_credits_zero AND $credits < 1)
    {
      @mail($email, 'Zero Open ' . $site_credits . ' in your Account', $mess1, $headers);
      $firstMail = 1;
      echo "{$site_abbr} affid:{$affid} was mailed an alert for having 0 credits\n";
    }

    if (! $firstMail AND $quota_coach AND $alert_quota_unreached AND $credit_drain)
    {
      @mail($email, $site_abbr . ' Alert - AD View Quota not Reached for your Account', $mess2, $headers);
      echo "{$site_abbr} affid:$affid was mailed an alert for not meeting quota\n";
    }
  }

  // delete orphaned banners/images.
  foreach (glob("$upload_path/*") as $filename)
  {
    $img = basename($filename);
    if ($db->Query("SELECT image FROM ad_banners WHERE image='$img'")) continue;
    if ($db->Query("SELECT image FROM ad_billboards WHERE image='$img'")) continue;
    //@unlink($filename);
    echo "{$site_abbr} Orphaned imagefile:{$filename} was detected\n";
  }

  // prevent earnedurls db table from growing out of control
  $db->Query("DELETE FROM earnedurls WHERE dateearned < DATE_SUB(NOW(), INTERVAL 180 DAY)");

  // reset everything else
  $db->Query("UPDATE users SET mailedtoday='0', credits_transfered='0' WHERE 1");

  $db->Query("UPDATE ad_banners SET clickers='' WHERE 1");
  $db->Query("UPDATE ad_billboards SET clickers='' WHERE 1");
  $db->Query("UPDATE ad_spotlights SET clickers='' WHERE 1");
  $db->Query("UPDATE ad_exits SET clickers='' WHERE 1");

  /* Done from calc_mail.php hourly, from CRON
  echo "Optimize tap Tables...";
  $db->OptimizeTables(1);
  echo "done\n";
  */

  echo "---------- FINISHED {$site_abbr}_BILLING ----------\n";
}
else {
  echo "{$site_abbr} nothing done...\n";
}

?>
