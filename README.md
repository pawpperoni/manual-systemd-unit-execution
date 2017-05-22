<!-- 

	Bruno Mondelo Giaramita                                    
	mondelob14@gmail.com                                       
	isx48185462                                                
	Escola del Treball de Barcelona 2017-04-21 
	
															 -->
															 
# Manual Systemd Unit Execution
> Executing Units Without Systemd

## Overview

The main objective of this repository is to analize all the
**systemd units** and find a way to simulate them in machine without
*systemd*. In this case the best technology to test, is **Docker**.

In the documentation section, you will find a description of all the
types of units. The **target**, due to it's importance have a special
section. Also I included a single section with all the
**systemd sections** and their parameters.

The [Dockerfile](Dockerfile) in main root, is a docker with all the
configured parameters.

## Documentation:
[Here](Documentation/README.md) you can find some usefull documentation about:
* [Systemd Sections](Documentation/sections.md)
* [Systemd Targets](Documentation/targets.md)
* [Systemd Units](Documentation/units.md)

## Docker Implementation
[Here](DockerImplementation/README.md) are some manual examples in dockers:
* [Socket](DockerImplementation/Socket)
* [Timer](DockerImplementation/Timer)
* [Path](DockerImplementation/Path)
