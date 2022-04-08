#include <iostream>
#include <string>
#include <getopt.h>
#include "algorithms/kmp.h"
#include "algorithms/ahoCorasick.h"
#include "algorithms/ukkonen.h"
#include "algorithms/brute.h"
#include "algorithms/wumanber.h"
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

string findBestAlgorithm(vector<string> &pats, int err = 0) {
  if(err) {
    if (err >= 6) {
      return "WuManber";
    }else {
      return "Ukkonen";
    }
  }else {
    if (pats.size() > 1) {
      return "AhoCorasick";
    }else {
      return "KMP";
    }
  }
}

int matchPattern(string line, string alg, int err = 0) {
  if(alg == "BruteForce") {
    return bruteMatchPatternList(line);
  }else if (alg == "KMP") {
    return kmpMatchPattern(line);
  }else if (alg == "Ukkonen") {
    return ukkonenMatchPattern(line);
  }else if (alg == "WuManber") {
    return wumMatchPattern(line, err);
  }else if (alg == "AhoCorasick") {
    return ahoSearch(line);
  }else {
    return wumMatchPattern(line, err);
  }
}

void addPatterns(vector<string> pat_list, string alg, int err = 0) {
  if(alg == "BruteForce") {
    // BruteForce Will ignore error option.
    bruteAddPatternListAndError(pat_list, err);
  }else if (alg == "KMP") {
    // KMP Will ignore error option.
    for (string pat: pat_list) {
      kmpAddPattern(pat);
    }
  }else if (alg == "Ukkonen") {
    ukkClearData();
    for (string pat: pat_list) {
      ukkonenAddPattern(pat, err);
    }
  }else if (alg == "WuManber") {
    for (string pat: pat_list) {
      wumAddPattern(pat, err);
    }
  }else if (alg == "AhoCorasick") {
    // AhoCorasick Will ignore error option.
    ahoClearData();
    for (string pat: pat_list) {
      addPatternAho(pat);
    }
    addFails();
  }else {
    algorithm = findBestAlgorithm(pat_list, err);
    cout<<algorithm<<endl;
    return addPatterns(pat_list, algorithm, err);
  }
}

int searchWithSimplePat(vector<string> files_list, vector<string> pattern_list, string alg) {
  int occ_count = 0;
  addPatterns(pattern_list, alg, err);

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
      int cur_oc = matchPattern(line, algorithm, err);
      if (cur_oc) {
        if (!only_count) {
          cout << file_name << " " << line_count << " " << line <<endl;
        }
        occ_count+=cur_oc;
      }
      line_count++;
    }
  }
  return occ_count;
}

int main(int argc, char* argv[]) {
  parse_args(argc, argv);
  if(help) {
    cout<<"Usage: pmt [options] pattern textfile [textfile...]"<<endl;
    cout<<"Options:"<<endl;
    cout<<"  -a, --algorithm ALGORITHM     Set the algorithm to be used (options are AhoCorasick, BruteForce, KMP, Ukkonen and WuManber)"<<endl;
    cout<<"  -p, --pattern PATTERN_FILE    Grabs multiple patterns at once from a file, when this option is passed, the pattern parameter should not be passed."<<endl;
    cout<<"  -c, --count                   Hides the line results and displays only the total number of occurences"<<endl;
    cout<<"  -e, --edit DISTANCE           Finds all approximate occurrences of the pattern within the given editing distance, will be ignored if non appliable in given algorithm"<<endl;
    cout<<"  -h, --help                    Shows this guide"<<endl;
    return 0;
  }

  int occ = searchWithSimplePat(files_list, pattern_list, algorithm);
  cout<< "Total occurrences: " << occ <<endl;
}
