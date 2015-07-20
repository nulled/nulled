<?php
require_once("/home/nulled/www/freeadplanet.com/secure/members.inc");
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<META HTTP-EQUIV="CONTENT-TYPE" CONTENT="text/html; charset=UTF-8">
<title>Free AD Planet - Members Area</title>
<link rel="stylesheet" type="text/css" href="../x.css" />
<script type="text/javascript" src="../jscript.js"></script>
<script type="text/javascript" src="../jsm.js"></script>
<script type="text/javascript">
<!--
<?php
$onLoad = "
var hw = document.getElementById('helpWindow');
//jsm.dnd.makeDraggable(hw);
hw.style.display='$help_state';
var a = hw.getElementsByTagName('a');
for (var i=0; i < a.length; i++) {
  jsm.handler.add(a[i], 'mousedown', function(e) {
    if (e.stopPropagation) e.stopPropagation();
  });
}
";
if      ($c == 'billboardads') $onLoad .= 'if (document.forms[0]){document.forms[0].counter_message.value = ('.$bb_max_mess_chars.' - document.forms[0].message.value.length);document.forms[0].counter_heading.value = ('.$bb_max_head_chars.' - document.forms[0].heading.value.length) }';
else if ($c == 'targetedads')  $onLoad .= 'if (document.forms[0]){document.forms[0].counter_message.value = ('.$ta_max_mess_chars.' - document.forms[0].message.value.length);document.forms[0].counter_heading.value = ('.$ta_max_head_chars.' - document.forms[0].heading.value.length) }';
else if ($c == 'spotlightads') $onLoad .= 'if (document.forms[0]){document.forms[0].counter_message.value = ('.$sl_max_mess_chars.' - document.forms[0].message.value.length);document.forms[0].counter_heading.value = ('.$sl_max_head_chars.' - document.forms[0].heading.value.length) }';
else if ($c == 'mailer')       $onLoad .= 'if (document.forms[0]){document.forms[0].counter_message.value = ('.$ml_max_mess_chars.' - document.forms[0].message.value.length);document.forms[0].counter_heading.value = ('.$ml_max_head_chars.' - document.forms[0].heading.value.length) }';
else if ($c == 'profile' && $x == 1) $onLoad .= "xferCredits('set');";
echo 'jsm.handler.add(window, \'load\', function() { '.$onLoad.' });';
?>

