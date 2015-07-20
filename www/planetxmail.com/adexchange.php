<?php
require_once('phpsecure/adexchange.inc');
?>
<html>
<head>
<title>Planet X Mail - AD Exchange</title>
<script language="javascript" src="submitsupressor.js"></script>
<link rel="stylesheet" type="text/css" href="x.css" />
<script language="javascript">
<!--
var focused = false;
function updateCount()
{
  if (focused)
  {
    var ad = document.ad.message.value.toLowerCase();
    document.ad.countmessage.value = document.ad.message.value.length;

    if (document.ad.message.value.length > 750)
    {
      alert('AD can not be greater than 750 characters.');
      document.ad.message.value = fcontent[0];
      document.ad.countmessage.value = document.ad.message.value.length;
      return;
    }

    if (ad.indexOf("<script")!=-1    || ad.indexOf("script>")!=-1   ||
        ad.indexOf('<?="<?"?>')!=-1  || ad.indexOf('<?="?>"?>')!=-1 ||
        ad.indexOf('<form')!=-1 || ad.indexOf("\'")!=-1)
    {
      alert("No Javascript, PHP, VBS or <form code allowed!\n\nAlso, No SINGLE quotes, please use DOUBLE quotes.");
      document.ad.message.value = fcontent[0];
      document.ad.countmessage.value = document.ad.message.value.length;
    }
    else
      fcontent[0]=document.ad.message.value;
  }
}
function checkCount(formname)
{
  if (document.ad.message.value.length > 750) alert('AD can not be greater than 750 characters.');
  else if (document.ad.message.value.length < 1) alert('Missing Message.');
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
//-->
</script>
</head>
<body background="images/directexposure_bg.jpg" onLoad="changecontent(); <?php if (! $message) echo "document.ad.message.value = fcontent[0];"; ?>">
<table border="0" width="590" align="center">

  <form name="ad">

  <tr>
    <td align="left">
      <h2>AD Exchange</h2>

      First and Last Name:
      <br />
      <input type="text" name="email" value="<?php echo $name; ?>" size="30" />
      <br /><br />

      Contact Email Address:
      <br />
      <input type="text" name="email" value="<?php echo $email; ?>" size="60" />

    </td>
  </tr>

  <tr>
    <td>
      <b>Your AD Message - Text/HTML:</b>
    </td>
  </tr>

  <tr>
    <td valign="top">
      <textarea wrap="PHYSICAL" rows="5" cols="80" name="message" onFocus="focused=true;" onBlur="focused=false;"><?php if ($message) $message = stripslashes($message); echo $message; ?></textarea>
      <br />
      <input type="text" name="countmessage" size="4" readonly />&nbsp;&nbsp;Maximum of <b>750</b> characters.
      <br /><br />
      <input type="hidden" name="submitted" value="send" />
      <input type="button" class="beigebutton" value="Submit AD" onClick="checkCount(this.form)" />
    </td>
  </tr>

  </form>

  <tr>
    <td>
      <br /><br />
      Below is what your AD will actually look like. Standard size 468 x 60.
      <script>
        var fwidth=468;
        var fheight=60;
        var delay=2500;
        var fcontent=new Array();
        begintag='<font size="2">';
        <?php
          if ($message) echo "fcontent[0]=document.ad.message.value;";
          else
            echo "fcontent[0]='<img src=\"http://www.planetxmail.com/images/elogo.jpg\">\\n<hr>\\n<font size=\"-2\">Here is an <b>example</b> AD.</font>\\n<br /><br /><i>AMAZING!</i>\\n<br /><br />You can even add graphics!';\n";
        ?>
        closetag='</font>';
      </script>
      <script text="text/javascript" src="mle/directads.js"></script>
      <ilayer id="fscrollerns" width=&{fwidth}; height=&{fheight};><layer id="fscrollerns_sub" width=&{fwidth}; height=&{fheight}; left=0 top=0></layer></ilayer>
    </td>
  </tr>

  </form>

  <tr>
    <td>
      <br /><br />
      <a name="help">
      <font size="+1"><b>Instructions</b></font>
      <br /><br />
      <script text="text/javascript" src="iframe.js"></script>
    </td>
  </tr>

  <tr>
    <td align="center" valign="top">
      <br /><hr><font size="-1">All Rights Reserved &copy;2001-<?php echo date("Y"); ?><br />Planet X Mail<br />
      Contact Us: <a href="openticket.php">Open a Ticket</a></font>
    </td>
  </tr>

</table>
</body>
</html>