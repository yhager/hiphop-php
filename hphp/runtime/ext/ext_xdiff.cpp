#include "hphp/runtime/ext/ext_xdiff.h"
#include <xdiff.h>

namespace HPHP {

static class XdiffExtension : public Extension {
public:
  XdiffExtension() : Extension("xdiff") { }
  virtual void moduleLoad(Hdf config) {
    HHVM_FE(xdiff_string_rabdiff);
  }
} s_xdiff_extension;


static mmfile_t* make_mmfile(const String& str)
{
  mmfile_t* mmfile = (mmfile_t*) malloc(sizeof(mmfile_t));

  if (xdl_init_mmfile(mmfile, str.length(), XDL_MMF_ATOMIC) < 0) {
    free(mmfile);
    return nullptr;
  }

  void *mem = xdl_mmfile_writeallocate(mmfile, str.length());
  if (!mem) {
    xdl_free_mmfile(mmfile);
    free(mmfile);
    return nullptr;
  }

  memcpy(mem, str.data(), str.length());
  return mmfile;
}

static int append_string(void *ptr, mmbuffer_t* bufs, int count) {
  String* str = (String*) ptr;
  for (int i=0; i< count; ++i) {
    str->operator+=(String(bufs[i].ptr, bufs[i].size, CopyString));
  }
  return 0;
}

Variant HHVM_FUNCTION(xdiff_string_rabdiff, const String& old_data,
                      const String& new_data) {
	mmfile_t *mmold, *mmnew;

  SCOPE_EXIT {
    xdl_free_mmfile(mmold);
    xdl_free_mmfile(mmnew);
  };

  mmold = make_mmfile(old_data);
  mmnew = make_mmfile(new_data);

  if (!mmold || !mmnew)
    return false;

  xdemitcb_t ecb;
  String output;
  ecb.priv = &output;
  ecb.outf = append_string;

	if (xdl_rabdiff(mmold, mmnew, &ecb) < 0)
    return false;

  return output;
}

}