var focus_heading = false;
var focus_message = false;
function updateCount()
{
  <?php

    $str  = "if (focus_heading && document.forms[0]) document.forms[0].counter_heading.value = ([max_head_chars] - document.forms[0].heading.value.length);\n";
    $str .= "if (focus_message && document.forms[0]) document.forms[0].counter_message.value = ([max_mess_chars] - document.forms[0].message.value.length);\n";

    if ($c == 'billboardads')
      echo str_replace(array('[max_head_chars]', '[max_mess_chars]'), array($bb_max_head_chars, $bb_max_mess_chars), $str);
    else if ($c == 'targetedads')
      echo str_replace(array('[max_head_chars]', '[max_mess_chars]'), array($ta_max_head_chars, $ta_max_mess_chars), $str);
    else if ($c == 'spotlightads')
      echo str_replace(array('[max_head_chars]', '[max_mess_chars]'), array($sl_max_head_chars, $sl_max_mess_chars), $str);
    else if ($c == 'mailer')
      echo str_replace(array('[max_head_chars]', '[max_mess_chars]'), array($ml_max_head_chars, $ml_max_mess_chars), $str);

  ?>
}
document.onkeyup=updateCount;
function saveOnly()
{
  document.getElementById('submitted').value = 'save';
  document.forms[0].submit();
}
-->
</script>
</head>
<?php flush(); ?>
<body>
<table bgcolor="white" align="center" width="800" style="border-collapse: collapse" bordercolor="#000000" border="1" cellspacing="0" cellpadding="0"><tr><td>
<table bgcolor="white" align="left" border="0" width="800" cellpadding="0" cellspacing="0">

  <!-- Title plus rotating banner -->
  <tr>
    <td bgcolor="black" colspan="2">
      <table border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td align="left" background="../images/title.jpg" width="800" height="100">
            <div style="position: relative; left: 295px; top: 0px; width: 468px; height: 60px; padding: 1px; background-color: transparent;">
              <?php echo $bannerad_top; ?>
            </div>
          </td>
        </tr>
      </table>
    </td>
  </tr>

 <!-- Menu -->

  <tr>
    <td class="main_menu" colspan="2" align="center" valign="center" nowrap>
    <div style="border-style: none;" class="member_menu_box">
      <font size="+1">
        <a href="?c=home" class="menumembers">Earn Credits</a> <font size="3">|</font>
        <a href="?c=profile" class="menumembers">Profile</a> <font size="3">|</font>
        <a href="?c=mailer" class="menumembers">Mailer</a> <font size="3">|</font>
        <a href="?c=referring" class="menumembers">Referring</a> <font size="3">|</font>
        <a href="?c=downline" class="menumembers">Downline</a> <font size="3">|</font>
        <a href="?c=commissions" class="menumembers">Commissions</a> <font size="3">|</font>
        <a href="?c=faq" class="menumembers">F.A.Q.</a> <font size="3">|</font>
        <a href="javascript:void(0)" onclick="ToggleHelp('helpWindow')" class="menumembers"><font color="blue"><b>Guide Me</b></font></a>
      </font>
     </div>
     </td>
   </tr>

   <tr>
     <td colspan="2" align="center" valign="center" nowrap>
     <div class="member_menu_box">
      <font size="+1">
        <a href="?c=buyads" class="menumembers">Buy ADs</a> <font size="3">|</font>
        <a href="?c=spotlightads" class="menumembers">SpotLight ADs</a> <font size="3">|</font>
        <a href="?c=targetedads" class="menumembers">Targeted ADs</a> <font size="3">|</font>
        <a href="?c=billboardads" class="menumembers">BillBoard ADs</a> <font size="3">|</font>
        <a href="?c=bannerads" class="menumembers">Banner ADs</a> <font size="3">|</font>
        <a href="?c=exitads" class="menumembers">Exit ADs</a> <font size="3">|</font>
        <a href="?c=logout" class="menumembers">Log Out</a>
      </font>
    </div>
    </td>
  </tr>

  <!-- END Menu -->

  <!-- Left Pane -->
  <tr>
    <td width="25%" valign="top">
      <table border="0" cellpadding="4" cellspacing="0">

        <tr>
          <td align="center">
            <div class="targeted_title">
              Pro Targeted ADs
            </div>
          </td>
        </tr>

        <tr>
          <td align="center" valign="top">

            <?php echo display_ad('targeted', $ta_pro, $db, $affid); ?>

          </td>
        </tr>

        <tr>
          <td align="center">
            <div class="targeted_title">
              Free Targeted ADs
            </div>
          </td>
        </tr>

        <tr>
          <td align="center" valign="top">

            <?php echo display_ad('targeted', $ta_free, $db, $affid); ?>

          </td>
        </tr>

      </table>
    </td>
    <!-- END Left Pane -->

    <!-- Main Content -->
    <td width="75%" valign="top">
      <table align="center" border="0" cellpadding="5" cellspacing="0">
        <tr>
          <td>

            <?php

              $no_credits_warning = '';
              if ($credits == 0)
                $no_credits_warning = '<center><font size="3" color="red"><b>Attention:</b></font> You currently have 0 (zero) <i>Open</i> Credits!<br />Some or all of your ADs will not be displayed to other Members.<br />Earn Credits by viewing ADs or <a href="?c=profile&x=1">Transfer</a> Credits, if possible.</center><hr />';

              echo $no_credits_warning.$main_content;

              if ($bannerad_bot) {
                echo '<br /><br /><center>'.$bannerad_bot;
                if ($status == '0') {
                  echo '<br />Your banner could be here. <a href="?c=upgrade">Find out how</a>.</center>';
                }
              }

            ?>

          </td>
        </tr>
      </table>
    </td>
  </tr>
  <!-- END Main Content -->

  <!-- Footer -->
  <tr>
    <td colspan="2" align="center">
      <hr /><br />
      All Rights Reserved &copy; 2007-<?php echo date('Y'); ?>
      <br /><br />
    </td>
  </tr>
  <!-- END Footer -->

