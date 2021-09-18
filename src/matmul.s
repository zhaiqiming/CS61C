.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 34
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 34
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 34
# =======================================================
matmul:

    # Error checks
    li t0, 1
    blt a1, t0, exit_34
    blt a2, t0, exit_34
    blt a4, t0, exit_34
    blt a5, t0, exit_34
    bne a2, a4, exit_34
    
    #init
    addi sp, sp, -20
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw ra, 16(sp)
    li s0, 0
    li s1, 0
    # Prologue
    

outer_loop_start:
    # beq s0, height, outer_loop_end
    li s1, 0

inner_loop_start:
    #save
    addi sp, sp, -32
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    sw a5, 20(sp)
    sw a6, 24(sp)
    sw ra, 28(sp)

    #set argument
    #mv a0, a0
    addi t4, x0, 4
    mul t2, t4, s1
    add a1, a3, t2
    #mv a2,a2
    li a3, 1
    mv a4, a5
    #calculate
    jal dot
    # get ans
    mv t1, a0
    #recover
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 12(sp)
    lw a4, 16(sp)
    lw a5, 20(sp)
    lw a6, 24(sp)
    lw ra, 28(sp)
    addi sp, sp, 32

    mul t2, s0, a5
    add t2, t2, s1
    addi t4, x0, 4
    mul t2, t2, t4
    add t2, a6, t2
    sw t1, 0(t2)
    
inner_loop_end:
    addi s1, s1, 1
    beq s1, a5, outer_loop_end
    j inner_loop_start

outer_loop_end:
    addi s0, s0, 1
    addi t4, x0, 4
    mul t0, t4, a2
    add a0, a0, t0
    beq s0, a1, end 
    j outer_loop_start

end:
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw ra, 16(sp)
    addi sp, sp, 20
    ret

exit_34:
    li a1, 34
    j exit2
