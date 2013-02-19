RST2HTML=rst2html --stylesheet-path=os.css --link-stylesheet --cloak-email-addresses --pep-references
SED=sed
ZIP=zip
CP=cp

TARGETS=index.html devguide.html manual.html authors.html todo.html license.txt
EXTRA_DIST=os.css
ZIPTARGET=pythran.zip

all:$(TARGETS)

dist:all
	$(ZIP) $(ZIPTARGET) $(TARGETS) $(EXTRA_DIST)

clean:
	$(RM) $(TARGETS) $(ZIPTARGET)

index.html:../README.rst Makefile
	$(RST2HTML) $< $@
	$(SED) -i -e 's,MANUAL file,<a href="manual.html">MANUAL</a>,'\
	          -e 's,DEVGUIDE file,<a href="devguide.html">DEVGUIDE</a>,'\
			  -e 's,AUTHORS file,<a href="authors.html">AUTHORS</a>,'\
			  -e 's,TODO file,<a href="todo.html">TODO</a>,'\
			  -e 's,LICENSE,<a href="license.txt">LICENSE</a>,'\
			  -e 's,pythran/tests/cases/,<a href="https://github.com/serge-sans-paille/pythran/tree/master/pythran/tests/cases">pythran/tests/cases</a>,'\
			  $@

devguide.html:../doc/DEVGUIDE.rst Makefile
	$(RST2HTML) $< $@

manual.html:../doc/MANUAL.rst Makefile
	$(RST2HTML) $< $@

authors.html:../AUTHORS Makefile
	$(RST2HTML) $< $@

todo.html:../TODO Makefile
	$(RST2HTML) $< $@

license.txt:../LICENSE
	$(CP) $< $@
