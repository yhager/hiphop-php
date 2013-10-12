#ifndef incl_HPHP_EXT_XDIFF_H_
#define incl_HPHP_EXT_XDIFF_H_

#include "hphp/runtime/base/base-includes.h"

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

void xdiff_keepme();
Variant HHVM_FUNCTION(xdiff_string_rabdicff, const String& str1, const String& str2);

///////////////////////////////////////////////////////////////////////////////
}

#endif // incl_HPHP_EXT_XDIFF_H_
