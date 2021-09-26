import sys
import os
import shutil

# userBinDir = os.path.split(os.path.realpath('__file__'))[0]
# userBinDir = os.path.abspath(userBinDir)

binDir = r"F:\user\bin"
pythonPath = r"D:\Anaconda3\envs\SystemEnv"


def IsExistInRegister(fileName, exeDirNameExt):
	with open(fileName, 'r') as exeReisterTablet:
		for line in exeReisterTablet.readlines():
			splitLine = line.split() #分割字符串
			if len(splitLine) == 0:
				continue
			sourceWorkHub = splitLine[1]
			if sourceWorkHub == exeDirNameExt:
				aliasName = splitLine[0]
				return (line, aliasName)
	return ([], '')
	


if __name__ == "__main__":

	if len(sys.argv) <= 1:
		print("argument: fileName")
		exit(1)



	(exeDir, exeNameExt) = os.path.split(sys.argv[1])
	if len(exeDir) == 0:
		exeDir = os.getcwd()
	exeDir = os.path.abspath(exeDir)
	(exeName, exeExt) = os.path.splitext(exeNameExt)
	exeDirNameExt = os.path.join(exeDir,exeNameExt)



	if not os.path.isfile(exeDirNameExt):
		print("Could not find " + exeDirNameExt)
		exit(1)
	


	exeReisterTabletFullName = os.path.join(binDir,"RegisterTablet.txt")

	#如果有注册表，且注册表里面存在,查找信息
	aliasName = ''
	msg = ''
	if os.path.isfile(exeReisterTabletFullName):
		(msg, aliasName) = IsExistInRegister(exeReisterTabletFullName, exeDirNameExt)
	bExit = False if len(aliasName) == 0 else True
	
	
	destName = aliasName if bExit else exeName
	destNameExt = destName + ".bat"
	destDirNameExt = os.path.join(binDir,destNameExt)


	if bExit:
		print("**********************************************")
		print(msg)
		print(destName + " already exists")
		print("Do you want to replace it [y/n]?")
		bReplace = input()
		while bReplace != "n" and bReplace != "y":
			print("Do you want to replace it [y/n]?")
			bReplace = input()
		if bReplace == "n":
			print("install interrupt")
			exit(1)

	
	#编写相应的快捷方式
	if ".bat" == exeExt:
		if not shutil.move(exeDirNameExt, destDirNameExt):
			print("Could not move " + exeDirNameExt)
		else:
			print("move successfully")


	if ".py" == exeExt:
		with open(destDirNameExt, 'w') as batFile:
			batFile.write("@echo off\n")
			batFile.write(r"set pythonPath={}".format(pythonPath)+"\n")
			batFile.write(r"call %pythonPath%\python.exe {} %*".format(exeDirNameExt) + "\n")
		print("install successfully")
	
	if ".exe" == exeExt:
		with open(destDirNameExt, 'w') as batFile:
			batFile.write("@echo off\n")
			batFile.write(r"call {} %*".format(exeDirNameExt) + "\n")
		print("install successfully")



	#注册信息
	if not bExit:
		with open(exeReisterTabletFullName, 'a') as exeReisterTablet:
			exeReisterTablet.write(exeName+"        "+exeDirNameExt + '\n')









	

	

	