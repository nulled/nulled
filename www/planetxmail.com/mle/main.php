<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/sessionsecure.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$maillist_redirect = true;

if ($option == '' OR strstr($option, '/'))
  $option = 'titlepage';
else if ($option == 'sendmail' AND $submitted != 'mail' AND $nextmaildate AND substr($lastvacation, 0, 1) == '0' AND $vacation == 0) {}
else if (($option == 'sendmail' AND $submitted == 'mail') OR ($option == 'sendmailcredits' AND $submitted == 'mailcredits'))
  $option = 'maillist';

if (! is_file('/home/nulled/www/planetxmail.com/mle/mlpsecure/' . $option . '.inc'))
  $option = 'titlepage';

require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/' . $option . '.inc');

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<title><?=$program_name?> - Main Menu</title>
<link rel="stylesheet" type="text/css" href="css_mlp.css" />
<script type="text/javascript" src="submitsupressor.js"></script>
<?php
if (($option == 'sendmail' OR $option == 'sendmailcredits') AND $nextmaildate AND substr($lastvacation, 0, 1) == '0' AND ! $vacation)
  echo '<script type="text/javascript" src="countdown.js"></script>'."\n";

if ($html AND ($option == 'sendmail' OR $option == 'sendmailcredits'))
{
  // not updated as it is default already at 5000, we need to lower this to 1500 like a  SOLO AD
  //$email_length = $email_length + 3500;

  echo '<script src="/tinymce/tinymce.min.js"></script>
<script>
tinymce.init({

  selector: "textarea",
  theme: "modern",

  plugins: ["advlist autolink autosave link image lists charmap preview hr anchor pagebreak",
            "searchreplace visualblocks visualchars code insertdatetime media nonbreaking",
            "table contextmenu directionality emoticons template textcolor paste"],

  toolbar: "undo redo | emoticons | forecolor | link image | bold italic | fontselect fontsizeselect | preview",
  relative_urls: false,
	remove_script_host: false,
	convert_urls: false,
	autoresize_max_height: 750,
	menubar: true,
  toolbar_items_size: "small",

	setup: function(ed) {
    ed.on("KeyUp", function(ed,evt) {
      //chars_without_format = tinymce.activeEditor.getContent().replace(/(<([^>]+)>)/ig,"").length;
      document.sendmail.countmessage.value = maxchars - tinymce.activeEditor.getContent().length;
    });
    ed.on("Click", function(ed,evt) {
      document.sendmail.countmessage.value = maxchars - tinymce.activeEditor.getContent().length;
    });
  }

});
</script>
';
}
?>
<script>
var focused = false;
var maxchars = <?=$email_length?>;
function updateCount()
{
<?php

  if ($option == 'sendmail' OR $option == 'sendmailcredits')
    echo '  if (focused) document.sendmail.countmessage.value = maxchars - document.sendmail.message.value.length;'."\n";
?>
}

function urlTrackerChoice(option, urltracker)
{
  if (option==1)
  {
    if (document.urllist.urlID.value == '')
      alert('Please select a URL Tracker name from list.');
    else
     location.href = 'main.php?option=viewurltracker&tracker=' + urltracker;
  }
  else if (option==2)
  {
    if (document.urllist.urlID.value=='')
      alert('Please select a URL Tracker name from list.');
    else
    {
      if (confirm('All statistics associated with this tracker will be lost FOREVER!\nAre you sure you want to delete?'))
      {
        document.urllist.submitteddelview.value = 2;
        document.urllist.submit();
      }
    }
  }
}

function openurlstats(option, name)
{
  var data = 'generateurltrackingdata.php?mode=' + option + '&uID=<?=$_SESSION['aauserID']?>&tracker=' + name + '&list=<?=$_SESSION['aalistname']?>&id=<?=$_SESSION['aalistownerID']?>';
  window.open(data, 'Url_Tracking_Statistics', 'top=100,left=100,resizable,scrollbars,width=600,height=300');
}

function selectAll()
{
  document.urltracker.tracker.focus();
  document.urltracker.tracker.select();
}

function checkCount()
{
  if (document.sendmail.subject.value.length > <?=$email_subject_length?>)
    alert ('Subject exceeds <?=$email_subject_length?> Characters.');
  else if (<?php if (! $html) echo 'document.sendmail.message.value.length'; else echo 'tinymce.activeEditor.getContent().length'; ?> > <?=$email_length?>)
    alert ('Message exceeds <?=$email_length?> Characters.');
  else if (document.sendmail.subject.value.length < 1)
    alert ('Missing Subject!');
  else if (<?php if (! $html) echo 'document.sendmail.message.value.length'; else echo 'tinymce.activeEditor.getContent().length'; ?> < 1)
    alert ('Missing Message!');
  else
    return true;

  return false;
}

function doSubmit(obj)
{
  if (checkCount() == true)
  {
    obj.value = 'Loading ...';
    obj.disabled = true;
    obj.form.submit();
  }
}

