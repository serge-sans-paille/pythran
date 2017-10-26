from subprocess import check_output
import os
import sys
os.environ['PYTHONPATH']='../../../../..'
os.chdir("pythran")
check_output(["python", "setup.py", "build_ext"])
os.chdir("..")

import glob
import timeit

candidate = os.path.join("pythran","hyantes.py")
sys.path.append("pythran")
nb_iter = 21
median = lambda x: sorted(x)[len(x) / 2]
with file(candidate) as content:
    runas = [line for line in content.readlines()
            if line.startswith('#runas')]
    if len(runas) == 1:
        module_name, _ = os.path.splitext(
                os.path.basename(candidate))
        # pythran + omp
        runas_commands = runas[0].replace('#runas', '').split(";")
        runas_context = ";".join(["import {0}_omp".format(
                        module_name)] + runas_commands[:-1])
        runas_command = "{0}_omp.{1}".format(module_name,
                        runas_commands[-1])

        ti = timeit.Timer(runas_command, runas_context)
        timing = median(ti.repeat(nb_iter, number=1))
        print timing

