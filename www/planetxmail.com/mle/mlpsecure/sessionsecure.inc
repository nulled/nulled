<?php
session_set_cookie_params(0, '/mle', '.planetxmail.com', 0, 1);
session_start();

require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');

if (isset($_SESSION['LAST_ACTIVITY']) AND (time() - $_SESSION['LAST_ACTIVITY'] > 1800)) // 30 minutes
  $_SESSION['aapsk'] = '';
$_SESSION['LAST_ACTIVITY'] = time();

if ($_SESSION['aapsk'] != 'jjDK83hFsj93bvi8shHbwj')
{
  if (is_file('logout.php'))
  {
    header('Location: logout.php?y=timedout');
    exit;
  }
  else
  {
    exit('<h3>Blogger Blaster access denied.</h3> You must be logged into *any* Planet X Mail safelist in order to access the Blogger Blaster site!
    <br /><br /><b>Remember, the Blogger Blaster is 100% FREE. All that is required is an active login session with any Planet X Mail Safelist.</b>
    <br /><br /><a href="http://planetxmail.com">Click Here</a> or log into ANY Planet X Mail Safelist to access Blogger Blaster.');
  }
}

?>