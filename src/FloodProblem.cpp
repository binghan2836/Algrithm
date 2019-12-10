/*
 * File: FloodProblem.cpp
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
#include "FloodProblem.h"

VertexObj::VertexType& VertexObj::Popup()
{
    QueueType queue;
    for(auto i = _vertexObjs.begin(); i != _vertexObjs.end(); ++i)
    {
        if(i->visted == 0)
            queue.push(*i);
    }

    VertexType& rslt = _vertexObjs[queue.top().index];
    rslt.visted = true;
    --_vertexLen;
    return rslt;
}

void AnchorObj::_SetEdges(const size_t index,const VertexObj &vertexs, VertexSet& sets,size_t source)
{
    AnchorType value =  index;

    while(1)
    {
        const VertexObj::VertexType &v = vertexs[value];
        VertexObj::PrecursorType pre = v.pre;

        if(pre == source || pre == VertexObj::NIL)//v.path == 0 ||
        {
            return;
        }

        assert(v.path != VertexObj::NIL);
        
        sets.insert(pre);

        value = pre;

        if(value == pre)
        {
            return;
        }
    }
}

void FloodProblem::Relax(VertexObj &vertexes, VertexObj::VertexType &u)
{
    VertexObj::EdgesType &edge = u.edges;

    for (auto it = edge.begin(); it != edge.end(); ++it)
    {
        VertexObj::VertexType &v = vertexes[*it];
        assert(v.index == *it);

        size_t rslt = 0;

        if(u.weight == 0)
        {
            rslt = v.weight;
        }
        else
        {
            rslt = u.path + v.weight;
        }
        
        if (v.path > rslt)
        {
            v.path = rslt;
            v.pre = u.index;
        }
    }
}

bool FloodProblem::_DoSort(size_t index, VertexObj &vertex, AnchorObj &anchor, AnchorObj::VertexSet& sets)
{
    size_t source = anchor.GetAnchor(index);
    assert(VertexObj::NIL == vertex[source].path);
    vertex[source].path = 0;

    while (!vertex.Empty())
    {
        VertexObj::VertexType &u = vertex.Popup();

        Relax(vertex, u);
    }

    anchor.SetEdages(vertex,sets,source);

    return true;
}

