import unittest
import pyClass

class TestMyClass(unittest.TestCase):

    def test_constructor(self):
        myClassObj = pyClass.MyClass("test")
        self.assertEqual(myClassObj.name, 'test')

if __name__ == '__main__':
    unittest.main()