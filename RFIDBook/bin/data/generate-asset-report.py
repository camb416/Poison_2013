import re
import os

print "generating report..."

f = open('settings/book.xml','r')
f2 = open('report.html','w')
c = f.read()
#r = re.search('(?<=src=")[^"\n]*(?=")',c)
matches = re.findall('(?<=src=")[^"\n]*(?=")',c)
# (?<=src=")[^"\n]*(?=")
fileList = []

output_str = '<html><head><link rel="stylesheet/less" type="text/css" href="report.less"><script src="js/less-1.4.1.min.js" type="text/javascript"></script></head><body><table><tr><th>FILES USED IN BOOK</th><th>english?</th><th>common?</th><th>translatable</th></tr>'

def getImageTag(path):
	result = ""
	if path.find(".png")>-1:
		result = '<img src="'+path+'" />'

	return result

def isImage(path):
	result = False
	if path.find(".png")>-1:
		result = True
	return result

def getOpenLink(path):
	result = '<a href="'+path+'" target="_blank" >'
	return result

def getCloseLink(path):

	result = '</a>'

	return result

for item in matches:
	
	itempath = "assets/en/"+item
	hasEnglish = os.path.exists(itempath)
	itempath2 = "assets/common/"+item
	hasCommon = os.path.exists(itempath2)

	#print item + "\t"+str(hasEnglish)+"\t"+str(hasCommon)

	img_str = ""
	if hasCommon & hasEnglish:
		itemClass = "yellow"
	elif hasCommon | hasEnglish:
		itemClass = "green"
		if hasEnglish:
			img_str = itempath
		elif hasCommon:
			img_str = itempath2
	else:
		itemClass = "red"

	itemOutput_str = '<tr class="'+itemClass+'">'
	itemOutput_str += "<td>" + getOpenLink(img_str)+ item + getCloseLink(img_str) + "</td><td>"+ str(hasEnglish)+"</td><td>"+str(hasCommon)+"</td><td>"+str(hasEnglish)+"</td></tr>"
	output_str += "\n" + itemOutput_str
	fileList.append(item)


output_str += '</table><table class="table2"><th>ASSET FOLDER LISTING</th></table>'






def list_files(startpath):
	result = ""
	for root, dirs, files in os.walk(startpath):
		level = root.replace(startpath, '').count(os.sep)
		indent = ' ' * 4 * (level)
		result += '<div class="folder" style="margin-left:'+str(40*(level+1))+';">'+('{}{}/'.format(indent, os.path.basename(root)))+"</div>"
		subindent = ' ' * 4 * (level + 1)

		for f in files:
			if(f[0]!='.'):
				tempstring = root+"/"+f

				tempstring2 = tempstring.replace("assets/","")

				tempstring3 = re.sub('^.*?/',"",tempstring2)
				foundFlag = False
				itemClass = "green"
				for listitem in fileList:
					if tempstring3 == listitem:
						foundFlag = True
						break
				if foundFlag==False:
					# print "file not found."
					itemClass = "red"

				result += '<div style="width:400px; margin-left:'+str(40*(level+1))+'px" class="'+itemClass+'" >'+getOpenLink(tempstring) + ('{}{}'.format(subindent, f)) +getCloseLink(tempstring) +' '+'</div>\n'
	return result

# print list_files(".")
output_str += list_files("assets")
f.close()
f2.write(output_str)
f2.close()
print "\nreport generated.\n"