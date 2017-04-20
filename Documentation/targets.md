<!-- 

	Bruno Mondelo Giaramita                                    
	mondelob14@gmail.com                                       
	isx48185462                                                
	Escola del Treball de Barcelona 2017-04-20
	
															 -->

# Systemd Targets
Systemd targets are a group of .target *runlevel* files that represents
a set of service needed to start to reach a determinate status of the
system. Targets can also need lower level targets to start before reach
the *runlevel*.

The *runlevels* specified on **SysVinit** were mapped to a specific **systemd**
target. Also you can create a new personal target to reach a set of
services. Targets are defined in /usr/lib/systemd/system

Comparission between SysInit runlevels and Systemd:
| SysVinit Runlevels |  Systemd Targets  |                    Description                    |
|:------------------:|:-----------------:|:-------------------------------------------------:|
|      emergency     |  emergency.target |                     Emergency                     |
|          0         |  poweroff.target  |                  Halt the system                  |
|          1         |   rescue.target   |                    Single user                    |
|          2         | multi-user.target | User defined target, by default multi-user.target |
|          3         | multi-user.target |                     Multi-user                    |
|          4         | multi-user.target | User defined target, by default multi-user.target |
|          5         |  graphical.target |                Graphical Multi-user               |
|          6         |   reboot.target   |                 Reboot the system                 |

```bash
[user@localhost ~]$ ll /usr/lib/systemd/system
.
.
.
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel0.target -> poweroff.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel1.target -> rescue.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel2.target -> multi-user.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel3.target -> multi-user.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel4.target -> multi-user.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel5.target -> graphical.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel6.target -> reboot.target
.
.
.
```
As we can see if we run the command, systemd implemented targets by *runlevel*
number that points to real systemd *targets*.


Bibliography:
* [Redhat Documentation](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/System_Administrators_Guide/sect-Managing_Services_with_systemd-Targets.html)
* [Arch Linux Documentation](https://wiki.archlinux.org/index.php/systemd)
