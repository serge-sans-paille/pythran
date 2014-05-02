#from http://rosettacode.org/wiki/Read_a_specific_line_from_a_file#Python
#pythran export readline(int)
#runas readline(6)

def readline(n):
    from itertools import islice

    f = open('rosetta/read_conf.cfg')
    linelist = list(islice(f, n, n + 1))
    assert linelist != [], 'Not ' + str(n) + ' lines in file'
    line = linelist[0]
    f.close()
    return line
