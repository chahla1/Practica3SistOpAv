#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

struct paquete {
    int op1;
    int op2;
    char operacion;
};

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    struct paquete envio;
    int resultado;


    WSAStartup(MAKEWORD(2, 2), &wsa);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error de conexion\n");
        return 1;
    }

    printf("Num1 Num2 Op (+,-,*,/,f): ");
    scanf("%d %d %c", &envio.op1, &envio.op2, &envio.operacion);

    send(s, (char*)&envio, sizeof(envio), 0);
    recv(s, (char*)&resultado, sizeof(resultado), 0);

    printf("Resultado: %d\n", resultado);

    closesocket(s);
    WSACleanup();
    return 0;
}