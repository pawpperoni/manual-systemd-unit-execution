<!-- 

	Bruno Mondelo Giaramita                                    
	mondelob14@gmail.com                                       
	isx48185462                                                
	Escola del Treball de Barcelona 2017-05-18
	
                                                                     -->
                                                                     
# Path

## About

In [src](src/) there's a little implementation of the **Path-based**
implementation. You can use [run.sh](run.sh) to generate the docker
image and create a new docker. Once the docker is started it will wait
for a **time status** change to execute the order.

The main work is made by [path-activation.c](src/path-activation.c) is
to continue checking the time status and execute the order if there's a
change in any of the times. The parameter required is the *-f | --file*.
This paramater accepts any UNIX filetype (such a regular file, socket,
directory...).

![flow](flow.png)

Due to Docker memory assignment/ussage, actually the service cause a
memory allocation error:

```INI
path-activation: malloc.c:2403: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
```

This problem makes the docker unusable.
