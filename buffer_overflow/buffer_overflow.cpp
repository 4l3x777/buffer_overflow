#include <Windows.h>
#include <winsock.h>
#include <stdio.h>
#pragma comment (lib, "ws2_32.lib")

#pragma comment(linker, "/STACK:16777216")

#define PORT 4444

void buffer_overflow_vuln(char *buf)
{
	LPVOID data;
	DWORD size;
	char localBuf[0x100000];
	size = *(DWORD*)buf;
	data = buf + 4;
	printf("size: %d\n",size);
	memcpy(localBuf, data, size);
}

int main()
{	
	void* buf = malloc(0x100f00);
	WSADATA wsaData;
	SOCKET s, client_sock;
	sockaddr_in serv_addr, client_addr;

	WSAStartup(0x202, &wsaData);		
	s = socket(AF_INET, SOCK_STREAM, 0);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = 0;
	bind(s, (sockaddr*)&serv_addr, sizeof(serv_addr));

	listen(s, 1);
		
	client_sock = accept(s, NULL, NULL);
	int msize = recv(client_sock, (char*)buf, 0x100f00, 0);
	
	buffer_overflow_vuln((char*)buf);
	WSACleanup();

	free(buf);

	system("pause");
    return 0;
}

