# pragma once
# include <vector>
# include <fstream>
# include <boost/algorithm/string.hpp>
# include <string>
# include <iostream>

class CSVReader {
  public:
    CSVReader(std::string filename, std::string delm = ",") :
        fileName(filename), delimeter(delm)
{
}

    std::vector<std::vector<double>> getData();
  protected:
    std::string fileName;
    std::string delimiter;
};

std::vector<std::vector<double>> getdata() {
  std::ifstream file( this.fileName );
  std::vector<std::vector<double>> data = {};
  std::string line = "";

  while( getline( file, line ) ) {
    std::vector<std::string> split_line = {};
    boost::algorithm::split( split_line, line, boost::is_any_of( this.delimiter ) );
    std::vector<double> split_line_double = {};
    for( auto elem : split_line ) {
      split_line_double.push_back( std::stod( elem ) );
    }
    std::cout << split_line << std::endl ;
    data.push_back( split_line_double );
  }
  file.close();
  return data;
}
