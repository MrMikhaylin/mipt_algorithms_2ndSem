/*!
\file
\brief Заголовочный файл с определением функций

 * Данный файл содержит в себе определения основных 
 * функций, используемых в программе
*/

#ifndef _G_H
#define _G_H

#include <stdio.h>


#define COMMAND_LEN 10          //! максимальная длина вводимой строки
#define MOD         1000000000  //! ограничение на приоритет узла

#define STRLEN_(x) #x           //! блок define для ограничения ввода для функции scanf
#define STRLEN(x) STRLEN_(x)

enum ERROR                      //! блок значений ошибок
{
    OK = 1,
    NONE = 0
};

typedef struct TreapNode TreapNode;

/*!
 * \brief Структура Декартова дерева
*/
struct TreapNode
{
    int priority;
    int key;
    int subtree_size;
    
    TreapNode* parent;
    TreapNode* left;
    TreapNode* right;
};

/*!
 * \brief Структура двух деревьев после разрезания split
*/
typedef struct TreePair
{
    TreapNode* first;
    TreapNode* second;
}TreePair;

/*!
 * Возвращает сумму поддерева аргумента
 * \param[in] Указатель на рассматриваемый узел
 * \param[out] Сумма поддерева узла
*/
int get_size (TreapNode* node);

/*!
 * Обновляет сумму поддерева аргумента
 * \param[in] Указатель на рассматриваемый узел
*/
void update (TreapNode* node);

/*!
 * Вычисляет k-порядковую статистику в дереве
 * \param[in] Указатель на корень дерева
 * \param[in] Искомая статистика
 * \param[in] Указатель на область памяти, куда необходимо вернуть результат работы функции
 * \param[out] Тип ошибки ERROR
*/
enum ERROR kstat (TreapNode* tree, int k, int* value);

/*!
 * Находит наименьший узел дерева среди больших заданного узла (выводит none если таких нет)
 * \param[in] Указатель на корень дерева
 * \param[in] Узел
 * \param[in] Указатель на область памяти, куда необходимо вернуть результат работы функции
 * \param[out] Тип ошибки ERROR
*/
enum ERROR next (TreapNode* tree, int value, int* next_value);

/*!
 * Находит набольший узел дерева среди меньших заданного узла (выводит none если таких нет)
 * \param[in] Указатель на корень дерева
 * \param[in] Узел
 * \param[in] Указатель на область памяти, куда необходимо вернуть результат работы функции
 * \param[out] Тип ошибки ERROR
*/
enum ERROR prev (TreapNode* tree, int value, int* prev_value);

/*!
 * Конструктор нового узла
 * \param[in] Значение нового узла
 * \param[in] Приоритет нового узла
 * \param[out] Указатель на новый корень (его структуру)
*/
TreapNode* construct_node (int new_value, int new_priority);

/*!
 * Разрезание дерева.
 * \param[in] Указатель на корень дерева
 * \param[in] Ключ по которому происходит разрезание
 * \param[out] Структура разрезания 
*/
TreePair split (TreapNode* tree, int key);

/*!
 * Слияние двух деревьев
 * \param[in] Указатель на корень первого дерева
 * \param[in] Указатель на корень второго дерева
 * \param[out] Указатель на итоговое дерево после слияния 
*/
TreapNode* merge (TreapNode* t1, TreapNode* t2);

/*!
 * Проверка на наличие узла в дереве
 * \param[in] Указатель на корень дерева
 * \param[in] Значение искомого корня
 * \param[out] Указатель на искомый корень, null, если узла с заданным значением в дереве нет 
*/
TreapNode* exists (TreapNode* tree, int searched_value);

/*!
 * Вставка узла
 * \param[in] Указатель на корень дерева
 * \param[in] Значение вставляемого узла
 * \param[in] Приоритет вставляемого узла
 * \param[out] Указатель на корень дерева
*/
TreapNode* insert_number (TreapNode* tree, int new_value, int new_priority);

/*!
 * Удаление узла
 * \param[in] Указатель на корень дерева
 * \param[in] Значение удаляемого узла
 * \param[out] Указатель на корень дерева
*/
TreapNode* delete_number (TreapNode* tree, int deleted_value);

/*!
 * Метод для работы с деревом
 * \param[in] Указатель на корень дерева
 * \param[in] Команда для обработки
 * \param[in] Считанное число (идет в паре с коммандой)
 * \param[in] Указатель на выходной файл
 * \param[out] Указатель на корень дерева 
*/
TreapNode* match_the_tree (TreapNode* tree, char* command, int curr_value, FILE* file_out);

/*!
 * Удаление дерева
 * \param[in] Указатель на корень дерева
*/
void delete_tree (TreapNode* tree);


#endif
