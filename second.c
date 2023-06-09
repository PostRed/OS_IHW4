#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// cтруктура определяет адрес сервера и адрес клиента.
struct sockaddr_in server, client;

int main(int argc, char *argv[]) {
    int ss,  // сокет сервера
    count,  // количество процессов-шифровальщиков
    start, // начальный индекс
    len_f, // длина кусочка текста
    len, // длина текста
    i;
    char encrypted_text[10000]; // зашифрованный текст (макс. длинна = 10000)
    count = rand() % 5 + 1; // количество процессов-шифровальщиков рандомно от 1 до 5
    ss = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2])); // argv[2] - порт
    // конвертируем IP-адрес в двоичный формат  // argv[1] = IP
    inet_pton(AF_INET, argv[1], &server.sin_addr);
    bind(ss, (struct sockaddr *) &server, sizeof(server));
    socklen_t len_c = sizeof(client);
    len = strlen(argv[3]); // argv[3] - текст
    for (i = 0; i < count; i++) {
        char start_text; // инициализирующее сообщение
        recvfrom(ss, &start_text, sizeof(start_text), 0, (struct sockaddr *) &client, &len_c);
        start = (len / count) * i;
        if (i < count - 1) {
            len_f = len / start; // если это последний шифроващик, то нужно учесть что длина текста не будет нацело делиться на количество процессов-шифровальщиков
        } else {
            len_f = len - (len / count) * (count - 1);
        }
        // отправляем начальный индекс
        sendto(ss, &start, sizeof(start), 0, (struct sockaddr *) &client, len_c);
        // отправляем длинну теста
        sendto(ss, &len_f, sizeof(len_f), 0, (struct sockaddr *) &client, len_c);
        // отправляем текст
        sendto(ss, argv[3] + start, len_f, 0, (struct sockaddr *) &client, len_c);
        // получаем зашифрованный текст
        recvfrom(ss, encrypted_text + start, len_f, 0, (struct sockaddr *) &client, &len_c);
    }
    encrypted_text[len] = '\0';
    printf("%s", encrypted_text);
    //  закрываем сокет сервера
    close(ss);
    return 0;
}
