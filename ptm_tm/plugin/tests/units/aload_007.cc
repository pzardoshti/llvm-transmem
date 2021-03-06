// Test of std::atomic load instrumentation.
//
// Here we ensure that a load of an atomic double results in a proper call to
// the API

#ifdef TEST_DRIVER
#include "../include/harness.h"

// declare the function in OFILE1 that comprises the root of the test
extern "C" {
double test_aload_d();
double tm_test_aload_d();
}

int main() {
  report<double>("aload_007", "loads of atomic doubles get instrumented",
                 {{test_aload_d(), tm_test_aload_d()}},
                 {{TM_STATS_LOAD_D, 0}, {TM_STATS_UNSAFE, 1}});
}
#endif

#ifdef TEST_OFILE1
#include "../../../common/tm_api.h"
#include <atomic>
extern std::atomic<double> var_d;
extern "C" {
TX_SAFE double test_aload_d() {
  return var_d == 9.7884637261 ? 9.7884637261 : 0;
}
}
#endif

#ifdef TEST_OFILE2
#include <atomic>
// declare var here, to ensure it doesn't get optimized away
std::atomic<double> var_d = {9.7884637261};
#endif
