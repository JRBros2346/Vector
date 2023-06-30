#pragma once

#include"iterator.hpp"
// #include<cstdexc>

namespace Lib {
	template<typename T>
	class Vector {
		const static auto DEFAULT_CAPACITY = 1ULL;
		const static auto RESIZE_FACTOR = 2ULL;
		
		unsigned long long SIZE;
		unsigned long long CAPACITY;
		T* DATA;
		public:
			explicit Vector();
			explicit Vector(Vector<T>&);
			explicit Vector(unsigned long long);
			~Vector();
			
			T& operator[](unsigned long long);
			T& at(unsigned long long);
			
			void resize();
			
			unsigned long long push(T, unsigned long long);
			unsigned long long push(T);
			T pop(unsigned long long);
			T pop();
			
			void clear();
			unsigned long long size() const;
			unsigned long long capacity() const;
			T* data() const;
			
			Iterator<T> begin() const;
			Iterator<T> end() const;
	};
	
	template<typename T>
	Vector<T>::Vector()
			: CAPACITY(DEFAULT_CAPACITY),
			  DATA(new T[DEFAULT_CAPACITY]),
			  SIZE(0) {
	}
	template<typename T>
	Vector<T>::Vector(Vector<T>& other)
			: DATA(other.data()),
			  SIZE(other.size()),
			  CAPACITY(other.capacity()) {
	}
	template<typename T>
	Vector<T>::Vector(unsigned long long capacity)
			: DATA(new T[capacity]),
			  SIZE(0),
			  CAPACITY(capacity) {
	}
	template<typename T>
	Vector<T>::~Vector() { delete[] DATA; }
	
	template<typename T>
	T& Vector<T>::operator[](unsigned long long pos) {
		return DATA[pos];
	}
	template<typename T>
	T& Vector<T>::at(unsigned long long pos) {
		if (pos < SIZE) 
			return DATA[pos];
		else
			std::invalid_argument("Out of bounds!");
	}
	
	template<typename T>
	void Vector<T>::resize() {
		CAPACITY *= RESIZE_FACTOR;
		T* temp = DATA;
		DATA = new T[CAPACITY];
		for (unsigned long long i = 0; i < SIZE; i++) DATA[i] = temp[i];
	}

	template<typename T>
	unsigned long long Vector<T>::push(T val, unsigned long long pos) {
		if(SIZE == CAPACITY) this->resize();
		for (auto i = SIZE; i > pos; i--) 
			DATA[i+1] = DATA[i];
		DATA[pos] = val;
		return SIZE++;
	}
	template<typename T>
	unsigned long long Vector<T>::push(T val) {
		if(SIZE == CAPACITY) this->resize();
		DATA[SIZE] = val;
		return SIZE++;
	}

	template<typename T>
	T Vector<T>::pop(unsigned long long pos) {
		T val = DATA[pos];
		for (auto i = pos; i < SIZE-1; i++)
			DATA[i] = DATA[i+1];
		SIZE--;
		return val;
	}
	template<typename T>
	T Vector<T>::pop() { return DATA[--SIZE]; }
	
	template<typename T>
	void Vector<T>::clear() { SIZE = 0; }
	template<typename T>
	unsigned long long Vector<T>::size() const { return SIZE; }
	template<typename T>
	unsigned long long Vector<T>::capacity() const { return CAPACITY; }
	template<typename T>
	T* Vector<T>::data() const { return DATA; }
	
	template<typename T>
	Iterator<T> Vector<T>::begin() const { return Iterator<T>(DATA); }
	template<typename T>
	Iterator<T> Vector<T>::end() const { return Iterator<T>(DATA + SIZE); }
} // namespace Lib
