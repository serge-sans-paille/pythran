if $PEP8;
then
  PYTHONPATH=$PWD:$PYTHONPATH py.test pythran --pep8 -m pep8;
else
  printf "[user]\ncxx=$CXX\ncxxflags=$CXXFLAGS\n" > ~/.pythranrc;
  OMP_NUM_THREADS=4 PYTHONPATH=$PWD:$PYTHONPATH py.test -n 1 -v $TESTCASE;
fi
