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

#include <utility>
#include <limits>

template <class Type>
class TwoDimensinalObj;

template <class Type, const size_t xLen, const size_t yLen>
class TwoDimensinalObj<Type[xLen][yLen]>
{
public:
    enum
    {
        XLEN = xLen,
        YLEN = yLen
    };
    typedef Type DataContinerType[xLen][yLen];
    TwoDimensinalObj(DataContinerType &data) : _dataContiner(data)
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
TwoDimensinalObj<Type> MakeTwoDimensinalObj(Type &data)
{
    return TwoDimensinalObj<Type>(data);
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

private:
    struct _Vertex
    {
        _Vertex() : pre(NIL), path(NIL), weight(NIL) {}

        PrecursorType pre;
        WeightType path;
        WeightType weight;
    };

public:
    typedef _Vertex VertexType;

    VertexObj(size_t len)
    {
        _vertexObjs.resize(len);
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
    typedef std::pair<size_t, size_t> AnchorType;

    inline void Insert(AnchorIndex index, size_t x, size_t y)
    {
        _anchorObjs[index] = std::make_pair(x, y);
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
    FloodProblem(Type &data) : _cells(data), _vertexObj(TwoDimensinalObj<Type>::XLEN * TwoDimensinalObj<Type>::YLEN) {}

    void InitSource()
    {
        size_t anchorIndex = AnchorObj::TOP_LEFT;
        size_t vertexIndex = 0;

        size_t max_left = 0;
        size_t max_top = 0;

        const size_t xLen = _cells.XLEN;
        const size_t yLen = _cells.YLEN;

        for (size_t i = 0; i < xLen; ++i)
        {
            for (size_t j = 0; j < yLen; ++j)
            {
                if (_cells.Cells()[i][j] == 0)
                {
                    if (anchorIndex == AnchorObj::TOP_LEFT)
                    {
                        max_left = i;
                        max_top = j;

                        ++anchorIndex;
                    }
                    else if (anchorIndex == AnchorObj::TOP_RIGHT)
                    {
                        if (max_top <= j)
                        {
                            _anchor.Insert(AnchorObj::TOP_LEFT, max_left, max_top);
                            _anchor.Insert(AnchorObj::TOP_RIGHT, i, j);
                        }
                        else
                        {
                            _anchor.Insert(AnchorObj::TOP_LEFT, i, j);
                            _anchor.Insert(AnchorObj::TOP_RIGHT, max_left, max_top);
                        }
                        ++anchorIndex;
                    }
                    else if (anchorIndex == AnchorObj::BOTTOM_LEFT)
                    {
                        max_left = i;
                        max_top = j;

                        ++anchorIndex;
                    }
                    else if (anchorIndex == AnchorObj::BOTTOM_RIGHT)
                    {
                        if (max_top <= j)
                        {
                            _anchor.Insert(AnchorObj::BOTTOM_LEFT, max_left, max_top);
                            _anchor.Insert(AnchorObj::BOTTOM_RIGHT, i, j);
                        }
                        else
                        {
                            _anchor.Insert(AnchorObj::BOTTOM_LEFT, i, j);
                            _anchor.Insert(AnchorObj::BOTTOM_RIGHT, max_left, max_top);
                        }

                        ++anchorIndex;
                    }
                    else
                    {
                        assert(0);
                    }
                }
                
                _vertexObj.SetWeight(vertexIndex, _cells.Cells()[i][j]);
                ++ vertexIndex;
            }
        }
    }

    inline void Relax(size_t u, size_t v, size_t wight)
    {
        //if(GetVertexObj(v).dest > GetVertexObj(v) + )
    }

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

private:
    TwoDimensinalObj<Type> _cells;
    VertexObj _vertexObj;
    AnchorObj _anchor;
};

template <class Type>
FloodProblem<Type> MakeFloodProblemInstance(Type &data)
{
    return FloodProblem<Type>(data);
}

#endif