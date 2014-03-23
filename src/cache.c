#include "cache.h"

cache_entry_t * newCacheEntry() {
  cache_entry_t * entry = malloc(sizeof(cache_entry_t));
  entry->numberOfFactors = 0;
  // TODO: need to allocate the array?
  return entry;
}

void freeCacheEntry(cache_entry_t * entry) {
  // TODO: need to free the array?
  free(entry);
}