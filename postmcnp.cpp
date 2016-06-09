#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
using namespace std;

//int main (int argc, char** argv)
//{
//    string line;
//    fstream infile;
//    infile.open(argv[1]);
//        while(!infile.eof()) // To get you all the lines.
//        {
//            getline(infile,line); // Saves the line in STRING.
//            if()
//        }
//        infile.close();
//        return 0;
//}

class Reader {
public:
    Reader(string);
    string getfilename();
    //int lines();
private:
    int nlines;
    const char* filename;
    const char* outName;
    void constr(string);
    void createOutputName();
    string NumberToString(int);
    string searchDate(ifstream&, int&);
    bool exists(const char* );
    void getTally(ifstream&, ofstream&, int&);

};

Reader::Reader(string fn) {

    //construct the output file
    constr(fn);
}

void Reader::constr(string fn) {
    //to track the line number
    int c = 0;
    //input
    filename = fn.c_str();
    if (!exists(filename)) {
        cout<< "ERROR: doesnot exists";
    }
    ifstream infile;
    infile.open(filename, std::ifstream::in);
    // output
    //createsthe output file
    createOutputName();
    ofstream outfile;
    outfile.open(outName, std::ofstream::out | std::ofstream::app);

    string date = searchDate(infile, c);
    string auxDate ("Date of creation  (mm/dd/yyyy):    ");
    string addline (" \n ");
    outfile.write(auxDate.c_str(), auxDate.length());
    outfile.write(date.c_str(), date.length());
    outfile.write(addline.c_str(), addline.length());
    getTally(infile, outfile, c);
    outfile.close();
}

string Reader::searchDate(ifstream& infile, int& c) {
    char s[18];
    s[17]='\0';
    string line;
    bool state=true;
    string aux="1mcnp";
    while(state) {
        // counts the procesing linenumber
        c++;
        //saves the line in Line
        getline(infile, line);
        if (equal(line.begin(), line.begin()+5, aux.begin())) {
            line.copy(s, 17, 56);
            string g (s);
            break;
        }
        if (c > 40){
            break;
        }
    }// end while
    return s;
}

void Reader::getTally(ifstream& infile, ofstream& outfile, int& c) {

    string line;
    bool state=true;
    string aux="1tally";
    string end=" ==";

    while (!infile.eof()) {
        // counts the procesing linenumber
        string addline (" \n ");
        c++;
        getline(infile, line);
        //saves the line in Line
        if (equal(line.begin(), line.begin()+5, aux.begin())) {
            while (!equal(line.begin(), line.begin()+3, end.begin()) and !infile.eof()) {
                outfile.write(line.c_str(),line.length());
                getline(infile, line);
                outfile.write(addline.c_str(), addline.length());
                c++;
            }
        }
    } // end while
}

void Reader::createOutputName() {
    string aux (filename);
    int i = 0;
    while (exists((aux+".out").c_str())){
        ++i;
        char a = i+'0';
        *(aux.end()-1)=a;
    }
    aux+=".out";
    cout<<"\n"<<aux<<"\n";
    outName=aux.c_str();
}

inline bool Reader::exists (const char* name) {
    ifstream infile(name);
    return infile.good();
}

//inline int Reader::lines() {
//    return nlines;
//}

inline string Reader::getfilename() {
    string fn (filename);
    return fn;
}

//string Reader::NumberToString ( int Number )
//{
//    std::ostringstream ss;
//    ss << Number;
//    return ss.str();
//}

int main(int argc, char** argv){

    Reader r(argv[1]);

    return 0;
}
