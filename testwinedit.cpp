
#include <iostream>
#include <string>

#ifdef _MSC_VER
#include "editline/readline.h"
#else
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include "vt_text_format.h"

#ifdef _WIN32
#include <windows.h>
bool open_console() {
  static bool console_not_opened=true;

  if (console_not_opened) {
    SetConsoleOutputCP(CP_UTF8);
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE) return false;
    DWORD dwMode=0;

    if (!GetConsoleMode(hOut, &dwMode)) return false;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    console_not_opened=false;
  }

  return true;
}
#else
bool open_console() { return true; }
#endif

// See https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
std::string vt_txt(unsigned int n) {
  return "\033["+std::to_string(n)+"m";
}

bool rdlnpp(std::string prompt, std::string& line) {
  char *_line=readline(prompt.c_str());
  if (_line) {
    line=_line;
    return true;
  }

  return false;
}

int main(int, char **)
{
  std::string line;
  int idx=1;
  open_console();
  std::cout << "Type exit/quit/x/q to quit."  << std::endl;
  while (rdlnpp("prompt "+std::to_string(idx)+">", line)) {
    if (line == "exit" || line == "quit" || line == "q" || line == "x") break;

    if (!line.empty()) {
      if (line.size() == 1 && (int)line[0] == 26) {
        std::cout << (int)line[0] << std::endl;
        break;
      } else {
        std::cout << vt_txt(VT_Green)+vt_txt(VT_Bold)+vt_txt(VT_Italic);
        std::system(line.c_str());
        std::cout << vt_txt(VT_Reset); //Reset
        add_history((char *)line.c_str());
        idx++;
      }
    }
  }
  
  return 0;
}
