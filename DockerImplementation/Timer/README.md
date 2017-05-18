<!-- 

	Bruno Mondelo Giaramita                                    
	mondelob14@gmail.com                                       
	isx48185462                                                
	Escola del Treball de Barcelona 2017-05-18
	
                                                                     -->
                                                                     
# Timer

The **Timer Unit** executes a process in a determined time. You can
easily configure this unit, using the crontab daemon. To edit the
crontab configuration:

```bash
[user@docket ~]$ crontab -e
```

All the crontab are saved in */var/spool/cron*. There's a file for
every user that configured a crontab. Crontab lines are formed by:
*timer* and *command*:

```INI
* * * * * /bin/command args
```

The five asterisk defines the following:
* Minutes (0-59)
* Hours (0-23)
* Day (1-31)
* Month (1-12)
* Week Day (0-6 (Sunday: 0))

If you let the asterisk it will mean every interval. For example an
asterisk in the day parameter will mean every day. You can use the '/'
to determine **repetition**, for example in month parameter /2, would
mean every two month.

```INI
0 22 1 /3 * /bin/command args
```

Every three monts, the first day at the 22:00 the command will be
executed. Crontab also includes special aliasses:
* @reboot: At the start
* @yearly: Annually
* @monthly: Once per month
* @daily/@midnight: One per day
* @hourly: Every hour

For example, with a timer for every week, like this:

```INI
[Timer]
OnCalendar=weekly
```

The crontab line could be:

```bash
@weekly /usr/bin/python3 /usr/sbin/write-file.py
```
