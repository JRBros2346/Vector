#pragma once 

namespace Lib {
	template<typename T>
	class Iterator {
		T* ptr;
		
		public:
			explicit Iterator();
			explicit Iterator(T*);
			
			~Iterator();
			
			bool operator==(const Iterator&) const;
			bool operator!=(const Iterator&) const;
			
			T operator*() const;
			
			Iterator& operator++();
			Iterator operator++(int);
			
			Iterator& operator--();
			Iterator operator--(int);
			
			bool operator>(const Iterator&);
			bool operator<(const Iterator&);
			bool operator>=(const Iterator&);
			bool operator<=(const Iterator&);
	};
	
	template<typename T>
	Iterator<T>::Iterator() : ptr(nullptr) {
	}
	template<typename T>
	Iterator<T>::Iterator(T* p) : ptr(p) {
	}
	
	template<typename T>
	Iterator<T>::~Iterator() { delete [] ptr; }
	
	template<typename T>
	bool Iterator<T>::operator==(const Iterator<T>& other) const {
		return (*this == other);
	}
	template<typename T>
	bool Iterator<T>::operator!=(const Iterator<T>& other) const {
		return !(*this == other);
	}
	
	template<typename T>
	T Iterator<T>::operator*() const {
		return *ptr;
	}
	
	template<typename T>
	Iterator<T>& Iterator<T>::operator++() {
		++ptr;
		return *this;
	}
	template<typename T>
	Iterator<T> Iterator<T>::operator++(int) {
		Iterator temp(ptr);
		++ptr;
		return temp;
	}
	
	template<typename T>
	Iterator<T>& Iterator<T>::operator--() {
		--ptr;
		return *this;
	}
	template<typename T>
	Iterator<T> Iterator<T>::operator--(int) {
		Iterator temp(ptr);
		--ptr;
		return temp;
	}
	
	template<typename T>
	bool Iterator<T>::operator>(const Iterator& other) {
		return (ptr > other.ptr);
	}
	template<typename T>
	bool Iterator<T>::operator<(const Iterator& other) {
		return (ptr < other.ptr);
	}
	template<typename T>
	bool Iterator<T>::operator>=(const Iterator& other) {
		return (ptr >= other.ptr);
	}
	template<typename T>
	bool Iterator<T>::operator<=(const Iterator& other) {
		return (ptr <= other.ptr);
	}
} // namespace Lib
