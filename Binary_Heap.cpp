#include "Binary_Heap.h"

void Binary_Heap::Clear()
{
    key.clear();
    pos.clear();
    satellite.clear();
}

void Binary_Heap::Insert(double k, int s)
{
    // Adjust the structures to fit new data
    if (s >= (int)pos.size())
    {
        pos.resize(s + 1, -1);
        key.resize(s + 1);

        // Recall at position 0 of unused satellite (if any)
        satellite.resize(s + 2);
    }

    // If satellite is already in the heap 
    else if (pos[s] != -1)
        throw "Error: satellite already in heap";

    int i;

    for (i = size++; i / 2 > 0 && GREATER(key[satellite[i / 2]], k); i /= 2)
    {
        satellite[i] = satellite[i / 2];
        pos[satellite[i]] = i;
    }

    satellite[i] = s;
    pos[s] = i;
    key[s] = k;
}

int Binary_Heap::Size() { return size; }

int Binary_Heap::DeleteMin()
{
    if (size == 0)
        throw "Error: empty heap";

    int min = satellite[1];
    int s_last = satellite[size--];

    int child;
    int i;

    for (i = 1, child = 2; child <= size; i = child, child *= 2)
    {
        if (child < size && GREATER(key[satellite[child]], key[satellite[child + 1]]))
        {
            child++;
        }

        if (GREATER(key[s_last], key[satellite[child]]))
        {
            satellite[i] = satellite[child];
            pos[satellite[child]] = i;
        }
        else 
            break;
    }

    satellite[i] = s_last;
    pos[s_last] = i;
    pos[min] = -1;
    return min;
}

void Binary_Heap::ChangeKey(double k, int s)
{
    Remove(s);
    Insert(k, s);
}

void Binary_Heap::Remove(int s)
{
    int i;

    for (i = pos[s]; i / 2 > 0; i /= 2)
    {
        satellite[i] = satellite[i / 2];
        pos[satellite[i]] = i;
    }

    satellite[1] = s;
    pos[s] = 1;

    DeleteMin();
}