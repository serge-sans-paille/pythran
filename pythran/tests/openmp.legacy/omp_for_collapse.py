# Utility function to check that i is increasing monotonically
#  with each call
def check_i_islarger (i, last_i):
    if i==1:
      last_i[0] = 0
    islarger = ((i >= last_i[0])and(i - last_i[0]<=1))
    last_i[0] = i
    return islarger

def omp_for_collapse():
    is_larger = 1
    last_i = [0]

    if 'omp parallel':
        my_islarger = 1
        #omp for schedule(static,1) collapse(2) ordered
        for i in range(1, 100):
            for  j in range(1, 100):
                #omp ordered
                my_islarger = check_i_islarger(i, last_i) and my_islarger
        #omp critical
        is_larger = is_larger and my_islarger

    return is_larger
