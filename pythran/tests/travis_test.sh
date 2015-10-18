if $PEP8
then
  PYTHONPATH=$PWD:$PYTHONPATH py.test pythran --pep8 -m pep8
else
  printf "[compiler]\ncflags=-std=c++11 $CXXFLAGS -w\n" > ~/.pythranrc
  OMP_NUM_THREADS=4 PYTHONPATH=$PWD:$PYTHONPATH py.test -n 2 -v $TESTCASE
fi
