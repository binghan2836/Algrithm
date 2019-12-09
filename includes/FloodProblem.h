/*
 * File: FloodProblem.h
 * Project: future stream
 * Created Date: Sunday December 1st 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Monday December 9th 2019 8:32:18 pm
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
#include <map>

template <class Type>
class TwoDimenTypeTraits;

template <class Type, const size_t xLen, const size_t yLen>
class TwoDimenTypeTraits<Type[xLen][yLen]>
{
public:
    enum
    {
        XLEN = xLen,
        YLEN = yLen
    };

    typedef Type DataContinerType[xLen][yLen];
    TwoDimenTypeTraits(DataContinerType &data):_dataContiner(data){}

private:
    DataContinerType &_dataContiner;
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

        static bool VertexCmp(_Vertex &rh, _Vertex &lh)
        {
            return rh.path > lh.path;
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
    typedef std::map<size_t, VertexType &> VertexObjMapType;
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

    inline const PrecursorType &GetPrecursor(size_t index)
    {
        return _vertexObjs[index].pre;
    }

    inline void SetPrecursor(size_t index, const PrecursorType &value)
    {
        _vertexObjs[index].pre = value;
    }

    inline const WeightType &GetPathValue(size_t index)
    {
        return _vertexObjs[index].path;
    }

    inline void SetPathValue(size_t index, const WeightType &value)
    {
        _vertexObjs[index].path = value;
    }

    inline const WeightType &GetWeight(size_t index)
    {
        return _vertexObjs[index].weight;
    }

    inline void SetWeight(size_t index, const WeightType &value)
    {
        _vertexObjs[index].weight = value;
    }

    inline const size_t GetIndex(size_t index)
    {
        return _vertexObjs[index].index;
    }

    inline void SetIndex(size_t index, const size_t value)
    {
        _vertexObjs[index].index = value;
    }

private:
    VertexObjType _vertexObjs;
    size_t _vertexLen;
};

class AnchorObj
{
public:
    enum AnchorIndex
    {
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT,
        ANCHOR_LENGTH
    };

    typedef typename VertexObj::EdgesType EdgesType;

    typedef size_t AnchorType;

    inline void Insert(AnchorIndex index, size_t x)
    {
        _anchorObjs[index] = x;
    }
    inline const AnchorType &GetAnchor(const AnchorIndex ind)
    {
        return _anchorObjs[ind];
    }

    inline void SetEdages(const VertexObj &vertexs)
    {
        _SetEdges(TOP_RIGHT,vertexs);
        _SetEdges(BOTTOM_LEFT,vertexs);
    }

    inline EdgesType &GetEdges(const AnchorIndex ind)
    {
        return _anchorEdges[ind];
    }

private:
    void _SetEdges(const AnchorIndex index,const VertexObj &vertexs);
    
    AnchorType _anchorObjs[ANCHOR_LENGTH];
    EdgesType _anchorEdges[ANCHOR_LENGTH];
};

template <class Type>
class FloodProblem
{
public:
    enum
    {
        XLEN = TwoDimenTypeTraits<Type>::XLEN,
        YLEN = TwoDimenTypeTraits<Type>::YLEN,
        ARRAY_LEN = TwoDimenTypeTraits<Type>::XLEN * TwoDimenTypeTraits<Type>::YLEN
    };
    typedef typename TwoDimenTypeTraits<Type>::DataContinerType ArrayObj;

    template<class AarryType>
    FloodProblem(AarryType &data):_cells(data), _vertexObj(TwoDimenTypeTraits<Type>::XLEN * TwoDimenTypeTraits<Type>::YLEN) 
    {
    }

    void InitSource();

    void BuildEdges(size_t x, size_t y);

    void Relax(VertexObj &vertexes, VertexObj::VertexType &u);

    void DoSort();

    inline const AnchorObj::AnchorType &GetAnchorObj(AnchorObj::AnchorIndex index)
    {
        return _anchor.GetAnchor(index);
    }

    inline const VertexObj::PrecursorType &GetPrecursor(size_t index)
    {
        return _vertexObj.GetPrecursor(index);
    }

    inline const VertexObj::WeightType &GetPathValue(size_t index)
    {
        return _vertexObj.GetPathValue(index);
    }

    inline const VertexObj::WeightType &GetWeight(size_t index)
    {
        return _vertexObj.GetWeight(index);
    }

    inline const size_t GetIndex(size_t index)
    {
        return _vertexObj.GetIndex(index);
    }

private:
    bool _DoSort(AnchorObj::AnchorIndex index, VertexObj &leftVertex);
    ArrayObj &_cells;
    VertexObj _vertexObj;
    AnchorObj _anchor;
    const int x;
    const int y;
};

template <class Type>
void FloodProblem<Type>::InitSource()
{
    size_t anchorIndex = AnchorObj::TOP_LEFT;
    size_t vertexIndex = 0;
    size_t vertexPre = 0;

    size_t max_top = 0;

    const size_t xLen = XLEN;
    const size_t yLen = YLEN;

    for (size_t i = 0; i < xLen; ++i)
    {
        for (size_t j = 0; j < yLen; ++j)
        {
            if (_cells[i][j] == 0)
            {
                if (anchorIndex == AnchorObj::TOP_LEFT)
                {
                    max_top = j;
                    vertexPre = vertexIndex;

                    ++anchorIndex;
                }
                else if (anchorIndex == AnchorObj::TOP_RIGHT)
                {
                    if (max_top <= j)
                    {
                        _anchor.Insert(AnchorObj::TOP_LEFT, vertexPre);
                        _anchor.Insert(AnchorObj::TOP_RIGHT, vertexIndex);
                    }
                    else
                    {
                        _anchor.Insert(AnchorObj::TOP_LEFT, vertexIndex);
                        _anchor.Insert(AnchorObj::TOP_RIGHT, vertexPre);
                    }
                    ++anchorIndex;
                }
                else if (anchorIndex == AnchorObj::BOTTOM_LEFT)
                {
                    max_top = j;
                    vertexPre = vertexIndex;

                    ++anchorIndex;
                }
                else if (anchorIndex == AnchorObj::BOTTOM_RIGHT)
                {
                    if (max_top <= j)
                    {
                        _anchor.Insert(AnchorObj::BOTTOM_LEFT, vertexPre);
                        _anchor.Insert(AnchorObj::BOTTOM_RIGHT, vertexIndex);
                    }
                    else
                    {
                        _anchor.Insert(AnchorObj::BOTTOM_LEFT, vertexIndex);
                        _anchor.Insert(AnchorObj::BOTTOM_RIGHT, vertexPre);
                    }

                    ++anchorIndex;
                }
                else
                {
                    assert(0);
                }
            }

            _vertexObj.Push(vertexIndex, _cells[i][j]);
            BuildEdges(i, j);
            ++vertexIndex;
        }
    }
}

template <class Type>
void FloodProblem<Type>::BuildEdges(size_t x, size_t y)
{
    switch (x)
    {
    case 0:
        switch (y)
        {
        case 0:
            _vertexObj[0].edges.push_back(1);
            _vertexObj[0].edges.push_back(YLEN);
            _vertexObj[0].edges.push_back(YLEN + 1);
            break;
        case YLEN - 1:
            _vertexObj[YLEN - 1].edges.push_back(YLEN - 2);
            _vertexObj[YLEN - 1].edges.push_back(2 * YLEN - 2);
            _vertexObj[YLEN - 1].edges.push_back(2 * YLEN - 1);
            break;
        default:
            _vertexObj[y].edges.push_back(y - 1);
            _vertexObj[y].edges.push_back(y + 1);
            _vertexObj[y].edges.push_back(y + YLEN - 1);
            _vertexObj[y].edges.push_back(y + YLEN);
            _vertexObj[y].edges.push_back(y + YLEN + 1);
            break;
        }
        break;
    case XLEN - 1:
        switch (y)
        {
        case 0:
            _vertexObj[(XLEN - 1) * YLEN].edges.push_back((XLEN - 2) * YLEN);
            _vertexObj[(XLEN - 1) * YLEN].edges.push_back((XLEN - 2) * YLEN + 1);
            _vertexObj[(XLEN - 1) * YLEN].edges.push_back((XLEN - 1) * YLEN + 1);

            break;
        case YLEN - 1:
            _vertexObj[XLEN * YLEN - 1].edges.push_back((XLEN - 1) * YLEN - 1);
            _vertexObj[XLEN * YLEN - 1].edges.push_back((XLEN - 1) * YLEN - 2);
            _vertexObj[XLEN * YLEN - 1].edges.push_back(XLEN * YLEN - 2);
            break;
        default:
        {
            size_t bottom = (XLEN - 1) * YLEN + y;
            _vertexObj[bottom].edges.push_back((XLEN - 2) * YLEN + y - 1);
            _vertexObj[bottom].edges.push_back((XLEN - 2) * YLEN + y);
            _vertexObj[bottom].edges.push_back((XLEN - 2) * YLEN + y + 1);
            _vertexObj[bottom].edges.push_back((XLEN - 1) * YLEN + y - 1);
            _vertexObj[bottom].edges.push_back((XLEN - 1) * YLEN + y + 1);
        }
        break;
        }
        break;
    default: // 0 <x < XLEN -1
        switch (y)
        {
        case 0:
        {
            size_t left = x * YLEN;
            _vertexObj[left].edges.push_back(left - YLEN);
            _vertexObj[left].edges.push_back(left - YLEN + 1);
            _vertexObj[left].edges.push_back(left + 1);
            _vertexObj[left].edges.push_back(left + YLEN);
            _vertexObj[left].edges.push_back(left + YLEN + 1);
            break;
        }

        case YLEN - 1:
        {
            size_t right = x * YLEN + YLEN - 1;
            _vertexObj[right].edges.push_back(right - YLEN);
            _vertexObj[right].edges.push_back(right - YLEN - 1);
            _vertexObj[right].edges.push_back(right - 1);
            _vertexObj[right].edges.push_back(right + YLEN);
            _vertexObj[right].edges.push_back(right + YLEN - 1);
            break;
        }
        default:
        {
            size_t middle = x * YLEN + y;
            _vertexObj[middle].edges.push_back(middle - YLEN - 1);
            _vertexObj[middle].edges.push_back(middle - YLEN);
            _vertexObj[middle].edges.push_back(middle - YLEN + 1);
            _vertexObj[middle].edges.push_back(middle - 1);
            _vertexObj[middle].edges.push_back(middle + 1);
            _vertexObj[middle].edges.push_back(middle + YLEN - 1);
            _vertexObj[middle].edges.push_back(middle + YLEN);
            _vertexObj[middle].edges.push_back(middle + YLEN + 1);
        }
        break;
        }
        break;
    }
}

template <class Type>
void FloodProblem<Type>::Relax(VertexObj &vertexes, VertexObj::VertexType &u)
{
    VertexObj::EdgesType &edge = u.edges;

    for (auto it = edge.begin(); it != edge.end(); ++it)
    {
        VertexObj::VertexType &v = vertexes[*it];
        assert(v.index == *it);

        if (v.path > u.path + v.weight)
        {
            v.path = u.path + v.weight;
            v.pre = u.index;
        }
    }
}

template <class Type>
bool FloodProblem<Type>::_DoSort(AnchorObj::AnchorIndex index, VertexObj &vertex)
{
    assert(VertexObj::NIL == vertex.GetPathValue(_anchor.GetAnchor(index)));
    vertex.SetPathValue(_anchor.GetAnchor(index), 0);

    while (!vertex.Empty())
    {
        VertexObj::VertexType &u = vertex.Popup();

        Relax(vertex, u);
    }

    return true;
}

template <class Type>
void FloodProblem<Type>::DoSort()
{
    VertexObj topVertex = _vertexObj;
    _DoSort(AnchorObj::TOP_LEFT, topVertex);

    _anchor.SetEdages(topVertex);

    //VertexObj bottomVertex = _vertexObj;
    _DoSort(AnchorObj::BOTTOM_RIGHT, _vertexObj);
    _anchor.SetEdages(topVertex);
}

template <class Type>
inline FloodProblem<Type> MakeFloodProblemInstance(Type &data)
{
    return FloodProblem<Type>(data);
}

#endif
