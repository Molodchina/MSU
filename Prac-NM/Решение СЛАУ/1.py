# coding=utf-8
import math
import numpy as np


# Вычисление решения СЛАУ методом Гаусса
# СЛАУ задается в виде матрицы data размером n на n
def gauss(data, n):
    data_copy = np.copy(data)

    for i in range(0, n):
        if data_copy[i][i] == 0:
            for j in range(i + 1, n):
                if data_copy[j][i] != 0:
                    data_copy[[j, i]] = data_copy[[i, j]]
                    break
        data_copy[i] /= data_copy[i][i]
        for j in range(i + 1, n):
            data_copy[j] -= data_copy[i] * data_copy[j][i]

    x = data_copy[:, n]
    for i in range(n - 1, -1, -1):
        for j in range(n - 1, i, -1):
            x[i] -= data_copy[i][j] * x[j]
    return x


# Вычисление решения СЛАУ методом Гаусса с выбором главного элемента
# СЛАУ задается в виде матрицы data размером n на n
def gauss_diag(data, n):
    data_copy = np.copy(data)
    idx = np.array(range(0, n))
    for i in range(0, n):
        if data_copy[i][i] == 0:
            for j in range(i + 1, n):
                if data_copy[j][i] != 0:
                    data_copy[[j, i]] = data_copy[[i, j]]
                    break
        col_max = i + np.argmax(abs(data_copy[i][i:n]))
        idx[i], idx[col_max] = idx[col_max], idx[i]
        data_copy[:, [i, col_max]] = data_copy[:, [col_max, i]]
        data_copy[i] /= data_copy[i][i]
        for j in range(i + 1, n):
            data_copy[j] -= data_copy[i] * data_copy[j][i]
    x = data_copy[:, n]
    for i in range(n - 1, -1, -1):
        for j in range(n - 1, i, -1):
            x[i] -= data_copy[i][j] * x[j]

    res = np.array(list(zip(x, idx)))
    res = res[res[:, 1].argsort()]
    x = res[:, 0]
    return x


# Функция, вычисляющая определитель матрицы data, размер которой n на n
def det_calc(data, n):
    det = 1
    data_copy = np.copy(data[:, :n])
    for i in range(0, n):
        if data_copy[i][i] == 0:
            for j in range(i + 1, n):
                if data_copy[j][i] != 0:
                    data_copy[[j, i]] = data_copy[[i, j]]
                    det *= -1
                    break
            return 0
        det *= data_copy[i][i]
        for j in range(i + 1, n):
            data_copy[j] -= data_copy[i] * data_copy[j][i] / data_copy[i][i]
    return det


# Вычисление обратной матрицы к матрице data, размер которой n на n
def inverse(data, n):
    data_copy = np.hstack((np.copy(data[:, :n]), np.identity(n)))
    for i in range(0, n):
        if data_copy[i][i] == 0:
            for j in range(i + 1, n):
                if data_copy[j][i] != 0:
                    data_copy[[j, i]] = data_copy[[i, j]]
                    break
        data_copy[i] /= data_copy[i][i]
        for j in range(i + 1, n):
            data_copy[j] -= data_copy[i] * data_copy[j][i]
    for j in range(n - 1, 0, -1):
        for i in range(j - 1, -1, -1):
            data_copy[i] -= data_copy[j] * data_copy[i][j]
    inv = data_copy[:, n:]
    return inv


# Вычисление числа обусловленности для квадратной матрицы data, со стороной n
def mat_norm(data, n):
    max = 0
    for i in range(0, n):
        max_i = 0

    for j in range(0, n):
        max_i += abs(data[i][j])
    if max_i > max:
        max = max_i
    return max


