/*
 * File: MergeSort.h
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
#ifndef FUTURE_STREAM_MERGE_SORT_H
#define FUTURE_STREAM_MERGE_SORT_H
#include "SortUtility.h"
#include <vector>
#include <algorithm> 
/*
                     |7|4|5|6|8|5|

                 |7|4|5|     |6|8|5|

                |7|  |4|5|  |6|  |8|5|
                
                    |4| |5|     |8|  |5|
*/

template<class Type>
struct Continer
{
    typedef Type value_type;
};

template<class Type>
struct Continer<Type&>
{
    typedef Type value_type;
};

template <class Comp>
class _MergeSort
{
public:

    _MergeSort(size_t len,Comp &c):_comp(c)
    {
    }

    template<class Type>
    void _Merge(Type &data,const size_t left,size_t middle,size_t right)
    {
        /**
         * @brief use C++11 decltype
         * 
         */
        size_t arrayLen = right - left + 1;
        std::vector<typename Continer<decltype(data[0])>::value_type > _mergerData;
        _mergerData.resize(arrayLen);
        
        for(size_t i = 0; i < arrayLen; ++i)
        {
            _mergerData[i] = data[left + i];
        }

        size_t index = left;
        size_t leftIndex = 0;
        size_t leftLen = middle - left + 1;
        size_t rightIndex = middle + 1 - left;

        while((leftIndex < leftLen) && (rightIndex < arrayLen))
        {
            if(_comp(_mergerData[leftIndex],_mergerData[rightIndex]))
            {
                data[index] = _mergerData[leftIndex];
                ++index;
                ++leftIndex;
            }
            else
            {
                data[index] = _mergerData[rightIndex];
                ++index;
                ++rightIndex;
            }
        }

        //attach left to tail
        for(; leftIndex < leftLen; ++leftIndex , ++index)
        {
            data[index] = _mergerData[leftIndex];
        }

        for(; rightIndex < arrayLen; ++rightIndex,++index)
        {
            data[index] = _mergerData[rightIndex];
        }
    }

    template <class Type>
    void _Sort(Type &data,const size_t left,size_t right)
    {
        if(left < right)
        {
            size_t middle = (right + left) / 2;

            _Sort(data,left,middle);
            _Sort(data,middle + 1,right);
            _Merge(data,left,middle,right);
        }
    }

    template<class Type>
    void operator()(Type &data,const size_t len)
    {
        _Sort(data,0,len -1);
    }

private:
    Comp &_comp;
};


template <class Type,class Comp>
inline void MergeSort(Type &data, const size_t len, Comp comp)
{
    _MergeSort<Comp>(len,comp)(data,len);
}

template<class Type>
inline void MergeSortDesc(Type &data, const size_t len)
{
    MergeSort(data,len,DescComp());
}


template<class Type>
inline void MergeSortAsc(Type &data, const size_t len)
{
    MergeSort(data,len,AscComp());
}

#endif
