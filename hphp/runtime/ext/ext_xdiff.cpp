#include "hphp/runtime/ext/ext_xdiff.h"
#include <xdiff.h>

namespace HPHP {

static void xdiff_init();

static class XdiffExtension : public Extension {
public:
  XdiffExtension() : Extension("xdiff") { }
  virtual void moduleLoad(Hdf config) {
    HHVM_FE(xdiff_string_bpatch);
    HHVM_NAMED_FE(xdiff_string_diff_binary, HHVM_FN(xdiff_string_bdiff)); // alias
    HHVM_FE(xdiff_string_diff);
    HHVM_FE(xdiff_string_merge3);
    HHVM_NAMED_FE(xdiff_string_patch_binary, HHVM_FN(xdiff_string_bpatch)); // alias
    HHVM_FE(xdiff_string_patch);
    HHVM_FE(xdiff_string_rabdiff);
		xdiff_init();
  }
} s_xdiff_extension;

// reperesent an mmfile_t from libxdiff
class XdiffMmFile {
  mmfile_t m_mmfile;
public:
  XdiffMmFile(String str) {
    // not checking return values here - the first always returns 0, the
    // second can only fail on malloc, which will throw
    xdl_init_mmfile(&m_mmfile, str.length(), XDL_MMF_ATOMIC);
    void *mem = xdl_mmfile_writeallocate(&m_mmfile, (long) str.length());
    assert(mem);
    memcpy(mem, str.data(), str.length());
  }

  ~XdiffMmFile() {
    xdl_free_mmfile(&m_mmfile);
  }

  mmfile_t* get() {
    return &m_mmfile;
  }
};

// wrap xdemitcb_t
class XdiffOutput {
  xdemitcb_t m_ecb;
  String m_output;
public:
  XdiffOutput() {
    m_ecb.priv = &m_output;
    m_ecb.outf = XdiffOutput::appendString;
  }
  static int appendString(void *ptr, mmbuffer_t* bufs, int count) {
    assert(ptr);
    assert(bufs);
    String* str = (String*) ptr;
    for (int i=0; i<count; ++i) {
      str->operator+=(String(bufs[i].ptr, bufs[i].size, CopyString));
    }
    return 0;
  }

  xdemitcb_t* get() {
    return &m_ecb;
  }

  String output() const {
    return m_output;
  }
};

void xdiff_keepme() {}

void* php_malloc(void*, unsigned int size) {
  return malloc(size);
}

void php_free(void*, void* ptr) {
  assert(ptr);
  free(ptr);
}

void* php_realloc(void*, void* ptr, unsigned int size) {
  assert(ptr);
  return realloc(ptr, size);
}

static void xdiff_init() {
  memallocator_t malt = {nullptr, php_malloc, php_free, php_realloc};
	xdl_set_allocator(&malt);
}

Variant HHVM_FUNCTION(xdiff_string_bdiff_size, const String& patch) {
  return xdl_bdiff_tgsize(XdiffMmFile(patch).get());
}

Variant HHVM_FUNCTION(xdiff_string_bdiff, const String& old_data,
                                          const String& new_data) {
  XdiffMmFile xold(old_data), xnew(new_data);
  XdiffOutput o;
  bdiffparam_t params = { 16 };

  if (xdl_bdiff(xold.get(), xnew.get(), &params, o.get()) < 0)
    return false;

  return o.output();
}

Variant HHVM_FUNCTION(xdiff_string_bpatch, const String& str,
                                           const String& patch) {
  XdiffMmFile xstr(str), xpatch(patch);
  XdiffOutput o;

  if (xdl_bpatch(xstr.get(), xpatch.get(), o.get()) < 0)
    return false;

  return o.output();
}

Variant HHVM_FUNCTION(xdiff_string_diff, const String& old_data,
                                         const String& new_data,
                                         int context /* =3 */,
                                         bool minimal /* = false */) {
  XdiffMmFile xold(old_data), xnew(new_data);
  XdiffOutput o;
  xpparam_t params = { minimal ? XDF_NEED_MINIMAL : 0 };
  xdemitconf_t conf = { abs(context) };

  if (xdl_diff(xold.get(), xnew.get(), &params, &conf, o.get()) < 0)
    return false;

  return o.output();
}

Variant HHVM_FUNCTION(xdiff_string_merge3, const String& old_data,
                                           const String& new_data1,
                                           const String& new_data2,
                                           String& error /* = null_string */) {
  XdiffMmFile xold(old_data), xnew1(new_data1), xnew2(new_data2);
  XdiffOutput o, e;

  if (xdl_merge3(xold.get(), xnew1.get(), xnew2.get(), o.get(), e.get()) < 0)
    return false;

  if (!error.empty())
    error = e.output();

  return o.output();
}

Variant HHVM_FUNCTION(xdiff_string_patch, const String& str,
                                          const String& patch,
                                          int64_t flags /* = XDIFF_PATCH_NORMAL */,
                                          String& error /* = null_string */) {
  XdiffMmFile xstr(str), xpatch(patch);
  XdiffOutput o, e;

  if (xdl_patch(xstr.get(), xpatch.get(), flags, o.get(), e.get()) < 0) {
    return false;
  }
  if (!error.empty())
    error = e.output();
  
  return o.output();
}

Variant HHVM_FUNCTION(xdiff_string_rabdiff, const String& old_data,
                                            const String& new_data) {
  XdiffMmFile xold(old_data), xnew(new_data);
  XdiffOutput o;

  if (xdl_rabdiff(xold.get(), xnew.get(), o.get()) < 0)
    return false;

  return o.output();
}

}
