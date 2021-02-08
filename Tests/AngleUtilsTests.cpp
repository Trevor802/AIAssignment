//
//  AngleUtilsTests.cpp
//  Tests
//
//  Created by Trevor Zhang on 2/8/21.
//

#include <gtest/gtest.h>
#include "AngleUtils-inl.hpp"

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

TEST(AngleUtils, RadiansToDegrees){
    float deviations = 0.0001f;
    float radians = 0.f, degrees = 0.f;
    float result = AI::AngleUtils::RadiansToDegrees(radians);
    ASSERT_LT(fabsf(degrees - result), deviations);
    
    radians = AI::AngleUtils::PIf / 4.f; degrees = 45.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = -AI::AngleUtils::PIf / 4.f; degrees = -45.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = AI::AngleUtils::PIf / 3.f; degrees = 60.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = AI::AngleUtils::PIf / 6.f; degrees = 30.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = AI::AngleUtils::PIf / 2.f; degrees = 90.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = AI::AngleUtils::PIf; degrees = 180.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = AI::AngleUtils::PIf * 2.f; degrees = 360.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = AI::AngleUtils::PIf * 1.5f; degrees = 270.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = -AI::AngleUtils::PIf / 2.f; degrees = -90.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = -AI::AngleUtils::PIf; degrees = -180.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = -AI::AngleUtils::PIf / 3.f; degrees = -60.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = -AI::AngleUtils::PIf / 4.f; degrees = -45.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = -AI::AngleUtils::PIf * 2.f; degrees = -360.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
    
    radians = -AI::AngleUtils::PIf * 1.5f; degrees = -270.f;
    ASSERT_LT(fabsf(degrees - AI::AngleUtils::RadiansToDegrees(radians)), deviations);
}

TEST(AngleUtils, DegreesToRadians){
    float deviations = 0.0001f;
    float radians = 0.f, degrees = 0.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = AI::AngleUtils::PIf / 4.f; degrees = 45.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = -AI::AngleUtils::PIf / 4.f; degrees = -45.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = AI::AngleUtils::PIf / 3.f; degrees = 60.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = AI::AngleUtils::PIf / 6.f; degrees = 30.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = AI::AngleUtils::PIf / 2.f; degrees = 90.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = AI::AngleUtils::PIf; degrees = 180.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = AI::AngleUtils::PIf * 2.f; degrees = 360.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = AI::AngleUtils::PIf * 1.5f; degrees = 270.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = -AI::AngleUtils::PIf / 2.f; degrees = -90.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = -AI::AngleUtils::PIf; degrees = -180.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = -AI::AngleUtils::PIf / 3.f; degrees = -60.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = -AI::AngleUtils::PIf / 4.f; degrees = -45.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = -AI::AngleUtils::PIf * 2.f; degrees = -360.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
    
    radians = -AI::AngleUtils::PIf * 1.5f; degrees = -270.f;
    ASSERT_LT(fabsf(radians - AI::AngleUtils::DegreesToRadians(degrees)), deviations);
}

TEST(AngleUtils, Vec2ToAngleInDegrees){
    float deviations = 0.0001f;
    float degrees = 0.f;
    float result = AI::AngleUtils::Vec2ToAngleInDegrees(0.f, 0.f);
    ASSERT_LT(fabsf(degrees - result), deviations);
    
    degrees = 45.f;
    result = AI::AngleUtils::Vec2ToAngleInDegrees(1.f, 1.f);
    ASSERT_LT(fabsf(degrees - result), deviations);
    
    degrees = 135.f;
    result = AI::AngleUtils::Vec2ToAngleInDegrees(-1.f, 1.f);
    ASSERT_LT(fabsf(degrees - result), deviations);
    
    degrees = -45.f;
    result = AI::AngleUtils::Vec2ToAngleInDegrees(1.f, -1.f);
    ASSERT_LT(fabsf(degrees - result), deviations);
    
    degrees = -135.f;
    result = AI::AngleUtils::Vec2ToAngleInDegrees(-1.f, -1.f);
    ASSERT_LT(fabsf(degrees - result), deviations);
    
    degrees = -90.f;
    result = AI::AngleUtils::Vec2ToAngleInDegrees(0.f, -1.f);
    ASSERT_LT(fabsf(degrees - result), deviations);
    
    degrees = 90.f;
    result = AI::AngleUtils::Vec2ToAngleInDegrees(0.f, 1.f);
    ASSERT_LT(fabsf(degrees - result), deviations);
    
    degrees = -180.f;
    result = AI::AngleUtils::Vec2ToAngleInDegrees(-1.f, 0.f);
    ASSERT_LT(fabsf(degrees - result), deviations);
}
