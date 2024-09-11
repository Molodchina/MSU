import numpy as np
import math
import matplotlib.pyplot as plt

global f, p, q, a_1, a_2, a, c_1, b_1, b_2, b, c_2, x_g, y_g
# p = p(x) - функция при первой производной
# q = q(x) - функция при y
# f - правая часть уравнения
# a_1, a_2 - коэффициенты в 1 дополнительном условии
# b_1, b_2 - коэффициенты в 2 дополнительном условии
# a, b - левая и правая границы
# c_1, c_2 - правая часть доп. условий
# x_g - сетка
# y_g - сеточная функция
# y’’ - 0.5xy’ + y = 2, y(0.4) = 1.2, y(0.7) + 2y’(0.7) = 1.4
# Решения, представимого в элементарных функциях, не существует


def p_1(x):
    return 3


def q_1(x):
    return -1 / x


def f_1(x):
    return x + 1


def probl_1():
    global f, p, q, a_1, a_2, a, c_1, b_1, b_2, b, c_2
    f = f_1
    p = p_1
    q = q_1
    a_1 = 0
    a_2 = 1
    a = 1.2
    c_1 = 1
    b_1 = 2
    b_2 = -1
    b = 1.5
    c_2 = 0.5


# y’’ + y’ = 1, y’(0) = 0, y(1) = 1
# Решение: y = x + exp(-x) – 1 / exp(1)
def sol_2(x):
    y = list()
    for i in x:
        y.append(i + math.exp(-i) - 1 / math.exp(1))
    return y


def p_2(x):
    return 1


def q_2(x):
    return 0


def f_2(x):
    return 1


def probl_2():
    global f, p, q, a_1, a_2, a, c_1, b_1, b_2, b, c_2
    f = f_2
    p = p_2
    q = q_2
    a_1 = 0
    a_2 = 1
    a = 0
    c_1 = 0
    b_1 = 1
    b_2 = 0
    b = 1
    c_2 = 1


def solution_task(n):
    # Решение задачи с помощью метода прогонки
    global x_g, y_g
    h = (b - a) / n
    x_i = a
    x_g = np.zeros(n + 1)
    x_g[0] = x_i
    y_g = np.zeros(n + 1)
    # Прогоночные коэффициенты
    alpha = np.zeros(n + 1)
    beta = np.zeros(n + 1)
    alpha[1] = -a_2 / (a_1 * h - a_2)
    beta[1] = c_1 * h / (a_1 * h - a_2)
    for i in range(1, n):
        x_i += h
        x_g[i] = x_i
        # Коэффициенты трёхдиагональной СЛАУ
        A_i = 1 / (h * h) - p(x_i) / (2 * h)
        C_i = 2 / (h * h) - q(x_i)
        B_i = 1 / (h * h) + p(x_i) / (2 * h)
        F_i = f(x_i)
        # Вычисление прогоночных коэффициентов по реккурентным формулам
        alpha[i + 1] = B_i / (C_i - A_i * alpha[i])
        beta[i + 1] = (beta[i] * A_i - F_i) / (C_i - A_i * alpha[i])
    # Обратная прогонка
    y_g[n] = (b_2 * beta[n] + c_2 * h) / (b_2 * (1 - alpha[n]) + b_1 * h)
    for i in range(n, 0, -1):
        y_g[i - 1] = y_g[i] * alpha[i] + beta[i]
    x_g[n] = b
