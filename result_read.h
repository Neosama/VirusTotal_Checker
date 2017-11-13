
int aff_result(std::string raw)
{
	std::string detection_pos = delimiter_string(raw, "\"positives\":");
	detection_pos = RemoveChar(detection_pos, ',');

	std::string scan_total = delimiter_string(raw, "\"total\":");
	scan_total = RemoveChar(scan_total, ',');

	std::string scan_date = delimiter_string_M(raw, "\"scan_date\":");
	scan_date = RemoveChar(scan_date, ',');
	scan_date = RemoveChar(scan_date, '\"');

	std::string md5_file = delimiter_string(raw, "\"md5\":");
	md5_file = RemoveChar(md5_file, ',');
	md5_file = RemoveChar(md5_file, '\"');
	md5_file = RemoveChar(md5_file, '}');
	
	if(raw.find("Scan finished") != std::string::npos)
	{
		std::cout << "=========================================\n";
		std::cout << "Last scan:  " << scan_date << "\n";
		std::cout << "MD5:        " << md5_file << "\n";
		std::cout << "Detections: " << detection_pos << "/" << scan_total << "\n";
		std::cout << "Log:        " << save_log(raw) << "\n";
		std::cout << "=========================================\n";
	}


	return 0;
}