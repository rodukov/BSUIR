import unittest
from max_digit import max_digit
class TestMaxDigit(unittest.TestCase):

    def test_positive_numbers(self):
        self.assertEqual(max_digit(123), 3)
        self.assertEqual(max_digit(987), 9)
        self.assertEqual(max_digit(100), 1)
        self.assertEqual(max_digit(555), 5)

    def test_negative_numbers(self):
        self.assertEqual(max_digit(-123), 3)
        self.assertEqual(max_digit(-987), 9)
        self.assertEqual(max_digit(-100), 1)

    def test_zero(self):
        self.assertEqual(max_digit(0), 0)

    def test_single_digit(self):
        self.assertEqual(max_digit(5), 5)
        self.assertEqual(max_digit(0), 0)

    def test_large_number(self):
        self.assertEqual(max_digit(1234567890), 9)

    # Граничные значения
    def test_boundary_values(self):
        self.assertEqual(max_digit(0), 0)
        self.assertEqual(max_digit(1), 1)      # нижняя положительная
        self.assertEqual(max_digit(9), 9)      # верхняя однозначная
        self.assertEqual(max_digit(10), 1)     # переход к двузначным
        self.assertEqual(max_digit(99), 9)     # верхняя двузначная
        self.assertEqual(max_digit(-1), 1)     # переход через ноль (отрицательное)
        self.assertEqual(max_digit(-9), 9)     # граница отрицательных однозначных

if __name__ == '__main__':
    unittest.main()