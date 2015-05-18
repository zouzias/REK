CXX=g++
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		REK-CPP.o vector/DoubleVector.o vector/SparseVector.o vector/DenseVector.o matrix/impl/DenseMatrix.o matrix/impl/SparseMatrix.o matrix/DoubleMatrix.o algorithms/LeastSquaresSolver.o algorithms/REKSolver.o

LIBS = -lm

TARGET =	REK-CPP

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *.o
