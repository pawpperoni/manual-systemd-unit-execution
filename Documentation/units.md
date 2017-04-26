<!-- 

	Bruno Mondelo Giaramita                                    
	mondelob14@gmail.com                                       
	isx48185462                                                
	Escola del Treball de Barcelona 2017-04-26
	
															 -->
                                                             
# Unit Types

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

## Automount
An automount unit is an automatic mount point, controlled by systemd. All
**automunt units** must have a **mount unit** that references the mount
parameters. It haves it's own [[Automount] Section](sections.md#automount).

### FSTAB and Automount
FSTAB entries will be translated into *automount units** (Details on
[Mount unit](#mount)). If it's configured on both resources, the *unit
file* take precedence.

## Device
A device unit have information a device unit tha requires systemd management

## Mount

hi


Bibliography:
* [Digital Ocean - Justin Ellingwood: *Understanding Systemd Units and Unit Files*](https://www.digitalocean.com/community/tutorials/understanding-systemd-units-and-unit-files)
* Man Files:
	* [systemd.unit(5)](https://www.freedesktop.org/software/systemd/man/systemd.unit.html)
    * [systemd.automount(5)](https://www.freedesktop.org/software/systemd/man/systemd.automount.html)
