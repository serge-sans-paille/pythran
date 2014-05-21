#!/usr/bin/env python
# taken from http://www.ripton.net/blog/?p=51
#pythran export euler14(int)
#runas euler14(1000000)
#bench euler14(650000)

"""Project Euler, problem 14

The following iterative sequence is defined for the set of positive integers:

n -> n / 2 (n is even)
n -> 3n + 1 (n is odd)

Which starting number, under one million, produces the longest chain?
"""

def next_num(num):
    if num & 1:
        return 3 * num + 1
    else:
        return num // 2



def series_length(num, lengths):
    if num in lengths:
        return lengths[num]
    else:
        num2 = next_num(num)
        result = 1 + series_length(num2, lengths)
        lengths[num] = result
        return result

def euler14(MAX_NUM):
    num_with_max_length = 1
    max_length = 0
    lengths = {1: 0}
    for ii in xrange(1, MAX_NUM):
        length = series_length(ii, lengths)
        if length > max_length:
            max_length = length
            num_with_max_length = ii
    return num_with_max_length, max_length
