#pythran export insertion_sort(float list)
#runas insertion_sort([1.3,5.6,-34.4,34.4,32,1.2,0,0.0,3.4,1.3])
#bench import random; in_ = random.sample(xrange(10000000), 6000) + [4.5]; insertion_sort(in_)
def insertion_sort(list2):
    for i in range(1, len(list2)):
        save = list2[i]
        j = i
        while j > 0 and list2[j - 1] > save:
            list2[j] = list2[j - 1]
            j -= 1
        list2[j] = save
