<?php

function cbValid()
{
  $key   = 'NTWS40NTWS40';
  $rcpt  = $_GET['cbreceipt'];
  $time  = $_GET['time'];
  $item  = $_GET['item'];
  $cbpop = $_GET['cbpop'];

  $xxpop = sha1("$key|$rcpt|$time|$item");
  $xxpop = strtoupper(substr($xxpop, 0, 8));

  if ($cbpop == $xxpop)
  {
    $timeallowed = (60 * 60 * 1);
    $timediff    = abs(time() - $time);

    return ($timediff > $timeallowed) ? 0 : 1;
  }
  else
    return 0;
}

?>
