<?php
include("../mlpsecure/config/classes.inc");
include("../mlpsecure/config/config.inc");
include("../mlpsecure/validationfunctions.php");

$db = new MySQL_Access("pxm");

if ($submitted=="yes")
{
	if ($testimonial && $listdescription && $link)
	{
		if (stristr($link, "https:"))
			$notValid = "ERROR: Link can not be from https:// secure server.";
		else
		{
			$link = str_ireplace("http://", "", $link);

			$link = "http://$link";

			$testimonial = trim($testimonial);
			$listdescription = trim($listdescription);

			$testimonial = addslashes($testimonial);
			$listdescription = addslashes($listdescription);

			// trim the "\" if there is one at the very end to prevent query errors
		  while(1)
		  {
			  if (substr($listdescription, strlen($listdescription)-1)=="\\")
			  	$listdescription = substr($listdescription, 0, strlen($listdescription)-1);
			  else
			  	break;
			}

			while(1)
		  {
			  if (substr($testimonial, strlen($testimonial)-1)=="\\")
			  	$testimonial = substr($testimonial, 0, strlen($testimonial)-1);
			  else
			  	break;
			}

			if ($db->Query("SELECT listname FROM clients WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'"))
				$db->Query("UPDATE clients SET link='$link', testimonial='$testimonial', listdescription='$listdescription', verified='0' WHERE listownerID='$_SESSION[aalistownerID]' AND listname='$_SESSION[aalistname]'");
			else
				$db->Query("INSERT INTO clients VALUES('$link','$_SESSION[aalistname]','$testimonial','$listdescription','$_SESSION[aalistownerID]','$_SESSION[aalistname]',0)");

			$notValid = "Profile Updated.  We will review it within a reasonable time period.";
		}
	}
	else
		$notValid = "ERROR: Missing required params.";
}

$db->Query("SELECT link, testimonial, listdescription, verified FROM clients WHERE listname='$_SESSION[aalistname]' AND listownerID='$_SESSION[aalistownerID]'");
list($link, $testimonial, $listdescription, $verified) = $db->FetchRow();

$link = str_ireplace("http://", "", $link);

?>