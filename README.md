yout: post
title: Manual
---

# DynamicData

### Introduction

Dynamic Data (DD) is an array like data structure, which can be persisted on disc. DD shares many properties with Log Structured Merge Trees, but is implemented differently. It is efficient for fast random read access and for insert and delete operations with minimal lock time. Usually b-trees or skip lists are employed in these kind of situations. The main difference to the DD data structure is that DD's random read access complexity is O(1) compared to O(log(n)) for b-trees or skip lists. 
Conceptually the data can be accessed like in a continous array with indexes rather than like in a linked list or a tree where you have to iterate over the nodes to find a stored value for a certain index. 
Because we could not find any similar data structure, we have chosen to call it Concurrent Mapped Vector (CMV). This might not be the most pretty name but it reflects that the data structure has the characteristics of a resizable array and that it can only work effectively in a multithreaded environment.
It is also worth noting that a CMV data structure could also be implemented as an in memory data structure only. 

### Interface Description

The CMV is a data structure with an API similar to the one of vector classes such as std::vector.

The API exposes the following methods:
 
	y_type get(size_type idx) // random access
	void insertIdx(size_type idx, y_type yvalue) // random insert 
	void deleteIdx(size_type idx) // random delete 

size_type is an unsigned integral type and y_type is a scalar value or a struct.

Please note that the indices of the CMV are different from the keys of a hash map. The keys of the hash map are constant in time, the indices of the CMV may change when new elements are inserted. 


The following example illustrates this. Sk is an instantiation of a CMV and contains 5 elements:

	//pseudocode
	//insert 6 at index 3
	sk.insert(3, 6);

	//insert 5 at index 3
	sk.insert(3, 5);

	//get index 4
	int value = sk.get(4);
	
The return value will be 6, because 5 was inserted at index 3 so the value 6 moved one index up. 


### Complexity

The CMV works transactionally and multithreaded. This means that it always accumulates a certain number of operations, these are the pending elements P_N. Other background working threads then incorporate these pending operations into the core memory of the CMV data structure which can be in RAM or on disc.

The main thread performs the read, write and delete operations with complexity 

	O(log(P_N))
	
If the background threads are fast enough to keep P_N small, then the complexity can become constant O(1).

In the current implementation the background thread calculates P_N pending elements down with the complexity 

	BACKGROUND_OPS = P_N + N 

where N is the number of elements currently contained in CMVs core memory. This complexity could possibly be optimized. 

Because of fast multithreaded hardware one can imagine that the frequency of insert and delete operations can be quite high and still P_N remains small.




### The Dynamic Data Project 

The DynamicData Project is a reference implementation of the MVC data structure where the core memory is kept persistently on disc. With few modifications the core memory could be relocated to RAM. 

The DD is still a prototype and should be tested thoroughly before using it in production work. There are still many performance improvements which could be implemented. 

Our main focus in this project was to reduce the BACKGROUND_OPS because this gives the biggest performance boost. We have to mention that the complexity for the insert and delete operations is O(log(P_N) + P_N) rather than O(log(P_N)). But this shortcoming could be overcome if we used a special skip list in our implementation.


### Applications

The interest in this kind of data structure arose during development of one of our mobile software products. We needed a simple ordered data storage. 

The main advantage of our solution over relational database implementations is that the storage can be queried without annoying cursor manipulations, caching and continuous data querying. This is because or solution can perform random reads efficiently. The ability to have an ordered set with a simple interface simplifies also the software development compared to similar relational database implementations.

It would be very interesting to find other real world applications where this data structure can be useful. We think that possible application could be in the domain of big data processing/storage, big text manipulations, data exchange, multimedia storage, audio and video processing.


### Future Work

These are some of the improvements which we have in mind: 

1. Faster manipulation of background data and faster caching
2. Dynamically changeable data layout size
3. Update operation (now implemented with a delete and an insert)
4. Build a key value store with efficient random read access and find out the difference in performance to log structured merge trees.

We are very interested in developing this data structure further. For suggestions improvements or possible applications please contact us: hello@cleverandson.com 


### Setup

DD is a header-only library which was developed on OSX and Xcode. It should supposedly run on all Unix systems. 
The code is standard C++11 compatible, except for mmap which is used to map the binary files to memory.

For basic usage of the library have a look at Demo.h. The application user interface is defined in DDIndex.

### Implementation Overview

work in progress ...

If you have questions about the implementation please feel free to contact us: hello@cleverandson.com 




###### This project is maintained by [Clever & Son](https://github.com/cleverandson "Clever & Son")

