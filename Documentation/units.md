<!-- 

	Bruno Mondelo Giaramita                                    
	mondelob14@gmail.com                                       
	isx48185462                                                
	Escola del Treball de Barcelona 2017-05-03
	
						                     -->

# Systemd Units

A unit is a configuration file that have information about the **systemd
resources**, like *services*, *mount points*, *sockets*... In this
section we gonna review the unit types that systemd implements actually.
Also a way to start up this resources.

Every unit can also include a directory in the *systemd unit directory*
(AKA */etc/systemd/system/* or */usr/lib/systemd/system/*) that
includes more configuration files. This directory must be named
**foo.unit.d/**, for example httpd.service.d/. Systemd will load first
the .conf files in the *.d/* directory and then the unit file.

Actually the *Systemd Units* are the following:
* [Automount](#automount)
* [Device](#device)
* [Mount](#mount)
* [Path](#path)
* [Scope](#scope)
* [Service](#service)
* [Slice](#slice)
* [Snapshot](#snapshot)
* [Socket](#socket)
* [Swap](#swap)
* [Target](#target)
* [Timer](#timer)

On this unit you can create your own units ([See DIY Section](#diy-units)).

## Unit Types

### Automount
An automount unit is an automatic mount point, controlled by systemd. All
**automunt units** must have a **mount unit** that references the mount
parameters. It haves it's own [[Automount] Section](sections.md#automount).

#### FSTAB and Automount
FSTAB entries will be translated into **automount units** (Details on
[Mount unit](#mount)). If it's configured on both resources, the *unit
file* take precedence.

### Device
A device unit have information a device unit that requires systemd
management. Not all devices requires a systemd *device unit*, just the
ones tagged with the udev systemd tag. Device unit doesn't have any own
*Section* called [Device].

### Mount
A mount unit contains information about a *mount point* of the filesystem
controlled by systemd. Basically when we do the **start we mount** the resource,
and when we **stop it we dismount** the resource. Mount units can have it's
ouwn [[Mount] Section](sections.md#mount). The unit must be named like the
*mount point* it controls, changing slash per hyphen; for example a mount
point like */dev/sda5* the unit file would be *dev-sda5.mount*. Mount
units can also have an [Automount](#automount) to specify an automatic
mount point.

#### FSTAB and Mount
Entries in the fstab file */etc/fstab* will be dinamically translated in
native systemd units in boot. Normally is a better praxis configuring mount
points on **FSTAB** file.

#### Example


#### Manually Mounting
To mount manually resources from a **mount unit** or the **fstab** file
you can use this orders:

Bash:

```bash
# Mount /dev/loop0 to /mnt/disk-0 with options: read-write and users
[user@localhost ~]$ mount -t ext2 -O "rw,users" /dev/loop0 /mnt/disk-0/

# Write file
[user@localhost ~]$ echo "Hello World!" > /mnt/disk-0/bash-test

# Umount device
[user@localhost ~]$ umount /mnt/disk-0
```

C:

```c
mount("/dev/loop0", "/mnt/disk-0", "ext2", 0, NULL);
/* Mount /dev/loop0 in /mnt/disk-0 without options */

FILE * ff;
ff = fopen("/mnt/disk-0/c-test", "w");
fprintf(ff, "Hello World!");
fclose(ff);
/* Write a file in the new mounted resource */

umount("/mnt/disk-0");
/* Umount device */

```

In [*Examples Section*](Examples) you will find an implementation of
this manual mount in [bash](Examples/manually-mount.sh) and
[C](Examples/manually-mount.c) and the umount in
[bash](Examples/manually-umount.sh) and [C](Examples/manually-umount.c).

### Path
Path units defines a *path* controlled by systemd. When the path status
changes, systemd executes a unit with the same *base name*. For example
a **path unit** named foo.path, when it's status changes systemd will
start a service unit called foo.service. This unit is the default to be
executed, the config parameter *Unit=* permits to change this default
unit (explained in [[Path] Section](sections.md#path)).

### Scope

### Service
Service units are processes supervised by systemd. This unit have his own
section [**[Section]** (Explained in sections part)](sections.md#service).

### Slice

### Snapshot

### Socket
Socket units are *IPC (UNIX sockets)*, *network sockets* or *FIFO*. This unit
is used for socket-based activation, this means, when the socket receives
information it executes a service. There must be a same named service or
specified by configuration **Service=**
(more information in [[Socket] Section](sections.md#socket)).

## DIY Units

Units can be exapanded by new *user units*, once you done the unit
configuration file; after running:

```bash
[user@localhost ~]$  systemctl daemon-reload
```

### Service Unit

Your unit could be accessed via *systemctl* commands. The easist unit
to create is the **Service Unit**. To create a service unit you need to
complete the *[Unit]* and *[Service]* Sections.

The **[Unit]** Section describes the service, and service hierarchy in
systemd. This example configures a *Service Unit* for a
[echo server](Examples/Services/echo-server.py)

```INI
[Unit]
Description=Basic echo server
Documentation=https://github.com/mondelob
After=network.target
``` 

The *[Unit]* section gives a basic description, the documentation path
and most important the *After* configuration (for more information
consult the [Sections](sections.md#service)

```INI
[Service]
Type=simple
ExecStart=/usr/bin/python /bin/echo-server.py
ExecStop=/bin/kill -9 $MAINPID
```

In the *[Service]* configuration, one of the most important part is the
**Type** parameter, in this case echo-server the executable is the main
program, so it's **simple** type. We also have the **ExecStart** and
**ExecStop** parameters, defining the start and the stop of the unit.
It is a requeriment that **ExecStart** and **ExecStop** contains the
absolute path of the binary. The *$MAINPID* variable contains the PID
of the unit. It is usefull for killing the service.

Advice: If you want to show Stdout and Stderr from your service, try to
flush them

```INI
[Install]
WatedBy=multi-user.target
```

The last section is the **[Install]**, when we *enable* the service will
be installed in the specified target.

#### Service types
The parameter **Type** configures the start up of the process.
| Type | Description | System Example | Own Example |
|------|:-:|:-:|:-:|
| simple | The process configured by *ExecStart* is the main process | zabbix-agent.service | echo-server |
| forking | The process configured in *ExecStart* is supposed to fork into the main process and then die | sshd.service | telnet-server.service |
| oneshot | 
| dbus |
| notify |
| idle |

In [Service Examples](Examples/Services) you can find more unit files
and services to test.


Bibliography:
* [Digital Ocean - Justin Ellingwood: *Understanding Systemd Units and Unit Files*](https://www.digitalocean.com/community/tutorials/understanding-systemd-units-and-unit-files)
* [redhat - System Administrators Guide: *Creating and Modifying systemd Unit Files*](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/System_Administrators_Guide/sect-Managing_Services_with_systemd-Unit_Files.html)
* Man Files:
        * [systemd.unit(5)](http://man7.org/linux/man-pages/man5/systemd.unit.5.html)
        * [systemd.automount(5)](http://man7.org/linux/man-pages/man5/systemd.automount.5.html)
        * [systemd.device(5)](http://man7.org/linux/man-pages/man5/systemd.device.5.html)
        * [systemd.mount(5)](http://man7.org/linux/man-pages/man5/systemd.mount.5.html)
        * [systemd.path(5)](http://man7.org/linux/man-pages/man5/systemd.path.5.html)
        * [systemd.socket(5)](http://man7.org/linux/man-pages/man5/systemd.socket.5.html)
        * [mount(2)](http://man7.org/linux/man-pages/man2/mount.2.html)
        * [umount(2)](http://man7.org/linux/man-pages/man2/umount.2.html)
