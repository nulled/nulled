<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/affiliatemanager.inc");
?>
<html>
<head>
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
</head>
<body>
<table width="600" cellpadding="5" cellspacing="2" align="center">
  <tr>
    <td align="center">
      <h2>Affiliate Manager</h2>
      <hr>
      Members Listed Below have affiliates they referred to your SafeList. Use this system to Pay and Edit your Affiliate records. Affiliates that
      are listed in <font color="red"><b>red</b></font> indicate that you owe them at least one commission.
      <br><br>
      <table cellpadding="1" cellspacing="1">
        <tr>
          <td bgcolor="lightblue"><b>Member Name</b></td><td bgcolor="lightblue"><b>Not Paid</b></td><td bgcolor="lightblue"><b>Grand Total</b></td>
        </tr>
        <?=$html?>
      </table>
    </td>
  </tr>
  <tr>
    <td align="center">
      <br><br>
      Please, use this system FAIRLY and HONESTLY.  Please, try to keep your prices and commission percentages unchanged as changing them will change
      all the stats in the Affiliate Manager and what Members view from their profiles.  If it is found that this system is used DISHONESTLY your
      List Owner and SafeList may be put under further investigation and possibly shut off without refund.  This is to protect the best interests of
      your members, yourself and my own. If you see any errors or problems with this NEW Affiliate system please email me at: <b>accounts@planetxmail.com</b>
    </td>
  </tr>
  <tr>
    <td align="center">
      <br><br>
      <input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
    </td>
  <tr>
</table>
</body>
</html>