#!/usr/bin/php -q
<?php

require_once('/home/nulled/config.inc');

$db = new MySQL_Access('mle');

calc_total_mail(1);

// since this is run from CRON every hour, might as well OptimizeTables ...
$db->OptimizeTables(1);

$db->SelectDB('fap');
$db->OptimizeTables(1);

$db->SelectDB('tap');
$db->OptimizeTables(1);

$db->SelectDB('pxm');
$db->OptimizeTables(1);

$db->SelectDB('webmail');
$db->OptimizeTables(1);

$db->SelectDB('blogblast');
$db->OptimizeTables(1);

$db->SelectDB('elp');
$db->OptimizeTables(1);

$db->Close();

?>