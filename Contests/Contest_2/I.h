/*!
\file
\brief Заголовочный файл с определением функций

 * Данный файл содержит в себе определения основных 
 * функций, используемых в программе
*/

#ifndef _I_H
#define _I_H

#include <stddef.h>

#define BUFF_SZE 4096                  //! максимальное количество запросов
#define NEW_CAP  10                    //! стратовый размер создаваемого стека

typedef struct SplayNode SplayNode;
typedef struct Stack Stack;

typedef SplayNode* elem_t;

/*!
 * \brief Структура Splay дерева
*/
struct SplayNode
{
    bool visited;                      //! Индентификатор прохождения вершины при удалении дерева
    char* key;                         //! Ключ     
    char* connect;                     //! Ключ-связка (пара)

    SplayNode* parent;
    SplayNode* left;
    SplayNode* right;
};

/*!
 * \brief Структура двух деревьев после разрезания split
*/
typedef struct TreePair
{
    SplayNode* first;
    SplayNode* second;
}TreePair;

/*!
 * \brief Структура стека для удаления дерева
*/
struct Stack
{
    SplayNode** data;
    size_t size;
    size_t capacity;
};

/*!
 * \brief Структура ошибок стека
*/
enum ERROR
{
    OK = 1,
    FAULT = 0
};

/*!
 * Конструктор нового стека
 * \param[in] Размер элемента стека
 * \param[in] Начальный размер стека
 * \param[out] Указатель на новый стек (его структуру)
*/
Stack* stack_ctor (size_t elem_size, size_t new_capacity);

/*!
 * Вставка в стек
 * \param[in] Указатель на стек
 * \param[in] Элемент для вставки
 * \param[out] Тип ошибки
*/
enum ERROR stack_push (Stack* stk, elem_t number);

/*!
 * Удаление из стека
 * \param[in] Указатель на стек
 * \param[out] Указатель на удаленный элемент
*/
elem_t stack_pop (Stack* stk);


/*!
 * Конструктор нового узла
 * \param[in] Значение нового узла
 * \param[in] Приоритет нового узла
 * \param[out] Указатель на новый корень (его структуру)
*/
SplayNode* construct_node (char* key, char* connect);

/*!
 * Правый поворот относительно заданного узла
 * \param[in] Указатель на узел, через который происходит поворот
 * \param[out] Указатель на корень, ставшим верхним после поворота
*/
SplayNode* rotate_right (SplayNode* node1);

/*!
 * Левый поворот относительно заданного узла
 * \param[in] Указатель на узел, через который происходит поворот
 * \param[out] Указатель на корень, ставшим верхним после поворота
*/
SplayNode* rotate_left (SplayNode* node1);

/*!
 * Поиск самого близкого значения, меньшего заданного
 * \param[in] Указатель на корень дерева
 * \param[in] Ключ (строка в реализации)
 * \param[out] Указатель на найденный узел (null, если такого нет)
*/
SplayNode* find_closest_lower (SplayNode* tree, char* key);

/*!
 * Разрезание дерева
 * \param[in] Указатель на корень дерева
 * \param[out] Структура разрезания 
*/
TreePair split (SplayNode* tree);

/*!
 * Функция splay относительно заданного узла
 * \param[in] Указатель на узел
 * \param[out] Указатель на корень дерева после splay
*/
SplayNode* splay (SplayNode* node);

/*!
 * Вставка нового узла
 * \param[in] Указатель на корень дерева
 * \param[in] Ключ (в реализации - строка)
 * \param[in] Пара к ключу (особенность реализации)
 * \param[out] Указатель на корень дерева
*/
SplayNode* insert (SplayNode* tree, char* key, char* connect);

/*!
 * Вставка нового узла
 * \param[in] Указатель на корень дерева
 * \param[in] Ключ (в реализации - строка)
 * \param[in] Пара к ключу (особенность реализации)
 * \param[out] Указатель на корень дерева
*/
SplayNode* exists (SplayNode* tree, char* request);

/*!
 * Последовательный поиск ключа (строки) в двух splay-деревьях
 * \param[in] Указатель на корень первого дерева
 * \param[in] Указатель на корень второго дерева
 * \param[in] Искомый ключ
 * \param[out] Пара к найденному ключу
*/
char* search (SplayNode** pilot_tree, SplayNode** aircraft_tree, char* request);

/*!
 * Удаление дерева
 * \param[in] Указатель на корень дерева
*/
void delete_tree (SplayNode* tree);


#endif