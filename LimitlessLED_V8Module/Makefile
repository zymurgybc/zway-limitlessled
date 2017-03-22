### Variables ###
TARGET = modsample.so

OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

INCLUDES = \
	-I. \
	-I/opt/z-way-server/libzway \
	-I/opt/z-way-server/modules-includes/z-way-js \
	-I/opt/z-way-server/modules-includes/v8

LIBS = -lzcommons -lv8 -lzwayjs -L/opt/z-way-server/libs

CFLAGS += -fpic

### Targets ###

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -shared $(TARGET_ARCH) $(LDFLAGS) -o $@ $^ $(LIBS)
	
%.o: %.cpp
	$(CXX) $(INCLUDES) $(CFLAGS) $(TARGET_ARCH) -c $< -o $@
		
clean:
	rm -f *.o $(TARGET)
			
.PHONY: all clean
				