<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/adminmemberaffview.inc");
?>
<html>
<head>
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
var prefix="";
var wd;
function parseelement(thisone)
{
  if (thisone.value.charAt(0)=="$") return;

  wd="w";
  var tempnum=thisone.value;

  for (i=0;i<tempnum.length;i++)
  {
    if (tempnum.charAt(i)==".")
    {
      wd="d";
      break;
    }
  }

  if (wd=="w") thisone.value=prefix+tempnum+".00";
  else
  {
    if (tempnum.charAt(tempnum.length-2)==".")
      thisone.value=prefix+tempnum+"0";
    else
    {
      tempnum=Math.round(tempnum*100)/100;
      thisone.value=prefix+tempnum;
    }
  }
}

document.affiliates.amounttopay.value = 0;

function setAmountToPay(amount, operation)
{
  totalamount = convertForm = 0;
  totalamount = document.affiliates.amounttopay.value * 1; // converts form string to an integer

  if (operation)
    document.affiliates.amounttopay.value = totalamount + amount;
  else
    document.affiliates.amounttopay.value = totalamount - amount;

  parseelement(document.affiliates.amounttopay);
}

function checkSelect(theform)
{
  totalamount = theform.amounttopay.value * 1;

  if (totalamount==0)
  {
    alert('Nothing was selected!\nUse the CheckBoxes to select\nwhat referals you want to pay.');
    return 0;
  }

  return 1;
}

function preSubmit(theform)
{
  var usernames = '';

  for (i=0; i < theform.length; i++)
  {
    var tempobj=theform.elements[i]

    if(tempobj.type.toLowerCase()=="checkbox" && tempobj.checked)
      usernames += tempobj.value + '|';
  }

  theform.affs.value = usernames;
  theform.submit();
}
//-->
</script>
</head>
<body onLoad="<?php if ($submitted=="update") echo "window.open('https://www.paypal.com/xclick/business=$affiliatemop&item_name=$_SESSION[aalistname]+Affiliate+Payment+for+$uname&item_number=1&amount=$amounttopay',1,'height=580,width=640,status=1,toolbar=1,menubar=1,resizable=1,location=0,scrollbars=1')"; ?>">
<table width="640" cellpadding="5" cellspacing="2" align="center">
  <tr>
    <td align="center">
      <font size="3">People that <font color="red"><b><?=$uname?></b></font> has referred:</font></center><br>
      <font color="red"><b><?=$uname?>'s</b></font> Paypal address is: <b><?=$affiliatemop?></b><br>
      <form name="affiliates" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
      <table align="center" cellspacing="2" cellpadding="1">
        <?=$html?>
      </table>
    </td>
  </tr>
  <tr>
   <td align="center">
     <br><br><input type="button" class="beigebutton" value="Back to Affiliate Manager" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "affiliatemanager.php"; else echo "affiliatemanager.php"; ?>'">
   </td>
  <tr>
</table>
</body>
</html>