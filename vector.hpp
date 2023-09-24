#pragma once

#include<iostream>

namespace Lib {
	template<typename T>
	class Vector {
		const static size_t DEFAULT_CAPACITY = 1;
		const static size_t RESIZE_FACTOR = 2;

		size_t SIZE = 0;
		size_t CAPACITY = 0;
		T* DATA = nullptr;
		public:
			explicit Vector();
			explicit Vector(size_t);
			explicit Vector(Vector<T>&&);
			explicit Vector(const Vector<T>&);
			~Vector();

			void push(T&&);
			void push(const T&);
			template<typename... Args>
			T& emplace(Args&&... args);
			T pop();
			
			void resize();
			void clear();
			
			size_t size() const;
			size_t capacity() const;
			T* data() const;
			
			class Iter {
				T* ptr;
				public:
					Iter();
					Iter(T*);
					
					T& operator*();
					T* operator->();
					
					Iter& operator++();
					Iter operator++(int);
					Iter& operator--();
					Iter operator--(int);
					
					bool operator==(Iter&);
					bool operator!=(Iter&);
					bool operator<=(Iter&);
					bool operator>=(Iter&);
					bool operator<(Iter&);
					bool operator>(Iter&);
			};
			
			Iter begin();
			Iter end();
			Iter rbegin();
			Iter rend();
			
			class ConstIter {
				T* ptr;
				public:
					ConstIter();
					ConstIter(T*);
					
					const T& operator*() const;
					const T* operator->() const;
					
					ConstIter& operator++();
					ConstIter operator++(int);
					ConstIter& operator--();
					ConstIter operator--(int);
					
					bool operator==(ConstIter&);
					bool operator!=(ConstIter&);
					bool operator<=(ConstIter&);
					bool operator>=(ConstIter&);
					bool operator<(ConstIter&);
					bool operator>(ConstIter&);
			};
			
			const ConstIter cbegin() const;
			const ConstIter cend() const;
			const ConstIter crbegin() const;
			const ConstIter crend() const;
			
			void display();
	};

	template<typename T>
	Vector<T>::Vector()
			: SIZE(0),
			  CAPACITY(DEFAULT_CAPACITY) {
		DATA = (T*)::operator new(DEFAULT_CAPACITY * sizeof(T));
	}
	template<typename T>
	Vector<T>::Vector(size_t capacity)
			: SIZE(0),
			  CAPACITY(capacity) {
		DATA = (T*)::operator new(capacity * sizeof(T));
	}
	template<typename T>
	Vector<T>::Vector(Vector<T>&& other)
			: SIZE(other.SIZE),
			  CAPACITY(other.CAPACITY) {
		DATA = other.DATA;
		
		other.SIZE = 0;
		other.CAPACITY = 0;
		other.DATA = nullptr;
	}
	template<typename T>
	Vector<T>::Vector(const Vector<T>& other)
			: SIZE(other.SIZE),
			  CAPACITY(other.CAPACITY) {
		DATA = ::operator new(other.CAPACITY * sizeof(T));
		for (size_t i = 0; i < other.SIZE; i++)
			DATA[i] = other.DATA[i];
	}
	template<typename T>
	Vector<T>::~Vector() {
		clear();
		::operator delete(DATA, CAPACITY * sizeof(T));
	}

	template<typename T>
	void Vector<T>::push(const T& val) {
		if (SIZE == CAPACITY)
			resize();
		DATA[SIZE++] = val;
	}
	template<typename T>
	void Vector<T>::push(T&& val) {
		if (SIZE == CAPACITY)
			resize();
		DATA[SIZE++] = std::move(val);
	}
	template<typename T>
	template<typename... Args>
	T& Vector<T>::emplace(Args&&... args) {
		if (SIZE == CAPACITY)
			resize();
		new(&DATA[SIZE]) T(std::move(args)...);
		return DATA[SIZE++];
	}
	template<typename T>
	T Vector<T>::pop() {
		T val = std::move(DATA[--SIZE]);
		DATA[SIZE].~T();
		return val;
	}
	
	template<typename T>
	void Vector<T>::resize() {
		CAPACITY *= RESIZE_FACTOR;
		T* block = (T*)::operator new(CAPACITY * sizeof(T));
		for (size_t i = 0; i < SIZE; i++)
			block[i] = std::move(DATA[i]);
		::operator delete(DATA, CAPACITY * sizeof(T));
		DATA = block;
		block = nullptr;
	}
	template<typename T>
	void Vector<T>::clear() {
		for (size_t i = 0; i < SIZE; i++)
			DATA[i].~T();
		SIZE = 0;
	}
	
	template<typename T>
	size_t Vector<T>::size() const { return SIZE; }
	template<typename T>
	size_t Vector<T>::capacity() const { return CAPACITY; }
	template<typename T>
	T* Vector<T>::data() const { return DATA; }
	
