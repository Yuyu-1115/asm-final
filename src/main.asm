.386

INCLUDE Irvine32.inc
INCLUDE WinWrapper.inc  

.data
    msg_press_a  db "Press 'A' to exit...", 0Ah, 0Dh, 0

.code
main PROC
    mov edx, OFFSET msg_press_a
    call WriteString

WaitFor_A:
    invoke GetAsyncKeyState, VK_A
    test ax, 8000h
    
    jz WaitFor_A
    
    INVOKE ExitProcess, 0

main ENDP
END main