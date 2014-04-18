#pythran export is_square(long)
#runas is_square(12345678987654321234567 ** 256)
#bench is_square(12345678987654321234567 ** 256)
#from http://stackoverflow.com/questions/2489435/how-could-i-check-if-a-number-is-a-perfect-square

def is_square(apositiveint):
  x = apositiveint // 2
  seen = { x }
  while x * x != apositiveint:
    x = (x + (apositiveint // x)) // 2
    if x in seen: return False
    seen.add(x)
  return True
