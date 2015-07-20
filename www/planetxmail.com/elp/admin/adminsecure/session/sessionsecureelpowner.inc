<?php
session_start();

require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');

require_once('/home/nulled/www/planetxmail.com/elp/admin/adminsecure/session/elpownerpsk.inc');

if ($_SESSION['aaelpownerpsk'] != $elpownerpsk)
{
  header("Location: logout.php");
  exit;
}

?>