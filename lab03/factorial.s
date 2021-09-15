.globl factorial

.data
n: .word 3

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    addi s2, x0, 1
    add s3, x0, x0
loop:
    beq s3, a0, exit
    addi s3, s3, 1
    mul s4, s3, s2
    add s2, s4, x0
    j loop
exit:
    add a0, s4, x0
    jr ra
