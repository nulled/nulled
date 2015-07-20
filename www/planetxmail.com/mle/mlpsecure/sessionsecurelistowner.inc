<?php
session_name('PHPADMINID'); // must use the same session_name for regular and super list owner
session_set_cookie_params(0, '/mle/admin', '.planetxmail.com', 0, 1);
session_start();

require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');

if (isset($_SESSION['LAST_ACTIVITY']) AND (time() - $_SESSION['LAST_ACTIVITY']) > 21600) // 6 hours
  $_SESSION['aalistownerpsk'] = '';
$_SESSION['LAST_ACTIVITY'] = time();

if ($_SESSION['aalistownerpsk'] != 'hSk8dKdj3Hak815hFcb')
{
  // if super admin, we logout to a different page
  $superadmin = ($_SESSION['aaadminpsk'] == 'hKsjO74GsbqcCos7264') ? '?a=aq1sw2de3' : '';

  header('Location: logout.php' . $superadmin);
  exit;
}

?>
