unsigned int solve(long n) {
  long a = 0, s = 0;
  for(long i = 0; i < n; ++i) {
    a += i;
    s += i * i;
  }
  return a * a - s;
}
