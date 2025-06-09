#include <iostream>
#include <fstream>
#include <string>

void	error_msg()
{
	std::cout << "Error: Wrong Number of Arguments" << std::endl;
	std::cout << "./main <filename> <string 1(s1)> <string 2(s2)>" << std::endl;
}

void	replace_text(std::ifstream &MyFile, char **argv)
{
	std::string	to_find;
	std::string	to_replace;
	std::string	content_str;
	std::string	final_str;
	std::string	file_name;
	std::string	rep_file_name;
	std::size_t	pos_idx;

	file_name = argv[1];
	to_find = argv[2];
	to_replace = argv[3];
	rep_file_name = file_name + ".replace";
	std::ofstream rep_file(rep_file_name.c_str());
	while (!MyFile.eof() && to_find.size())
	{
		final_str = "";
		std::getline(MyFile, content_str);
		pos_idx = content_str.find(to_find);
		while (pos_idx != std::string::npos)
		{
			content_str.erase(pos_idx, to_find.size());
			final_str = final_str + content_str.substr(0, pos_idx);
			final_str = final_str + to_replace;
			content_str = content_str.substr(pos_idx);
			pos_idx = content_str.find(to_find);
		}
		if (content_str.size() && pos_idx == std::string::npos)
			final_str = final_str + content_str.substr(0, pos_idx);
		rep_file << final_str;
		if (!MyFile.eof())
			rep_file << "\n";
	}
	MyFile.close();
	rep_file.close();
}

int main(int argc, char **argv)
{
	if (argc == 4)
	{		
		std::ifstream MyFile(argv[1]);
		if (MyFile)
		{
			if (MyFile.is_open())
				replace_text(MyFile, argv);
			else
				std::cout << "File not opened" << std::endl;
		}
		else
			std::cout << "File does not exist" << std::endl;
	}
	else
		error_msg();
}