<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$unmixup = unmixup($c);
$e       = makehash($unmixup.$h);

$db = new MySQL_Access('mle');

$url = '';
if (! $db->Query("SELECT link FROM earnedlinks WHERE link='$c' LIMIT 1"))
{
  if ($db->Query("SELECT id, crediturl, datemailed FROM soloads WHERE receipt != '' AND crediturl != '' AND datemailed > DATE_SUB(NOW(), INTERVAL 5 DAY) ORDER BY MD5(RAND()) LIMIT 1"))
  {
    list($soloadID, $urlID, $datemailed) = $db->FetchRow();

    if ($db->Query("SELECT url FROM userlinks WHERE id='$urlID' LIMIT 1"))
    {
      list($url) = $db->FetchRow();

      $db->Query("INSERT INTO iframe_stats (soloadID, urlID, counter, url, datemailed, lastupdate) VALUES ('$soloadID','$urlID','1','$url','$datemailed',NOW())
                  ON DUPLICATE KEY UPDATE counter=counter+1, lastupdate=NOW()");
    }
  }
}
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Planet X Mail - Credit Earner</title>
<script>
function bt(){setTimeout('ri()', 10000);}
function ri(){location.href="http://planetxmail.com/earn.php?c=<?=$c?>&h=<?=$h?>&e=<?=$e?>";}
<?php
if ($url)
{
  echo "function ca(){if(!document.body.appendChild||!document.createElement)return;var i=document.createElement('iframe');if(!i)return;i.src='{$url}';i.style.display='none';document.body.appendChild(i);}
window.onload=function(){bt();ca();}
";
}
else
{
  echo 'window.onload = bt;
';
}
?>
</script>
</head>
<?php flush() ?>
<body bgcolor="#FFFFFF" text="#000000">
<table width="100%" border="0" cellspacing="3" cellpadding="0" align="center" valign="top" height="30">
  <tr>
    <td height="7" bgcolor="#FFFF66" width="39%">
      <font face="Verdana, Arial, Helvetica, sans-serif" size="2"><b><font color="#FF0000">&nbsp;<b>Please wait 10 seconds to earn your credits. Browse the site below in the mean time!</b></font></font>
    </td>
  </tr>
</table>
</body>
</html>