<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/login.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title><?=$program_name?> - Login</title>
<script>
function submitOnce(obj)
{
  obj.disabled = true;
  obj.value = 'Loading...';
  obj.form.submit();
}
</script>
<style>
body {
  text-align: center;
  font-family: Verdana;
  font-size: 14px;
}
.main {
  width: 500px;
  padding: 15px 0;
  margin: 30px auto;
  border: 1px solid black;
  border-radius: 10px;
}
.title {
  background-color: #F9ECC5;
  margin: 0 auto;
  font-size: 20px;
  padding: 6px;
}
.listname {
  font-size: 26px;
  font-weight: bold;
}
.notValid {
  padding: 5px;
  font-size: 16px;
  border-radius: 10px;
  width: 400px;
  border: 1px solid red;
  margin: 15px auto 0 auto;
  background-color: pink;
}
.warning {
  color: red;
  font-weight: bold;
}
.mailer {
  font-weight: bold;
}
.username,
.password,
.turingkey,
.forgotpassword {
  font-size: 18px;
}
.loginfooter {
  font-size: 12px;
  text-align: left;
  padding: 5px;
  margin: 15px 5%;
  border: 1px solid #778899;
  border-radius: 10px;
}
input {
  color: #000000;
  font-size: 16px;
  background-image: url(../images/input.jpg);
  background-repeat: repeat-y;
  border: 1px solid #778899;
  padding: 5px;
  text-align: left;
}
</style>
</head>
<?php flush(); ?>
<body>
<div class="main">

    <img src="<?php if ($titleIMG) echo "admin/$titleIMG"; else echo "images/title.gif"; ?>" border="0" />

    <?php

    if ($bannerIMG) echo '<div class="image_banner"><a href="' . $bannerLINK . '" target="_blank"><img src="admin/' . $bannerIMG . '" border="0" /></a></div>'."\n";

    ?>

    <div class="title">
      Login
      <br />
      <div class="listname"><?=$list?></div>
    </div>

    <?php if ($notValid) echo '<div class="notValid">' . $notValid . '</div>'; ?>

    <form class="loginform" name="login" action="login.php" method="POST">
      <br />
      <div class="username">Username</div>

      <input type="text" name="username" value="<?=$username?>" />
      <br /><br />
      <div class="password">Password</div>

      <input type="password" name="password" />
      <br /><br />
      <div class="turingkey">Enter Key Below:</div>

      <img src="http://planetxmail.com/mle/keyimages/<?=$turingkey->keyfilename?>" border="0" />
      <input type="text" name="key" size="2" maxlength="4" autocomplete="off" />

      <input type="hidden" name="submitted" value="login" />
      <input type="hidden" name="l" value="<?=$l?>" />
      <input type="hidden" name="list" value="<?=$list?>" />
      <input type="hidden" name="id" value="<?=$id?>" />
      <input type="hidden" name="validate" value="<?=$turingkey->validate?>" />
      <input type="hidden" name="evalidate" />
      <input type="hidden" name="login_failure_link" value="<?=$login_failure_link?>" />
      <br /><br />
      <input type="submit" value="Log-In" onclick="submitOnce(this)" />
    </form>
<!--
    <div class="loginfooter">
      <span class="warning">Friendly Warning:</span> There are now websites that claim to be <span class="mailer">"Viral Mailers"</span>
        that once you get on their list, will Spam you to no end. ANY Website that ONLY accepts a Gmail account should
        put you on <span class="warning">High Alert</span> that they will Spam you, even if you Unsubscribe.
    </div>
-->
    <br />
    <input type="button" value="Request ALL Your Log-In URLs" onClick="location.href='requestlogins.php'">
    <br /><br />
    <input type="button" value="Request ALL Unsubscribe URLs" onClick="location.href='requestremovelinks.php'">
    <br /><br />
    <hr />
    <form name="lostpassword" action="login.php" method="POST">

    <div class="forgotpassword">Forget your password?</div>
    <br />
    <b>Contact Email Address</b>
    <br />
    <input type="text" name="email" value="<?=$email?>" size="35" maxlength="100" />
    <br />

    <input type="hidden" name="submitted" value="lostpassword" />
    <input type="hidden" name="l" value="<?=$l?>" />
    <input type="hidden" name="list" value="<?=$list?>" />
    <input type="hidden" name="id" value="<?=$id?>" />
    <br />
    <input type="submit" value="Request Password" onclick="submitOnce(this)" />
  </form>
</div>
<script>
document.forms[0].username.focus();
</script>

<script type="text/javascript" src="http://edge.quantserve.com/quant.js"></script>
<script type="text/javascript">
_qacct="p-a26V9rP8NfTY2";quantserve();</script>
<noscript>
<img src="http://pixel.quantserve.com/pixel/p-a26V9rP8NfTY2.gif" style="display: none" height="1" width="1" alt="Quantcast"/>
</noscript>

<script src="http://www.google-analytics.com/urchin.js" type="text/javascript"></script>
<script type="text/javascript">
_uacct = "UA-2323813-1";
urchinTracker();
</script>

</body>
</html>