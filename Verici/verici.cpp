//GNU GPL 2.0 ile lisanslıdır.
#include <signal.h>
#include <cstdio>
#include <iostream>
#include <winsock2.h>

using namespace std;

void windowsSocketControl();
void socketCreateControl(int sock);

int main()
{
    int sock,dataSize;
    char data[1024],data1[1014];
    struct hostent *he;
    struct sockaddr_in server_addr;

    windowsSocketControl();

    he = gethostbyname("127.0.0.1");//Sunucu ip

    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // Soket olusturuldu.
    socketCreateControl(sock); //Soket hata kontrülü

    /*==========Adresleme Başlıyor.==========*/
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr=*((struct in_addr *)he->h_addr);
    server_addr.sin_port=htons(5000);
    memset(&(server_addr.sin_zero), '\0', 8);
    /*==========Adresleme Tamamlandı.==========*/

    if (connect(sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1)
        cout<<"Bir hata oldu."<<endl;

    while(1)
    {
        data[0]=getchar();
        dataSize = sizeof(data);
        send(sock,data,dataSize,0);

    }

    closesocket(sock);
    WSACleanup();
    return 0;

}

void windowsSocketControl()
{
    WSAData version;
    WORD mkword=MAKEWORD(2,2);
    int what=WSAStartup(mkword,&version);
    if(what!=0)
        cout<<"Bu surum desteklenmiyor! - \n"<<WSAGetLastError()<<endl;
    else
        cout<<"Iyi, hersey yolunda!\n"<<endl;
}

void socketCreateControl(int sock)
{
    if(sock==INVALID_SOCKET)
        cout<<"Soket olusturulken hata oldu!\n";

    else
        cout<<"Soket basari ile olusturuldu.\n";
}
