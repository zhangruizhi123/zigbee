#编译工具
CC = gcc
#项目根路径
PROJECT_PATH = /home/telrob/Desktop/zigbee
#引用到的库
MLIB = -lpthread -lmosquitto -lm -lcurl
#头文件包含路径
MINCLUDE = -I ${PROJECT_PATH}/include  -I /usr/local/include
#项目生产文件路径
OBJ_DIR = ${PROJECT_PATH}/bin
#项目源码路径
MSRC = ${PROJECT_PATH}/src
#项目名称
PNAME = smarthome
${PNAME}:
	${CC} -o  ${OBJ_DIR}/${PNAME}  ${MINCLUDE} ${MSRC}/*.c main.c  ${MLIB}
clear:
	rm -rf ${OBJ_DIR}/*