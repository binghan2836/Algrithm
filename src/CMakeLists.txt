###
#File: CMakeLists.txt
#Project: future stream
#Created Date: Wednesday November 27th 2019
#Author: DaGai  <binghan2836@163.com>
#-----
#Last Modified: Wednesday November 27th 2019 1:50:48 pm
#Modified By:   the developer formerly known as DaGai
#-----
#MIT License
#
#Copyright (c) 2019 binghan2836@163.com
#
#Permission is hereby granted, free of charge, to any person obtaining a copy of
#this software and associated documentation files (the "Software"), to deal in
#the Software without restriction, including without limitation the rights to
#use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
#of the Software, and to permit persons to whom the Software is furnished to do
#so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.
#-----
#HISTORY:
#Date          By    Comments
#----------    ---    ----------------------------------------------------------
###


aux_source_directory(. Algorithm)
ADD_LIBRARY(algorithm STATIC ${Algorithm})