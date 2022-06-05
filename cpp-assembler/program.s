#comment
# label    dsa    
mov input, r2
mov 0, r4
mov 1, r5
label loop
sub r2,1,r2
mov r4, r3
mov r5, r4
add r3, r4, r5
les 0, r2, loop
mov r3,output