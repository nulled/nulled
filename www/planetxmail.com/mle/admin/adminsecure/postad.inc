<?php
include("../mlpsecure/config/classes.inc");
include("../mlpsecure/config/config.inc");
include("../mlpsecure/validationfunctions.php");

function HandleLogoImage($imagename, $image, &$filename, &$notValid, $logo_max_width, $logo_max_height)
{
  // no logo, return no error
  if ($image=="none") return true;

  // build random name
  $logoname = generateID(15);

  // build path and filename to save on server
  $ext = explode(".", $imagename);
  $filename = "_signs/".$logoname.".".$ext[1];

  // copy image to server
  if(copy($image, $filename))
  {
    $imgSize = GetImageSize($filename);

    // check dimensions
    if ($imgSize[0] > $logo_max_width) $notValid = "ERROR: The width of your logo image is greater than $logo_max_width pixels.";
    else if ($imgSize[1] > $logo_max_height) $notValid = "ERROR: The height of your logo image is greater than $logo_max_height pixels.";

    // dimensions out of tolerance so delete from server, return error
    if ($notValid!="")
    {
      @unlink($filename);
      $filename = "none";
      return false;
    }

    return true;
  }
  else
  {
    // image name given, but unable to copy to server for some reason, return no error
    $filename = "none";
  }
  return true;
}

if ($submitted=="1")
{
  if ($adsubject!=""&&$addescription!="")
  {
    $fileType = $_FILES["adimage"]["type"];
    $adimagename = $_FILES["adimage"]["name"];

    // validate entries
    if (strlen($adsubject)>$ad_subject_length) $notValid = "ERROR: Ad subject length may not exceed $board_subject_length characters.";
    else if (strlen($addescription)>$ad_description_length) $notValid = "ERROR: Ad description length may not exceed $board_description_length characters.";
    else if ($_FILES["adimage"]["size"]>$image_size) $notValid = "ERROR: Image file size maximum is $image_size bytes";
    else if ($adurl=="http://") $notValid = "ERROR: Advertisement URL is missing.";
    else if (has_urlunsafe2($adurl)) $notValid = "ERROR: Advertisement URL contains illegal characters or spaces.";
    else if (has_illegal($adsubject)) $notValid = "ERROR:  Ad subject contains ILLEGAL characters.";
    else if ($adimage!="none" && $adimage)
      if (!preg_match("/image\/(gif|jpeg|pjpeg)/", $fileType))
        $notValid = "ERROR: Image must be a jpg or gif.";

    if ($notValid=="")
    {
      $filename = "none";
      $notValid = "";

      // adlogo validated so insert ad
      if (HandleLogoImage($adimagename, $adimage, $filename, $notValid, $logo_max_width, $logo_max_height))
      {
        $db = new MySQL_Access();
    	  $db->Query("INSERT INTO ads VALUES ('','$adsubject','$adurl','$filename','$addescription','$bg_color','$subject_text_color','$subjectstylechoice1','$description_text_color','$descriptionstylechoice1','$_SESSION[aalistname]','$_SESSION[aalistownerID]')");

    	  header("Location: listads.php");
      	exit;
      }
    }
  }
  else
    $notValid = "ERROR: Missing required fields.";
}

if (!isset($adurl)) $adurl = "http://";
?>
