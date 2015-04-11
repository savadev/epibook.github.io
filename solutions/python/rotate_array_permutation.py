# Rotate_array_permutation.h 848813e190b1b85a8e75107fe8513c3be38ad1a9
import fractions


# @include
def rotate_array(rotate_amount, A):
    rotate_amount %= len(A)
    num_cycles = fractions.gcd(len(A), rotate_amount)
    cycle_length = len(A) // num_cycles

    for c in range(num_cycles):
        apply_cyclic_permutation(rotate_amount, c, cycle_length, A)


def apply_cyclic_permutation(rotate_amount, offset, cycle_length, A):
    temp = A[offset]
    for i in range(1, cycle_length):
        idx = (offset + i * rotate_amount) % len(A)
        A[idx], temp = temp, A[idx]
    A[offset] = temp
# @exclude