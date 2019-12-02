/*
 * File: FloodProblemTest.cpp
 * Project: future stream
 * Created Date: Sunday December 1st 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Sunday December 1st 2019 6:05:27 pm
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

TEST(FloodProblemTest,TwoDimensinalObjArray)
{
    int matrix[4][4];

    for(int i =0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            matrix[i][j] = j;
        }
    }

    auto obj = MakeTwoDimensinalObj(matrix);
    EXPECT_EQ(obj.GetValue(0,3),3);
    EXPECT_EQ(obj.GetValue(1,3),3);

    obj.SetValue(0,3,10);
    obj.Cells()[1][3] = 20;

    EXPECT_EQ(obj.GetValue(0,3),10);
    EXPECT_EQ(obj.GetValue(1,3),20);
}

TEST(FloodProblemTest,GetAnchor)
{
    int matrix[4][4];

    for(int i =0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            matrix[i][j] = j;
        }
    }

    auto flood = MakeFloodProblemInstance(matrix);

    AnchorObj obj;
    
    EXPECT_EQ(flood.GetAnchorObj(obj), true);
}

