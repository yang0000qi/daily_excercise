#CXX=g++ -Wall -g
#PROG=simple_string_pc
CXX=arm-poky-linux-gnueabi-g++ -Wall -g
PROG=simple_string_arm
OBJS=proxy.o refstring.o test.o

$(PROG):$(OBJS)
	$(CXX) $^ -o $@

.SUFFIXES: .o .cpp

.cpp.o:
	$(CXX) -c $< 

clean:
	$(RM) $(OBJS) $(PROG)



