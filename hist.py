#!/bin/python
# Joshua Skootsky, June 2, 2015

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

# print(voltages)

# Histogram the voltages
plt.hist(voltages, bins=100, normed=True)
plt.title("Voltage Distribution")
plt.xlabel("Value")
plt.ylabel("Probability")
plt.show()
