#from http://rosettacode.org/wiki/Ackermann_function#Python
#pythran export ack1(int, int)
#pythran export ack2(int, int)
#pythran export ack3(int, int)
#runas ack1(2, 2)
#runas ack2(2, 1)
#runas ack3(1, 2)

def ack1(M, N):
   return (N + 1) if M == 0 else (
         ack1(M-1, 1) if N == 0 else ack1(M-1, ack1(M, N-1)))


def ack2(M, N):
    if M == 0:
        return N + 1
    elif N == 0:
        return ack1(M - 1, 1)
    else:
        return ack1(M - 1, ack1(M, N - 1))


def ack3(M, N):
   return (N + 1)   if M == 0 else (
          (N + 2)   if M == 1 else (
          (2*N + 3) if M == 2 else (
          (8*(2**N - 1) + 5) if M == 3 else (
          ack2(M-1, 1) if N == 0 else ack2(M-1, ack2(M, N-1))))))
