#pythran export histogram(float list, int)
#runas histogram([ (i*1.1+j*2.3)%10 for i in xrange(100) for j in xrange(100) ],10)
#bench histogram([ (i*1.1+j*2.3)%10 for i in xrange(1000) for j in xrange(2000) ],10)
def histogram(data, bin_width):
    lower_bound, upper_bound = min(data), max(data)
    out_data=[0]*(1+bin_width)
    for i in data:
        out_data[ int(bin_width * (i - lower_bound) / ( upper_bound - lower_bound)) ]+=1
    out_data[-2]+=out_data[-1]
    out_data.pop()
    return out_data
