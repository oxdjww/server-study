#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_CLIENTS 5

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    // 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("서버 소켓 생성 실패");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 소켓을 주소에 바인딩
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("바인딩 실패");
        exit(EXIT_FAILURE);
    }

    // 클라이언트의 연결을 기다림
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("대기 실패");
        exit(EXIT_FAILURE);
    }

    printf("서버가 클라이언트 연결을 기다리고 있습니다...\n");

    // 클라이언트 연결 받기
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
    if (client_socket == -1) {
        perror("연결 수락 실패");
        exit(EXIT_FAILURE);
    }

    printf("클라이언트 연결 성공!\n");

    // 클라이언트와 통신
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            perror("수신 실패 또는 클라이언트 종료");
            break;
        }
        
        printf("클라이언트로부터 메시지 수신: %s", buffer);

        // 에코 메시지를 클라이언트에게 다시 보냄
        send(client_socket, buffer, strlen(buffer), 0);
    }

    // 소켓 종료
    close(client_socket);
    close(server_socket);

    return 0;
}
