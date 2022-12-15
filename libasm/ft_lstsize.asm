ft_lstsize:
    push %rbp            # save the old frame pointer
    mov %rsp, %rbp       # set the new frame pointer
    mov $0, %eax         # initialize the size variable to 0

    # Check if the linked list is empty
    cmp $0, %rdi         # compare the list pointer to 0
    jz .end              # if it's 0, jump to the end

    # Iterate through the linked list
    mov %rdi, %rdx       # copy the list pointer to rdx
.loop:
    cmp $0, %rdx         # check if we've reached the end of the list
    jz .end              # if we have, jump to the end

    mov %rdx, %rdi       # copy the current node to rdi
    mov -8(%rdi), %rdx   # move to the next node in the list
    inc %eax             # increment the size variable
    jmp .loop            # go back to the beginning of the loop

.end:
    mov %rbp, %rsp       # restore the old stack pointer
    pop %rbp             # restore the old frame pointer
    ret                  # return the size of the list

