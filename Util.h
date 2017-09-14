#ifndef UTIL
#define UTIL

#include <iostream>
#include <string>
#include <fstream>

using namespace std ;

class Util {
    public:
        vector<string> split(const string &text, char sep) {
            std::vector<std::string> tokens;
            std::size_t start = 0, end = 0;
            while ((end = text.find(sep, start)) != std::string::npos) {
              tokens.push_back(text.substr(start, end - start));
              start = end + 1;
            }
            tokens.push_back(text.substr(start));
            return tokens;
        }

        template <size_t rows, size_t cols>
        void loadCSV(string fileName, float (&array)[rows][cols]){
            ifstream myfile ( fileName ); 
            string value;
            std::string::size_type sz;     // alias of size_t

            if (myfile.is_open())
            {
                int rowCount = 0;
                int colCount = 0;
                vector<string> tokens ;
                std::string::size_type sz;     // alias of size_t

                while ( myfile.good() )
                {        
                    getline ( myfile, value );      

                    if(value=="")
                        break;

                    tokens = split(value, ',');
                    for(int i=0;i<tokens.size();i++){
                        array[rowCount][colCount]= std::stof (tokens[i],&sz);
                        colCount++;
                    }

                    if(colCount == cols){
                        rowCount++ ;
                        colCount= 0 ;
                        tokens.clear();
                    }                    
                }

            myfile.close();
            }
            else cout << "Unable to open file"<<endl;
        }

        template <size_t rows, size_t cols>
        void printData(float (&array)[rows][cols]){
            for(int i=0; i<rows; i++)    //This loops on the rows.
            {
                for(int j=0; j<cols; j++) //This loops on the columns
                {
                    cout << array[i][j]  << "  ";
                }
                cout << endl;
            }
        }

        string vectorToString(vector<float> data) {
            string out = "";
            for (float& a : data) {
                out = out + to_string(a) + ", ";
            }
            return out;   
        }

};

#endif
