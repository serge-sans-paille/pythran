#runas solve(1000000)
#pythran export solve(int)
'''
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
'''

def fact(n):
     f = 1
     for x in xrange(1, n+1): f = f * x
     return f

def permutation(orig_nums, n):
     nums = list(orig_nums)
     perm = []
     while len(nums):
         divider = fact(len(nums)-1)
         pos = n / divider
         n = n % divider
         perm.append(nums[pos])
         nums = nums[0:pos] + nums[pos+1:]
     return perm

def solve(perm):
  return ''.join(str(x) for x in permutation(range(0,10), perm - 1))
