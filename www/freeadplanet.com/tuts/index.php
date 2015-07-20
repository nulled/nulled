<?php
if (stristr($c, '/') || stristr($c, '..') || ! $c) $c = 'home';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html>
<head>
<title>Programming Language Reference Guide</title>
<link rel="stylesheet" type="text/css" href="x.css" />
<script>
<!--
function Toggle(whichLayer)
{
  var style2 = document.getElementById(whichLayer).style;
  if (style2.display == 'none' || style2.display == '') style2.display = 'block';
  else style2.display = 'none';
}
-->
</script>
</head>
<body>
<table border="0" cellpadding="0" cellspacing="0" align="center" width="800">

  <tr>
    <td nowrap>
      <center><h3>C# - C <i>Sharp</i></h3></center>

      <a href="?c=home">Home</a> |
      <a href="?c=strings">Strings</a> |
      <a href="?c=sockets">Sockets</a> |
      <a href="?c=types">Types</a> |
      <a href="?c=classes">Classes</a> |
      <a href="?c=datastructures">Data Structures</a> |
      <a href="?c=reflection">Reflection</a> |
      <a href="?c=performance">Performance</a> |
      <a href="?c=references">References</a>

      <hr />
    </td>
  </tr>

  <tr>
    <td>
      <?php require_once($c.'.inc'); ?>
    </td>
  </tr>

</table>
</body>
</html>