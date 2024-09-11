import grid as grid
import numpy as np
import math
import matplotlib.pyplot as plt


# y’ = sin(x) - y, y(0) = 10

def f1(x, y):
    return math.sin(x) - y
    # Точное решение теста выше
    # y = -0.5cos(x) + 0.5sin(x) + 21/2*exp(-x)


def sol1(x):
    y = list()
    for i in x:
        y.append(-0.5 * math.cos(i) + 0.5 * math.sin(i) + 10.5 * math.exp(-i))
    return y


# Первая система (решения, представимого в элементарных функциях, не сущ ествует):
# (y_1)’ = y_2 - cos(x), y_1(0) = 0
# (y_2)’ = y_1 + sin(x), y_2(0) = 0

# Вычисление производной y1
def f1_1(x, y):
    return y[1] - math.cos(x)


# Вычисление производной y2
def f1_2(x, y):
    return y[0] + math.sin(x)


# Метод Рунге-Кутта 2-ого порядка
def R_K_2(func, x_0, y_0, func_cnt, n, len):
    # Используется схема "предиктор - корректор"
    h = len / n  # шаг
    if func_cnt == 1:
        # Одно уравнение
        grid = dict()  # Сеточная функция
        grid[x_0] = y_0
        x_i = x_0
        y_i = y_0
        for i in range(0, n):
            x_new = x_i + h
            grid[x_new] = y_i + (func(x_i, y_i) + func(x_new, y_i + h * func(x_i, y_i))) * h / 2
            y_i = grid[x_new]
            x_i = x_new
        return grid
    else:
        # Система уравнений
        grid = dict()
        grid[x_0] = y_0
        x_i = x_0
        y_i = y_0
        for i in range(0, n):
            x_new = x_i + h
            y_vals1 = np.zeros(func_cnt)
            y_vals2 = np.zeros(func_cnt)
            for j in range(0, func_cnt):
                y_vals1[j] = func[j](x_i, y_i)
                y_vals2[j] = func[j](x_new, y_i + h * y_vals1[j])
            grid[x_new] = y_i + (y_vals1 + y_vals2) * h / 2
            y_i = grid[x_new]
            x_i = x_new
        return grid


# Метод Рунге-Кутта 4-ого порядка
def R_K_4(func, x_0, y_0, func_cnt, n, len):
    h = len / n  # шаг
    grid = dict()  # Сеточная функция
    grid[x_0] = y_0
    x_i = x_0
    y_i = y_0
    if func_cnt == 1:
        # Одно уравнение
        for i in range(0, n):
            x_new = x_i + h
            k1 = func(x_i, y_i)
            k2 = func(x_i + h / 2, y_i + (h / 2) * k1)
            k3 = func(x_i + h / 2, y_i + (h / 2) * k2)
            k4 = func(x_new, y_i + h * k3)
            grid[x_new] = y_i + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4)
            y_i = grid[x_new]
            x_i = x_new
        return grid
    else:
        # Система уравнений
        for i in range(0, n):
            x_new = x_i + h
            k1 = np.zeros(func_cnt)
            k2 = np.zeros(func_cnt)
            k3 = np.zeros(func_cnt)
            k4 = np.zeros(func_cnt)
            for j in range(0, func_cnt):
                k1[j] = func[j](x_i, y_i)
            for j in range(0, func_cnt):
                k2[j] = func[j](x_i + h / 2, y_i + (h / 2) * k1)
            for j in range(0, func_cnt):
                k3[j] = func[j](x_i + h / 2, y_i + (h / 2) * k2)
            for j in range(0, func_cnt):
                k4[j] = func[j](x_new, y_i + h * k3)
            grid[x_new] = y_i + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4)
            y_i = grid[x_new]
            x_i = x_new
        return grid
