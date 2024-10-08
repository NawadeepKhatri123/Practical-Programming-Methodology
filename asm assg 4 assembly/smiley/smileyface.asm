;Nawadeep Khatri
;Oct 7
;Print smiley faces

INCLUDE Irvine32.inc  

.data
    smiley BYTE '@', 0 
	
.code
main PROC
    mov ecx, 79         ; Set ECX to 79, the number of smiley faces to print

myloop:
    mov al, smiley      ; Move the smiley character into the AL register
    call WriteChar      ; Print the character in AL (@)
    dec ecx             ; Decrement the counter
    cmp ecx, 1          ; Compare ECX to 1
    jg myloop           ; If ECX > 1, repeat the loop and print another smiley

    exit               
main ENDP
END main 
