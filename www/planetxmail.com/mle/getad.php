<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecure.inc');
require_once('/home/nulled/www/planetxmail.com/mle/aftermail.php');
require_once('/home/nulled/config.inc');

$db = new MySQL_Access('mle');

$seconds_to_wait = 7;

if ($db->Query("SELECT crediturl FROM soloads WHERE receipt != '' AND crediturl != '' AND datemailed > DATE_SUB(NOW(), INTERVAL 5 DAY) ORDER BY MD5(RAND()) LIMIT 2"))
{
  list($urlID1) = $db->FetchRow();
  list($urlID2) = $db->FetchRow();

  if ($db->Query("SELECT url FROM userlinks WHERE id='$urlID1' LIMIT 1"))
    list($url1) = $db->FetchRow();

  if ($db->Query("SELECT url FROM userlinks WHERE id='$urlID2' LIMIT 1"))
    list($url2) = $db->FetchRow();
}

$header = $div . '
  Thank You for Submitting your AD ... Please Wait ' . $seconds_to_wait . ' seconds so you can move on to mail on ...
  </div>
';
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title>Planet X Mail - After Mail Earn Credits</title>
<script type="text/javascript" src="http://freeadplanet.com/jsm.js"></script>
<script>
function uh(){if(jsm.ajax.connection.readyState==4){if(jsm.ajax.connection.status==200){jsm.byId('header').innerHTML=jsm.ajax.connection.responseText;}else{jsm.byId('header').innerHTML='<b>ERROR: Loading website failed.</b>';}}}
function bt(){setTimeout('ri()',(<?=$seconds_to_wait?> * 1000));}
function ri(){jsm.ajax.get('http://planetxmail.com/mle/aftermail.php?option=<?=$option?>&o=1',uh);}
<?php
if ($url1)
{
  echo "function ca(){d=document;if(!d.body.appendChild||!d.createElement)return;var i=d.createElement('iframe');if(!i)return;i.src='{$url1}';i.style.display='none';d.body.appendChild(i);}
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
<noscript>Javascript must be enabled to properly run this page.</noscript>
<style>
* {
  padding: 0;
  margin: 0;
}

a:link {color:#ab0000;}      /* unvisited link */
a:visited {color:#ab0000;}  /* visited link */
a:hover {color:#ab0000;}  /* mouse over link */
a:active {color:#ab0000;}  /* selected link */

.urlly {
  font-size: 14px;
  font-weight: bold;
}

#header {
  color: black;
  padding: 1px;
  height: 25px;
  width: 100%;
  border: 1px solid black;
  text-align: center;
}
</style>
</head>
<?php flush(); ?>
<body>
<div id="header">
<?=$header?>
</div>
<iframe id="content" name="content" width="100%" height="1000" frameborder="0" scrolling="auto" src="<?=$url2?>"></iframe>
</body>
</html>