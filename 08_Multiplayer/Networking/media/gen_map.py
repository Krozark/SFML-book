# -*- coding: utf-8 -*-
from os import listdir
from os.path import isfile, join
import random
import math

mypath = "img/tree"
files = [ f for f in listdir(mypath) if isfile(join(mypath,f)) ]

min_x = 0
max_x = 99
min_y = 0
max_y = 99

nb = int(math.sqrt((max_x+1) * (max_y+1))) * 5
l = []
while nb > 0:
    x = random.randrange(min_x,max_x +1)
    y = random.randrange(min_y,max_y+1)
    print """{"x" : %d, "y" : %d, "img" : "media/img/tree/%s"},""" % (x, y, random.choice(files))
    nb-=1


