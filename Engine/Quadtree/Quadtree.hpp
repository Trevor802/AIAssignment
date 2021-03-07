//
//  Quadtree.hpp
//  AIAssignment
//
//  Created by Trevor Zhang on 3/4/21.
//

// Reference: https://github.com/timohausmann/quadtree-js/blob/master/quadtree.js

#pragma once
#include <vector>
#include <unordered_set>

#define Quad 4

//typedef void(*GetPositionFunc)(int&, int&);
typedef std::vector<int> IDs;

template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
class Quadtree final{
    size_t myMaxLevel = 3;
    size_t myNodeCapacity = 4;
    int myLevel = -1;
    float myCenterX = 0, myCenterY = 0;
    float myHalfWidth = 0, myHalfHeight = 0;
    std::vector<Object*> myObjects;
    class Quadtree<Object, PosFunc>* myNodes = nullptr;

    void Split();
    int FindIntersectNodes(float, float, float, float, IDs&);
    static bool IsAABBIntersecting(float, float, float, float, float, float, float, float);
    bool InsertInternal(Object*, float, float, float, float);
    
public:
    Quadtree() = default;
    virtual ~Quadtree();
    void Setup(float, float, float, float, size_t, size_t);
    bool Insert(Object*);
    std::vector<Object*> Search(float, float, float, float);
    void Clear();
};

template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
void Quadtree<Object, PosFunc>::Setup(float centerX, float centerY, float halfWidth, float halfHeight, size_t maxLevel, size_t capacity){
    myCenterX = centerX;
    myCenterY = centerY;
    myHalfWidth = halfWidth;
    myHalfHeight = halfHeight;
    myLevel = 0;
    myMaxLevel = maxLevel;
    myNodeCapacity = capacity;
}

template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
Quadtree<Object, PosFunc>::~Quadtree(){
    delete [] myNodes;
}

/// [0][1]
/// [2][3]
template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
void Quadtree<Object, PosFunc>::Split(){
    myNodes = new Quadtree<Object, PosFunc>[Quad];
    float x = myCenterX / 2;
    float y = myCenterY / 2;
    float w = myHalfWidth / 2;
    float h = myHalfHeight / 2;
    myNodes[0].Setup(x, y, w, h, myMaxLevel, myNodeCapacity);
    myNodes[0].myLevel = myLevel + 1;
    myNodes[1].Setup(x + myHalfWidth, y, w, h, myMaxLevel, myNodeCapacity);
    myNodes[1].myLevel = myLevel + 1;
    myNodes[2].Setup(x, y + myHalfHeight, w, h, myMaxLevel, myNodeCapacity);
    myNodes[2].myLevel = myLevel + 1;
    myNodes[3].Setup(x + myHalfWidth, y + myHalfHeight, w, h, myMaxLevel, myNodeCapacity);
    myNodes[3].myLevel = myLevel + 1;
}

/// [0][1]
/// [2][3]
template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
int Quadtree<Object, PosFunc>::FindIntersectNodes(float centerX, float centerY, float halfWidth, float halfHeight, IDs& output){
    int count = 0;
    bool startWest  = centerX - halfWidth <= myCenterX;
    bool endEast    = centerX + halfWidth >= myCenterX;
    bool startNorth = centerY - halfHeight <= myCenterY;
    bool endSouth   = centerY + halfHeight >= myCenterY;
    if (startWest && startNorth){
        output.push_back(0);
        ++count;
    }
    if (startNorth && endEast){
        output.push_back(1);
        ++count;
    }
    if (startWest && endSouth){
        output.push_back(2);
        ++count;
    }
    if (endSouth && endEast){
        output.push_back(3);
        ++count;
    }
    return count;
}

template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
bool Quadtree<Object, PosFunc>::InsertInternal(Object* object, float centerX, float centerY, float halfWidth, float halfHeight){
    bool result = true;
    if (myNodes){
        IDs nodes;
        FindIntersectNodes(centerX, centerY, halfWidth, halfHeight, nodes);
        for(const int& id : nodes)
            result &= myNodes[id].InsertInternal(object, centerX, centerY, halfWidth, halfHeight);
        return result;
    }
    myObjects.push_back(object);
    if (myObjects.size() > myNodeCapacity && myLevel < myMaxLevel){
        if (myLevel + 1 >= myMaxLevel)
            return false;
        Split();
        for(int i = 0; i <= myNodeCapacity; ++i){
            float x, y, w, h;
            PosFunc(*myObjects[i], x, y, w, h);
            IDs nodes;
            FindIntersectNodes(x, y, w, h, nodes);
            for(const int& id : nodes)
                result &= myNodes[id].InsertInternal(myObjects[i], x, y, w, h);
        }
        myObjects.clear();
    }
    return result;
}

template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
bool Quadtree<Object, PosFunc>::Insert(Object* object){
    float x, y, w, h;
    PosFunc(*object, x, y, w, h);
    return InsertInternal(object, x, y, w, h);
}

template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
void Quadtree<Object, PosFunc>::Clear(){
    myObjects.clear();
    if (myNodes)
        for(int i = 0; i < Quad; ++i){
            myNodes[i].Clear();
        }
    delete[] myNodes;
    myNodes = nullptr;
}

template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
std::vector<Object*> Quadtree<Object, PosFunc>::Search(float centerX, float centerY, float halfWidth, float halfHeight){
    std::vector<Object*> result;
    IDs nodes;
    int count = 0;
    count = FindIntersectNodes(centerX, centerY, halfWidth, halfHeight, nodes);
    if (0 == count)
        return result;
    if (myNodes){
        for(const int& id : nodes){
            const auto& objects = myNodes[id].Search(centerX, centerY, halfWidth, halfHeight);
            result.insert(result.end(), objects.begin(), objects.end());
        }
    }
    else{
        for(Object* pObject : myObjects){
            float x, y, w, h;
            PosFunc(*pObject, x, y, w, h);
            if (IsAABBIntersecting(centerX, centerY, halfWidth, halfHeight, x, y, w, h))
                result.push_back(pObject);
        }
    }
    // Reference: https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
    std::unordered_set<Object*> s;
    for(Object* pObject : result)
        s.insert(pObject);
    result.assign(s.begin(), s.end());
    return result;
}

template<typename Object, void PosFunc(const Object&, float&x, float&y, float& w, float& h)>
bool Quadtree<Object, PosFunc>::IsAABBIntersecting(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2){
    if (x1 - w1 > x2 + w2 || x2 - w2 > x1 + w1)
        return false;
    if (y1 - h1 > y2 + h2 || y2 - h2 > y1 + h1)
        return false;
    return true;
}
