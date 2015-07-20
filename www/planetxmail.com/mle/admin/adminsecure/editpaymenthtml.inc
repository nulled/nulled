<?php
include("../mlpsecure/config/config.inc");
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();

if ($submitted=="1" && $_SESSION[aaadminpsk])
{
  $signuphtml  = trim($signuphtml);
  $renewalhtml = trim($renewalhtml);
  $upgradehtml = trim($upgradehtml);

  $html = $signuphtml."n!t!w_s!4!0".$renewalhtml."n!t!w_s!4!0".$upgradehtml;

  $db->Query("UPDATE listmanager SET paymenthtml='$html' WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
  $notValid = "HTML successfully updated.";
}

$db->Query("SELECT paymenthtml FROM listmanager WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($html) = $db->FetchRow();
list($signuphtml, $renewalhtml, $upgradehtml) = explode("n!t!w_s!4!0", $html);

?>