import sys
import os
import shutil

# userBinDir = os.path.split(os.path.realpath('__file__'))[0]
# userBinDir = os.path.abspath(userBinDir)

binDir = r"F:\user\bin"




if __name__ == "__main__":

	if len(sys.argv) <= 2:
		print("argument: oldName    newName")
		exit(1)


	oldName = sys.argv[1]
	newName = sys.argv[2]
	newName = os.path.split(newName)[1]
	if "." in newName:
		newName = os.path.splitext(newName)[1]
	(exeDir, exeNameExt) = os.path.split(oldName)


	registerTabletDirNameExt = os.path.join(binDir,"RegisterTablet.txt")
	#查找注册表的信息
	bExit = False
	index = 0
	msg = ''
	batName = ''
	if os.path.isfile(registerTabletDirNameExt):
		with open(registerTabletDirNameExt, 'r') as rF:
			lines = rF.readlines()
			for line in lines:
				splitLine = line.split()
				if len(splitLine) == 0:
					index+=1
					continue
				batName = splitLine[0]
				sourceWorkHub = splitLine[1]
				(srcDir, srcNameExt) = os.path.split(sourceWorkHub)
				if oldName == batName or oldName == sourceWorkHub or exeNameExt == srcNameExt or oldName == (batName+".bat"):
					bExit = True
					msg = line
					break
				index +=1

	batNameExt = batName + ".bat"
	srcDirNameExt = os.path.join(binDir,batNameExt)
	dstNameExt = newName+".bat"
	dstDirNameExt = os.path.join(binDir, dstNameExt)


	if not bExit:
		print("Could not find "+oldName)
		exit(1)
	else:
		if not shutil.move(srcDirNameExt, dstDirNameExt):
			print("Could not rename " + oldName)
		else:
			print("rename successfully")
			print("new name is "+ newName)
			print("before")
			print(msg)
			length = len(batName)
			msg = newName + msg[length:]
			print("now")
			print(msg)

			lines[index] = msg
			with open(registerTabletDirNameExt, 'w') as wF:
				for wline in lines:
					wF.write(wline)
					

	

	


	













	

	

	