# Проверка матрицы data размеров n на n
# на самосопряженность и положительную определенность
# параметр функции pr_par отвечает за вывод (если pr_par = 1),
# либо за возврат значения (1, если матрица самосопр. и полож. опред.)
# функцией (pr_par = 0)
def herm_and_pos(data, n, pr_par):
    herm = 0
    pos_def = 1
    data_copy = np.copy(data[:, :n])
    # Проверка самосопряжённости
    if np.array_equal(data_copy, data_copy.T):
        herm = 1

    # Проверка матрицы на положительную определенность
    if data_copy[0][0] > 0:
        for i in range(2, n + 1):
            corn_minor = det_calc(data_copy[:i, :i], i)
            if corn_minor <= 0:
                pos_def = 0
                break
    if pr_par == 1:
        if (herm == 0) and (pos_def == 0):
            print("\nМатрица коэффициентов данной системы не "
                  "является самосопряжённой и положительно определённой")
        elif (herm == 0) and (pos_def == 1):
            print("\nМатрица коэффициентов данной системы не "
                  "является самосопряжённой, но является положительно "
                  "определённой")
        elif (herm == 1) and (pos_def == 1):
            print("\nМатрица коэффициентов данной системы "
                  "является самосопряжённой, но не "
                  "является положительно "
                  "определённой")
        else:
            print("\nМатрица коэффициентов данной системы "
                  "является самосопряжённой и положительно"
                  "определённой")
    else:
        return herm & pos_def


# Метод верхней релаксации
def relax(data, n, eps, w):
    data_copy = np.copy(data[:, :n])
    f = np.copy(data[:, n])
    if herm_and_pos(data_copy, n, 0) == 1:
        f = data_copy.T @ f
        data_copy = data_copy.T @ data_copy
        cond_num = mat_norm(data_copy, n) * mat_norm(inverse(data, n), n)
        print("\nЧисло обусловленности полученной "
              "симметрической и положительно определённой "
              "матрицы: %.4f" % cond_num)
    else:
        cond_num = mat_norm(data_copy, n) * mat_norm(inverse(data_copy, n), n)
        print("\nЧисло обусловленности: %.4f" % cond_num)

    x_new = np.zeros(n)
    discrep_y = eps + 1
    iter = 0
    first_m = np.zeros((n, n))
    for i in range(0, n):
        first_m[i][i] = data_copy[i][i] / w
    first_m += np.tril(data_copy, k=-1)
    if det_calc(first_m, n) == 0:
        return 1
    first_m = inverse(first_m, n)
    while (eps <= discrep_y) and (iter <= 500000):
        iter += 1
        x_prev = np.copy(x_new)
        second_m = f - (data_copy @ x_prev)
        x_new = (first_m @ second_m) + x_prev
        discrep_y = (np.linalg.norm(f - (data_copy @ x_new), 2)) * \
                    np.linalg.norm(np.linalg.inv(data_copy), 2)
    if iter > 500000:
        print("\nКол-во итераций превысило 500000")
    else:
        print("\nРешения, полученные с помощью"
              " метода верхней релаксации:")
        for i in range(0, n):
            print("x_%d = %.7f" % (i + 1, x_new[i]))
        print("\nКол-во итераций:", iter)


# Вычисление элементов матрицы по формуле
def formula(n, m):
    x = 50
    data = np.zeros((n, n + 1))
    for i in range(1, n + 1):
        data[i - 1][n] = x * math.exp(x / i) * math.cos(x / i)
        for j in range(1, n + 1):
            q = 1.001 - 2 * m * 0.001
            if i == j:
                data[i - 1][j - 1] = (q - 1) ** (i + j)
            else:
                data[i - 1][j - 1] = q ** (i + j) + 0.1 * (j - i)
    return data


