<td align="left">
  <font size="+1">Clients with Planet X Mail</font>
  <p>
    Below are some of the SafeLists we currently host.  Entries where submitted by the List Owners and were not changed by us in any way. They are word for word.
    Not all our List Owners have submitted their profiles, so this list is not representing all the SafeLists we currently host.
    <br><br>
    <b>Note:</b> This list is ordered randomly everytime the page is loaded.
  </p>
  <?php
    $db->SelectDB("mle");

    while (list($link, $linkname, $testimonial, $listdesc, $id, $list) = mysqli_fetch_row($clients))
    {
    	if ($db->Query("SELECT banner FROM banners WHERE listownerID='$id' AND listname='$list' AND bannerlink='TITLE_GRAPHIC' LIMIT 1"))
    	{
    		list($image) = $db->FetchRow();
    		$image = "http://205.252.250.4/mle/admin/$image";
    	}
    	else
    		$image = "http://205.252.250.4/mle/images/pxm_title.jpg";

      echo "<img src=\"http://205.252.250.4/mle/images/ritebar2.jpg\" border=\"0\"><p>\n";
      echo "<a href=\"$link\" target=\"_BLANK\"><img src=\"$image\" border=\"0\"></a><br><br>\n";
      echo "  <a href=\"$link\" target=\"_BLANK\">$linkname</a><br><br>\n";
      echo "<table style=\"border-collapse: collapse\" bordercolor=\"#000000\" border=\"1\" cellspacing=\"0\" cellpadding=\"4\" width=\"600\"><tr><td bgcolor=\"#F4F4F7\">\n";
      echo "<u>List Description:</u><br>".stripslashes(str_replace("\n", "<br>", $listdesc))."</font><br><br>\n";
      echo "</tr></td></table><br>\n";
      echo "<table style=\"border-collapse: collapse\" bordercolor=\"#000000\" border=\"1\" cellspacing=\"0\" cellpadding=\"4\" width=\"600\"><tr><td bgcolor=\"beige\">\n";
      echo "<u>Planet X Mail Service Testimonial:</u><br>".stripslashes(str_replace("\n", "<br>", $testimonial))."</font>\n";
      echo "</tr></td></table>\n";
      echo "</p>\n";
    }
  ?>
</td>