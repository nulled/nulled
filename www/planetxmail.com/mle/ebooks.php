<?php
include("mlpsecure/sessionsecure.inc");
if ($_SESSION[aalistownerID]!="4032668343") exit;
?>
<html>
<head>
<title>M2Masses eBooks Download List</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<body>
<table>
<tr>
<td>
<img src="http://www.marketing2masses.com/images/title.jpg" border="0">
<h3>Download eBooks</h3>
Click on the Links to download.  The number besides each link is the size of the eBook.
<br><br>
<?php
  if ($dir = @opendir("/home/nulled/www/marketing2masses.com/ebooks"))
	{
	  while($file = readdir($dir))
	  {
	    if ($file != "." && $file != "..")
	    	$files[] = $file;
	  }
	  closedir($dir);

	  sort($files);
	  for ($i=0; $i<count($files); $i++)
	  {
		  $size = stat("/home/nulled/www/marketing2masses.com/ebooks/$files[$i]");
	    if ($size[7]) $size[7] = $size[7] / 1000;
	    list($size) = explode(".", $size[7]);
	    $size .= " k";
	    echo "<a href=\"http://www.marketing2masses.com/ebooks/$files[$i]\">$files[$i]</a> : $size<br>\n";
	  }
	}
?>
<br>
More will be added all the time, stay tuned.
</td>
</tr>
</table>
</body>
</html>