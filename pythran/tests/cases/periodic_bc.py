#pythran export periodic_bc(float [][][])
#runas import numpy; r = numpy.arange(0., 27.).reshape((3,3,3)); periodic_bc(r)
def periodic_bc(f):
        f[:, 0, :] = f[:, -2, :]
        return f

