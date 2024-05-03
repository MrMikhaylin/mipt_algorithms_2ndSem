import matplotlib.pyplot as plt

def plot_iterations_vs_time(file1, file2, file3, file4, file5):
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
    
    data3 = []
    with open(file3, 'r') as f:
        for line in f:
            iterations, time = line.split()
            data3.append((int(iterations), float(time)))
    
    data4 = []
    with open(file4, 'r') as f:
        for line in f:
            iterations, time = line.split()
            data4.append((int(iterations), float(time)))
            
    data5 = []
    with open(file5, 'r') as f:
        for line in f:
            iterations, time = line.split()
            data5.append((int(iterations), float(time)))

    # Создать график
    plt.figure(figsize=(10, 6))

    # Нанести данные на график
    plt.plot(*zip(*data1), color='blue', label=file1)
    plt.plot(*zip(*data2), color='red', label=file2)
    plt.plot(*zip(*data3), color='green', label=file3)
    plt.plot(*zip(*data4), color='purple', label=file4)
    plt.plot(*zip(*data5), color='cyan', label=file5)
    
    # Настроить оси
    plt.xlabel('Количество элементов')
    plt.ylabel('Время исполнения (с)')
    plt.legend()
    plt.grid(True)

    plt.savefig('Combined.png')
    plt.close()

# Создаем объединение графиков
plot_iterations_vs_time('LSD', 'Merge', 'Hoar', 'Heap', 'stdlib_qsort')