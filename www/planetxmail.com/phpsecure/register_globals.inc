<?php

if (stristr($_SERVER['HTTP_HOST'], 'targetedadplanet.com') OR stristr($_SERVER['SERVER_NAME'], 'targetedadplanet.com'))
  $_SKIP_FORCED_REGISTER_GLOBALS = 1;

if (! isset($_SKIP_FORCED_REGISTER_GLOBALS))
{
  $_SKIP_FORCED_REGISTER_GLOBALS = $_PARAMETERS_WERE_ESCAPED = 1;

  if (! ini_get('register_globals')) {
    foreach (array_merge($_GET, $_POST) as $key => $val) {
      global $$key;
      $$key = (get_magic_quotes_gpc() OR is_array($val)) ? $val : addslashes($val);
    }
  }
  if (! get_magic_quotes_gpc()) {
    foreach ($_POST as $key => $val) if (! is_array($val)) $_POST[$key] = addslashes($val);
    foreach ($_GET as $key => $val)  if (! is_array($val)) $_GET[$key]  = addslashes($val);
  }
}

?>