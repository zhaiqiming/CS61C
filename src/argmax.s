.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 32
# =================================================================
argmax:

    # Prologue
    li t5, 1
    blt a1, t5, exit_argmax

    lw t0, 0(a0)
    addi t1, x0, 0

    addi t5, x0, 0

loop_start:
    beq t5, a1, loop_end
    lw t2, 0(a0)
    bgt t2, t0, update_max


loop_continue:
    addi t5, t5, 1
    addi a0, a0, 4
    j loop_start

update_max:
    addi t0, t2, 0
    addi t1, t5, 0
    j loop_continue

exit_argmax:
    li a1, 32
    j exit2

loop_end:
    add a0, t1, zero
    ret
