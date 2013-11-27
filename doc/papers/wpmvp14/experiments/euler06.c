unsigned int solve(unsigned int n) {
  unsigned int a = 0, s = 0;
  for(unsigned int i = 0; i < n; ++i) {
    a += i;
    s += i * i;
  }
  return a * a - s;
}
