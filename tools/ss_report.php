<?php
include("/home/nulled/www/planetxmail.com/phpsecure/classes.inc");

$dir_path = "/home/accounts/Maildir/cur/";

if ($dir = opendir($dir_path))
{
  while($file = readdir($dir))
  {
    if ($file != "." && $file != "..")
    {
      $files[] = $file;
    }
  }

  closedir($dir);
}
else
{
  echo "Error: Unable to open dir\n";
  exit;
}

echo $files[$i]."\n";

for ($i=0; $i<count($files); $i++)
{
  $text = "";

  $fp = fopen($dir_path.$files[$i], "r");
  $text = fread($fp, filesize($dir_path.$files[$i]));
  @fclose($fp);

  if (strstr($text, "Subject: _Server_Status_"))
    list($header, $body[]) = explode("Subject: ", $text);
}

?>
<html>
<head>
<title>Server Status</title>
</head>
<body>
<table border="1" align="center">
<?php

	for ($i=0; $i<3; $i++)
	{
		echo "<tr><td><pre>".$body[$i]."</pre></td>\n";
		echo "<td><pre>".$body[$i+1]."</pre></td></tr>\n";
		$i++;
	}

?>
</table>
</body>
</html>
