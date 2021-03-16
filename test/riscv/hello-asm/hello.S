
        .section .text, "ax"
        .global _start
_start:
        li t1, 100
        li t2, 0
        li t3, 1
        li t4, 2
1:
        add t2, t2, 1
        add t3, t3, 2
        add t4, t4, 3
        //sub t1, t1, 1
        add t1, t1, -1
        bnez t1, 1b

        j _start
        
