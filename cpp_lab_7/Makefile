CXX := g++
CXXFLAGS := -std=c++17 -Wall \
            -Iheaders \
            -Itemplates \
            -Iutils \
            -Istring

TARGET := cpp_lab_7

SRCS := src/Clock.cpp \
        src/ElectronicClock.cpp \
        src/MechanicalClock.cpp \
        src/SmartClock.cpp \
        src/WallClock.cpp \
        src/WristClock.cpp \
        utils/string_utils.cpp \
        main.cpp

OBJS := $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
