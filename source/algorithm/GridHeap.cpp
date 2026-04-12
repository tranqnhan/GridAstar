#include "GridHeap.hpp"
#include <algorithm>


GridHeap::GridHeap(int maxNumberOfItems) : maxNumberOfItems(maxNumberOfItems) {
    this->heapItems.reserve(maxNumberOfItems);
    this->heapIdMap.resize(maxNumberOfItems, maxNumberOfItems);
}


bool GridHeap::Push(int id, float value) {
    bool result = true;

    const int heapIdIndex = this->heapIdMap[id];

    if (heapIdIndex != this->maxNumberOfItems) {
        if (this->heapItems[heapIdIndex].value > value) {
            this->heapItems[heapIdIndex].value = value;
            this->Up(heapIdIndex);
        } else {
            result = false;
        }
    } else {
        this->heapItems.emplace_back(id, value);
        this->heapIdMap[id] = this->heapItems.size() - 1; 
        this->Up(this->heapItems.size() - 1);
    }

    return result;
}


int GridHeap::Pop() {
    int result = this->heapItems.front().id;
    
    this->Swap(0, this->heapItems.size() - 1);
    this->heapIdMap[this->heapItems.back().id] = this->maxNumberOfItems;
    this->heapItems.pop_back();

    this->Down(0);

    return result;
}


int GridHeap::Size() const {
    return this->heapItems.size();
}


void GridHeap::Clear() {
    std::fill(this->heapIdMap.begin(), this->heapIdMap.end(), this->maxNumberOfItems);
    this->heapItems.clear();
}


void GridHeap::Up(int heapIndex) {
    int parentIndex = (heapIndex - 1) / 2;

    while (heapIndex != 0 && this->heapItems[parentIndex] > this->heapItems[heapIndex]) {    
        this->Swap(parentIndex, heapIndex);
        heapIndex = parentIndex;
        parentIndex = (heapIndex - 1) / 2;
    }
}


void GridHeap::Down(int heapIndex) {
    int leftIndex;
    int rightIndex;
    int nextIndex; 

    while (true) {
        leftIndex = heapIndex * 2 + 1;
        if (leftIndex >= this->heapItems.size()) {
            break;
        }

        rightIndex = heapIndex * 2 + 2;
        if (rightIndex >= this->heapItems.size()) {
            nextIndex = leftIndex;
        } else {
            nextIndex = this->heapItems[leftIndex] > this->heapItems[rightIndex] ? rightIndex : leftIndex;
        }
        
        if (this->heapItems[heapIndex] > this->heapItems[nextIndex]) {
            this->Swap(nextIndex, heapIndex);
            heapIndex = nextIndex;
        } else {
            break;
        }
    }
}
 

void GridHeap::Swap(int heapIndex1, int heapIndex2) {
    this->heapIdMap[this->heapItems[heapIndex1].id] = heapIndex2;
    this->heapIdMap[this->heapItems[heapIndex2].id] = heapIndex1;

    GridHeapItem value = this->heapItems[heapIndex1];
    this->heapItems[heapIndex1] = this->heapItems[heapIndex2];
    this->heapItems[heapIndex2] = value;
}

