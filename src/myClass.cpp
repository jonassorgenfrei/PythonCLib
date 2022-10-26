#include <boost/python.hpp>
#include <string>
#include <sstream>

class MyClass
{
public:
    SomeClass(std::string n) : name(n), mNumber(0.0) {}

    std::string name;
    double getNumber() const { return mNumber; }
    void setNumber(double n)
    {
        if (n > 3.141592654)
            n = -1;
        mNumber = n;
    }
private:
    double mNumber;
};



using namespace boost::python;

BOOST_PYTHON_MODULE(pyClass)
{
    class_<MyClass>("MyClass", init<std::string>())
        .def_readwrite("name", &MyClass::name)
        .add_property("number", &MyClass::getNumber, &MyClass::setNumber)
        ;

}
