<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/linkentry.inc');
//$url_hidden= '';
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>FREE LINK EXCHANGE!  Fast and Easy Exposure!</title>
<link rel="stylesheet" type="text/css" href="mle/css_mlp.css" />
<script>
function postLink(obj)
{
  obj.disabled = true;
  obj.value = 'Loading...';
  obj.form.submit();
}
secs = <?php if ($url_hidden) echo '4000'; else echo '6000'; ?>;
loca = '<?php if ($url_hidden) echo 'linkentry.php?link=' . urlencode($_GET['link']) . '&h=' . $_GET['h'] . '&d=1'; else echo 'links.php'; ?>';
function bt(){setTimeout('ri()', secs);}
function ri(){location.href=loca;}
<?php
if ($entered AND $url)
{
  echo "function ca(){var d=document;if(!d.body.appendChild||!d.createElement)return;var i=d.createElement('iframe');if(!i)return;i.src='{$url}';i.style.display='none';d.body.appendChild(i);}
window.onload=function(){bt();ca();}
";
}
else if ($entered AND ! $url)
{
  echo 'window.onload=bt;
';
}
else if ($url_hidden)
{
    echo "function ca(){var d=document;if(!d.body.appendChild||!d.createElement)return;var i=d.createElement('iframe');if(!i)return;i.src='{$url_hidden}';i.style.display='none';d.body.appendChild(i);}
window.onload=function(){bt();ca();}
";
}
?>
</script>
<style>
body {
  font-family: verdana;
  font-size: 12px;
  color: black;
  background-color: lightblue;
  text-align: left;
  padding: 0;
  border: 0px solid black;
  width: 100%;
  margin: 0;
}
.formcontent {
  border: 0px solid black;
  width: 750px;
  margin: 0 auto;
}
.formleft,
.formright {
  width: 350px;
  border: 0px solid black;
  float: left;
}
.formclear {
  clear: both;
}
.footer {
  font-size: 20px;
  width: 100%;
  text-align: center;
}
</style>
</head>
<?php flush(); ?>
<body>
<?php

    if (! $entered)
    {
      echo '<form class="formcontent" name="linkentry" action="linkentry.php" method="POST">
          <div class="formleft">
            <b>Describe your Website. 80 Characters or Less:</b><br />
            <input type="text" name="description" size="40" maxlength="80" />
          </div>
          <div class="formright">
            <b>Link/URL to your Website:</b><br />
            <input type="text" name="link" value="http://" size="30" maxlength="80" />&nbsp;<input type="button" value="Post Link" onclick="postLink(this)" />
          </div>
          <input type="hidden" name="submitted" value="postlink" />
          <input type="hidden" name="prevlink" value="' . $link . '" />
        </form>
      <div class="formclear"></div>
      ';
    }
    else
      echo '<div class="footer">Your Link was Posted! You will be Redirected to see it at the Top of Page!</div>';

?>
</body>
</html>
