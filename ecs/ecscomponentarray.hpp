#pragma once

#include<iostream>
#include<vector>

#include "ecscomponent.hpp"

// a wrapper over std::vector that properly contains a contigiuous array of components.
// in addition, this will contain methods for adding and removing components
// using a handle/pointer management system.



// we will need a stack for the dangling pointers.
template<typename T>
struct Stack
{
public:
	
	void Push(T element);
	T Pop();

	std::vector<T>& getArray();

	uint Size();
	void Clear();

private:
	std::vector<T> m_array;
};


// actual component array.
template<typename TComponent> 
class ECSComponentArray
{
public:

	ECSComponentArray();
	~ECSComponentArray();
	
	// operator overloads:
	// commented for now. probably get rid of this because of the problems that will
	// arise when accessing a handle pointing to a removed component.
	//TComponent& operator[](uint handle);

	// array management:
	uint AddComponent(BaseECSComponent& component); // returns the index of the pointer.
	void RemoveComponent(uint handle);

	// getters for entire arrays:
	std::vector<TComponent>& getArray();
	std::vector<TComponent*>& getPointerArray();

	// single-element getter using the handles:
	// return as a pointer to the element in case the component is null.
	TComponent* getComponent(uint handle); // NOTE: CAN RETURN A NULLPTR.

	// synchronizing arrays:
	// trust copy should only be used if the pointers are exactly the same between them.
	void TrustCopyFrom(ECSComponentArray<TComponent> from);

	// getters for elements:
	TComponent* getPointer(uint handle);

	// array properties:
	uint NumberOfComponents();
	uint NumberOfPointers();

	// debug:
	void CompareAddresses();

private:

	std::vector<TComponent> m_components;
	std::vector<TComponent*> m_pointers;
	Stack<uint> m_recycledPointers;

};

template<typename TComponent>
TComponent* ECSComponentArray<TComponent>::getComponent(uint handle)
{
	if (handle >= m_pointers.size())
	{
		return nullptr;
	}
	
	// search through recycled pointers.
	for (auto it = m_recycledPointers.getArray().begin(); it != m_recycledPointers.getArray().end(); it++)
	{
		if ((*it) == handle) // then this pointer is not pointing to a component.
		{
			return nullptr;
		}
	}

	// here, the handle refers to an actual component.
	return m_pointers[handle];
}

template<typename TComponent>
TComponent* ECSComponentArray<TComponent>::getPointer(uint handle)
{
	return m_pointers[handle];
}

/*template<typename TComponent>
TComponent& ECSComponentArray<TComponent>::operator[](uint handle)
{
	if (handle >= m_pointers.size())
	{
		std::cout << "Either handle refers outside of the pointer array or the component has been removed! Returning first component instead. " << std::endl;
		return *m_pointers[0];
	}
	return *m_pointers[handle];
}*/

template<typename TComponent>
void ECSComponentArray<TComponent>::TrustCopyFrom(ECSComponentArray<TComponent> from)
{
	m_components = from.getArray();
}

template<typename TComponent>
ECSComponentArray<TComponent>::ECSComponentArray()
{
	m_components.reserve(8);
	m_pointers.reserve(8);
}

template<typename TComponent>
ECSComponentArray<TComponent>::~ECSComponentArray()
{
	m_components.clear();
	m_pointers.clear();
	m_recycledPointers.Clear();
}


template<typename TComponent>
void ECSComponentArray<TComponent>::CompareAddresses()
{
	for (uint i = 0; i < m_components.size(); i++)
	{
		std::cout << "Component at " << &m_components[i] << std::endl;
		std::cout << "Pointer at.. " << m_pointers[i] << std::endl;
	}
}

template<typename TComponent>
void ECSComponentArray<TComponent>::RemoveComponent(uint handle)
{
	// algorithm for removing a component:
	// the component to delete is found by: handle indexes into the pointer array, which
	// points to the component in the component array.
	// 
	// ALGORITHM:
	// 1. identify the component ci with pointer pi. 
	// 2. using the pointerID of the last element of the component array, identify the 
	//	  pointer pBack that points to that element. 
	// 3. repoint pi and pBack so pi points at cBack and pBack points at ci.
	// 4. swap components ci and the last component cBack in the array. 
	// 5. push the index of pi onto the recycled pointer stack.
	// 6. pop ci off of the component array.

	// exceptions:
	if (handle > m_pointers.size() - 1) // this should never happen if components are added properly.
	{
		std::cout << "This component does not exist! " << std::endl;
		return;
	}

	// 1.
	TComponent*& pi = m_pointers[handle];
	TComponent& ci = *pi;
	
	// 2.
	BaseECSComponent cBack = static_cast<BaseECSComponent>(m_components.back());
	TComponent*& pBack = m_pointers[cBack.getPointerID()];
		
	// 3.
	TComponent* temp = pi;
	pi = pBack;
	pBack = temp;

	// 4.
	std::swap(ci, m_components.back());

	// 5.
	m_recycledPointers.Push(handle);

	// 6.
	m_components.pop_back();

}


template<typename TComponent>
uint ECSComponentArray<TComponent>::AddComponent(BaseECSComponent& component)
{
	// case 1: there are no pointers in the recycle bin. add a component normally.
	if (m_recycledPointers.Size() == 0)
	{
		// store index of the new pointer that will be added in component.setPointerID().
		component.setPointerID(m_pointers.size());

		// add the component to the component array.
		m_components.push_back(*(static_cast<TComponent*>(&component)));

		// add a pointer that points to the component we just added.
		m_pointers.push_back(&(m_components.back()));

		// return a handle to the pointer so the entity knows where its component is.
		return m_pointers.size() - 1;
	}

	// case 2: a pointer is available to be recycled.
	// by storing the indices of the pointers in a stack, the pointer that gets popped off will 
	// point directly to the next spot in the component array.
	else
	{
		// get handle on the pointer at the top of the recycle bin and pop it off.
		uint index = m_recycledPointers.Pop();
		
		// register that pointer to the component.
		component.setPointerID(index);

		// add the component to the component array. the pointer should be pointing to this spot already.
		m_components.push_back(*(static_cast<TComponent*>(&component)));

		// return a handle to that same pointer.
		return index;
	}
}

template<typename TComponent>
uint ECSComponentArray<TComponent>::NumberOfComponents()
{
	return m_components.size();
}

template<typename TComponent>
uint ECSComponentArray<TComponent>::NumberOfPointers()
{
	return m_pointers.size();
}


template<typename TComponent>
std::vector<TComponent>& ECSComponentArray<TComponent>::getArray()
{
	return m_components; 
}

template<typename TComponent>
std::vector<TComponent*>& ECSComponentArray<TComponent>::getPointerArray()
{
	return m_pointers; 
}



// STACK:

template<typename T>
void Stack<T>::Push(T element)
{
	m_array.push_back(element);
}

template<typename T>
T Stack<T>::Pop()
{
	T t = m_array.back();
	m_array.pop_back();
	return t;
}
	
template<typename T>
uint Stack<T>::Size()
{
	return m_array.size();
}

template<typename T>
void Stack<T>::Clear()
{
	m_array.clear();
}

template<typename T>
std::vector<T>& Stack<T>::getArray()
{
	return m_array;
}




















