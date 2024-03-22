import matplotlib.pyplot as plt

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
    plt.plot(*zip(*data1), color='green', label=file1)
    plt.plot(*zip(*data2), color='purple', label=file2)
    
    # Настроить оси
    plt.xlabel('Количество элементов')
    plt.ylabel('Время исполнения (с)')
    plt.legend()
    plt.grid(True)

    plt.savefig('Combined.png')
    plt.close()

# Создаем объединение графиков
plot_iterations_vs_time('LSD', 'MSD')