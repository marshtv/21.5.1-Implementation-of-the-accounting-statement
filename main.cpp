#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct recipient {
	std::string first_name = "unknown_first_name";
	std::string last_name = "unknown_last_name";
	std::string date = "01.01.2022";
	long long money = 0;
	std::string currency = "RUB";
};

void add_to_statement_file(std::ofstream& file, recipient& person) {
	file << person.first_name << " "
		<< person.last_name << " "
		<< person.date << " "
		<< person.money << " "
		<< person.currency << std::endl;
}

int main() {
	recipient person;
	std::string command;
	std::cout << "Input command (add/list):" << std::endl;
	std::cin >> command;
	if (command == "add") {
		std::ofstream statement_file("statement.txt", std::ios::app);
		std::cout << "First name:";
		std::cin >> person.first_name;
		std::cout << "Last name:";
		std::cin >> person.last_name;
		std::cout << "Date (DD.MM.YYYY):";
		std::cin >> person.date;
		std::cout << "Payment:";
		std::cin >> person.money;
		std::cout << "Currency:";
		std::cin >> person.currency;

		add_to_statement_file(statement_file, person);
		statement_file.close();
	} else if (command == "list") {
		std::ifstream statement_file("statement.txt");
		if (statement_file.is_open()) {
			while (!statement_file.eof()) {
				long long pos;
				pos = statement_file.tellg();
				std::string temp_name;
				statement_file >> temp_name;
				if (temp_name.empty())
					break;
				statement_file.seekg(pos);
				statement_file >> person.first_name >> person.last_name >> person.date
								>> person.money >> person.currency;
				std::cout << person.first_name << " " << person.last_name << " "
						  << person.date << " " << person.money << " "
						  << person.currency << std::endl;
			}
		} else {
			std::cout << "ERROR. File not available." << std::endl;
		}
	} else {
		std::cout << "Incorrect command!" << std::endl;
	}
}
