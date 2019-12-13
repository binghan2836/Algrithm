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
class ArrayTraits;

template <const size_t xLen, const size_t yLen>
class ArrayTraits<size_t[xLen][yLen]>
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
    FloodProblem(size_t **data,const size_t x,const size_t y):_p(data),_xLen(x),_yLen(y),_arrayLen(x*y)
    {
        
    }

    void InitSource(VertexObj& vertexObj, AnchorObj &anchor);

    void BuildEdges(const size_t x, const size_t y,VertexObj& vertexObj);

    void Relax(VertexObj &vertexes, VertexObj::VertexType &u);

    size_t DoSort();

private:
    bool _DoSort(size_t index, VertexObj &leftVertex, AnchorObj &anchor, AnchorObj::VertexSet& sets);
    size_t **_p;
    const size_t _xLen;
    const size_t _yLen;
    const size_t _arrayLen;
};

template <class Type>
inline size_t SortFloodProblem(Type &data)
{
    FloodProblem flood(reinterpret_cast<size_t **>(&data),ArrayTraits<Type>::XLEN,ArrayTraits<Type>::YLEN);
    return flood.DoSort();
}

#endif
