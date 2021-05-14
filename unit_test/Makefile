# Makefile for gtest examples

GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include
QT_CORE_INCLUDE = /usr/include/qt/QtCore
QT_INCLUDE = /usr/include/qt
JELYAZKA_INCLUDE = ../source

G++ = g++
G++_FLAGS = -c -Wall -D_REENTRANT -fPIC -DQT_NO_VERSION_TAGGING -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_SQL_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -I $(GOOGLE_TEST_INCLUDE) -I $(QT_CORE_INCLUDE) -I $(QT_INCLUDE) -I $(JELYAZKA_INCLUDE)
LD_FLAGS = -L /usr/local/lib /usr/lib/libQt5Widgets.so /usr/lib/libQt5Gui.so /usr/lib/libQt5Sql.so /usr/lib/libQt5Network.so /usr/lib/libQt5Core.so -l $(GOOGLE_TEST_LIB) -l pthread

OBJECTS = main.o search_test.o ../source/search.o

TARGET = jelyazka_unit_test
all: $(TARGET)


$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o: %.cpp
	$(G++) $(G++_FLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
