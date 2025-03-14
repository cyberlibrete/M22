#include <iostream>
#include <string>
#include <map>
#include <vector>

namespace kernel
{
	bool is_phone(const std::string& value)
	{
		__int8 _digits = 0, _delimiter = 0;

		int idx = 0;
		while(idx < value.length())
		{
			if (value[idx] >= '0' && value[idx] <= '9')
				_digits++;
			else if (value[idx] == '-' || value[idx] == '_')
				_delimiter++;
			else
				return false;
			idx++;
		}

		return _digits > _delimiter;
	}

	enum str
	{
		nothing		= 0,
		spc_left	= 1 << 0,
		spc_right	= 1 << 1,
		spc_into	= 1 << 2,
		all_spcs	= spc_left | spc_into | spc_right,
		spec_line	= 1 << 4

	};

	bool format_str(std::string& value, __int8 _settings)
	{
		int idx = 0, _idx = 0;

		if (_settings & str::spc_left)
		{
			while (idx < value.length() && value[idx] == ' ')
				idx++;
			
			while ((_idx + idx) < value.length())
			{
				value[_idx] = value[_idx+idx];
				_idx++;
			}
		}
		value.resize(value.length() - idx);
		if (_settings & str::spc_into)
		{
			int _shift = 0;
			_idx = 0;

			while (_idx < value.length())
			{
				while (_idx > 0 && value[_idx] == ' ' && value[_idx - 1] == ' ')
					_idx++;
				
				if (_shift != _idx)
					value[_shift] = value[_idx];
				
				_shift++;
				_idx++;
			}
			idx = _idx - _shift;
			_shift = 0;
		}
		value.resize(value.length() - idx);
		
		if (_settings & str::spc_right)
		{
			_idx = value.length() - 1, idx = 0;

			while (value[_idx] == ' ')
			{
				_idx--;
				idx++;
			}
		}

		value.resize(value.length() - idx);
		//std::cout << '|' << value << '|' << std::endl;
		idx = 0, _idx = 0;
		return true;
	}

	bool split_str(std::string& value, std::string _delimiter, std::vector<std::string>& output, __int8 _settings = str::nothing)
	{
		std::string word;

		int idx = 0, _idx = 0;
		while (idx < value.length())
		{
			_idx = 0;
			bool is_delimiter = true;
			while (_idx < _delimiter.length())
			{
				if (value[idx + _idx] != _delimiter[_idx])
				{
					is_delimiter = false;
					break;
				}
				_idx++;
			}

			if (is_delimiter)
			{
				if (_settings & ~str::nothing)
					format_str(word, _settings);
				
				output.push_back(word);
				word.clear();
				idx = idx + _delimiter.length();
			}
			else
			{
				word += value[idx];
				idx++;
			}
		}

		if (_settings & ~str::nothing)
			format_str(word, _settings);

		output.push_back(word);
		word.clear();

		idx = 0, _idx = 0;

		return true;
	}
}

int main()
{
	std::cout	<< "MODULE 22 | Task 01" << std::endl
				<< "Telephone Directory" << std::endl
				<< "-------------------" << std::endl << std::endl;


	std::map<std::string, std::vector<std::string>> phone_dir;
	std::vector<std::string> req_phone_dir;
	std::string __cmd;


	while ((std::cout << "> ") && std::getline(std::cin, __cmd))
	{
		if (__cmd == "stop" || __cmd == "exit")
			return 0;
		else if (__cmd == "help")
		{
			std::cout	<< "available commands:" << std::endl
						<< "stop, exit - end and exit the program (data is not saved)" << std::endl << std::endl
						<< "[last name] [number], [last name] [number] - record the number in the phone book" << std::endl
						<< "[last name] - request all phone numbers by last name" << std::endl
						<< "[number] - request last name for this phone number" << std::endl << std::endl;
			continue;
		}
		
		
		req_phone_dir.clear();
		
		kernel::split_str(__cmd, " ", req_phone_dir, kernel::str::all_spcs);

		if (req_phone_dir.size() == 1 && phone_dir.count(req_phone_dir[0]) > 0)
		{
			int idx = 0;
			while (idx < phone_dir[req_phone_dir[0]].size())
			{
				std::cout << phone_dir[req_phone_dir[0]][idx] << std::endl;
				idx++;
			}
		}
		else if (req_phone_dir.size() == 1 && phone_dir.count(req_phone_dir[0]) == 0)
		{
			std::cerr << "There's no such " << (kernel::is_phone(req_phone_dir[0])? "phone number" : "name") << " in the notebook" << std::endl;
		}
		else if (req_phone_dir.size() == 2)
		{
			if ((kernel::is_phone(req_phone_dir[0]) && !kernel::is_phone(req_phone_dir[1]))
				|| (!kernel::is_phone(req_phone_dir[0]) && kernel::is_phone(req_phone_dir[1])))
			{
				phone_dir[req_phone_dir[0]].push_back(req_phone_dir[1]);
				phone_dir[req_phone_dir[1]].push_back(req_phone_dir[0]);
			}
		}
		else
		{
			std::cerr << "ERROR!" << std::endl;
		}
		__cmd.clear();
	}

	return 0;
}