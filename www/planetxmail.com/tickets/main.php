<?php

$_SKIP_FORCED_REGISTER_GLOBALS = 1;

require_once('/home/nulled/www/planetxmail.com/phpsecure/classes.inc');
require_once('/home/nulled/www/planetxmail.com/mle/mlpsecure/validationfunctions.php');

$allowed = array('readreplyticket','readclosedticket','viewopentickets','viewclosedtickets','ticketsubmitted');

$c = trim($_GET['c']);

if (! @in_array($c, $allowed))
  $c = 'home';

require_once('secure/' . $c . '.inc');

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8" />
<title>Planet X Mail - Tickets</title>
<script language="javascript" src="../submitsupressor.js"></script>
<style>
</style>
<link rel="stylesheet" type="text/css" href="x.css" />
<script>
<?php

  if ($c == 'readreplyticket')
  {
    echo "function checkreply(op)
    {
      if (op == 1)
      {
        if (! document.replyticket.status.checked)
          alert('Please select if you want to keep open or to close this ticket.');
        else
          document.replyticket.submit();
      }
      else
      {
        if (document.replyticket.e.value == 'admin-reply')
          alert('You can not reply to an admin-reply message!');
        else if (! document.replyticket.status[0].checked && ! document.replyticket.status[1].checked && ! document.replyticket.status[2].checked)
          alert('Please select if you want to keep open or to close this ticket.');
        else
          document.replyticket.submit();
      }
    }
    ";
  }

  if ($c == 'readclosedticket')
  {
    echo "function checkoption()
    {
      if (! document.closedticket.status[0].checked && ! document.closedticket.status[1].checked)
        alert('Please select which option you want.');
      else
        document.closedticket.submit();
    }
    ";
  }

?>
</script>

<?php

  $onLoad = '';

  if ($c == 'ticketsubmitted')
  {
    echo '
    <script type="text/javascript">
    function createXMLHttpRequest()
    {
      try { return new XMLHttpRequest(); } catch (e) {}
      try { return new ActiveXObject("Msxml2.XMLHTTP"); } catch (e) {}
      try { return new ActiveXObject("Microsoft.XMLHTTP"); } catch (e) {}
      alert("XMLHttpRequest not supported.");
      return null;
    }
    function $(id)
    {
      return document.getElementById(id);
    }
    function scanlog()
    {
      var xhr = createXMLHttpRequest();

      xhr.onreadystatechange = function()
      {
        // readyState Status Codes:
        // 0 = uninitialized
        // 1 = loading
        // 2 = loaded
        // 3 = interactive
        // 4 = complete

        // if (xhr.readyState == 3) $("layer1").innerHTML = xhr.responseText;

        // alert(xhr.readyState);

        if (xhr.readyState == 4)
        {
          if (xhr.status != 200)
             alert("An error occured.");
          else
            $("layer1").innerHTML = xhr.responseText;
        }
      }
      xhr.open("GET", "../scanlog.php?e=' . $e . '&h=' . $h . '", true);
      xhr.send(null);
    }
    </script>
    ';

    $onLoad = ' onload="scanlog()"';

  }

?>
</head>
<?php flush(); ?>
<body<?=$onLoad?>>
<table border="1">
  <tr>
    <td valign="top" width="150">
      <b>Main Menu</b>
      <hr>
      <a href="main.php?c=viewopentickets">View Open Tickets</a>
      <br>
      <a href="main.php?c=viewclosedtickets">View Closed Tickets</a>
    </td>
    <td><?php require_once($c . '.php'); ?></td>
  </tr>
</table>
</body>
</html>