#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct WiadomosciOZnajomym {
    int indywidulanyNumer;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
};
int wczytywanieDanychZPliku (vector <WiadomosciOZnajomym> &daneOsobowe, int iloscKontaktow) {
    string wczytywanaLinia;
    vector<WiadomosciOZnajomym>pomocniczy(1);
    int numerLinii = 1;
    fstream plikZAdresami;
    plikZAdresami.open("PlikTekstowy.txt", ios::in);
    if (plikZAdresami.good()) {
        while (getline(plikZAdresami, wczytywanaLinia)) {
            for (int i = 0; i < 6; i++) {
                size_t pozycja=wczytywanaLinia.find('|');
                {
                    string bufor = wczytywanaLinia.substr(0, pozycja);
                    wczytywanaLinia.erase(0, pozycja + 1);
                    if (i == 0) pomocniczy [0].indywidulanyNumer = atoi(bufor.c_str());
                    else if(i == 1) pomocniczy[0].imie = bufor;
                    else if (i == 2) pomocniczy[0].nazwisko = bufor;
                    else if (i == 3) pomocniczy [0].numerTelefonu = bufor;
                    else if (i == 4) pomocniczy [0].email = bufor;
                    else if (i == 5) pomocniczy [0].adres = bufor;
                }
            }
            daneOsobowe.push_back(pomocniczy[0]);
            ++numerLinii;
            iloscKontaktow++;
        }
        plikZAdresami.close();
        return iloscKontaktow;
    } else cout << "Problemy z otwarciem pliku ";
    return 0;
}

