# -*- coding: utf8 -*-
#-------------------------------------------------------------------------------
# @Author      : hejia
# @Created     : 2015/1/13
# @Desc        : log模块
#-------------------------------------------------------------------------------

import sys
import os
import cm

# "red" "green" "blue" "yellow" "cyan" "magenta" "white"
# "red_h" "green_h" "blue_h" "yellow_h" "cyan_h" "magenta_h" "white_h"

class OutPut:
	def __init__(self):
		self.__curLineWrtCnt = 0

	def write(self, s):
		fd = open("log.text","a")
		fd.write(s)
		fd.close()

		if str(s) == "\n":
			self.__curLineWrtCnt = -1
		if self.__curLineWrtCnt == 0:
			cm.cwrite("python:  ", "yellow_h", "")
		self.__curLineWrtCnt += 1

		cm.cwrite(str(s))  # c++层使用gbk编码, c++层已做处理
		
	def writeline(self, sl):
		map(self.write, sl)

	def flush(self):
		pass

class ErrOutPut:
	def write(self, s):
		fd = open("log.text","a")
		fd.write(s)
		fd.close()
		cm.cwrite(str(s),"red_h", "")
		
	def writeline(self, sl):
		map(self.write, sl)


def init():
	# 清空log
	fd = open("log.text","w")
	fd.write("")
	fd.close()

	# python输出重定向
	sys.stdout = OutPut()
	sys.stderr = ErrOutPut()






