<?php
require_once('/home/nulled/config.inc');
// service php5-fpm stop && service nginx stop && service mysql stop && service mysql start && service nginx start && service php5-fpm start
// find ./ -name "*.php" -exec sed -i 's/file_get_contents/file_get_contents/g' {} \; && find ./ -name "*.inc" -exec sed -i 's/stri_replace/str_ireplace/g' {} \;
// $headers = 'From: Planet X Mail <do_not_reply@planetxmail.com>';

// find ./ -name "*.php" -exec grep 'EmailFormat' {} \;
/*
The special regular expression characters are: . \ + * ? [ ^ ] $ ( ) { } = ! < > | : -
preg_​filter
preg_​grep
preg_​last_​error
int preg_match_all ( string $pattern , string $subject [, array &$matches [, int $flags = PREG_PATTERN_ORDER [, int $offset = 0 ]]] )
int preg_match     ( string $pattern , string $subject [, array &$matches [, int $flags = 0 [, int $offset = 0 ]]] )
string preg_quote  ( string $str [, string $delimiter = NULL ] )
mixed preg_replace ( mixed $pattern , mixed $replacement , mixed $subject [, int $limit = -1 [, int &$count ]] )
array preg_split   ( string $pattern , string $subject [, int $limit = -1 [, int $flags = 0 ]] )
*/

$db = new MySQL_Access('mle');

if ($_POST['submitted'] == 'mail')
{
  $subject = $_POST['subject'];
  $message = $_POST['message'];

  if ($subject AND $message)
  {
    $headers  = "From: Matt <do_not_reply@planetxmail.com>\n";
    $headers .= "MIME-Version: 1.0\nContent-type: text/html; charset=iso-8859-1\n";

    //mail('elitescripts2000@yahoo.com', $subject, $message, $headers);
    //mail('admin.email@planetxmail.com', $subject, $message, $headers);
    //mail('elitescripts2000@gmail.com', $subject, $message, $headers);
    
    //$message = preg_replace('/(?:(?:\r\n|\r|\n)\s*){2}/s', "\n\n", $message);

    $print_pre = $message;

    $notValid = 'Email was Sent.';
  }
  else
    $notValid = 'ERROR: Missing Subject and/or Message.';
}

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Test Form</title>
<script src="/tinymce/tinymce.min.js"></script>
<script>
/*
tinymce.init({

  selector: "textarea",
  theme: "modern",
  plugins: ["advlist autolink autoresize code emoticons hr preview media legacyoutput link image table textcolor visualblocks visualchars wordcount"],
  toolbar: "undo redo | emoticons | forecolor backcolor | link image media | bold italic | fontselect fontselectsize | preview",
  relative_urls: false,
	remove_script_host: false,
	convert_urls: false

});
*/
</script>
<style>
pre {
  font-size: 12px;
}
.main {
  width: 600px;
  margin: 10px auto;
  border: 1px solid black;
  border-radius: 10px;
  padding: 10px;
}
.mailform {
  border: 0px solid #000000;
  margin: 20px auto;
  padding: 5px;
  text-align: left;
}
.notValid {
  border: 1px solid #ff0000;
  background-color: #ffc2c2;
  border-radius: 10px;
  padding: 5px;
  margin: 10px auto;
  text-align: center;
  width: 400px;
}
</style>
</head>
<body>

<div class="main">

<?php if ($notValid) echo '<div class="notValid">' . $notValid . '</div>'."\n"; ?>

<form class="mailform" action="testform.php" method="post">
  Subject:
  <br />
  <input type="text" name="subject" value="<?=$subject?>" size="60" maxlength="80" />
  <br />
  Message:
  <br />
  <textarea rows="10" cols="50" name="message"><?=$message?></textarea>
  <input type="button" value="Send" onclick="this.value='Loading...';this.disabled=true;this.form.submit()" />
  <input type="hidden" name="submitted" value="mail" />
</form>
<?php
echo '<pre>';
echo $print_pre;
echo '</pre>'."\n";
?>

</div>

</body>
</html>
