#include "site_arranger.h"
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <memory>
#include <mutex>

vector<UpdateInfo> SiteArranger::updates_{};

void SiteArranger::ReadData(const string& path) {
	vector<string> vec_lines;
	string line;
	ifstream node_file(path);
	for (int i = 0; i < 100000; i++) {
		getline(node_file, line);
		vec_lines.push_back(line);
	}
	cout << "end reading" << vec_lines.size() << endl;
	node_file.close();

	updates_.clear();
	updates_.reserve(100000);
	regex reg_node("([0-9]*)[\\t\\s]+([0-9]*\\.?[0-9]+)[\\t\\s]+([0-9]*\\.?[0-9]+)");
	smatch m;
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 1000; j++) {
			if (regex_search(vec_lines[i * 1000 + j].cbegin(), vec_lines[i * 1000 + j].cend(), m, reg_node)) {
				updates_.push_back({ stoi(m.str(1)), (int)stof(m.str(2)) * 100, (int)stof(m.str(3)) * 100, (int)i });
			}
		}
		cout << "." << updates_.size() << endl;
	}

	cout << endl << updates_.size();
}
