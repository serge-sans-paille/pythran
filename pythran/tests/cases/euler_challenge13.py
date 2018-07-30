""" Euler chalenge number 13. """
# pythran export solve(int)
# runas solve(0)


def solve(v):
    """ Sum big numbers and get first digits. """
    # no gmp support, pruning table
    t = (
        371072875339021027,
        463769376774900097,
        743249861995247410,
        919422133635741615,
        230675882075393461,
        892616706966236338,
        281128798128499794,
        442742289174325203,
        474514457360013064,
        703864861058430254,
        )
    # prevent constant evaluation
    return str(sum(t) + v)[0:10]
