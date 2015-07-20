<?php

// use to delete FAP members that have not logged in a long time...

require_once('/home/nulled/www/freeadplanet.com/secure/classes.inc');
require_once('/home/nulled/www/freeadplanet.com/secure/functions.inc');

$db = new MySQL_Access('fap');

$hour = 60 * 60;
$day  = $hour * 24;
$year = $day * 365;

$db->Query("SELECT username, affid, dateloggedin, datesignedup FROM users
            WHERE verified='1' AND (UNIX_TIMESTAMP(NOW()) - " . ($year * 2) . ") > UNIX_TIMESTAMP(dateloggedin) ORDER BY dateloggedin DESC");
$res = $db->result;

while(list($u, $a, $dl, $ds) = mysqli_fetch_row($res))
{
  echo "$dl, $ds\n";
  //delete_user($a, $db);
}

?>