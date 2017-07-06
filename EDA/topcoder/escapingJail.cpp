#include <iostream>
#include <string>
#include <map>
#include <vector>

typedef std::map<char,int> mDicc;
typedef std::vector< std::string > matrixOfChars;
typedef std::vector< std::vector<int> > matrixOfInts;


class Diccionary{
    mDicc Dicc;
public:
    Diccionary(){
        char c;
        for(int i = 0;i<=61;i++){
            if(i < 10){
               c = (char)i+48;
               Dicc[c] = i;
            } else if (i < 36){
                c = (char)i-10+97;
                Dicc[c] = i;
            } else{
                c = (char)i-36+65;
                Dicc[c] = i;
            }
        }
        Dicc[' ']  = 2000;
    }
    int & operator[](const int & index){return Dicc[index];}
};

class EscapingJail{
    Diccionary mDicc;
    int **mDistances;

public:
    int getMaxDistance(matrixOfChars chain){
        fillMatrix(chain);
        std::cout << mDistances[2][0];

    }
    void fillMatrix(const matrixOfChars & chain){
        int sz = chain.size();
        mDistances = new int*[sz];
        for(int i = 0; i < sz; i++){
            mDistances[i] = new int[sz];
        }

        for(int i = 0; i < sz; i++)
        for(int j = 0; j<sz;j++){
            mDistances[i][j] = mDicc[ chain[i][j] ];
        }
    }

};

int main(){
    matrixOfChars matrix = {"0568", "5094", "6903", "8430"};

    EscapingJail A;
    A.getMaxDistance(matrix);
}
