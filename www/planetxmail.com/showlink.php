<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');

$link = trim($_GET['link']);
$h    = trim($_GET['h']);
$e    = trim($_GET['entered']);

if ($e AND $link AND $h) // e = entered, which was set in linkentry.inc e, is the soloadID
{
  $vhash = substr(sha1('fK#4_b87HwZOOOg!gDDuw' . urldecode($link) . $e), 0, 5);

  if ($vhash != $h)
  {
    header('Location: links.php');
    exit;
  }
}
else
{
  $vhash = substr(sha1('fK#4_b87HwZOOOg!gDDuw' . urldecode($link)), 0, 5);

  if ($vhash != $h)
  {
    header('Location: links.php');
    exit;
  }
}

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>FREE LINK EXCHANGE!  Fast and Easy Exposure!</title>
<script>
//window.onload=function(){document.getElementById('frm').rows='50,*';}
// we do not like frame breaking, but for this we need it in order for it to work.
// this page is not ment to be shared in framed earn pages anyhow ...
//if (top.location != location) top.location.href = document.location.href;
</script>
<style>
* {
  margin: 0;
  padding: 0;
}
</style>
</head>
<?php flush(); ?>
<frameset id="frm" rows="50,*" frameborder="YES" border="1" framespacing="1">
  <frame name="topFrame" scrolling="NO" noresize src="linkentry.php?link=<?=urlencode($link)?>&entered=<?=$e?>&h=<?=$h?>">
  <frame name="mainFrame" src="<?=urldecode($link)?>">
</frameset>
</html>