<table align="center" border="0" cellpadding="2" cellspacing="0">
  <tr>
    <td align="center" width="640">
      <font size="+1"><b>Upgrade your Account</b></font>
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