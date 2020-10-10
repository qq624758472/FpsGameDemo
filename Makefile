#编译所有子目录
#SUBDIRS=`ls -d */ | grep -v 'bin' | grep -v 'lib' | grep -v 'include'`
#编译指定子目录
SUBDIRS= client server
#如果Makefile中出现一些相同命令序列，那么我们可以为这些相同的命令序列定义一个变量。定义这种命令序列的语法以“define”开始，以“endef”结束，如：
#   define run-yacc
#   yacc $(firstword $^)
#   mv y.tab.c $@
#   endef


#命令包的用法。
define make_subdir
	#for 循环的用法。
	for subdir in $(SUBDIRS) ; \
	do \
		( cd $$subdir && make $1) \
	done;
endef

define target
	(cd $(DIR) && make)
endef

all:
	$(call make_subdir )
install :
	$(call make_subdir , install)
debug:
	$(call make_subdir , debug)
clean:
	$(call make_subdir , clean) #后边是参数，传到命令包的参数。

target:
	$(call target)