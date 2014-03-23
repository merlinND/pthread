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

void freeCache(map_t cache) {
  cache_entry_t * entry = NULL;

  int status = MAP_MISSING;
  do {
    status = hashmap_get_one(cache, (any_t) &entry, 1);
    if (status == MAP_OK) {
      freeCacheEntry(entry);
      entry = NULL;
    }
  } while (status != MAP_MISSING);

  hashmap_free(cache);
}