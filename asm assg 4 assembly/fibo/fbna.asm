;Nawadeep Khatri
;Oct 7
; Find the nth fibonacci number
INCLUDE Irvine32.inc 

.data
prompt BYTE "Which Fibonacci number do you wish: ", 0  ; Prompt message asking for Fibonacci input
result_msg BYTE "Fibonacci value = ", 0                ; Message to display the Fibonacci result

.code
main PROC
   
    ; Display the prompt message to the user
    mov edx, OFFSET prompt  	; Load the address of the prompt message into EDX
    call WriteString        				; Print the prompt message

   
    call ReadDec            ; Read a decimal number input from the user, result stored in EAX
    mov ecx, eax            ; Move the user's input Fibonacci index into ECX
  
    
    mov eax, 1              ; EAX will hold the current Fibonacci number
    mov ebx, 1              ; EBX will hold the previous Fibonacci number

    ; Handle the case where the user requests the 1st Fibonacci number or lower
    cmp ecx, 1              ; Compare ECX  with 1 (users iinput)
    jle print_result         ; If ECX <= 1, jump to print_result 

ggloop:							;instialize a loop
    ; Calculate the next Fibonacci number
    add eax, ebx            ; Add EBX the previous Fibonacci to EAX  the current Fibonaccito get the next fibonacci and store it in eax
    xchg eax, ebx           ; Swap EAX and EBX, so EBX now holds the current Fibonacci, and EAX holds the previous one
  
    ; Decrease the counter and check if we need to continue looping
    dec ecx                 ; Decrement the counter (ECX = ECX - 1)
    cmp ecx, 1              ; Check if the counter is greater than 1
    jg ggloop               ; If ECX > 1, repeat the loop to calculate the next Fibonacci number

print_result:
    ; Display the result message and the calculated Fibonacci number
    mov edx, OFFSET result_msg  ; Load the address of the result message into EDX
    call WriteString            ; Print the result message
    call WriteDec               ; Print the current Fibonacci number (in EAX)
        		 
    exit                        
main ENDP

END main  

