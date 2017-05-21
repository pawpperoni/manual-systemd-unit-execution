<!-- 

	Bruno Mondelo Giaramita                                    
	mondelob14@gmail.com                                       
	isx48185462                                                
	Escola del Treball de Barcelona 2017-04-26
	
															 -->

# Unit Sections

All units can have two standard sections: **[Unit]** and **[Install]**.
We should differ *unit* and *[UNIT]*; the first are a type of 
configuration file in systemd environment, the second one is a section
inside the unit file. All type of units can also implement it's own
sections, like **[Socket]** in socket units or **[Mount]** in mount
units. In this section we will comment the sections of systemd and how
to start this units manually.

## Unit

|   Parameter   |                                                            Description                                                             |
|---------------|:----------------------------------------------------------------------------------------------------------------------------------:|
|  Description  |                                                    A string describing the unit                                                    | 
| Documentation |                                     Space separated list of URI's referencing the documentation                                    |
|   Requires    | Space-separated list of dependence units to start when this unit starts. If one of this dependences fails, it won't start the unit |
|     Wants     |                         Similar to requires, but if the dependence start fails it wont fail the unit start                         |
|   Conflicts   |                                           Dependence units to stop before start the unit                                           |
| Before, After |                                                       Set hierarchy of units                                                       |
| AllowIsolate  |                                         Boolean, set the permission to isolate to this unit                                        |

