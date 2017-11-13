
/*
	VirusTotal Checker V1311
	API PUBLIC
*/

#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>

// For network lib
#include <wininet.h>
#pragma comment(lib,"wininet.lib")

#include "hex.h"
#include "network.h"
#include "file.h"
#include "result_read.h"

int main()
{

	/*
	Config file 

	@API-KEY@ API_KEY_HERE_!

	// List Hash file, one per line.
	8f2d08ab9240bba1c333ba04d7cead759fc9cf11fd0d19eb5d73952d763eb545
	807fcbd8d37af9a30f17ef14e720bd73
	f07b47c010037f984d425affc3bb3aaf15203a51
	10d2b418a5c029404e5093b95acd975a9380578a9ad886e7d14be3cc4124b66d
	*/

	// CONFIG PATH
	std::string config_file = "config.txt";

	FILE * fConfig = fopen(config_file.c_str(), "r");

	if(fConfig == NULL)
	{
		std::cout << "config.txt not found!\n";
		return 1;
	}

	std::string API_VirusTotal = get_key_api(config_file); // Get API Key from config file
	std::cout << "\nAPI KEY: " << API_VirusTotal << "\n";
	char line_r[255] = {0};
	int n_line = 0;
	std::string str_line = "";
	
	int n_request_api = 0; // With API Public = 4 requests / minute

	while(fgets(line_r,255,fConfig))
	{
		n_line++;
		str_line = line_r;
		if (str_line.size () > 0)
			str_line.resize(str_line.size () - 1);
		if(n_line > 3)
		{
			n_request_api++;
			std::cout << "\nHASH SEARCH: " << str_line << "\n";
			aff_result(virustotal_check_hash(API_VirusTotal, str_line));
			if(n_request_api >= 4)
			{
				std::cout << "\nSleep 1 minute for API public\n";
				Sleep(60000); // 1 minutes
				n_request_api = 0; // Reset counter
			}

		}

		memset(line_r, 0, sizeof(line_r));
	}

	fclose(fConfig);

	std::cout << "\n\n" << std::endl;
	system("PAUSE");
	return 0;
}