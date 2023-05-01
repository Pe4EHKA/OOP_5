#pragma once
#include <iostream>
#include <memory>
#include <typeinfo>
#include <string>

class Animal {
private:
    void walk() {
        std::cout << this->classname() << " went for a walk" << std::endl;
    }
public:

    Animal() {
        std::cout << "Animal is born!" << std::endl;
    }

    void hungry() {
        std::cout << "Animal is hungry" << std::endl;
        eat();
    }

    virtual void lying() {
        std::cout << "Animal lying on the floor" << std::endl;
    }

    virtual void eat() {
        std::cout << "Animal is eating" << std::endl;
    }

    void sleep() {
        std::cout << "Animal is sleeping" << std::endl;
    }

    void need_walk() {
        std::cout << this->classname() << " is getting for a walk" << std::endl;
        walk();
    }

    virtual void speak() {
        std::cout << "I am an animal!" << std::endl;
    }

    virtual ~Animal() {
        std::cout << "Animal destructor called" << std::endl;
    }

    virtual std::string classname() {
        return "Animal";
    }

    virtual bool isA(std::string classname) {
        return this->classname() == classname;
    }
};

class Cat : public Animal {
private:
    void walk() {
        std::cout << this->classname() << " keep staying at home" << std::endl;
    }
public:

    Cat() {
        std::cout << "Cat is born!" << std::endl;
    }

    void eat() override {
        std::cout << "Cat is eating" << std::endl;
    }

    void lying() {
        std::cout << "Cat is lying on the table" << std::endl;
    }

    void sleep() {
        std::cout << "Cat is purring" << std::endl;
    }

    void speak() override {
        std::cout << "Meow!" << std::endl;
    }

    void run_from_dog() {
        std::cout << "Scary Cat running from dog" << std::endl;
    }

    ~Cat() override {
        std::cout << "Cat destructor called" << std::endl;
    }

    std::string classname() override {
        return "Cat";
    }

    bool isA(std::string classname) override {
        return this->classname() == classname || Animal::isA(classname);
    }
};

class Dog : public Animal {
private:

public:
    Dog() {
        std::cout << "Dog is born!" << std::endl;
    }

    void eat() override {
        std::cout << "Dog is eating" << std::endl;
    }

    void bark() {
        std::cout << "Dog is barking!" << std::endl;
    }

    void speak() {
        std::cout << "GAV!" << std::endl;
    }

    void run_for_cat(Cat enemy) {
        std::cout << "Dog running to Cat!" << std::endl;
        enemy.run_from_dog();
    }

    ~Dog() override {
        std::cout << "Dog destructor called" << std::endl;
    }

    std::string classname() override {
        return "Dog";
    }

    bool isA(std::string classname) override {
        return this->classname() == classname || Animal::isA(classname);
    }
};

void Welcome_to_the_Zoo() {
    std::unique_ptr<Animal> animal = std::make_unique<Animal>();
    std::unique_ptr<Cat> cat = std::make_unique<Cat>();

    // ����� classname ���������� ��� ������, � ������� �� ��� ������, 
    // � ����� isA ��������� ��� ������ � ���������� true, ���� ������, 
    // ��� �������� �� ��� ������, ����������� ����� ������.

    std::cout << "Animal pointer is pointing to " << animal->classname() << std::endl;
    std::cout << "Cat pointer is pointing to " << cat->classname() << std::endl;

    std::cout << "Is animal pointer an Animal? " << std::boolalpha << animal->isA("Animal") << std::endl;
    std::cout << "Is cat pointer an Animal? " << std::boolalpha << cat->isA("Animal") << std::endl;
    std::cout << "Is animal pointer a Cat? " << std::boolalpha << dynamic_cast<Cat*>(animal.get()) << std::endl;
    std::cout << "Is cat pointer a Cat? " << std::boolalpha << dynamic_cast<Cat*>(cat.get()) << std::endl;

    Animal* animal2 = cat.get();
    std::cout << "Animal2 pointer is pointing to " << animal2->classname() << std::endl;
    std::cout << "Is animal2 pointer a Cat? " << std::boolalpha << dynamic_cast<Cat*>(animal2) << std::endl;
}

