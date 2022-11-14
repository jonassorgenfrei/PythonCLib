#include <boost/python.hpp>

using namespace boost::python;

struct Base
{
    virtual ~Base() {}
    // non pure virutal function
    virtual int f() { return 0; }
};

struct BaseWrap : Base, wrapper<Base>
{
    int f()
    {
        // check if the function is implemented
        if (override f = this->get_override("f"))
            return f();
        // if no virtual function is defined call base function
        return Base::f();
    }

    int default_f() { return this->Base::f(); }
};

BOOST_PYTHON_MODULE(baseWrapper)
{
    // expose both functions fto keep track of the dispatch function f & forwarding
    // the function to its defualt implementation default_f
    class_<BaseWrap, boost::noncopyable>("Base")
        .def("f", &Base::f, &BaseWrap::default_f)
        ;
}
