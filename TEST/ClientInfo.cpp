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
  
    //�������˿ڴ���  
    SOCKET m_hServerSocket;  
    m_hServerSocket = socket(AF_INET,SOCK_STREAM,0);  
  
    //�������˿ڰ�  
    SOCKADDR_IN m_addr;  
    m_addr.sin_family = AF_INET;  
    m_addr.sin_addr.S_un.S_addr = INADDR_ANY;//����������ǵ������ģ���������������ip��ַ������Ƕ��������������е�����һ���ip��ַ  
    m_addr.sin_port = htons(9800);  
    ret = bind(m_hServerSocket,(LPSOCKADDR)&m_addr,sizeof(m_addr));  
      
    //�������˿ڿ�ʼ����  
    ret = listen(m_hServerSocket,10);//�ڶ�������ָ����������������  
  
    WSADATA cli_wsadata;  
    ret = WSAStartup(version,&cli_wsadata);  
  
    //�ͻ��˶˿ڴ���  
    SOCKET m_hClientSocket;  
    m_hClientSocket = socket(AF_INET,SOCK_STREAM,0);  
  
  
    //�ͻ����������������������  
    SOCKADDR_IN m_addr1;  
    m_addr1.sin_family = AF_INET;  
    m_addr1.sin_addr.S_un.S_addr = inet_addr("139.196.167.131");//��������ip��ַ  
    m_addr1.sin_port = htons(10000);//������socket�Ķ˿ں�  
    ret = connect(m_hClientSocket,(LPSOCKADDR)&m_addr1,sizeof(m_addr1));//�ӿͻ��˶˿�m_hClientSocket��������˿�m_addr1������������  
      
    //0xCD,0xCD,0xCD,0XCD. ��ΪDEBUGΪÿ���ֽڳ�ʼ��0xcd(204),��δ��ȷȡ�öԷ�IP��������ı���δ��ʼ���Ľ����   
    //��ʼʹ��accept��getpeernameһֱ����204.204.204.204��ԭ��  
  
    SOCKET com_Sock;  
    SOCKADDR_IN addr_conn;  
    int nSize = sizeof(addr_conn);  
    //initialize the memory block via the memset function  
    memset((void *)&addr_conn,0,sizeof(addr_conn));  
  
    com_Sock = accept(m_hServerSocket,NULL,NULL);           //�����Ӷ�����ȡ��һ�����ӽ���ͨ��  
    //��ʼʱ���������Ϊ�ѵ���������д����(int *)(sizeof(addr_conn))�����Բ��ᱨ����ȡ������ȷ���������  
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