<div style="width:600px;text-align:center">

  <div style="margin:5px auto; text-align:center;font-size:16px">
    Change Your Contact Email Address
  </div>

  <hr />

  The Domains below Do not Accept Contact or List Address Mail Loads, thus cannot be used.

  <div style="width:400px;margin:3px auto;text-align:center">
    <ul style="float:left;text-align:left">

      <?php

        $totalbanned = $_BANNED_DOMAINS;
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

    <a href="/mle/main.php?option=greylist">Click Here</a> for a list of Grey Listed Contact Address Domain Options.

  </div>

  <?php if ($notValid) echo '<div class="notValid">' . $notValid . '</div>'; ?>

  <hr />
    <form name="changecontactemail" action="/mle/main.php" method="POST">
      New Contact Address:<br />
      <input type="text" name="email1" value="<?php echo $email1; ?>" size="25" maxlength="100" />
      <br /><br />
      New Contact Address Again:<br />
      <input type="text" name="email2" value="<?php echo $email2; ?>" size="25" maxlength="100" />

      <input type="hidden" name="submitted" value="changeemail" />
      <input type="hidden" name="greylist_bypass" value="<?=$h?>" />
      <input type="hidden" name="option" value="changesignupemail" /><br /><br />
      <?php if (! $sentemail) echo '<input type="button" class="greenbutton" value="Change Contact Email" onclick="preSubmit(this)" />'; ?>
    </form>
</div>