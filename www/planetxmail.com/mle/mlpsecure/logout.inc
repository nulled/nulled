<?php
// logout.php is called from sessionsecure.inc without going though main.php
// so we need to start the session, get config parameters (for logout location)
// then killed the session
// if the users clicked the logout menu button, the session is started via main.php
if (trim($_GET['y']) == 'timedout')
{
  $timeout_msg = 'notValid=' . urlencode('Your Session Has Timed Out.');

  session_set_cookie_params(0, '/mle', '.planetxmail.com', 0, 1);
  session_start();
}
else
  $timeout_msg = 'notValid=' . urlencode('Successfully Logged Out.');

// if session contains data, try to get list's default logout location
if (is_array($_SESSION) AND count($_SESSION) > 2)
  require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');

// set a global default logout if one not gotten from list's default
if (! $logout_location)
  $logout_location = 'http://planetxmail.com/mle/requestlists.php';

// append timeout message
if (stristr($logout_location, '.php?'))
  $logout_location .= '&' . $timeout_msg;
else
  $logout_location .= '?' . $timeout_msg;

// destroy session array, and session cookie on client
$_SESSION = array();
if (ini_get('session.use_cookies')) {
  $p = session_get_cookie_params();
  setcookie(session_name(), '', time() - 31536000, $p['path'], $p['domain'], $p['secure'], $p['httponly']);
}
@session_destroy();

// redirect
header('Location: ' . $logout_location);
exit;

?>