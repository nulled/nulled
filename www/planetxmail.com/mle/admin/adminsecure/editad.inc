<?php
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/config/config.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$db = new MySQL_Access('mle');

if ($submitted)
{
  if ($adsubject AND $addescription)
  {
    // 1 = GIF, 2 = JPG, 3 = PNG
    list($width, $height, $type) = getimagesize($_FILES['adimage']['tmp_name']);

    if (strlen($adsubject) > $ad_subject_length)              $notValid = "ERROR: Ad subject length may not exceed $board_subject_length characters.";
    else if (strlen($addescription) > $ad_description_length) $notValid = "ERROR: Ad description length may not exceed $board_description_length characters.";
    else if ($_FILES['adimage']['size'] > $image_size)        $notValid = "ERROR: Image file size maximum is $image_size bytes";
    else if ($adurl == 'http://')                             $notValid = 'ERROR: AD URL is missing.';
    else if (has_urlunsafe2($adurl))                          $notValid = 'ERROR: AD URL contains illegal characters or spaces.';
    else if (has_illegal($adsubject))                         $notValid = 'ERROR: AD subject contains bad characters.';
    else if ($width > $logo_max_width)                        $notValid = "ERROR: The width of image is greater than $logo_max_width pixels.";
    else if ($height > $logo_max_height)                      $notValid = "ERROR: The height of image is greater than $logo_max_height pixels.";
    else if ($type != 1 AND $type != 2 AND $type != 3)        $notValid = 'ERROR: Image must be a jpg, gif or png.';
    else
    {
      // get current logo in database
      $db->Query("SELECT adimage FROM ads WHERE id='$adID' LIMIT 1");
      list($oldimage) = $db->FetchRow();

      if ($delimage == '1' AND is_file($oldimage))
        unlink($oldimage);

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

      if (move_uploaded_file($_FILES['adimage']['tmp_name'], $filename))
      {
        $db->Query("UPDATE ads SET adlink='$adurl', adsubject='$adsubject', addescription='$addescription', adimage='$filename', bgcolor='$bg_color', subjectcolor='$subject_text_color', subjectstyle='$subjectstylechoice1', descriptioncolor='$description_text_color', descriptionstyle='$descriptionstylechoice1' WHERE id='$adID' LIMIT 1");

        // delete previous logo
        if (is_file($oldimage))
          unlink($oldimage);

        header('Location: listads.php');
        exit;
      }
      else
        $notValid = 'ERROR: Unable to upload logo image.'
    }
  }
  else
    $notValid = "ERROR: Missing required fields.";
}

if ($deletead == '1')
{
  $db->Query("SELECT adimage FROM ads WHERE id='$adID'");
  list($image) = $db->FetchRow();

  $db->Query("DELETE FROM ads WHERE id='$adID'");

  if (is_file($image))
    unlink($image);

  header('Location: listads.php');
  exit;
}

if (is_numeric($adID))
{
  $db->Query("SELECT * FROM ads WHERE id='$adID' LIMIT 1");
  $adData = $db->FetchArray();

  $adsubject               = $adData['adsubject'];
  $addescription           = $adData['addescription'];
  $adurl                   = $adData['adlink'];
  $adimage                 = $adData['adimage'];
  $bg_color                = $adData['bgcolor'];
  $subject_text_color      = $adData['subjectcolor'];
  $subjectstylechoice1     = $adData['subjectstyle'];
  $description_text_color  = $adData['descriptioncolor'];
  $descriptionstylechoice1 = $adData['descriptionstyle'];
}

@unset($adData);

?>