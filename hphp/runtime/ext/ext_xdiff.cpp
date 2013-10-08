#include "hphp/runtime/ext/ext_xdiff.h"

namespace HPHP {

static class XdiffExtension : public Extension {
public:
  XdiffExtension() : Extension("xdiff") { }
  virtual void moduleLoad(Hdf config) {
    HHVM_FE(xdiff_native);
  }
} s_xdiff_extension;

String HHVM_FUNCTION(xdiff_native) {
  String s("Hello from xdiff cpp");

  return s;
}

}
