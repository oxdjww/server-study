#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // 서버 IP 주소(=클라이언트 IP 주소, 즉 로컬)
#define PORT 12345

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[1024];

    // 소켓 생성
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("클라이언트 소켓 생성 실패");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 서버에 연결
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("서버 연결 실패");
        exit(EXIT_FAILURE);
    }

    printf("서버에 연결되었습니다. 메시지를 입력하세요 (종료하려면 'quit' 입력).\n");

    while (1) {
        printf("메시지 입력: ");
        fgets(message, sizeof(message), stdin);

        // 'quit'을 입력하면 클라이언트 종료
        if (strncmp(message, "quit", 4) == 0)
            break;

        // 서버로 메시지 전송
        send(client_socket, message, strlen(message), 0);

        // 서버로부터 에코 메시지 수신
        memset(message, 0, sizeof(message));
        recv(client_socket, message, sizeof(message), 0);
        printf("서버로부터 수신한 메시지: %s", message);
    }

    // 소켓 종료
    close(client_socket);

    return 0;
}