The full documentation is in the man
[systemd.unit(5)](http://man7.org/linux/man-pages/man5/systemd.unit.5.html).

## Install

|      Parameter       |                                                        Description                                                         |
|----------------------|:--------------------------------------------------------------------------------------------------------------------------:|
|        Alias         |                                      Space-separated list of alias names of the unit                                       | 
| WantedBy, RequiredBy | Creates a symlink on *requires* or *wants* directory. Same effect of *Wants* and *Requires* parameters on **Unit** section |
|         Also         |                            Units to install/desinstall when this unit is installed/desinstalled                            |

The full documentation is in the man
[systemd.unit(5)](http://man7.org/linux/man-pages/man5/systemd.unit.5.html).

## Automount

|   Parameter    |                                      Description                                      | Required |
|----------------|:-------------------------------------------------------------------------------------:|:--------:|
|     Where      | The absolute path of the automount point. If not exists is created in the mount order |   Yes    |
| DirectoryMode  |                   If the directory is created the filesystem access                   |    No    |
| TimeoutIdleSec |          Time to wait the mount, after this time, systemd tries to umount it          |    No    |

The unit must be named like the mount point, for example a unit with 
*Where=/mnt/disk-0* should be called *mnt-disk-0.automount*. A **mount
unit** with the same name must exists.

## Device

## Mount

|   Parameter   |                                                Description                                                | Required |
|---------------|:---------------------------------------------------------------------------------------------------------:|:--------:|
|     What      |                                  Defines the path of the device to mount                                  |   Yes    |
|     Where     |                              Defines the mount point. Creates if not exists                               |   Yes    |
|     Type      |                                  A string containing the filesystem type                                  |    No    |
|    Options    |                                   Coma separated list of mount options                                    |    No    |
| SloppyOptions |                   Boolean value, on true unknown options in *Options* will be tolerated                   |    No    |
| DirectoryMode | When automatically creating mount point directory denotes it's permissions in octal mode. Default is 0755 |    No    |
|  TimeoutSec   | Time to wait the mount, after this time sends a SIGTERM, after another delay of this time sends a SIGKILL |    No    |

The unit must be named like the mount point, for example a unit with 
*Where=/mnt/disk-0* should be called *mnt-disk-0.mount*. You can
manually execute this systemd units. Some examples:

### Simple mount file:

```INI
[Mount]
What=/dev/loop0
Where=/mnt/disk-0
```

#### In bash:

```bash
mount /dev/loop0 /mnt/disk-0
```

#### In C:

```c
mount("/dev/loop0", "/mnt/disk-0", "ext4", 0, NULL);
/* You must specify the filesystem
   in this case is a ext4*/
```

### Mount with a filesystem:

```INI
[Mount]
What=/dev/loop0
Where=/mnt/disk-0
Type=ext2
```

#### In bash:

```bash
mount /dev/loop0 /mnt/disk-0 -t ext2
```

#### In C:

```c
mount("/dev/loop0", "/mnt/disk-0", "ext2", 0, NULL);
```

### Mount with options:

```INI
[Mount]
What=/dev/loop0
Where=/mnt/disk-0
Type=ext2
Options=rw,users
```

#### In bash:

```bash
mount /dev/loop0 /mnt/disk-0 -t ext2 -o rw,users
```

#### In C:

```c
mount("/dev/loop0", "/mnt/disk-0", "ext2", "rw,users", NULL);
```

### Mount with sloppy options:

```INI
[Mount]
What=/dev/loop0
Where=/mnt/disk-0
Type=ext2
Options=rw,users
SloppyOptions=true
```

#### In bash:

```bash
mount /dev/loop0 /mnt/disk-0 -t ext2 -s -o rw,users
```

### Mount with timeout:

```INI
[Mount]
What=/dev/loop0
Where=/mnt/disk-0
TimeoutSec="3min 10s"
```

#### In bash:

```bash
# To mount with a timeout we must use a order to timeout
# a process
maxtime "mount /dev/loop0 /mnt/disk-0" 190

# When the time is exceeded it sends a kill signal to the mount
```

## Scope

## Service

## Slice

## Snapshot

## Socket

|        Parameter        |Description|
|-------------------------|:---------:|
|      ListenStream       | Defines a SOCK_STREAM address to listen: sequenced, reliable, two-way, connection-based. |
|     ListenDatagram      | Defines a SOCK_DGRAM address to listen: datagram connectionless, unreliable messages of maximum length. |
| ListenSequentialPacket  | Defines a SOCK_SEQPACKET address to listen: datagram sequenced, reliable, two-way, connection-based, messages with maximum length. |
|       ListenFIFO        | Defines a system FIFO to listen. |
|      ListenSpecial      | Defines a special file to listen, such as character device nodes. |
|      ListenNetlink      | Defines a Netlink family to listen. |
|   ListenMessageQueue    | Defines a POSIX message queue to listen (See mqueue). |
|    ListenUSBFunction    | Defines a USB Endpoint to listen. |
|     SocketProtocol      | 
|      BindIPv6Only       |
|         Backlog         |
|      BindToDevice       |
|       SocketUser        |
|       SocketGroup       |
|       SocketMode        |
|      DirectoryMode      |
|         Accept          |
|        Writable         |
|     MaxConnections      |
|        KeepAlive        |
|    KeepAliveTimeSec     |
|  KeepAliveIntervalSec   |
|     KeepAliveProbes     |
|         NoDelay         |
|        Priority         |
|     DeferAcceptSec      |
|      ReceiveBuffer      |
|       SendBuffer        |
|          IPTOS          |
|          IPTTL          |
|          Mark           |
|        ReusePort        |
|       SmackLabel        |
|     SmackLabelIPIn      |
|     SmackLabelIPOut     |
|  SELinuxContextFromNet  |
|        PipeSize         |
| MessageQueueMaxMessages |
| MessageQueueMessageSize |
|        FreeBind         |
|       Transparent       |
|        Broadcast        |
|     PassCredentials     |
|      PassSecurity       |
|      TCPCongestion      |
|      ExecStartPre       |
|      ExecStartPost      |
|       ExecStopPre       |
|      ExecStopPost       |
|       TimeoutSec        |
|         Service         |
|      RemoveOnStop       |
|        Symlinks         |
|   FileDescriptorName    |

### Execute order when socket receives message

```INI
[Socket]
ListenStream=4111
```

#### In bash

This example is NOT efficient.

```bash
while true
        do
                # Create the socket for only one connection
                nc -l 4111 > /dev/null
                # Execute the order
                echo "Doing some orders!" >> /tmp/socket-activation.log
        done
```



Bibliography:
* Man Files:
	* [systemd.unit(5)](http://man7.org/linux/man-pages/man5/systemd.unit.5.html)
        * [systemd.unit(5)](http://man7.org/linux/man-pages/man5/systemd.unit.5.html)
        * [systemd.mount(5)](http://man7.org/linux/man-pages/man5/systemd.mount.5.html)
        * [mount(8)](http://man7.org/linux/man-pages/man8/mount.8.html)
        * [mount(2)](http://man7.org/linux/man-pages/man2/mount.2.html)
        * [systemd.socket(5)](http://man7.org/linux/man-pages/man5/systemd.socket.5.html)
        * [socket(2)](http://man7.org/linux/man-pages/man2/socket.5.html)
        
