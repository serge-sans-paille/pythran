""" Euler chalenge number 13. """
# pythran export solve(int)
# runas solve(0)


def solve(v):
    """ Sum big numbers and get first digits. """
    # no gmp support, pruning table
    # int32 support: trunc digits
    t = (
        37107, #2875339021027,
        46376, #9376774900097,
        74324, #9861995247410,
        91942, #2133635741615,
        23067, #5882075393461,
        89261, #6706966236338,
        28112, #8798128499794,
        44274, #2289174325203,
        47451, #4457360013064,
        70386, #4861058430254,
        )
    # prevent constant evaluation
    return str(sum(t) + v)[0:10]
