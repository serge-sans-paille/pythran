#!/usr/bin/env python
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import math

with file("hyantes.dat") as fd:

    r = [float(x) for x in fd.read().split('\n') if x]
    r = [ r[0] / x for x in r ]

        

    fig = plt.figure(1, figsize=(8,3.6))
    plt.xlabel('number of cores')
    plt.ylabel('speedup')
    plt.plot(range(1, len(r)+1), range(1, len(r)+1), linestyle='--', color='black')
    plt.plot(range(1, len(r)+1), r, linestyle='-', color='black', marker='o')
    plt.savefig('hyantes.pdf',format='pdf')
