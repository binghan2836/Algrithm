/*
 * File: InsertSort.h
 * Project: future stream
 * Created Date: Wednesday November 27th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Wednesday November 27th 2019 2:18:55 pm
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
#ifndef FUTURE_STREAM_INSERT_SORT_H
#define FUTURE_STREAM_INSERT_SORT_H
#include "SortUtility.h"

template<class Type,class Comp>
void InsertSort(Type &data, const size_t len, Comp comp)
{
    if(len <= 1)
    {
        return;
    }

    for(size_t index = 1; index < len; index ++)
    {
        size_t current = index -1;
        auto key = data[index];


        for(size_t loop = 0; (loop < index) && (comp(key,data[current]));loop++)//data[current] < key
        {
            data[current + 1] = data[current];
            current --;
        }
        data[current + 1] = key;
    }
}

template<class Type>
inline void InsertSortDesc(Type &data, const size_t len)
{
    InsertSort(data,len,DescComp());
}

template<class Type>
inline void InsertSortAsc(Type &data, const size_t len)
{
    InsertSort(data,len,AscComp());
}

#endif
