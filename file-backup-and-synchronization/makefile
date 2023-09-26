c = g++ -std=c++17
obj = build/function_source.o build/copy.o build/main.o build/source_sync_to_tar.o build/two_copy.o build/two_way_sync.o
RM = rm -rf
cflag = -g -pthread -I include/

run: main.o function_source.o copy.o source_sync_to_tar.o two_copy.o two_way_sync.o  
	$(c) -o run $(cflag) $(obj)

main.o:src/main.cpp include/fbas.h 
	$(c) -c -o ./build/main.o $(cflag) src/main.cpp

two_way_sync.o:src/two_way_sync.cpp include/fbas.h
	$(c) -c -o ./build/two_way_sync.o $(cflag) src/two_way_sync.cpp

two_copy.o:src/two_copy.cpp include/fbas.h
	$(c) -c -o ./build/two_copy.o $(cflag) src/two_copy.cpp

source_sync_to_tar.o:src/source_sync_to_tar.cpp include/fbas.h
	$(c) -c -o ./build/source_sync_to_tar.o $(cflag) src/source_sync_to_tar.cpp

function_source.o:src/function_source.cpp include/fbas.h
	$(c) -c -o ./build/function_source.o $(cflag) src/function_source.cpp

copy.o:src/copy.cpp include/fbas.h
	$(c) -c -o ./build/copy.o $(cflag) src/copy.cpp

.PHONY:clean

clean:
	$(RM) ./build ./run&&mkdir build
