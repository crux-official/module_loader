#ifndef CRUX_MODULE_LOADER_API_H
#define CRUX_MODULE_LOADER_API_H

#include "kernel_types.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// The module concern's contract: the one struct of function pointers the
// module driver fills and serves - the dynamic module loading machinery
// (the host loads a module, resolves its symbols, and queries its facts).
// Handles are opaque per-platform records defined in the driver's source, so
// growing the record is not growing the contract. GetMtime returns the
// last-write fact the record captured at load (not a live query of the file
// system); FileName decorates a machine name with the build's shared-library
// prefix and suffix.
//
// The concern is dispatched through the engine's registry channel: the
// driver's served ModuleAPI, selected by the concern's stable dispatch id.
// The concern is OPTIONAL:
// module_loader_none serves the empty contract and registers no concern bit
// (the consumer's gate is Engine_Supports(CRUX_CONCERN_MODULE)).
typedef struct ModuleAPI {
  PackageVersion version;
  void *(*Load)(const char *path);
  void (*Unload)(void *handle);
  void *(*GetSymbol)(void *handle, const char *name);
  bool (*GetMtime)(void *handle, int64_t *outMtimeSeconds);
  bool (*FileName)(const char *baseName, char *out, size_t size);
} ModuleAPI;

#ifdef __cplusplus
}
#endif

#endif
