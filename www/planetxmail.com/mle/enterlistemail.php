<div style="margin:5px auto;width:600px">
  <div style="text-align:center;font-size:20px;color:black">Edit Your List Address</div>

  <br />

  <div style="text-align:left">
    The Domains Below can be set as Contact Address (light mail load), but not for List Address.
    List Addresses receive heavier than Normal Mail Loads from all the Members of the Safelist.
    We were able to make a deal with these domains especially Microsoft domains like (Hotmail, Outlook, etc)
    to be used as Contact Addresses Only.
    <br /><br />
    We will continue to work with as many Email Providers as we can to allow List Address use, but for now
    the list Below can not be used for List Addresses.
  </div>

  <br />

  These Email Providers are <u><i><b style="color:red">Not</b></i></u> friendly to List Addresses. They have Daily/Hourly Mail Limits.

  <br /><hr />

  <div style="width:400px;margin:3px auto;text-align:center">
    <ul style="float:left;text-align:left">

      <?php

        $totalbanned = array_merge($_BANNED_DOMAINS, $_LISTEMAIL_BANNED_DOMAINS);
        sort($totalbanned);
        $numemails = count($totalbanned);

        foreach ($totalbanned as $i => $bld)
        {
          if ($i < ceil($numemails / 2))
            echo "<li><b>$bld</b></li>\n";
          else if ($i == ceil($numemails / 2))
            echo "</ul><ul style=\"float:left;text-align:left\">\n<li><b>{$bld}</b></li>\n";
          else
            echo "<li><b>$bld</b></li>\n";
        }

      ?>

    </ul>

    <div style="clear:both"></div>

  </div>

  <hr />

  <?php

    if ($notValid)
      echo '<div style="padding:5px;font-size:14px;border-radius:5px;width:400px;border:1px solid red;margin:5px auto;text-align:center;background-color:pink">' . $notValid . '</div>';

  ?>

  <h3>Currently set to: </h3><b class="red"><h4><?php echo (! $listaddress) ? 'None Entered' : $listaddress; ?></h4></b></font>

  <form name="enterlistemail" action="/mle/main.php" onSubmit="submitonce(this)" method="POST">
    <b>Enter New List Address:</b>
    <br />
    <input type="text" name="email1" value="<?=$email1?>" size="30" maxlength="100" />
    <br /><br />
    <b>Enter List Address Again:</b>
    <br />
    <input type="text" name="email2" value="<?=$email2?>" size="30" maxlength="100" />
    <br /><br />
    <input type="submit" class="greenbutton" value="Submit" />
    <br /><br />
    <input type="checkbox" name="clear" value="yes" style="border-width:0px;"> Check to Blank Our Current List Address.
    <input type="hidden" name="option" value="enterlistemail" />
    <input type="hidden" name="submitted" value="addlistaddress" />
  </form>

</div>