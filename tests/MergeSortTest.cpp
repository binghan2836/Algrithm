/*
 * File: MergeSortTest.cpp
 * Project: future stream
 * Created Date: Thursday November 28th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Thursday November 28th 2019 1:33:01 pm
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
TEST(MergeSortTest,Desc)
{
    std::vector<int> data;
    
    for(int i = 0;i < 5; i++)
    {
        data.push_back(GetRandomValue(OutputIntegerRandom(),0,100));
    }

    for(auto i:data)
    {
        cout << i << " ";
    }
    cout << "\n";

    MergeSortDesc(data,data.size());

    for(auto i:data)
    {
        cout << i << " ";
    }

    cout << "\n";
}
