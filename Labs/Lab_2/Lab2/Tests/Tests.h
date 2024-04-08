#ifndef TESTS_H_
#define TESTS_H_

/*Надо запушить 10^6 интов, потом удалить половину элементов и запушить четверть - останется 750000 интов. 
Повторять удаление половины и вставку четверти, пока не останется в стеке меньше 100000 элементов (получится 9 итераций).*/
#define TEST_ONE(T, time_point)                                 \
do                                                              \
{                                                               \
    struct T* stack = stack_ctr ();                             \
    assert (stack != NULL);                                     \
                                                                \
    elem_t element = 0;                                         \
                                                                \
    clock_t begin = clock ();                                   \
                                                                \
    for (size_t i = 0; i < MILLION; i++)                        \
    {                                                           \
        element = (rand()%(2000001)*100)/13;                    \
                                                                \
        push (stack, element);                                  \
    }                                                           \
                                                                \
    for (size_t i = 0; i < 9; i++)                              \
    {                                                           \
        size_t number_of_elements = stack->size;                \
                                                                \
        for (size_t j = 0; j < number_of_elements/2; j++)       \
        {                                                       \
            pop (stack);                                        \
        }                                                       \
                                                                \
        for (size_t k = 0; k < number_of_elements/4; k++)       \
        {                                                       \
            element = (rand()%(2000001)*100)/13;                \
                                                                \
            push (stack, element);                              \
        }                                                       \
    }                                                           \
                                                                \
    clock_t end = clock ();                                     \
                                                                \
    *time_point = (double) (end - begin)/CLOCKS_PER_SEC;        \
}                                                               \
while(0)

/*Надо запушить 10^6 интов, потом 100 раз удалить 10000 элементов и добавить столько же. 
Далее как в первом тесте провести 9 итераций удаления-вставки и снова 100 раз удалить 10000 элементов и добавить столько же.*/
#define TEST_TWO(T, time_point)                                 \
do                                                              \
{                                                               \
    struct T* stack = stack_ctr ();                             \
    assert (stack != NULL);                                     \
                                                                \
    elem_t element = 0;                                         \
                                                                \
    clock_t begin = clock ();                                   \
                                                                \
    for (size_t i = 0; i < MILLION; i++)                        \
    {                                                           \
        element = (rand()%(2000001)*100)/13;                    \
                                                                \
        push (stack, element);                                  \
    }                                                           \
                                                                \
    for (size_t i = 0; i < 100; i++)                            \
    {                                                           \
        for (size_t k = 0; k < 10000; k++)                      \
        {                                                       \
            pop (stack);                                        \
        }                                                       \
                                                                \
        for (size_t k = 0; k < 10000; k++)                      \
        {                                                       \
            element = (rand()%(2000001)*100)/13;                \
                                                                \
            push (stack, element);                              \
        }                                                       \
    }                                                           \
                                                                \
    for (size_t i = 0; i < 9; i++)                              \
    {                                                           \
        size_t number_of_elements = stack->size;                \
                                                                \
        for (size_t j = 0; j < number_of_elements/2; j++)       \
        {                                                       \
            pop (stack);                                        \
        }                                                       \
                                                                \
        for (size_t k = 0; k < number_of_elements/4; k++)       \
        {                                                       \
            element = (rand()%(2000001)*100)/13;                \
                                                                \
            push (stack, element);                              \
        }                                                       \
    }                                                           \
                                                                \
    for (size_t i = 0; i < 100; i++)                            \
    {                                                           \
        for (size_t k = 0; k < 10000; k++)                      \
        {                                                       \
            pop (stack);                                        \
        }                                                       \
                                                                \
        for (size_t k = 0; k < 10000; k++)                      \
        {                                                       \
            element = (rand()%(2000001)*100)/13;                \
                                                                \
            push (stack, element);                              \
        }                                                       \
    }                                                           \
                                                                \
    clock_t end = clock ();                                     \
                                                                \
    *time_point = (double) (end - begin)/CLOCKS_PER_SEC;        \
}                                                               \
while(0)

/*Надо научиться средствами языка генерировать случайные числа из множества {1,2}. 
Далее сначала довести размер стека до миллиона, а потом выполнить миллион инструкций следующего вида: каждое выпадение единицы добавлять элемент, а на двойку - попать из стека. 
Засекать время после доведения размера стека до миллиона.*/
#define TEST_THREE(T, time_point)                               \
do                                                              \
{                                                               \
    struct T* stack = stack_ctr ();                             \
    assert (stack != NULL);                                     \
                                                                \
    elem_t element = 0;                                         \
                                                                \
    for (size_t i = 0; i < MILLION; i++)                        \
    {                                                           \
        element = (rand()%(2000001)*100)/13;                    \
                                                                \
        push (stack, element);                                  \
    }                                                           \
                                                                \
    clock_t begin = clock ();                                   \
                                                                \
    size_t data = 0;                                            \
                                                                \
    for (size_t i = 0; i < MILLION; i++)                        \
    {                                                           \
        data = 1 + rand()%2;                                    \
                                                                \
        if (data == 1)                                          \
        {                                                       \
            element = (rand()%(2000001)*100)/13;                \
                                                                \
            push (stack, element);                              \
        }                                                       \
                                                                \
        else                                                    \
            pop (stack);                                        \
    }                                                           \
                                                                \
    clock_t end = clock ();                                     \
                                                                \
    *time_point = (double) (end - begin)/CLOCKS_PER_SEC;        \
}                                                               \
while(0)

#define TEST_FOUR(T, file_out)                                  \
do                                                              \
{                                                               \
    struct T* stack = stack_ctr ();                             \
    assert (stack != NULL);                                     \
                                                                \
    FILE* file = fopen (file_out, "w");                         \
    assert (file != NULL);                                      \
                                                                \
    elem_t element = 0;                                         \
    size_t i = 0;                                               \
                                                                \
    clock_t begin = clock ();                                   \
    clock_t end = 0;                                            \
                                                                \
    while (i < MILLION)                                         \
    {                                                           \
        for (int j = 0; j < 1000; j++)                          \
        {                                                       \
            assert (push (stack, j) == OK);                     \
                                                                \
            i++;                                                \
        }                                                       \
                                                                \
        end = clock ();                                         \
                                                                \
        fprintf (file, "%d  %lf\n", i, (double) (end - begin)/CLOCKS_PER_SEC); \
    }                                                           \
                                                                \
    stack_dtr (stack);                                          \
                                                                \
    fclose (file);                                              \
}                                                               \
while(0)


#endif