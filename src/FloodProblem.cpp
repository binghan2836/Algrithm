/*
 * File: FloodProblem.cpp
 * Project: future stream
 * Created Date: Sunday December 1st 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Sunday December 1st 2019 8:25:10 am
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

void AnchorObj::_SetEdges(const AnchorIndex index,const VertexObj &vertexs)
{
    AnchorType value = _anchorObjs[index];
    EdgesType & edges= _anchorEdges[index];
    while(1)
    {
        const VertexObj::VertexType &v = vertexs[value];

        if(v.path == 0)
        {
            edges.push_back(v.index);
            break;
        }

        assert(v.pre != VertexObj::NIL);
        assert(v.path != VertexObj::NIL);

        edges.push_back(v.index);

        value = v.pre;

    }
}
