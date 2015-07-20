<?php
include("class.smtp.php");

$fp = fopen("domains", "r");
$domains = unserialize(fread($fp, filesize("domains")));
fclose($fp);

$smtp = new SMTP();
$smtp->do_debug = 2;

foreach ($domains as $key => $value)
{
	$email = $domains[$key][0];
	$mx    = $domains[$key][1];

	//echo "email:$email mx:$mx\n";

	echo "--->> $mx <<---\n";
	$smtp->Connect($mx, 25, 30);
	$smtp->Hello("planetxmail");
	$smtp->Mail("accounts@planetxmail.com");
	$smtp->Recipient($email);
	$smtp->Data("This is only a test.");
	$smtp->Close();
	echo "--------------------\n";
}

?>