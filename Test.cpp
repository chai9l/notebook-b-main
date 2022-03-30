#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"
using namespace ariel;

#include <string>
#include <algorithm>

using namespace std;
Notebook notebook;

TEST_CASE("Good Input") {
    
    notebook.write(1,1,1,Direction::Horizontal,"barcelona");
    CHECK(notebook.read(1,1,1,Direction::Horizontal,5)=="barce");
    notebook.erase(1,1,1,Direction::Horizontal, 9);
    CHECK(notebook.read(1,1,1,Direction::Horizontal,5)=="~~~~~");
    CHECK(notebook.read(2,2,2,Direction::Horizontal,5)=="_____");
    
    // Ascii art
    notebook.write(3,3,3,Direction::Horizontal,">@)_//");
    notebook.write(3,4,3,Direction::Horizontal," (__) ");
    CHECK(notebook.read(3,3,3,Direction::Horizontal,6) != ">-)_//");
    CHECK(notebook.read(3,4,3,Direction::Horizontal,6) == " (__) ");
    notebook.erase(3,3,3,Direction::Horizontal,6);
    CHECK(notebook.read(3,3,3,Direction::Horizontal,6) != ">@)_//");
    CHECK(notebook.read(3,3,3,Direction::Horizontal,6) == "~~~~~~");

    notebook.write(3,5,3,Direction::Horizontal,"()=()");
    notebook.write(3,6,3,Direction::Horizontal,"(^;^)");
    notebook.write(3,7,3,Direction::Horizontal,"C   C");
    notebook.write(3,8,3,Direction::Horizontal,"()_()");
    CHECK(notebook.read(3,5,3,Direction::Horizontal,5) == "()=()");
    CHECK(notebook.read(3,6,3,Direction::Horizontal,5) != "(-.-)");
    CHECK(notebook.read(3,7,3,Direction::Horizontal,5) != "(...)");
    CHECK(notebook.read(3,8,3,Direction::Horizontal,5) == "()_()");

    notebook.write(4,1,4,Direction::Horizontal,"    0  ");
    notebook.write(4,2,4,Direction::Horizontal," _ /-_ ");
    notebook.write(4,3,4,Direction::Horizontal,"(*)>(*)");
    notebook.write(4,4,4,Direction::Horizontal,"--------");
    notebook.write(4,6,4,Direction::Horizontal,"--------");
    CHECK(notebook.read(4,1,4,Direction::Horizontal,7) == "    0  ");
    CHECK(notebook.read(4,2,4,Direction::Horizontal,7) == " _ /-_ ");
    CHECK(notebook.read(4,3,4,Direction::Horizontal,7) == "(*)>(*)");
    CHECK(notebook.read(4,4,4,Direction::Horizontal,7) == "-------");
    CHECK(notebook.read(4,5,4,Direction::Horizontal,7) == "_______");
    CHECK(notebook.read(4,6,4,Direction::Horizontal,7) == "-------");

    notebook.write(5,0,0,Direction::Vertical,"@@@@@@@");
    notebook.write(5,0,1,Direction::Vertical,"@-----@");
    notebook.write(5,0,2,Direction::Vertical,"@-@@@-@");
    notebook.write(5,0,3,Direction::Vertical,"@-@-@-@");
    notebook.write(5,0,4,Direction::Vertical,"@-@@@-@");
    notebook.write(5,0,5,Direction::Vertical,"@-----@");
    notebook.write(5,0,6,Direction::Vertical,"@@@@@@@");
    // CHECK(notebook.read(5,0,0,Direction::Horizontal,7) == "@@@@@@@");
    // CHECK(notebook.read(5,1,0,Direction::Horizontal,7) == "@-----@");
    // CHECK(notebook.read(5,2,0,Direction::Horizontal,7) == "@-@@@-@");
    // CHECK(notebook.read(5,3,0,Direction::Horizontal,7) == "@-@-@-@");
    // CHECK(notebook.read(5,4,0,Direction::Horizontal,7) == "@-@@@-@");
    // CHECK(notebook.read(5,5,0,Direction::Horizontal,7) == "@-----@");
    // CHECK(notebook.read(5,6,0,Direction::Horizontal,7) == "@@@@@@@");

}

TEST_CASE("Bad Input") {
    // Negative Numbers
    CHECK_THROWS(notebook.read(-1,0,0,Direction::Vertical,5));
    CHECK_THROWS(notebook.read( 0,-1,0,Direction::Vertical,5));
    CHECK_THROWS(notebook.read( 0,0,-1,Direction::Vertical,5));
    CHECK_THROWS(notebook.read(-1,-2,-3,Direction::Vertical,5));
    CHECK_THROWS(notebook.read( 1,0,0,Direction::Vertical,-5));
    // Bad asci sign
    CHECK_THROWS(notebook.write( 0,0,0,Direction::Vertical,"~~~"));

}