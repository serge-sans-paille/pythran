#from http://www.daniweb.com/software-development/python/code/216689/sorting-algorithms-in-python
#pythran export bubble_sort(float list)
def bubble_sort(list2):
    for i in xrange(0, len(list2) - 1):
        swap_test = False
        for j in range(0, len(list2) - i - 1):
            if list2[j] > list2[j + 1]:
                list2[j], list2[j + 1] = list2[j + 1], list2[j]  # swap
            swap_test = True
        if swap_test == False:
            break
