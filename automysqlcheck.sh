# system variables (change these according to your system)
PATH=/usr/local/bin:/usr/bin:/bin:$PATH
USER=root
PASSWORD=
DBHOST=localhost
LOGFILE=/var/log/automysqlcheck.log
MAILTO=elitescripts2000@yahoo.com
TYPE1=FAST # extra params to CHECK_TABLE e.g. FAST
TYPE2=
CORRUPT=no # start by assuming no corruption
DBNAMES="all" # either "all" or a list delimited by space
DBEXCLUDE="" # either "" or a list delimited by space

# I/O redirection...
touch $LOGFILE
exec 6>&1
exec > $LOGFILE # stdout redirected to $LOGFILE
echo -n "AutoMySQLCheck: "
date
echo "---------------------------------------------------------"; echo; echo

# Get our list of databases to check...
if [ "$DBNAMES" = "all" ] ; then
DBNAMES=""
ALLDB="`mysql --host=$DBHOST --user=$USER --password=$PASSWORD --batch -N -e "show databases"`"
for i in $ALLDB ; do
INCLUDEDB=1
for j in $DBEXCLUDE ; do
if [ "$i" = "$j" ] ; then
INCLUDEDB=0
fi
done
if [ $INCLUDEDB -eq 1 ] ; then
DBNAMES=$DBNAMES" "$i
fi
done
fi

# Lock tables
mysql --host=$DBHOST --user=$USER --password=$PASSWORD --batch -N -e "flush tables with read lock; flush logs"
# Run through each database and execute our CHECK TABLE command for all tables
# in a single pass - eyechart
for i in $DBNAMES ; do
# echo the database we are working on
echo "Database being checked:"
echo -n "SHOW DATABASES LIKE '$i'" | mysql -t --host=$DBHOST -u$USER -p$PASSWORD $i; echo

# Check all tables in one pass, instead of a loop
# Use AWK to put in comma separators, use SED to remove trailing comma
# Modified to only check MyISAM or InnoDB tables - eyechart
DBTABLES="`mysql --host=$DBHOST --user=$USER --password=$PASSWORD $i --batch -N -e "show table status;" | awk 'BEGIN {ORS=", " } $2 == "MyISAM" || $2 == "InnoDB"{print "\`" $1 "\`"}' | sed 's/, $//'`"

# Output in table form using -t option
if [ ! "$DBTABLES" ] ; then
echo "NOTE: There are no tables to check in the $i database - skipping..."; echo; echo
else
echo "CHECK TABLE $DBTABLES $TYPE1 $TYPE2" | mysql --host=$DBHOST -t -u$USER -p$PASSWORD $i; echo; echo
fi
done
# Unlock tables
mysql --host=$DBHOST --user=$USER --password=$PASSWORD --batch -N -e "unlock tables"

exec 1>&6 6>&- # Restore stdout and close file descriptor #6

# test our logfile for corruption in the database...
for i in `cat $LOGFILE` ; do
if test $i = "warning" ; then
CORRUPT=yes
elif test $i = "error" ; then
CORRUPT=yes
fi
done

# Send off our results...
if test $CORRUPT = "yes" ; then
cat $LOGFILE | mail -s "MySQL CHECK Log [ERROR FOUND] for $DBHOST-`date`" $MAILTO
else
echo '' > /dev/null
# cat $LOGFILE | mail -s "MySQL CHECK Log [PASSED OK] for $DBHOST-`date`" $MAILTO
fi
