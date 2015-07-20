<?php
session_start();

if ($_SESSION['aaadminpsk'])
  $logout_location = "http://www.planetxmail.com/elp/admin/index.php";
else if ($_SESSION['aaaffpsk'] OR $aff)
  $logout_location = "http://www.planetxmail.com/elp/admin/afflogin.php";
else
  $logout_location = "http://www.planetxmail.com/elp/admin/indexelpowner.php";

session_destroy();

header("Location: $logout_location");
exit;

?>