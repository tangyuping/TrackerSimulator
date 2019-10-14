#include "StdAfx.h"
#include "ClientInfo.h"
#include <iostream>  
#include <winsock.h>  
#include <stdio.h>  
  
#pragma comment(lib, "wsock32")  
ClientInfo::ClientInfo(void)
{
}

ClientInfo::~ClientInfo(void)
{
}


using namespace std;  
  
void main()   
{  
    int ret = 0;  
    WSADATA wsadata;  
    WORD version = MAKEWORD(2,0);  
    ret = WSAStartup(version,&wsadata);  
  
    //服务器端口创建  
    SOCKET m_hServerSocket;  
    m_hServerSocket = socket(AF_INET,SOCK_STREAM,0);  
  
    //服务器端口绑定  
    SOCKADDR_IN m_addr;  
    m_addr.sin_family = AF_INET;  
    m_addr.sin_addr.S_un.S_addr = INADDR_ANY;//如果服务器是单网卡的，则就是这块网卡的ip地址；如果是多网卡，则是其中的任意一块的ip地址  
    m_addr.sin_port = htons(9800);  
    ret = bind(m_hServerSocket,(LPSOCKADDR)&m_addr,sizeof(m_addr));  
      
    //服务器端口开始监听  
    ret = listen(m_hServerSocket,10);//第二个参数指定最大申请的连接数  
  
    WSADATA cli_wsadata;  
    ret = WSAStartup(version,&cli_wsadata);  
  
    //客户端端口创建  
    SOCKET m_hClientSocket;  
    m_hClientSocket = socket(AF_INET,SOCK_STREAM,0);  
  
  
    //客户端向服务器发送连接请求  
    SOCKADDR_IN m_addr1;  
    m_addr1.sin_family = AF_INET;  
    m_addr1.sin_addr.S_un.S_addr = inet_addr("139.196.167.131");//服务器的ip地址  
    m_addr1.sin_port = htons(10000);//服务器socket的端口号  
    ret = connect(m_hClientSocket,(LPSOCKADDR)&m_addr1,sizeof(m_addr1));//从客户端端口m_hClientSocket想服务器端口m_addr1发送连接请求  
      
    //0xCD,0xCD,0xCD,0XCD. 因为DEBUG为每个字节初始化0xcd(204),你未正确取得对方IP，并且你的变量未初始化的结果。   
    //开始使用accept和getpeername一直返回204.204.204.204的原因  
  
    SOCKET com_Sock;  
    SOCKADDR_IN addr_conn;  
    int nSize = sizeof(addr_conn);  
    //initialize the memory block via the memset function  
    memset((void *)&addr_conn,0,sizeof(addr_conn));  
  
    com_Sock = accept(m_hServerSocket,NULL,NULL);           //从连接队列中取第一个连接进行通信  
    //开始时候错误是因为把第三个参数写成了(int *)(sizeof(addr_conn))，所以不会报错但是取不到正确结果！！！  
    //com_Sock = accept(m_hServerSocket,(SOCKADDR *)&addr_conn,&nSize); //or  
    getpeername(com_Sock,(SOCKADDR *)&addr_conn,&nSize);  
  
    char szPeerAddress[16];  
    //Sets buffers to a specified character.  
    memset((void *)szPeerAddress,0,sizeof(szPeerAddress));  
    cout << szPeerAddress << "**************" <<endl;  
    //If no error occurs, inet_ntoa returns a character pointer to a static buffer   
    //containing the text address in standard ".'' notation  
    //strcpy(szPeerAddress,inet_ntoa(addr_conn.sin_addr)); 
	strcpy_s(szPeerAddress,inet_ntoa(addr_conn.sin_addr));
    //Copy a string.the second parameter strSource Null-terminated source string  
    cout << szPeerAddress << endl;  
    //so remember that every time use the inet_ntoa, you must copy the result by yourself  
    //or it will be covered by the other value  
    addr_conn.sin_addr.S_un.S_addr = inet_addr("139.196.167.131");  
    cout << inet_ntoa(addr_conn.sin_addr) << endl;  
  
    cout << endl;  
  
}  