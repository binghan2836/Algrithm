/*
 * File: FloodProblem.h
 * Project: future stream
 * Created Date: Sunday December 1st 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Saturday December 7th 2019 10:51:58 am
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
    typedef Type ItemType;
    TwoDimenTypeTraits(DataContinerType &data) : _dataContiner(data)
    {
    }

    inline const Type &GetValue(const size_t x, const size_t y) { return _dataContiner[x][y]; }
    inline void SetValue(const size_t x, const size_t y, const Type &value) { _dataContiner[x][y] = value; }

    inline DataContinerType &Cells() { return _dataContiner; }
    inline const size_t GetXLen() { return xLen; }
    inline const size_t GetYLen() { return yLen; }

private:
    DataContinerType &_dataContiner;
};

template <class Type>
TwoDimenTypeTraits<Type> MakeTwoDimenTypeTraits(Type &data)
{
    return TwoDimenTypeTraits<Type>(data);
}

class VertexObj
{
public:
    typedef size_t PrecursorType;
    typedef size_t WeightType;
    enum
    {
        NIL = std::numeric_limits<size_t>::max()
    };

    struct _Vertex
    {
        _Vertex() : index(NIL), weight(NIL), pre(NIL), path(NIL) {}

        _Vertex(size_t in, WeightType w, PrecursorType pre, WeightType path) : index(in), weight(w), pre(NIL), path(NIL) {}

        static bool VertexCmp(const _Vertex &rh, const _Vertex &lh)
        {
            return rh.path > lh.path;
        }

        size_t index;
        WeightType weight;
        PrecursorType pre;
        WeightType path;
        std::vector<size_t> edges;
    };

    typedef _Vertex VertexType;

    inline VertexObj(size_t len)
    {
        _vertexObjs.reserve(len);
    }

    void Push(VertexType v)
    {
        _vertexObjs.push_back(v);
    }

    void Push(size_t in, WeightType weight, PrecursorType pre = VertexObj::NIL, WeightType path = VertexObj::NIL)
    {
        _vertexObjs.push_back(VertexType(in, weight, pre, path));
    }

    bool Empty()
    {
        return _vertexObjs.empty();
    }

    VertexType &operator[](size_t index)
    {
        return _vertexObjs[index];
    }

    VertexType Popup()
    {
        std::make_heap(_vertexObjs.begin(), _vertexObjs.end(), VertexType::VertexCmp);

        VertexType rslt = _vertexObjs.front();
        _vertexObjs.pop_back();

        return rslt;
    }

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
    std::vector<_Vertex> _vertexObjs;
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
    typedef size_t AnchorType;

    inline void Insert(AnchorIndex index, size_t x)
    {
        _anchorObjs[index] = x;
    }
    inline const AnchorType &GetAnchor(const AnchorIndex ind)
    {
        return _anchorObjs[ind];
    }

private:
    AnchorType _anchorObjs[ANCHOR_LENGTH];
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
    typedef typename TwoDimenTypeTraits<Type>::DataContinerType ArrayType;
    FloodProblem(ArrayType &data) : _cells(data), _vertexObj(ARRAY_LEN) {}

    void InitSource();

    void BuildEdges(size_t x, size_t y);

    inline void Relax(VertexObj &vertexes, VertexObj::VertexType &u)
    {

        //if(GetVertexObj(v).dest > GetVertexObj(v) + )
        //size_t index = u.index;
    }

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
    ArrayType &_cells;
    VertexObj _vertexObj;
    AnchorObj _anchor;
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
            BuildEdges(i,j);
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
                size_t left = x* YLEN;
                _vertexObj[left].edges.push_back(left - YLEN);
                _vertexObj[left].edges.push_back(left - YLEN + 1);
                _vertexObj[left].edges.push_back(left + 1);
                _vertexObj[left].edges.push_back(left + YLEN);
                _vertexObj[left].edges.push_back(left + YLEN + 1);
                break;
            }
            
        case YLEN - 1:
            {
                size_t right = x* YLEN + YLEN - 1;
                _vertexObj[right].edges.push_back(right - YLEN);
                _vertexObj[right].edges.push_back(right - YLEN - 1);
                _vertexObj[right].edges.push_back(right - 1);
                _vertexObj[right].edges.push_back(right + YLEN);
                _vertexObj[right].edges.push_back(right + YLEN - 1);
                break;
            }
        default:
            {
                size_t middle = x* YLEN + y;
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
bool FloodProblem<Type>::_DoSort(AnchorObj::AnchorIndex index, VertexObj &leftVertex)
{

    VertexObj vertex = _vertexObj;

    size_t loopTime = ARRAY_LEN - 1;

    VertexObj::VertexType u;

    assert(VertexObj::NIL == vertex.GetPathValue(_anchor.GetAnchor(index)));
    vertex.SetPathValue(_anchor.GetAnchor(index), 0);

    while (vertex.Empty())
    {
        u = vertex.Popup();
        leftVertex.Push(u);

        Relax(vertex, u);

        if (--loopTime)
        {
            break;
        }
    }

    return false;
}

template <class Type>
void FloodProblem<Type>::DoSort()
{
    VertexObj leftVertex(ARRAY_LEN);
    _DoSort(AnchorObj::TOP_LEFT, leftVertex);
}

template <class Type>
inline FloodProblem<Type> MakeFloodProblemInstance(Type &data)
{
    return FloodProblem<Type>(data);
}

#endif