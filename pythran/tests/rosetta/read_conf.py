#from http://rosettacode.org/wiki/Read_a_configuration_file#Python
#pythran export readconf(str)
#runas readconf("rosetta/read_conf.cfg")

def readconf(fn):
    ret = {}
    fp = file(fn)
    for line in fp:
        # Assume whitespace is ignorable
        line = line.strip()
        if not line or line.startswith('#'): continue

        boolval = "True"
        # Assume leading ";" means a false boolean
        if line.startswith(';'):
            # Remove one or more leading semicolons
            line = line.lstrip(';')
            # If more than just one word, not a valid boolean
            if len(line.split()) != 1: continue
            boolval = "False"

        bits = line.split(None, 1)
        if len(bits) == 1:
            # Assume booleans are just one standalone word
            k = bits[0]
            v = boolval
        else:
            # Assume more than one word is a string value
            k, v = bits
        ret[k.lower()] = v
    fp.close()
    return ret
