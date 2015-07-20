<?php

while(1)
{
$remcmd = "find /var/spool/postfix/active -type f -print | wc -w";
$refp = popen($remcmd, "r");
$active = trim(fread($refp, 12));
pclose($refp);

$remcmd = "find /var/spool/postfix/incoming -type f -print | wc -w";
$refp = popen($remcmd, "r");
$incoming = trim(fread($refp, 12));
pclose($refp);

$remcmd = "find /var/spool/postfix/deferred -type f -print | wc -w";
$refp = popen($remcmd, "r");
$deferred = trim(fread($refp, 12));
pclose($refp);

$remcmd = "find /var/spool/postfix/bounce -type f -print | wc -w";
$refp = popen($remcmd, "r");
$bounce = trim(fread($refp, 12));
pclose($refp);

echo "Active: $active\n";
echo "Incoming: $incoming\n";
echo "Deferred: $deferred\n";
echo "Bounce: $bounce\n\n";

sleep(2);
}

?>

