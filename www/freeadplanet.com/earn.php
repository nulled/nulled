<?php
require_once('/home/nulled/www/freeadplanet.com/secure/classes.inc');
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');

$logging_enabled = 0;
$log_str = '';
$current_time = time();
$type_ad_name = array(0 => 'mail', 1 => 'spotlight', 2 => 'billboard', 3 => 'targeted', 4 => 'banner', 5 => 'exit', 9 => 'soload');

$userlink = 'http://planetxmail.com/soloads.php?list=fap_cred';

if ($b == '1')
  $h2 = '- <a href="javascript:void(0)" onclick="javascript:top.location.href=\'http://freeadplanet.com/?c=home\'">Back to Free AD Planet</a>';
else if ($b == '2')
  $h2 = '- <a href="javascript:void(0)" onclick="javascript:top.location.href=\'http://freeadplanet.com/members/?c=home\'">Back to Free AD Planet</a>';
else
  $h2 = '- <a href="http://planetxmail.com/soloads.php?list=fap_cred" target="_blank">Send a SOLO AD to 135,000+</a>';

$ajax_request = 0;
if ($a) $ajax_request = 1;

$un    = unmix_link(strtoupper($u));
$seed  = substr($un, 0, 10);
$affid = substr($un, 10, 8);
$raw   = substr($un, 18);
$urlID = substr($raw, 0, strlen($raw)-1);
$type  = substr($raw, strlen($raw)-1);

if ($affid == '11187448')
{
    //header("Location: http://freeadplanet.com/earnX.php?u=$u&h=$h");die;
}

// if ($affid != '11187448') exit("We are doing upgrades... try again later.");
// exit("Maintenance Mode... stand by: un=$un seed=$seed affid=$affid urlID=$urlID type=$type raw=$raw");

