INCLUDE Irvine32.inc

INCLUDE WinWrapper.inc  
INCLUDE WinSocks.inc  
INCLUDE HttpUtil.inc

.data
  serviceData WSADATA <>
  hSocket SOCKET_HANDLE ?
  hClient SOCKET_HANDLE ?
  service SOCKADDR_IN <>
  clientAddress SOCKADDR_IN <>
  clientLength DWORD SIZEOF service
  buffer BYTE 2048 DUP(?)
  respBuffer BYTE 64 DUP(?)
  acceptMsg BYTE "Connection accepted...", 0
  ppmBody   BYTE "P3", 13, 10
            BYTE "3 2", 13, 10
            BYTE "255", 13, 10
            BYTE "255 0 0", 13, 10
            BYTE "0 255 0", 13, 10
            BYTE "0 0 255", 13, 10
            BYTE "255 255 0", 13, 10
            BYTE "255 255 255", 13, 10
            BYTE "0 0 0", 13, 10
            BYTE 0
.code
main PROC
  ; initializa windows sockets with version 2.2
  invoke WSAStartup, 0202h, ADDR serviceData
  ; initiate sockaddr_in
  mov service.sin_family, AF_INET; ipv4
  mov service.sin_addr, 0; 0.0.0.0
  invoke htons, 8080;
  mov service.sin_port, ax;
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
ServerLoop:
  ; establish connection
  invoke accept, hSocket, ADDR clientAddress, ADDR clientLength
  mov hClient, eax;

  mov edx, OFFSET acceptMsg
  call WriteString
  call Crlf

  invoke recv, hClient, ADDR buffer, LENGTH buffer, 0

  ; sending response

  mov edx, OFFSET ppmHeader
  call WriteString

  mov edx, OFFSET respBuffer
  call WriteString

  mov edx, OFFSET ppmBody
  call WriteString


  ; wsprintf return ohow many bytes are written
  invoke Str_length, OFFSET ppmBody
  ; preserve length
  mov ebx, eax
  invoke Str_length, OFFSET ppmHeader
  invoke send, hClient, OFFSET ppmHeader, eax, 0
  invoke wsprintf, OFFSET respBuffer, OFFSET lengthFmt, ebx
  invoke send, hClient, OFFSET respBuffer, eax, 0
  invoke send, hClient, OFFSET ppmBody, ebx, 0

  invoke closesocket, hClient
  jmp ServerLoop
exitProgram:
  exit
main ENDP
END main
