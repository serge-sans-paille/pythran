import numpy as np

#pythran export max_len_seq_inner(int64 [], int8[], int, int, int8[])
#runas import numpy as np; x = np.arange(10, dtype=np.int64); y = np.arange(10, dtype=np.int8); z = np.arange(10, dtype=np.int8); max_len_seq_inner(x, y, 10, 2, z)

def max_len_seq_inner(taps, state, nbits, length, seq):
    # Here we compute MLS using a shift register, indexed using a ring buffer
    # technique (faster than using something like np.roll to shift)
    n_taps = taps.shape[0]
    idx = 0
    for i in range(length):
        feedback = state[idx]
        seq[i] = feedback
        for tap in taps:
            feedback ^= state[(tap + idx) % nbits]
        state[idx] = feedback
        idx = (idx + 1) % nbits
    # state must be rolled s.t. next run, when idx==0, it's in the right place
    return np.roll(state, -idx, axis=0)
