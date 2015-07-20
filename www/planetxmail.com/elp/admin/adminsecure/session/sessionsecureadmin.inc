<?php
session_start();

require_once('/home/nulled/www/planetxmail.com/phpsecure/register_globals.inc');

require_once('/home/nulled/www/planetxmail.com/elp/admin/adminsecure/session/adminpsk.inc');

if ($_SESSION['aaadminpsk'] != $adminpsk)
{
  header("Location: logout.php");
  exit;
}
?>