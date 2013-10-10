#ifndef incl_HPHP_EXT_XDIFF_H_
#define incl_HPHP_EXT_XDIFF_H_

#include "hphp/runtime/base/base-includes.h"

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

Variant HHVM_FUNCTION(xdiff_string_rabdiff, const String& str1, const String& str2);

///////////////////////////////////////////////////////////////////////////////
}

#endif // incl_HPHP_EXT_XDIFF_H_
