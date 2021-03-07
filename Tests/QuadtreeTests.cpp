//
//  QuadtreeTests.cpp
//  Tests
//
//  Created by Trevor Zhang on 3/6/21.
//

#include <gtest/gtest.h>
#include "Quadtree.hpp"
#include <vector>

struct Rect{
    float x, y;
    float w, h;
};

void GetRect(const Rect& r, float& x, float& y, float& w, float& h){
    x = r.x;
    y = r.y;
    w = r.w;
    h = r.h;
}

TEST(Quadtree, Search){
    // Setup
    const size_t numRects = 4;
    Rect rects[numRects] = {
        {50, 40, 10, 10},
        {150, 120, 10, 10},
        {50, 120, 10, 10},
        {150, 40, 10, 10}
    };
    auto pQuadtree = new Quadtree<Rect, GetRect>;
    pQuadtree->Setup(100, 80, 100, 80, 3, 4);
    
    // Assert
    for(int i = 0; i < numRects; ++i)
        pQuadtree->Insert(&rects[i]);
    
    std::vector<Rect*> result;
    result = pQuadtree->Search(0, 0, 100, 80);
    ASSERT_EQ(&rects[0], result[0]);
    
    result = pQuadtree->Search(200, 160, 100, 80);
    ASSERT_EQ(&rects[1], result[0]);
    
    result = pQuadtree->Search(100, 80, 10, 10);
    ASSERT_EQ(0, result.size());
    
    result = pQuadtree->Search(100, 80, 100, 80);
    ASSERT_EQ(4, result.size());
    
    Rect r4 = {100, 80, 10, 10};
    pQuadtree->Insert(&r4);
    
    result = pQuadtree->Search(0, 0, 100, 80);
    ASSERT_EQ(2, result.size());
    
    result = pQuadtree->Search(200, 0, 100, 80);
    ASSERT_EQ(2, result.size());
    
    result = pQuadtree->Search(200, 160, 100, 80);
    ASSERT_EQ(2, result.size());
    
    result = pQuadtree->Search(0, 160, 100, 80);
    ASSERT_EQ(2, result.size());
    
    pQuadtree->Clear();
    
    result = pQuadtree->Search(100, 80, 100, 80);
    ASSERT_EQ(0, result.size());
    
    Rect r5 = {100, 80, 0, 0};
    pQuadtree->Insert(&r5);
    
    result = pQuadtree->Search(100, 80, 0, 0);
    ASSERT_EQ(1, result.size());
    
    result = pQuadtree->Search(50, 40, 50, 40);
    ASSERT_EQ(1, result.size());
    
    result = pQuadtree->Search(150, 120, 50, 40);
    ASSERT_EQ(1, result.size());
    
    result = pQuadtree->Search(150, 120, 50, 40);
    ASSERT_EQ(1, result.size());

    // Teardown
    delete pQuadtree;
}

TEST(Quadtree, Level1){
    const size_t numRects = 4;
    const size_t maxLevel = 1;
    bool result = true;
    Rect rects[numRects] = {
        {50, 40, 10, 10},
        {150, 120, 10, 10},
        {50, 120, 10, 10},
        {150, 40, 10, 10}
    };
    auto pQuadtree = new Quadtree<Rect, GetRect>;
    pQuadtree->Setup(100, 80, 100, 80, maxLevel, 4);
    
    // Assert
    for(int i = 0; i < numRects; ++i)
        result &= pQuadtree->Insert(&rects[i]);
    
    ASSERT_TRUE(result);
    
    Rect r4 = {100, 80, 10, 10};
    result &= pQuadtree->Insert(&r4);
    ASSERT_FALSE(result);
    
    delete pQuadtree;
}

TEST(Quadtree, Level2){
    const size_t numRects = 16;
    const size_t maxLevel = 2;
    bool result = true;
    Rect rects[numRects] = {
        {25, 20, 0, 0},
        {75, 20, 0, 0},
        {125, 20, 0, 0},
        {150, 20, 0, 0},
        {25, 60, 0, 0},
        {75, 60, 0, 0},
        {125, 60, 0, 0},
        {175, 60, 0, 0},
        {25, 100, 0, 0},
        {75, 100, 0, 0},
        {125, 100, 0, 0},
        {175, 100, 0, 0},
        {25, 140, 0, 0},
        {75, 140, 0, 0},
        {125, 140, 0, 0},
        {175, 140, 0, 0}
    };
    auto pQuadtree = new Quadtree<Rect, GetRect>;
    pQuadtree->Setup(100, 80, 100, 80, maxLevel, 4);
    
    // Assert
    for(int i = 0; i < numRects; ++i)
        result &= pQuadtree->Insert(&rects[i]);
    
    ASSERT_TRUE(result);
    
    Rect r4 = {100, 80, 10, 10};
    result &= pQuadtree->Insert(&r4);
    ASSERT_FALSE(result);
    
    delete pQuadtree;
}

TEST(Quadtree, DeepLevel){
    const size_t numRects = 4;
    bool result = true;
    Rect rects[numRects] = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0}
    };
    auto pQuadtree = new Quadtree<Rect, GetRect>;
    pQuadtree->Setup(3.5, 3.5, 4, 4, 3, 3);
    
    // Assert
    for(int i = 0; i < numRects; ++i){
        result &= pQuadtree->Insert(&rects[i]);
    }
    
    ASSERT_FALSE(result);
    
    result = true;
    pQuadtree->Clear();
    pQuadtree->Setup(3.5, 3.5, 4, 4, 4, 3);
    for(int i = 0; i < numRects; ++i)
        result &= pQuadtree->Insert(&rects[i]);
    ASSERT_TRUE(result);
    
    result = true;
    pQuadtree->Clear();
    pQuadtree->Setup(4, 4, 4, 4, 4, 3);
    for(int i = 0; i < numRects; ++i)
        result &= pQuadtree->Insert(&rects[i]);
    ASSERT_FALSE(result);
    
    result = true;
    pQuadtree->Clear();
    pQuadtree->Setup(4, 4, 4, 4, 5, 3);
    for(int i = 0; i < numRects; ++i)
        result &= pQuadtree->Insert(&rects[i]);
    ASSERT_TRUE(result);

    delete pQuadtree;
}
