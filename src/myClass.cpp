#include <boost/python.hpp>
#include <string>
#include <sstream>
#include <vector>

struct MyClassData {
    std::vector<std::string> paths;
};

class MyClass
{
public:
    MyClass(std::string n, float num=0) : name(n), mNumber(0.0), num(num) {
        ptr = std::make_shared<MyClassData>();
        ptr->paths.reserve(1);
        ptr->paths.push_back("test");
    }

    float num = 0.0f;

    std::string name;

    double getNumber() const { return mNumber; }
    void setNumber(double n)
    {
        if (n > 3.141592654)
            n = -1;
        mNumber = n;
    }
    const std::vector<std::string>& GetPaths() const
    {
        return ptr->paths;
    }

    int foo(int a, char b = 1, unsigned c = 2, double d = 3) {
        return a;
    }


private:
    
    double mNumber;
    std::shared_ptr<MyClassData> ptr;
};

static std::string 
_Repr(const MyClass& ctx) {
    std::string repr = "MyClass(";
    for (std::string s : ctx.GetPaths()) {
        repr += s;
    }
    repr += ")";
    return repr;
}

using namespace boost::python;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(foo_overloads, foo, 1, 4)

BOOST_PYTHON_MODULE(pyClass)
{    
    using This = MyClass;

    // to not expose any constructors at all: use no_init adds an 
    // __init__ method which always raises a Python RuntimeError exception
    class_<This>("MyClass", "My Class Doc String", init<std::string, optional<float>>())
        .def_readwrite("name", &MyClass::name)
        // if the number should only be read-only only set getNumber method
        .add_property("number", &MyClass::getNumber, &MyClass::setNumber)
        .def_readonly("num", &MyClass::num)
        .def("foo", &MyClass::foo, foo_overloads(args("a", "b", "c", "d"), "f's docstring"))
        .def("__repr__", &_Repr)
        ;

    // for derived class the following syntax could be used: 
    // class_<Derived, bases<Base> >("Derived")
    // automatically inheriting of base python methods
}
