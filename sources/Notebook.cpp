#include "Notebook.hpp"
#include "Direction.hpp"
#include <vector>
#include <string>

#include <iostream>
#include <stdexcept>

using ariel::Direction;
using namespace std;
using namespace ariel;

/////// Row functions ///////
void ariel::Row::write_char_to_row(const unsigned int c, const char toWrite)
{
    row[c] = toWrite;
}
char ariel::Row::read_char_from_row(const unsigned int c)
{
    return row[c];
}

void ariel::Row::erase_char_from_row(const unsigned int c)
{
    row[c] = '~';
}
///////////////////////////////

/////// Page Funcitons ///////
Row ariel::Page::get_row(const unsigned int num_of_row)
{
    return page[num_of_row];
}

unsigned int ariel::Page::get_num_rows()
{
    return page.size();
}

/////// Notebook Functions //////////
Page ariel::Notebook::get_page(const unsigned int p)
{
    return notebook[p];
}

void ariel::Notebook::write(const int p, const int r, const int c, Direction dir, const string &to_write)
{

    if (p < 0 || r < 0 || c < 0 || c >= 100)
    {
        throw out_of_range("Input must be positive and the column must be between 0-100");
    }

    if (to_write.find('~') != string::npos)
    {
        throw invalid_argument("The string to be written cannot contain '~'");
    }


    if (to_write.find('\n') != string::npos)
    {
        throw invalid_argument("Invalid argument");
    }
    unsigned int row = (unsigned int)r;
    unsigned int col = (unsigned int)c;
    unsigned int page = (unsigned int)p;

    // If the page does not exist create it.
    if (notebook.size() <= page)
    {
        notebook.resize((page + 1));
    }
    string re = this->read(p, r, c, dir, to_write.size());
    // cout << re << endl;
    for (char ch : re) {
        if (ch != '_') {
            throw invalid_argument("Cannot write on top of anything but '_'");
        }
    }

    for (char ch : to_write) {
        if (ch < 32 || ch > 126) {
            throw invalid_argument("Invalid chars in the string (32 - 126)");
        }
    }

    if (dir == Direction::Horizontal)
    {
        if (col + to_write.size() > 99)
        {
            throw out_of_range("Row deviation");
        }

        // If the page doesnt have enough rows, create enough rows.
        if (notebook[page].get_num_rows() <= row)
        {
            notebook[page].page.resize(row + 1);
        }
        for (char w : to_write)
        {
            notebook[page].page[row].write_char_to_row(col, w);
            col++;
        }
    }

    if (dir == Direction::Vertical)
    {

        // If there are not enough rows create enough rows to write vertically.
        if (notebook[page].get_num_rows() <= row + to_write.size())
        {
            notebook[page].page.resize(row + to_write.size());
        }
        for (char w : to_write)
        {
            notebook[page].page[row].write_char_to_row(col, w);
            row++;
        }
    }
}

string ariel::Notebook::read(const int p, const int r, const int c, Direction dir, int length_to_read)
{

    if (p < 0 || r < 0 || c < 0 || c >= 100)
    {
        throw out_of_range("Input must be positive and the column must be between 0-100");
    }
    unsigned int row = (unsigned int)r;
    unsigned int col = (unsigned int)c;
    unsigned int page = (unsigned int)p;

    string ret;
    // If the page does not exist create it.
    if (notebook.size() <= page)
    {
        notebook.resize(page + 1);
    }
    // Negative length
    if (length_to_read < 0)
    {
        throw invalid_argument("Length cannot be negative");
    }

    if (dir == Direction::Horizontal)
    {
        if (col + (unsigned int)length_to_read - 1 > 99){
            throw out_of_range("Row deviation");
        }

        // If the page doesnt have enough rows, create enough rows.
        if (notebook[page].page.size() <= row)
        {
            notebook[page].page.resize(row + 1);
        }
        unsigned int l_to_read = (unsigned int)length_to_read;
        for (unsigned int i = col; i < col + l_to_read; i++)
        {
            char to_read = notebook[page].page[row].read_char_from_row(i);
            ret += to_read;
        }
    }
    if (dir == Direction::Vertical)
    {
        // If there are not enough rows create enough rows to read vertically.
        unsigned long l_to_read = (unsigned long)length_to_read;
        if (notebook[page].page.size() <= row + l_to_read)
        {
            notebook[page].page.resize(row + l_to_read +1);
        }
        for (unsigned int i = row; i < row + l_to_read; i++)
        {
            char to_read = notebook[page].page[i].read_char_from_row(col);
            ret += to_read;
        }
    }
    return ret;
}
void ariel::Notebook::erase(const int p, const int r, const int c, Direction dir, int length_to_erase)
{


    if (p < 0 || r < 0 || c < 0 || c >= 100 || length_to_erase < 0)
    {
        throw out_of_range("Input must be positive and the column must be between 0-100");
    }

    string erasing;
    unsigned int row = (unsigned int)r;
    unsigned int col = (unsigned int)c;
    unsigned int page = (unsigned int)p;

    for (int i = 0; i < length_to_erase; i++)
    {
        erasing += '~';
    }
    // Resize number of pages if not enough pages
    if (notebook.size() <= page)
    {
        notebook.resize(page + 1);
    }

    if (dir == Direction::Horizontal)
    {
        if (col + erasing.size() > 99)
        {
            throw out_of_range("Row deviation");
        }
        // If the page doesnt have enough rows, create enough rows.
        if (notebook[page].get_num_rows() <= row)
        {
            notebook[page].page.resize(row + 1);
        }
        for (char w : erasing)
        {
            notebook[page].page[row].write_char_to_row(col, w);
            col++;
        }
    }
    if (dir == Direction::Vertical)
    {
        // If there are not enough rows create enough rows to write vertically.
        if (notebook[page].get_num_rows() <= row + erasing.size())
        {
            notebook[page].page.resize(row + erasing.size());
        }
        for (char w : erasing)
        {
            notebook[page].page[row].write_char_to_row(col, w);
            row++;
        }
    }
}

void ariel::Notebook::show(const int p)
{
    if (p < 0)
    {
        throw "Cannot find the page";
    }

    if (notebook.size() <= p)
    {
        cout << "Page does not exist" << endl;
        return;
    }
    unsigned int page = (unsigned int)p;
    unsigned int num_rows = notebook[page].get_num_rows();
    int row = 0;
    while (row != num_rows)
    {
        string row_str = ariel::Notebook::read(p, row, 0, Direction::Horizontal, 100);
        cout << row_str << endl;
        row++;
    }
}
