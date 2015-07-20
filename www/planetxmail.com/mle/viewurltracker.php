<table width="590" cellpadding="5" cellspacing="0" border="0">
  <tr>
    <td class="UpInTheClouds_content" valign="top">
      <center>URL tracker stats for: <b class="red"><?=$urlInfo['name']?></b><br>
      Link attached to URL tracker: <b><?=$urlInfo['url']?></b><br></center>
      <br><br>
      <form name="urltracker">
      <input type="text" name="tracker" value="<?php echo "http://www.planetxmail.com/mle/uht.php?urlID=".$urlInfo['urlID']."&user=$_SESSION[aauserID]"; ?>" size="80"><br>
      <input type="button" class="beigebutton" value="Select URL" onClick="selectAll();"><br>
      Above is the link you use to replace the old link.
      </form>
      <br>
      <br>
      <font color="red"><b>How do you wish to view your URL tracker data?</b></font><br><br>
      <form name="dc">
      <ul>
        <li><a href="javascript:openurlstats('all','<?=$urlInfo['name']?>');">Show <b>all</b> hits to date.</a></li>
        <li><a href="javascript:openurlstats('hour','<?=$urlInfo['name']?>');">Show hits for the <b>hour</b>.</a></li>
        <li><a href="javascript:openurlstats('day','<?=$urlInfo['name']?>');">Show hits for the <b>day</b>.</a></li>
        <li><a href="javascript:openurlstats('week','<?=$urlInfo['name']?>');">Show hits for the <b>week</b>.</a></li>
        <li><a href="javascript:openurlstats('month','<?=$urlInfo['name']?>');">Show hits for the <b>month</b>.</a></li>
        <li><a href="javascript:openurlstats('year','<?=$urlInfo['name']?>');">Show hits for the <b>year</b>.</a></li>
      </ul>
      <br>
      </form>
    </td>
  </tr>
 </td>
</tr>
</table>