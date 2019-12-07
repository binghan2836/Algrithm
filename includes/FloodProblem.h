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
template<class Type>
class TwoDimensinalObj;

template<class Type,const size_t xLen, const size_t yLen>
class TwoDimensinalObj<Type[xLen][yLen]>
{
public:
    typedef Type DataContinerType[xLen][yLen];
    TwoDimensinalObj(DataContinerType & data):_dataContiner(data)
    {}

    inline const Type& GetValue(const size_t x,const size_t y) {return _dataContiner[x][y];}
    inline void SetValue(const size_t x,const size_t y,const Type &value){_dataContiner[x][y] = value;}

    inline DataContinerType& Cells() {return _dataContiner;}
    inline const size_t GetXLen(){return xLen;}
    inline const size_t GetYLen(){return yLen;}
private:
    DataContinerType &_dataContiner;
};

template<class Type>
TwoDimensinalObj<Type>  MakeTwoDimensinalObj(Type &data)
{
    return TwoDimensinalObj<Type>(data); 
}

class AnchorObj
{

};


template<class Type>
class FloodProblem{
public:
    FloodProblem(Type &data):_cells(data){}
    
    bool GetAnchorObj(AnchorObj &anchor){
        const size_t xLen = _cells.GetXLen();
        const size_t yLen = _cells.GetYLen();
        for(size_t i = 0; i < xLen; ++i)
        {
            for(size_t j = 0; j < yLen; ++ j)
                if(_cells.Cells()[i][j] == -1)
                {
                    /**
                     * @brief handle anchors
                     * 
                     */
                }
        }
        return false;
    }

private:
    TwoDimensinalObj<Type> _cells;
};



template<class Type>
FloodProblem<Type>  MakeFloodProblemInstance(Type &data)
{
    return FloodProblem<Type>(data); 
}

#endif