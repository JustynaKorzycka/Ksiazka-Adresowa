#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Uzytkownicy {
    string login, haslo;
    int idUzytkownika;
};

void wczytajUzytkownikowZPliku (vector <Uzytkownicy> &daneUzytkownika) {
    fstream plikZUzytkownikami;
    string wczytywanaLinia;
    vector <Uzytkownicy> pomocniczy(1);
    int numerLinii;
    plikZUzytkownikami.open("Uzytkownicy.txt", ios :: in);
    if (plikZUzytkownikami.good() == true) {
        while (getline(plikZUzytkownikami, wczytywanaLinia)) {
            for (int i = 0; i < 3; i++) {
                size_t pozycja=wczytywanaLinia.find('|');
                {
                    string bufor = wczytywanaLinia.substr(0, pozycja);
                    wczytywanaLinia.erase(0, pozycja + 1);
                    if (i == 0) pomocniczy [0].idUzytkownika = atoi(bufor.c_str());
                    else if(i == 1) pomocniczy[0].login = bufor;
                    else if (i == 2) pomocniczy[0].haslo = bufor;
                }
            }
            daneUzytkownika.push_back(pomocniczy[0]);
            ++numerLinii;
        }
        plikZUzytkownikami.close();
    } else cout << "Problemy z otwarciem pliku ";
}
void aktualizujDaneUzytkownikow (vector <Uzytkownicy> &daneUzytkownika) {
    string bufor;
    fstream plikZAdresami;
    plikZAdresami.open("Uzytkownicy.txt", ios::out | ios :: trunc);
    ofstream plik( "Uzytkownicy.txt" );
    cout << daneUzytkownika.size()<<endl;
    getchar();
    if (plikZAdresami.good()) {
        for (vector <Uzytkownicy> :: iterator itr = daneUzytkownika.begin(); itr != daneUzytkownika.end(); ++itr) {
            plikZAdresami << itr -> idUzytkownika << "|";
            plikZAdresami << itr -> login << "|";
            plikZAdresami << itr -> haslo << endl;
        }
        plikZAdresami.close();
    } else cout << "Wystapil problem z otwarciem pliku. " <<endl;
}

void dopiszUzytkownikaDoPliku (vector <Uzytkownicy> &daneUzytkownika) {
    fstream plikZUzytkownikami;
    plikZUzytkownikami.open("Uzytkownicy.txt", ios::out|ios::app);
    if (plikZUzytkownikami.good()) {
        plikZUzytkownikami << daneUzytkownika[0].idUzytkownika << "|";
        plikZUzytkownikami << daneUzytkownika[0].login << "|";
        plikZUzytkownikami << daneUzytkownika[0].haslo << endl;
        plikZUzytkownikami.close();
    } else cout << "Problemy z otwarciem pliku ";
}

int zaloguj (vector <Uzytkownicy> &daneUzytkownika) {
    string login, haslo;
    cout << "Podaj login: ";
    cin >> login;
    for (vector <Uzytkownicy> :: iterator itr = daneUzytkownika.begin(); itr != daneUzytkownika.end(); ++itr) {
        if (itr -> login == login) {
            for (int i = 2; i >= 0; i--) {
                cout << "Podaj haslo: ";
                cin >> haslo;
                if (itr -> haslo == haslo) {
                    cout << "Witaj w swojej ksiazce adresowej!";
                    Sleep (3000);
                    return itr -> idUzytkownika;
                } else if (i == 0) {
                    cout << "Niepoprawne logowanie";
                    Sleep(1000);
                    return 0;
                } else cout << "Podales zle haslo. Pozostalo Ci jeszcze " << i << " prob" << endl;
            }
        }
    }
    cout << "Nie ma takiego uzytkownika";
    Sleep(1000);
    return 0;
}

