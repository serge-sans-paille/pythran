LU_MASTERS=paper tool
LU_FLAVORS=PDF
# generic Makefile from latex-make package
include LaTeX.mk
check:pdf
	! grep 'LaTeX Warning:' $(LU_MASTERS).log


fullpaper.pdf:paper.pdf tool.pdf
	pdfjoin $^ -o $@
