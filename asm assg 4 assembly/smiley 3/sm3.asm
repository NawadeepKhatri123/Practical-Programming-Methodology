;Nawadeep Khatri
;Oct 7
;Q1 : no 3
INCLUDE Irvine32.inc 

.data
    smiley BYTE '@'     ; Define the smiley chara

.code
main PROC
    mov ecx, 80         ; Set ECX to 80
    mov dl, 0           ; Initialize DL to 0

my_loop:
    ; Set the cursor to the current position
    mov dh, 1           ; Set the row position to 1 or 0 (!)
    mov al, dl          ; Move DL into AL
    call Gotoxy         ; Set the cursor to the specified position

    ; Print the smiley character
    mov al, smiley      ; Move the smiley character into AL
    call WriteChar      ; Print the smiley at the current position

    ; Introduce a delay 
    mov eax, 500        ; Load EAX with 500
    call Delay          ; Introduce a delay of 500 milliseconds

    ; Erase the previous smiley by printing a space at the same position
    mov al, ' '         ; Move a space character into AL
    call Gotoxy         ; Reset the cursor to the previous smiley's position
    call WriteChar      ; Overwrite the smiley with a space

    ; Move the smiley to the next position
    inc dl              ; Increment DL to move the smiley to the right
    dec ecx             ; Decrement ECX to track the number of moves
    cmp ecx, 1          ; Compare ECX to 1
    jg my_loop          ; If ECX > 1, continue the loop

    exit                
main ENDP
END main  
