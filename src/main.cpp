#include <iostream>
#include <string>
#include <getopt.h>
#include "algorithms/kmp.h"
#include <fstream>
#include <set>
#include <map>
#include <queue>
#include <vector>

const char* const short_opts = "tce:p:a:h";
const option long_opts[] = {
    {"help", no_argument, nullptr, 'h'},
    {"count", no_argument, nullptr, 'c'},
    {"edit", required_argument, nullptr, 'e'},
    {"pattern", required_argument, nullptr, 'p'},
    {"algorithm", required_argument, nullptr, 'a'},
};

using namespace std;

string pattern_file_path = "";
vector<string> pattern_list;
vector<string> files_list;

ifstream* file = NULL;
string cur_filename = "";
string algorithm = "";
string buffer;

bool help = false;
bool line = true;
bool dist = false;
bool only_count = false;

int err = 0;

int parse_args(int argc, char* argv[]) {
  int opt = 0;
  while(opt != -1) {
    opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
    switch(opt) {
      case 'c':
        only_count = true;
        break;
      case 'e':
        err = stoi(optarg);
        break;
      case 'p':
        pattern_file_path = string(optarg);
        break;
      case 'a':
        algorithm = string(optarg);
        break;
      case -1:
        break;
      default:
        help = true;
        return 1;
    }
  }

  if (argc <= 1) {
    cerr << "Missing arguments, printing help details" << endl;
    help = true;
    return 1;
  }

  int ind = optind;
  if(pattern_file_path.size() > 0) {
    string pattern;
    ifstream* pattern_file = new ifstream();
    pattern_file->open(pattern_file_path);
    if(!pattern_file->is_open()){
      cerr << "Pattern file were unable to be opened" << endl;
      return -1;
    }
    while(!pattern_file->eof()) {
      getline(*pattern_file, pattern);
      pattern_list.push_back(pattern);
      if(pattern.length() <= err) {
        cerr << "Edit distance should be less then pattern size" << endl;
        return -1;
      }
    }
    pattern_file->close();
  } else if (ind != argc) {
    string pattern = string(argv[ind++]);
    pattern_list.push_back(pattern);
    if(pattern.length() <= err) {
      cerr << "Edit distance should be less then pattern size" << endl;
      return -1;
    }
  }

  while(ind < argc) {
    files_list.push_back(string(argv[ind++]));
  }

  return 0;
}

int main(int argc, char* argv[]) {
  parse_args(argc, argv);
  if(help) {
    cout << "Usage: pmt [options] pattern textfile [textfile...]"<<endl;
    cout << "Options:"<<endl;
    cout << "  -a, --algorithm ALGORITHM     Set the algorithm to be used(options are )"<<endl;
    cout << "  -p, --pattern PATTERN_FILE    Grabs the patterns given in a file, when this option is passed, the pattern parameter should not be passed."<<endl;
    cout << "  -c, --count                   Displays only the number of occurences for each pattern"<<endl;
    cout << "  -e, --edit DISTANCE           Finds all approximate occurrences of the pattern within the given editing distance, will be ignored if non appliable in given algorithm"<<endl;
    cout << "  -h, --help                    Shows the guide"<<endl;
    return 0;
  }

  int occ = 0;

  for(auto file_name: files_list) {
    string line = "a";
    int line_count = 1;

    file = new ifstream();
    file->open(file_name);
    if(!file->is_open()) {
      cerr << "File '" << file_name << "' not found or could not be opened." << endl;
      return 0;
    }

    while(!file->eof()) {
      getline(*file, line);
      bool found_oc = 0;
      for(auto pat: pattern_list) {
        vector<int> line_ocs = kmpMatchPattern(line, pat);
        if(line_ocs.size() > 0) {
          if (!only_count) {
            cout << file_name << " " << line_count << line <<endl;
          }
          occ++;
          break;
        }
      }
      line_count++;
    }
  }
  cout<< "Total occurrences: " << occ <<endl;
}
