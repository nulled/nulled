<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');
?>
<!DOCTYPE html>
<head>
<meta charset="UTF-8" />
<title>Grey List Domains</title>
<style>
body {
  font-size: 12px;
}
.main {
  width: 600px;
  text-align: center;
  margin: 0 auto;
  border: 1px solid black;
  padding: 10px;
  border-radius: 10px;
}
.title {
 margin: 5px auto;
 text-align: center;
 font-size: 18px;
}
</style>
</head>
<body>
<div class="main">

  <div class="title">
    Grey Listed Domains
  </div>

  <hr />

  <div style="margin:5px auto; text-align:left;font-size:14px">

  The Domains below can be set as your <b>Contact Address</b>, but <i>not</i> List Address.
  <br />
  <b>Simple Steps</b> are required to make them work properly. We step you through this simple <b>One Time Process.</b>

  </div>

  <div style="padding: 0 0 0 50px; width:400px;margin:3px auto;text-align:center">
    <ul style="float:left;text-align:left;font-size:18px">

      <?php

        $totalbanned = $_GREYLISTED_DOMAINS;
        sort($totalbanned);
        $numemails = count($totalbanned);

        foreach ($totalbanned as $i => $bld)
        {
          if ($i < ceil($numemails / 2))
            echo "<li><b>$bld</b></li>\n";
          else if ($i == ceil($numemails / 2))
            echo "</ul><ul style=\"float:left;text-align:left;font-size:18px\">\n<li><b>{$bld}</b></li>\n";
          else
            echo "<li><b>$bld</b></li>\n";
        }

      ?>

    </ul>

    <div style="clear:both"></div>

  </div>

  <?php
    // allow greylist to be bypassed, as we assume they took the steps to allow the mail to get through, used in EmailFormat() in validationfunctions.php
    $sh = substr(sha1('dfjJfd76f'), 0, 5);
  ?>

  <div style="text-align: left">
    <ol>
      <li><i>Log into your <b>AOL.COM</b> account.</i></li>
      <li><b>Send</b> a Message to <b>do_not_reply@planetxmail.com</b> (Simple Hello and Goodbye)</li>
      <li>You will be asked to click on a URL that Pops up in your AOL Account.</li>
      <li>Enter in the <i>Secret Key</i> they present to You.</li>
      <li>Once <i>proven you are a Human</i>, by entering the Key, the Email Should be sent to Us.</li>
      <li>Email Address: <b>do_not_reply@planetxmail.com</b> <i>should</i> appear in your <i>Sent Folder</i>.</li>
      <li><b>Finally</b>, Add <b>do_not_reply@planetxmail.com</b> to your <i>Address Book</i>.</li>
      <li style="color:red">Once <i>All</i> steps completed, <a href="/mle/signup.php?l=<?=$l?>&sh=<?=$sh?>">Click Here</a> to try entering aim/aol.com as Contact Email.</li>
    </ol>

    <u><b>IMPORTANT</b></u>: Any Email from <b>planetxmail.com</b> that appears in your <b>Junk/Spam</b> Folder <i>MUST</i>
    be Clicked as <b>Not Spam</b> by <i>You</i>.
    This lets AOL/AIM known that You do not concider planetxmail.com to be Spam! That you are a <i>Network Marketer</i> using Planet X Mails
    Platform to send your Daily Offerings, in return for You receiving daily offerings. It does not mean you have to read every single email.
    <br /><br />
    <b>Everytime you UnSpam a message in your Spam Folder you are placing Your vote!</b>
    <br /><br />
    <b>This goes for <i>ALL</i> Mail Providers</b>, including Yahoo!, Gmail, Hotmail, etc. They all follow the same model, and in some cases share information.
    <br /><br />
    Anytime you are having problems with messages going to your Junk/Spam Folder, simply UnSpam them! And <i>Double check</i> that
    <b>do_not_reply@planetxmail.com</b> is in Your Address Book.
    <br /><br />
    <b>It is <i>Your INBOX</i> and Therefore Your Vote!</b>
  </div>

</div>
</body>
</html>