/**
 * @file main.cpp
 * @author Метальников М.А.
 * @version 1.0
 * @date 22.12.2023
 * @brief Главный модуль сервера
 */
#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "ErrorLog.h"

/**
 * @brief Главный модуль сервера.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Возвращает 0 в случае успешного завершения.
 */
int main(int argc, char *argv[])
{
    unsigned short port = 33333; /**< Порт по умолчанию */
    int qlen = 10; /**< Длина очереди по умолчанию */
    std::string dbFile = "/etc/vcalc.conf"; /**< Путь к файлу базы данных. */

    int opt;
    while ((opt = getopt(argc, argv, "p:q:d:h:?")) != -1) {
        switch (opt) {
        case 'p':
            port = std::stoi(optarg);
            break;
        case 'q':
            qlen = std::stoi(optarg);
            break;
        case 'd':
            dbFile = optarg;
            break;
        case 'h':
            // Вывод справки по использованию приложения
            std::cout << "Usage: " << argv[0] << " -p <port> -q <queue_length> -d <database_file>" << std::endl;
            return 0;
        case '?':
            // Обработка ошибок ввода аргументов командной строки
            if (optopt == 'p' || optopt == 'q' || optopt == 'd') {
                std::cerr << "Option -" << static_cast<char>(optopt) << " requires an argument." << std::endl;
            } else {
                std::cerr << "Unknown option: -" << static_cast<char>(optopt) << std::endl;
            }
            std::cerr << "Usage: " << argv[0] << " -p <port> -q <queue_length> -d <database_file>" << std::endl;
            return 1;
        }
    }

    try {
        // Запуск сервера с заданными параметрами
        std::cout << "Server started on port: " << port << std::endl;
        Server server(port, qlen, dbFile);
        server.get_base(dbFile);
        server.startListening(server);
    } catch (const std::exception &e) {
        // Обработка исключений, возникающих при запуске сервера
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0; // Возвращаем успешный статус завершения
}
