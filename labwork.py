import matplotlib.pyplot as plt
def plot_graph(file_name, color):
    with open(file_name, 'r') as file:
        lines = file.readlines()
        x = []
        y = []
        for line in lines:
            data = line.split()
            x.append(int(data[0]))
            y.append(float(data[1]))

    plt.figure()
    plt.plot(x, y, color=color, label=file_name)
    plt.xlabel('Количество итераций')
    plt.ylabel('Время (с)')
    plt.title('График данных из файла ' + file_name)
    plt.grid(True)

    plt.savefig(file_name.replace('.txt', '.png'))
    plt.close()

def plot_iterations_vs_time(file1, file2):
    # Загрузить данные из файлов
    data1 = []
    with open(file1, 'r') as f:
        for line in f:
            iterations, time = line.split()
            data1.append((int(iterations), float(time)))

    data2 = []
    with open(file2, 'r') as f:
        for line in f:
            iterations, time = line.split()
            data2.append((int(iterations), float(time)))

    # Создать график
    plt.figure(figsize=(10, 6))

    # Нанести данные на график
    plt.plot(*zip(*data1), color='blue', label=file1)
    plt.plot(*zip(*data2), color='red', label=file2)

    # Настроить оси
    plt.xlabel('Количество итераций')
    plt.ylabel('Время исполнения (с)')
    plt.legend()
    plt.grid(True)

    plt.savefig('Combined.png')
    plt.close()

# Создаем первый, второй графики и их объединение
plot_graph('ArrayTest4.txt', 'blue')
plot_graph('ListTest4.txt', 'red')
plot_iterations_vs_time('ArrayTest4.txt', 'ListTest4.txt')