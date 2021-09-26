import sys
import os
import shutil

# userBinDir = os.path.split(os.path.realpath('__file__'))[0]
# userBinDir = os.path.abspath(userBinDir)

binDir = r"F:\user\bin"




if __name__ == "__main__":

	registerTabletDirNameExt = os.path.join(binDir,"RegisterTablet.txt")
	#查找注册表的信息
	if os.path.isfile(registerTabletDirNameExt):
		with open(registerTabletDirNameExt, 'r') as rF:
			lines = rF.readlines()
		for eachLine in lines:
			eachList = eachLine.split()
			if len(eachList) == 0:
				continue
			print(eachList[0].ljust(25) + eachList[1])

