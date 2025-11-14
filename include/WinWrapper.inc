; ======================================================
; Virtual Key Code Constants for Windows API
; ======================================================


; --- Number Keys (0-9) ---
VK_0             = 030h     ; 0 key
VK_1             = 031h     ; 1 key
VK_2             = 032h     ; 2 key
VK_3             = 033h     ; 3 key
VK_4             = 034h     ; 4 key
VK_5             = 035h     ; 5 key
VK_6             = 036h     ; 6 key
VK_7             = 037h     ; 7 key
VK_8             = 038h     ; 8 key
VK_9             = 039h     ; 9 key

; --- Letter Keys (A-Z) ---
VK_A             = 041h     ; A key
VK_B             = 042h     ; B key
VK_C             = 043h     ; C key
VK_D             = 044h     ; D key
VK_E             = 045h     ; E key
VK_F             = 046h     ; F key
VK_G             = 047h     ; G key
VK_H             = 048h     ; H key
VK_I             = 049h     ; I key
VK_J             = 04Ah     ; J key
VK_K             = 04Bh     ; K key
VK_L             = 04Ch     ; L key
VK_M             = 04Dh     ; M key
VK_N             = 04Eh     ; N key
VK_O             = 04Fh     ; O key
VK_P             = 050h     ; P key
VK_Q             = 051h     ; Q key
VK_R             = 052h     ; R key
VK_S             = 053h     ; S key
VK_T             = 054h     ; T key
VK_U             = 055h     ; U key
VK_V             = 056h     ; V key
VK_W             = 057h     ; W key
VK_X             = 058h     ; X key
VK_Y             = 059h     ; Y key
VK_Z             = 05Ah     ; Z key

; ======================================================
; Windows API Declaration
; ======================================================

GetAsyncKeyState PROTO stdcall, vKey: DWORD
; Get the states of given keys (vKey)
; vKey: (int) use the constant above
; If the function succeeds, the return value specifies whether the key was pressed since the last call 
; to GetAsyncKeyState, and whether the key is currently up or down. 
; 1. If MSB is set, the key is **down**
; 2. If LSB is set, the key was pressed after the previous call to GetAsyncKeyState. 

; **However, you should not rely on 2.**
; The return value is zero for the following cases:
; 1. The current desktop is not the active desktop
; 2. The foreground thread belongs to another process and the desktop does not allow the hook or the journal record.
