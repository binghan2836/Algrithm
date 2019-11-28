/*
 * File: MergeSort.h
 * Project: future stream
 * Created Date: Thursday November 28th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Thursday November 28th 2019 1:19:12 pm
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
/*
                     |7|4|5|6|8|5|

                 |7|4|5|     |6|8|5|

                |7|  |4|5|  |6|  |8|5|
                
                    |4| |5|     |8|  |5|
*/


template <class Comp>
class _MergeSort
{
public:

    _MergeSort(size_t len,Comp &c):_comp(c)
    {
        _mergerData.resize(len);
    }

    template<class Type>
    void _Merge(Type &data,const size_t left,size_t middle,size_t right)
    {
        size_t index = left;
        size_t leftIndex = left;
        size_t rightIndex = middle + 1;

        std::vector<decltype> _mergerData;
        
        while((leftIndex <= middle) && (rightIndex <= right))
        {
            if(_comp(data[leftIndex],data[rightIndex]))
            {
                _mergerData[index] = data[leftIndex];
                ++index;
                ++leftIndex;
            }
            else
            {
                _mergerData[index] = data[rightIndex];
                ++index;
                ++rightIndex;
            }
        }

        //attach left to tail
        for(; leftIndex <= middle; ++leftIndex , ++index)
        {
            _mergerData[index] = data[leftIndex];
        }

        for(; rightIndex <= right; ++rightIndex,++index)
        {
            _mergerData[index] = data[rightIndex];
        }

        std::cout << "\n";
        for(auto i:_mergerData)
        {
            std::cout << i << " ";
        }
        std::cout << "\n";

    }

    template <class Type>
    void _Sort(Type &data,const size_t left,size_t right)
    {
        if(left < right)
        {
            size_t middle = (right + left) / 2;

            _Sort(data,left,middle);
            _Sort(data,middle + 1,right);
            std::cout << "_Merge " << left << "  " << middle << " " << right << " ";
            _Merge(data,left,middle,right);
        }
    }

    template<class Type>
    void operator()(Type &data,const size_t len)
    {
        _Sort(data,0,len -1);

        data.swap(_mergerData);
    }

private:
    Comp &_comp;
};


template <class Type,class Comp>
void MergeSort(Type &data, const size_t len, Comp comp)
{
    _MergeSort<Comp>(len,comp)(data,len);
}

template<class Type>
inline void MergeSortDesc(Type &data, const size_t len)
{
    MergeSort(data,len,DescComp());
}

#endif
