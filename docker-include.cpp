#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdarg>

#include "err.hpp"

using std::ifstream;
using std::string;
using std::istringstream;

string filenam;
string stdin4doc;
string line;
int lineNum;

inline int strAppendLine() {
  stdin4doc += line;
  stdin4doc.push_back('\n');

  return 0;
}

int strAppendFile(const string& incFilenam) {
  ifstream file(incFilenam.c_str());
  die(2,
      file.good(),
      "Cannot read INCLUDE file %s:%d %s\n",
      filenam.c_str(),
      lineNum,
      incFilenam.c_str());

  while (getline(file, line)) {
    strAppendLine();
  }

  return 0;
}

int main(int, const char** argv) {
  ++argv;
  die(3, *argv, "%s\n", "No args specified");

  filenam = *argv;

  ifstream file(filenam.c_str());
  die(1, file.good(), "Cannot read file %s\n", filenam.c_str());

  for (lineNum = 1; getline(file, line); ++lineNum) {
    istringstream iss(line);
    string word;

    iss >> word;
    if (word == "INCLUDE") {
      die(4,
          (iss >> word),
          "No INCLUDE file specified %s:%d\n",
          filenam.c_str(),
          lineNum);

      strAppendFile(word);
    }

    strAppendLine();
  }

  printf("%s", stdin4doc.c_str());

  return 0;
}

