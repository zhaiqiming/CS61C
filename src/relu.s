.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 32
# ==============================================================================
relu:
    # Prologue
    li t5, 1
    blt a1, t5, exit_relu
    
    add t0, x0, x0
    addi t2, x0, 4


loop_start:
    beq t0, a1, loop_end 
    mul t1, t0, t2
    add t3, a0, t1
    lw t4, 0(t3)
    bgt t4, x0, loop_continue
    sub t4, t4, t4
    sw t4, 0(t3)



loop_continue:
    addi t0, t0, 1
    j loop_start

exit_relu:
    li a1, 32
    j exit2

loop_end:

	ret
