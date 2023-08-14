#pragma once
#include <iostream>
#include <utility>
#define Poolsize 65536

using namespace std;

struct MemoryPool
{
	void* start;
	void* current;
	size_t size;
	size_t usedMemory;
	size_t numAllocations;

	MemoryPool()
		: usedMemory(0)
		, numAllocations(0)
		, size(Poolsize)
	{
		start = malloc(Poolsize);
		current = start;
	};

	~MemoryPool()
	{
		if (start != nullptr)
		{
			free(start);
		}
	};
};

static MemoryPool GloabalPool = MemoryPool();

template <class T >
class CustomAllocator 
{
public:
	
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	CustomAllocator() 
	{
		cout << "CustomAllocator constructor  " << endl;	
	};
	
	CustomAllocator(const CustomAllocator&) {};
	~CustomAllocator()	{};

	template <class U>
	struct rebind
	{
		typedef CustomAllocator<U> other;
	};

	pointer allocate(size_type n, const void* = 0)
	{
		if (GloabalPool.usedMemory + n * sizeof(T) > GloabalPool.size)
		{
			cout << "Poolsize exeeded! " << endl;
			throw bad_alloc();
			return nullptr;
		}
		pointer res = (pointer)GloabalPool.current;
		GloabalPool.current = ptr_add(GloabalPool.current, n * sizeof(T));
		GloabalPool.usedMemory += n * sizeof(T);
		GloabalPool.numAllocations++;
		cout << "Allocated = " << n * sizeof(T) << " bytes. Total used = " << GloabalPool.usedMemory << " bytes" << endl;
		return res;
	};


	void deallocate(void* p, size_type n)
	{
		// No deallocation in line allocator
	};

	void clear()
	{
		GloabalPool.usedMemory = 0;
		GloabalPool.numAllocations = 0;
		GloabalPool.current = GloabalPool.start;
	};

	pointer address(reference x) const { return &x;	};
	const_pointer address(const_reference x) const { return &x;	};
	CustomAllocator<T>& operator=(const CustomAllocator&) { return *this;};

	void construct(pointer p, const T& val)
	{
		new ((T*)p) T(val);
	};

	void destroy(pointer p)
	{
		p->~T();
	};

	size_type max_size() const
	{
		return GloabalPool.size;
	};

	template <class U>
	CustomAllocator(const CustomAllocator<U>& other) {}

	template <class U>
	CustomAllocator& operator=(const CustomAllocator<U>&) { return *this; }

	inline void* ptr_add(const void* const p, const uintptr_t& amount)
	{
		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(p) + amount);
	}


};