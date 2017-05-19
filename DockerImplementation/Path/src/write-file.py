#! /usr/bin/python

# write-file.py -- writes the hour to a file
# usage: write-file.py

import sys
import datetime

FILE = "/tmp/hour"

ff = open(FILE, "a")

ff.write(str(datetime.datetime.now()) + "\n")

ff.close()

sys.exit(0)
