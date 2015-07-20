<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/mca.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Planet X Mail - Contact Address Changed</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<?php flush(); ?>
<body>

  <div style="width:640px;margin:5px auto;text-align:center;border:1px solid lightgray">

    <div style="width:600px;margin:5px auto;text-align:center">
      <img src="../images/title.jpg" border="0" />
      <hr />
      <?php
        echo '<div style="margin:5px auto;width:500px;border-radius:5px;padding:5px;font-size:14px;border:1px solid red;background-color:pink">' . $notValid . '</div>';
        echo str_replace('[location]', 'contactaddressechanged', $ads_ads_ads);
      ?>
    </div>
    <hr />
    <div style="font-size:12px;width:640px;margin:5px auto;text-align:center">
      All Rights Reserved &copy; 2001 - <?=date('Y')?> - <a href="/openticket.php" target="_self">Contact Support</a>
    </div>

  </div>

</body>
</html>