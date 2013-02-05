LU_MASTERS=paper
LU_FLAVORS=PDF

paper_DEPENDS=cython.pdf

# generic Makefile from latex-make package
include LaTeX.mk
check:pdf
	! grep 'LaTeX Warning:' $(LU_MASTERS).log


cython.pdf:cython.py cython.dat
	python cython.py

cython.dat:bench/run_all.py
	cd bench ; python run_all.py > ../$@
