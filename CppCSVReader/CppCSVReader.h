#pragma once
#include "pch.h"

namespace csv
{
	union SerializedData {
		char* s_data;
		double d_data;
	};

	// Todo: Implement CSVColumn class
	class CSVColumn {
	private:
		void Serialize(const std::string& data);
	public:
		SerializedData data;
		bool is_str;
		CSVColumn(const std::string& col_data);
	};

	class CSVRow {
		// contains CSVColumn objects [heap]
	private:
		void SplitIntoColumns(const std::string& str, const char& delimiter);

	public:
		std::vector<CSVColumn> csvColumns;
		std::string row_str_data;
		CSVRow() {};
		CSVRow(const std::string& row, const char& delimiter);
	};

	class CSVReader {
		// contains CSVRow objects [heap]
	private:
		char m_delim;

	public:
		std::vector<CSVRow> csvRows;
		CSVRow headers;
		CSVReader() {};
		CSVReader(std::ifstream& file, const char delimiter);
	};
}
std::ostream& operator <<(std::ostream& os, csv::CSVColumn col);