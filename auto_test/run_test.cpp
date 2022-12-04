#include <fstream>
#include <ctime>
#include <vector>
#include <stdexcept>
using namespace std;

#define TEST
#include "main.cpp"

// user configuration
const bool USE_STRICTLY_JUDGE = false;
const string USER_OUTPUT_FILE_NAME = "output_temporary.out";
const size_t FILE_ID_LENGTH = 2;
const string TEST_FILE_PREFIX = "test_case"; // file_name = TEST_FILE_PREFIX[i] + "_{integer}" e.g. "test_case_01"
const size_t MAX_TEST_CASE_COUNT = 25;


using FileIO = IO<ifstream, ofstream>; 
void run_test(ifstream &ifile, ofstream &ofile) { Solver<FileIO>(FileIO(ifile, ofile)); }

string file_id(int x) {
  string s = to_string(x); 
  if(s.size() > FILE_ID_LENGTH) throw runtime_error("File id length must greater than real file id length.");
  while(s.size() < FILE_ID_LENGTH) {
    s = "0" + s;
  }
  return s;
}

string read_all(ifstream &is) {
  string s, ret;
  while(!is.eof()) getline(is, s), ret += s;
  return ret;
}

void strip(string &s) {
  if(s.empty()) return;
  while(s.front() == '\n' || s.front() == ' ' || s.front() == '\t') s.erase(s.begin());
  while(s.back() == '\n' || s.back() == ' ' || s.back() == '\t') s.pop_back();
}

int main() {
  ifstream ifs;
  ofstream ofs;

  vector<double> execution_times;
  vector<string> user_outputs;
  
  cout << fixed;

  // run tests
  for(int _test_case = 0; _test_case < MAX_TEST_CASE_COUNT; ++_test_case) {
    string file_name_prefix = TEST_FILE_PREFIX;
    string test_case = file_id(_test_case + 1);
    string ifile_name = file_name_prefix + "_" + test_case + ".in";
    string ofile_name = USER_OUTPUT_FILE_NAME;

    ifs.open(ifile_name), ofs.open(ofile_name);

    if(!(ifs.is_open() && ofs.is_open())) {
      if(_test_case == 0) throw runtime_error("Error while opening test data file.");
      else break;
    }

    // caculate execution time
    clock_t start, end;

    start = clock();
    run_test(ifs, ofs);
    end = clock();

    ifs.close(), ofs.close();

    execution_times.push_back((double)(end - start) / CLOCKS_PER_SEC);


    // get user output
    ifs.open(USER_OUTPUT_FILE_NAME);
    user_outputs.push_back(read_all(ifs));
    ifs.close();
  }

  // print and check result
  for(int _test_case = 0; _test_case < user_outputs.size(); ++_test_case) {
    string file_name_prefix = TEST_FILE_PREFIX;
    string test_case = file_id(_test_case + 1);
    string correct_output, user_output;
    double execution_time = execution_times[_test_case];
    bool accept;

    ifs.open(file_name_prefix + "_" + test_case + ".out");
    correct_output = read_all(ifs);
    ifs.close();

    user_output = user_outputs[_test_case];

    // judging
    if(!USE_STRICTLY_JUDGE) {
      strip(correct_output);
      strip(user_output);
    }

    accept = (correct_output == user_output);

    // print result
    cout << "Case #" << test_case << ": ";
    if(accept) {
      cout << "[V]\n";
      cout << "  Result: AC\n";
      cout << "  Time: " << setprecision(2) << execution_time << '\n';
    } else {
      cout << "[X]\n";
      cout << "  Result: WA\n";
      cout << "  Time: " << setprecision(2) << execution_time << '\n';
      cout << "  User Output: \n";
      cout << "  -----\n";
      cout << "  " << user_output << '\n';
      cout << "  -----\n";
      cout << "  Correct Output: \n";
      cout << "  -----\n";
      cout << "  " << correct_output << '\n';
      cout << "  -----\n";
    }
    cout << "\n\n";
  }
}
