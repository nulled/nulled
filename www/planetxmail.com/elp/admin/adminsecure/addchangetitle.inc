<?php
include("../../mle/mlpsecure/config/classes.inc");
include("../../mle/mlpsecure/validationfunctions.php");

$db = new MySQL_Access("elp");

if ($submitted=="change")
{
  if ($useDefault=="yes")
  {
    $db->Query("SELECT titlegraphic FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
    list($titleData) = $db->FetchRow();

    @unlink($titleData);

    $db->Query("UPDATE elpowners SET titlegraphic='DEFAULT' WHERE elpownername='$_SESSION[aaelp]ownername'");
    $notValid = "Using DEFAULT title image now.  Settings have been applied.";
  }
  else if ($title!="none")
  {
    $fileType = $_FILES["title"]["type"];
    $titleimagename = $_FILES["title"]["name"];

    if ($_FILES["title"]["size"]>50000)
      $notValid = "ERROR: Title file size maximum is 50 K bytes";
    else if (!preg_match("/image\/(gif|jpeg|pjpeg)/", $fileType))
      $notValid = "ERROR: Title just be a jpg or gif.";
		else
    {
      $logoname = generateID(15);

      $ext = explode(".", $titleimagename);
	    $filename = "banners/".$logoname.".".$ext[1];

	    if(@copy($title, $filename))
      {
        $imgSize = GetImageSize($filename);

        if ($imgSize[0]>450) $notValid = "ERROR: The width of title is greater than 450.";
        else if ($imgSize[1]>250) $notValid = "ERROR: The height of title is greater than 250.";
      }
      else
      {
        $filename = "none";
        $notValid = "ERROR: You title was unable to upload.";
      }

      if ($notValid)
        @unlink($filename);
      else
      {
      	$db->Query("SELECT titlegraphic FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
    		list($oldfile) = $db->FetchRow();
    		@unlink($oldfile);
	      $db->Query("UPDATE elpowners SET titlegraphic='$filename' WHERE elpownername='$_SESSION[aaelp]ownername'");
	      $notValid = "Title graphic updated.";
	    }
  	}
  }
  else
    $notValid = "ERROR: No title graphic selected";
}

$db->Query("SELECT titlegraphic FROM elpowners WHERE elpownername='$_SESSION[aaelp]ownername'");
list($titleIMG) = $db->FetchRow();

if ($titleIMG==""||$titleIMG=="DEFAULT")
  $titleIMG = "../images/elplogo.jpg";

?>