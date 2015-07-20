#!/usr/bin/php -q
<?php
require_once('/home/nulled/config.inc');

class ManageMail extends MySQL_Access
{
  function __construct()
  {
    parent::__construct('webmail');
  }

  public function GetAll($option='return')
  {
    $i = 0;
    $mailboxes = array();

    if ($this->Query("SELECT username, quota FROM mailbox WHERE 1 ORDER BY username"))
    {
      while (list($username, $quota, $active) = $this->FetchRow())
      {
        $mailboxes[$i]['username'] = $username;
        $mailboxes[$i]['quota']    = $quota;
        $i++;
      }
    }

    if ($option == 'list')
    {
      foreach ($mailboxes as $i => $box)
        echo "mailbox={$box['username']} quota={$box['quota']}MB\n";
    }
    else if ($option == 'return')
      return $mailboxes;
  }

  public function ListAll()
  {
    $this->GetAll('list');
  }
};

$mm = new ManageMail();

if ($argv[1] == 'list')
  $mm->ListAll();
else
  echo "Command unknown\n";

?>