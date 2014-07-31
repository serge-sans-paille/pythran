from test_env import TestEnv


@TestEnv.module
class TestTime(TestEnv):

    def test_time_and_sleep(self):
        self.run_test("""
def time_and_sleep():
    import time
    begin = time.time()
    time.sleep(2)
    end = time.time()
    return (end - begin) < 2.05 and (end - begin) > 1.95""", time_and_sleep=[])
