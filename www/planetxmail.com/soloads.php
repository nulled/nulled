<?php
require_once('/home/nulled/www/planetxmail.com/phpsecure/soloads.inc');
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title>Planet X Mail - Solo Ads</title>
<link rel="stylesheet" type="text/css" href="x.css" />
<script src="/tinymce/tinymce.min.js"></script>
<script>
var focused = false;
var maxchars = <?php if ($html) echo '5000'; else echo '1500'; ?>;
function updateCount()
{
  if (focused) document.soload.countmessage.value = maxchars - document.soload.message.value.length;
}
function preSubmit(obj)
{
  var d = document.soload;

  if (d.countmessage.value < 0)                alert('Message greater than ' + maxchars + ' Characters.');
  else if (d.subject.value.length > 70)        alert('Subject greater than 70 Characters.');
  else if (d.subject.value.length < 1)         alert('Missing Subject.');
  else if (<?php if (! $html) echo 'd.message.value.length'; else echo 'tinymce.activeEditor.getContent().length'; ?> < 1)         alert('Missing Message.');
  else if (d.name.value.length < 1)            alert('Missing your Name.');
  else if (d.email.value.length < 1)           alert('Missing your Contact Email.');
  else if (d.crediturl.value.length < 1)       alert('Missing your Credit URL.');
  else
  {
    if (confirm('Make SURE that your AD is HOW YOU WANT IT!\nOnce submitted you CAN NOT request a RE-MAIL\ndue to missing URLs or Email Contacts you MEANT\nto include in the AD!\n\nSince our systems are automated your Solo AD is\nmailed within minutes from submittion.\n\nClick OK to Submit your SOLO AD as is.\n\nClick CANCEL to go back and make changes.'))
    {
      obj.value = 'Loading ...';
      obj.disabled = true;
      obj.form.submit();
    }
  }
}
<?php
if ($html)
{
  echo '
tinymce.init({

  selector: "textarea#message",
  theme: "modern",
  plugins: ["advlist autolink autosave link image lists charmap preview hr anchor pagebreak",
            "searchreplace visualblocks visualchars code insertdatetime media nonbreaking",
            "table contextmenu directionality emoticons template textcolor paste"],

  toolbar: "undo redo | emoticons | forecolor backcolor | link image media | bold italic | fontselect fontsizeselect | preview",
  relative_urls: false,
	remove_script_host: false,
	convert_urls: false,
	autoresize_max_height: 750,
	menubar: true,
  toolbar_items_size: "small",

	setup: function(ed) {
    ed.on("KeyUp", function(ed,evt) {
      //chars_without_format = tinymce.activeEditor.getContent().replace(/(<([^>]+)>)/ig,"").length;
      //chars_with_format = tinymce.activeEditor.getContent().length;
      document.soload.countmessage.value = maxchars - tinymce.activeEditor.getContent().length;
    });
    ed.on("Click", function(ed,evt) {
      document.soload.countmessage.value = maxchars - tinymce.activeEditor.getContent().length;
    });
  }

});
';
}

if ($html)
  echo 'window.onload = function(){document.soload.countmessage.value = maxchars - tinymce.activeEditor.getContent().length;}' . "\n";
