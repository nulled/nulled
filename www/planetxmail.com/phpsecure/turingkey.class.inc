<?php

class TuringKey
{
  public $time_limit;
  public $keyfilename;
  public $validate;

  function TuringKey($time_limit=90)
  {
    $this->time_limit = $time_limit;
    $this->createkey();
  }

  function createkey()
  {
    // create image and colors
    $im    = ImageCreate(65, 25);
    $white = ImageColorAllocate($im, 255, 255, 255);
    $black = ImageColorAllocate($im, 0, 0, 0);

    // fill image
    ImageFill($im, 0, 0, $white);

    $codekey = substr(mt_rand(), 0, 4);
    $time_proof = time() + $this->time_limit;
    $this->validate = strrev(md5(md5(strrev($time_proof.$codekey.$time_proof)))).$time_proof."S".strlen($time_proof);

    // write string in black
    ImageTTFText($im, 20, 0, 0, 25, $black, "/home/nulled/www/planetxmail.com/mle/images/font.ttf", $codekey);

    if ($dir = @opendir("/home/nulled/www/planetxmail.com/mle/keyimages"))
    {
      while($file = readdir($dir))
      {
        if ($file != "." AND $file != "..")
        {
          $deletetime = time() - 60;
          $modified = stat("/home/nulled/www/planetxmail.com/mle/keyimages/$file");
          if ($modified[9] < $deletetime)
            @unlink("/home/nulled/www/planetxmail.com/mle/keyimages/$file");
        }
      }
      closedir($dir);
    }

    while (1)
    {
      $keyfilename = md5(md5(mt_rand())).".jpg";
      if(@file_exists("/home/nulled/www/planetxmail.com/mle/keyimages/$keyfilename"))
        continue;
      else
        break;
    }

    $this->keyfilename = $keyfilename;

    touch("/home/nulled/www/planetxmail.com/mle/keyimages/$keyfilename");

    // create image
    chmod("/home/nulled/www/planetxmail.com/mle/keyimages/$keyfilename", 0664);
    ImageJPEG($im, "/home/nulled/www/planetxmail.com/mle/keyimages/$keyfilename");
  }

  function validate()
  {
    $time_good = 0;

    $current_time = time();
    $parts = explode('S', $_REQUEST['validate']);
    $time_sent = substr($parts[0], strlen($parts[0]) - $parts[1], $parts[1]);
    $val = substr($parts[0], 0, strlen($parts[0]) - $parts[1]);
    $time_max = $current_time + $this->time_limit;

    if ($current_time <= $time_sent && $time_sent <= $time_max)
      $time_good = 1;

    if ((strrev(md5(md5(strrev($time_sent.$_REQUEST['key'].$time_sent))))==$val && $time_good))
      return 1;
    else
      return 0;
  }
}

?>
