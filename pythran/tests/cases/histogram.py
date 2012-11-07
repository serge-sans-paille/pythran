#pythran export histogram(float list, int)
def histogram(data, bin_width):
    lower_bound, upper_bound = min(data), max(data)
    out_data=[0]*(1+bin_width)
    for i in data:
        out_data[ bin_width * (i - lower_bound) / ( upper_bound - lower_bound) ]+=1
    out_data[-2]+=out_data[-1]
    out_data.pop()
    return out_data
