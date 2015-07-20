<?php
if ($a == 'aq1sw2de3')
  session_name('PHPADMINID');
else
  session_name('PHPADMINID');

session_set_cookie_params(0, '/mle/admin', '.planetxmail.com', 0, 1);
session_start();

require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');

if ($a == 'aq1sw2de3')
  $logout_location = "http://planetxmail.com/mle/admin/mleadminindexloginonly.php";
else
  $logout_location = "http://planetxmail.com/mle/admin/indexlistowner.php";

$_SESSION = array();
if (ini_get('session.use_cookies')) {
  $p = session_get_cookie_params();
  setcookie(session_name(), '', time() - 42000, $p['path'], $p['domain'], $p['secure'], $p['httponly']);
}
@session_destroy();

header("Location: {$logout_location}");
exit;

?>