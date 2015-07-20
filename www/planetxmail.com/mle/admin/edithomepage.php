<?php
include("../mlpsecure/sessionsecurelistowner.inc");
include("adminsecure/edithomepage.inc");
?>
<html>
<head>
<title><?=$program_name?> - Edit Home Pages HTML</title>
<link rel="stylesheet" type="text/css" href="../css_mlp.css" />
<script language="javascript">
<!--
var focusedmem = false;
var focusedpro = false;
var focusedexe = false;
var fcontent=new Array();
function updateCount()
{
  if (focusedmem)
  {
  	document.edithtml.counthtmlmem.value = document.edithtml.htmlmem.value.length;
  	ad = document.edithtml.htmlmem.value.toLowerCase();
  }
  else if (focusedpro)
  {
  	document.edithtml.counthtmlpro.value = document.edithtml.htmlpro.value.length;
  	ad = document.edithtml.htmlpro.value.toLowerCase();
  }
  else if (focusedexe)
  {
  	 document.edithtml.counthtmlexe.value = document.edithtml.htmlexe.value.length;
  	 ad = document.edithtml.htmlexe.value.toLowerCase();
  }

  if (ad.indexOf("<script")!=-1    || ad.indexOf("script>")!=-1   ||
        ad.indexOf('<?="<?"?>')!=-1  || ad.indexOf('<?="?>"?>')!=-1 ||
        ad.indexOf('<head>')!=-1 || ad.indexOf("<title>")!=-1 ||
        ad.indexOf("<hmtl>")!=-1)
  {
    if (focusedmem)
    {
    	document.edithtml.htmlmem.value = fcontent[0];
    	document.edithtml.counthtmlmem.value = document.edithtml.htmlmem.value.length;
    }
    else if (focusedpro)
    {
    	document.edithtml.htmlpro.value = fcontent[1];
    	document.edithtml.counthtmlpro.value = document.edithtml.htmlpro.value.length;
    }
    else if (focusedexe)
    {
    	document.edithtml.htmlexe.value = fcontent[2];
    	document.edithtml.counthtmlexe.value = document.edithtml.htmlexe.value.length;
    }

    alert("No Javascript, PHP, VBS or <html>, <title>, <head> tags allowed!");
  }
  else
  {
  	if (focusedmem) fcontent[0] = document.edithtml.htmlmem.value;
  	else if (focusedpro) fcontent[1] = document.edithtml.htmlpro.value;
  	else if (focusedexe) fcontent[2] = document.edithtml.htmlexe.value;
  }
}
function checkCount(formname)
{
  if (document.edithtml.htmlmem.value.length > <?=$html_length?>) alert('The maximum characters your MEMBER HTML can have is <?=$html_length?> characters.');
  else if (document.edithtml.htmlpro.value.length > <?=$html_length?>) alert('The maximum characters your PROFESSIONAL HTML can have is <?=$html_length?> characters.');
  else if (document.edithtml.htmlexe.value.length > <?=$html_length?>) alert('The maximum characters your EXECUTIVE HTML can have is <?=$html_length?> characters.');
  else formname.submit();
}
document.onkeyup=updateCount;
//-->
</script>
</head>
<body onLoad="fcontent[0]=document.edithtml.htmlmem.value;fcontent[1]=document.edithtml.htmlpro.value;fcontent[2]=document.edithtml.htmlexe.value;">
<table  cellpadding="0" cellspacing="0" align="center" border="1">
  <tr>
    <td>
      <table width="500" cellpadding="3" cellspacing="0" align="center" border="0">
        <tr>
          <td colspan="2" align="center">
            <h4>Edit your HTML home page.</h4>
            <p>The HTML will be placed in between <b>&lt;td&gt;</b> <i>your HTML here</i> <b>&lt;&#047;td&gt;</b>
            which is a table row.  Any valid HTML is legal.  This will then appear on the HOME section when your
            members login to the list.  This is useful for customizing the HOME page with links and information you
            wish to give to your list members PER STATUS.  Each Status can be a different Home page! No Java script,
            PHP, VBS, &lt;head&gt;, &lt;html&gt;, &lt;title&gt; tags allowed since they are already placed for you.</p>
            <p>
              The following tags will be replaced with text pretaining to their name description: <b>[list_name]</b>, <b>[program_name]</b>, <b>[member_status]</b>, <b>[total_count]</b>, <b>[mem_count]</b>, <b>[pro_count]</b>, <b>[exe_count]</b>
            </p>
            <hr>
            <b class="red"><?php if ($notValid) echo "$notValid<br><br>"; ?><b>
          </td>
        </tr>
        <!-- Message segment -->
        <tr>
          <td align="right" valign="top">
            <b>Free</b>&nbsp;HTML:
            <form name="edithtml" action="<?=$_SERVER[PHP_SELF]?>" method="POST">
          </td>
          <td>
            <textarea wrap="OFF" rows="10" cols="80" name="htmlmem" onFocus="focusedmem=true;" onBlur="focusedmem=false;"><?=$htmlmem?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="counthtmlmem" READONLY size="4">
          </td>
          <td>Maximum of <?=$html_length?> characters.<hr></td>
        </tr>
        <!-- Message segment -->
        <tr>
          <td align="right" valign="top">
            <b>Pro</b>&nbsp;HTML:
          </td>
          <td>
            <textarea wrap="OFF" rows="10" cols="80" name="htmlpro" onFocus="focusedpro=true;" onBlur="focusedpro=false;"><?=$htmlpro?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="counthtmlpro" READONLY size="4">
          </td>
          <td>Maximum of <?=$html_length?> characters.<hr></td>
        </tr>
        <!-- Message segment -->
        <tr>
          <td align="right" valign="top">
            <b>Exe</b>&nbsp;HTML:
          </td>
          <td>
            <textarea wrap="OFF" rows="10" cols="80" name="htmlexe" onFocus="focusedexe=true;" onBlur="focusedexe=false;"><?=$htmlexe?></textarea><br>
          </td>
        </tr>
        <tr>
          <td align="right">
            <input type="text" name="counthtmlexe" READONLY size="4">
          </td>
          <td>Maximum of <?=$html_length?> characters.<hr></td>
        </tr>
        <tr>
          <td><input type="button" class="greenbutton" value="Save" onClick="checkCount(this.form);"></td>
          <td align="right"><input type="reset" value="Reset" class="redbutton"></td>
        </tr>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td colspan="2" align="center">
            <input type="button" class="beigebutton" value="Back to Main" onClick="location.href='<?php if ($_SESSION[aaadminpsk]) echo "main.php"; else echo "mainlistowner.php"; ?>'">
            <input type="hidden" name="submitted" value="1">
            </form>
          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>
</body>
</html>