# Тело основной функции
global matrix
choice = 1
while choice == 1:  # Бесконечный цикл вычислений решений СЛАУ
    print("\nКаким методом Вы хотите решать "
          "систему?\n1 - методы Гаусса (1 подзадание)\n2 - метод верхней "
          "релаксации (2 подзадание)")
    task_num = int(input("\nВведите соответствующий номер: "))
    if (task_num < 1) or (task_num > 2):
        print("\nНеправильный номер")
        continue
    print("\nКак Вы хотите ввести систему: "
          "1 - из файла, 2 - с помощью формулы?")
    mode = int(input("\nВведите соответствующий номер: "))
    if mode == 1:  # Если ввод системы с из файла, названного "sys"+"№"+".txt"
        sys_num = int(input("\nНомер системы, "
                            "которую Вы хотите ввести (1/2/3): "))
        if (sys_num > 6) or (sys_num < 1):
            print("\nНеправильный номер системы\n")
            continue
        else:
            file_name = str("sys" + str(sys_num) + ".txt")
            f = open(file_name, 'r')
            file_contents = f.read()
            print("\nВы выбрали систему\n", file_contents, sep='')
            matrix = np.loadtxt(file_name)
    elif mode == 2:  # Если ввод системы с помощью формулы
        print()
        n = 100
        m = 6
        matrix = formula(n, m)
        print("\nПолученная система:")
        for i in range(0, n):
            for j in range(0, n):
                print("%*.4f " % (7, matrix[i][j]), end="")
            print("| %*.4f " % (7, matrix[i][n]))
    else:
        print("\nНеправильный способ ввода")
        continue

    cnt = matrix.shape[0]

    det = det_calc(matrix, cnt)
    print("\nОпределитель: %.7f" % det)
    if det == 0:  # Если определитель матрицы maxtrix = 0
        print("\nДанная система вырождена, "
              "поэтому имеет бесконечно много решений")
    elif task_num == 1:  # Если был выбран поиск решений СЛАУ
                            # с помощью метода Гаусса
        inv = inverse(matrix, cnt)
        print("\nОбратная матрица:")
        for i in range(0, cnt):
            for j in range(0, cnt):
                print("%*.4f " % (7, inv[i][j]), end="")
            print()

        cond_num = mat_norm(matrix, cnt) * mat_norm(inv, cnt)
        print("\nЧисло обусловленности: %.4f" % cond_num)
        x_gauss = gauss(matrix, cnt)
        print("\nРешения, полученные с помощью метода Гаусса:")
        for i in range(0, cnt):
            print("x_%d = %.7f" % (i + 1, x_gauss[i]))
        x_gauss_m_el = gauss_diag(matrix, cnt)
        print("\nРешения, полученные с помощью"
              " метода Гаусса с выбором главного элемента:")
        for i in range(0, cnt):
            print("x_%d = %.7f" % (i + 1, x_gauss_m_el[i]))
    else:  # Если был выбран поиск решений СЛАУ
                # с помощью метода Релаксации
        choice_2 = 1
        herm_and_pos(matrix, cnt, 1)
        cond_num = mat_norm(matrix, cnt) * mat_norm(inverse(matrix, cnt), cnt)
        print("\nЧисло обусловленности: %.4f" % cond_num)
        while choice_2 == 1:  # Запускаем бесконечный цикл,
                                # завершающийся при желании пользователя
            try:
                eps = float(input("\nВведите положительную точность eps, "
                                  "с которой Вы хотите получить решения: "))
                if eps <= 0:
                    raise RuntimeError
            except:
                eps = -1
                while eps <= 0:
                    try:
                        eps = float(input("\nВведена неправильная точность."
                                          " Попробуйте еще раз:"))
                    except:
                        eps = -1
            try:
                w = float(input("\nВведите положительный итерационный параметр w\n "
                                "(для симметрической положительно определенной "
                                "матрицы системы следует выбирать 0<w < 2): "))
                if w <= 0:
                    raise RuntimeError
            except:
                w = -1
                while w <= 0:
                    try:
                        w = float(input("\nВведён неправильный параметр."
                                        " Попробуйте ещё раз:"))
                    except:
                        w = -1
            relax(matrix, cnt, eps, w)

            try:
                choice_2 = int(input("\n\nВведите 1, если хотите заново протестировать"
                                     " метод при других параметрах,0 - если "
                                     "хотите закончить тестирование:"))
                if (choice_2 != 0) and (choice_2 != 1):
                    raise RuntimeError
            except:
                choice_2 = -1
                while (choice_2 != 0) and (choice_2 != 1):
                    try:
                        choice_2 = int(input("\nВведен неправильныйномер."
                                             " Попробуйте еще раз: "))
                    except:
                        choice_2 = -1
        print("\n\nТестирование метода верхней релаксации закончено")
    try:
        choice = int(input("\n\nВведите 1, если хотите заново "
                           "запустить программу, 0 - если хотите выйти: "))
        if (choice != 0) and (choice != 1):
            raise RuntimeError
    except:
        choice = -1
        while (choice != 0) and (choice != 1):
            try:
                choice = int(input("\nВведён неправильный номер. Попробуйте ещё раз: "))
            except:
                choice = -1
print("\nВыход")
