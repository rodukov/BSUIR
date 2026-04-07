def max_digit(n: int) -> int:
    """
    Возвращает наибольшую цифру в десятичной записи числа n.
    Для отрицательных чисел знак игнорируется.
    Если число равно 0, возвращает 0.
    """
    n = abs(n)
    if n == 0:
        return 0
    max_d = 0
    while n > 0:
        digit = n % 10
        if digit > max_d:
            max_d = digit
        n //= 10
    return max_d