void foo(Animal* a) {
    a->sleep();
    Cat* something = dynamic_cast<Cat*>(a);
    //std::cout << (something ? "YES" : "NO") << std::endl;
    if (something != nullptr) {
        something->run_from_dog();
    }
    //a->speak();
    std::cout << std::boolalpha << a << std::endl;
    //a->speak();
    std::cout << "---------End of foo()---------" << std::endl;
    
}

void overrided_and_inherited() {
    std::cout << "---------Override and inherite---------" << std::endl;
    Cat* cat = new Cat();
    foo(cat);
    Animal* cat2 = new Cat();
    // ���������� �������
    cat->speak();  // ������������� �����
    cat->Animal::speak();  // ����������� �����
    delete cat;
    delete cat2;
}
void safe_dangerous_conversion() {
    // �������� �������������� ���������� ������ � ������� typeid
    std::cout << "---------Safe/Dangerous conversion---------" << std::endl;
    std::cout << "--------- By typeid ---------" << std::endl;
    Animal* animal_ = new Cat();
    if (typeid(*animal_) == typeid(Cat)) {
        std::cout << "Animal is a Cat" << std::endl;
    }
    else {
        std::cout << "Animal is not a Cat" << std::endl;
    }
    delete animal_;
    std::cout << "--------- By dynamic_cast ---------" << std::endl;
    animal_ = new Dog();
    Dog* dog = dynamic_cast<Dog*>(animal_);
    if (dog) {
        std::cout << "Animal is a Dog" << std::endl;
        dog->bark();
    }
    else {
        std::cout << "Animal is not a Dog" << std::endl;
    }
    delete animal_;
    std::cout << "--------- By static_cast ---------" << std::endl;
    Animal* animal_second = new Animal();
    Cat* someone = new Cat();
    std::cout << "Look at this Cheburashka" << std::endl;
    // ����� ����������, ����������� ��� "Cat", ����� �������� ��� ����������� ������ "Animal"
    *animal_second = static_cast<Animal>(*someone);  // �������� ����� ������� "Cat"
    //c ������� "static_cast", ������� ��� "Cat" � ���� "Animal"
    std::cout << "Who is it?" << std::endl;
    delete animal_second;
    delete someone;
}

void answers() {
    /* � ������1 �������� ������ ���������� �����2, ������� ��������� � ���� �� 
    ������ ��� �� �����������, � ������-������� �����2 �������������: 
    ��� ���������� ��� ������ ������1 � ������-�������?*/
    std::cout << "1------------------" << std::endl;
    Cat* visycat = new Cat();
    visycat->need_walk();  // �������� ����� �������� ������ � ����� �������
    std::cout << "2------------------" << std::endl;
    /*�	� ������1 �������� ������ ���������� �����2, ������� ��������� � ���� ��
    ������ ��� �����������, � ������-������� �����2 �������������:
    ��� ���������� ��� ������ ������1 � ������-�������?*/
    Dog* catdog = new Dog();
    catdog->hungry(); // ���������� ������� �����1 �������� ������ � �����2 ������������ ������
    std::cout << "3------------------" << std::endl;
    /*�	� ������� ������ �������� ����� �� �����������, � � ������-������� �������� �����
    � ����� �� ������: ����� ����� ����� ���������� ��� ��������� � ������� ����� ���������
    �� ������� �����, ����� ��������� �� �����-�������?*/
    Animal* someone = new Cat();
    someone->sleep();
    visycat->sleep();
    std::cout << "------------------" << std::endl;
    /*�	� ������� ������ �������� ����� �����������, � � ������-������� �������� �����
    � ����� �� ������: ����� ����� ����� ���������� ��� ��������� � ������� ����� ���������
    �� ������� �����, ����� ��������� �� �����-�������?*/
    someone->lying();
    visycat->lying();
    std::cout << "------------------" << std::endl;
    delete someone;
    delete catdog;
    delete visycat;
}