<!-- 

	Bruno Mondelo Giaramita                                    
	mondelob14@gmail.com                                       
	isx48185462                                                
	Escola del Treball de Barcelona 2017-04-19  
	
															 -->

# Systemd Targets
Systemd targets are a group of .target *runlevel* files that represents
a set of service needed to start to reach a determinate status of the
system. Targets can also need lower level targets to start before reach
the *runlevel*.

The runlevels specified on sysvinit were mapped to a specific systemd
target. Also you can create a new personal target to reach a set of
services.

Comparission between SysInit runlevels and Systemd:



Bibliography:
* [Redhat Documentation](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/System_Administrators_Guide/sect-Managing_Services_with_systemd-Targets.html)
* [Arch Linux Documentation](https://wiki.archlinux.org/index.php/systemd)
