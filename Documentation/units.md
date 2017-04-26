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


Bibliography:
* Man Files:
	* [systemd.unit(5)](https://www.freedesktop.org/software/systemd/man/systemd.unit.html)

P.D ~ THIS IS ME
![Me](http://redesdecomputadores.umh.es/IPTABLES%20manual%20practico,%20tutorial%20de%20iptables%20con%20ejemplos_archivos/autor.jpg)
