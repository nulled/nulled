<?php
require_once('/home/nulled/www/freeadplanet.com/secure/public.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8" />
<title>Free AD Planet</title>
<link rel="stylesheet" type="text/css" href="x.css" />
<script language="javascript" src="jscript.js"></script>

<?php

  $onLoad = '';

  if ($show_email_confirmer)
  {
    echo '
    <script type="text/javascript">
    function createXMLHttpRequest()
    {
      try { return new XMLHttpRequest(); } catch (e) {}
      try { return new ActiveXObject("Msxml2.XMLHTTP"); } catch (e) {}
      try { return new ActiveXObject("Microsoft.XMLHTTP"); } catch (e) {}
      return null;
    }
    function $(id)
    {
      return document.getElementById(id);
    }
    function scanlog()
    {
      var xhr = createXMLHttpRequest();

      if (xhr == null) return;

      xhr.onreadystatechange = function() {
        // readyState Status Codes:
      	// 0 = uninitialized
      	// 1 = loading
      	// 2 = loaded
      	// 3 = interactive
      	// 4 = complete

      	// IE does not like code 3
        if (document.addEventListener) {
          if (xhr.readyState == 3) {
            $("layer1").innerHTML = xhr.responseText;
          }
        } else {
          $("layer1").innerHTML = "<b>Please wait while we verify the confirmation email was sent.<br /><u>This may take several minutes.</u><br />Please, check your INBOX.</b>";
        }

        if (xhr.readyState == 4) {
          if (xhr.status == 200) {
             $("layer1").innerHTML = xhr.responseText;
          } else {
            $("layer1").innerHTML = "ERROR: Unable to determine if mail was successfually sent or not.<br />Please, check your INBOX.";
          }
        }
      }
      xhr.open("GET", "scanlog.php?e=' . $email . '&h=' . $hash . '", true);
      xhr.send(null);
    }
    </script>
    ';
    $onLoad = 'onload="javascript:scanlog();"';
  }

?>

</head>
<?php flush(); ?>
<body <?php echo $onLoad; ?>>

<div class="mainContainer">

  <header class="header">
            <div class="title_banner">
              <?php echo $bannerad_top; ?>
            
            </div>
  </header> 
  
  <nav class="main_menu">
       <a href="?c=home" class="menu">Home</a> |
        <a href="?c=joinfree" class="menu">Join FREE</a> |
        <a href="?c=earncash" class="menu">Earn Cash</a> |
        <a href="?c=aboutus" class="menu">About Us</a> |
        <a href="http://freeadplanet.com/openticket.php" target="_blank" class="menu">Contact Us</a> |
        <a href="?c=memberlogin" class="menu">Member Log-In</a>
  </nav>

  <!-- Distributed ADs -->
      <iframe src="http://freeadplanet.com/?c=dah&affid=66165448&no=1" marginheight="0" marginwidth="0" height="85" width="800" scrolling="no" frameborder="0" align="middle"></iframe>
  <!-- END Distributed ADs -->

<div class="subContainer">
<div class="subLeft">
            <div class="billboard_title">
              BillBoard ADs
            </div>
            <br />
            <?php echo display_ad('billboard', $bb, 'public'); ?>
            
            <div class="spotlight_title">
              SpotLight ADs
            </div>
            <br />
            
            <?php echo display_ad('spotlight', $sl, 'public'); ?>
</div>
<div class="subRight">
    <!-- Main Content -->
            <?php

              echo $main_content;

              if ($bannerad_bot AND $c != 'joinfree') {
                echo '<br /><br /><br /><div style="margin:0 auto">' . $bannerad_bot . '</div>';
              }

            ?>
</div>
</div>
<div class="clearBoth"></div>

<footer>
      <br /><br />
      <hr />
      All Rights Reserved &copy; 2007-<?php echo date('Y'); ?>
      <br /><br />
</footer>

</div>

<?php
if ($c == 'memberlogin' OR $c == 'joinfree')
{
  echo '
  <script type="text/javascript">
  <!--
    if (document.forms[0].username.value)
      document.forms[0].tkey.focus();
    else
      document.forms[0].username.focus();
  -->
  </script>
  ';
}
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
