#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

struct paquete { int op1; int op2; char operacion; };

long factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in server;
    int c = sizeof(struct sockaddr_in);

    WSAStartup(MAKEWORD(2, 2), &wsa);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 3);

    printf("Servidor Windows esperando...\n");

    while(1) {
        new_socket = accept(server_fd, NULL, NULL);
        struct paquete p;
        int res = 0;

        recv(new_socket, (char*)&p, sizeof(p), 0);

        // Lógica de operaciones
        if (p.operacion == '+') res = p.op1 + p.op2;
        else if (p.operacion == '-') res = p.op1 - p.op2;
        else if (p.operacion == '*') res = p.op1 * p.op2;
        else if (p.operacion == '/') res = (p.op2 != 0) ? p.op1 / p.op2 : 0;
        else if (p.operacion == 'f') res = (int)factorial(p.op1);

        send(new_socket, (char*)&res, sizeof(res), 0);
        closesocket(new_socket);
    }

    WSACleanup();
    return 0;
}
