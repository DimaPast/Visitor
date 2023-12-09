
#include <iostream>
#include <vector>
#include <Windows.h>

class ConcreteElementA;
class ConcreteElementB;


class Visitor {
public:
    virtual void visitConcreteElementA(ConcreteElementA* elementA) = 0;
    virtual void visitConcreteElementB(ConcreteElementB* elementB) = 0;
    virtual void visitAllElements() = 0;  
    virtual ~Visitor() = default;
};


class Element {
public:
    virtual void accept(Visitor* visitor) = 0;
    virtual ~Element() = default;
};


class ConcreteElementA : public Element {
public:
    void accept(Visitor* visitor) override {
        visitor->visitConcreteElementA(this);
    }

    void operationA() {
        std::cout << "ConcreteElementA: Операція A" << std::endl;
    }
};


class ConcreteElementB : public Element {
public:
    void accept(Visitor* visitor) override {
        visitor->visitConcreteElementB(this);
    }

    void operationB() {
        std::cout << "ConcreteElementB: Операція B" << std::endl;
    }
};

class ConcreteVisitor : public Visitor {
public:
    void visitConcreteElementA(ConcreteElementA* elementA) override {
        elementA->operationA();
    }

    void visitConcreteElementB(ConcreteElementB* elementB) override {
        elementB->operationB();
    }

    void visitAllElements() override {
        std::cout << "ConcreteVisitor: Відвідано всі елементи" << std::endl;
    }
};


class ObjectStructure {
private:
    std::vector<Element*> elements;

public:
    void addElement(Element* element) {
        elements.push_back(element);
    }

    void accept(Visitor* visitor) {
        for (Element* element : elements) {
            element->accept(visitor);
        }
        visitor->visitAllElements();
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ConcreteElementA elementA;
    ConcreteElementB elementB;

    ObjectStructure objectStructure;
    objectStructure.addElement(&elementA);
    objectStructure.addElement(&elementB);

    ConcreteVisitor concreteVisitor;
    objectStructure.accept(&concreteVisitor);

    return 0;
}
