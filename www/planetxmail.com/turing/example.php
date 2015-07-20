<?php require_once('createkey.inc'); ?>
<html>
<head>
<title>Example</title>
</head>
<body>

<table>
  <tr>
    <td>
      <?php echo $notValid; ?>
      <form method="POST">
        Enter The Turing Key Below:
        <br />
        <?php echo $form_fields; ?>
        <input type="submit" value="Submit" />
      </form>

    </td>
  </tr>
</table>

</body>
</html>