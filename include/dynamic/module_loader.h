#ifndef CRUX_DYNAMIC_MODULE_LOADER_H
#define CRUX_DYNAMIC_MODULE_LOADER_H

#include "kernel_types.h"
#include "module_loader_api.h"
#include "engine.h"
#include "kernel_types.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// The dynamic rendering of the module contract: every call dispatches through
// the engine's registry channel - the module driver's served ModuleAPI,
// selected by the concern's stable dispatch id (DRIVER_MODULE,
// platform_types.h).
static inline void *Module_Load(const char *path) {
  return ((ModuleAPI *)crux_engine_api->GetExtensionAPI(DRIVER_MODULE))->Load(path);
}
static inline void Module_Unload(void *handle) {
  ((ModuleAPI *)crux_engine_api->GetExtensionAPI(DRIVER_MODULE))->Unload(handle);
}
static inline void *Module_GetSymbol(void *handle, const char *name) {
  return ((ModuleAPI *)crux_engine_api->GetExtensionAPI(DRIVER_MODULE))->GetSymbol(handle, name);
}
static inline bool Module_GetMtime(void *handle, int64_t *outMtimeSeconds) {
  return ((ModuleAPI *)crux_engine_api->GetExtensionAPI(DRIVER_MODULE))->GetMtime(handle, outMtimeSeconds);
}
static inline bool Module_FileName(const char *baseName, char *out, size_t size) {
  return ((ModuleAPI *)crux_engine_api->GetExtensionAPI(DRIVER_MODULE))->FileName(baseName, out, size);
}

#ifdef __cplusplus
}
#endif

#endif