else
{
  echo 'document.onkeyup = updateCount;' . "\n";
  echo 'window.onload = function(){document.soload.countmessage.value = maxchars - document.soload.message.value.length;}' . "\n";
}
?>
</script>
<style>
input {
  padding: 5px;
  font-size: 14px;
  border-radius: 5px;
}
body {
  margin: 10px 0;
  text-align: center;
  font-family: verdana, arial;
  background: #ffffff url('/images/solo_ad_bg.jpg') repeat;
}
.main {
  border: 1px solid #7a7a7a;
  border-radius: 10px;
  width: 640px;
  margin: 5px auto;
  text-align: center;
  padding: 10px;
  font-size: 14px;
}
.main_sub {
  text-align: left;
}
.notValid {
  margin: 15px auto;
  font-weight: bold;
  background-color: #FFB0CD;
  text-align: center;
  padding: 5px;
  border: 1px solid #913C5B;
  border-radius: 10px;
  width: 350px;
}
.htmlcheck {
  color: #b50000;
  font-size: 14;
}
</style>
</head>
<?php flush(); ?>
<body>
<div class="main">
  <img src="/images/solo_ad_title.jpg" />
  <h3>Get Massive Hits!</h3>
    <script src="http://connect.facebook.net/en_US/all.js#xfbml=1"></script><fb:like href="http://planetxmail.com/soloads.php" layout="button_count" show_faces="false" width="50" font="verdana"></fb:like>
    <a href="http://twitter.com/share" class="twitter-share-button" data-count="none" data-via="planetxmail">Tweet</a><script type="text/javascript" src="http://platform.twitter.com/widgets.js"></script>
    <br /><br />

    <div class="main_sub">
      Looking for a way to send <i>your</i> AD to <b>TENS of thousands</b> of people?
      <br /><br />
      Look no further!
      <br /><br />
      Our <b>vast</b> SafeList network, <b>Planet <i>X</i> Mail</b> has over
      <b>150+</b> List Owners that are managing over <b>245+</b> SafeLists totaling <b>135,000+ members!</b>
      All of them being <u>Active Email Readers</u>!
      <br /><br />
      <font color="red"><b>100% <i>Double Optin</i></b></font> - <b>100%</b> SPAM FREE
      <br /><br />
      <font size="3">Below is a <b>REAL TIME</b> count of our network:</font><br />
      <font size="1">These numbers are queried <i>directly</i> from our datebases.</font>
      <ul>
        <li><?=$totalowners?> <b>List Owners</b>.</li>
        <li><?=$totallists?> <b>Safelists</b>.</li>
        <li><?=$totalmembers?> <b>active members</b>.</li>
      </ul>

      <font size="1"><b>Note:</b> All our addresses are Double-Optin from all <?=$totallists?> of the SafeLists that
      our Company Hosts.</font>
      <br /><br />

      <font color="red"><b>New!</b></font> <b>Your Solo AD will <i>also</i> be mailed to <b>all</b> FreeAdPlanet.com members!</b>
      Free AD Planet and Targeted AD Planet are extremely active sites totalling over <i>50,000 members!</i> Your Solo AD just got an added kick!
      <a href="http://targetedadplanet.com" target="_blank">Click to visit Targeted Ad Planet.com</a> and see for yourself.
      <br />

      <p style="background-color:beige;padding:5px;border:1px solid #DBDBDB;border-radius:10px;">
        <b>Note:</b>  This Solo AD service is <i>seperate</i> from ANY SafeList you may have signed up with. Please, do not contact
        the list owner asking why this is seperate, as it is a service that Planet X Mail is offering to everyone.
        <a href="openticket.php" target="_blank">Open a Ticket</a> for further questions.
      </p>

      <p style="background-color:#CCFFD4;text-align:left;padding:5px;border:1px solid #DBDBDB;border-radius:10px;">
        Solo ADs are mailed to the <b>Contact Address</b> of every Safelist Member.
        This produces a Solo AD that is <u>highly</u> visible! Readers also earn 5x more credits than regular mails! Your AD
        will be displayed when members <b>Mail Out using the Regular and Credit Mailers</b>, When </b>Earning Credits</b>, at our
        <b>Link Exchange</b> and other various places in and around our SafeList Network!
      </p>

      Customize your Solo AD! Works in the <b>AD Subject</b> and <b>AD Message</b>.
      <ul>
        <li><b>[first_name]</b> - Replaced by each members First Name.</li>
      </ul>

      <hr />

      <?php if ($notValid) echo '<div class="notValid">' . $notValid . '</div>'; ?>

      <form name="soload" action="soloads.php" method="POST">

        <b>Your Name:</b><br />
        <input type="text" name="name" value="<?=$name?>" size="25" maxlength="40" />

        <br /><br />
        <b>Your Contact Email:</b> <font size="1">For <i>receipt purposes <b>only.</b></i></font><br />
        <input type="text" name="email" value="<?=$email?>" size="45" maxlength="255" />

        <br /><br />
        <b>Credit URL:</b> <font size="1">Readers earn 5x the regular amount of credits!</font><br />
        <input type="text" name="crediturl" value="<?=$crediturl?>" size="60" maxlength="255" /><br />
        <font size="1"><i>Example: http://yoursite.com</i></font>

        <br /><br />
        <b>AD Subject:</b> <font size="1">No Deceptive titles or Porn. *Read below</font><br />
        <input type="text" name="subject" value="<?=$subject?>" size="65" maxlength="70" /><br />
        <font size="1"><i><u>Never</u> use ALL CAPS and <u>Avoid</u> none Letters/Numbers or the AD could be tagged as Spam.</i></font>

        <br /><br />
        <b>AD Message:</b> <?php if (! $html) echo '<span class="htmlcheck"><b>New!</b> Check <input type="checkbox" onclick="location.href=\'/soloads.php?l='.$l.'&html=1\'" /> to Enable HTML Editor! Currently entered Data will be lost.</span>'; else echo 'If you know HTML, use Menu - Tools - Source Code to directly code.'; ?>
        <textarea id="message" rows="20" cols="70" name="message" onFocus="focused=true" onBlur="focused=false"><?=ex_stripslashes($message)?></textarea>

        <?php
        echo '<hr /><input type="text" name="countmessage" size="3" readonly="readonly" /> <font size="2">Characters Remaining</font>';
        if (! $html) echo ' - <b>Advice:</b> <i>One paragraph or less gets <u>Best</u> Results.</i>';
        else echo ' - Number Includes the HTML Markup plus the Visible Text.';
        ?>

        <input type="hidden" name="submitted" value="send" />
        <input type="hidden" name="html" value="<?=$html?>" />

        <hr />

        <div style="text-align:center">
          <input type="button" name="submitButton" class="greenbutton" value="Submit Your <?php if ($html) echo 'HTML'; else echo 'Plain Text'; ?> Solo AD" onclick="preSubmit(this)" />
          <br /><br />
          <script src="http://connect.facebook.net/en_US/all.js#xfbml=1"></script><fb:like href="http://planetxmail.com/soloads.php" layout="button_count" show_faces="false" width="50" font="verdana"></fb:like>
          <a href="http://twitter.com/share" class="twitter-share-button" data-count="none" data-via="planetxmail">Tweet</a><script type="text/javascript" src="http://platform.twitter.com/widgets.js"></script>
        </div>

      </form>

      <p>
        <b>*</b> If your Subject and/or Message contains Deceptive texts like, "Notification Of Payment Received", "Confirm your list address"
        or the like, your Solo AD will NOT be sent. Also, <b>Absolutely No Porn</b>, this includes any Women's sexy clothes. It angers them.
        No Anti-Govt or Anti-Religeon. Save all that stuff for message boards that are made for such topics!
        <b>Angry readers</b> (mostly women) will come knocking on Your door (and mine!) with Pitch Forks and Torches in Hand!
      </p>
      <p>
        <textarea name="disclaimer" rows="5" cols="70">DISCLAIMER

        Although many clients get good results from Solo AD mailings, we cannot guarantee results from using our service, as this largely depends on market demand for your product or service and your ability to write ads that create a desire for the product or service in the readers mind, and as such, we do Not offer refunds with Planet X Mail Solo Ads service.  We do however guarantee that your ad will reach the number of people ordered.
        </textarea>
      </p>
  </div>

  <div style="text-align:center;font-size:10px">
    All Rights Reserved &copy; 2001 - <?=date('Y')?> - planetxmail.com - <a href="/openticket.php" target="_blank">Contact Support</a>
  </div>
</div>

<script type="text/javascript" src="http://edge.quantserve.com/quant.js"></script>
<script type="text/javascript">
_qacct="p-a26V9rP8NfTY2";quantserve();</script>
<noscript>
<img src="http://pixel.quantserve.com/pixel/p-a26V9rP8NfTY2.gif" style="display: none" height="1" width="1" alt="Quantcast"/>
</noscript>
<script src="http://www.google-analytics.com/urchin.js" type="text/javascript">
</script>
<script type="text/javascript">
_uacct = "UA-2323813-1";
urchinTracker();
</script>

</body>
</html>
