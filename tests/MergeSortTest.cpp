/*
 * File: MergeSortTest.cpp
 * Project: future stream
 * Created Date: Thursday November 28th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Friday November 29th 2019 10:05:57 am
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
#include "MergeSort.h"
using namespace std;

#define MERGE_SORT_TEST_DESC_ARRAY_LEN  50

TEST(MergeSortTest,DescForRandomItertor)
{
    std::vector<int> data;
    
    for(int i = 0;i < 50; i++)
    {
        data.push_back(GetRandomValue(OutputIntegerRandom(),0,100));
    }

    MergeSortDesc(data,data.size());

    EXPECT_EQ(true,VaildateDesc(data,data.size()));
}

TEST(MergeSortTest,DescForArray)
{
    
    int data[MERGE_SORT_TEST_DESC_ARRAY_LEN];
    
    for(int i = 0;i < MERGE_SORT_TEST_DESC_ARRAY_LEN; i++)
    {
        data[i] = GetRandomValue(OutputIntegerRandom(),0,100);
    }

    MergeSortDesc(data,static_cast<size_t>(MERGE_SORT_TEST_DESC_ARRAY_LEN));

    EXPECT_EQ(true,VaildateDesc(data,MERGE_SORT_TEST_DESC_ARRAY_LEN));
}

TEST(MergeSortTest,ForRandomItertor)
{
    std::vector<int> data;
    
    for(int i = 0;i < 50; i++)
    {
        data.push_back(GetRandomValue(OutputIntegerRandom()));
    }

    MergeSortAsc(data,data.size());

    EXPECT_EQ(true,VaildateAsc(data,data.size()));
}

TEST(MergeSortTest,ForArray)
{
    int data[MERGE_SORT_TEST_DESC_ARRAY_LEN];
    
    for(int i = 0;i < MERGE_SORT_TEST_DESC_ARRAY_LEN; i++)
    {
        data[i] = GetRandomValue(OutputIntegerRandom(),0,100);
    }

    MergeSortAsc(data,MERGE_SORT_TEST_DESC_ARRAY_LEN);

    EXPECT_EQ(true,VaildateAsc(data,MERGE_SORT_TEST_DESC_ARRAY_LEN));
}
