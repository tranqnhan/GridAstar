#pragma once

#include <vector>

struct GridHeapItem {
    int id;
    float value;

    bool operator>(GridHeapItem item2) {
        return value > item2.value;
    }
};


class GridHeap {
public:
    GridHeap(int maxNumberOfItems);
    bool Push(int id, float value);
    int Pop();

    int Size() const;

private:
    std::vector<GridHeapItem> heapItems;
    std::vector<int> heapIdMap;
    int maxNumberOfItems;

    void Up(int heapIndex);
    void Down(int heapIndex);
    void Swap(int heapIndex1, int heapIndex2);
};

