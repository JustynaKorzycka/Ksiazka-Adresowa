#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string changeIntToString (int number) {
    ostringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}

void loadTheFile (string nameOfFile, string nameOfNewFile ) {
    fstream originalFile;
    fstream fileAfterChange;
    string loadLine;
    int numberOfLine = 1;
    int id = 0;
    string supplementaryTekst="";
    originalFile.open(nameOfFile.c_str(), ios :: in);
    fileAfterChange.open(nameOfNewFile.c_str(), ios::out);
    if (originalFile.good()) {
        while (getline(originalFile, loadLine)) {
            switch(numberOfLine) {
            case 1:
                supplementaryTekst += (changeIntToString(id) +"|"+loadLine+"|");
                break;
            case 2:
                supplementaryTekst += (loadLine+"|");
                break;
            case 3:
                supplementaryTekst += (loadLine+"|");
                break;
            case 4:
                supplementaryTekst += (loadLine+"|");
                break;
            case 5:
                supplementaryTekst += loadLine;
                break;
            }
            if (numberOfLine == 5) {
                fileAfterChange << supplementaryTekst << endl;
                numberOfLine = 1;
                id++;
                supplementaryTekst = "";
            } else numberOfLine++;
        }
        originalFile.close();
        fileAfterChange.close();
    } else cout << "Problem z otwarciem pliku." << endl;
}

int main() {
    string nameOfFile;
    cout << "Podaj nazwe pliku z ktorego bedziesz wczytywal dane kontaktowe: ";
    cin >> nameOfFile;
    string nameOfNewFile = nameOfFile + "_nowy_format.txt";
    string fullNameOfOriginFile = nameOfFile + ".txt";
    loadTheFile(fullNameOfOriginFile, nameOfNewFile);

    return 0;
}
