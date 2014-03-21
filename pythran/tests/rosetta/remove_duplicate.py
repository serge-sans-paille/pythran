#from http://rosettacode.org/wiki/Remove_duplicate_elements#Python
#pythran export unique(int list)
#runas unique([1, 2, 3, 2, 3, 4])

def unique(items):
    return list(set(items))
