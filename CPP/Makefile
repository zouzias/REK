CXX=g++
CXXFLAGS =	-O2 -g -Wall -std=gnu++0x

OBJS =		REK-CPP.o vector/DoubleVector.o \
					vector/SparseVector.o vector/DenseVector.o \
					matrix/DoubleMatrix.o matrix/impl/DenseMatrix.o matrix/impl/SparseMatrix.o \
					algorithms/REKSolver.o samplers/AliasSampler.o

LIBS = -lm

TARGET =	REK-CPP

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)


test: testSampler

testSampler: testSampler.o samplers/AliasSampler.o
	$(CXX) -c testSampler.cpp
	$(CXX) -o testSampler testSampler.o samplers/AliasSampler.o $(LIBS)
	./testSampler
	


clean:
	rm -f $(OBJS) $(TARGET) *.o
