<?php

$mail_root = '/home/nulled/mailstorage';

$d = 'webhostedservices.com';

$m = 'test_seller';

if (file_exists("$mail_root/$d/$m")) exit("Mailbox already exists\n");

system("mkdir -p $mail_root/$d/$m/Maildir/cur");
system("mkdir -p $mail_root/$d/$m/Maildir/new");
system("mkdir -p $mail_root/$d/$m/Maildir/tmp");

system("mkdir -p $mail_root/$d/$m/Maildir/.Trash/cur");
system("mkdir -p $mail_root/$d/$m/Maildir/.Trash/new");
system("mkdir -p $mail_root/$d/$m/Maildir/.Trash/tmp");

system("mkdir -p $mail_root/$d/$m/Maildir/.sent-mail/cur");
system("mkdir -p $mail_root/$d/$m/Maildir/.sent-mail/new");
system("mkdir -p $mail_root/$d/$m/Maildir/.sent-mail/tmp");


system("chmod 770 -R $mail_root/$d/$m");
system("chown www-data:postfix -R $mail_root/$d/$m");

system("echo '$m@$d $d/$m/Maildir/' >> /etc/postfix/maildir");
system("postmap /etc/postfix/maildir");

system("postfix reload");

echo "Mailbox was created\n";

?>
