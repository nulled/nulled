<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/requestremovelinks.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Request Remove URLs</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
<script language="javascript" src="submitsupressor.js"></script>
</head>
<?php flush(); ?>
<body>
<table width="600" align="center" cellpadding="2" cellspacing="2" border="1">
  <tr>
    <td align="center">
      <img src="images/pxm_title.jpg" border="0" />
      <h2>Request Remove URL for all SafeLists</h2>
      This tool will email you all the Unsubscribe URLs from all the Planet X Mail SafeLists, for which that email
      is registered to.  This Searchs the Contact Address and List Address for Accounts.
      It will also email you a <i>"Master Remove URL"</i> that if used will remove ALL accounts from ALL
      the Planet X Mail SafeLists for which that email is registered to.  Warning!  This includes the Contact
      AND List Address!  So use the <i>"Master Remove URL"</i> carefully!
      <br /><br />
      <?php if ($notValid) echo '<font color="red"><b>' . $notValid . '</b></font><br /><br />'; ?>
      <form name="email" action="/mle/requestremovelinks.php" method="POST" onSubmit="submitonce(this)">
        Enter in the <b>Email Address</b> below:<br>
        <input type="text" name="email" value="<?=$email?>" size="30" />
        <br /><br />
        <input type="submit" value="Request Remove URLs" />
      </form>
      <?php echo str_replace('[location]','requestremovelinks', $ads_ads_ads); ?>
    </td>
  </tr>
</table>
</body>
</html>