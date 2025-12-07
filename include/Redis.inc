ifndef REDIS_INC_
REDIS_INC_ EQU 1

INCLUDE WinSocks.inc

HANDLE TEXTEQU <DWORD>

; ======================================================
; Redis Client Interfaces
; ======================================================


RedisConnect PROTO stdcall,
hostAddress: LPSOCKADDR_IN
; NOTE: Establish an connection to the designated RESP-compatible server
;
; NOTE:
; RETURN: an descriptor to the socket to the RESP-compatible server.

CreateArt PROTO stdcall,
hRedis: HANDLE,
artData: PTR BYTE,
dataLen: DWORD

; NOTE: Create an art using given data and store it to the server
;
; NOTE:
; RETURN: an ID used to query the art



ReadArt PROTO stdcall,
hRedis: HANDLE,
buffer: PTR BYTE,
artID: DWORD,
; NOTE: retrieve an art using given ID and store the data in buffer
;
; NOTE:
; RETURN: maybe an error check (WIP)


UpdateArt PROTO stdcall,
hRedis: HANDLE,
buffer: PTR BYTE,
dataLen: DWORD,
artID: DWORD
; NOTE: update the art using given ID and update the data stored in server
;
; NOTE:
; RETURN: maybe an error check (WIP)
endif
