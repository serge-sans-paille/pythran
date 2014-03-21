#from http://rosettacode.org/wiki/Greatest_subsequential_sum#Python
#pythran export maxsum(int list)
#pythran export maxsumseq(int list)
#pythran export maxsumit(int list)
#runas maxsum([0, 1, 0])
#runas maxsumseq([-1, 2, -1, 3, -1])
#runas maxsumit([-1, 1, 2, -5, -6])

def maxsum(sequence):
    """Return maximum sum."""
    maxsofar, maxendinghere = 0, 0
    for x in sequence:
        # invariant: ``maxendinghere`` and ``maxsofar`` are accurate for ``x[0..i-1]``          
        maxendinghere = max(maxendinghere + x, 0)
        maxsofar = max(maxsofar, maxendinghere)
    return maxsofar


def maxsumseq(sequence):
    start, end, sum_start = -1, -1, -1
    maxsum_, sum_ = 0, 0
    for i, x in enumerate(sequence):
        sum_ += x
        if maxsum_ < sum_: # found maximal subsequence so far
            maxsum_ = sum_
            start, end = sum_start, i
        elif sum_ < 0: # start new sequence
            sum_ = 0
            sum_start = i
    assert maxsum_ == maxsum(sequence)
    assert maxsum_ == sum(sequence[start + 1:end + 1])
    return sequence[start + 1:end + 1]


def maxsumit(iterable):
    maxseq = seq = []
    start, end, sum_start = -1, -1, -1
    maxsum_, sum_ = 0, 0
    for i, x in enumerate(iterable):
        seq.append(x); sum_ += x
        if maxsum_ < sum_:
            maxseq = seq; maxsum_ = sum_
            start, end = sum_start, i
        elif sum_ < 0:
            seq = []; sum_ = 0
            sum_start = i
    assert maxsum_ == sum(maxseq[:end - start])
    return maxseq[:end - start]
