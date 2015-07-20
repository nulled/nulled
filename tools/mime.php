<?php

if ($_FILES['filename']['name'] != 'none' && $_FILES['filename']['size'] > 0 && is_uploaded_file($_FILES['filename']['tmp_name']))
{
  echo 'type='.$_FILES['filename']['type'];
}

?>
<html>
<head>
<title>Get Mime Type</title>
</head>
<body>
<form name="mime" action="mime.php" method="post" enctype="multipart/form-data">
  Upload file:
  <input type="file" name="filename" />
  <br /><br />
   <input type="submit" value="Submit" />
</form>
</body>
</html>