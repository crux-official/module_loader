#ifndef CRUX_STATIC_MODULE_LOADER_H
#define CRUX_STATIC_MODULE_LOADER_H

#include "kernel_types.h"
#include "module_loader_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// The static rendering of the module contract: plain externs, defined by the
// module driver and linked into the binary. A static consumer pays zero
// indirection and cannot accidentally dispatch.
extern void *Module_Load(const char *path);
extern void Module_Unload(void *handle);
extern void *Module_GetSymbol(void *handle, const char *name);
extern bool Module_GetMtime(void *handle, int64_t *outMtimeSeconds);
extern bool Module_FileName(const char *baseName, char *out, size_t size);

#ifdef __cplusplus
}
#endif

#endif