function preSubmit(obj)
{
  obj.value = 'Loading ...';
  obj.disabled = true;
  obj.form.submit();
}

<?php

  $onvacation = (substr($lastvacation, 0, 1) == '0' AND ! $vacation) ? 0 : 1;
  $clockstr   = "countto='$nextmaildate'; servertime='$servertime'; startclock();";

  $onload = '';

  if ($option == 'sendmail' AND $submitted != 'mail' AND $nextmaildate AND ! $onvacation)
    $onload = $clockstr;
  else if ($option == 'sendmailcredits' AND $submitted != 'mailcredits' AND $nextmaildate AND ! $onvacation)
    $onload = $clockstr;

  if ($option == 'sendmail' OR $option == 'sendmailcredits')
    $onload .= ' document.sendmail.countmessage.value = maxchars - document.sendmail.message.value.length; changecontent();';

  if ($html)
    echo 'window.onload = function(){document.sendmail.countmessage.value = maxchars - tinymce.activeEditor.getContent().length; changecontent();}' . "\n";
  else
  {
    echo 'document.onkeyup = updateCount;' . "\n";
    echo 'window.onload = function() {' . $onload . '}' . "\n";
  }
?>
</script>
<style>
.menu_td {
  text-align: center;
  background: #FFFFFF url('images/tab_lightblue.jpg');
  background-repeat: repeat-y;
  background-position: center;
  white-space: nowrap;
}
.notValid {
  border: 1px solid #fa0a0a;
  margin: 5px auto;
  background-color: #ffc0c5;
  text-align: center;
  padding: 10px;
  border-radius: 10px;
}
.banned {
  color: red;
  font-weight: bold;
}
</style>
</head>
<?php flush(); ?>
<body>
<table style="border: 1px solid gray;border-radius:10px;" align="center" cellspacing="0" cellpadding="5" width="800">
  <tr>
    <td align="center">
      <table cellspacing="1" cellpadding="3" border="0">
        <tr>
          <td colspan="10" align="center">
            <img src="<?php if ($titleIMG) echo "admin/$titleIMG"; else echo "images/title.gif"; ?>" border="0">
            <hr>
          </td>
        </tr>

        <?php if ($bannerIMG) echo '<tr><td align="center" colspan="8"><a href="' . $bannerLINK . '" target="_blank"><img src="admin/' . $bannerIMG . '" border="0"></a></td></tr>'."\n"; ?>

        <tr>
          <td colspan="10" align="center">
            <a href="http://planetxmail.com/soloads.php?list=<?=$_SESSION['aalistname']?>"><b>SOLO ADs to 135,000+</b></a> |
            <a href="http://targetedadplanet.com/" target="_blank"><font color="red"><b>NEW! - Post Your Free Ad</b></font></a>
            <br /><br />
          </td>
        </tr>

        <tr>
          <td bgcolor="lightblue" align="center"><a href="main.php"><font size="2">Home</font></a></td>
          <td class="menu_td"><a href="main.php?option=memberprofile"><font size="2">Member Profile</font></a></td>
          <td class="menu_td"><a href="main.php?option=sendmail"><font size="2">Regular Mailer</font></a></td>
          <td class="menu_td"><a href="main.php?option=sendmailcredits"><font size="2">Credits Mailer</font></a></td>
          <td class="menu_td"><a href="http://planetxmail.com/blogblast/index.php"><font size="2">Blogger Blast</font></a></td>
          <td class="menu_td"><a href="main.php?option=urltrackers"><font size="2">URL Trackers</font></a></td>
          <?php if ($referer) echo '<td class="menu_td"><a href="main.php?option=memberaffview"><font size="2">Affiliate Stats</font></a></td>'."\n"; ?>
          <td bgcolor="pink" align="center"><a href="main.php?option=logout"><font size="2">Logout</font></a></td>
        </tr>

        <tr>
          <td colspan="10" align="center">
          <?php
            if ($option != 'maillist') require_once('/home/nulled/www/planetxmail.com/mle/' . $option . '.php');
          ?>
          </td>
        </tr>

        <tr>
          <td align="center" colspan="10">

            <hr />
            <a href="safelistfaq.php" target="_BLANK">F.A.Q.</a> |
            <!-- <a href="http://planetxmail.com/wondersites.php" target="_blank">Profit Making Products!</a> | -->
            <a href="../links.php" target="_blank">FREE Link Exchange</a> |
            <a href="http://targetedadplanet.com" target="_blank">Targeted AD Planet</a> |
            <a href="../what_to_do_credits.php" target="_blank">What To Do With Your Credits</a> |
            <a href="../creditmailerhowto.php" target="_blank">Howto use Credit Mailer</a>

            <br />

            <!-- <a href="http://planetxmail.com/lists4sale.php" target="_BLANK">SafeLists 4 Sale!</a> |
            <a href="http://planetxmail.com/ebooks" target="_BLANK">9 eBooks</a> |
            <a href="http://planetxmail.com" target="_blank">Run YOUR own Credit Based SafeList</a> | -->

          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>

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