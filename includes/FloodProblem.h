/*
 * File: FloodProblem.h
 * Project: future stream
 * Created Date: Sunday December 1st 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Tuesday December 10th 2019 9:26:30 am
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
#ifndef FUTURE_STREAM_FLOOD_PROMBLEM_H
#define FUTURE_STREAM_FLOOD_PROMBLEM_H

#include <algorithm>
#include <utility>
#include <limits>
#include <queue>
#include <cassert>
#include <set>
#include <iostream>
template <class Type>
class TwoDimenTypeTraits;

template <const size_t xLen, const size_t yLen>
class TwoDimenTypeTraits<size_t[xLen][yLen]>
{
public:
    enum
    {
        XLEN = xLen,
        YLEN = yLen,
        ArrayLen = xLen * yLen
    };

    typedef size_t DataContinerType[xLen][yLen];
};

class VertexObj
{
public:
    typedef size_t PrecursorType;
    typedef size_t WeightType;
    typedef std::vector<size_t> EdgesType;

    enum
    {
        NIL = std::numeric_limits<size_t>::max()
    };

    struct _Vertex
    {
        _Vertex() : index(NIL), weight(NIL), pre(NIL), path(NIL) ,visted(0){}

        _Vertex(size_t in, WeightType w, PrecursorType p, WeightType pa,size_t v) : index(in), weight(w), pre(p), path(pa),visted(v) {}

        bool operator()(const _Vertex &lhs, const _Vertex &rhs) const
        {
            return lhs.path > rhs.path;
        }

        size_t index;
        WeightType weight;
        PrecursorType pre;
        WeightType path;
        EdgesType edges;
        size_t visted;
    };

    typedef _Vertex VertexType;
    typedef std::vector<VertexType> VertexObjType;
    typedef std::priority_queue<VertexType, std::vector<VertexType>, VertexType> QueueType;
    
    inline VertexObj(size_t len):_vertexLen(len)
    {
        _vertexObjs.reserve(len);
    }

    void Push(const VertexType &v)
    {
        _vertexObjs.push_back(v);
    }

    void Push(size_t in, WeightType weight, PrecursorType pre = VertexObj::NIL, WeightType path = VertexObj::NIL)
    {
        _vertexObjs.push_back(VertexType(in, weight, pre, path,false));
    }

    inline bool Empty() const
    {
        return _vertexLen == 0;
    }

    inline size_t Size() const
    {
        return _vertexLen;
    }

    inline VertexType &operator[](size_t index)
    {
        return _vertexObjs[index];
    }

    inline const VertexType &operator[](size_t index) const
    {
        return static_cast<const VertexType &>(const_cast<VertexObj *>(this)->operator[](index));
    }

    VertexType& Popup();

private:
    VertexObjType _vertexObjs;
    size_t _vertexLen;
};

class AnchorObj
{
public:

    typedef size_t AnchorType;
    typedef std::vector<AnchorType> ContinerType;
    typedef std::set<AnchorType> VertexSet;

    AnchorObj(size_t len){_anchorObjs.reserve(len);}

    inline void Insert(size_t x)
    {
        _anchorObjs.push_back(x);
    }
    inline const AnchorType &GetAnchor(const size_t ind)
    {
        return _anchorObjs[ind];
    }

    inline void SetEdages(const VertexObj &vertexs, VertexSet& sets,size_t source)
    {
        for(auto index:_anchorObjs)
        {
            _SetEdges(index,vertexs,sets,source);
        }
    }
    const ContinerType& GetAnchors() 
    {
        return _anchorObjs;
    }

private:
    void _SetEdges(const size_t index,const VertexObj &vertexs, VertexSet& sets,size_t source);
    
    ContinerType _anchorObjs;
};


class FloodProblem
{
public:

    template <class Type>
    void InitSource(Type &cell, VertexObj& vertexObj, AnchorObj &anchor);

    template <class Type>
    void BuildEdges(size_t x, size_t y, VertexObj& vertexObj);

    void Relax(VertexObj &vertexes, VertexObj::VertexType &u);

    template <class Type>
    size_t DoSort(Type &arr);

private:
    bool _DoSort(size_t index, VertexObj &leftVertex, AnchorObj &anchor, AnchorObj::VertexSet& sets);
};

template <class Type>
void FloodProblem::InitSource(Type &cell, VertexObj& vertexObj, AnchorObj &anchor)
{
    size_t vertexIndex = 0;

    const size_t xLen = TwoDimenTypeTraits<Type>::XLEN;
    const size_t yLen = TwoDimenTypeTraits<Type>::YLEN;

    for (size_t i = 0; i < xLen; ++i)
    {
        for (size_t j = 0; j < yLen; ++j)
        {
            if (cell[i][j] == 0)
            {
                anchor.Insert(vertexIndex);
            }

            vertexObj.Push(vertexIndex, cell[i][j]);
            BuildEdges<Type>(i, j, vertexObj);
            ++vertexIndex;
        }
    }
}

template<class Type>
void FloodProblem::BuildEdges(size_t x, size_t y, VertexObj& vertexObj)
{
    switch (x)
    {
    case 0:
        switch (y)
        {
        case 0:
            vertexObj[0].edges.push_back(1);
            vertexObj[0].edges.push_back(TwoDimenTypeTraits<Type>::YLEN);
            vertexObj[0].edges.push_back(TwoDimenTypeTraits<Type>::YLEN + 1);
            break;
        case TwoDimenTypeTraits<Type>::YLEN - 1:
            vertexObj[TwoDimenTypeTraits<Type>::YLEN - 1].edges.push_back(TwoDimenTypeTraits<Type>::YLEN - 2);
            vertexObj[TwoDimenTypeTraits<Type>::YLEN - 1].edges.push_back(2 * TwoDimenTypeTraits<Type>::YLEN - 2);
            vertexObj[TwoDimenTypeTraits<Type>::YLEN - 1].edges.push_back(2 * TwoDimenTypeTraits<Type>::YLEN - 1);
            break;
        default:
            vertexObj[y].edges.push_back(y - 1);
            vertexObj[y].edges.push_back(y + 1);
            vertexObj[y].edges.push_back(y + TwoDimenTypeTraits<Type>::YLEN - 1);
            vertexObj[y].edges.push_back(y + TwoDimenTypeTraits<Type>::YLEN);
            vertexObj[y].edges.push_back(y + TwoDimenTypeTraits<Type>::YLEN + 1);
            break;
        }
        break;
    case TwoDimenTypeTraits<Type>::XLEN - 1:
        switch (y)
        {
        case 0:
            vertexObj[(TwoDimenTypeTraits<Type>::XLEN - 1) * TwoDimenTypeTraits<Type>::YLEN].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 2) * TwoDimenTypeTraits<Type>::YLEN);
            vertexObj[(TwoDimenTypeTraits<Type>::XLEN - 1) * TwoDimenTypeTraits<Type>::YLEN].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 2) * TwoDimenTypeTraits<Type>::YLEN + 1);
            vertexObj[(TwoDimenTypeTraits<Type>::XLEN - 1) * TwoDimenTypeTraits<Type>::YLEN].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 1) * TwoDimenTypeTraits<Type>::YLEN + 1);

            break;
        case TwoDimenTypeTraits<Type>::YLEN - 1:
            vertexObj[TwoDimenTypeTraits<Type>::XLEN * TwoDimenTypeTraits<Type>::YLEN - 1].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 1) * TwoDimenTypeTraits<Type>::YLEN - 1);
            vertexObj[TwoDimenTypeTraits<Type>::XLEN * TwoDimenTypeTraits<Type>::YLEN - 1].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 1) * TwoDimenTypeTraits<Type>::YLEN - 2);
            vertexObj[TwoDimenTypeTraits<Type>::XLEN * TwoDimenTypeTraits<Type>::YLEN - 1].edges.push_back(TwoDimenTypeTraits<Type>::XLEN * TwoDimenTypeTraits<Type>::YLEN - 2);
            break;
        default:
        {
            size_t bottom = (TwoDimenTypeTraits<Type>::XLEN - 1) * TwoDimenTypeTraits<Type>::YLEN + y;
            vertexObj[bottom].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 2) * TwoDimenTypeTraits<Type>::YLEN + y - 1);
            vertexObj[bottom].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 2) * TwoDimenTypeTraits<Type>::YLEN + y);
            vertexObj[bottom].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 2) * TwoDimenTypeTraits<Type>::YLEN + y + 1);
            vertexObj[bottom].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 1) * TwoDimenTypeTraits<Type>::YLEN + y - 1);
            vertexObj[bottom].edges.push_back((TwoDimenTypeTraits<Type>::XLEN - 1) * TwoDimenTypeTraits<Type>::YLEN + y + 1);
        }
        break;
        }
        break;
    default: // 0 <x < XLEN -1
        switch (y)
        {
        case 0:
        {
            size_t left = x * TwoDimenTypeTraits<Type>::YLEN;
            vertexObj[left].edges.push_back(left - TwoDimenTypeTraits<Type>::YLEN);
            vertexObj[left].edges.push_back(left - TwoDimenTypeTraits<Type>::YLEN + 1);
            vertexObj[left].edges.push_back(left + 1);
            vertexObj[left].edges.push_back(left + TwoDimenTypeTraits<Type>::YLEN);
            vertexObj[left].edges.push_back(left + TwoDimenTypeTraits<Type>::YLEN + 1);
            break;
        }

        case TwoDimenTypeTraits<Type>::YLEN - 1:
        {
            size_t right = x * TwoDimenTypeTraits<Type>::YLEN + TwoDimenTypeTraits<Type>::YLEN - 1;
            vertexObj[right].edges.push_back(right - TwoDimenTypeTraits<Type>::YLEN);
            vertexObj[right].edges.push_back(right - TwoDimenTypeTraits<Type>::YLEN - 1);
            vertexObj[right].edges.push_back(right - 1);
            vertexObj[right].edges.push_back(right + TwoDimenTypeTraits<Type>::YLEN);
            vertexObj[right].edges.push_back(right + TwoDimenTypeTraits<Type>::YLEN - 1);
            break;
        }
        default:
        {
            size_t middle = x * TwoDimenTypeTraits<Type>::YLEN + y;
            vertexObj[middle].edges.push_back(middle - TwoDimenTypeTraits<Type>::YLEN - 1);
            vertexObj[middle].edges.push_back(middle - TwoDimenTypeTraits<Type>::YLEN);
            vertexObj[middle].edges.push_back(middle - TwoDimenTypeTraits<Type>::YLEN + 1);
            vertexObj[middle].edges.push_back(middle - 1);
            vertexObj[middle].edges.push_back(middle + 1);
            vertexObj[middle].edges.push_back(middle + TwoDimenTypeTraits<Type>::YLEN - 1);
            vertexObj[middle].edges.push_back(middle + TwoDimenTypeTraits<Type>::YLEN);
            vertexObj[middle].edges.push_back(middle + TwoDimenTypeTraits<Type>::YLEN + 1);
        }
        break;
        }
        break;
    }
}

template <class Type>
size_t FloodProblem::DoSort(Type &arr)
{
    AnchorObj anchor(TwoDimenTypeTraits<Type>::ArrayLen);
    VertexObj vertexObj(TwoDimenTypeTraits<Type>::ArrayLen);

    AnchorObj::VertexSet setMax,setCurrent;
    size_t rsltCurrent = 0, rsltMax = 0;

    InitSource(arr,vertexObj,anchor);

    {
        VertexObj verMaxObj = vertexObj;

        _DoSort(0, verMaxObj, anchor, setMax);

        for (auto vM : setMax)
        {
            rsltMax += verMaxObj[vM].weight;
        }
    }
    
    size_t setLen = anchor.GetAnchors().size();
    for(size_t index = 1; index < setLen; ++index)
    {
        rsltCurrent = 0;
        VertexObj verCurrentObj = vertexObj;
        _DoSort(index, verCurrentObj,anchor,setCurrent);

        for(auto vC:setCurrent)
        {
            rsltCurrent += verCurrentObj[vC].weight;
        }

        if(rsltMax > rsltCurrent)
        {
            rsltMax = rsltCurrent;
            setMax.swap(setCurrent);
        }
        setCurrent.clear();
    }
    

    //std::cout << "\n<(" << anchor.GetAnchor(0) << "):w(0),";
    for(auto i: setMax)
    {
        std::cout <<"<v(" << i << "):w(" << vertexObj[i].weight << ")>, ";
    }
    std::cout << "\nrslt: " << rsltMax << std::endl;

    return rsltMax;
}

template <class Type>
inline size_t SortFloodProblem(Type &data)
{
    FloodProblem flood;
    return flood.DoSort(data);
}

#endif
