<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/requestlogins.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title>Request Login URLs</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
<script>
function doSubmit(obj)
{
  obj.value = 'Loading ...';
  obj.disabled = true;
  obj.form.submit();
}
</script>
</head>
<?php flush(); ?>
<body>
<table width="600" align="center" cellpadding="2" cellspacing="2" border="1">
  <tr>
    <td align="center">
      <img src="/mle/images/pxm_title.jpg">
      <h2>Request Logins for all SafeLists</h2>
      This tool will email you all the Login URLs from all the Planet X Mail SafeLists that the email
      is registered with.  This includes searching the Contact Address and the List Email Address.
      <br /><br />
      <?php if ($notValid) echo '<font color="red"><b>' . $notValid . '</b></font><br /><br />'; ?>
      <form name="email" action="/mle/requestlogins.php" method="POST">
        Enter in the <b>Email Address</b> below:<br />
        <input type="text" name="email" value="<?=$email?>" size="30" />
        <br /><br />
        <input type="submit" value="Request Login URLs" onclick="doSubmit(this)" />
      </form>
      <?php echo str_replace('[location]','requestlogins', $ads_ads_ads); ?>
    </td>
  </tr>
</table>
</body>
</html>