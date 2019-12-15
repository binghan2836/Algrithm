/*
 * File: FloodProblemTest.cpp
 * Project: future stream
 * Created Date: Sunday December 1st 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Tuesday December 10th 2019 9:17:59 pm
 * Modified By:   the developer formerly known as DaGai
 * -----
 * MIT License
 * 
 * Copyright (c) 2019 binghan2836@163.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * -----
 * HISTORY:
 * Date          By    Comments
 * ----------    ---    ----------------------------------------------------------
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>
#include "RandomGenerator.h"
#include "FloodProblem.h"

/*TEST(FloodProblemTest, Init)
{
    int data[] = {0, 8, 0, 7, 2, 6, 0, 5, 0};
    int (&matrix)[3][3] = *reinterpret_cast<int (*)[3][3]>(&data);

    auto flood = MakeFloodProblemInstance(matrix);

    auto obj = flood.GetAnchorObj(AnchorObj::TOP_LEFT);
    EXPECT_EQ(obj, 0);

    auto rightObj = flood.GetAnchorObj(AnchorObj::BOTTOM_RIGHT);

    EXPECT_EQ(rightObj, 8);

    for (int i = 0; i < 9; i++)
    {
        EXPECT_EQ(flood.GetPrecursor(i), VertexObj::NIL);
        EXPECT_EQ(flood.GetPathValue(i), VertexObj::NIL);
        EXPECT_EQ(flood.GetWeight(i), data[i]);
        EXPECT_EQ(flood.GetIndex(i), i);
    }
}*/

TEST(FloodProblemTest, SMallCase1)
{
    size_t data[] = {9,0,3,10,3,4,4,0,7};
    size_t (&matrix)[3][3] = *reinterpret_cast<size_t (*)[3][3]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),3);
}


TEST(FloodProblemTest, SMallCase2)
{
    size_t data[] = {0,6,10,9,1,9,0,6,8,0,2,3,1,4,7,0,6,0,3,4};
    
    size_t (&matrix)[5][4] = *reinterpret_cast<size_t (*)[5][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),4);
}

TEST(FloodProblemTest, SMallCase3)
{
    size_t data[] = {3,9,5,10,10,0,7,0,4,4,10,8,0,7,0,8};

    size_t (&matrix)[4][4] = *reinterpret_cast<size_t (*)[4][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),9);
}

TEST(FloodProblemTest, SMallCase4)
{
    size_t data[] = {3,9,5,10,10,0,7,0,4,4,10,8,0,7,0,8};

    size_t (&matrix)[4][4] = *reinterpret_cast<size_t (*)[4][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),9);
}