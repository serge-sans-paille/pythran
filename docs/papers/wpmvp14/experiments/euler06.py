#pythran export solve(int)
def solve(n):
  r = range(1, n)
  a = sum(r)
  return a * a - sum(i * i for i in r)
