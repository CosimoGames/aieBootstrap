#pragma once
#include <vector>
#include <cassert>


template <typename DataType>
class DynamicStore
{
public:
	std::vector<DataType*> elementPointerArray;

public:
	auto begin()
	{
		return elementPointerArray.begin(); // update start and end iterators
	}

	auto end() const
	{
		return elementPointerArray.end();

	}

	void addItem(const DataType& item)
	{
		DataType* pNewItem = new DataType(item); // creat a copy of the new item on the heap
		elementPointerArray.push_back(pNewItem); // add the pointer to the dynamic array

	}

	auto erase(typename std::vector<DataType*>::iterator item)
	{
		// delete the memory for the item of the heap
		assert(*item != nullptr);
		delete(*item);
		// remove its pointer from the dynamic array
		// note how erase returns an updated iterator which we need to return to avoid memory corruption
		return elementPointerArray.erase(item);
	}
};

