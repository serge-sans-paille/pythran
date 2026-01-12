import os
import re
import glob
import pytest
import importlib
import numpy as np
from pythran import compile_pythrancode


def make_benchmark(benchmark_path):
    modname, _ = os.path.splitext(os.path.basename(benchmark_path))
    def the_benchmark(benchmark):
        def setup():

            with open(benchmark_path) as fd:
                code = fd.readlines()
                for line in code:
                    if line.startswith('#bench '):
                        _, bench = line.split(' ', 1)
                        tbench = bench.rsplit(';', 1)

                        setup_env = tbench[0] if len(tbench) == 2 else ""
                        run = tbench[-1].strip()
                        fun, _ = run.split('(', 1)
                        assert run
                        break
                else:
                    raise RuntimeError(f"#bench line not found in {benchmark_path}")
                env = {"builtins": __import__("builtins")}
                exec(setup_env, env)
                benchmark_run = lambda: eval(run, env)

                compiled = compile_pythrancode(modname, "".join(code))
                loader = importlib.machinery.ExtensionFileLoader(modname, compiled)
                spec = importlib.machinery.ModuleSpec(name=modname, loader=loader,
                                                      origin=compiled)
                pymod = importlib._bootstrap._load(spec)
                env[fun] = getattr(pymod, fun)
                return (compiled, benchmark_run), {}

        def target(path, runner):
            return runner()

        def teardown(path, *args):
            # Cleanup code that shouldn't be measured
            os.remove(path)

        result = benchmark.pedantic(
            target,
            setup=setup,
            teardown=teardown,
            rounds=7,          # Number of rounds to run
            warmup_rounds=1    # Number of warmup rounds
        )
    return modname, the_benchmark

for file_py in glob.glob(os.path.join(os.path.dirname(__file__), "..", "tests", "cases", "*.py")):
    with open(file_py) as fd:
        code = fd.read()
        if not re.search(r"#bench\s+", code):
            continue
        if not re.search(r"#\s*pythran\s+export\s+", code):
            continue

    modname, benchmark = make_benchmark(file_py)
    globals()[f'test_{modname}'] = benchmark
