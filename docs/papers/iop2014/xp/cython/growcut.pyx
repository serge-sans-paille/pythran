# Authors: Stefan van der Walt, Nathan Faggian, Aron Ahmadia
# https://github.com/stefanv/growcut_py
from __future__ import division
 
import numpy as np
cimport cython
 
cdef extern from "math.h" nogil:
    double sqrt(double)
 

@cython.boundscheck(False)
@cython.wraparound(False)
cdef inline double distance(double[:, :, ::1] image,
                            Py_ssize_t r0, Py_ssize_t c0,
                            Py_ssize_t r1, Py_ssize_t c1) nogil:
    cdef:
        double s = 0, d
        int i
 
    for i in range(3):
        d = image[r0, c0, i] - image[r1, c1, i]
        s += d * d
 
    return sqrt(s)
 

cdef double s3 = sqrt(3)
 
cdef inline double g(double d) nogil:
    return 1 - (d / s3)
 
@cython.boundscheck(False)
@cython.wraparound(False)
def growcut(double[:, :, ::1] image, double[:, :, ::1] state, double[:, :, ::1] state_next, Py_ssize_t window_radius):
 
    cdef:
        Py_ssize_t i, j, ii, jj, width, height
        double gc, attack_strength, defense_strength, winning_colony
        int changes
 
    height, width = image.shape[0], image.shape[1]
 
    changes = 0
 
    for j in range(width):
        for i in range(height):
 
            winning_colony = state[i, j, 0]
            defense_strength = state[i, j, 1]
 
            for jj in xrange(max(0, j - window_radius), min(j + window_radius + 1, width)):
                for ii in xrange(max(0, i - window_radius), min(i + window_radius + 1, height)):
                    if ii == i and jj == j:
                        continue
 
                    # p -> current cell, (i, j)
                    # q -> attacker, (ii, jj)
 
                    gc = g(distance(image, i, j, ii, jj))
 
                    attack_strength = gc * state[ii, jj, 1]
 
                    if attack_strength > defense_strength:
                        defense_strength = attack_strength
                        winning_colony = state[ii, jj, 0]
                        changes += 1
 
                    state_next[i, j, 0] = winning_colony
                    state_next[i, j, 1] = defense_strength
 
    return changes
