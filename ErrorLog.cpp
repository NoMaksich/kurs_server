/**
 * @file ErrorLog.cpp
 * @author Метальников М.А.
 * @version 1.0
 * @date 22.12.2023
 * @brief Реализация модуля обработки ошибок для сервера
 */
#include "ErrorLog.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

/**
 * @brief Модуль записи ошибки в лог файл.
 *
 * @param critical Флаг, указывающий на критичность ошибки.
 * @param errorMessage Сообщение об ошибке.
 */
std::string ErrorLog::LogFile = "default_log_file.txt";

void ErrorLog::logError(bool critical, const std::string& errorMessage) {
    std::ofstream logFile(LogFile, std::ios_base::app); // Открываем лог-файл для записи
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        time_t now_c = std::chrono::system_clock::to_time_t(now);
        struct tm* timeinfo = localtime(&now_c);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        // Записываем информацию об ошибке в лог-файл
        logFile << "Date and time: " << buffer << " Critical: " << (critical ? "Yes" : "No") << " Error: " << errorMessage << std::endl;
        logFile.close(); // Закрываем лог-файл после записи
    } else {
        std::cout << "Unable to open log file." << std::endl; // Выводим сообщение об ошибке, если не удалось открыть файл
    }
}
