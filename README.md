# QSearch

QSearch is a (stub) project whose main interest was for me to experiment with the `std::async` C++ API. It is written using both the Qt API and the STL.

The initial motivation was to find a use-case for a highly-concurrent task that could be parallelized with `std::async` in a better and / or simpler way than `std::thread` (or `QThread`). 
The use-case I found was searching for files on a disk, an operation that is known to be highly IO-bound. 

The code exposes a simple but rather smart way not to have to use any thread-count limiting technique while still making the most of `std::async` on modern computers (the number of threads is still pretty high) (it may also work well on less modern computers, though I have to admit I haven't tried it).

**Note:** Qt concurrency features (such as `QFuture` have voluntareely not been used, as Qt was chosen uniquely for user interaction and not as a real framework in this project.
