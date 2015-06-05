#!/bin/python
# Joshua Skootsky, June 2, 2015

# Usage: python hist.py name-of-output-file (from erdos-renyi graph simulation)

from __future__ import (absolute_import, division, print_function)
import numpy as np
import matplotlib.pyplot as plt
from StringIO import StringIO
import math
import seaborn as sns
import os
from sys import argv

filename = argv[1]
with open(filename, 'r') as f:
    data = f.read()
    #Automatically closes when block ends

voltages = np.genfromtxt(fname=StringIO(data),dtype='float', delimiter='\n', comments='#')

# get comments
with open(filename, 'r') as f:
  first_line = f.readline()

# Histogram the voltages
plt.hist(voltages, bins=100, normed=True)
plt.title("Normalized Voltage Distribution of " + filename + "\n" + first_line, fontsize=14, horizontalalignment='center')
plt.xlabel("Voltage", fontsize=14)
plt.ylabel("Probability", fontsize=14)
plt.show()
