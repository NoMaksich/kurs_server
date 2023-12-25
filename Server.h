/**
 * @file Server.h
 * @author Метальников М.А.
 * @version 1.0
 * @date 22.12.2023
 * @brief Модуль для прослушки сокета, чтения БД, аутентификации и вычислений
 */
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUFLEN 1024

/**
 * @brief Модуль для прослушки сокета, чтения БД, аутентификации и вычислений.
 */
class Server {
public:
    /**
     * @brief Конструктор сервера.
     *
     * @param port Порт, на котором будет работать сервер.
     * @param qlen Длина очереди подключений.
     * @param db Путь к файлу базы данных.
     */
    Server(unsigned short port, int qlen, const std::string& db);

    /**
     * @brief Метод для получения данных из базы.
     *
     * @param db_file Путь к файлу базы данных.
     */
    void get_base(const std::string& db_file);

    /**
     * @brief Метод аутентификации пользователя.
     *
     * @param work_sock Сокет для работы с пользователем.
     * @param credentials Список учетных данных пользователя.
     * @return Возвращает true, если аутентификация прошла успешно.
     */
    bool authentication(int work_sock, const std::unordered_map<std::string, std::string>& credentials);

    /**
     * @brief Метод для выполнения операции квадрата числа.
     *
     * @param work_sock Сокет для работы с пользователем.
     * @return Возвращает результат операции квадрата числа.
     */
    float quad(int work_sock);

    /**
     * @brief Метод для чтения строки из сокета.
     *
     * @param work_sock Сокет для работы с пользователем.
     * @return Возвращает строку, прочитанную из сокета.
     */
    std::string str_read(int work_sock);

    /**
     * @brief Деструктор сервера.
     */
    ~Server();

    /**
     * @brief Метод для запуска прослушивания подключений.
     *
     * @param server Сервер, который будет прослушивать подключения.
     */
    void startListening(Server& server);

    std::unordered_map<std::string, std::string> userCredentials; /**< Список учетных данных пользователей. */

private:
    std::string db_file; /**< Путь к файлу базы данных. */
    int work_sock; /**< Сокет для работы с пользователем. */
    int sock; /**< Сокет сервера. */
    std::unique_ptr<sockaddr_in> self_addr; /**< Указатель на структуру с адресом сервера. */
    std::unique_ptr<sockaddr_in> foreign_addr; /**< Указатель на структуру с адресом клиента. */
    int queueLen; /**< Длина очереди подключений. */

    /**
     * @brief Оператор () для обработки подключений.
     *
     * @param sock Сокет для работы с пользователем.
     */
    void operator()(int sock);
};
