#include "hphp/runtime/ext/ext_xdiff.h"

namespace HPHP {

String HHVM_FUNCTION(xdiff_native) {
  String s("Hello from xdiff cpp");

  return s;
}

}
