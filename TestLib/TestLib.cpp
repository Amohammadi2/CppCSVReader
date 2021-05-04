#include "CppCSVReader.h"

int main()
{
	std::ifstream input_file("Students.csv");
	csv::CSVReader reader(input_file, ',');

	for (const auto& header: reader.headers.csvColumns) {
		std::cout << header << "|";
	}

	std::cout << "-----------------------------------------" << std::endl;

	for (const auto& row : reader.csvRows) {
		for (const auto& col : row.csvColumns) {
			std::cout << col << "|";
		}
		std::cout << std::endl;
	}
}