<?php
session_name('PHPADMINID'); // must use the same session_name for regular and super list owner
session_set_cookie_params(0, '/mle/admin', '.planetxmail.com', 0, 1);
session_start();

require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');

if (isset($_SESSION['LAST_ACTIVITY']) AND (time() - $_SESSION['LAST_ACTIVITY']) > 21600) // 6 hours
  $_SESSION['aaadminpsk'] = '';
$_SESSION['LAST_ACTIVITY'] = time();

if ($_SESSION['aaadminpsk'] != 'hKsjO74GsbqcCos7264' OR $_SESSION['aalistownerpsk'] != 'hSk8dKdj3Hak815hFcb')
{
  header('Location: logout.php?a=aq1sw2de3');
  exit;
}

?>
