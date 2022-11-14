import unittest
import pyClass

class TestMyClass(unittest.TestCase):

    def test_constructor(self):
        myClassObj = pyClass.MyClass("test")
        self.assertEqual(myClassObj.name, 'test')

        # optinal parameters
        myClassObj = pyClass.MyClass("test", 2)
        self.assertEqual(myClassObj.num, 2)

    def test_readOnlyVariable(self):
        myClassObj = pyClass.MyClass("test")
        with self.assertRaises(AttributeError):
            myClassObj.num = 0.5
    
    def test_overloads(self):
        myClassObj = pyClass.MyClass("test")

        # check minimal one paramter
        try:
            myClassObj.foo()
        except Exception as e:
            self.assertTrue(str(e).startswith("Python argument types in"))
        
        self.assertEqual(myClassObj.foo(1,'a'), 1)
        self.assertEqual(myClassObj.foo(1,'a',4), 1)
        self.assertEqual(myClassObj.foo(1,'a',5,6.0), 1)

    def test_docstring(self):
        myClassObj = pyClass.MyClass("test")

        self.assertTrue(str(myClassObj.__doc__).find("My Class Doc String") != -1)

if __name__ == '__main__':
    unittest.main()