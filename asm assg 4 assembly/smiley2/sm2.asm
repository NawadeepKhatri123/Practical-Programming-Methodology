;Nawadeep Khatri
;Oct 7
;Delay your smiley face

INCLUDE Irvine32.inc  

.data
    smiley BYTE '@'     ; Define the smiley characters

.code
main PROC
    mov ecx, 80         ; Set the loop counter to 80 
    mov dl, 0           ; Initialize DL to 0 

my_loop:
    call Clrscr         ; Clear the screen before printing the smiley again

    mov dh, 1           ; Set the row position DH to 1 
    mov al, dl          ; Move DL into AL
    call Gotoxy         ; Set the cursor to the position 
    
    mov al, smiley      ; Move the smiley character into AL
    call WriteChar      ; Print the smiley character at the current cursor position
    
    mov eax, 50         ; Load EAX with 50 
    call Delay          ; delay of 50 milliseconds

    inc dl              ; Increment DL to move the smiley to the right
    loop my_loop        ; Decrement ECX and loop back if ECX is not 0

    call WaitMsg        
    exit                
main ENDP
END main  