int wprowadzenieNowegoKontaktu (int iloscKontaktow, vector <WiadomosciOZnajomym> &daneOsobowe) {
    string imie, nazwisko, email, adres, numerTelefonu;
    vector <WiadomosciOZnajomym>pomocniczy(1);
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    int i = 0;
    while(i < iloscKontaktow) {
        if (daneOsobowe[i].imie == imie && daneOsobowe[i].nazwisko == nazwisko) {
            cout << "Taki kontakt juz istnieje. Wprowadz inne dane kontaktowe" << endl;
            cout << "Podaj imie: ";
            cin >> imie;
            cout << "Podaj nazwisko: ";
            cin >> nazwisko;
            i = 0;
        } else i++;
    }
    cin.sync();
    cout << "Podaj adres: ";
    getline(cin,adres);
    cin.sync();
    cout << "Podaj numer telefonu: ";
    getline(cin,numerTelefonu);
    cout << "Podaj adres email: ";
    cin >> email;
    int IndywidulanyNumer;
    if (iloscKontaktow == 0) IndywidulanyNumer=iloscKontaktow+1;
    else if(iloscKontaktow != 0)IndywidulanyNumer = daneOsobowe[iloscKontaktow-1].indywidulanyNumer+1;
    pomocniczy[0].indywidulanyNumer = IndywidulanyNumer;
    pomocniczy[0].imie = imie;
    pomocniczy[0].nazwisko = nazwisko;
    pomocniczy[0].numerTelefonu = numerTelefonu;
    pomocniczy[0].email = email;
    pomocniczy[0].adres = adres;

    daneOsobowe.push_back(pomocniczy[0]);
    fstream plikZAdresami;
    plikZAdresami.open("PlikTekstowy.txt", ios::out|ios::app);
    if (plikZAdresami.good()) {
        plikZAdresami << IndywidulanyNumer << "|";
        plikZAdresami << imie << "|";
        plikZAdresami << nazwisko << "|";
        plikZAdresami << numerTelefonu << "|";
        plikZAdresami << email<<"|";
        plikZAdresami << adres << endl;
        plikZAdresami.close();
        cout << "Kontakt zostal zapisany.";
    } else cout << "Problemy z otwarciem pliku ";
    Sleep(1000);
    return iloscKontaktow+1;
}
void wyszukiwanieKontaktuPoImieniu(int iloscKontaktow, vector <WiadomosciOZnajomym>& daneOsobowe) {
    string imie;
    cout << "Podaj imie: ";
    cin >> imie;
    int j = 0;
    for (int i = 0; i < iloscKontaktow; i++) {
        if (imie == daneOsobowe[i].imie) {
            cout << "----------------------" << endl;
            cout << "Nazwisko: "<<daneOsobowe[i].nazwisko << endl;
            cout << "Adres: " << daneOsobowe[i].adres << endl;
            cout << "Numer telefonu: " << daneOsobowe[i].numerTelefonu << endl;
            cout << "Email: " << daneOsobowe[i].email << endl;
            cout << endl;
            j++;
        }
    }
    if (j == 0) {
        cout << "Nie znaleziono takiego kontaktu." << endl;
    }
    getch();
}
void wyszukiwanieKontaktuPoNazwisku(int iloscKontaktow, vector <WiadomosciOZnajomym>& daneOsobowe) {
    string nazwisko;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    int j = 0;
    for (int i = 0; i < iloscKontaktow; i++) {
        if (nazwisko == daneOsobowe[i].nazwisko) {
            cout <<"----------------------" << endl;
            cout << "Nazwisko: " << daneOsobowe[i].imie << endl;
            cout << "Adres: " << daneOsobowe[i].adres << endl;
            cout << "Numer telefonu: " << daneOsobowe[i].numerTelefonu << endl;
            cout << "Email: " << daneOsobowe[i].email << endl;
            cout << endl;
            j++;
        }
    }
    if (j == 0) {
        cout << "Nie znaleziono takiego kontaktu." << endl;
    }
    getch();
}
void wyswietlWszystkieKontakty (int iloscKontaktow, vector <WiadomosciOZnajomym> daneOsobowe) {
    for (int i = 0; i < iloscKontaktow; i++) {
        cout << "Kontakt nr " << i+1 << endl;
        cout << "----------------------" << endl;
        cout << "Imie: " << daneOsobowe[i].imie << endl;
        cout << "Nazwisko: " << daneOsobowe[i].nazwisko << endl;
        cout << "Adres: " << daneOsobowe[i].adres << endl;
        cout << "Numer telefonu: " << daneOsobowe[i].numerTelefonu << endl;
        cout << "Email: " << daneOsobowe[i].email << endl;
        cout << endl;
    }
    getch();
}
vector <WiadomosciOZnajomym> zmianaDaychKontakowych (int iloscKontaktow, vector <WiadomosciOZnajomym>&daneOsobowe) {
    string imie, nazwisko;
    int nrKonktaktu = -1;
    cout << "Podaj imie kontatku: ";
    cin >> imie;
    cout << "Podaj nazwikso kontaktu: ";
    cin >> nazwisko;
    for(int i = 0; i < iloscKontaktow; i++) {
        if (daneOsobowe[i].imie == imie && daneOsobowe[i].nazwisko == nazwisko) nrKonktaktu = i;
    }
    if (nrKonktaktu == -1) {
        cout << "Nie ma takiego kontaktu." << endl;
        Sleep(3000);
        return daneOsobowe;
    } else if (nrKonktaktu != -1) {
        cout << "Obecne dane kontaktowe:" << endl;
        cout << "------------------------------" << endl;
        cout << "Imie: " << daneOsobowe[nrKonktaktu].imie << endl;
        cout << "Nazwisko: " << daneOsobowe[nrKonktaktu].nazwisko << endl;
        cout << "Adres: " << daneOsobowe[nrKonktaktu].adres << endl;
        cout << "Numer telefonu: " << daneOsobowe[nrKonktaktu].numerTelefonu << endl;
        cout << "Email: " << daneOsobowe[nrKonktaktu].email << endl;
        cout << "Wpisz nowe dane kontakowe: " << endl;
        string imie, nazwisko, adres, numerTelefonu, email;
        cout << "Podaj imie: ";
        cin >> imie;
        cout << "Podaj nazwisko: ";
        cin >> nazwisko;
        cin.sync();
        cout << "Podaj adres: ";
        getline(cin,adres);
        cout << "Podaj numer telefonu: ";
        cin >> numerTelefonu;
        cout << "Podaj email: ";
        cin >> email;
        daneOsobowe[nrKonktaktu].imie = imie;
        daneOsobowe[nrKonktaktu].nazwisko = nazwisko;
        daneOsobowe[nrKonktaktu].adres = adres;
        daneOsobowe[nrKonktaktu].numerTelefonu = numerTelefonu;
        daneOsobowe[nrKonktaktu].email = email;
        string wczytywanaLinia;
        string bufor;
        fstream plikZAdresami;
        plikZAdresami.open("PlikTekstowy.txt", ios::out|ios::app);
        ofstream plik( "PlikTekstowy.txt" );
        if (plikZAdresami.good()) {
            for (int i = 0; i < iloscKontaktow; i++) {
                plikZAdresami<<daneOsobowe[i].indywidulanyNumer << "|";
                plikZAdresami<<daneOsobowe[i].imie << "|";
                plikZAdresami<<daneOsobowe[i].nazwisko << "|";
                plikZAdresami<<daneOsobowe[i].numerTelefonu << "|";
                plikZAdresami<<daneOsobowe[i].email << "|";
                plikZAdresami<<daneOsobowe[i].adres << endl;
            }
            plikZAdresami.close();
        }
        cout << "Zmiany zostaly zapisane";
        Sleep(1000);
        return daneOsobowe;
    }
}
int usuwanieKontaktu (int iloscKontaktow, vector <WiadomosciOZnajomym> &daneOsobowe) {
    string imie, nazwisko;
    int wybor;
    int nrKonktaktu = -1;
    cout << "Podaj imie kontatku: ";
    cin >> imie;
    cout << "Podaj nazwikso kontaktu: ";
    cin >> nazwisko;
    for(int i = 0; i < iloscKontaktow; i++) {
        if (daneOsobowe[i].imie == imie && daneOsobowe[i].nazwisko == nazwisko) nrKonktaktu = i;
    }
    if (nrKonktaktu == -1) {
        cout << "Nie ma takiego kontaktu." << endl;
        Sleep(3000);
        return iloscKontaktow;
    } else if (nrKonktaktu != -1) {
        cout << "Czy na pewno chcesz usunac kontakt " << daneOsobowe[nrKonktaktu].imie << " " << daneOsobowe[nrKonktaktu].nazwisko << "?" << endl;
        cout << "Jesli tak wcisnij 1, jesli nie wcisnij 2. " << endl;
        cin >> wybor;
        if (wybor == 2) return iloscKontaktow;
        else if (wybor == 1) {
            daneOsobowe.erase(daneOsobowe.begin()+nrKonktaktu);
            iloscKontaktow--;
            string wczytywanaLinia;
            string bufor;
            fstream plikZAdresami;
            plikZAdresami.open("PlikTekstowy.txt", ios::out|ios::app);
            ofstream plik( "PlikTekstowy.txt" );
            if (plikZAdresami.good()) {
                for (int i = 0; i < iloscKontaktow; i++) {
                    plikZAdresami << daneOsobowe[i].indywidulanyNumer << "|";
                    plikZAdresami << daneOsobowe[i].imie << "|";
                    plikZAdresami << daneOsobowe[i].nazwisko << "|";
                    plikZAdresami << daneOsobowe[i].numerTelefonu << "|";
                    plikZAdresami << daneOsobowe[i].email << "|";
                    plikZAdresami << daneOsobowe[i].adres << endl;
                }
                plikZAdresami.close();
            }
        }
        cout << "Kontakt zostal usuniety.";
        Sleep(1000);
        return iloscKontaktow;
    }
}
int main() {
    vector <WiadomosciOZnajomym> daneOsobowe;
    char wyborFunkcji;
    int iloscKontaktow = 0;
    iloscKontaktow = wczytywanieDanychZPliku (daneOsobowe, iloscKontaktow);
    Sleep(1000);
    while (1) {
        system("cls");
        cout << "Menu" << endl;
        cout << "--------------------" << endl;
        cout << "1. Wprowadz nowe dane kontaktowe" << endl;
        cout << "2. Wyszukaj kontakt po imieniu" << endl;
        cout << "3. Wyszukaj kontakt po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie kontakty" << endl;
        cout << "5. Zmiana danych kontaktu"<<endl;
        cout << "6. Usuwanie kontaktu" << endl;
        cout << "9. Wyjdz z programu" << endl;
        cin >> wyborFunkcji;

        if (wyborFunkcji == '1') {
            iloscKontaktow = wprowadzenieNowegoKontaktu (iloscKontaktow, daneOsobowe);
        } else if (wyborFunkcji == '2') {
            wyszukiwanieKontaktuPoImieniu(iloscKontaktow, daneOsobowe);
        } else if (wyborFunkcji == '3') {
            wyszukiwanieKontaktuPoNazwisku(iloscKontaktow, daneOsobowe);
        } else if (wyborFunkcji == '4') {
            wyswietlWszystkieKontakty (iloscKontaktow, daneOsobowe);
        } else if (wyborFunkcji == '5') {
            daneOsobowe=zmianaDaychKontakowych (iloscKontaktow, daneOsobowe);
        } else if (wyborFunkcji == '6') {
            iloscKontaktow = usuwanieKontaktu(iloscKontaktow, daneOsobowe);

        } else if (wyborFunkcji == '9') exit(0);
    }

    return 0;
}
