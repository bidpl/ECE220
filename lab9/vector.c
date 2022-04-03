#include "vector.h"
#include <stdlib.h>


vector_t * createVector(int initialSize)
{
    vector_t *vector = malloc(sizeof(vector_t));

    vector->size = 0;
    vector->maxSize = initialSize;

    vector->array = malloc(initialSize * sizeof(int));

    return vector;
}

void destroyVector(vector_t * vector)
{
    free(vector->array);
    free(vector);
}

void resize(vector_t * vector)
{
    vector->array = realloc(vector->array, vector->maxSize * 2 * sizeof(int));
    vector->maxSize *= 2;
}

void push_back(vector_t * vector, int element)
{
    // If vector is full, resize vector
    if(vector->size == vector->maxSize) {
        resize(vector);
    }

    vector->array[vector->size] = element;
    vector->size++;
}

int pop_back(vector_t * vector)
{
    // If no items, return 0
    if(vector->size == 0) {
        return 0;
    }

    // Decrement size
    vector->size--;

    // Return item corresponding to preious size
    return vector->array[vector->size];
}

int access(vector_t * vector, int index)
{
    return vector->array[index];
}

