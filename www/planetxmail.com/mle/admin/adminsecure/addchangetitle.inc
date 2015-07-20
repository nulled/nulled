<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access();

if ($submitted}
{
  if ($useDefault == '1')
  {
    $db->Query("SELECT banner FROM banners WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}' AND bannerlink='TITLE_GRAPHIC'");
    list($titleData) = $db->FetchRow();

    @unlink($titleData);

    $db->Query("DELETE FROM banners WHERE listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}' AND bannerlink='TITLE_GRAPHIC'");
    $notValid = 'Using DEFAULT title image now. Settings have been applied.';
  }
  else if ($title != 'none' AND ! $notValid)
  {
    // 1 = GIF, 2 = JPG, 3 = PNG
    list($width, $height, $type) = getimagesize($_FILES['title']['tmp_name']);

    if ($_FILES['title']['size'] > $title_size)        $notValid = "ERROR: Title file size maximum is $title_size bytes";
    else if ($type != 1 AND $type != 2 AND $type != 3) $notValid = "ERROR: Title must be a jpg or gif.";
    else
    {
      if ($type == 1) $ext = '.gif';
      if ($type == 2) $ext = '.jpg';
      if ($type == 3) $ext = '.png';

      while (1)
      {
        $filename = '_signs/' . generateID(15) . $ext;

        if (is_file($filename))
          continue;
        else
          break;
      }

      if (move_uploaded_file($_FILES['title']['tmp_name'], $filename))
      {
        if ($width > $title_width)
          $notValid = "ERROR: The width of title is greater than $title_width pixels.";
        else if ($height > $title_height)
          $notValid = "ERROR: The height of title is greater than $title_height pixels.";
      }
      else
      {
        $filename = 'none';
        $errorMsg = 'ERROR: Your title was unable to upload.';
      }
    }
  }
  else
    $notValid = 'ERROR: No title graphic selected.';

  if (! $notValid)
  {
    if ($db->Query("SELECT id, banner FROM banners WHERE listownerID='{$_SESSION['aalistownerID']}' AND listname='{$_SESSION['aalistname']}'"))
    {
      $titleData = $db->FetchRow();

      @unlink($titleData[1]);

      $db->Query("UPDATE banners SET banner='$filename', bannerlink='TITLE_GRAPHIC', listname='{$_SESSION['aalistname']}', listownerID='{$_SESSION['aalistownerID']}' WHERE id='{$titleData[0]}'");
      $notValid = "Title graphic updated.";
    }
    else
      $db->Query("INSERT INTO banners VALUES ('','$filename','TITLE_GRAPHIC','{$_SESSION['aalistname']}','{$_SESSION['aalistownerID']}')");
  }
}

// get title, if none use default
$db->Query("SELECT banner FROM banners WHERE bannerlink='TITLE_GRAPHIC' AND listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");

if ($db->rows)
 list($titleIMG) = $db->FetchRow();
else
  $titleIMG = '../images/title.gif';

?>