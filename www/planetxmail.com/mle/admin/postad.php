<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/postad.inc");
?>
<html>
<head>
<title><?=$program_name?> - Administrator Control</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
var focused = false;
function updateCount()
{
  if (focused) document.createad.countaddescription.value = document.createad.addescription.value.length;
}

document.onkeyup=updateCount;

function setColor (code)
{
  if (! document.getElementById)
  {
    alert("Upgrade your browser before you can use. Version 5 or higher.");
    return;
  }

  if (document.createad.choice[0].checked)
  {
    window.document.getElementById('subjectfont').style.color = code;
    document.createad.subject_text_color.value = code;
  }
  else if (document.createad.choice[1].checked)
  {
    window.document.getElementById('descriptionfont').style.color = code;
    document.createad.description_text_color.value = code;
  }
  else if (document.createad.choice[2].checked)
  {
    window.document.getElementById('bg').style.background = code;
    document.createad.bg_color.value = code;
  }
}

function setStyle()
{
  if (! document.getElementById)
  {
    alert("Upgrade your browser before you can use. Version 5 or higher.");
    return;
  }

  if (document.createad.subjectstylechoice[0].checked)
  {
    window.document.getElementById('subjectfont').style.fontWeight = 'normal';
    window.document.getElementById('subjectfont').style.fontStyle = 'normal';
    document.createad.subjectstylechoice1.value = 'font-style: normal; font-weight: normal;';
  }
  if (document.createad.subjectstylechoice[1].checked)
  {
    window.document.getElementById('subjectfont').style.fontStyle = 'normal';
    window.document.getElementById('subjectfont').style.fontWeight = 'bold';
    document.createad.subjectstylechoice1.value = 'font-style: normal; font-weight: bold;';
  }
  if (document.createad.subjectstylechoice[2].checked)
  {
    window.document.getElementById('subjectfont').style.fontWeight = 'normal';
    window.document.getElementById('subjectfont').style.fontStyle = 'italic';
    document.createad.subjectstylechoice1.value = 'font-style: italic; font-weight: normal;';
  }
  if (document.createad.subjectstylechoice[3].checked)
  {
    window.document.getElementById('subjectfont').style.fontWeight = 'bold';
    window.document.getElementById('subjectfont').style.fontStyle = 'italic';
    document.createad.subjectstylechoice1.value = 'font-style: italic; font-weight: bold;';
  }
  if (document.createad.descriptionstylechoice[0].checked)
  {
    window.document.getElementById('descriptionfont').style.fontWeight = 'normal';
    window.document.getElementById('descriptionfont').style.fontStyle = 'normal';
    document.createad.descriptionstylechoice1.value = 'font-style: normal; font-weight: normal;';
  }
  if (document.createad.descriptionstylechoice[1].checked)
  {
    window.document.getElementById('descriptionfont').style.fontStyle = 'normal';
    window.document.getElementById('descriptionfont').style.fontWeight = 'bold';
    document.createad.descriptionstylechoice1.value = 'font-style: normal; font-weight: bold;';
  }
  if (document.createad.descriptionstylechoice[2].checked)
  {
    window.document.getElementById('descriptionfont').style.fontWeight = 'normal';
    window.document.getElementById('descriptionfont').style.fontStyle = 'italic';
    document.createad.descriptionstylechoice1.value = 'font-style: italic; font-weight: normal;';
  }
  if (document.createad.descriptionstylechoice[3].checked)
  {
    window.document.getElementById('descriptionfont').style.fontWeight = 'bold';
    window.document.getElementById('descriptionfont').style.fontStyle = 'italic';
    document.createad.descriptionstylechoice1.value = 'font-style: italic; font-weight: bold;';
  }
}
//-->
</script>
</head>
<body>
<table bgcolor="lightgrey" width="500" align="center" cellspacing="0" cellpadding="5" border="0">
  <tr>
    <td colspan="2" align="center">
      <b class="red">Post an Ad</b><br>
      These Ads will appear on the pop up sent mail window after a member sends mail.<br>
      Along with the Banners you uploaded, if any.
      <hr>
      <b class="red"><?=$notValid?></b>
    </td>
  </tr>
  <tr>
    <td align="center">
      <form name="createad" action="<?=$_SERVER[PHP_SELF]?>" ENCTYPE="multipart/form-data" method="POST">
      Subject:
    </td>
    <td valign="top">
      <input type="text" name="adsubject" size="45" value="<?=$adsubject?>">
    </td>
  </tr>
  <tr>
    <td align="right" valign="top">
      Description:
    </td>
    <td>
      <textarea rows="10" cols="70" name="addescription" onFocus="focused=true;" onBlur="focused=false;"><?=$addescription?></textarea>
    </td>
  </tr>
  <tr>
    <td align="right">Characters:</td>
    <td align="left">
      <input type="text" name="countaddescription" size="4" READONLY>&nbsp;&nbsp;Maximum of <?=$ad_description_length?> characters allowed.
    </td>
  </tr>
  <tr>
    <td align="right">
      Website URL:
    </td>
    <td>
      <input type="text" name="adurl" size="45" value="<?=$adurl?>">
    </td>
  </tr>
  <tr>
    <td colspan="2" align="center">
      <?php
        if ($_SESSION[aastatus]!="mem")
        {
          echo "      Upload your ad image or Logo.<br>Must be a <b>jpg</b> or <b>gif</b>. No larger than: <b>Width</b> and <b>Height</b> of <b>$logo_max_width</b> by <b>$logo_max_height</b>.\n    </td>\n    </tr>\n";
          echo "    <tr>\n  <td align=\"right\">Upload Logo:</td><td>\n      <input type=\"file\" size=\"35\" name=\"adimage\">\n   </td>\n";
        }
        else
          echo "<input type=\"hidden\" name=\"adimage\" value=\"none\"></td>\n";
      ?>
  </tr>
  <tr>
    <td colspan="2" align="center">
      <map name="map_webpal">
      <area coords="2,2,18,18" href="javascript:{;}" onClick="setColor('#330000');return 0">
      <area coords="18,2,34,18" href="javascript:{;}" onClick="setColor('#333300');return 0">
      <area coords="34,2,50,18" href="javascript:{;}" onClick="setColor('#336600');return 0">
      <area coords="50,2,66,18" href="javascript:{;}" onClick="setColor('#339900');return 0">
      <area coords="66,2,82,18" href="javascript:{;}" onClick="setColor('#33CC00');return 0">
      <area coords="82,2,98,18" href="javascript:{;}" onClick="setColor('#33FF00');return 0">

      <area coords="98,2,114,18" href="javascript:{;}" onClick="setColor('#66FF00');return 0">
      <area coords="114,2,130,18" href="javascript:{;}" onClick="setColor('#66CC00');return 0">
      <area coords="130,2,146,18" href="javascript:{;}" onClick="setColor('#669900');return 0">
      <area coords="146,2,162,18" href="javascript:{;}" onClick="setColor('#666600');return 0">
      <area coords="162,2,178,18" href="javascript:{;}" onClick="setColor('#663300');return 0">
      <area coords="178,2,194,18" href="javascript:{;}" onClick="setColor('#660000');return 0">

      <area coords="194,2,210,18" href="javascript:{;}" onClick="setColor('#FF0000');return 0">
      <area coords="210,2,226,18" href="javascript:{;}" onClick="setColor('#FF3300');return 0">
      <area coords="226,2,242,18" href="javascript:{;}" onClick="setColor('#FF6600');return 0">
      <area coords="242,2,258,18" href="javascript:{;}" onClick="setColor('#FF9900');return 0">
      <area coords="258,2,274,18" href="javascript:{;}" onClick="setColor('#FFCC00');return 0">
      <area coords="274,2,290,18" href="javascript:{;}" onClick="setColor('#FFFF00');return 0">

      <area coords="2,18,18,34" href="javascript:{;}" onClick="setColor('#330033');return 0">
      <area coords="18,18,34,34" href="javascript:{;}" onClick="setColor('#333333');return 0">
      <area coords="34,18,50,34" href="javascript:{;}" onClick="setColor('#336633');return 0">
      <area coords="50,18,66,34" href="javascript:{;}" onClick="setColor('#339933');return 0">
      <area coords="66,18,82,34" href="javascript:{;}" onClick="setColor('#33CC33');return 0">
      <area coords="82,18,98,34" href="javascript:{;}" onClick="setColor('#33FF33');return 0">

      <area coords="98,18,114,34" href="javascript:{;}" onClick="setColor('#66FF33');return 0">
      <area coords="114,18,130,34" href="javascript:{;}" onClick="setColor('#66CC33');return 0">
      <area coords="130,18,146,34" href="javascript:{;}" onClick="setColor('#669933');return 0">
      <area coords="146,18,162,34" href="javascript:{;}" onClick="setColor('#666633');return 0">
      <area coords="162,18,178,34" href="javascript:{;}" onClick="setColor('#663333');return 0">
      <area coords="178,18,194,34" href="javascript:{;}" onClick="setColor('#660033');return 0">

      <area coords="194,18,210,34" href="javascript:{;}" onClick="setColor('#FF0033');return 0">
      <area coords="210,18,226,34" href="javascript:{;}" onClick="setColor('#FF3333');return 0">
      <area coords="226,18,242,34" href="javascript:{;}" onClick="setColor('#FF6633');return 0">
      <area coords="242,18,258,34" href="javascript:{;}" onClick="setColor('#FF9933');return 0">
      <area coords="258,18,274,34" href="javascript:{;}" onClick="setColor('#FFCC33');return 0">
      <area coords="274,18,290,34" href="javascript:{;}" onClick="setColor('#FFFF33');return 0">

      <area coords="2,34,18,50" href="javascript:{;}" onClick="setColor('#330066');return 0">
      <area coords="18,34,34,50" href="javascript:{;}" onClick="setColor('#333366');return 0">
      <area coords="34,34,50,50" href="javascript:{;}" onClick="setColor('#336666');return 0">
      <area coords="50,34,66,50" href="javascript:{;}" onClick="setColor('#339966');return 0">
      <area coords="66,34,82,50" href="javascript:{;}" onClick="setColor('#33CC66');return 0">
      <area coords="82,34,98,50" href="javascript:{;}" onClick="setColor('#33FF66');return 0">

      <area coords="98,34,114,50" href="javascript:{;}" onClick="setColor('#66FF66');return 0">
      <area coords="114,34,130,50" href="javascript:{;}" onClick="setColor('#66CC66');return 0">
      <area coords="130,34,146,50" href="javascript:{;}" onClick="setColor('#669966');return 0">
      <area coords="146,34,162,50" href="javascript:{;}" onClick="setColor('#666666');return 0">
      <area coords="162,34,178,50" href="javascript:{;}" onClick="setColor('#663366');return 0">
      <area coords="178,34,194,50" href="javascript:{;}" onClick="setColor('#660066');return 0">

      <area coords="194,34,210,50" href="javascript:{;}" onClick="setColor('#FF0066');return 0">
      <area coords="210,34,226,50" href="javascript:{;}" onClick="setColor('#FF3366');return 0">
      <area coords="226,34,242,50" href="javascript:{;}" onClick="setColor('#FF6666');return 0">
      <area coords="242,34,258,50" href="javascript:{;}" onClick="setColor('#FF9966');return 0">
      <area coords="258,34,274,50" href="javascript:{;}" onClick="setColor('#FFCC66');return 0">
      <area coords="274,34,290,50" href="javascript:{;}" onClick="setColor('#FFFF66');return 0">

      <area coords="2,50,18,66" href="javascript:{;}" onClick="setColor('#330099');return 0">
      <area coords="18,50,34,66" href="javascript:{;}" onClick="setColor('#333399');return 0">
      <area coords="34,50,50,66" href="javascript:{;}" onClick="setColor('#336699');return 0">
      <area coords="50,50,66,66" href="javascript:{;}" onClick="setColor('#339999');return 0">
      <area coords="66,50,82,66" href="javascript:{;}" onClick="setColor('#33CC99');return 0">
      <area coords="82,50,98,66" href="javascript:{;}" onClick="setColor('#33FF99');return 0">

      <area coords="98,50,114,66" href="javascript:{;}" onClick="setColor('#66FF99');return 0">
      <area coords="114,50,130,66" href="javascript:{;}" onClick="setColor('#66CC99');return 0">
      <area coords="130,50,146,66" href="javascript:{;}" onClick="setColor('#669999');return 0">
      <area coords="146,50,162,66" href="javascript:{;}" onClick="setColor('#666699');return 0">
      <area coords="162,50,178,66" href="javascript:{;}" onClick="setColor('#663399');return 0">
      <area coords="178,50,194,66" href="javascript:{;}" onClick="setColor('#660099');return 0">

      <area coords="194,50,210,66" href="javascript:{;}" onClick="setColor('#FF0099');return 0">
      <area coords="210,50,226,66" href="javascript:{;}" onClick="setColor('#FF3399');return 0">
      <area coords="226,50,242,66" href="javascript:{;}" onClick="setColor('#FF6699');return 0">
      <area coords="242,50,258,66" href="javascript:{;}" onClick="setColor('#FF9999');return 0">
      <area coords="258,50,274,66" href="javascript:{;}" onClick="setColor('#FFCC99');return 0">
      <area coords="274,50,290,66" href="javascript:{;}" onClick="setColor('#FFFF99');return 0">

      <area coords="2,66,18,82" href="javascript:{;}" onClick="setColor('#3300CC');return 0">
      <area coords="18,66,34,82" href="javascript:{;}" onClick="setColor('#3333CC');return 0">
      <area coords="34,66,50,82" href="javascript:{;}" onClick="setColor('#3366CC');return 0">
      <area coords="50,66,66,82" href="javascript:{;}" onClick="setColor('#3399CC');return 0">
      <area coords="66,66,82,82" href="javascript:{;}" onClick="setColor('#33CCCC');return 0">
      <area coords="82,66,98,82" href="javascript:{;}" onClick="setColor('#33FFCC');return 0">

      <area coords="98,66,114,82" href="javascript:{;}" onClick="setColor('#66FFCC');return 0">
      <area coords="114,66,130,82" href="javascript:{;}" onClick="setColor('#66CCCC');return 0">
      <area coords="130,66,146,82" href="javascript:{;}" onClick="setColor('#6699CC');return 0">
      <area coords="146,66,162,82" href="javascript:{;}" onClick="setColor('#6666CC');return 0">
      <area coords="162,66,178,82" href="javascript:{;}" onClick="setColor('#6633CC');return 0">
      <area coords="178,66,194,82" href="javascript:{;}" onClick="setColor('#6600CC');return 0">

      <area coords="194,66,210,82" href="javascript:{;}" onClick="setColor('#FF00CC');return 0">
      <area coords="210,66,226,82" href="javascript:{;}" onClick="setColor('#FF33CC');return 0">
      <area coords="226,66,242,82" href="javascript:{;}" onClick="setColor('#FF66CC');return 0">
      <area coords="242,66,258,82" href="javascript:{;}" onClick="setColor('#FF99CC');return 0">
      <area coords="258,66,274,82" href="javascript:{;}" onClick="setColor('#FFCCCC');return 0">
      <area coords="274,66,290,82" href="javascript:{;}" onClick="setColor('#FFFFCC');return 0">

      <area coords="2,82,18,98" href="javascript:{;}" onClick="setColor('#3300FF');return 0">
      <area coords="18,82,34,98" href="javascript:{;}" onClick="setColor('#3333FF');return 0">
      <area coords="34,82,50,98" href="javascript:{;}" onClick="setColor('#3366FF');return 0">
      <area coords="50,82,66,98" href="javascript:{;}" onClick="setColor('#3399FF');return 0">
      <area coords="66,82,82,98" href="javascript:{;}" onClick="setColor('#33CCFF');return 0">
      <area coords="82,82,98,98" href="javascript:{;}" onClick="setColor('#33FFFF');return 0">

      <area coords="98,82,114,98" href="javascript:{;}" onClick="setColor('#66FFFF');return 0">
      <area coords="114,82,130,98" href="javascript:{;}" onClick="setColor('#66CCFF');return 0">
      <area coords="130,82,146,98" href="javascript:{;}" onClick="setColor('#6699FF');return 0">
      <area coords="146,82,162,98" href="javascript:{;}" onClick="setColor('#6666FF');return 0">
      <area coords="162,82,178,98" href="javascript:{;}" onClick="setColor('#6633FF');return 0">
      <area coords="178,82,194,98" href="javascript:{;}" onClick="setColor('#6600FF');return 0">

      <area coords="194,82,210,98" href="javascript:{;}" onClick="setColor('#FF00FF');return 0">
      <area coords="210,82,226,98" href="javascript:{;}" onClick="setColor('#FF33FF');return 0">
      <area coords="226,82,242,98" href="javascript:{;}" onClick="setColor('#FF66FF');return 0">
      <area coords="242,82,258,98" href="javascript:{;}" onClick="setColor('#FF99FF');return 0">
      <area coords="258,82,274,98" href="javascript:{;}" onClick="setColor('#FFCCFF');return 0">
      <area coords="274,82,290,98" href="javascript:{;}" onClick="setColor('#FFFFFF');return 0">

      <area coords="2,98,18,114" href="javascript:{;}" onClick="setColor('#0000FF');return 0">
      <area coords="18,98,34,114" href="javascript:{;}" onClick="setColor('#0033FF');return 0">
      <area coords="34,98,50,114" href="javascript:{;}" onClick="setColor('#0066FF');return 0">
      <area coords="50,98,66,114" href="javascript:{;}" onClick="setColor('#0099FF');return 0">
      <area coords="66,98,82,114" href="javascript:{;}" onClick="setColor('#00CCFF');return 0">
      <area coords="82,98,98,114" href="javascript:{;}" onClick="setColor('#00FFFF');return 0">

      <area coords="98,98,114,114" href="javascript:{;}" onClick="setColor('#99FFFF');return 0">
      <area coords="114,98,130,114" href="javascript:{;}" onClick="setColor('#99CCFF');return 0">
      <area coords="130,98,146,114" href="javascript:{;}" onClick="setColor('#9999FF');return 0">
      <area coords="146,98,162,114" href="javascript:{;}" onClick="setColor('#9966FF');return 0">
      <area coords="162,98,178,114" href="javascript:{;}" onClick="setColor('#9933FF');return 0">
      <area coords="178,98,194,114" href="javascript:{;}" onClick="setColor('#9900FF');return 0">

      <area coords="194,98,210,114" href="javascript:{;}" onClick="setColor('#CC00FF');return 0">
      <area coords="210,98,226,114" href="javascript:{;}" onClick="setColor('#CC33FF');return 0">
      <area coords="226,98,242,114" href="javascript:{;}" onClick="setColor('#CC66FF');return 0">
      <area coords="242,98,258,114" href="javascript:{;}" onClick="setColor('#CC99FF');return 0">
      <area coords="258,98,274,114" href="javascript:{;}" onClick="setColor('#CCCCFF');return 0">
      <area coords="274,98,290,114" href="javascript:{;}" onClick="setColor('#CCFFFF');return 0">

      <area coords="2,114,18,130" href="javascript:{;}" onClick="setColor('#0000CC');return 0">
      <area coords="18,114,34,130" href="javascript:{;}" onClick="setColor('#0033CC');return 0">
      <area coords="34,114,50,130" href="javascript:{;}" onClick="setColor('#0066CC');return 0">
      <area coords="50,114,66,130" href="javascript:{;}" onClick="setColor('#0099CC');return 0">
      <area coords="66,114,82,130" href="javascript:{;}" onClick="setColor('#00CCCC');return 0">
      <area coords="82,114,98,130" href="javascript:{;}" onClick="setColor('#00FFCC');return 0">

      <area coords="98,114,114,130" href="javascript:{;}" onClick="setColor('#99FFCC');return 0">
      <area coords="114,114,130,130" href="javascript:{;}" onClick="setColor('#99CCCC');return 0">
      <area coords="130,114,146,130" href="javascript:{;}" onClick="setColor('#9999CC');return 0">
      <area coords="146,114,162,130" href="javascript:{;}" onClick="setColor('#9966CC');return 0">
      <area coords="162,114,178,130" href="javascript:{;}" onClick="setColor('#9933CC');return 0">
      <area coords="178,114,194,130" href="javascript:{;}" onClick="setColor('#9900CC');return 0">

      <area coords="194,114,210,130" href="javascript:{;}" onClick="setColor('#CC00CC');return 0">
      <area coords="210,114,226,130" href="javascript:{;}" onClick="setColor('#CC33CC');return 0">
      <area coords="226,114,242,130" href="javascript:{;}" onClick="setColor('#CC66CC');return 0">
      <area coords="242,114,258,130" href="javascript:{;}" onClick="setColor('#CC99CC');return 0">
      <area coords="258,114,274,130" href="javascript:{;}" onClick="setColor('#CCCCCC');return 0">
      <area coords="274,114,290,130" href="javascript:{;}" onClick="setColor('#CCFFCC');return 0">

      <area coords="2,130,18,146" href="javascript:{;}" onClick="setColor('#000099');return 0">
      <area coords="18,130,34,146" href="javascript:{;}" onClick="setColor('#003399');return 0">
      <area coords="34,130,50,146" href="javascript:{;}" onClick="setColor('#006699');return 0">
      <area coords="50,130,66,146" href="javascript:{;}" onClick="setColor('#009999');return 0">
      <area coords="66,130,82,146" href="javascript:{;}" onClick="setColor('#00CC99');return 0">
      <area coords="82,130,98,146" href="javascript:{;}" onClick="setColor('#00FF99');return 0">

      <area coords="98,130,114,146" href="javascript:{;}" onClick="setColor('#99FF99');return 0">
      <area coords="114,130,130,146" href="javascript:{;}" onClick="setColor('#99CC99');return 0">
      <area coords="130,130,146,146" href="javascript:{;}" onClick="setColor('#999999');return 0">
      <area coords="146,130,162,146" href="javascript:{;}" onClick="setColor('#996699');return 0">
      <area coords="162,130,178,146" href="javascript:{;}" onClick="setColor('#993399');return 0">
      <area coords="178,130,194,146" href="javascript:{;}" onClick="setColor('#990099');return 0">

      <area coords="194,130,210,146" href="javascript:{;}" onClick="setColor('#CC0099');return 0">
      <area coords="210,130,226,146" href="javascript:{;}" onClick="setColor('#CC3399');return 0">
      <area coords="226,130,242,146" href="javascript:{;}" onClick="setColor('#CC6699');return 0">
      <area coords="242,130,258,146" href="javascript:{;}" onClick="setColor('#CC9999');return 0">
      <area coords="258,130,274,146" href="javascript:{;}" onClick="setColor('#CCCC99');return 0">
      <area coords="274,130,290,146" href="javascript:{;}" onClick="setColor('#CCFF99');return 0">

      <area coords="2,146,18,162" href="javascript:{;}" onClick="setColor('#000066');return 0">
      <area coords="18,146,34,162" href="javascript:{;}" onClick="setColor('#003366');return 0">
      <area coords="34,146,50,162" href="javascript:{;}" onClick="setColor('#006666');return 0">
      <area coords="50,146,66,162" href="javascript:{;}" onClick="setColor('#009966');return 0">
      <area coords="66,146,82,162" href="javascript:{;}" onClick="setColor('#00CC66');return 0">
      <area coords="82,146,98,162" href="javascript:{;}" onClick="setColor('#00FF66');return 0">

      <area coords="98,146,114,162" href="javascript:{;}" onClick="setColor('#99FF66');return 0">
      <area coords="114,146,130,162" href="javascript:{;}" onClick="setColor('#99CC66');return 0">
      <area coords="130,146,146,162" href="javascript:{;}" onClick="setColor('#999966');return 0">
      <area coords="146,146,162,162" href="javascript:{;}" onClick="setColor('#996666');return 0">
      <area coords="162,146,178,162" href="javascript:{;}" onClick="setColor('#993366');return 0">
      <area coords="178,146,194,162" href="javascript:{;}" onClick="setColor('#990066');return 0">

      <area coords="194,146,210,162" href="javascript:{;}" onClick="setColor('#CC0066');return 0">
      <area coords="210,146,226,162" href="javascript:{;}" onClick="setColor('#CC3366');return 0">
      <area coords="226,146,242,162" href="javascript:{;}" onClick="setColor('#CC6666');return 0">
      <area coords="242,146,258,162" href="javascript:{;}" onClick="setColor('#CC9966');return 0">
      <area coords="258,146,274,162" href="javascript:{;}" onClick="setColor('#CCCC66');return 0">
      <area coords="274,146,290,162" href="javascript:{;}" onClick="setColor('#CCFF66');return 0">

      <area coords="2,162,18,178" href="javascript:{;}" onClick="setColor('#000033');return 0">
      <area coords="18,162,34,178" href="javascript:{;}" onClick="setColor('#003333');return 0">
      <area coords="34,162,50,178" href="javascript:{;}" onClick="setColor('#006633');return 0">
      <area coords="50,162,66,178" href="javascript:{;}" onClick="setColor('#009933');return 0">
      <area coords="66,162,82,178" href="javascript:{;}" onClick="setColor('#00CC33');return 0">
      <area coords="82,162,98,178" href="javascript:{;}" onClick="setColor('#00FF33');return 0">

      <area coords="98,162,114,178" href="javascript:{;}" onClick="setColor('#99FF33');return 0">
      <area coords="114,162,130,178" href="javascript:{;}" onClick="setColor('#99CC33');return 0">
      <area coords="130,162,146,178" href="javascript:{;}" onClick="setColor('#999933');return 0">
      <area coords="146,162,162,178" href="javascript:{;}" onClick="setColor('#996633');return 0">
      <area coords="162,162,178,178" href="javascript:{;}" onClick="setColor('#993333');return 0">
      <area coords="178,162,194,178" href="javascript:{;}" onClick="setColor('#990033');return 0">

      <area coords="194,162,210,178" href="javascript:{;}" onClick="setColor('#CC0033');return 0">
      <area coords="210,162,226,178" href="javascript:{;}" onClick="setColor('#CC3333');return 0">
      <area coords="226,162,242,178" href="javascript:{;}" onClick="setColor('#CC6633');return 0">
      <area coords="242,162,258,178" href="javascript:{;}" onClick="setColor('#CC9933');return 0">
      <area coords="258,162,274,178" href="javascript:{;}" onClick="setColor('#CCCC33');return 0">
      <area coords="274,162,290,178" href="javascript:{;}" onClick="setColor('#CCFF33');return 0">

      <area coords="2,178,18,194" href="javascript:{;}" onClick="setColor('#000000');return 0">
      <area coords="18,178,34,194" href="javascript:{;}" onClick="setColor('#003300');return 0">
      <area coords="34,178,50,194" href="javascript:{;}" onClick="setColor('#006600');return 0">
      <area coords="50,178,66,194" href="javascript:{;}" onClick="setColor('#009900');return 0">
      <area coords="66,178,82,194" href="javascript:{;}" onClick="setColor('#00CC00');return 0">
      <area coords="82,178,98,194" href="javascript:{;}" onClick="setColor('#00FF00');return 0">

      <area coords="98,178,114,194" href="javascript:{;}" onClick="setColor('#99FF00');return 0">
      <area coords="114,178,130,194" href="javascript:{;}" onClick="setColor('#99CC00');return 0">
      <area coords="130,178,146,194" href="javascript:{;}" onClick="setColor('#999900');return 0">
      <area coords="146,178,162,194" href="javascript:{;}" onClick="setColor('#996600');return 0">
      <area coords="162,178,178,194" href="javascript:{;}" onClick="setColor('#993300');return 0">
      <area coords="178,178,194,194" href="javascript:{;}" onClick="setColor('#990000');return 0">

      <area coords="194,178,210,194" href="javascript:{;}" onClick="setColor('#CC0000');return 0">
      <area coords="210,178,226,194" href="javascript:{;}" onClick="setColor('#CC3300');return 0">
      <area coords="226,178,242,194" href="javascript:{;}" onClick="setColor('#CC6600');return 0">
      <area coords="242,178,258,194" href="javascript:{;}" onClick="setColor('#CC9900');return 0">
      <area coords="258,178,274,194" href="javascript:{;}" onClick="setColor('#CCCC00');return 0">
      <area coords="274,178,290,194" href="javascript:{;}" onClick="setColor('#CCFF00');return 0">
      </map>
      <table cellspacing="2" cellpadding="0" border="0">
      <tr>
        <td colspan="2"><hr></td>
      </tr>
      <tr>
        <td align="center" colspan="2">
          <font color="#000000"><b>Text</b>, <b>background colors</b> and <b>styles</b> for your ad.</font><br>
          <?php if ($_SESSION[aastatus]=="mem") echo "<b class=\"red\">As a FREE member, you can adjust the color settings, but they will not be applied.  In order to activate this feature you will need to <a href=\"$_SERVER[PHP_SELF]?option=upgrade\">UPGRADE</a> your status level."; ?>
          <hr>
        </td>
      </tr>
      <tr>
        <td valign="top">
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="choice" value="1" <?php if ($choice==1) echo "CHECKED"; if (!isset($choice)) echo "CHECKED"; ?>>Subject Font Color
          <input type="hidden" name="subject_text_color" value="<?php if (isset($subject_text_color)) echo $subject_text_color; else echo "#000000"; ?>"><br>
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="choice" value="2" <?php if ($choice==2) echo "CHECKED"; ?>>Description Font Color
          <input type="hidden" name="description_text_color" value="<?php if (isset($description_text_color)) echo $description_text_color; else echo "#FF0000"; ?>"><br>
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="choice" value="3" <?php if ($choice==3) echo "CHECKED"; ?>>Background color
          <input type="hidden" name="bg_color" value="<?php if (isset($bg_color)) echo $bg_color; else echo "#FFFFFF"; ?>"><br><br><br>
          <img src="images/null.gif" border="0" height="1" width="120"><b>Color Chart</b>
        </td>
        <td>
          <b>Subject Font Style</b><br>
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="subjectstylechoice" value="1" onClick="setStyle()" <?php if ($subjectstylechoice==1) echo "CHECKED"; if (!isset($subjectstylechoice)) echo "CHECKED"; ?>>Normal
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="subjectstylechoice" value="2" onClick="setStyle()" <?php if ($subjectstylechoice==2) echo "CHECKED"; ?>>Bold<br>
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="subjectstylechoice" value="3" onClick="setStyle()" <?php if ($subjectstylechoice==3) echo "CHECKED"; ?>>Italic&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="subjectstylechoice" value="4" onClick="setStyle()" <?php if ($subjectstylechoice==4) echo "CHECKED"; ?>>Bold Italic<br>
          <input type="hidden" name="subjectstylechoice1" value="<?php if (isset($subjectstylechoice1)) echo $subjectstylechoice1; else echo "font-style: normal; font-weight: normal;"; ?>">

          <b>Description Font Style</b><br>
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="descriptionstylechoice" value="1" onClick="setStyle()" <?php if ($descriptionstylechoice==1) echo "CHECKED"; if (!isset($descriptionstylechoice)) echo "CHECKED"; ?>>Normal
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="descriptionstylechoice" value="2" onClick="setStyle()" <?php if ($descriptionstylechoice==2) echo "CHECKED"; ?>>Bold<br>
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="descriptionstylechoice" value="3" onClick="setStyle()" <?php if ($descriptionstylechoice==3) echo "CHECKED"; ?>>Italic&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          <input type="radio" style="border-top-width:0px;border-bottom-width:0px;border-right-width:0px;border-left-width:0px;" name="descriptionstylechoice" value="4" onClick="setStyle()" <?php if ($descriptionstylechoice==4) echo "CHECKED"; ?>>Bold Italic
          <input type="hidden" name="descriptionstylechoice1" value="<?php if (isset($descriptionstylechoice1)) echo $descriptionstylechoice1; else echo "font-style: normal; font-weight: normal;"; ?>">
        </td>
      </tr>
      <tr>
        <td>
          <img src="../images/colorchart.gif" width="292" height="196" border="0" alt="" usemap="#map_webpal" ismap>
        </td>
        <td id="bg" bgcolor="<?=$bg_color?>" align="left" style="padding: 8px">
          <p><font size="3"><em id="subjectfont" color="<?=$subject_text_color?>" style="<?=$subjectstylechoice1?>">Ad subject text here.</em></p><br><em id="descriptionfont" color="<?=$description_text_color?>" style="<?=$descriptionstylechoice1?>">Ad description here.</em></font><br>
          <img src="images/null.gif" border="0" height="1" width="160">
        </td>
      </tr>
    </table>
  </tr>
  </td>
  </tr>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td valign="top" align="left">
      <input type="submit" class="greenbutton" value="Post Ad">
    </td>
    <td valign="top" align="right">
      <input type="hidden" name="submitted" value="1">
      <input type="button" class="redbutton" value="Abort Post" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
      </form>
    </td>
  </tr>
  <tr>
    <td align="center" colspan="2"><input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'"></td>
  </tr>
</table>
</body>
</html>