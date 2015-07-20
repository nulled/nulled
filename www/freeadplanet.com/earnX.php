<?php
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');
require_once('/home/nulled/www/freeadplanet.com/secure/classes.inc');

$log_str = '';
$current_time = time();

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

// if ($affid != '11187448') exit("We are doing upgrades... try again later.");
// exit("Maintenance Mode... stand by: un=$un seed=$seed affid=$affid urlID=$urlID type=$type raw=$raw");

$allowed_types = array(0, 1, 2, 3, 4, 5, 9);
if (! in_array($type, $allowed_types)) {
  $header = 'Type AD check failed. Make sure you copy and paste the link properly. <u>Do not try to tamper with links.</u>'.$h2;
} else if (! is_numeric($urlID)) {
  $header = 'urlID check failed. Make sure you copy and paste the link properly. <u>Do not try to tamper with links.</u>'.$h2;
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

  if ($e)
  {
    if ($hash_failed) {
      $header = 'Hash check failed. Make sure you copy and paste the link properly. <u>Do not try to tamper with urls.</u>'.$h2;
    }
    else if ($urlID_failed) {
      $header = 'urlID failed. Make sure you copy and paste the link properly. <u>Do not try to tamper with urls.</u>'.$h2;
    }
    else if ($e != make_hash($un.$h)) {
      $header = 'Earn Hash check FAILED.'.$h2;
    }
    else if ($db->Query("SELECT url FROM earnedurls WHERE url='$un' LIMIT 1")) {
      $header = 'This Credit URL has already been Earned.'.$h2;
    } 
    else if (! $db->Query("SELECT status, username, weekadcount, weekadmissed, lastearned, turingkeycount FROM users WHERE affid='$affid' LIMIT 1")) {
      $header = 'user affid not found.'.$h2;
    } 
    else 
    {
      list($status, $username, $weekadcount, $weekadmissed, $lastearned, $turingkeycount) = $db->FetchRow();
      
      $rand_num = rand(0,9);
      $rand_nums = array(1,2,3,4,5,6,7);

      // TURING TEST
      if ( ($turingkeycount AND ! turing_key_valid(500)) OR (! turing_key_valid(500) AND ! in_array($rand_num, $rand_nums, 0) AND ! $s) OR ($s AND ! turing_key_valid(500)) )
      {
        list($v, $keyfilename) = turing_key_create();

        $header = '
        <form action="http://freeadplanet.com/earnX.php" method="post">
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
        
        if ($turingkeycount)
          $db->Query("UPDATE users SET turingkeycount=0 WHERE affid='$affid' LIMIT 1");

        // prevent ad view rushing
        if ($timediff >= $earn_buffer_time)
        {
          $earncredits = 0;
          $ad_quota_txt = '';
          $weekadcount++;

          $db->Query("INSERT INTO earnedurls (url, dateearned) VALUES('$un', NOW())");

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
            @mail('elitescripts2000@yahoo.com', 'FAP - earnX.php ERROR:2', 'Should never reach line ~116 of earnX.php, yet it did.', $headers);
            die;
          }
          // -------------------- end ad view quota

          // update user.adstoday to record they clicked this ad
          if ($type == 0)      $earncredits = $earncredits * $creds_earn_regmail; // reg email ads
          else if ($type == 1) set_earned_ads($affid, $urlaffid, 'spotlight', $urlID, $db);
          else if ($type == 2) set_earned_ads($affid, $urlaffid, 'billboard', $urlID, $db);
          else if ($type == 3) set_earned_ads($affid, $urlaffid, 'targeted', $urlID, $db);
          else if ($type == 4) set_earned_ads($affid, $urlaffid, 'banner', $urlID, $db);
          else if ($type == 5) set_earned_ads($affid, $urlaffid, 'exit', $urlID, $db);
          else if ($type == 9) $earncredits = $earncredits * $creds_earn_soload; // solo email ads

          $lastearned = time();

          $db->Query("UPDATE users SET credits=credits+$earncredits, weekadcount=$weekadcount, weekadmissed=$weekadmissed, lastearned='$lastearned' WHERE affid='$affid' LIMIT 1");
          
          $log_str .= "$username earned $earncredits typead:$type";
          
          $debug_mess = "username=$username\nearncredits=$earncredits\n";

          // minus credits from ad/url owner
          if ($db->Query("SELECT status, credits FROM users WHERE affid='$urlaffid' LIMIT 1"))
          {
            list($status, $credits) = $db->FetchRow();

            if ($credits)
            {
              if ($status != 1)
              {
                if ($credits < 100) $_credits = $credits - $creds_deducted_ad_view_free;
                else {
                  $_credits = round($credits / 100);
                  $_credits = $credits - $_credits;
                }
                if ($_credits < 1) $_credits = 0;
                $db->Query("UPDATE users SET credits='$_credits' WHERE affid='$urlaffid' LIMIT 1");
              }
              else
              {
                if ($credits < 100) $_credits = $credits - $creds_deducted_ad_view_pro;
                else {
                  $_credits = round($credits / 100);
                  $_credits = $credits - $_credits;
                }
                if ($_credits < 1) $_credits = 0;
                $db->Query("UPDATE users SET credits='$_credits' WHERE affid='$urlaffid' LIMIT 1");
              }
              
              $log_str .= " - " . ($credits - $_credits) ." deducted affid:$urlaffid";
            }
          }

          // if ($username == 'soloadmin88') @mail("elitescripts2000@yahoo.com", "fap earnX.php debugger", $debug_mess, $headers);
        
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
    $header = 'Please, wait 15 seconds, to Earn your Credits. Browse the site below, in the mean time!';
  }
}

if ($log_str) fap_log($log_str);

if ($ajax_request) exit('<b>'.$header.'</b>');

$e = make_hash(unmix_link(strtoupper($u)).$h);



$parts = parse_url($userlink);
$domain = $parts['scheme'] . '://' . $parts['host'];
//die($domain);
$opts = array($parts['scheme'] =>
    array(
        max_redirects => 99
    )
);
$context  = stream_context_create($opts);
$content = file_get_contents($userlink);
$content = reltoabs($content, $domain);


?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
<title>Free AD Planet - Earn Credits</title>
<script type="text/javascript" src="jsm.js"></script>
<script type="text/javascript">
<!--
function uh(){if(jsm.ajax.connection.readyState==4){if(jsm.ajax.connection.status==200){jsm.byId('header').innerHTML=jsm.ajax.connection.responseText;}else{jsm.byId('header').innerHTML='<b>ERROR: Loading website failed.</b>';}}}
function bt(){setTimeout('ri()',15000);}
function ri(){jsm.ajax.get('http://freeadplanet.com/earnX.php?<?php echo "u=$u&h=$h&e=$e&b=$b&a=1&v=$v&tkey=$tkey"; ?>',uh);}
<?php if ( ! $s ) echo "bt();\n"; ?>
-->
</script>
<noscript>Javascript must be enabled to properly run this page.</noscript>
<style type="text/css">
body {
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
  margin: 0;
  text-align: center;
}

#content {
    padding:0;
    margin:0;
    width: auto;
    height: 800px;
    overflow: auto;
}
</style>
</head>
<?php flush(); ?>
<body>
<div id="header">
<?php echo "$header\n"; ?>
</div>
<div id="content"><?php echo $content; ?></div>
</body>
</html>
