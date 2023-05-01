#pragma once
#include <iostream>
#include <memory>

class MyClass {
private:
	int num_;
public:
	MyClass(int num) : num_(num) {
		std::cout << "Constructor called" << std::endl;
	}
	~MyClass() {
		std::cout << "Destructor called" << std::endl;
	}
	int GetNum() {
		return num_;
	}
};

void Function1(std::unique_ptr<MyClass> ptr) {
	std::cout << "Function1 called with " << ptr->GetNum() << std::endl;
}

void Function2(std::shared_ptr<MyClass> ptr) {
	std::cout << "Functional called with " << ptr->GetNum() << std::endl;
}


void smart_pointers() {
	// �������� ������� � ���������� �� � ������� unique_ptr
	std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>(42);
	std::cout << "ptr1 points to " << ptr1->GetNum() << std::endl;
	Function1(std::move(ptr1)); // �������� � ������� � ������� std::move
	// ��� ������������� unique_ptr ������ ��������� ��� �������� � �������
	std::cout << "ptr1 is " << (ptr1 ? "not null" : "null") << std::endl;  // ptr1 ������ null

	// �������� ������� � ���������� �� � ������� shared_ptr
	std::shared_ptr<MyClass> ptr2 = std::make_shared<MyClass>(24);
	std::cout << "ptr2 points to " << ptr2->GetNum() << std::endl;
	Function2(ptr2); // �������� � �������
	std::cout << "ptr2 still points to " << ptr2->GetNum() << std::endl;  // ptr2 ��� ��� ��������� �� ������
	std::cout << "ptr2 use_count is " << ptr2.use_count() << std::endl;

	// �������� ����������� ������ � ������� shared_ptr
	std::shared_ptr<MyClass> ptr3 = std::make_shared<MyClass>(100);
	std::shared_ptr<MyClass> ptr4 = std::make_shared<MyClass>(200);
	std::shared_ptr<MyClass> tmp1(ptr3);
	std::shared_ptr<MyClass> tmp2(ptr4);
	ptr3.swap(ptr4);
	std::cout << ptr3->GetNum() << std::endl; // ptr3->GetNum() = 200;
	ptr4.swap(ptr3);
	std::cout << ptr3->GetNum() << std::endl;
	std::cout << "ptr3 use_count is " << ptr3.use_count() << std::endl;  // use_count ����� 2
	std::cout << "ptr4 use_count is " << ptr4.use_count() << std::endl;  // use_count ����� ����� 2
	// ����� ��� shared_ptr ������� �� ������� ���������, ������� ���������


}
