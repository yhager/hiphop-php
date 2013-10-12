#ifndef incl_HPHP_EXT_XDIFF_H_
#define incl_HPHP_EXT_XDIFF_H_

#include "hphp/runtime/base/base-includes.h"

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

void xdiff_keepme();

Variant HHVM_FUNCTION(xdiff_string_bdiff_size, const String& patch);

Variant HHVM_FUNCTION(xdiff_string_bdiff, const String& old_data,
                                          const String& new_data);

Variant HHVM_FUNCTION(xdiff_string_bpatch, const String& str,
                                           const String& patch);

Variant HHVM_FUNCTION(xdiff_string_diff, const String& old_data,
                                         const String& new_data,
                                         int context /* =3 */,
                                         bool minimal /* = false */);

Variant HHVM_FUNCTION(xdiff_string_merge3, const String& old_data,
                                           const String& new_data1,
                                           const String& new_data2,
                                           String& error /* = null_string */);

Variant HHVM_FUNCTION(xdiff_string_patch, const String& str,
                                          const String& patch,
                                          int64_t flags /* = XDIFF_PATCH_NORMAL */,
                                          String& error /* = null_string */);
Variant HHVM_FUNCTION(xdiff_string_rabdiff, const String& str1,
                                            const String& str2);

///////////////////////////////////////////////////////////////////////////////
}

#endif // incl_HPHP_EXT_XDIFF_H_