</table>
</tr></td></table>
<?php

  echo '
  <div id="helpWindow">
    <div style="float:right">
      <a href="javascript:void(0)" onclick="ToggleHelp(\'helpWindow\')"><font size="-2"><b>[close]</b></font></a>
    </div>

    <center>
      <b>Your Free AD Planet Guide</b>
      <br />
      <font color="red">Remains open, even while you navigate this site!</font>
    </center>

    <br />
    '.$porn_warning.'
    <br /><br />

    <hr />
  	First timers on Free AD Planet, please, read below to get your First ADs placed.

  	<ol>
  	  <li>Click <a href="?c=spotlightads">SpotLight ADs</a> or use the Menu above.</li>
  	    <ul>
  	      <li>Add Spotlight Heading, URL and Message! Save your AD.</li>
  	    </ul>

  	  <li>Click on <a href="?c=targetedads">Targeted ADs</a> or use the Menu above.</li>
  	    <ul>
  	      <li>Add Targeted Heading, URL and Message! Save your AD.</li>
  	    </ul>

  	  <li>Goto <a href="?c=profile">Profile</a> and set Categories and ways we can pay you.</li>
  	    <ul>
  	      <li>Note the <a href="?c=profile&x=1">Transfer Credits</a> Link. You can Lock away Credits, keeping them from being drained because of people vieing your ADs. But, if you run out of Open Credits some of your ADs will become invisible until you earn the Credits back.</li>
  	    </ul>

  	  <li><a href="?c=referring">Referring</a> people can earn you cash. Learn how there.</li>
  	  <li>Goto <a href="?c=downline">Downline</a> to see who you referred. You can <a href="?c=mailer">mail</a> them and earn money from them.</li>
  	  <li><a href="?c=commissions">Commissions</a> is where you claim and view your commissions owned to you.</li>
  	  <li><a href="?c=buyads">Buy ADs</a> is where you can buy credits and ADs using money or your own Credits.</li>
  	  <li>It is important to understand the <a href="http://freeadplanet.com/policies.php" target="_blank">AD View Quota System</a>.</li>
  	</ol>

  	<hr />

  	Once your ADs are submitted it is time to Earn some Credits! Credits allow you the ability to:

  	<ol>
  	  <li>Save up to <a href="?c=buyads">Buy ADs</a> with your Credits.</li>
  	  <li>Having 0 Open Credits is bad, because then your ADs will not be displayed until you earn a greater than 0 Open Credit balance. Having Locked Credits do not count.</li>
  	  <li>Each time you view an AD you Earn Credits. The account that posted that AD you just viewed will be drained those Credits.</li>
  	  <li>This works for your ADs as well. When someone views your AD you get drained a credit and they earn a credit, because they viewed your website!</li>
  	  <li><a href="?c=profile&x=1">Transfer</a> and Lock your Credits if you do not want them to get Drained. Say if you are trying to save them up.</li>
  	</ol>

  	<hr />

  	How to Earn Credits is explained below.

  	<ol>
  	  <li>Any AD that is not yours will contain a Heading/Link you can click on.</li>
  	  <li>Clicking on AD links will open a new browser window ( or tab ) showing you the ADs website.</li>
  	  <li>There is then a 15 second counter that starts which is indicated in yellow at the top.</li>
  	  <li>While the timer is counting down you can navigate and quickly view the Website...bookmark if you want to come back later if you wish.</li>
  	  <li>After the 15 seconds is up you will see you have earned your credits, shown in yellow at the top.</li>
  	  <li>Please <a href="http://planetxmail.com/openticket.php" target="_blank">Report</a> any ADs/Websites that break the frames when you view the AD. You will not earn your Credits from these! So report them to us.</li>
  	  <li>You will see your own ADs in the mix and they are easily distinguishable by a Light Blue Border. You can not Earn from your own ADs, but it is always a good idea to click them from time to time to be sure they are working.</li>
  	  <li>If you are a PRO Member you can Transfer Credits from any of your planetxmail.com Safelist Accounts.</li>
  	</ol>

  </div>
  ';

?>
<!-- Start Quantcast tag -->
<script type="text/javascript" src="http://edge.quantserve.com/quant.js"></script>
<script type="text/javascript">
_qacct="p-a26V9rP8NfTY2";quantserve();</script>
<noscript>
<img src="http://pixel.quantserve.com/pixel/p-a26V9rP8NfTY2.gif" style="display: none" height="1" width="1" alt="Quantcast"/>
</noscript>
<!-- End Quantcast tag -->
<script src="http://www.google-analytics.com/urchin.js" type="text/javascript">
</script>
<script type="text/javascript">
_uacct = "UA-2323813-2";
urchinTracker();
</script>
</body>
</html>
