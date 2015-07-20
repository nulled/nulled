<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/directads.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF=8" />
<title>Planet X Mail - Direct Exposure ADs</title>
<script language="javascript" src="submitsupressor.js"></script>
<link rel="stylesheet" type="text/css" href="x.css" />
<script language="javascript">
var focused = false;
function updateCount()
{
  if (focused)
  {
    ad = document.de_ad.message.value.toLowerCase();
    document.de_ad.countmessage.value = document.de_ad.message.value.length;

    if (document.de_ad.message.value.length > 750)
    {
      alert('AD can not be greater than 750 characters.');
      document.de_ad.message.value = fcontent[0];
      document.de_ad.countmessage.value = document.de_ad.message.value.length;
      return;
    }

    if (ad.indexOf("<script")!=-1    || ad.indexOf("script>")!=-1   ||
        ad.indexOf('<?="<?"?>')!=-1  || ad.indexOf('<?="?>"?>')!=-1 ||
        ad.indexOf('<form')!=-1 || ad.indexOf("\'")!=-1)
    {
      alert("No Javascript, PHP, VBS or <form code allowed!\n\nAlso, No SINGLE quotes, please use DOUBLE quotes.");
      document.de_ad.message.value = fcontent[0];
      document.de_ad.countmessage.value = document.de_ad.message.value.length;
    }
    else
      fcontent[0]=document.de_ad.message.value;
  }
}
function checkCount(formname)
{
  if (document.de_ad.message.value.length > 750) alert('AD can not be greater than 750 characters.');
  else if (document.de_ad.message.value.length < 1) alert('Missing Message.');
  else
  {
    if (confirm('You Ad will appear exactly as it does in the\nAD Preview window.\n\nAre you satisfied to continue?'))
    {
      submitonce(formname);
      formname.submit();
    }
  }
}
document.onkeyup=updateCount;
</script>
<style>
.main {
  margin: 10px auto;
  padding: 10px;
  text-align: left;
  width: 640px;
  border: 1px solid black;
  border-radius: 10px;
}
.notValid {
  border: 1px solid red;
  border-radius: 10px;
  background-color: pink;
  padding: 5px;
  margin: 5px; auto;
  text-align: center;
  font-weight: bold;
  font-size: 14px;
  width: 250px;
}
.message_main {
  width: 635px;
}
.message_left {
  float: left;
  padding: 0 5px;
}
.message_right {
  float: left;
}
</style>
</head>
<body background="images/directexposure_bg.jpg" onLoad="changecontent(); <?php if (! $message) echo "document.de_ad.message.value = fcontent[0];"; ?>">
<div class="main">
      <img src="images/directexposure_title.jpg"><br>
      <font size="+2"><b>Put your ADs where people will see them!</b></font><br><br>
      <font size="+1"><b>Get Massive Hits!</b></font>
      <p>
        <a href="index.php" target="_blank">Click Here to read about us - Planet X Mail</a>
      </p>
      </center>
      Looking for a <b><i>good place</i></b> to put your ADs?
      <br><br>
      We have the answer!
      <br><br>
      We will place your AD <b><u>directly in the line of traffic</u></b>.
      <br><br>
      Thousands of people use our systems <b>daily</b>
      to send their own ADs. We will place <b>your</b> AD where it <b><u>counts</u></b>!
      <br><br>
      <u>Your</u> AD will appear to the left of <i><b>ALL Send Mail Forms</b></i> on <b>ALL 245+ of our SafeLists</b> for as many DAYS as <b>you</b> like!
      <br><br>
      <b>135,000+ active members</b> use this system on a <u>daily</u> basis.  Maintained by <b>230+ List Owners</b> that carry
      <b><i>paid active members</i></b> looking for <u><b>your</b></u> opportunities!
      <hr>
      <ul>
        <li>Your AD placed in <b>direct line of traffic</b>.</li>
        <li>Over 230+ <b>List Owners</b>.</li>
        <li>Over 245+ <b>Safelists</b>.</li>
        <li>Over 135,000+ <b>active members</b>.</li>
      </ul>
      <hr>
      <ul>
        <li>No Porn Site ADs</li>
      </ul>
      <hr>

      <?php if ($notValid) echo '<div class="notValid">' . $notValid . '</div>'; ?>

      <form name="de_ad" action="directads.php" method="POST">

      <b>Your name:</b><br>
      <input type="text" name="name" value="<?=ex_stripslashes($name)?>" size="20">
      <br><br>
      <b>Your contact email:</b> <i>Your <b>contact email address</b> needed <u>only</u> for your <u>receipt</u>.</i><br />
      <input type="text" name="email" value="<?=ex_stripslashes($email)?>" size="30" />
      <br /><br />

      <div class="message_main">

        <div class="message_left">
          <b>Your AD Message - Text/HTML:</b>

          <br>
          <textarea wrap="OFF" rows="14" cols="50" name="message" onFocus="focused=true;" onBlur="focused=false;"><?=ex_stripslashes($message)?></textarea>
          <br>
          <input type="text" name="countmessage" size="4" readonly>&nbsp;&nbsp;Maximum of <b>750</b> characters.<br><br>
          <input type="hidden" name="submitted" value="send">
          <input type="button" class="beigebutton" value="Submit Your Direct Exposure AD" onClick="checkCount(this.form)">
          </form>
        </div>

        <div class="message_right">
          <font size="+1"><b>AD Preview:</b></font>
          <font size="-2">5 sec refresh</font>
          <script>
            var fwidth=100;
            var fheight=200;
            var delay=5000;
            var fcontent=new Array();
            begintag='<font size="2">';
            <?php
              if ($message) echo "fcontent[0]=document.de_ad.message.value;";
              else
                echo "fcontent[0]='<img src=\"http://planetxmail.com/images/elogo.jpg\">\\n<hr>\\n<font size=\"-2\">Here is an <b>example</b> AD.</font>\\n<br><br><i>AMAZING!</i>\\n<br><br>You can even add graphics!';\n";
            ?>
            closetag='</font>';
          </script>
          <script text="text/javascript" src="mle/da.js"></script>
          <ilayer id="fscrollerns" width=&{fwidth}; height=&{fheight};><layer id="fscrollerns_sub" width=&{fwidth}; height=&{fheight}; left=0 top=0></layer></ilayer>
        </div>
      </div>

      <div style="clear: both"></div>

      <hr />
      <font size="-1">All Rights Reserved &copy;2001 - <?php echo date('Y'); ?> -
      Planet X Mail -
      Contact: <a href="openticket.php">Planet X Mail Support</a></font>
</div>
</body>
</html>
