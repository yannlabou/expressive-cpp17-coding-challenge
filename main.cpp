#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

bool is_empty(std::ifstream& input)
{
    if (input)
        return input.peek() == std::ifstream::traits_type::eof();
    return true;
}

std::vector<std::string> split(const std::string& csv_row, char delimiter = ',')
{
    std::vector<std::string> result;
    auto p = std::begin(csv_row);
    for (auto q = std::find(p, std::end(csv_row), delimiter);
         q != std::end(csv_row);
         q = std::find(++p, std::end(csv_row), delimiter))
    {
        result.emplace_back(p, q);
        p = q;
    }
    if (p != std::end(csv_row))
        result.emplace_back(p, std::end(csv_row));
    return result;
}

template<typename Container>
void write_csv_row(Container first, Container last,
                   std::string_view filename,
                   std::string_view delimiter,
                   size_t line_number)
{
    std::ofstream ofs{filename.data(), std::ios::out | (line_number ? std::ios::app : std::ios::trunc) | std::ios::binary};
    std::copy(first, last - 1, std::ostream_iterator<std::string>(ofs, delimiter.data()));
    std::copy(last - 1, last, std::ostream_iterator<std::string>(ofs, "\n"));
    ofs.close();
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cerr << "Invalid number of arguments!" << '\n';
        return -1;
    }

    std::vector<std::string> args;
    args.reserve(4);
    for (int i = 1; i != argc; ++i)
        args.emplace_back(argv[i]);

    std::string csv_input{args.at(0)};
    std::string column_name{args.at(1)};
    std::string replacement_text{args.at(2)};
    std::string csv_output{args.at(3)};


    std::ifstream ifs{csv_input};
    if (is_empty(ifs))
    {
        std::cerr << "input file missing" << '\n';
        return -1;
    }

    std::string str_csv_row;
    std::vector<std::string> vec_csv_row;
    std::vector<std::string>::iterator city_column;
    std::ptrdiff_t index;
    std::size_t line_number = 0;
    while(std::getline(ifs, str_csv_row))
    {
        vec_csv_row = split(str_csv_row);
        if (!line_number)
        {
            city_column = std::find(vec_csv_row.begin(), vec_csv_row.end(), "City");
            if (!(city_column != vec_csv_row.end()))
            {
                std::cerr << "column name doesn't exists in the input file" << '\n';
                break;
            }
            else
            {

            }
            index = std::distance(vec_csv_row.begin(), city_column);
        }
        else
        {
            vec_csv_row.at(index) = replacement_text;
        }
        write_csv_row(vec_csv_row.begin(), vec_csv_row.end(), csv_output, ",", line_number);
        ++line_number;
    }
    return 0;
}
