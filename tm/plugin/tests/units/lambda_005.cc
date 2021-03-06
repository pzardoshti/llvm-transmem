// Test of C++ lambdas for transaction boundaries
//
// Across-TU marked calls from a lambda get instrumented

#ifdef TEST_DRIVER
#include "../include/harness.h"
int marked_not_in_tu_call_test();
int main() {
  report<int>("lambda_005",
              "Marked cross-TU calls from lambda get instrumented",
              {{marked_not_in_tu_call_test(), 121}},
              {{TM_STATS_TRANSLATE_FOUND, 1},
               {TM_STATS_TRANSLATE_NOTFOUND, 0},
               {TM_STATS_UNSAFE, 0},
               {TM_STATS_STORE_U4, 1}});
}
#endif

#ifdef TEST_OFILE1
#include "../../../common/tm_api.h"
int x = 0;
void marked(int val);
int marked_not_in_tu_call_test() {
  x = 66;
  TX_BEGIN { marked(11); }
  TX_END;
  return x;
}
#endif

#ifdef TEST_OFILE2
#include "../../../common/tm_api.h"
extern int x;
TX_SAFE void marked(int val) { x = val * val; }
#endif