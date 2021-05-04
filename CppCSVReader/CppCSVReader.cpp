// CppCSVReader.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "CppCSVReader.h"

csv::CSVReader::CSVReader(std::ifstream& file, const char delimiter)
{
	m_delim = delimiter;
	std::string row;
	bool first_iteration = 1;

	while (std::getline(file, row)) {

		if (first_iteration) {
			headers = csv::CSVRow(row, delimiter);
			first_iteration = 0;
			continue;
		}

		csvRows.push_back({ row, delimiter });
	}
}

void csv::CSVRow::SplitIntoColumns(const std::string & str, const char& delimiter)
{
	int delimiter_pos = 0;
	int search_pos = 0;
	do {
		delimiter_pos = str.find_first_of(',', delimiter_pos + 1);
		std::string token;
		if (delimiter_pos == std::string::npos) {
			token = str.substr(search_pos, str.size());
			csvColumns.push_back({ token });
			break;
		}
		token = str.substr(search_pos, delimiter_pos - search_pos);
		search_pos = delimiter_pos + 1;
		csvColumns.push_back({ token });
	} while (1);
}

csv::CSVRow::CSVRow(const std::string& row, const char& delimiter)
{
	SplitIntoColumns(row, delimiter);
}


std::ostream & operator<<(std::ostream & os, csv::CSVColumn col)
{
	if (col.is_str) std::cout << col.data.s_data;
	else			std::cout << col.data.d_data;

	return os;
}

void csv::CSVColumn::Serialize(const std::string& data)
{
	// if it is a string, store it as a string
	if (data.find_first_not_of("0123456789.-") != std::string::npos) {
		size_t len = data.size() + 1;
		this->data.s_data = new char[len];
		memcpy(this->data.s_data, data.c_str(), sizeof(char) * len);
		is_str = 1;
		return;
	}

	// otherwise store it as a number
	std::stringstream s_stream(data);
	double a;
	s_stream >> a;
	this->data.d_data = a;
	is_str = 0;
}

csv::CSVColumn::CSVColumn(const std::string& col_data)
{
	Serialize(col_data);
}