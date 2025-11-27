ifndef WINSOCKS_INC_
WINSOCKS_INC_ EQU 1

; ======================================================
; WinSocks API's Constant
; ======================================================

; constant for WSADATA
WSADESCRIPTION_LEN EQU 256
WSASYS_STATUS_LEN EQU 128

; ----- constant for sockets -----
; IPv4 and IPv6 are supported address families
AF_INET EQU 2
AF_INET6 EQU 23
; use TCP for connection
SOCK_STREAM EQU 1
; UDP is here just in case
SOCK_DGRAM EQU 2
; 0 is used so the type of socket will choose the protocol for us
IPPROTO_DEFAULT EQU 0

SOMAXCONN EQU 7FFFFFFFh

; ======================================================
; WinSocks API's typedef and struct definition
; ======================================================
;
; NOTE: Information about the implementation of Windows Sockets
WSADATA STRUCT
    wVersion       WORD ?
    wHighVersion   WORD ?
    szDescription  BYTE (WSADESCRIPTION_LEN + 1) DUP(?) ; 257 bytes
    szSystemStatus BYTE (WSASYS_STATUS_LEN + 1)  DUP(?) ; 129 bytes
    iMaxSockets    WORD ?
    iMaxUdpDg      WORD ?
    lpVendorInfo   DWORD ?                              ; 32-bit Pointer
WSADATA ENDS

LPWSADATA TYPEDEF PTR WSADATA

; NOTE: Members
; wVersion:
; The version of the Windows Sockets specification that the Ws2_32.dll expects the caller to use. 
; wHighVersion:
; The version of the Windows Sockets specification that the Ws2_32.dll expects the caller to use. 
; The high-order byte specifies the minor version number;
; the low-order byte specifies the major version number.
; szDescription:
; A NULL-terminated ASCII string into which the Ws2_32.dll copies a description of the Windows Sockets implementation.
; szSystemStatus:
; A NULL-terminated ASCII string into which the Ws2_32.dll copies relevant status or configuration information.

IN_ADDR STRUCT
  S_addr DWORD ?
IN_ADDR ENDS

LPIN_ADDR TYPEDEF PTR IN_ADDR


SOCKADDR_IN STRUCT
  sin_family  SWORD ?
  sin_port    WORD ?
  sin_addr    IN_ADDR <>
  sin_zero    BYTE 8 DUP(0) ; padding to fit 16 bits
SOCKADDR_IN ENDS

LPSOCKADDR_IN TYPEDEF PTR SOCKADDR_IN

SOCKET_HANDLE TYPEDEF DWORD

; ======================================================
; Windows API Declaration
; ======================================================
;

WSAStartup PROTO stdcall,
  wVersionRequired: WORD,
  lpWSAData: LPWSADATA

; NOTE: 
; initiates use of the Winsock DLL by a process according to the data given.
;
; NOTE: 
; RETURN: If successful, the WSAStartup function returns zero, else return error code.

htons PROTO stdcall,
  hostshort: WORD
; NOTE: 
; The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).
;
; NOTE: 
; RETURN: the value in TCP/IP network byte order.

socket PROTO stdcall,
  af: SDWORD,
  sockType: SDWORD,
  protocol: SDWORD


; NOTE: 
; Create a socket
; af: the address family to use
; sockType: the type of the socket
; protocol: just use 0 to not specify anything, as the service provider will determine it
;
; NOTE: 
; RETURN: If successful, the WSAStartup function returns zero, else return error code.

bind PROTO stdcall,
  s: SOCKET_HANDLE,
  lpName: LPSOCKADDR_IN,
  namelen: DWORD

; NOTE:
; The bind function associates a local address with a socket.
; lpName: A pointer to a sockaddr structure of the local address to assign to the bound socket .
; namelen: The length, in bytes, of the sockaddr structure pointed to by the name parameter.
; NOTE:
; RETURN: If no error occurs, connect returns zero. Otherwise, it returns SOCKET_HANDLE_ERROR.

listen PROTO stdcall,
  s: SOCKET_HANDLE,
  backlog: DWORD
; NOTE:
; The listen function places a socket in a state in which it is listening for an incoming connection.
; the socket must be bound and unconnected.
; backlog: the maximum queue, just use SOMAXCONN
;
; NOTE: 
; RETURN: If no error occurs, listen returns zero. Otherwise, a value of SOCKET_HANDLE_ERROR is returned


connect PROTO stdcall,
  s: SOCKET_HANDLE,
  lpName: LPSOCKADDR_IN,
  namelen: DWORD

; NOTE:
; The connect function establishes a connection to a specified socket.
; lpName: A pointer to the sockaddr structure to which the connection should be established.
; namelen: The length, in bytes, of the sockaddr structure pointed to by the name parameter.
; NOTE:
; RETURN: If no error occurs, connect returns zero. Otherwise, it returns SOCKET_HANDLE_ERROR.

accept PROTO stdcall,
  s: SOCKET_HANDLE,
  sockaddr: LPSOCKADDR_IN,
  addrlen: PTR DWORD

; NOTE:
; Establish the connection and return a new socket that made the connection
; sockaddr: An optional pointer to a buffer that receives the address of the connecting entity, as known to the communications layer.
; addrlen: An optional pointer to an integer that contains the length of structure pointed to by the addr parameter.
; 
; NOTE:
; RETURN: If no error occurs, accept returns a value of type SOCKET_HANDLE that is a descriptor for the new socket. 
; This returned value is a handle for the socket on which the actual connection is made.

send PROTO stdcall,
  s: SOCKET_HANDLE,
  buf: PTR BYTE,
  len: DWORD,
  flags: DWORD; just pass 0
; NOTE:
; Send data to the connected socket.
; the flag is not used here, so just pass 0
;
; NOTE:
; RETURN: If no error occurs, send returns the total number of bytes sent,
; which can be less than the number requested to be sent in the len parameter. 
; Otherwise, a value of SOCKET_HANDLE_ERROR is returned

recv PROTO stdcall,
  s: SOCKET_HANDLE,
  buf: PTR BYTE,
  len: DWORD,
  flags: DWORD; just pass 0
; NOTE:
; Send data to the connected socket.
; the flag is not used here, so just pass 0
;
; NOTE:
; RETURN: If no error occurs, send returns the total number of bytes sent,
; which can be less than the number requested to be sent in the len parameter. 
; Otherwise, a value of SOCKET_HANDLE_ERROR is returned

closesocket PROTO stdcall,
  s: SOCKET_HANDLE
; NOTE:
; Close the socket
;
; NOTE:
; RETURN: If no error occurs, closesocket returns zero. Otherwise, a value of SOCKET_ERROR is returned

endif
