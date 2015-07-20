#!/usr/bin/php -q
<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/datefunctions.inc');

function mysql_timestamp_to_humandatetime1($dt)
{
  $yr=strval(substr($dt,0,4)); $mo=strval(substr($dt,4,2)); $da=strval(substr($dt,6,2)); $hr=strval(substr($dt,8,2));
  $mi=strval(substr($dt,10,2)); $se=strval(substr($dt,12,2)); return date("Y-m-d H:i:s", mktime ($hr,$mi,$se,$mo,$da,$yr));
}

$day = date('d');
$onehour = 3600;
$oneday  = 86400;

$midnight = mktime(0, 0, -1, date('m'), date('d'), date('y'));
$midnight = timestamp_to_mysql_timestamp($midnight);

$db = new MySQL_Access('pxm');

if ($db->Query("SELECT lastmailed FROM system WHERE lastmailed < DATE_SUB(NOW(), INTERVAL 1 DAY)"))
{
  $db->Query("UPDATE system SET lastmailed='$midnight' LIMIT 1");

  $currentdate = mysql_timestamp_to_humandatetime1(timestamp_to_mysql_timestamp(time()));
  list($cyear, $cmonth, $cday, $ctime) = preg_split('/[- ]/', $currentdate);

  $today = getdate();
  $senddate = $today['month'].'/'.$today['mday'].'/'.$today['year'].' '.$today['hours'].':'.$today['minutes'].' - '.$today['weekday'];

  // reset all to paid=no
  $db->Query("SELECT datesubmitted, id FROM orders WHERE verified='yes' AND paid != 'no' AND listname != 'bulklist' AND listownername != 'PlanetXMail'");
  $orders = $db->result;
  while (list($datelastbilled, $oid) = mysqli_fetch_row($orders))
  {
    $months = DateDiff(mysql_datetime_to_timestamp($datelastbilled), time(), 'm');
    if ($months > 0)
      $db->Query("UPDATE orders SET paid='no' WHERE id='$oid'");
  }

  // Extended - reset all to paid=no
  $db->Query("SELECT datesubmitted, id FROM extended WHERE verified='yes' AND paid != '0' AND listname != 'bulklist' AND listownername != 'PlanetXMail'");
  $orders = $db->result;
  while (list($datelastbilled, $oid) = mysqli_fetch_row($orders))
  {
    $months = DateDiff(mysql_datetime_to_timestamp($datelastbilled), time(), 'm');
    if ($months > 0)
      $db->Query("UPDATE extended SET paid='0' WHERE id='$oid' LIMIT 1");
  }

  // get all that have not paid
  $subject = 'Payment Due for your Mailing List.';
  $headers = 'From: Planet X Mail <do_not_reply@planetxmail.com>';

  $message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/pxm_bill.txt');

  $db->Query("SELECT id, price, howheard, email, listtype, nummembers, listownername, listowneremail, listname, datesubmitted FROM orders WHERE verified='yes' AND paid='no' AND listownername != 'planetxmail'");
  $orders = $db->result;
  while (list($id, $price, $howheard, $email, $listtype, $nummembers, $listownername, $listowneremail, $listname, $date) = mysqli_fetch_row($orders))
  {
    if ($day % 5) continue;

    $price -= 25;

    $paylink = "http://planetxmail.com/listpayment.php?id={$id}&listtype=" . rawurlencode($listtype);

    $mess = str_replace(array('[paylink]','[listowner]', '[listtype]','[listname]','[nummembers]','[price]','[senddate]','[date]'),
                        array($paylink, $listownername,   $listtype,   $listname,   $nummembers,   $price,   $senddate,   $date),
                        $message);

    @mail($email, $subject, $mess, $headers);

    if ($email != $listowneremail)
      @mail($listowneremail, $subject, $message, $headers);
  }

  $subject = 'Payment Due for your Additional Mailing List.';
  $message = file_get_contents('/home/nulled/www/planetxmail.com/mle/messages/pxm_ebill.txt');

  // get all extended orders
  $db->Query("SELECT id, listownername, listtype, nummembers, price, datesubmitted, listname FROM extended WHERE verified='yes' AND paid='0' AND listownername != 'planetxmail'");
  $orders = $db->result;
  while (list($id, $listownername, $listtype, $nummembers, $price, $date, $listname) = mysqli_fetch_row($orders))
  {
    if ($day % 5) continue;

    $db->Query("SELECT email, listowneremail FROM orders WHERE listownername='$listownername' LIMIT 1");
    list($email, $listowneremail) = $db->FetchRow();

    $paylink = "http://planetxmail.com/listpayment.php?id={$id}&ex=1&listtype=" . rawurlencode($listtype);

    $mess = str_replace(array('[paylink]','[listowner]', '[listname]', '[listtype]','[nummembers]','[price]','[senddate]','[date]'),
                        array($paylink,  $listownername, $listname,     $listtype,   $nummembers,   $price,   $senddate,   $date),
                        $message);

    @mail($email, $subject, $mess, $headers);

    if ($email != $listowneremail)
      @mail($listowneremail, $subject, $mess, $headers);

    @mail('elitescripts2000@yahoo.com', $subject, $mess, $headers);
  }

  // mail to me over due list payments over 24 days

  $db->SelectDB('mle');

  $db->Query("SELECT username, listownerID FROM listowner WHERE username != 'demoit' AND username != 'planetxmail'");
  $listowners = $db->result;
  while (list($listownername, $listownerID) = mysqli_fetch_row($listowners))
  {
    $db->SelectDB('mle');

    $db->Query("SELECT listname FROM listmanager WHERE created='1' AND listownerID='$listownerID'");
    $lists = $db->result;

    $db->SelectDB('pxm');

    while (list($listname) = mysqli_fetch_row($lists))
    {
      $ex = $days_bill_late = 0;

      // orders
      if ($db->Query("SELECT id, datesubmitted, paid, listtype, price, email FROM orders WHERE listownername='$listownername' AND listname='$listname' AND verified='yes' AND paid='no' LIMIT 1"))
      {
        list($orderID, $datesubmitted, $paid, $type, $price, $email) = $db->FetchRow();

        $ex = 'no';

        $months = DateDiff(mysql_datetime_to_timestamp($datesubmitted), time(), 'm');
        $bill_started_timestamp = DateAdd(mysql_datetime_to_timestamp($datesubmitted), 'm', $months);
        $date_bill_start = cDatePL($bill_started_timestamp);
        $date_next_bill  = DateAdd(mysql_datetime_to_timestamp($datesubmitted), 'm', 1 + $months);
        $days_next_bill  = DateDiff(time(), $date_next_bill, 'd');
        $days_bill_late  = DateDiff($bill_started_timestamp, time(), 'd');
      }
      // extended
      else if ($db->Query("SELECT id, datesubmitted, paid, listtype, price FROM extended WHERE listownername='$listownername' AND listname='$listname' AND verified='yes' AND paid='0' LIMIT 1"))
      {
        list($orderID, $datesubmitted, $paid, $type, $price) = $db->FetchRow();

        $ex = 'yes';

        $months = DateDiff(mysql_datetime_to_timestamp($datesubmitted), time(), 'm');
        $bill_started_timestamp = DateAdd(mysql_datetime_to_timestamp($datesubmitted), 'm', $months);
        $date_bill_start = cDatePL($bill_started_timestamp);
        $date_next_bill  = DateAdd(mysql_datetime_to_timestamp($datesubmitted), 'm', 1 + $months);
        $days_next_bill  = DateDiff(time(), $date_next_bill, 'd');
        $days_bill_late  = DateDiff($bill_started_timestamp, time(), 'd');
      }

      if ($ex)
      {
        // get rid of decimal place
        list($days_bill_late) = explode('.', $days_bill_late);

        if ($days_bill_late > 24)
          $late_bill_message .= "Listownername: {$listownername}\nListname: {$listname}\nDays Over Due: {$days_bill_late}\nEx: {$ex}\nOrderID: {$orderID}\n----------------\n";
      }
    }
  }

  $today = date('F j, Y');
  if ($late_bill_message)
    @mail('elitescripts2000@yahoo.com', 'WARNING: List payment over due: ' . $today, $late_bill_message, $headers);

  /////////////////////////////////////////
  // handle billing for safelist members //
  /////////////////////////////////////////
  $db->SelectDB('mle');

  // loop each list check for do billing check
  $db->Query("SELECT paylinkparams, listownerID, listname FROM listmanager WHERE created='1'");
  $lists = $db->result;
  while (list($params, $id, $list) = mysqli_fetch_row($lists))
  {
    $parts = explode('|', $params);

    if ($parts[10])
    {
      $db->Query("SELECT userID, datelastbilled FROM users WHERE verified='yes' AND status != 'mem' AND memberpaid='1' AND listname='$list' AND listownerID='$id'");
      $users = $db->result;
      while(list($uID, $datelastbilled) = mysqli_fetch_row($users))
      {
        $months = DateDiff(mysql_datetime_to_timestamp($datelastbilled), time(), 'm');

        switch($parts[11])
        {
          case 0: // monthly
          {
            if ($months > 0)
            {
              $db->Query("UPDATE users SET memberpaid='0', datelastbilled=NOW() WHERE userID='$uID' LIMIT 1");
              $maildata .= "list: $list User: $uID paid reset to 0 - monthly\n";
            }
            break;
          }
          case 1: // bi monthly
          {
            if ($months > 1)
            {
              $db->Query("UPDATE users SET memberpaid='0', datelastbilled=NOW() WHERE userID='$uID' LIMIT 1");
              $maildata .= "list: $list User: $uID paid reset to 0 - bi monthly\n";
            }
            break;
          }
          case 2: // quarterly
          {
            if ($months > 2)
            {
              $db->Query("UPDATE users SET memberpaid='0', datelastbilled=NOW() WHERE userID='$uID' LIMIT 1");
              $maildata .= "list: $list User: $uID paid reset to 0 - quarterly\n";
            }
            break;
          }
          case 3: // yearly
          {
            if ($months > 11)
            {
              $db->Query("UPDATE users SET memberpaid='0', datelastbilled=NOW() WHERE userID='$uID' LIMIT 1");
              $maildata .= "list: $list User: $uID paid reset to 0 - yearly\n";
            }
            break;
          }
          case 4: // lifetime
            break;
          default:
            $maildata .= "list: $list User: $uID ERROR renewal type UNKNOWN: parts=$parts[11]\n";
            break;
        }
      }
    }
  }

  // prevent earnedlinks db table from growing out of control
  $db->Query("DELETE FROM earnedlinks WHERE dateearned < DATE_SUB(NOW(), INTERVAL 180 DAY)");

  /* Done from calc_mail.php hourly, from CRON
  echo "Optimize mle Tables...";
  $db->OptimizeTables(1);
  echo "done\n";
  */

  // if ($maildata) @mail('elitescripts2000@yahoo.com', 'do billing cycle '.$today, $maildata, $headers);
}
else
  echo "Already finished for today...\n";

?>