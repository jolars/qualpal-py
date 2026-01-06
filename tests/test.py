"""Basic test for the Qualpal package."""

from qualpal import MyClass, my_function

def test_my_class():
    """Test the MyClass functionality."""
    obj = MyClass(10)
    assert obj.get_value() == 10

def test_my_function():
    """Test the add function."""
    assert my_function(3, 5) == 8
    assert my_function(-1, 1) == 0
