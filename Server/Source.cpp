#include <iostream>
#include "DatabaseServer.h"
#include "MasterStorage.h"
#include "QueryIntepreter.h"
#include "Storage.h"
#include "StudentEntity.h"
#define DEBUG	
using guid = Storage::guid;
void AddTestStudents(MasterStorage& storage);

int main() {
    std::string storagePath;
    std::string isTrue;
    std::cout << "Student database S5 Server starting.\n";
    std::cout << "Enter folder path, that will be used for storage : ";
    std::cin >> storagePath;
    std::cout << "\nConfirm choise? (yes/no) : ";
    std::cin >> isTrue;
    while (isTrue != "yes") {
		std::cout << "\nChoise was not confirmed";
        std::cout << "\nEnter new folder path, that will be used for storage : ";
        std::cin >> storagePath;
        std::cout << "\nAre you sure? (yes/no) : ";
        std::cin >> isTrue;
    }
#ifndef DEBUG
    try {
#endif
        boost::asio::io_context io_context;
		MasterStorage storage(storagePath);
		AddTestStudents(storage);
		const short port = 12345;

		TcpServer server(io_context, port, &storage);
		std::cout << "\n - Database server started\n";

		std::vector<std::thread> threads;
		unsigned int thread_count = std::thread::hardware_concurrency();
		for (unsigned int i = 0; i < thread_count; ++i) {
			threads.emplace_back([&io_context]() { io_context.run(); });
		}
		
	
		for (auto& thread : threads) {
			thread.join();
		}
#ifndef DEBUG
    } catch (const std::exception& ex) {
        std::cout << "Exception: " << ex.what() << "\n";
    }
    return 0;
#endif 
}

void AddTestStudents(MasterStorage& storage) 
{
	StudentEntity s1("Ivanov", 201, 42, "Extra info 1");
	StudentEntity s2("Ivleev", 202, 5.4, "Extra info 2");
	StudentEntity s3("Ivshin", 203, 314.12, "Extra info 3");
	StudentEntity s4("Petrov", 204, 2, "Extra info 4");
	StudentEntity s5("Sidorov", 201, 3, "Extra info 5");
	StudentEntity s6("Jew", 205, 4, "Extra info 6");
	StudentEntity s7("Ivtan", 202, 5, "Extra info 7");
	
	storage.insert(s1);
	storage.insert(s2);
	storage.insert(s3);
	storage.insert(s4);
	storage.insert(s5);
	storage.insert(s6);
	storage.insert(s7);
}
/*






*/







