#include<iostream>

#include"vector.hpp"

int main() {
	Lib::Vector<int> v;
	v.push(1);
	v.push(100);
	v.emplace(5);
	v.emplace(6);
	v.pop();
	v.emplace(10);
	v.display();

	int sum = 0;
	for (const auto& e : v)
		sum += e;
	std::cout << "Sum: " << sum;
}