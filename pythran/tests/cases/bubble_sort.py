#adapted from http://www.daniweb.com/software-development/python/code/216689/sorting-algorithms-in-python
#pythran export bubble_sort(int list)
#runas bubble_sort([-4,1,45,-6,123,4,6,1,34,-8,12])
#bench import random; in_ = random.sample(xrange(1000000000), 4000); bubble_sort(in_)
def bubble_sort(list0):
    list1=[x for x in list0 ] # simulate copy
    for i in xrange(0, len(list1) - 1):
        swap_test = False
        for j in range(0, len(list1) - i - 1):
            if list1[j] > list1[j + 1]:
                list1[j], list1[j + 1] = list1[j + 1], list1[j]  # swap
            swap_test = True
        if swap_test == False:
            break
    return list1
