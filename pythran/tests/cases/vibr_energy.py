#from http://stackoverflow.com/questions/17112550/python-and-numba-for-vectorized-functions
#pythran export calculate_vibr_energy(float[], float[],int [])
#pythran export calculate_vibr_energy(float[], float[], int)
#pythran export calculate_vibr_energy(float[], float[], float)
#pythran export calculate_vibr_energy(float[], float[], float [])
#runas import numpy as np ; a = np.sin(np.ones(1000000)) ; b = np.cos(np.ones(1000000)) ; n = np.arange(1000000); calculate_vibr_energy(a, b, n)
#runas import numpy as np ; a = np.sin(np.ones(1000000)) ; b = np.cos(np.ones(1000000)) ; calculate_vibr_energy(a, b, 10)
#runas import numpy as np ; a = np.sin(np.ones(1000000)) ; b = np.cos(np.ones(1000000)) ; calculate_vibr_energy(a, b, 10.)
#runas import numpy as np ; a = np.sin(np.ones(1000000)) ; b = np.cos(np.ones(1000000)) ; n = np.arange(1000000, dtype=np.double); calculate_vibr_energy(a, b, n)
import numpy
def calculate_vibr_energy(harmonic, anharmonic, i):
    return numpy.exp(-harmonic * i - anharmonic * (i ** 2))
