'''
This modules contains a distutils extension mechanism for Pythran
    * PythranExtension: is used as distutils's Extension
'''

import pythran.config as cfg
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
    def __init__(self, name, sources, *args, **kwargs):
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
            base, _ = os.path.splitext(source)
            output_file = base + '.cpp'  # target name

            # stage 0 when we have the .py
            if os.path.exists(source):
                stage = 0
            # stage 1 otherwise. `.cpp' should already be there
            # as generated upon stage 0
            else:
                assert os.path.exists(output_file)
                stage = 1
                source = output_file

            # stage-dependant processing
            if stage == 0:
                # get the last name in the path
                if '.' in name:
                    module_name = os.path.splitext(name)[-1][1:]
                else:
                    module_name = name
                tc.compile_pythranfile(source, output_file,
                                       module_name, cpponly=True)
            cxx_sources.append(output_file)

        kwargs.update(cfg.make_extension())
        Extension.__init__(self, name, cxx_sources, *args, **kwargs)
