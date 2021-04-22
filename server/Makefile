CC=g++
prom = main
deps = ServerConnect.h MyDB.h
obj = main.o ServerConnect.o MyDB.o
ARG := -lmysqlclient -g

$(prom): $(obj)
	$(CC) -o $(prom) $(obj) $(ARG)

#%.o:%.c 所有的.o目标都依赖于与它同名的.c文件
#当然还有deps中列出的头文件
#$<  第一个依赖文件    $@目标文件   $^所有的依赖文件
%.o:%.cpp $(deps)
	$(CC) -c $< -o $@ $(ARG)

clean:
	rm -rf $(obj) $(prom)
