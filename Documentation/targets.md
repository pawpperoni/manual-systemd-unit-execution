<!-- 

	Bruno Mondelo Giaramita                                    
	mondelob14@gmail.com                                       
	isx48185462                                                
	Escola del Treball de Barcelona 2017-04-21
	
															 -->

# Systemd Targets
Systemd targets are a group of .target *runlevel* files that represents
a set of service needed to start to reach a determinate status of the
system. Targets can also need lower level targets to start before reach
the *runlevel*.

The *runlevels* specified on **SysVinit** were mapped to a specific **systemd**
target. Also you can create a new personal target to reach a set of
services. Targets are defined in /usr/lib/systemd/system and system or
modifications done by system administrator are in /etc/systemd/system.
Files in /etc overrrides the target units in /usr

Comparission between SysVinit runlevels and Systemd:

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
...
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel0.target -> poweroff.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel1.target -> rescue.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel2.target -> multi-user.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel3.target -> multi-user.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel4.target -> multi-user.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel5.target -> graphical.target
lrwxrwxrwx. 1 root root  01 Jan  1 00:00 /usr/lib/systemd/system/runlevel6.target -> reboot.target
...
```

As we can see if we run the command, systemd implemented targets by *runlevel*
number that points to real systemd *targets*. We have many others targets
defined by system such as *basic.target*, *printer.target*, *final.target*...
To list all targets in system use this commands:

```bash
# Show active targets
[user@localhost ~]$ systemctl list-units --type=target
UNIT                   LOAD   ACTIVE SUB    DESCRIPTION
basic.target           loaded active active Basic System
cryptsetup.target      loaded active active Encrypted Volumes
getty.target           loaded active active Login Prompts
graphical.target       loaded active active Graphical Interface
...

# Show all targets (active ∪ inactive)
[user@localhost ~]$ systemctl list-units --type=target --all
  UNIT                   LOAD      ACTIVE   SUB    DESCRIPTION
  basic.target           loaded    active   active Basic System
  cryptsetup.target      loaded    active   active Encrypted Volumes
  emergency.target       loaded    inactive dead   Emergency Mode
  getty.target           loaded    active   active Login Prompts
...
```

## Default Target and Target After Boot

The default.target, is the system boot-up target. This target, is just a
symlink to the defined boot target.

```bash
# Systemd order
[user@localhost ~]$ systemctl get-default 
graphical.target

# Symlink
[user@localhost ~]$ ll /usr/lib/systemd/system/default.target
lrwxrwxrwx. 1 root root 01 Jan  1 00:00 /usr/lib/systemd/system/default.target -> graphical.target
```

In this case, if it is not specified on boot sequence, system will reach
graphical.target on boot. To change The default target you should run this
systemd command:

```bash
# Changing default.target to multi-user.target
[user@localhost ~]$ systemctl set-default multi-user.target
Removed symlink /etc/systemd/system/default.target.
Created symlink from /etc/systemd/system/default.target to /usr/lib/systemd/system/multi-user.target.

[user@localhost ~]$ systemctl get-default
multi-user.target
```

<!-- Comment change default target source code(?) -->

The *set-default* argument from systemctl, deletes the old symlink, and
creates the new pointing to the specified target. Now every time system
boots, will reach (or almost try) multi-user.target.

Kernel also permits passing parameters to boot on a specified target. You
can edit it on the main file, or in the boot editor.

```
linux16 /boot/kernel.. systemd.unit=graphical.target ro
```

This will bot the system in graphical.target, ignoring the default.target.
Once system is runing, you can change actual target by running the following
command:

```bash
[user@localhost ~]$ systemct isolate rescue.target
```

This will only work with targets that allows the **isolate** function
([Sections documentation](sections.md)).

## The Target File

Targets function are defined in the target files. Target files are just
another systemd-unit file. As man describes this unit does not have any
special **section**, the configutation is defined in *[Unit]* and *[Intall]*
sections. A target file, usually have this structure:

```
#  To comment lines you can use '#' at the start of the line

[Unit]
Description=Graphical Interface
Documentation=man:systemd.special(7)
Requires=multi-user.target
Wants=display-manager.service
Conflicts=rescue.service rescue.target
After=multi-user.target rescue.service rescue.target display-manager.service
AllowIsolate=yes
```

This *[Unit]* section is commented on [Sections documentation](sections.md).

Also all targets can have a **wants directory**, such as
*/etc/systemd/system/graphical.target.wants* . This directory will contain
symlinks of services are configured as they are in the **Wants** configuration.
You can specify services on the **Wants** configuration or on the **wants
directory**.

Knowing this configuration file, means that you could create your own target,
for example to create a *defined service machine* and change into targets
easily.

Here you have an example of a web server target:

```bash
[user@localhost ~]$ cat /usr/lib/systemd/system/web-server.target
[Unit]
Description=Web Server
Documentation=https://github.com/mondelob/manual-systemd-unit-execution/blob/master/Documentation/targets.md
Requires=multi-user.target
Wants=httpd.service named.service
Conflicts=rescue.service rescue.target
After=multi-user.target rescue.service rescue.target
AllowIsolate=yes
```

We could symlink those services in the folder *web-server.target.wants*

Bibliography:
* [Redhat Documentation](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/System_Administrators_Guide/sect-Managing_Services_with_systemd-Targets.html)
* [Arch Linux Documentation](https://wiki.archlinux.org/index.php/systemd)
* Man Files:
	* [file-hierarchy(7)](https://www.freedesktop.org/software/systemd/man/file-hierarchy.html)
	* [systemd.unit(5)](https://www.freedesktop.org/software/systemd/man/systemd.unit.html)
	* [systemd.target(5)](https://www.freedesktop.org/software/systemd/man/systemd.target.html#)
