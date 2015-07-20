<?php
include("mlpsecure/signuppaylinks.inc");
?>
<head>
<title>Sign Up Form</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
</head>
<body>
<table align="center" width="600" cellspacing="3" cellpadding="3">
  <tr>
    <td colspan="2" align="center">
    	<img src="<?php if ($titleIMG) echo "admin/$titleIMG"; else echo "images/title.gif"; ?>" border="0">
    	<br /><br />
    	<font size="+1">Sign up to <?php echo $listname; ?></font>
 		</td>
 	</tr>

 	<tr>
 	  <td align="center">
   	  <table border="0" width="700" cellspacing="0" cellpadding="0">
        <tr>
          <td colspan="2" align="left">
          	This SafeList is a <u><b><?php echo $paylinks->renewaltype; ?></b></u> subscription.
            <br /><br />
          	<b><?php echo "{$paylinks->fname} {$paylinks->lname}"; ?></b>, review the benefits below then choose your Method of Payment.
          	<hr />
          </td>
        </tr>

        <?php echo $upgradehtml; ?>

      </table>
 	  </td>
 	</tr>
</table>
</body>
</html>