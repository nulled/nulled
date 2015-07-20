<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/rl.inc');
//@mail('admin.email@planetxmail.com', 'rl.php', print_r($GLOBALS, 1));
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>List Account Removal Form</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
<style>
div {
  font-size: 14px;
  border: 1px solid black;
  border-radius: 10px;
  width: 500px;
  padding: 5px;
  text-align: center;
  margin: 10px auto;
}
</style>
</head>
<?php flush(); ?>
<body>
<form name="removeall" action="/mle/rl.php" method="POST">
<div>
      <img src="images/pxm_title.jpg">
      <hr />
      <h2>Unsubscribe From:<br /><b style="font-size:20px;"><?=$list?></b></h2>
      <?php if ($notValid) echo '<b class="red">' . $notValid. '</b>'; ?>
      <hr />
      <br />
      <b class="red">Unsubscribe</b> from <i><?=$list?></i> List.
      All your URL tracking, Credits and ability to Login will all disappear.
      <br /><br />
      <b>IMPORTANT,</b>
      if you wish to unsubscribe from ALL the Safelists you joined,
      you will need to Unsubscribe from them <b>All Individually.</b>
      <br /><br />

      <center>
        <a href="/mle/requestremovelinks.php" target="_blank">Click to Search All Your Accounts.</a>
        <br /><br />
        <input type="submit" class="redbutton" value="Unsubscribe from <?=$list?>" />
      </center>

      <input type="hidden" name="submitted" value="removeall" />
      <input type="hidden" name="u" value="<?=$u?>" />
      <input type="hidden" name="v" value="<?=$v?>" />

      <hr />

      All Rights Reserved &copy; 2001 - <?=date('Y')?><br />
      <a href="/mle/login.php?l=<?=$listhash?>&username=<?=$username?>" target="_blank">Login to <?=$list?></a> -
      <a href="/../openticket.php" target="_blank">Contact Support</a> -
      <a href="/mle/requestremovelinks.php" target="_blank">Find All Your Accounts</a>
</div>
</form>
</body>
</html>