void rejestruj (vector <Uzytkownicy> &daneUzytkownika) {
    string login, haslo;
    int iloscUzytkownikow = daneUzytkownika.size();
    getchar();
    vector <Uzytkownicy> pomocniczy(1);
    cout << "Wprowadz nazwe uzytkownika: ";
    cin >> login;

    for (vector <Uzytkownicy> :: iterator itr = daneUzytkownika.begin(); itr != daneUzytkownika.end(); ++itr) {
        if (itr -> login == login) {
            cout << "Wprowadzona nazwa jest juz zajeta. Podaj inna nazwe uzytkownika: ";
            cin>>login;
        }
    }
    pomocniczy[0].login = login;
    cout << "Podaj haslo: ";
    cin >> haslo;
    pomocniczy[0].haslo = haslo;
    getchar();
    if (iloscUzytkownikow == 0) pomocniczy[0].idUzytkownika = 1;
    else if (iloscUzytkownikow != 0) pomocniczy[0].idUzytkownika = daneUzytkownika.back().idUzytkownika + 1;
    dopiszUzytkownikaDoPliku (pomocniczy);
    daneUzytkownika.push_back(pomocniczy[0]);
    cout << "Konto zostalo pomysle zalozone." << endl;
    Sleep (1000);
}

struct Adresat {
    int     indywidulanyNumer;
    int     idUzytkownika;
    string  imie;
    string  nazwisko;
    string  numerTelefonu;
    string  email;
    string  adres;
};

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst) {
    if (!tekst.empty()) {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

void wczytywanieDanychZPliku (vector <Adresat> &daneOsobowe, int idZalogowanegoUzytkownika) {
    string wczytywanaLinia;
    vector<Adresat>pomocniczy(1);
    int numerLinii = 1;
    int idKontaktu;
    fstream plikZAdresami;
    plikZAdresami.open("Adresaci.txt", ios::in);
    if (plikZAdresami.good()) {
        while (getline(plikZAdresami, wczytywanaLinia)) {
            for (int i = 0; i < 2; i++) {
                size_t pozycja = wczytywanaLinia.find('|');
                {
                    string bufor = wczytywanaLinia.substr(0, pozycja);
                    wczytywanaLinia.erase(0, pozycja + 1);
                    if (i == 0) idKontaktu = atoi(bufor.c_str());
                    else if (i == 1 && idZalogowanegoUzytkownika == atoi(bufor.c_str())) {
                        pomocniczy[0].indywidulanyNumer = idKontaktu;
                        pomocniczy [0].idUzytkownika = idZalogowanegoUzytkownika;
                        for (int j = 0; j <5; j++) {
                            size_t pozycja = wczytywanaLinia.find('|');
                            string bufor = wczytywanaLinia.substr(0, pozycja);
                            wczytywanaLinia.erase(0, pozycja + 1);
                            if(j == 0) pomocniczy[0].imie = bufor;
                            else if (j == 1) pomocniczy[0].nazwisko = bufor;
                            else if (j == 2) pomocniczy [0].numerTelefonu = bufor;
                            else if (j == 3) pomocniczy [0].email = bufor;
                            else if (j == 4) pomocniczy [0].adres = bufor;
                        }
                        daneOsobowe.push_back(pomocniczy[0]);
                    }
                }
            }
            ++numerLinii;
        }
        plikZAdresami.close();
    } else cout << "Problemy z otwarciem pliku ";
}

void dopiszKontaktDoPliku (vector <Adresat>&daneDoDodania) {
    fstream plikZAdresami;
    plikZAdresami.open("Adresaci.txt", ios::out|ios::app);
    if (plikZAdresami.good()) {
        plikZAdresami << daneDoDodania[0].indywidulanyNumer << "|";
        plikZAdresami << daneDoDodania[0].idUzytkownika << "|";
        plikZAdresami << daneDoDodania[0].imie << "|";
        plikZAdresami << daneDoDodania[0].nazwisko << "|";
        plikZAdresami << daneDoDodania[0].numerTelefonu << "|";
        plikZAdresami << daneDoDodania[0].email << "|";
        plikZAdresami << daneDoDodania[0].adres << endl;
        plikZAdresami.close();
    } else cout << "Problemy z otwarciem pliku ";
}



void usuwanieKontaktuZPliku (int idKontatkuDoUsuniecia) {
    string wczytywanaLinia;
    int nrLinii = 1;
    fstream plikZAdresami;
    fstream plikTymczasowy;
    plikZAdresami.open("Adresaci.txt", ios::in);
    if (plikZAdresami.good()) {
        while (getline(plikZAdresami, wczytywanaLinia)) {
            size_t pozycja = wczytywanaLinia.find('|');
            string bufor = wczytywanaLinia.substr(0, pozycja);
            if (idKontatkuDoUsuniecia != atoi(bufor.c_str())) {
                plikTymczasowy.open("Adresaci.tymczasowy.txt", ios :: out | ios :: app);
                plikTymczasowy << wczytywanaLinia <<endl;
                plikTymczasowy.close();
            }
            nrLinii++;
        }
        plikZAdresami.close();
        remove("Adresaci.txt");
        rename("Adresaci.tymczasowy.txt", "Adresaci.txt");
    } else cout << "Wystapil problem z otwarciem pliku. " <<endl;
}

void wprowadzaieZminaKontaktuWPliku (int idKontatkuDoZmiany, vector <Adresat> doZmiany) {

    string wczytywanaLinia;
    int nrLinii = 1;
    fstream plikZAdresami;
    fstream plikTymczasowy;
    plikZAdresami.open("Adresaci.txt", ios::in);
    if (plikZAdresami.good()) {
        while (getline(plikZAdresami, wczytywanaLinia)) {
            size_t pozycja = wczytywanaLinia.find('|');
            string bufor = wczytywanaLinia.substr(0, pozycja);
            if (idKontatkuDoZmiany != atoi(bufor.c_str())) {
                plikTymczasowy.open("Adresaci.tymczasowy.txt", ios :: out | ios :: app);
                plikTymczasowy << wczytywanaLinia <<endl;
                plikTymczasowy.close();
            } else if (idKontatkuDoZmiany == atoi(bufor.c_str())) {
                plikTymczasowy.open("Adresaci.tymczasowy.txt", ios :: out | ios :: app);
                plikTymczasowy << doZmiany[0].indywidulanyNumer << "|";
                plikTymczasowy << doZmiany[0].idUzytkownika << "|";
                plikTymczasowy << doZmiany[0].imie << "|";
                plikTymczasowy << doZmiany[0].nazwisko << "|";
                plikTymczasowy << doZmiany[0].numerTelefonu << "|";
                plikTymczasowy << doZmiany[0].email << "|";
                plikTymczasowy << doZmiany[0].adres << endl;
                plikTymczasowy.close();
            }
            nrLinii++;
        }
        plikZAdresami.close();
        remove("Adresaci.txt");
        rename("Adresaci.tymczasowy.txt", "Adresaci.txt");
    } else cout << "Wystapil problem z otwarciem pliku. " <<endl;
}

void nadanieIdKontkatu (int &idNowegoKontaktu) {
    fstream plikZAdresami;
    string wczytywanaLinia;
    string bufor1;
    plikZAdresami.open("Adresaci.txt", ios::in  );
    int dlugoscPliku = plikZAdresami.tellg()+1;
    if (dlugoscPliku == 0) idNowegoKontaktu = 1;
    else {
        while (getline(plikZAdresami, wczytywanaLinia)) {
            bufor1 = wczytywanaLinia;
        }
        size_t pozycja = bufor1.find('|');
        string bufor = bufor1.substr(0, pozycja);
        idNowegoKontaktu = atoi(bufor.c_str()) +1;
    }

}

void wprowadzNowyKontakt (vector <Adresat> &daneOsobowe, int idZalogowanegoUzytkownika) {
    string imie, nazwisko, email, adres, numerTelefonu;
    int idNowegoKontaktu = 0;
    vector <Adresat> pomocniczy(1);
    cout << "Podaj imie: ";
    cin >> pomocniczy[0].imie;
    zamienPierwszaLitereNaDuzaAPozostaleNaMale(pomocniczy[0].imie);
    cout << "Podaj nazwisko: ";
    cin >> pomocniczy[0].nazwisko;
    zamienPierwszaLitereNaDuzaAPozostaleNaMale(pomocniczy[0].nazwisko);
    cin.sync();
    cout << "Podaj adres: ";
    getline(cin,pomocniczy[0].adres);
    cin.sync();
    cout << "Podaj numer telefonu: ";
    getline(cin,pomocniczy[0].numerTelefonu);
    cout << "Podaj adres email: ";
    cin >> pomocniczy[0].email;
    nadanieIdKontkatu (idNowegoKontaktu);
    cout << "Id po funkcji : " << idNowegoKontaktu << endl;
    getchar();
    pomocniczy[0].indywidulanyNumer = idNowegoKontaktu;
    pomocniczy[0].idUzytkownika = idZalogowanegoUzytkownika;
    daneOsobowe.push_back(pomocniczy[0]);
    dopiszKontaktDoPliku (pomocniczy);
    cout << "Kontakt zostal zapisany.";
    Sleep(1000);
}
void wyszukajKontaktPoImieniu (vector <Adresat>& daneOsobowe) {
    string imiePoszukiwanegoKontaktu;
    int iloscWyszukanychKontaktow = 0;
    if (! daneOsobowe.empty()) {
        cout << "Podaj imie: ";
        cin >> imiePoszukiwanegoKontaktu;
        for (vector <Adresat> :: iterator itr = daneOsobowe.begin(); itr != daneOsobowe.end(); ++itr) {
            if (imiePoszukiwanegoKontaktu == itr ->imie) {
                cout << "---------------------- " << endl;
                cout << "Id:                " << itr -> indywidulanyNumer << endl;
                cout << "Nazwisko:          " << itr -> nazwisko << endl;
                cout << "Adres:             " << itr -> adres << endl;
                cout << "Numer telefonu:    " << itr -> numerTelefonu << endl;
                cout << "Email:             " << itr -> email << endl;
                cout << endl;
                iloscWyszukanychKontaktow++;
            }
        }
        if (iloscWyszukanychKontaktow == 0) {
            cout << "Nie znaleziono kontaktu o takim imieniu." << endl;
        }
    } else cout << "Ksiazka adresowa jest pusta. " << endl;
    getch();
}

void wyszukajKontaktPoNazwisku (vector <Adresat>& daneOsobowe) {
    string nazwiskoPoszukiwanegoKontaktu;
    int iloscWyszukanychKontaktow = 0;
    if (! daneOsobowe.empty()) {
        cout << "Podaj nazwisko: ";
        cin >> nazwiskoPoszukiwanegoKontaktu;
        for (vector <Adresat> :: iterator itr = daneOsobowe.begin(); itr != daneOsobowe.end(); ++itr) {
            if (nazwiskoPoszukiwanegoKontaktu == itr ->nazwisko) {
                cout << "---------------------- " << endl;
                cout << "Id:                    " << itr -> indywidulanyNumer << endl;
                cout << "Imie:                  " << itr -> imie << endl;
                cout << "Adres:                 " << itr -> adres << endl;
                cout << "Numer telefonu:        " << itr -> numerTelefonu << endl;
                cout << "Email:                 " << itr -> email << endl;
                cout << endl;
                iloscWyszukanychKontaktow ++;
            }
        }
        if (iloscWyszukanychKontaktow == 0) {
            cout << "Nie znaleziono kontaktu o takim nazwisku." << endl;
        }
    } else cout << "Ksiazka adresowa jest pusta. " << endl;
    getch();
}
void wyswietlWszystkieKontakty (vector <Adresat> daneOsobowe) {
    if (!daneOsobowe.empty()) {
        for (vector <Adresat> :: iterator itr = daneOsobowe.begin(); itr != daneOsobowe.end(); itr++) {

            cout << "Id               " << itr -> indywidulanyNumer << endl;
            cout << "Imie:            " << itr -> imie << endl;
            cout << "Nazwisko:        " << itr -> nazwisko<< endl;
            cout << "Adres:           " << itr -> adres << endl;
            cout << "Numer telefonu:  " << itr -> numerTelefonu << endl;
            cout << "Email:           " << itr -> email << endl;
            cout << endl;
        }
    } else cout << "Ksiazka adresowa jest pusta.";
    getch();
}
void zmianaDaychKontakowych (vector <Adresat>&daneOsobowe) {
    int idWyszukiwanegoKontaktu;
    int czyIstniejeKontakt =0;
    vector <Adresat> pomocniczy(1);
    cout << "Podaj id kontaktu: ";
    cin >> idWyszukiwanegoKontaktu;
    for (vector <Adresat> :: iterator itr = daneOsobowe.begin(); itr != daneOsobowe.end(); ++itr) {
        if (itr -> indywidulanyNumer == idWyszukiwanegoKontaktu) {
            czyIstniejeKontakt = 1;
            cout << "Obecne dane kontaktowe: " << endl;
            cout << "------------------------------" << endl;
            cout << "Imie:           "        << itr -> imie << endl;
            cout << "Nazwisko:       " << itr -> nazwisko << endl;
            cout << "Adres:          " << itr -> adres << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Email:          " << itr -> email << endl<<endl;
            string doZmiany;
            char wybor;
            cout << "Prosze wybrac jedna z ponizszych opcji (wpisujac cyfre od 1 do 6) : " << endl;
            cout << "1. Zmiana imienia" << endl;
            cout << "2. Zmiana nazwiska" << endl;
            cout << "3. Zmiana adresu" << endl;
            cout << "4. Zmiana numeru telefonu" << endl;
            cout << "5. Zmiana adresu email" << endl;
            cout << "6. Powrot do menu" << endl;
            cin >> wybor;
            if (wybor != '6') {
                cin.sync();
                cout << "Wprowadz dane do zapisu: ";
                getline(cin, doZmiany);
                switch (wybor) {
                case '1':
                    itr -> imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(doZmiany);
                    pomocniczy[0].adres = itr -> adres;
                    pomocniczy[0].imie = itr -> imie;
                    pomocniczy [0].nazwisko = itr -> nazwisko;
                    pomocniczy[0].idUzytkownika = itr -> idUzytkownika;
                    pomocniczy[0].email = itr -> email;
                    pomocniczy[0].indywidulanyNumer = itr -> indywidulanyNumer;
                    pomocniczy[0].numerTelefonu = itr -> numerTelefonu;
                    wprowadzaieZminaKontaktuWPliku (itr -> indywidulanyNumer, pomocniczy);
                    break;
                case '2':
                    itr -> nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(doZmiany);
                    pomocniczy[0].adres = itr -> adres;
                    pomocniczy[0].imie = itr -> imie;
                    pomocniczy [0].nazwisko = itr -> nazwisko;
                    pomocniczy[0].idUzytkownika = itr -> idUzytkownika;
                    pomocniczy[0].email = itr -> email;
                    pomocniczy[0].indywidulanyNumer = itr -> indywidulanyNumer;
                    pomocniczy[0].numerTelefonu = itr -> numerTelefonu;
                    wprowadzaieZminaKontaktuWPliku (itr -> indywidulanyNumer, pomocniczy);
                    break;
                case '3':
                    itr -> adres = doZmiany;
                    pomocniczy[0].adres = itr -> adres;
                    pomocniczy[0].imie = itr -> imie;
                    pomocniczy [0].nazwisko = itr -> nazwisko;
                    pomocniczy[0].idUzytkownika = itr -> idUzytkownika;
                    pomocniczy[0].email = itr -> email;
                    pomocniczy[0].indywidulanyNumer = itr -> indywidulanyNumer;
                    pomocniczy[0].numerTelefonu = itr -> numerTelefonu;
                    wprowadzaieZminaKontaktuWPliku (itr -> indywidulanyNumer, pomocniczy);
                    break;
                case '4':
                    itr -> numerTelefonu = doZmiany;
                    pomocniczy[0].adres = itr -> adres;
                    pomocniczy[0].imie = itr -> imie;
                    pomocniczy [0].nazwisko = itr -> nazwisko;
                    pomocniczy[0].idUzytkownika = itr -> idUzytkownika;
                    pomocniczy[0].email = itr -> email;
                    pomocniczy[0].indywidulanyNumer = itr -> indywidulanyNumer;
                    pomocniczy[0].numerTelefonu = itr -> numerTelefonu;
                    wprowadzaieZminaKontaktuWPliku (itr -> indywidulanyNumer, pomocniczy);
                    break;
                case '5':
                    itr -> email = doZmiany;
                    pomocniczy[0].adres = itr -> adres;
                    pomocniczy[0].imie = itr -> imie;
                    pomocniczy [0].nazwisko = itr -> nazwisko;
                    pomocniczy[0].idUzytkownika = itr -> idUzytkownika;
                    pomocniczy[0].email = itr -> email;
                    pomocniczy[0].indywidulanyNumer = itr -> indywidulanyNumer;
                    pomocniczy[0].numerTelefonu = itr -> numerTelefonu;
                    wprowadzaieZminaKontaktuWPliku (itr -> indywidulanyNumer, pomocniczy);
                    break;
                }
                cout << "Zmiany zostaly zapisane";
                Sleep(1000);
            } else if (wybor == 6) break;
        }
    }
    if (czyIstniejeKontakt == 0) {
        cout << "Nie ma takiego kontaktu." << endl;
        Sleep(3000);
    }

}

void usuwanieKontaktu (vector <Adresat> &daneOsobowe) {
    int rozmiar = daneOsobowe.size();
    int czyIstniejeKontakt = 0;
    int idSzukanegoKontaktu = 0;
    int wybor;
    cout << "Podaj id kontaktu ";
    cin >> idSzukanegoKontaktu;
    for (vector <Adresat>::iterator itr = daneOsobowe.begin(); itr != daneOsobowe.end(); itr++) {
        if (itr -> indywidulanyNumer == idSzukanegoKontaktu) {
            czyIstniejeKontakt = 1;
            cout << "Czy na pewno chcesz usunac kontakt " << itr -> imie << " " << itr -> nazwisko << "?" << endl;
            cout << "Jesli tak wcisnij 1, jesli nie wcisnij 2. " << endl;
            cin >> wybor;
            if (wybor == 1) {
                itr = daneOsobowe.erase(itr);
                usuwanieKontaktuZPliku(idSzukanegoKontaktu);
                cout << "Kontakt zostal usuniety.";
                Sleep(1000);
                break;
            } else  if (wybor !=1) break;
        }
    if (czyIstniejeKontakt == 0) cout << "Taki kontakt nie istnieje. " << endl;

    }
}


void zmienHaslo(vector <Uzytkownicy> &daneUzytkownika, int idZalogowanegoUzytkownika) {
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (vector <Uzytkownicy> :: iterator itr = daneUzytkownika.begin(); itr != daneUzytkownika.end(); ++itr) {
        if (itr -> idUzytkownika == idZalogowanegoUzytkownika) {
            itr -> haslo=haslo;
            aktualizujDaneUzytkownikow (daneUzytkownika);
        }
    }

    cout<<"Haslo zostalo zmienione";
    Sleep(1000);
}

int main() {

    char wyborPierwszy;
    int idZalogowanegoUzytkownika = 0;
    vector <Uzytkownicy> daneUzytkownika;
    wczytajUzytkownikowZPliku (daneUzytkownika);
    while (1) {
        system ("cls");
        if (idZalogowanegoUzytkownika == 0) {
            cout << "Menu logowania " << endl;
            cout << "---------------------" << endl;
            cout << "1. Logowanie " <<endl;
            cout << "2. Rejestracja " <<endl;
            cout << "3. Wyjscie z programu " << endl;
            cin >> wyborPierwszy;
            switch (wyborPierwszy) {
            case '1':
                idZalogowanegoUzytkownika = zaloguj(daneUzytkownika);
                break;
            case '2':
                rejestruj (daneUzytkownika);
                break;
            case '3':
                exit(0);
                break;
            }
        } else if (idZalogowanegoUzytkownika != 0) {
            vector <Adresat> daneOsobowe;
            char wyborFunkcji;
            wczytywanieDanychZPliku (daneOsobowe, idZalogowanegoUzytkownika);
            while (idZalogowanegoUzytkownika != 0) {
                system("cls");
                cout << "Menu" << endl;
                cout << "--------------------" << endl;
                cout << "1. Wprowadz nowe dane kontaktowe" << endl;
                cout << "2. Wyszukaj kontakt po imieniu" << endl;
                cout << "3. Wyszukaj kontakt po nazwisku" << endl;
                cout << "4. Wyswietl wszystkie kontakty" << endl;
                cout << "5. Zmiana danych kontaktu"<<endl;
                cout << "6. Usuwanie kontaktu" << endl;
                cout << "7. Zmien haslo" << endl;
                cout << "8. Wyloguj" << endl;
                cout << "9. Wyjdz z programu" << endl;
                cin >> wyborFunkcji;

                if (wyborFunkcji == '1') {
                    wprowadzNowyKontakt (daneOsobowe, idZalogowanegoUzytkownika);
                } else if (wyborFunkcji == '2') {
                    wyszukajKontaktPoImieniu(daneOsobowe);
                } else if (wyborFunkcji == '3') {
                    wyszukajKontaktPoNazwisku(daneOsobowe);
                } else if (wyborFunkcji == '4') {
                    wyswietlWszystkieKontakty (daneOsobowe);
                } else if (wyborFunkcji == '5') {
                    zmianaDaychKontakowych (daneOsobowe);
                } else if (wyborFunkcji == '6') {
                    usuwanieKontaktu(daneOsobowe);
                } else if (wyborFunkcji == '7') {
                    cout <<  "w menu: "<< daneUzytkownika.size()<<endl;
                    zmienHaslo(daneUzytkownika, idZalogowanegoUzytkownika);
                } else if (wyborFunkcji == '8') {
                    idZalogowanegoUzytkownika = 0;
                    break;
                } else if (wyborFunkcji == '9') exit(0);
            }
        }
    }
    return 0;
}
