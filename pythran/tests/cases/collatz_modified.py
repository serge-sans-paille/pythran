#pythran export collatz_modified(int)
#runas collatz_modified(10)

def collatz_modified(target):
    start = 1
    while True:
        i = start
        steps = 0
        while True:
            if i == 1:
                break
            if i % 2 == 0:
                i = i // 2
            else:
                i = 3 * i + 1
            steps += 1
        if steps == target:
            return start
        start += 1
