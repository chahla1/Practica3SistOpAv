#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

struct paquete { int op1; int op2; char operacion; };

DWORD WINAPI AtenderCliente(LPVOID lpParam) {
    SOCKET sock = *(SOCKET*)lpParam;
    struct paquete p;
    int res = 0;

    recv(sock, (char*)&p, sizeof(p), 0);


    res = p.op1 + p.op2;

    send(sock, (char*)&res, sizeof(res), 0);
    closesocket(sock);
    free(lpParam);
    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in server;

    WSAStartup(MAKEWORD(2, 2), &wsa);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 3);

    while(1) {
        SOCKET* client_sock = malloc(sizeof(SOCKET));
        *client_sock = accept(server_fd, NULL, NULL);


        CreateThread(NULL, 0, AtenderCliente, client_sock, 0, NULL);
    }
}