	template<typename T>
	Vector<T>::Iter::Iter() : ptr(nullptr) {
	}
	template<typename T>
	Vector<T>::Iter::Iter(T* p) : ptr(p) {
	}
	
	template<typename T>
	T& Vector<T>::Iter::operator*() {
		return *ptr;
	}
	template<typename T>
	T* Vector<T>::Iter::operator->() {
		return ptr;
	}
	
	template<typename T>
	typename Vector<T>::Iter& Vector<T>::Iter::operator++() {
		++ptr;
		return *this;
	}
	template<typename T>
	typename Vector<T>::Iter Vector<T>::Iter::operator++(int) {
		Iter tmp = *this;
		++ptr;
		return tmp;
	}
	template<typename T>
	typename Vector<T>::Iter& Vector<T>::Iter::operator--() {
		--ptr;
		return *this;
	}
	template<typename T>
	typename Vector<T>::Iter Vector<T>::Iter::operator--(int) {
		Iter tmp = *this;
		--ptr;
		return tmp;
	}
	
	template<typename T>
	bool Vector<T>::Iter::operator==(Vector<T>::Iter& other) { return ptr == other.ptr; }
	template<typename T>
	bool Vector<T>::Iter::operator!=(Vector<T>::Iter& other) { return ptr != other.ptr; }
	template<typename T>
	bool Vector<T>::Iter::operator<=(Vector<T>::Iter& other) { return ptr <= other.ptr; }
	template<typename T>
	bool Vector<T>::Iter::operator>=(Vector<T>::Iter& other) { return ptr >= other.ptr; }
	template<typename T>
	bool Vector<T>::Iter::operator<(Vector<T>::Iter& other) { return ptr < other.ptr; }
	template<typename T>
	bool Vector<T>::Iter::operator>(Vector<T>::Iter& other) { return ptr > other.ptr; }
	
	template<typename T>
	typename Vector<T>::Iter Vector<T>::begin() { return DATA; }
	template<typename T>
	typename Vector<T>::Iter Vector<T>::end() { return DATA + SIZE; }
	template<typename T>
	typename Vector<T>::Iter Vector<T>::rbegin() { return DATA + SIZE - 1; }
	template<typename T>
	typename Vector<T>::Iter Vector<T>::rend() { return DATA - 1; }
	
	template<typename T>
	Vector<T>::ConstIter::ConstIter() : ptr(nullptr) {}
	template<typename T>
	Vector<T>::ConstIter::ConstIter(T* p) : ptr(p) {}
	
	template<typename T>
	const T& Vector<T>::ConstIter::operator*() const {
		return *ptr;
	}
	template<typename T>
	const T* Vector<T>::ConstIter::operator->() const {
		return ptr;
	}
	
	template<typename T>
	typename Vector<T>::ConstIter& Vector<T>::ConstIter::operator++(){
		++ptr;
		return *this;
	}
	template<typename T>
	typename Vector<T>::ConstIter Vector<T>::ConstIter::operator++(int){
		Iter tmp = *this;
		++ptr;
		return tmp;
	}
	template<typename T>
	typename Vector<T>::ConstIter& Vector<T>::ConstIter::operator--(){
		--ptr;
		return *this;
	}
	template<typename T>
	typename Vector<T>::ConstIter Vector<T>::ConstIter::operator--(int){
		Iter tmp = *this;
		--ptr;
		return tmp;
	}
	
	template<typename T>
	bool Vector<T>::ConstIter::operator==(Vector<T>::ConstIter& other) { return ptr == other.ptr; }
	template<typename T>
	bool Vector<T>::ConstIter::operator!=(Vector<T>::ConstIter& other) { return ptr != other.ptr; }
	template<typename T>
	bool Vector<T>::ConstIter::operator<=(Vector<T>::ConstIter& other) { return ptr <= other.ptr; }
	template<typename T>
	bool Vector<T>::ConstIter::operator>=(Vector<T>::ConstIter& other) { return ptr >= other.ptr; }
	template<typename T>
	bool Vector<T>::ConstIter::operator<(Vector<T>::ConstIter& other) { return ptr < other.ptr; }
	template<typename T>
	bool Vector<T>::ConstIter::operator>(Vector<T>::ConstIter& other) { return ptr > other.ptr; }
	
	template<typename T>
	const typename Vector<T>::ConstIter Vector<T>::cbegin() const { return DATA; }
	template<typename T>
	const typename Vector<T>::ConstIter Vector<T>::cend() const { return DATA + SIZE; }
	template<typename T>
	const typename Vector<T>::ConstIter Vector<T>::crbegin() const { return DATA + SIZE - 1; }
	template<typename T>
	const typename Vector<T>::ConstIter Vector<T>::crend() const { return DATA - 1; }
	
	template<typename T>
	void Vector<T>::display() {
		std::cout << "< ";
		for (const auto& v : *this)
			std::cout << v << ' ';
		std::cout << '>' << std::endl;
	}

} // namespace Lib
