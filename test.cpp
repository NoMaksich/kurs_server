#include <UnitTest++/UnitTest++.h>
#include <string>
#include <fstream>
#include "Server.h"
#include "ErrorLog.h"
#include <regex>

SUITE(ServerTests)
{
    TEST(ConstructorValidArguments) {
        unsigned short port = 8080;
        int qlen = 5;
        std::string db = "test_db.txt";

        Server server(port, qlen, db);
        CHECK(true);
    }
    TEST(ConstructorSmallValidArguments) {
        unsigned short port = 1;
        int qlen = 5;
        std::string db = "test_db.txt";

        try {
            Server server(port, qlen, db);
            CHECK(false);
        } catch (const std::system_error& e) {
            CHECK(std::string(e.what()) == "Socket error: Permission denied");
        }

    }
    TEST(ConstructorBigValidArguments) {
        unsigned short port = 65537;
        int qlen = 5;
        std::string db = "test_db.txt";

        CHECK_THROW({
            Server server(port, qlen, db);
        }, std::system_error);
    }
    TEST(GetBaseValidFile) {
        unsigned short port = 8080;
        int qlen = 5;
        std::string db = "test_db.txt";
        Server server(port, qlen, db);
        server.get_base(db);

        CHECK(!server.userCredentials.empty());
    }
    TEST(DatabaseFileOpenedWithGetBase) {
    unsigned short port = 8080;
    int qlen = 5;
    std::string db_file = "test_db.txt";
    Server server(port,qlen,db_file);

    try {
        server.get_base(db_file);
        CHECK(true);
    } catch (...) {
        CHECK(false);
    }
}
    TEST(GetBaseInvalidFile) {
        unsigned short port = 8080;
        int qlen = 5;
        std::string db = "testiki.txt";
        Server server(port, qlen, db);
        server.get_base(db);

        CHECK(server.userCredentials.empty());
    }
    TEST(ValidUser) {
        unsigned short port = 8080;
        int qlen = 5;
        std::string db = "test_db.txt";
        Server server(port, qlen, db);
        server.get_base(db);

        bool userExists = false;
        for (const auto& user : server.userCredentials) {
            if (user.first == "user") {
                userExists = true;
                break;
            }
        }
        CHECK(userExists);
    }
    TEST(InvalidUser) {
        unsigned short port = 8080;
        int qlen = 5;
        std::string db = "test_db.txt";
        Server server(port, qlen, db);
        server.get_base(db);

        bool userExists = false;
        for (const auto& user : server.userCredentials) {
            if (user.first == "nonexistent_user") {
                userExists = true;
                break;
            }
        }
        CHECK(!userExists);
    }

    TEST(TestLogError) {
        unsigned short port = 1;
        int qlen = 5;
        std::string db = "test_db.txt";
        std::string searchString = "Socket error: Permission denied";
        bool searchStringFound = false;

        try {
            Server server(port, qlen, db);
            CHECK(false);
        } catch (const std::system_error& e) {
            ErrorLog::logError(true, std::string("Socket error: ") + e.what());
            CHECK(true);

            std::ifstream file("/var/log/vcalc.log");
            std::string line;
            while (std::getline(file, line)) {
                if (line.find(searchString) != std::string::npos) {
                    searchStringFound = true;
                    break;
                }
            }
        }

        CHECK(searchStringFound);
    }
    TEST(TestLogFileEndsWithStringWithTime) {
        unsigned short port = 8080;
        int qlen = 5;
        std::string db = "test_db.txt";
        Server server(port, qlen, db);
        server.get_base(db);
        std::string filename = "/var/log/vcalc.log";
        std::string expectedErrorString = "Date and time: .* Critical: Yes Error: Socket error: Socket error: Permission denied";

        std::ifstream file(filename);
        REQUIRE CHECK(file.good());

        // Чтение содержимого файла
        std::stringstream fileContents;
        fileContents << file.rdbuf();
        std::string fileString = fileContents.str();

        // Создание регулярного выражения для поиска строки с ошибкой, включающей время
        std::regex errorRegex(expectedErrorString);
        std::smatch match;

        // Поиск строки с ошибкой в содержимом файла
        if (std::regex_search(fileString, match, errorRegex)) {
            // Если найдено совпадение, строка содержит ожидаемую ошибку с учетом времени
            CHECK(true);
        } else {
            // Если строка с ошибкой не найдена
            CHECK(false); // Неожиданный результат - тест провален
        }
    }
}
int main()
{
    return UnitTest::RunAllTests();
}
