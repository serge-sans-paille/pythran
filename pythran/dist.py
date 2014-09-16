'''
This modules contains a distutils extension mechanism for Pythran
    * PythranExtension: is used as distutils's Extension
'''

import pythran.toolchain as tc

from distutils.core import Extension
import os.path
import os


class PythranExtension(Extension):
    '''
    Description of a Pythran extension

    Similar to distutils.core.Extension except that the sources are .py files
    They must be processable by pythran, of course.

    The compilation process ends up in a native Python module.
    '''
    def __init__(self, name, sources, **kwargs):
        # the goal is to rely on original Extension
        # to do so we convert the .py to .cpp with pythran
        # and register the .cpp in place of the .py
        # That's stage 0, and it's enough if you get the source
        # from github and `python setup.py install it`
        #
        # *But* if you want to distribute the source through
        # `python setup.py sdist` then the .py no longer exists
        # and only the .cpp is distributed. That's stage 1

        cxx_sources = []
        for source in sources:
            base, ext = os.path.splitext(source)
            output_file = base + '.cpp'  # target name

            # stage 0 when we have the .py
            if os.path.exists(source):
                stage = 0
            # stage 1 otherwise. `.cpp' should already be there
            # as generated upon stage 0
            else:
                assert os.path.exists(output_file)
                stage = 1
                ext = '.cpp'
                source = output_file

            # stage-dependant processing
            if stage == 0:
                tc.compile_pythranfile(source, output_file,
                                       module_name=name, cpponly=True)
            cxx_sources.append(output_file)

        # in both cases, setup the flags in a pythran-compatible way.
        kwargs['language'] = 'c++'
        kwargs.setdefault('extra_compile_args', []).extend(tc.cppflags() +
                                                           tc.cxxflags())
        # FIXME: force the compiler to be pythran's ones
        # I cannot find a way to do this in a less intrusive manner
        os.environ['CC'] = tc.default_compiler()
        os.environ['CXX'] = tc.default_compiler()
        kwargs.setdefault('extra_link_args', []).extend(tc.ldflags())
        Extension.__init__(self, name, cxx_sources, **kwargs)
