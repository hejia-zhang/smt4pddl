#include <cstdio>
#include <fstream>
#include <iostream>

#include <FlexLexer.h>

#include "ptree.h"

extern int yyparse();
extern int yydebug;

using std::ifstream;
using std::ofstream;

namespace VAL {

  extern parse_category *top_thing;

  extern analysis an_analysis;
  extern analysis *current_analysis;

  extern yyFlexLexer *yfl;

};  // namespace VAL

extern char *current_filename;

using namespace VAL;

int main(int argc, char *argv[]) {
  current_analysis = &an_analysis;
  ifstream *current_in_stream;
  yydebug = 0;

  yfl = new yyFlexLexer;

  // Loop over given args
  for (int a = 1; a < argc; ++a) {
    current_filename = argv[a];
    cout << "File: " << current_filename << '\n';
    current_in_stream = new ifstream(current_filename);
    if (current_in_stream->bad()) {
      // Output a message new
      cout << "Failed to open\n";

      // Log an error to be reported in summary later
      line_no = 0;
      log_error(E_FATAL, "Failed to open file");
    } else {
      line_no = 1;

      // Switch the tokeniser to the current input stream
      yfl->switch_streams(current_in_stream, &cout);
      yyparse();

      // Output syntax tree
      if (top_thing) top_thing->display(0);
    }
    delete current_in_stream;
  }
  // Output the errors from all input files
  current_analysis->error_list.report();
  delete yfl;
}