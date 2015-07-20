<?php
set_time_limit(0);

require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access('mle');

$db->Query("SELECT bademail, reason FROM bounced WHERE count > 0 ORDER BY bademail");
while(list($e, $r) = $db->FetchRow())
{
	list($t, $domain) = explode("@", strtolower($e), 2);
	if (! $domains[$domain])
		$domains[$domain] = $r;
}

ksort($domains);

/*
echo "<pre>";
echo print_r($domains);
echo "</pre>";
*/

echo count($domains)."\n";

$i=0;
foreach ($domains as $domain => $reason)
{
	$p = popen('/usr/bin/host -t mx ' . $domain, 'r');
	$contents = trim(fread($p, 1024));
	pclose($p);

	$mxrecords = explode("\n", $contents);

	if (count($mxrecords))
	{
		$db->Query("SELECT bademail FROM bounced WHERE bademail LIKE '%@$domain'");
	  list($domains_mx[$domain][0]) = $db->FetchRow();

		foreach ($mxrecords as $mx)
		{
			if (! $mx) continue;
			// 1safelistcentral.com mail is handled by 0 1safelistcentral.com.
			list(,,,,,, $record) = explode(' ', $mx);
			$domains_mx[$domain][] = $record;
		}
	}

	$i++;
	echo "$i\n";
}

ksort($domains_mx);

echo "<pre>NOW:\n\n";
echo print_r($domains_mx);
echo "</pre>";

$arraydata = serialize($domains_mx);

/*
echo "\n\n";
echo $arraydata;
echo "\n\n";
*/

//file_put_contents('domains', $arraydata);

?>
