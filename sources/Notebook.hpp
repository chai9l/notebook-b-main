
#include <vector>
#include <string>
#include "Direction.hpp"
using ariel::Direction;




using namespace std;

namespace ariel {
    
    class Row {
        public:
            vector<char> row;

            void write_char_to_row(const unsigned int c, const char toWrite);
            char read_char_from_row (const unsigned int c);
            void erase_char_from_row(const unsigned int c);

        Row() {
            for (int i = 0; i < 100; i++) {
                row.push_back('_');
            }
        }
    };

    class Page {
        public:
            vector<Row> page;

        Row get_row(const unsigned int num_of_row);

        // void writePage(const int r, const int c, Direction dir, const string &to_write);
        // string readPage(const int r, const int c, Direction dir, const int to_read);
        // void erasePage(const int r, const int c, Direction dir, const int to_erase);
        unsigned int get_num_rows();
    };

    class Notebook {
        private:
            
        public:
            vector<Page> notebook;

            Page get_page(const unsigned int p);

            void write(const int p,const int r,const int c, Direction dir,const string &to_write);
            string read(const int p, const int r, const int c, Direction dir, int length_to_read);
            void erase(const int p, const int r,const int c, Direction dir, int length_to_erase);
            void show(const int p);
    };


};