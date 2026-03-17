#pragma once
#include <cassert>


template <typename DataType, int size>

class MemoryPool
{
	DataType poolData[size]; // array for the pool
	DataType* pNextFree = nullptr; // Pointer to the next free item

public:
	class iterator
	{
	public:
		iterator(DataType* ptr) : ptr(ptr) {} // constructor

		iterator operator ++ () // Increment the pointer
		{
			++ptr;
			return *this;
		}

		iterator operator --() // Decrement the pointer
		{
			--ptr;
			return *this;
		}

		bool operator != (const iterator& other) const // returns thrue if two iterators are not equal
		{
			return ptr != other.ptr;
		}

		DataType* operator*() // returns current pointer
		{
			return ptr;
		}
	private:
		DataType* ptr;	// Pointer for this iterator
	};

public:
	MemoryPool() : pNextFree(poolData) {}

	// returns an iterator which points at the start of the pool
	iterator begin() { return iterator(poolData);}

	// returns an iterator which points the next element after the memory pool
	iterator end() { return iterator(pNextFree);}

	// takes the next available item from the pool and returns thrue if its allocated. if it doesnt find a free item then it returns false.
	bool addItem(DataType& item)
	{
		if (pNextFree < (poolData + size)) // if the pNextFree pointer is less than the end of the array the we have more free elements
		{
			*pNextFree = item; // overwrite the cells data with the new object
			++pNextFree; // bump the pointer
			return true;
		}
		return false; // if we get here we have no free elements in the momory pool
	}
	
	// we must call free when an aelement becomes free otherwise we'll not be able to allocate
	void erase(DataType* item)
	{
		assert(pNextFree > poolData); // check we arent trying to erase an item when the pool is already empty
		*item = *(pNextFree - 1); // replace the element which is now dead with the last active one
		--pNextFree; // decrement the pointer
	}

};

