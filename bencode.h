#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <ctype.h>
#include <windows.h>
#include <shobjidl_core.h>





namespace Bencode
{
	class Exception : public std::runtime_error
	{
	public:
		using runtime_error::runtime_error;

	};

	class Parser
	{

		struct BItem
		{
			enum class Type
			{
				Int,
				String
			} d_type;

			BItem(std::string& str, const int& a)
			{
				if (a == 1)
					d_type = Type::Int;
				else
					d_type = Type::String;
				raw_value = str;
			}

			std::string raw_value;
		};
	public:

		Parser() = default;
		void Print();
		void AddString(const std::string& ref, std::ostream& os = std::cout);
		void GetHash();
		void AddFile(const std::filesystem::path& path);
		void PrintPieces();
	private:
		void Reset();
		void WToFile();
		void ProcessChar(const char& c);
		
		static bool isDigit(const char& c) {
			return std::isdigit(static_cast<unsigned char>(c));
		}
		const std::string& GetTemp() const {
			return temp;
		}
		enum class State {
			ReadyForData,
			Int,
			Length,
			Str,
			List,
			Dict
		};

		int i = 0;
		
		std::vector<BItem> m_items;
		std::string m_string, m_int, m_hash, temp, m_holder;
		State m_state = State::ReadyForData;
	};
}
