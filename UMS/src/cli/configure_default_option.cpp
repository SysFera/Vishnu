#include <boost/program_options.hpp>
#include "configureOptionUtils.hpp"
#include "cliUtil.hpp"
#include "utils.hpp"
#include "utilVishnu.hpp"
#include "Options.hpp"
#include "api_ums.hpp"

namespace po = boost::program_options;

using namespace std;
using namespace vishnu;

int
main (int ac, char* av[]) {
  boost::shared_ptr<Options> opt(new Options(av[0])) ;

  return  commonConfigure(opt,  ac,  av,&configureDefaultOption);
}  // end of main
