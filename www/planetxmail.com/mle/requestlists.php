<?php
require_once('/home/nulled/config.inc');

$db = new MySQL_Access('mle');

$db->Query("SELECT listname, listhash FROM listurls WHERE 1 ORDER BY listname");

$lists = array();
while(list($listname, $listhash) = $db->FetchRow())
  $lists[$listhash] = $listname;

if ($notValid = trim($_GET['notValid']))
  $notValid = urldecode($notValid);

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title>Planet X Mail - Request Safelist List</title>
<style>
a:link { color: #000; text-decoration: none; }
a:visited { color: #000; text-decoration: none; }
a:hover { color: #FF0000; text-decoration: underline; }
a:active { color: #000; text-decoration: none; }

* {
  margin: 0;
  padding: 0;
  font: Verdana, Geneva, Arial, Helvetica, sans-serif;
  font-size: 12px;
}

body {
  margin: 20px 0;
}

a {
  font-size: 12px;
}

.title_img {
  margin: 0 auto;
  text-align: center;
  font-size: 12px;
}

.title {
  margin: 0 auto;
  text-align: center;
  font-size: 14px;
}

.link_container {
  padding: 5px 40px;
  margin: 5px auto;
  width: 1014px;
  text-align: center;
  border: 1px dashed white;
}

.link1 {
  background-color: #A9D4FF;
  margin: 3px;
  border: 1px solid #5C6166;
  padding: 7px 0;
  width: 180px;
  border-radius: 7px;
  float: left;
  font-size: 12px;
}

.link2 {
  background-color: #D4EAFF;
  margin: 3px;
  border: 1px solid #5C6166;
  padding: 7px 0;
  width: 180px;
  border-radius: 7px;
  float: left;
}

.clear {
  clear: both;
}

.footer {
  margin: 0 auto;
  text-align: center;
  font-size: 12px;
}

.notValid {
  border: 1px solid red;
  padding: 5px;
  margin: 10px auto;
  text-align: center;
  background-color: pink;
  color: black;
  width: 300px;
  border-radius: 5px;
}
</style>
</head>
<?php flush(); ?>
<body>

  <div class="title_img">
    <a href="/" target="_self"><img src="/mle/images/pxm_title.jpg" border="0" /></a>
    <br />
    Sign up is FREE. Sign up and Login to as many Safelists as you like!
    <br />
    <i>Not all Safelists are Listed here, per Request of the List Owner</i>
  </div>

  <div class="title">
    Top Link = SignUp - Bottom Link = LogIn
  </div>

  <?php

    if ($notValid) echo '<div class="notValid">' . $notValid . ' </div>
                        ';

  ?>

  <div class="link_container">

    <?php

    $i = 0;
    foreach($lists as $hash => $name)
    {
      $c = ($i % 2) ? 'link1' : 'link2';

      echo '<div class="' . $c . '">
            <a href="/mle/signup.php?l=' . $hash . '" title="SIGN-UP to ' . $name . '">' . $name . '</a>
            <br />
            <a href="/mle/login.php?l=' . $hash . '" title="LOG-IN to ' . $name . '">' . $name . '</a>
            </div>
            ';
      $i++;
    }

    ?>

    <div class="clear"></div>

  </div>

  <div class="footer">
    All Rights Reserved &copy; 2001 - <?=date('Y')?> Planet X Mail<br />
  </div>

</body>
</html>