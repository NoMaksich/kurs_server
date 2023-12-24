/**
 * @file ErrorLog.h
 * @author Метальников М.А.
 * @version 1.0
 * @date 22.12.2023
 * @brief Модуль обработки ошибок для сервера
 */
#pragma once
#include <iostream>
#include <string>

/**
 * @brief Модуль для работы с логированием ошибок.
 */
class ErrorLog {
public:
    /**
     * @brief Записывает ошибку в лог-файл.
     *
     * @param critical Флаг, указывающий на критичность ошибки.
     * @param errorMessage Сообщение об ошибке.
     */
    static void logError(bool critical, const std::string& errorMessage);
};
