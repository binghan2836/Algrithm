/*
 * File: FloodProblem.cpp
 * Project: future stream
 * Created Date: Sunday December 1st 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Saturday December 14th 2019 7:51:26 am
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
#include "FloodProblem.h"
#include <map>

VertexObj::VertexType &VertexObj::Popup()
{
    QueueType queue;
    for (auto i = _vertexObjs.begin(); i != _vertexObjs.end(); ++i)
    {
        if (i->visted == 0)
            queue.push(*i);
    }

    VertexType &rslt = _vertexObjs[queue.top().index];
    rslt.visted = true;
    --_vertexLen;
    return rslt;
}

void AnchorObj::_SetEdges(const size_t index, const VertexObj &vertexs, VertexSet &sets, size_t source)
{
    AnchorType value = index;

    while (1)
    {
        const VertexObj::VertexType &v = vertexs[value];
        VertexObj::PrecursorType pre = v.pre;

        if (pre == source)
        {
            sets.insert(pre);
            return;
        }
        else if (pre == VertexObj::NIL)
        {
            return;
        }

        assert(v.path != VertexObj::NIL);

        sets.insert(pre);

        value = pre;
    }
}

void FloodProblem::Relax(VertexObj &vertexes, VertexObj::VertexType &u)
{
    VertexObj::EdgesType &edge = u.edges;

    for (auto it = edge.begin(); it != edge.end(); ++it)
    {
        VertexObj::VertexType &v = vertexes[*it];

        if (v.index != *it)
        {
            assert(0);
        }

        size_t rslt = u.path + v.weight;

        if (v.path > rslt)
        {
            v.path = rslt;
            v.pre = u.index;
        }
    }
}

bool FloodProblem::_DoSort(size_t index, VertexObj &vertex, AnchorObj &anchor, AnchorObj::VertexSet &sets)
{
    size_t source = anchor.GetAnchor(index);
    assert(VertexObj::NIL == vertex[source].path);
    vertex[source].path = 0;

    while (!vertex.Empty())
    {
        VertexObj::VertexType &u = vertex.Popup();
        Relax(vertex, u);
    }

    anchor.SetEdages(vertex, sets, source);

    return true;
}

void FloodProblem::BuildEdges(const size_t x, const size_t y, VertexObj &vertexObj)
{
    if (x == 0)
    {
        if (y == 0)
        {
            vertexObj[0].edges.push_back(1);
            vertexObj[0].edges.push_back(_yLen);
            vertexObj[0].edges.push_back(_yLen + 1);
        }
        else if (y == _yLen - 1)
        {
            vertexObj[_yLen - 1].edges.push_back(_yLen - 2);
            vertexObj[_yLen - 1].edges.push_back(2 * _yLen - 2);
            vertexObj[_yLen - 1].edges.push_back(2 * _yLen - 1);
        }
        else
        {
            vertexObj[y].edges.push_back(y - 1);
            vertexObj[y].edges.push_back(y + 1);
            vertexObj[y].edges.push_back(y + _yLen - 1);
            vertexObj[y].edges.push_back(y + _yLen);
            vertexObj[y].edges.push_back(y + _yLen + 1);
        }
    }
    else if (x == _xLen - 1)
    {
        if (y == 0)
        {
            size_t leftTop = (_xLen - 1) * _yLen;
            vertexObj[leftTop].edges.push_back((_xLen - 2) * _yLen);
            vertexObj[leftTop].edges.push_back((_xLen - 2) * _yLen + 1);
            vertexObj[leftTop].edges.push_back((_xLen - 1) * _yLen + 1);
        }
        else if (y == _yLen - 1)
        {
            size_t rightTop = _xLen * _yLen - 1;
            vertexObj[rightTop].edges.push_back((_xLen - 1) * _yLen - 1);
            vertexObj[rightTop].edges.push_back((_xLen - 1) * _yLen - 2);
            vertexObj[rightTop].edges.push_back(_xLen * _yLen - 2);
        }
        else
        {
            size_t bottom = (_xLen - 1) * _yLen + y;
            vertexObj[bottom].edges.push_back((_xLen - 2) * _yLen + y - 1);
            vertexObj[bottom].edges.push_back((_xLen - 2) * _yLen + y);
            vertexObj[bottom].edges.push_back((_xLen - 2) * _yLen + y + 1);
            vertexObj[bottom].edges.push_back((_xLen - 1) * _yLen + y - 1);
            vertexObj[bottom].edges.push_back((_xLen - 1) * _yLen + y + 1);
        }
    }
    else
    {
        if (y == 0)
        {
            size_t left = x * _yLen;
            vertexObj[left].edges.push_back(left - _yLen);
            vertexObj[left].edges.push_back(left - _yLen + 1);
            vertexObj[left].edges.push_back(left + 1);
            vertexObj[left].edges.push_back(left + _yLen);
            vertexObj[left].edges.push_back(left + _yLen + 1);
        }
        else if (y == _yLen - 1)
        {
            size_t right = x * _yLen + _yLen - 1;
            vertexObj[right].edges.push_back(right - _yLen);
            vertexObj[right].edges.push_back(right - _yLen - 1);
            vertexObj[right].edges.push_back(right - 1);
            vertexObj[right].edges.push_back(right + _yLen);
            vertexObj[right].edges.push_back(right + _yLen - 1);
        }
        else
        {
            size_t middle = x * _yLen + y;
            vertexObj[middle].edges.push_back(middle - _yLen - 1);
            vertexObj[middle].edges.push_back(middle - _yLen);
            vertexObj[middle].edges.push_back(middle - _yLen + 1);
            vertexObj[middle].edges.push_back(middle - 1);
            vertexObj[middle].edges.push_back(middle + 1);
            vertexObj[middle].edges.push_back(middle + _yLen - 1);
            vertexObj[middle].edges.push_back(middle + _yLen);
            vertexObj[middle].edges.push_back(middle + _yLen + 1);
        }
    }
}

void FloodProblem::InitSource(VertexObj &vertexObj, AnchorObj &anchor)
{
    size_t(&cell)[_xLen][_yLen] = *reinterpret_cast<size_t(*)[_xLen][_yLen]>(_p);

    size_t vertexIndex = 0;

    for (size_t i = 0; i < _xLen; ++i)
    {
        for (size_t j = 0; j < _yLen; ++j)
        {
            if (cell[i][j] == 0)
            {
                anchor.Insert(vertexIndex);
            }

            vertexObj.Push(vertexIndex, cell[i][j]);
            BuildEdges(i, j, vertexObj);
            ++vertexIndex;
        }
    }
}

size_t FloodProblem::DoSort()
{
    AnchorObj anchor(_arrayLen);
    VertexObj vertexObj(_arrayLen);

    AnchorObj::VertexSet currentSets;

    InitSource(vertexObj, anchor);

    size_t setLen = anchor.GetAnchors().size();
    for (size_t index = 0; index < setLen; ++index)
    {
        VertexObj verCurrentObj = vertexObj;
        _DoSort(index, verCurrentObj, anchor, currentSets);
    }

    //layer vistor
    AnchorObj::VertexSet rsltVertexs;
    _LayerTravsal(anchor.GetAnchor(0), anchor.GetAnchorLength(), vertexObj, currentSets, rsltVertexs);

    VertexObj::WeightType rslt = 0;
    for (auto i : rsltVertexs)
    {
        std::cout << "<v(" << i << "):w(" << vertexObj[i].weight << ")>, ";
        rslt += vertexObj[i].weight;
    }

    return rslt;
}

struct PathRecodeObjType
{
    PathRecodeObjType(size_t l) : level(l) {}
    PathRecodeObjType() {}
    std::set<size_t> preIndexSets; //in
    std::set<size_t> nextIndexSets;
    size_t level;
};

void FloodProblem::_LayerTravsal(size_t start, size_t len, VertexObj &vertexMaps, AnchorObj::VertexSet &vertexsIn, AnchorObj::VertexSet &vertexsOut)
{
    typedef PathRecodeObjType PathRecodeObj;
    typedef std::map<size_t, PathRecodeObj> PathRecodeType;
    if (vertexsIn.size() < 3)
    {
        vertexsOut = vertexsIn;
        return;
    }

    PathRecodeType pathRecord;

    const size_t length = len;

    //trim duplcated path
    std::queue<size_t> layerMark;
    layerMark.push(start);

    pathRecord[start] = PathRecodeObj(1);

    size_t anchorMarks = 1;

    while (layerMark.size() && (anchorMarks < length))
    {
        size_t curr = layerMark.front();
        layerMark.pop();

        VertexObj::VertexType &vertexParents = vertexMaps[curr];
        VertexObj::EdgesType &edge = vertexParents.edges;

        vertexParents.visted++;

        for (auto it : edge)
        {
            //find in destination sets
            if (vertexsIn.find(it) != vertexsIn.end())
            {
                VertexObj::VertexType &vertexChild = vertexMaps[it];

                if (vertexChild.visted == 0)
                {
                    if (pathRecord.find(it) != pathRecord.end())
                    {
                        if (pathRecord[curr].level != pathRecord[it].level)
                        {
                            pathRecord[it].preIndexSets.insert(curr);
                            pathRecord[curr].nextIndexSets.insert(it);
                        }
                    }
                    else
                    {
                        pathRecord[it] = PathRecodeObj(pathRecord[curr].level + 1);

                        pathRecord[it].preIndexSets.insert(curr);
                        pathRecord[curr].nextIndexSets.insert(it);

                        layerMark.push(it);

                        if (vertexMaps[it].weight == 0)
                        { //try to jump out if we get enough anchors
                            ++anchorMarks;
                            if (anchorMarks >= length)
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    for (PathRecodeType::iterator path = pathRecord.begin(); path != pathRecord.end(); ++path)
    {
        vertexsOut.insert(path->first);
        if (path->second.preIndexSets.size() > 1)
        {
            for (auto pre : path->second.preIndexSets)
            {
                if (pathRecord[pre].nextIndexSets.size() < 2)
                {
                    vertexsOut.erase(pre);
                }
            }
        }
    }
}
