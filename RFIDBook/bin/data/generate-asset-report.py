import re
import os

f = open('settings/book.xml','r')
f2 = open('report.html','w')
c = f.read()
#r = re.search('(?<=src=")[^"\n]*(?=")',c)
matches = re.findall('(?<=src=")[^"\n]*(?=")',c)
# (?<=src=")[^"\n]*(?=")
fileList = []

output_str = '<html><head><link rel="stylesheet" type="text/css" href="report.css"></head><body><table><tr><th>FILES USED IN BOOK</th><th>english?</th><th>common?</th><th>translatable</th></tr>'

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
			img_str = '<img src="'+itempath+'" />'
		elif hasCommon:
			img_str = '<img src="'+itempath2+'" />'
	else:
		itemClass = "red"

	itemOutput_str = '<tr class="'+itemClass+'">'
	itemOutput_str += "<td>" + item + "</td><td>"+ str(hasEnglish)+"</td><td>"+str(hasCommon)+"</td><td>"+str(hasEnglish)+"</td><td>"+img_str+"</td></tr>"
	output_str += "\n" + itemOutput_str
	fileList.append(item)


output_str += "</table><table><th>OTHER FILES</th></table>"


def getImageTag(path):
	result = ""
	if path.find(".png")>-1:
		result = '<img src="'+path+'" />'

	return result



def list_files(startpath):
	result = ""
	for root, dirs, files in os.walk(startpath):
		level = root.replace(startpath, '').count(os.sep)
		indent = ' ' * 4 * (level)
		result += ('{}{}/'.format(indent, os.path.basename(root)))+"\n"
		subindent = ' ' * 4 * (level + 1)

		for f in files:
			tempstring = root+"/"+f

			tempstring2 = tempstring.replace("assets/","")
			print tempstring2
			tempstring3 = re.sub('^.*?/',"",tempstring2)
			print "\t" + tempstring3
			foundFlag = False
			itemClass = "green"
			for listitem in fileList:
				if tempstring3 == listitem:
					foundFlag = True
					break
			if foundFlag:
				print "file found OK"

			else:
				print "file not found."
				itemClass = "red"

			result += '<div style="width:400px; margin-left:'+str(40*(level+1))+'px" class="'+itemClass+'" >'+('{}{}'.format(subindent, f)) +' '+getImageTag(tempstring)+'</div>\n'
	return result

# print list_files(".")
output_str += list_files("assets")

f2.write(output_str)
f2.close()