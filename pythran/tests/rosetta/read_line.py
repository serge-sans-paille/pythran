#from http://rosettacode.org/wiki/Read_a_file_line_by_line#Python
#pythran export readfile()
#runas readfile()

def readfile():
    return [line for line in file("pythran/tests/rosetta/read_conf.cfg")]
