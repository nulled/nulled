<?php
include("../mlpsecure/config/classes.inc");

$db = new MySQL_Access();


// get all banners
$db->Query("SELECT banner FROM banners WHERE 1 ORDER BY banner");

while (list($banner) = $db->FetchRow())
	list($tmp, $banners[]) = explode("/", $banner);



// get all ads
$db->Query("SELECT adimage FROM ads WHERE adimage!='none' ORDER BY adimage");

while (list($banner) = $db->FetchRow())
	list($tmp, $banners[]) = explode("/", $banner);



if ($dir = opendir("_signs"))
{
  while($file = readdir($dir))
  {
    if ($file != "." && $file != "..")
      $files[] = $file;
  }

  closedir($dir);
}

sort($files);

for ($i=0; $i<count($files); $i++)
{
	for ($j=0, $found=0; $j<count($banners); $j++)
	{
		if (stristr($banners[$j], $files[$i]))
		{
			$found = 1;
			break;
		}
	}

	if (! $found) echo "$files[$i]<br>\n"; # unlink("_signs/$files[$i]");

	#  echo "$files[$i]<br>\n";
}


?>
