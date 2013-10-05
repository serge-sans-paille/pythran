#from http://rosettacode.org/wiki/Read_a_specific_line_from_a_file#Python

def test():
    from itertools import islice
     
    f = open('read_conf.cfg')
    linelist = list(islice(f, 6, 7))
    assert linelist != [], 'Not 6 lines in file'
    line = linelist[0]
    f.close()
    return line
