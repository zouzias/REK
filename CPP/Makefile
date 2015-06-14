CXX=g++
CXXFLAGS =	-O2 -g -Wall -std=gnu++0x

OBJS =	 vector/DoubleVector.o vector/SparseVector.o vector/DenseVector.o \
					matrix/DoubleMatrix.o matrix/impl/DenseMatrix.o matrix/impl/SparseMatrix.o \
					algorithms/REKSolver.o samplers/AliasSampler.o

LIBS = -lm
TARGET =	main

$(TARGET):	$(OBJS)
	$(CXX) -c main.cpp
	$(CXX) -o $(TARGET) 	main.o $(OBJS) $(LIBS)

all:	$(TARGET)

test: testSampler testDense testSparse

testSampler: testSampler.o samplers/AliasSampler.o
	$(CXX) -c testSampler.cpp
	$(CXX) -o testSampler testSampler.o samplers/AliasSampler.o $(LIBS)
	./testSampler

testDense: testDense.o ${OBJS}
	$(CXX) -c testDense.cpp
	$(CXX) -o testDense testDense.o ${OBJS} $(LIBS)
	./testDense

testSparse: testSparse.o ${OBJS}
	$(CXX) -c testSparse.cpp
	$(CXX) -o testSparse testSparse.o ${OBJS} $(LIBS)
	./testSparse

clean:
	rm -f $(OBJS) $(TARGET) *.o
