#include <iostream>
#pragma once

class Base {

public:
	Base() { std::cout << "Base default constructor" << std::endl; }
	Base(Base* obj) { std::cout << "Base pointer constructor" << std::endl; }
	Base(Base& obj) { std::cout << "Base reference constructor" << std::endl; }
	virtual ~Base() { std::cout << "Base destructor" << std::endl; }

};

class Desc : public Base {

public:
	Desc() { std::cout << "Desc default constructor" << std::endl; }
	Desc(Desc* obj) { std::cout << "Desc pointer constructor" << std::endl; }
	Desc(Desc& obj) { std::cout << "Desc reference constructor" << std::endl; }
	~Desc() { std::cout << "Desc destructor" << std::endl; }
};

void func1(Base obj) {
	Base* x = &obj;
	Desc* pointer = dynamic_cast<Desc*>(x);
	if (pointer) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
		std::cout << std::boolalpha << pointer << std::endl;
	}
	std::cout << "func1(Base obj)" << std::endl;
}

void func2(Base* obj) {
// Можно ли внутри функции привести переданный Base к Desc с помощью приведения типов?
	// Нет нельзя, так как в классе Base нету ни единственного виртуального метода
	// Класс не полиморфного типа
	// this doesn't work -> obj = dynamic_cast<Desc*>(obj);
	std::cout << "func2(Base* obj)" << std::endl;
}

void func3(Base& obj) {
	std::cout << "func3(Base& obj)" << std::endl;
}

// Функция1 возвращает статический объект Base, который создается локально внутри функции.
// При возвращении объекта происходит его копирование в локальную переменную, после чего вызывается
// деструктор для временного объекта. Никаких проблем с памятью не возникает.
// разницу со static & без static
Base func1() {
	Base b;
	std::cout << "func1: Created static Base object" << std::endl;
	return b;
}

// Функция2 возвращает указатель на статический объект Base, созданный локально в функции.
// При возвращении указателя создается копия указателя, а не объекта, 
// поэтому никаких проблем с памятью не возникает. (UB)
Base* func2() {
	Base b;
	std::cout << "func2: Created static Base object" << std::endl;
	return &b;
}

// Функция3 возвращает ссылку на статический объект Base, созданный локально в функции.
// При возвращении ссылки не создается никаких копий объектов, 
// поэтому проблемы с памятью не возникают. (UB)
Base& func3() {
	Base b;
	std::cout << "func3: Created static Base object" << std::endl;
	return b;
}

// Функция 4 возвращает динамически созданный объект Base. При возвращении объекта создается
// копия объекта, после чего вызывается деструктор для временного объекта. Однако, в данном случае
// происходит утечка памяти, так как созданный объект не был освобожден оператором delete.
Base func4() {
	Base* b = new Base();
	std::cout << "func4: Created dynamic Base object" << std::endl;
	return *b;
}

// Функция 5 возвращает указатель на динамически созданный объект Base. При возвращении указателя
// создается копия указателя, а не объекта, поэтому никаких проблем с памятью не возникает.
// Проблема решается unique_ptr
Base* func5() {
	Base* b = new Base();
	std::cout << "func5: Created dynamic Base object" << std::endl;
	return b;
}

// Функция 6 возвращает ссылку на динамически созданный объект Base. При возвращении ссылки не создается
// никаких копий объектов, поэтому никаких проблем с памятью не возникает. Однако в данном случае
// возникает утечка памяти, так как объект не был освобожден оператором delete.
Base& func6() {
	Base* b = new Base();
	std::cout << "func6: Created dynamic base object" << std::endl;
	return *b;
}


void base_and_desc() {
	Base b;
	Base* pb = new Base();
	Base& lb = b;
	Desc d;
	Desc* pd = new Desc();
	Desc& ld = d;
	std::cout << "------------------" << std::endl;
	std::cout << "Checking the mechanism of passing objects as parameters to a function" << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "Base" << std::endl;
	func1(b);
	func2(pb);
	func3(lb);
	std::cout << "------------------" << std::endl;
	std::cout << "Desc" << std::endl;
	func1(d);
	func2(pd);
	func3(ld);
	std::cout << "------------------" << std::endl;
	std::cout << "Deleting pb and pd" << std::endl;
	std::cout << "------------------" << std::endl;
	delete pb;
	delete pd;
	std::cout << "Dynamic object are deleted" << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "Checking the mechanism for returning objects from a function" << std::endl;
	std::cout << "------------------" << std::endl;
	b = func1();
	pb = func2();
	lb = func3();
	std::cout << "First three functions passed" << std::endl;
	std::cout << "------------------" << std::endl;
	b = func4();
	pb = func5();
	lb = func6();
	std::cout << "Last three functions passed" << std::endl;
	std::cout << "------------------" << std::endl;

}