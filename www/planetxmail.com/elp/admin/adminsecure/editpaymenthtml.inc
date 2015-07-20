<?php
include("../../mle/mlpsecure/config/classes.inc");

$db = new MySQL_Access("elp");

if ($submitted=="save")
{
  $signuppaylinks = trim($signuppaylinks);
  $monthlypaylinks = trim($monthlypaylinks);

  $html = $signuppaylinks."n!t!w_s!4!0".$monthlypaylinks;

  $db->Query("UPDATE elpowners SET signuppaylinks='$signuppaylinks', monthlypaylinks='$monthlypaylinks' WHERE elpownername='$_SESSION[aaelp]ownername'");
  $notValid = "HTML successfully updated.";
}

$db->Query("SELECT signuppaylinks, monthlypaylinks FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
list($signuppaylinks, $monthlypaylinks) = $db->FetchRow();

?>