#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// структура определяет адрес сервера
struct sockaddr_in server;

int main(int argc, char *argv[]) {
    char text[10000], // исходный текст
        encrypted_text[10000], // зашифрованный текст
        start_text = '*'; // инициализирующее сообщение
    int cs, // сокет для соединения с сервером
    start, // начальный индекс текста
    len, // длина текста, который нужно зашифровать
    i; // без комментариев
    
    // создаем новый сокет, который используется для соединения с сервером
    cs = socket(AF_INET, SOCK_STREAM, 0);
    if (cs < 0) {
        exit(1); // ошибка создания сокета
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2])); // argv[2] - порт
    // конвертируем IP-адрес в двоичный формат
    inet_pton(AF_INET, argv[1], &server.sin_addr); // argv[1] = IP
    
    socklen_t help = sizeof(server);
    // отправляем инициализирующее сообщение на сервер, 
    sendto(cs, &start_text, sizeof(start_text), 0, (struct sockaddr *) &server, help);
    // чтобы получить начальный индекс текста `start` его длину `len` и сам текст `text`
    recvfrom(cs, &start, sizeof(start), 0, (struct sockaddr *) &server, &help);
    recvfrom(cs, &len, sizeof(len), 0, (struct sockaddr *) &server, &help);
    recvfrom(cs, text, len, 0, (struct sockaddr *) &server, &help);
    
    // шифруем текст просто сдвигая каждый символ
    for (i = 0; i < len; i++) {
        encrypted_text[i] = text[i] + 2;
    }
    // отправляет данные на сервер.
    sendto(cs, encrypted_text, len, 0, (struct sockaddr *) &server, help);

    close(cs); // закрываем сокет
    return 0;
}
