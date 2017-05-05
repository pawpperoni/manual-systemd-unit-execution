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

## Automount

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

Simple mount file:

```INI
[Mount]
What=/dev/loop0
Where=/mnt/disk-0
```

```bash
mount /dev/loop0 /mnt/disk-0
```

Bibliography:
* Man Files:
	* [systemd.unit(5)](http://man7.org/linux/man-pages/man5/systemd.unit.5.html)
