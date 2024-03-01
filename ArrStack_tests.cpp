#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "ArrStack_functions.h"
#include "ArrStack_tests.h"

double go_test_one (struct ArrStack* st)
{
    /*Надо запушить 10^6 интов, потом удалить половину элементов и запушить четверть - останется 750000 интов. 
    Повторять удаление половины и вставку четверти, пока не останется в стеке меньше 100000 элементов (получится 9 итераций).*/

    assert (st != nullptr);

    elem_t value = 0;

    clock_t begin = clock ();

    for (size_t i = 0; i < MILLION; i++)
    {
        value = (rand()%(2000001)*100)/13;
        
        push (st, value);
    }

    for (size_t i = 0; i < 9; i++)
    {
        size_t number_of_elements = st->fcp;

        for (size_t j = 0; j < number_of_elements/2; j++)
        {
            pop (st);
        }

        for (size_t k = 0; k < number_of_elements/4; k++)
        {
            value = (rand()%(2000001)*100)/13;
        
            push (st, value);
        }
    }
    
    clock_t end = clock ();

    return (double) (end - begin)/CLOCKS_PER_SEC;
}

double go_test_two (struct ArrStack* st)
{
    /*Надо запушить 10^6 интов, потом 100 раз удалить 10000 элементов и добавить столько же. 
    Далее как в первом тесте провести 9 итераций удаления-вставки и снова 100 раз удалить 10000 элементов и добавить столько же.*/

    assert (st != nullptr);

    elem_t value = 0;

    clock_t begin = clock ();

    for (size_t i = 0; i < MILLION; i++)
    {
        value = (rand()%(2000001)*100)/13;
        
        push (st, value);
    }

    for (size_t i = 0; i < 100; i++)
    {
        for (size_t k = 0; k < 10000; k++)
        {
            pop (st);
        }

        for (size_t k = 0; k < 10000; k++)
        {
            value = (rand()%(2000001)*100)/13;
        
            push (st, value);
        }
    }

    for (size_t i = 0; i < 9; i++)
    {
        size_t number_of_elements = st->fcp;

        for (size_t j = 0; j < number_of_elements/2; j++)
        {
            pop (st);
        }

        for (size_t k = 0; k < number_of_elements/4; k++)
        {
            value = (rand()%(2000001)*100)/13;
        
            push (st, value);
        }
    }

    for (size_t i = 0; i < 100; i++)
    {
        for (size_t k = 0; k < 10000; k++)
        {
            pop (st);
        }

        for (size_t k = 0; k < 10000; k++)
        {
            value = (rand()%(2000001)*100)/13;
        
            push (st, value);
        }
    }

    clock_t end = clock ();

    return (double) (end - begin)/CLOCKS_PER_SEC;
}

double go_test_three (struct ArrStack* st)
{
    /*Надо научиться средствами языка генерировать случайные числа из множества {1,2}. 
    Далее сначала довести размер стека до миллиона, а потом выполнить миллион инструкций следующего вида: каждое выпадение единицы добавлять элемент, а на двойку - попать из стека. 
    Засекать время после доведения размера стека до миллиона.*/

    assert (st != nullptr);

    elem_t value = 0;

    for (size_t i = 0; i < MILLION; i++)
    {
        value = (rand()%(2000001)*100)/13;
    
        push (st, value);
    }

    clock_t begin = clock ();

    size_t data = 0;

    for (size_t i = 0; i < MILLION; i++)
    {
        data = 1 + rand()%2;

        if (data == 1)
        {
            value = (rand()%(2000001)*100)/13;
        
            push (st, value);
        }

        else
            pop (st);
    }

    clock_t end = clock ();

    double time_spent = (double) (end - begin)/CLOCKS_PER_SEC;

    return time_spent; 
}

void test_four ()
{
    struct ArrStack* stack = stack_ctr (1, sizeof (elem_t));
    assert (stack != nullptr);
    
    FILE* file = fopen ("ArrayTest4.txt", "w");
    assert (file != nullptr);

    elem_t value = 0;
    
    double time_spent = 0;

    size_t i = 0;

    clock_t begin = clock ();
    clock_t end = 0;

    while (i < MILLION)
    {   
        for (int j = 0; j < 1000; j++)
        {
            assert (push (stack, j) == OK);

            i++;
        }
        
        end = clock ();

        time_spent = (double) (end - begin)/CLOCKS_PER_SEC;

        fprintf (file, "%d  %lf\n", i, time_spent);
    }

    stack_dtr (stack);

    fclose (file);
}