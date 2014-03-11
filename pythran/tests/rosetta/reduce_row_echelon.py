#from http://rosettacode.org/wiki/Reduced_row_echelon_form#Python
#pythran export ToReducedRowEchelonForm(int list list)
#runas mtx = [ [ 1, 2, -1, -4], [ 2, 3, -1, -11], [-2, 0, -3, 22],]; ToReducedRowEchelonForm(mtx)

def ToReducedRowEchelonForm( M):
    if not M: return
    lead = 0
    rowCount = len(M)
    columnCount = len(M[0])
    for r in range(rowCount):
        if lead >= columnCount:
            return
        i = r
        while M[i][lead] == 0:
            i += 1
            if i == rowCount:
                i = r
                lead += 1
                if columnCount == lead:
                    return
        M[i],M[r] = M[r],M[i]
        lv = M[r][lead]
        M[r] = [ mrx / lv for mrx in M[r]]
        for i in range(rowCount):
            if i != r:
                lv = M[i][lead]
                M[i] = [ iv - lv*rv for rv,iv in zip(M[r],M[i])]
        lead += 1
