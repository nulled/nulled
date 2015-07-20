<?php

// This config file is read/include() every nth $ping_mod second to reload/change a config setting

$time_max          = (60 * 60 * 3); // can be used to also kill_procbounce when you need to
$ping_mod          = 5;             // every nth second will ping (check for config changes,
$u_seconds         = 250000;        // microseconds to wait for output from tail -f mail.log
$save_mail_log     = true;         // appends mail.log in /root before rm -rfing it
$echo_query        = false;         // 0 or 1 log SQL INSERT
$OK_250_TXT        = '+';           // indicator when message was sent OK, if '' a default will be printed
$CYCLE_TXT         = '';            // indicator showing how fast the while loop is looping
$size_log          = 100;           // in megabytes

?>