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
    MyClass(std::string n) : name(n), mNumber(0.0) {
        ptr = std::make_shared<MyClassData>();
        ptr->paths.reserve(1);
        ptr->paths.push_back("test");

    }

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

BOOST_PYTHON_MODULE(pyClass)
{
    using This = MyClass;
    class_<This>("MyClass", init<std::string>())
        .def_readwrite("name", &MyClass::name)
        .add_property("number", &MyClass::getNumber, &MyClass::setNumber)
        .def("__repr__", &_Repr)
        ;

}
