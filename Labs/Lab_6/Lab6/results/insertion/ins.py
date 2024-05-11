import matplotlib.pyplot as plt

def plot_iterations_vs_time(file1, file2, file3):
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

    # Создать график
    plt.figure(figsize=(10, 6))

    # Нанести данные на график
    plt.plot(*zip(*data1), color='purple', label=file1)
    plt.plot(*zip(*data2), color='red', label=file2)
    plt.plot(*zip(*data3), color='green', label=file3)
    
    # Настроить оси
    plt.xlabel('Количество элементов')
    plt.ylabel('Время исполнения (с)')
    plt.title('Вставка')
    plt.legend()
    plt.grid(True)

    plt.savefig('../insertion.png')
    plt.close()

# Создаем объединение графиков
plot_iterations_vs_time('Treap', 'AVL', 'Splay')