#pythran export QuickSort(float list)
#runas QuickSort(range(10))
#bench a = range(200000); QuickSort(a)

# swap two value of the list
def swap (l, idx1, idx2):
    if (idx1 != idx2):
        tmp = l[idx1]
        l[idx1] = l[idx2]
        l[idx2] = tmp

# partition the list using the value at pivot index size / 2 and return the
# new pivot index
def partition (l):
    size = len (l)
    # the pivot indfex
    pivot_idx = size / 2
    # the pivot value
    val = l[pivot_idx]
    # the idx of last unsorted elemet
    idx = size - 1
    # move the pivot to the end
    if (pivot_idx != idx):
        swap (l, pivot_idx, idx)

    # the pivot must stay at the end until the final swap
    idx = idx - 1
    # go through the list of the elements to be sorted
    i = 0
    while (i <= idx):
        if (l[i] > val) :
            while ((l[idx] > val) and (idx > i)):
                idx = idx - 1
            if (idx != i):
                swap (l, i, idx)
                idx = idx - 1
            else:
                break
        i = i+1
    # finally bring the pivot at its final place
    assert ((idx == i) or (idx + 1 == i))
    swap (l, i, size - 1)
    return i

def QuickSort (l):
    size = len (l)
    if size > 1:
        # Get the lists of bigger and smaller items and final position of pivot
        idx = partition (l)
        l1 = []
        l2 = []
        for i in range (0, idx):
            l1.append (l[i])
        for i in range (idx, size):
            l2.append (l[i])
        # Recursively sort elements smaller than the pivot
        QuickSort(l1);
        # Recursively sort elements at least as big as the pivot
        QuickSort(l2);
        for i in range (0, len (l1)):
            l[i] = l1[i]
        for i in range (0, len (l2)):
            l[len (l1) + i] = l2[i]
    return l
