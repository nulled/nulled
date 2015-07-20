<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');

$db = new MySQL_Access('mle');

$vhash = substr(sha1('fK#4_b87HwZOOOg!gDDuw' . $_GET['id']), 0, 5);

if (isset($_GET['h']) AND $vhash == trim($_GET['h']))
{
  $db->Query("SELECT link FROM links WHERE id='$id' LIMIT 1");
  list($link) = $db->FetchRow();

  $_link = urlencode($link);

  $hash = substr(sha1('fK#4_b87HwZOOOg!gDDuw' . $link), 0, 5);

  header('Location: showlink.php?link=' . $_link . '&h=' . $hash);
  exit;
}

$db->Query("SELECT id, description, link FROM links ORDER BY id DESC");
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>FREE LINK EXCHANGE!  Fast and Easy Exposure!</title>
<link rel="stylesheet" type="text/css" href="x.css" />
<script>
// we do not like frame breaking, but for this we need it in order for it to work.
// this page is not ment to be shared in framed earn pages anyhow ...
if (top.location != location) top.location.href = document.location.href;
</script>
<style>
a {
  font-size: 14px;
  text-decoration: none;
}
a:hover {
  font-size: 14px;
  text-decoration: underline;
}
body {
  margin: 10px;
  padding: 0;
  text-align: center;
  background-image:url('images/link_exchange_bg.jpg');
}
.main {
  margin: 10px auto 80px auto;
  padding: 10px;
  width: 700px;
  border: 1px solid black;
  border-radius: 10px;
}
.labelcentered {
  text-align: center;
  margin: 10px 0;
  font-size: 16px;
  font-weight: bold;
}
.listcontent {
  text-align: left;
  width: 690px;
  border: 0px solid red;
  padding: 10px;
}
.line1 {
  padding: 2px;
  background-color: #CFD7FF;
}
.line2 {
  padding: 2px;
  background-color: #EBEBEB;
}
.header {
  width: 650px;
  text-align: left;
  margin: 0 auto;
}
.footer {
}
</style>
</head>
<?php flush(); ?>
<body>
<div class="main">

      <img src="images/title_link_exchange.jpg" border="0" />
      <br />
      <a href="soloads.php?list=linkexchange" target="_blank">Solo ADs to 135,000+</a>
      <hr />

      <div class="header">
        <b>Press <u>Control + D</u> to Book Mark this page! You can come back and post again!</b>
        <br />

        The only rules are as follows.  Please do not abuse them. We do have filters in place, but if you see something
        that violates the Guide Lines, <a href="openticket.php" target="_blank">Open a Ticket</a>.
        <ol>
          <li>No Porn sites.</li>
          <li>No Anti-Govt or Anti-Religious sites.</li>
        </ol>

        <b>What Now?</b> Click any URL on the List that catches your <i>Attention</i>.
        You will then See the Web page. At the <i>Top of the Page</i> a Form Allows <u>You to enter in <i>Your own  Web Site</i></u>
        for others to View!
      </div>

      <div class="labelcentered">
        Last 30 links shown.
      </div>

      <div class="listcontent">

  <?php

    $i   = 0;
    $class1 = 'line1';
    $class2 = 'line2';

    while (list($id, $description, $link) = $db->FetchRow())
    {
      $i++;
      $cssClass = ($i % 2) ? $class1 : $class2;
      $_i = ($i < 10) ? "0$i" : $i;

      $hash = substr(sha1('fK#4_b87HwZOOOg!gDDuw' . $id), 0, 5);

      echo '<div class="'. $cssClass . '">' . $_i . ' - <a href="links.php?id=' . $id . '&h=' . $hash . '" title="' . $link . '">' . $description . '</a></div>'."\n";
    }

  ?>

  </div>

  <hr />

  <div class="footer">
    All Rights Reserved &copy;2001 - <?=date('Y')?> - <a href="openticket.php">Open a Ticket</a>
  </div>

</div>
</body>
</html>