$allowed_types = array(0, 1, 2, 3, 4, 5, 9);
if (! in_array($type, $allowed_types)) {
  $header = 'Type AD check failed. Make sure you copy and paste the link properly. <u>Do not try to tamper with links.</u>'.$h2;
  exit('<b>'.$header.'</b>');
} else if (! is_numeric($urlID)) {
  $header = 'urlID check failed. Make sure you copy and paste the link properly. <u>Do not try to tamper with links.</u>'.$h2;
  exit('<b>'.$header.'</b>');
} else {

  $db = new MySQL_Access('fap');

  $hash_failed = $urlID_failed = 0;
  if ($h != make_hash($un)) $hash_failed = 1;
  else if ($type == 0 AND ! $db->Query("SELECT url, affid FROM urls WHERE id='$urlID' LIMIT 1"))          $urlID_failed = 1; // standard mail
  else if ($type == 1 AND ! $db->Query("SELECT url, affid FROM ad_spotlights WHERE id='$urlID' LIMIT 1")) $urlID_failed = 1; // spotlight
  else if ($type == 2 AND ! $db->Query("SELECT url, affid FROM ad_billboards WHERE id='$urlID' LIMIT 1")) $urlID_failed = 1; // billboard
  else if ($type == 3 AND ! $db->Query("SELECT url, affid FROM ad_targeted WHERE id='$urlID' LIMIT 1"))   $urlID_failed = 1; // targeted
  else if ($type == 4 AND ! $db->Query("SELECT url, affid FROM ad_banners WHERE id='$urlID' LIMIT 1"))    $urlID_failed = 1; // banner
  else if ($type == 5 AND ! $db->Query("SELECT url, affid FROM ad_exits WHERE id='$urlID' LIMIT 1"))      $urlID_failed = 1; // exit
  else if ($type == 9 AND ! $db->Query("SELECT url, affid FROM urls WHERE id='$urlID' LIMIT 1"))          $urlID_failed = 1; // soload mail
  else
    list($userlink, $urlaffid) = $db->FetchRow();

  $header = '';

  $ad_type = $type_ad_name[$type];

  if ($hash_failed) {
    $header = 'Hash check failed. Make sure you copy and paste the link properly. <u>Do not try to tamper with urls.</u>'.$h2;
  }
  else if ($urlID_failed) {
    $header = 'urlID failed. Make sure you copy and paste the link properly. <u>Do not try to tamper with urls.</u>'.$h2;
  }
  else if ($e)
  {
    // get earner's info and do a check to see if all they are doing is clicking Email ads and no other types of Ads.
    if (! $db->Query("SELECT status, username, weekadcount, weekadmissed, lastearned, mailcount, turingkeycount FROM users WHERE affid='$affid' LIMIT 1"))
      $header = 'user affid not found.'.$h2;
    else
    {
      list($status, $username, $weekadcount, $weekadmissed, $lastearned, $mailcount, $key_count) = $db->FetchRow();

      if ($type == 0 AND $mailcount > 5)
        $header = 'You must click/earn other types of ADs (from Members Area) for every 5 Email ADs you view. (Excluding Solo Ads).';
    }

    if ($e != make_hash($un.$h)) {
      $header = 'Earn Hash check FAILED.'.$h2;
    }
    else if ($db->Query("SELECT url FROM earnedurls WHERE url='$un' LIMIT 1")) {
      $header = 'This Credit URL has already been Earned.'.$h2;
    }
    else if ($header) {
      $header = $header;
    }
    else
    {
      // 5% chance of turing test
      $rand_hit = in_array(rand(0,19), array(0), 0);

      $key_valid = turing_key_valid(180);

      // TURING TEST
      if ( ! $key_valid AND ($key_count OR $s OR ($rand_hit AND ! $s)) )
      {
        list($v, $keyfilename) = turing_key_create();

        $header = '
        <form action="http://freeadplanet.com/earn.php" method="post">
        <b>Enter Turing Key: </b><img src="http://freeadplanet.com/keys/'.$keyfilename.'" border="0" /> <input type="text" name="tkey" size="4" />
        <input id="submit" type="submit" value="Get Your Credits" />

        <input type="hidden" name="v" value="'.$v.'" />
        <input type="hidden" name="u" value="'.$u.'" />
        <input type="hidden" name="h" value="'.$h.'" />
        <input type="hidden" name="e" value="'.$e.'" />
        <input type="hidden" name="b" value="'.$b.'" />
        <input type="hidden" name="a" value="0" />
        <input type="hidden" name="s" value="1" />
        </form>
        ';

        $db->Query("UPDATE users SET turingkeycount=turingkeycount+1 WHERE affid='$affid' LIMIT 1");
      }
      else
      {
        $timediff = $current_time - $lastearned;

        if ($key_count)
          $db->Query("UPDATE users SET turingkeycount=0 WHERE affid='$affid' LIMIT 1");

        // prevent ad view rushing
        if ($timediff >= $earn_buffer_time)
        {
          $earncredits = 0;
          $ad_quota_txt = '';
          $weekadcount++;

          $db->Query("REPLACE INTO earnedurls (url, dateearned) VALUES('$un', NOW())");

          // ----------------  ad view quota
          $quotaURL = '<a href="http://freeadplanet.com/policies.php" target="_blank">Quota</a>';
          $dayNum   = $numericDays[date('D')];

          $expected       = ($weekadmissed * $quotaRequirement[$status]) + ($dayNum * $quotaDailyRequirement[$status]);
          $totalmissed    = $expected - $weekadcount;
          $totalRemaining = $quotaRequirement[$status] - $weekadcount;

          // check if we need to decrease a lost week
          if ($weekadmissed > 0 AND $totalRemaining < 1)
          {
            $weekadmissed--;
            $weekadcount -= $quotaRequirement[$status];
            $earncredits  = $creds_earn_missed_week; // bonus for making a passed weekly quota
            $ad_quota_txt = ' - '.$quotaURL.' <i>Past</i> Week met! Credit bonus given! ';
          }
          else if ($weekadmissed > 0) // there are missed weeks...
          {
            $earncredits = $status ? $creds_earn_pro : $creds_earn_free;
            $ad_quota_txt = ' - Keep going to reach Weekly '.$quotaURL.'. ('.$totalRemaining.' more), plus <i>'.$weekadmissed.'</i> <i>Unmet</i> Carry Over Week(s)! ';
          }
          else if ($weekadmissed == 0 AND $weekadcount > $quotaRequirement[$status])
          {
            $earncredits = $status ? ($creds_earn_pro * 2) : ($creds_earn_free * 2); // bonus double for exceeding minimum required
            $ad_quota_txt = ' - You Exceeded the Ad Viewing '.$quotaURL.'! Credits are now Doubled! ';
          }
          else if ($weekadmissed == 0 AND $weekadcount == $quotaRequirement[$status])
          {
            $earncredits = $creds_earn_missed_week; // bonus for making quota week
            $ad_quota_txt = ' - Weekly '.$quotaURL.' has been met. Credit bonus given! ';
          }
          else if ($weekadmissed == 0 AND $weekadcount < $quotaRequirement[$status])
          {
            $earncredits = $status ? $creds_earn_pro : $creds_earn_free;
            $ad_quota_txt = ' - Keep going to reach Weekly '.$quotaURL.'. ('.$totalRemaining.' more) to get your Bonus! ';
          }
          else
          {
            @mail('elitescripts2000@yahoo.com', 'FAP - earn.php ERROR:2', 'Should never reach line ~116 of earn.php, yet it did.', $headers);
            die;
          }
          // -------------------- end ad view quota

          // update user.adstoday to record they clicked this ad
          $newmailcount = 0;
          if ($type == 0) {
            $earncredits = $earncredits * $creds_earn_regmail; // standard email
            $newmailcount = $mailcount + 1;
          }
          else if ($type == 1) set_earned_ads($affid, $urlaffid, 'spotlight', $urlID, $db);
          else if ($type == 2) set_earned_ads($affid, $urlaffid, 'billboard', $urlID, $db);
          else if ($type == 3) set_earned_ads($affid, $urlaffid, 'targeted', $urlID, $db);
          else if ($type == 4) set_earned_ads($affid, $urlaffid, 'banner', $urlID, $db);
          else if ($type == 5) set_earned_ads($affid, $urlaffid, 'exit', $urlID, $db);
          else if ($type == 9) $earncredits = $earncredits * $creds_earn_soload; // soload email

          $lastearned = time();

          //mail('elitescripts2000@yahoo.com','FAP Test', $sql);
          $db->Query("DELETE FROM ad_breakers WHERE ad_type='$ad_type' AND ad_id='$urlID'");

          $db->Query("UPDATE users SET credits=credits+$earncredits, weekadcount=$weekadcount, dateloggedin=NOW(),
                                       weekadmissed=$weekadmissed, lastearned='$lastearned', mailcount='$newmailcount'
                                       WHERE affid='$affid' LIMIT 1");

          $log_str .= "$username earned $earncredits typead:{$type_ad_name[$type]}";

          $debug_mess = "username=$username\nearncredits=$earncredits\n";

          // minus credits from ad/url owner
          if ($db->Query("SELECT username, status, credits FROM users WHERE affid='$urlaffid' LIMIT 1"))
          {
            list($urlaffuser, $status, $credits) = $db->FetchRow();

            $_credits = $creds_to_deduct = 0;

            if ($credits)
            {
              $_creds = ($status != 1) ? $creds_deducted_ad_view_free : $creds_deducted_ad_view_pro;

              if ($credits > 5000)      $creds_to_deduct = $_creds * 3;
              else if ($credits > 4500) $creds_to_deduct = $_creds * 2.5;
              else if ($credits > 4000) $creds_to_deduct = $_creds * 2;
              else if ($credits > 3500) $creds_to_deduct = $_creds * 1.5;
              else $creds_to_deduct = $_creds;

              $_credits = $credits - ceil($creds_to_deduct);

              if ($_credits < 0)
                $_credits = 0;

              if ($affid != $urlaffid AND $_credits)
                $db->Query("UPDATE users SET credits='$_credits' WHERE affid='$urlaffid' LIMIT 1");
            }

            $log_str .= " - $creds_to_deduct deducted user:$urlaffuser";

            if ($status == 0 AND $credits == 0 AND ($type != 0 AND $type != 9) )
              $log_str .= " - ERROR: user:$urlaffuser free yet showing ads!";
          }

          // if ($username == 'soloadmin88') @mail("elitescripts2000@yahoo.com", "fap earn.php debugger", $debug_mess, $headers);

          $header = $earncredits.' Credit(s) Earned - User: '.$username.$ad_quota_txt.$h2;
        } else {
          $log_str .= "throtted user:$username";
          $header = ($earn_buffer_time - $timediff).' seconds too fast. Slow down. <i>No</i> Credits Awarded! Press <b>F5</b> to try again.';
        }
      }
    }
  }
  else
  {
    // add to AD Breakers only one per person per ad id
    if (! $db->Query("SELECT id FROM ad_breakers
                                WHERE clickerID='$affid' AND ownerID='$urlaffid' AND ad_type='$ad_type' AND ad_id='$urlID' LIMIT 1"))
    {
      $db->Query("INSERT INTO ad_breakers (id, clickerID, ownerID,    ad_type,     ad_id,  dateinserted)
                                    VALUES('', '$affid', '$urlaffid', '$ad_type', '$urlID',NOW())");
    }

    $header = 'Please, wait ' . $earn_time_secs . '  seconds, to Earn your Credits. Browse the site below, in the mean time!';
  }
}

if ($log_str AND $logging_enabled) fap_log($log_str);

if ($ajax_request) exit('<b>'.$header.'</b>');

$e = make_hash(unmix_link(strtoupper($u)).$h);

// get iframe url data
$url = '';
if (! $db->Query("SELECT url FROM earnedurls WHERE url='$un' LIMIT 1"))
{
  $db->SelectDB('mle');

  if ($db->Query("SELECT id, crediturl, datemailed FROM soloads WHERE receipt != '' AND crediturl != '' AND datemailed > DATE_SUB(NOW(), INTERVAL 5 DAY) ORDER BY MD5(RAND()) LIMIT 1"))
  {
    list($soloadID, $urlID, $datemailed) = $db->FetchRow();

    if ($db->Query("SELECT url FROM userlinks WHERE id='$urlID'"))
    {
      list($url) = $db->FetchRow();

      $db->Query("INSERT INTO iframe_stats (soloadID, urlID, counter, url, datemailed, lastupdate)
                                    VALUES ('$soloadID','$urlID','1','$url','$datemailed',NOW()) ON DUPLICATE KEY UPDATE counter=counter+1, lastupdate=NOW()");
    }
  }
}

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Free AD Planet - Earn Credits</title>
<script type="text/javascript" src="jsm.js"></script>
<script type="text/javascript">
<!--
function uh(){if(jsm.ajax.connection.readyState==4){if(jsm.ajax.connection.status==200){jsm.byId('header').innerHTML=jsm.ajax.connection.responseText;}else{jsm.byId('header').innerHTML='<b>ERROR: Loading website failed.</b>';}}}
function bt(){setTimeout('ri()',(<?=$earn_time_secs?>*1000));}
function ri(){jsm.ajax.get('http://freeadplanet.com/earn.php?<?="u=$u&h=$h&e=$e&b=$b&a=1&v=$v&tkey=$tkey"?>',uh);}
<?php
if ($url)
{
  echo "function ca(){if(!document.body.appendChild||!document.createElement)return;var i=document.createElement('iframe');if(!i)return;i.src='{$url}';i.style.display='none';document.body.appendChild(i);}
window.onload=function(){bt();ca();}
";
}
else
{
  echo 'window.onload = bt;
';
}
?>
-->
</script>
<noscript>Javascript must be enabled to properly run this page.</noscript>
<style type="text/css">
* {
  padding: 0;
  margin: 0;
}

#header {
  color: black;
  padding: 2px;
  height: 30px;
  width: 100%;
  font-size: 12px;
  font-family: verdana, arial, helvetica, sans-serif;
  border: 1px solid black;
  background-color: yellow;
  text-align: center;
}
</style>
</head>
<?php flush(); ?>
<body>
<div id="header">
<?="$header\n";?>
</div>
<iframe id="content" name="content" width="100%" height="1000" frameborder="0" scrolling="auto" src="<?=$userlink;?>"></iframe>
</body>
</html>
