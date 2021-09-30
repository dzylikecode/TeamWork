import sys
import os

# userBinDir = os.path.split(os.path.realpath('__file__'))[0]
# userBinDir = os.path.abspath(userBinDir)

import laGlobal

binDir = laGlobal.binDir




if __name__ == "__main__":

	if len(sys.argv) <= 1:
		print("argument: fileName")
		exit(1)


	(exeDir, exeNameExt) = os.path.split(sys.argv[1])
	(exeName, exeExt) = os.path.splitext(exeNameExt)


	registerTabletDirNameExt = os.path.join(binDir,"RegisterTablet.txt")
	#查找注册表的信息
	bExit = False
	bRm = False
	batName = ''
	msg = ''
	if os.path.isfile(registerTabletDirNameExt):
		with open(registerTabletDirNameExt, 'r') as rF:
			lines = rF.readlines()
		with open(registerTabletDirNameExt, 'w') as wF:
			for wline in lines:
				splitLine = wline.split()		#wline有\n
				if len(splitLine) == 0:			#splitLine没有\n
					continue
				splitLine = wline.split('\n')
				splitLine = splitLine[0].split('\t')
				batName = splitLine[0]
				sourceWorkHub = splitLine[1]
				(srcDir, srcNameExt) = os.path.split(sourceWorkHub)
				(srcName, srcExt) = os.path.splitext(srcNameExt)
				if exeName == batName or exeName == srcName:
					bExit = True
					msg = wline
					print(msg)
					print("Do you want to uninstall it [y/n]?")
					bUninstall = input()
					while bUninstall != "n" and bUninstall != "y":
						print("Do you want to uninstall it [y/n]?")
						bUninstall = input()
					if bUninstall == "n":
						print("uninstall interrupt")
					else:
						print("remove from register tablet")
						bRm = True
						continue
				
				wF.write(wline)
					
	if bExit and bRm:
		batNameExt = batName + ".bat"
		batDirNameExt = os.path.join(binDir,batNameExt)
		#避免异常导致文件未被写入
		try:
			os.remove(batDirNameExt)
			if os.path.isfile(batDirNameExt):  #存在表明失败
				print("Remove failed")
				with open(registerTabletDirNameExt, 'a') as aF:
					aF.write(msg)
				print(msg)
				print("restore register tablet")
			else:
				print(msg)
				print("Remove successfully")
		except:
			print("Remove failed")
			with open(registerTabletDirNameExt, 'a') as aF:
				aF.write(msg)
			print(msg)
			print("restore register tablet")
		
	else:
		print(exeName + " not exists")

	

	


	













	

	

	