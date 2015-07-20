<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

if ($submitted AND $bannerID)
{
  if ($deletebanner == '1')
  {
    if ($db->Query("SELECT banner FROM banners WHERE id='$bannerID' AND listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'"))
    {
      list($oldbanner) = $db->FetchRow();

      if (is_file($oldbanner))
        unlink($oldbanner);
    }

    $db->Query("DELETE FROM banners WHERE id='$bannerID' AND listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");

    header('Location: listbannerads.php');
    exit;
  }
  else if ($banner != 'none')
  {
    // 1 = GIF, 2 = JPG, 3 = PNG
    list($width, $height, $type) = getimagesize($_FILES['banner']['tmp_name']);

    if ($_FILES['banner']['size'] > $banner_size)      $notValid = "ERROR: Banner file size maximum is $banner_size bytes";
    else if (! $bannerlink)                            $notValid = 'ERROR: Missing banner URL/Link.';
    else if ($width > $banner_width)                   $notValid = "ERROR: The width of banner is greater than $banner_width pixels.";
    else if ($height > $banner_height)                 $notValid = "ERROR: The height of banner is greater than $banner_height pixels.";
    else if ($type != 1 AND $type != 2 AND $type != 3) $notValid = 'ERROR: Banner must be a jpg, gif or png.';
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

      if (move_uploaded_file($_FILES['banner']['tmp_name'], $filename))
      {
        $db->Query("SELECT banner FROM banners WHERE id='$bannerID' AND listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");
        list($oldbanner) = $db->FetchRow();

        if (is_file($oldbanner))
          unlink($oldbanner);

        $db->Query("UPDATE banners SET banner='$filename', bannerlink='PER{$bannerlink}' WHERE id='$bannerID' AND listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");

        $notValid = 'Banner has been successfully updated.';
      }
      else
        $notValid = 'ERROR: Unable to upload your banner.';
    }
  }
}

$db->Query("SELECT banner FROM banners WHERE id='$bannerID' AND listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");
$banners = $db->FetchRow();

$numLinks = $db->Query("SELECT bannerlink FROM banners WHERE id='$bannerID' AND listname='{$_SESSION['aalistname']}' AND listownerID='{$_SESSION['aalistownerID']}'");
$bannerlinks = $db->FetchRow();

// strip the PER in the links
for ($i = 0; $i < $numLinks; $i++)
  $bannerlinks[$i] = substr($bannerlinks[$i], 3);

?>