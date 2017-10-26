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
	cd bench ; OMP_NUM_THREADS=4 python run_all.py > ../$@

hyantes.pdf:hyantes.py hyantes.dat
	python hyantes.py
hyantes.dat:bench/run_hyantes.sh
	cd bench ; sh run_hyantes.sh > ../$@
