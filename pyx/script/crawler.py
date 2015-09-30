# -*- coding:utf-8 -*-
import re
import os 
import urllib.request as urllib2
from bs4 import BeautifulSoup


def print_list(lData):
	print ("[")
	for x in lData:
		print ("\t", x)
	print ("]")

def getHtml(surl):
	req = urllib2.Request(surl)
	res = urllib2.urlopen(req)
	html = res.read()
	res.close()
	html = html.decode("utf8")
	return html
	# -----------------------------------------

def getTiebaLastPageNum(html):
	soup = BeautifulSoup(html, "html.parser")
	result = soup.find_all("li", class_="l_pager pager_theme_4 pb_list_pager")
	oLiTag = result[0]
	lLi = list(oLiTag.children)
	lLi = list(filter(lambda x:str(x)!="\n", lLi))
	oLastLiTag = lLi[-1]
	if oLastLiTag.getText() == "尾页":
		sHref = oLastLiTag["href"]
		sNum = sHref.rpartition("=")[2]
		iNum = int(sNum)
	else:
		sNum = oLastLiTag.getText()
		iNum = int(sNum)
	print("共", iNum, "页")
	return iNum

def extractTiebaPlainText(html):
	soup = BeautifulSoup(html, "html.parser")
	result = soup.find_all("div", class_="d_post_content j_d_post_content ")
	result = map(lambda x:str(x).replace("<br>", "<br>\n").replace("</br>", "</br>\n"), result)
	result = map(lambda x:BeautifulSoup(x, "html.parser").get_text().strip()+"\n\n", result)
	sResult = "".join(result)
	return sResult

def getTiebaNovel(surl, sTarFileName):
	# surl = "http://tieba.baidu.com/p/2721844934?see_lz=1&pn=1"
	surl = surl.rpartition("=")[0] + "=%s"
	html = getHtml(surl%1)
	iPage = getTiebaLastPageNum(html)
	sContent = ""
	for i in range(1, iPage + 1):
		print("process: ", surl%i)
		html = getHtml(surl%i)
		sResult = extractTiebaPlainText(html)
		sContent += sResult
	with open(sTarFileName, 'wb') as fd:
		fd.write(sContent.encode("utf8"))




def test():   #控制台不准
	surl = "http://tieba.baidu.com/p/2721844934?see_lz=1&pn=1"
	getTiebaNovel(surl, "content.txt")
	# 换行符要转换



