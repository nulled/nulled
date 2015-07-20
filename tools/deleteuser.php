<?php
if ($submitted=="deleteuser")
{
	$userID = trim($userID);

	if ($userID)
	{
		include("/home/nulled/www/planetxmail.com/mle/mlpsecure/config/classes.inc");
		$db = new MySQL_Access();

		if ($db->Query("SELECT userID FROM users WHERE userID='$userID'"))
		{
			$db->Query("DELETE FROM urldata WHERE userID='$userID'");
			$db->Query("DELETE FROM urlmanager WHERE userID='$userID'");
			$db->Query("DELETE FROM users WHERE userID='$userID'");

			$notValid = "UserID: $userID was deleted from the database.";
		}
		else
			$notValid = "ERROR: User not found. None was deleted.";

	}
	else
		$notValid = "ERROR: UserID not provided.";
}
?>
<html>
<head>
<title>Delete user</title>
</head>
<body>
<table>
	<tr>
		<td>
		This Form will remove a user based on their userID.
		<?php if ($notValid) echo "<br><br><font color=red><b>$notValid</b></font>"; ?>
		<form name="delete" action="<?=$PHP_SELF?>" method="POST">
			<b>UserID:</b>
			<br>
			<input type="text" name="userID">
			<br><br>
			<input type="hidden" name="submitted" value="deleteuser">
			<input type="submit" value="Submit">
		</form>
		</td>
	</tr>
</table>
</body>
</html>