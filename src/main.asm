INCLUDE Irvine32.inc

INCLUDE WinWrapper.inc  
INCLUDE WinSocks.inc  
INCLUDE HttpUtil.inc
INCLUDE Redis.inc

.data
  REDIS_IP EQU 61EC4A64h;

  serviceData WSADATA <>
  hSocket SOCKET_HANDLE ?
  hClient SOCKET_HANDLE ?
  hRedis SOCKET_HANDLE ?

  service SOCKADDR_IN <>
  redisAddress SOCKADDR_IN <>
  clientAddress SOCKADDR_IN <>

  clientLength DWORD SIZEOF service

  buffer BYTE 65536 DUP(?)
  respBuffer BYTE 64 DUP(?)

  acceptMsg BYTE "Connection accepted...", 0Dh, 0Ah, 0
  redisInitMsg BYTE "[INFO] Successfully establish connection to Redis...", 0Dh, 0Ah, 0
  testMsg BYTE "[INFO] test...", 0Dh, 0Ah, 0
.code
main PROC
  ; initializa windows sockets with version 2.2
  invoke WSAStartup, 0202h, ADDR serviceData

  ; initiate the server's in address
  mov service.sin_family, AF_INET; ipv4
  mov service.sin_addr, 0; 0.0.0.0
  invoke htons, 8080;
  mov service.sin_port, ax;

  ; initiate the redis server's address
  mov redisAddress.sin_family, AF_INET; ipv4
  mov redisAddress.sin_addr, REDIS_IP
  invoke htons, 6379;
  mov redisAddress.sin_port, ax;


  jnz exitProgram
  ; create TCP socket in IPv4
  invoke socket, AF_INET, SOCK_STREAM, 0
  mov hSocket, eax
  ; bind the socket into local addresses
  invoke bind, hSocket, ADDR service, SIZEOF service
  jnz ExitProgram
  ; start listening
  invoke listen, hSocket, SOMAXCONN
  jnz ExitProgram

  ; establish connection to redis
  invoke RedisConnect, ADDR redisAddress
  .IF eax == -1
    jmp exitProgram
  .ENDIF
  mov hRedis, eax

  mov edx, OFFSET redisInitMsg
  call WriteString

ServerLoop:
  ; establish connection
  invoke accept, hSocket, ADDR clientAddress, ADDR clientLength
  mov hClient, eax;

  mov edx, OFFSET acceptMsg
  call WriteString

  ; receiving HTTP request
  invoke recv, hClient, ADDR buffer, LENGTH buffer, 0


CREATE: 
; POST, 

UPLOAD:
; POST, 

READ:
; GET, id: int




  ; wsprintf return ohow many bytes are written
  invoke Str_length, OFFSET ppmBody
  ; preserve length
  mov ebx, eax
  invoke Str_length, OFFSET ppmHeader
  invoke send, hClient, OFFSET ppmHeader, eax, 0
  invoke wsprintf, OFFSET buffer, OFFSET lengthFmt, ebx
  invoke send, hClient, OFFSET buffer, eax, 0
  invoke send, hClient, OFFSET ppmBody, ebx, 0

  invoke closesocket, hClient
  jmp ServerLoop

DOWNLOAD:

exitProgram:
  exit
main ENDP
END main
