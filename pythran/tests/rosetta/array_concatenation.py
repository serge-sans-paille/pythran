#from http://rosettacode.org/wiki/Array_concatenation#Python
def array_concatenation():
    arr1 = [1, 2, 3]
    arr2 = [4, 5, 6]
    arr3 = [7, 8, 9]
    arr4 = arr1 + arr2
    assert arr4 == [1, 2, 3, 4, 5, 6]
    arr4.extend(arr3)
    assert arr4 == [1, 2, 3, 4, 5, 6, 7, 8, 9]

    arr5 = [4, 5, 6]
    arr6 = [7, 8, 9]
    arr6 += arr5
    assert arr6 == [7, 8, 9, 4, 5, 6]

def test():
    array_concatenation()
