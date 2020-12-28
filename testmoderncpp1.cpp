// testmoderncpp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class non_virtual_class {
public:
    int test_value;
};

class virtual_class {
public:
    int test_value;

    virtual void test()
    {
        std::cout << "test";
    }
};

class reference_test_base {
public:

    virtual void testme()
    {
        std::cout << "testme" << std::endl;
    }
};

template <typename T> class reference_test : public  reference_test_base
{
    T data;
public:
    virtual void testme()
    {
        std::cout << "testderived" << std::endl;
    }

};

struct some_struct 
{
    int a, b, c;
};

class some_class
{
public:
    int a, b, c;
};

class some_class2
{
public:
    int a, b, c;

    some_class2()
    {
        ;
    }
};

class some_class3 : public some_class2
{
public:

    char* ptr;

    some_class3() : ptr( nullptr )
    {
        ;
    }
};

class header_base
{
public:
    int a;
    int b;
};

template <typename ExtraData> class header_big : public header_base
{
public:
    ExtraData c;
};

template <typename ItemType, typename ExtraData = void> class test_header
{
public:

    using header_type = std::conditional_t<std::is_same_v<ExtraData,void>, header_base, header_big<ExtraData>>;

    ItemType items[42];
    header_type  my_header;

    template<class retval = ExtraData>
    typename std::enable_if< !std::is_same_v<retval, void>, retval >::type get_c()
    {
        return my_header.c;
    }

};

void test_reference(reference_test_base& something)
{
    something.testme();
}

int main()
{
    std::cout << "Hello World!\n";

    std::cout << sizeof(non_virtual_class) << std::endl;
    std::cout << sizeof(virtual_class) << std::endl;

    reference_test_base a;
    reference_test<int> b;

    std::cout << typeid(a).name() << std::endl;
    std::cout << typeid(b).name() << std::endl;

    test_reference(a);
    test_reference(b);

    int buffer[4];
    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    buffer[3] = 0;

    std::cout << "setting a pointer to a buffer leaves it" << std::endl;
    some_struct* x = (some_struct*)buffer;
    std::cout << x->a << " " << x->b << " " << x->c << std::endl;

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    some_struct* s = new (buffer) some_struct();
    std::cout << "placement new with a struct clears it" << std::endl;
    std::cout << s->a << " " << s->b << " " << s->c << std::endl;

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    some_class* c = new (buffer) some_class();
    std::cout << "placement new with a class clears it" << std::endl;
    std::cout << c->a << " " << c->b << " " << c->c << std::endl;

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    some_class2* d = new (buffer) some_class2();
    std::cout << "placement new with a class that has a constructor does not clear it" << std::endl;
    std::cout << d->a << " " << d->b << " " << d->c << std::endl;

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    some_class3* e = new (buffer) some_class3();
    std::cout << "placement new with a base class that has a constructor does not clear it" << std::endl;
    std::cout << e->a << " " << e->b << " " << e->c << " " << (int)e->ptr << std::endl;

    test_header<int> testo1;
    // this correctly will not compile
    // std::cout << testo1.get_c();

    test_header<int, std::string> testo2;
    std::cout << testo2.get_c();

    std::cout << sizeof(testo1) << " vs " << sizeof(testo2) << std::endl;

}

