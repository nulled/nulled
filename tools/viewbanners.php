<html>
<head>
<title>Banners</title>
</head>
<table border=0 cellspacing=5 cellpadding=0>
<?php
$i=0;
if ($dir = @opendir("/home/nulled/www/planetxmail.com/mle/admin/banners"))
{
  while($file = readdir($dir))
  {
    if ($file != "." && $file != "..")
    {
    	if ($i%2==0)
        echo "<tr><td><img src=http://www.planetxmail.com/mle/admin/banners/$file border=0></td>\n";
      else
      	echo "<td><img src=http://www.planetxmail.com/mle/admin/banners/$file border=0></td></tr>\n";

     	$i++;
    }
  }
  closedir($dir);
}
?>
</table>
</body>
</html>