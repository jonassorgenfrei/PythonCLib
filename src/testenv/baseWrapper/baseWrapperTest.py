import unittest
from baseWrapper import Base

class TestMyClass(unittest.TestCase):

    def test_virtual_function_with_default_implementation(self):
        base = Base()
        class Derived(Base):
            def f(self):
                return 42

        derived = Derived()

        self.assertEqual(base.f(), 0)
        self.assertEqual(derived.f(), 42)



if __name__ == '__main__':
    unittest.main()