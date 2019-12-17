/*
 * File: FloodProblemTest.cpp
 * Project: future stream
 * Created Date: Sunday December 1st 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Friday December 13th 2019 9:11:04 pm
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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>
#include "RandomGenerator.h"
#include "FloodProblem.h"

#include <fstream>
#include <sstream>
#include <string>

size_t MyArray[200*200];

typedef std::vector<std::vector<size_t> > ContainerType;

class DataInput{
public:
    DataInput(std::string fileName):_name(fileName),_row(0),_col(0)
    {
        memset(MyArray,0,sizeof(MyArray));
    }
    const size_t GetRow(){return _row;}
    const size_t GetCol(){return _col;}
    bool GetData(size_t *c);
private:
    std::string _name;
    size_t _row;
    size_t _col;
};

bool DataInput::GetData(size_t *c)
{
    std::fstream file(_name);

    if(file.is_open() == false)
    {
        std::cout <<_name << " open error!\n";
        return false;
    }

    std::string line;
    size_t index = 0;

    while(std::getline(file,line))
    {   
        ++ _row;
        std::stringstream formtObj(line);
 
        while(formtObj >> c[index])
        {
            //formtObj >> c[index];
            ++ index;
        }
    }

    _col = index/_row;

    return true;
}

TEST(FloodProblemTest, SMallCase3)
{
    size_t data[] = {3,9,5,10,10,0,7,0,4,4,10,8,0,7,0,8};

    size_t (&matrix)[4][4] = *reinterpret_cast<size_t (*)[4][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),9);
}

TEST(FloodProblemTest, SMallCase1)
{
    size_t data[] = {9,0,3,10,3,4,4,0,7};
    size_t (&matrix)[3][3] = *reinterpret_cast<size_t (*)[3][3]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),3);
}


TEST(FloodProblemTest, SMallCase2)
{
    size_t data[] = {0,6,10,9,1,9,0,6,8,0,2,3,1,4,7,0,6,0,3,4};
    
    size_t (&matrix)[5][4] = *reinterpret_cast<size_t (*)[5][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),4);
}

TEST(FloodProblemTest, SMallCase4)
{
    size_t data[] = {6,8,0,3,1,1,0,9};

    size_t (&matrix)[4][2] = *reinterpret_cast<size_t (*)[4][2]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),1);
}

TEST(FloodProblemTest, SMallCase5)
{
    size_t data[] = {0,2,0,2,9,4,3,7,8,0,6,0,4,3,10,10};

    size_t (&matrix)[4][4] = *reinterpret_cast<size_t (*)[4][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),5);
}

TEST(FloodProblemTest, SMallCase6)
{
    size_t data[] = {5,1,0,1,3,7,0,9,4,10};

    size_t (&matrix)[5][2] = *reinterpret_cast<size_t (*)[5][2]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),3);
}

TEST(FloodProblemTest, SMallCase7)
{
    size_t data[] = {0,1,4,4,6,0};

    size_t (&matrix)[3][2] = *reinterpret_cast<size_t (*)[3][2]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),4);
}

TEST(FloodProblemTest, SMallCase8)
{
    size_t data[] = {8,0,5,5,5,1,5,7,0,7,0,5,0,4,9,1,2,4,1,0,8,0,5,0,10};

    size_t (&matrix)[5][5] = *reinterpret_cast<size_t (*)[5][5]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),4);
}

TEST(FloodProblemTest, SMallCase9)
{
    size_t data[] = {5,1,1,4,1,0,5,0,7,4,8,8};

    size_t (&matrix)[3][4] = *reinterpret_cast<size_t (*)[3][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),1);
}


TEST(FloodProblemTest, SMallCase10)
{
    size_t data[] = {3,6,5,0,6,5,0,8,7,7};

    size_t (&matrix)[2][5] = *reinterpret_cast<size_t (*)[2][5]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),5);
}

TEST(FloodProblemTest, SMallCase11)
{
    size_t data[] = {10,3,2,3,8,0,10,0,7,10,9,2};

    size_t (&matrix)[3][4] = *reinterpret_cast<size_t (*)[3][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),2);
}

TEST(FloodProblemTest, SMallCase12)
{
    size_t data[] = {6,0,2,0,8,8,3,2};

    size_t (&matrix)[2][4] = *reinterpret_cast<size_t (*)[2][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),2);
}

TEST(FloodProblemTest, SMallCase13)
{
    size_t data[] = {7,5,5,0,9,4,0,5,5,6,6,9,6,0,3,0,9,0,4,10};

    size_t (&matrix)[4][5] = *reinterpret_cast<size_t (*)[4][5]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),11);
}

TEST(FloodProblemTest, SMallCase14)
{
    size_t data[] = {5,9,3,4,7,6,0,5,0,9,3,10,3,7,2,5,0,3,0,7};

    size_t (&matrix)[4][5] = *reinterpret_cast<size_t (*)[4][5]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),3);
}

TEST(FloodProblemTest, SMallCase15)
{
    size_t data[] = {7,0,10,0,9,8,9,1};

    size_t (&matrix)[2][4] = *reinterpret_cast<size_t (*)[2][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),9);
}

TEST(FloodProblemTest, SMallCase16)
{
    size_t data[] = {9,6,0,10,0,6,1,7};

    size_t (&matrix)[2][4] = *reinterpret_cast<size_t (*)[2][4]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),6);
}

TEST(FloodProblemTest, SMallCase17)
{
    size_t data[] = {7,1,0,0,9,6};

    size_t (&matrix)[2][3] = *reinterpret_cast<size_t (*)[2][3]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),1);
}

TEST(FloodProblemTest, SMallCase18)
{
    size_t data[] = {2,4,9,7,0,3,1,7,10,7,0,3};

    size_t (&matrix)[4][3] = *reinterpret_cast<size_t (*)[4][3]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),1);
}

TEST(FloodProblemTest, SMallCase19)
{
    size_t data[] = {8,1,9,0,7,3,0,5,10,5,7,5,9,0,7};

    size_t (&matrix)[3][5] = *reinterpret_cast<size_t (*)[3][5]>(&data);

    EXPECT_EQ(SortFloodProblem(matrix),5);
}

std::string path = "/home/dev/newFormatTestCase";
TEST(FloodProblemTest,charactor0)
{
    DataInput input(path + "/small/charactor0.txt");

    input.GetData(MyArray);

    EXPECT_EQ(SortFloodProblem(reinterpret_cast<size_t **>(&MyArray),input.GetRow(),input.GetCol()),11);
}

TEST(FloodProblemTest,charactor1)
{
    DataInput input(path + "/small/charactor1.txt");

    input.GetData(MyArray);

    EXPECT_EQ(SortFloodProblem(reinterpret_cast<size_t **>(&MyArray),input.GetRow(),input.GetCol()),9);
}


TEST(FloodProblemTest,charactor2)
{
    DataInput input(path + "/small/charactor2.txt");

    input.GetData(MyArray);

    EXPECT_EQ(SortFloodProblem(reinterpret_cast<size_t **>(&MyArray),input.GetRow(),input.GetCol()),0);
}

TEST(FloodProblemTest,charactor3)
{
    DataInput input(path + "/small/charactor3.txt");

    input.GetData(MyArray);

    EXPECT_EQ(SortFloodProblem(reinterpret_cast<size_t **>(&MyArray),input.GetRow(),input.GetCol()),13);
}


TEST(FloodProblemTest,charactor4)
{
    DataInput input(path + "/small/charactor4.txt");

    input.GetData(MyArray);

    EXPECT_EQ(SortFloodProblem(reinterpret_cast<size_t **>(&MyArray),input.GetRow(),input.GetCol()),14);
}
