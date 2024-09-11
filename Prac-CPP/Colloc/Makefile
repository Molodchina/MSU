TARGET := main
OBJECTS := main.cpp

LIBS := -lm -ldl

CPPFLAGS := -Wall -Werror -std=gnu++2b -O2
COLLOC := -fno-elide-constructors -O -std=gnu++11

CPP := g++


all: $(OBJECTS)
	$(CPP) $(COLLOC) $(OBJECTS) -o $(TARGET) $(LIBS)

.PHONY: clean help

clean:
	rm -f $(TARGET)
	
help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'