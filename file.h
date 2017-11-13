
std::string delimiter_string(std::string str_raw, std::string str_del)
{
	std::string str_found = "NOFOUND_DS";
	try
	{
		int strlenght = strlen(str_del.c_str()) + 1;
		std::size_t pos = str_raw.find(str_del.c_str()) + strlenght;
		std::string str3 = str_raw.substr (pos);
		std::stringstream scommandes;
		scommandes.str(str3);

		scommandes >> str_found;
	}

	catch(const std::out_of_range& oor){}

	return str_found;
}

std::string delimiter_string_M(std::string str_raw, std::string str_del)
{
	std::string str_found = "NOFOUND_DS";
	std::string str_found2 = "NOFOUND_DS";
	try
	{
		int strlenght = strlen(str_del.c_str()) + 1;
		std::size_t pos = str_raw.find(str_del.c_str()) + strlenght;
		std::string str3 = str_raw.substr (pos);
		std::stringstream scommandes;
		scommandes.str(str3);

		scommandes >> str_found >> str_found2;
	}

	catch(const std::out_of_range& oor){}

	return str_found + " " + str_found2;
}

std::string RemoveChar(std::string str, char c) 
{
   std::string result;
   for (size_t i = 0; i < str.size(); i++) 
   {
          char currentChar = str[i];
          if (currentChar != c)
              result += currentChar;
   }
       return result;
}

std::string save_log(std::string raw)
{
	char bdir[255];
	GetCurrentDirectoryA(255, bdir);
	CreateDirectoryA("\Logs_VirusTotal_Checker", 0);

	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	Sleep(1000); // For Secure
	char btime[80];
	strftime(btime, 80, "%d_%m_%y_%HH%MM%S", timeinfo);

	std::string date_time = btime;
	std::string path_file = "\Logs_VirusTotal_Checker" + std::string("\\") + date_time;
	FILE * log = fopen(path_file.c_str(), "a+");

	if(log != NULL)
	{
		fputs(raw.c_str(), log);
		fclose(log);
	}

	else
		return "ERROR";

	return bdir + std::string("\\") + path_file;
}

std::string get_key_api(std::string path_config)
{
	FILE * fConfig = fopen(path_config.c_str(), "r");

	char b_read[128];
	std::string all_file = "";

	if(fConfig != NULL)
	{
		while(fread(b_read,1,128,fConfig))
			all_file += b_read;

		fclose(fConfig);
	}
	else
		return "Error Config File";

	return delimiter_string(all_file, "@API-KEY@");
}