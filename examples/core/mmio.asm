BITS 64
mov al       , byte[rbx]
add al       , 1
mov byte[rbx], al
hlt