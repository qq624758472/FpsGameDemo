CC=g++
prom = main
deps = process_schedule.h
obj = main.o process_schedule.o

$(prom): $(obj)
	$(CC) -o $(prom) $(obj)

#%.o:%.c 所有的.o目标都依赖于与它同名的.c文件
#当然还有deps中列出的头文件
#$<  第一个依赖文件    $@目标文件   $^所有的依赖文件
%.o:%.c $(deps)
	$(CC) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)