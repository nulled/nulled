<?php

// http://andyydev.com/project.php?file=captcha

$post_to_domain = 'www.example.com';
$post_to_page = '/myform.pl';
$is_https = 0; // set to 1 if https://
$success_text = 'Thank you for your submittion.';
$secret_key = 'blah';

$font_path  = realpath('.').'/font.ttf';
$images_dir = 'keys';

// ---------------------------------------------------------
// do not edit below this line unless you know what is up...
// ---------------------------------------------------------
$time_limit = 60; // seconds

// create image and colors
$im    = ImageCreate(50, 25);
$white = ImageColorAllocate($im, 255, 255, 255);
$black = ImageColorAllocate($im, 0, 0, 0);

// fill image
ImageFill($im, 0, 0, $white);

srand((double)microtime()*1000000);
$codekey = substr((string)md5(rand()), 0, 3);
$time_proof = time() + $time_limit;
$validate = md5($time_proof.$codekey.$time_proof.$secret_key).$time_proof.'S'.strlen($time_proof);

// write string in black
ImageTTFText($im, 20, 0, 0, 22, $black, $font_path, $codekey);

if ($dir = @opendir($images_dir))
{
  while($file = readdir($dir))
  {
    if ($file != '.' && $file != '..')
    {
      $deletetime = time() - 60;
      $modified = stat("$images_dir/$file");
      if ($modified[9] < $deletetime)
        @unlink("$images_dir/$file");
    }
  }
  closedir($dir);
}

$i = 0;
while (1)
{
  $i++;
  if ($i > 1000) exit('ERROR: Unable to generate random key image filename.');

  srand((double)microtime()*1000000);
  $keyfilename = substr((string)md5(rand()), 0, 20).'.jpg';

  if(@file_exists("$images_dir/$keyfilename"))
    continue;
  else
    break;
}

$fp = @fopen("$images_dir/$keyfilename", "w");
@fclose($fp);

// create image
chmod("$images_dir/$keyfilename", 0777);
ImageJPEG($im, "$images_dir/$keyfilename");

$form_fields = '
<img src="'.$images_dir.'/'.$keyfilename.'" border="0" />
<input type="text" name="key" size="4" />
<input type="hidden" name="validate" value="'.$validate.'">
';

function post($domain, $page, $postvars, $port=80, $timeout=15)
{
  $req = '';

  if (count($postvars)) foreach ($postvars as $key => $value) $req .= '&'.urlencode(stripslashes($key)).'='.urlencode(stripslashes($value));
  else
    exit('ERROR: No postvars given in.');

  // post to page
  $header  = "POST ".$page." HTTP/1.0\r\n";
  $header .= "Content-Type: application/x-www-form-urlencoded\r\n";
  $header .= "Content-Length: ".strlen($req)."\r\n\r\n";

  if (! $fs=@fsockopen($domain, $port, $errno, $errstr, $timeout))
    exit('ERROR: '.$errstr.' ('.$errno.') fsockopen() POST to <font color="blue">'.$page.'</font><br />domain='.$domain.' port='.$port.' timeout='.$timeout);
  else
  {
    if (! @fputs($fs, $header.$req))
    {
      @fclose($fs);
      exit('ERROR: fputs() in post_to_page() POST to <font color="blue">'.$page.'</font><br />domain='.$domain.' port='.$port.' timeout='.$timeout);
    }
    $res = '';
    while(! @feof($fs)) $res .= @fgets($fs, 4096);
    // echo "<pre>".$res."\n</pre>";
  }
  @fclose($fs);
}

if ($_POST['validate'])
{
  // see if turing key is within time limits
  $time_good = 0;
  $current_time = time();
  $parts = explode('S', $_POST['validate']);
  $time_sent = substr($parts[0], strlen($parts[0]) - $parts[1], $parts[1]);
  $v = substr($parts[0], 0, strlen($parts[0]) - $parts[1]);
  $time_max = $current_time + $time_limit;
  if ($current_time <= $time_sent && $time_sent <= $time_max)
    $time_good = 1;

  // check if key present, then if key is correct
  if (! $key) $notValid = "ERROR: Missing Turing Key.";
  else if (md5($time_sent.$key.$time_sent.$secret_key) == $v && $time_good)
  {
    if ($is_https) $port = 143; else $port = 80;
    post($post_to_domain, $post_to_page, $_POST, $port);
    exit($success_text);
  }
  else
    $notValid = "ERROR: Invalid Turing Key.";
}

?>
