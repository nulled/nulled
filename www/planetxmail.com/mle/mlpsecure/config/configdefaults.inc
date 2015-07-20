<?php

$program_name = 'Planet X Mail - SafeList Hosting';
$commission = '25|25|0';
$mletime = time();

$domainroot  = 'http://planetxmail.com/mle';

$email_wordwrap_length  = 70; // set to false or 0 to turn word wrapping off
$admin_email_address    = 'elitescripts2000@yahoo.com';
$bounceemail            = 'do_not_reply@planetxmail.com';
$fromemail              = 'do_not_reply@planetxmail.com';
$logout_location        = 'http://planetxmail.com';

$message_length         = 5000;
$paylinkhtml_length     = 20000;
$header_length          = 500;
$footer_length          = 500;
$subconfirm_length      = 2000;
$subsuccess_length      = 2000;
$unsubsuccess_length    = 2000;
$html_length            = 20000;
$email_length           = 5000;
$admin_email_length     = 5000;
$email_subject_length   = 80;
$ad_subject_length      = 100;
$ad_description_length  = 500;
$banner_size            = 30000; // size is in bytes
$banner_width           = 468;  // standard size for banners is 468 by 60
$banner_height          = 60;
$image_size             = 30000; // size is in bytes
$logo_max_width         = 468;   // standard size for banners is 468 by 60
$logo_max_height        = 60;

$numurltrackersMem = 3;
$numurltrackersPro = 5;
$numurltrackersExe = 10;

$mem_sendmail_times_week = 1;
$pro_sendmail_times_week = 3;
$exe_sendmail_times_day  = 1;

$cost_of_pro = "47.00|47.00|47.00";
$cost_of_exe = "87.00|87.00|47.00";

$defaultstatus     = 'mem'; // must be mem, pro or exe
$testmode_username = ''; // 1 or 0
$newmembernotice   = 0; // 1 or 0;
$allowupgrades     = 1; // 0 or 1  If set to 0 defaultstatus is only status allowed to signup

$pro_upgradeform = "http://www.ENTER_YOUR_DOMAIN.com/proupgrade.php";
$exe_upgradeform = "http://www.ENTER_YOUR_DOMAIN.com/exeupgrade.php";

?>