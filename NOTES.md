# Fast prime factorization

Strategy :
- Activate compiler optimization
- Look for more efficient factorization algorithms
- Find the optimal number of threads to run in parallel on the target architecture
- Use hashmap caching (one cache shared by all threads) to store the result of each factorization
- Use thread-local caching of the prime numbers discovered (this cache is local to remove the need for synchronization)
- Delay output until the end so as to remove the need for an output synchronization. By the end of the run, each thread will have put its factorizations in the cache. The only thing left to do is go through the cache once every thread has finished computing.