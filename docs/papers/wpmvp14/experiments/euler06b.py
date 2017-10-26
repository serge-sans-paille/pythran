#pythran export solve(int)
def solve(n):
  r = range(1, n)
  a = vsum(r)
  m = vmap(lambda i:i*i, r)
  return a * a - vsum(m)
