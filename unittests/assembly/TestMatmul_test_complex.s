.import ../../src/utils.s
.import ../../src/matmul.s
.import ../../src/dot.s

.data
m0: .word 2 5 45 4 410 41 86 845 85 0 42 445
m1: .word 2 86 90 56 33 54 5 44 4 47 50 12 6 18 12 10 45 15 20 51
m2: .word 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
m3: .word 2564 917 730 1022 1045 15784 74522 51895 41572 59584 6720 27839 14577 14416 26004
msg0: .asciiz "expected m2 to be:\n2564 917 730 1022 1045 15784 74522 51895 41572 59584 6720 27839 14577 14416 26004\nInstead it is:\n"

.globl main_test
.text
# main_test function for testing
main_test:

    # load address to array m0 into a0
    la a0 m0

    # load 3 into a1
    li a1 3

    # load 4 into a2
    li a2 4

    # load address to array m1 into a3
    la a3 m1

    # load 4 into a4
    li a4 4

    # load 5 into a5
    li a5 5

    # load address to array m2 into a6
    la a6 m2

    # call matmul function
    jal ra matmul

    ##################################
    # check that m2 == [2564, 917, 730, 1022, 1045, 15784, 74522, 51895, 41572, 59584, 6720, 27839, 14577, 14416, 26004]
    ##################################
    # a0: exit code
    li a0, 2
    # a1: expected data
    la a1, m3
    # a2: actual data
    la a2, m2
    # a3: length
    li a3, 15
    # a4: error message
    la a4, msg0
    jal compare_int_array

    # exit normally
    jal exit
