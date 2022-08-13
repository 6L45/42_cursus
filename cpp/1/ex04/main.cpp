#include <iostream>
#include <fstream>
#include <string>

void	send_out(std::string file_content, std::string file_name)
{
	std::string dest;

	dest = file_name;
	dest.append(".replace");
	std::ofstream outfile (dest, std::ios::out);
	outfile << file_content;
	outfile.close();
}

std::string	replace(std::string file_content, std::string trigger, std::string swap)
{
	long int	pos;
	std::string	base;
	std::string	res;

	res = file_content;
	while ((pos = res.find(trigger)) > 0)
	{
		base = res.substr(0, pos);
		base += swap;
		base += res.substr(pos + trigger.length());
		res = base;
	}
	return (res);
}

int	main(int argc, char **argv)
{
	if (argc != 4)
		return (0);
	if (!argv[1][0] || !argv[2][0] || !argv[3][0])
		return (0);

	std::string file(argv[1]);
	std::string s1(argv[2]);
	std::string s2(argv[3]);
	
	std::string file_content;
	std::string line;
	std::fstream file_stream;

	file_stream.open(file, std::ios::in);
	if (file_stream.is_open())
	{
		while (getline(file_stream, line))
			file_content += line + "\n";
		file_stream.close();
	}
	else
	{
		std::cout << "Error : File" << std::endl;
		return (1);
	}
	file_content = replace(file_content, s1, s2);
	send_out(file_content, file);	
	return (0);
}
