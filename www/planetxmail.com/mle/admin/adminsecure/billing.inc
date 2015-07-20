<?php
include("../mlpsecure/datefunctions.inc");

$db->SelectDB("pxm");

if ($listname)
{
  $templistname = $_SESSION[aalistname];
  $_SESSION[aalistname] = $listname;

  $templistownername = $_SESSION[aalistownername];
  $_SESSION[aalistownername] = $listownername;
}

// orders
if ($db->Query("SELECT id, datesubmitted, paid, listtype, price, email FROM orders WHERE listownername='$_SESSION[aalistownername]' AND listname='$_SESSION[aalistname]' AND verified='yes'"))
{
  list($orderID, $datesubmitted, $paid, $type, $price, $email) = $db->FetchRow();

  $price -= 25;

  $months = DateDiff(mysql_datetime_to_timestamp($datesubmitted), time(), "m");
  $bill_started_timestamp = DateAdd(mysql_datetime_to_timestamp($datesubmitted), "m", $months);
  $date_bill_start = cDatePL($bill_started_timestamp);
  $date_next_bill = DateAdd(mysql_datetime_to_timestamp($datesubmitted), "m", 1 + $months);
  $days_next_bill = DateDiff(time(), $date_next_bill, "d");
  $days_bill_late = DateDiff($bill_started_timestamp, time(), "d");
}
// extended
else if ($db->Query("SELECT id, datesubmitted, paid, listtype, price FROM extended WHERE listownername='$_SESSION[aalistownername]' AND listname='$_SESSION[aalistname]' AND verified='yes'"))
{
  list($orderID, $datesubmitted, $paid, $type, $price) = $db->FetchRow();

  // get email from extended
  $db->Query("SELECT email FROM orders WHERE listownername='$_SESSION[aalistownername]' AND listname='$_SESSION[aalistname]'");
  list($email) = $db->FetchRow();

  $ex = "1";

  $months = DateDiff(mysql_datetime_to_timestamp($datesubmitted), time(), "m");
  $bill_started_timestamp = DateAdd(mysql_datetime_to_timestamp($datesubmitted), "m", $months);
  $date_bill_start = cDatePL($bill_started_timestamp);
  $date_next_bill = DateAdd(mysql_datetime_to_timestamp($datesubmitted), "m", 1 + $months);
  $days_next_bill = DateDiff(time(), $date_next_bill, "d");
  $days_bill_late = DateDiff($bill_started_timestamp, time(), "d");
}
// orders free
else if ($db->Query("SELECT id, datesubmitted, paid, email FROM orders WHERE listownername='$_SESSION[aalistownername]' AND listname='$_SESSION[aalistname]' AND verified='no' AND howheard LIKE 'free%'"))
{
  list($orderID, $datesubmitted, $paid, $email) = $db->FetchRow();

  $days_free_left = DateAdd(mysql_datetime_to_timestamp($datesubmitted), "m", 1);
  $days_free_left = DateDiff(time(), $days_free_left, "d");

  $paid = "free2months";
}
// extended free
else if ($db->Query("SELECT id, datesubmitted, paid FROM extended WHERE listownername='$_SESSION[aalistownername]' AND listname='$_SESSION[aalistname]' AND verified='no' AND howheard LIKE 'free%'"))
{
  list($orderID, $datesubmitted, $paid) = $db->FetchRow();

  $days_free_left = DateAdd(mysql_datetime_to_timestamp($datesubmitted), "m", 1);
  $days_free_left = DateDiff(time(), $days_free_left, "d");

  $paid = "free2months";
}
// orders cancelled but still active
else if ($db->Query("SELECT id, datesubmitted, paid FROM orders WHERE listownername='$_SESSION[aalistownername]' AND listname='$_SESSION[aalistname]' AND verified='no' AND howheard LIKE 'cancelled%'"))
  $paid = "cancelled";
// extended cancelled but still active
else if ($db->Query("SELECT id, datesubmitted, paid FROM extended WHERE listownername='$_SESSION[aalistownername]' AND listname='$_SESSION[aalistname]' AND verified='no' AND howheard LIKE 'cancelled%'"))
  $paid = "cancelled";
else
  $paid = "notlisted";

if ($listname)
{
  $_SESSION[aalistname] = $templistname;
  $_SESSION[aalistownername] = $templistownername;
}

// Get rid of decimal places
$parts = explode(".", $days_next_bill);
$days_next_bill = $parts[0];

$parts = explode(".", $days_bill_late);
$days_bill_late = $parts[0];

$parts = explode(".", $days_free_left);
$days_free_left = $parts[0];

// make abs
$days_next_bill = abs($days_next_bill);
$days_late_bill = abs($days_late_bill);

$timestr_next_bill = "$days_next_bill Day(s)";
$timestr_late_bill = "$days_bill_late Day(s)";

$db->SelectDB("mle");


?>