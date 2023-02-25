#include <stdio.h>
#include <stdbool.h>

typedef struct list * _list;
typedef int list_elem;              //necesitaría opacar esto??

//CONTRUCTORES:
_list empty(void);     //crear una _lista vacía

_list addl(list_elem e, _list l);      //agregar un elemento a la _lista


//OPERACIONES:

bool is_empty(_list l);
//{- Devuelve True si l es vacía. -}

list_elem head(_list l);
//{- Devuelve el primer elemento de la _lista l -}
//{- PRE: not is_empty(l) -}

_list tail(_list l);
//{- Elimina el primer elemento de la _lista l -}
//{- PRE: not is_empty(l) -}

_list addr (_list l,list_elem e);
//{- agrega el elemento e al final de la _lista l. -}

unsigned int length(_list l);
//{- Devuelve la cantidad de elementos de la _lista l -}

_list concat(_list l, _list l0);
//{- Agrega al final de l todos los elementos de l0 en el mismo orden.-}

list_elem index(_list l, unsigned int n);
//{- Devuelve el n-ésimo elemento de la _lista l -}
//{- PRE: length(l) > n -}

_list take(_list l, unsigned int n);
//{- Deja en l sólo los primeros n elementos, eliminando el resto -}

_list drop(_list l, unsigned int n);
//{- Elimina los primeros n elementos de l -}

_list copy__list(_list l1);
//{- Copia todos los elementos de l1 en la nueva _lista l2 -}


//DESTROY:

_list destroy (_list l);