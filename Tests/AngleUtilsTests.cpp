//
//  AngleUtilsTests.cpp
//  Tests
//
//  Created by Trevor Zhang on 2/8/21.
//

#include <gtest/gtest.h>
#include "AngleUtils.hpp"

TEST(AngleUtils, WrapDegrees) {
    float degrees = 90.f;
    AI::AngleUtils::WrapDegrees(degrees);
    ASSERT_EQ(90.f, degrees);
    
    degrees = 180.f;
    AI::AngleUtils::WrapDegrees(degrees);
    ASSERT_EQ(-180.f, degrees);
    
    degrees = -180.f;
    AI::AngleUtils::WrapDegrees(degrees);
    ASSERT_EQ(-180.f, degrees);
    
    degrees = -90.f;
    AI::AngleUtils::WrapDegrees(degrees);
    ASSERT_EQ(-90.f, degrees);
    
    degrees = 0.f;
    AI::AngleUtils::WrapDegrees(degrees);
    ASSERT_EQ(0.f, degrees);
    
    degrees = 270.f;
    AI::AngleUtils::WrapDegrees(degrees);
    ASSERT_EQ(-90.f, degrees);
    
    degrees = -270.f;
    AI::AngleUtils::WrapDegrees(degrees);
    ASSERT_EQ(90.f, degrees);
    
    degrees = 360.f;
    AI::AngleUtils::WrapDegrees(degrees);
    ASSERT_EQ(0.f, degrees);
    
    degrees = 540.f;
    AI::AngleUtils::WrapDegrees(degrees);
    ASSERT_EQ(-180.f, degrees);
}

TEST(AngleUtils, AngleDiff){
    float angleA = 0.f, angleB = 0.f, diff = 0.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(0.f, diff);
    
    angleA = 0.f; angleB = 90.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(90.f, diff);
    
    angleA = 0.f; angleB = -90.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(-90.f, diff);
    
    angleA = -90.f; angleB = 90.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(-180.f, diff);
    
    angleA = 90.f; angleB = -90.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(-180.f, diff);
    
    angleA = 179.f; angleB = 181.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(2.f, diff);
    
    angleA = 181.f; angleB = 179.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(-2.f, diff);
    
    angleA = 0.f; angleB = 361.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(1.f, diff);
    
    angleA = 361.f; angleB = -361.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(-2.f, diff);
    
    angleA = 180.f; angleB = -180.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(0.f, diff);
    
    angleA = -180.f; angleB = 180.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(0.f, diff);
    
    angleA = -180.f; angleB = 1.f;
    diff = AI::AngleUtils::AngleDiff(angleB, angleA);
    ASSERT_EQ(-179.f, diff);
}
