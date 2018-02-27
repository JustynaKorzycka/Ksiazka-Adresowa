#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;

struct WiadomosciOZnajomym {
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int indywidulanyNumer;
};

int wczytywanieDanychZPliku (WiadomosciOZnajomym DaneOsobowe[], int iloscKontaktow) {
    string wczytywanaLinia;
    int numerLinii=1;
    fstream plikZAdresami;
    plikZAdresami.open("PlikTekstowy.txt", ios::in);
    if (plikZAdresami.good()) {
        while (getline(plikZAdresami, wczytywanaLinia)) {
            switch(numerLinii) {
            case 1:
                DaneOsobowe[iloscKontaktow].imie=wczytywanaLinia;
                break;
            case 2:
                DaneOsobowe[iloscKontaktow].nazwisko=wczytywanaLinia;
                break;
            case 3:
                DaneOsobowe[iloscKontaktow].numerTelefonu=wczytywanaLinia;
                break;
            case 4:
                DaneOsobowe[iloscKontaktow].email=wczytywanaLinia;
                break;
            case 5:
                DaneOsobowe[iloscKontaktow].adres=wczytywanaLinia;
                break;
            case 6:
                DaneOsobowe[iloscKontaktow].indywidulanyNumer=atoi(wczytywanaLinia.c_str());
                break;
            }
            if(numerLinii==6) {
                numerLinii=0;
                iloscKontaktow++;
            } else numerLinii++;
        }
        plikZAdresami.close();
        return iloscKontaktow+1;
    } else cout<<"Problemy z otwarciem pliku ";
    return 0;
}

int wprowadzenieNowegoKontaktu (int iloscKontaktow, WiadomosciOZnajomym DaneOsobowe[]) {
    string imie, nazwisko, email, adres, numerTelefonu;
    cout<<"Podaj imie: ";
    cin>>imie;
    cout<<"Podaj nazwisko: ";
    cin>>nazwisko;
    int numerTablicy=0;
    while(numerTablicy<iloscKontaktow) {
        if (DaneOsobowe[numerTablicy].imie==imie&&DaneOsobowe[numerTablicy].nazwisko==nazwisko) {
            cout<<"Taki kontakt juz istnieje. Wprowadz inne dane kontaktowe"<<endl;
            cout<<"Podaj imie: ";
            cin>>imie;
            cout<<"Podaj nazwisko: ";
            cin>>nazwisko;
            numerTablicy=0;
        } else numerTablicy++;
    }
    cout<<"Podaj adres: ";
    cin.sync();
    getline(cin,adres);
    cout<<"Podaj numer telefonu: ";
    cin.sync();
    getline(cin,numerTelefonu);
    cout<<"Podaj adres email: ";
    cin>>email;
    int IndywidulanyNumer = iloscKontaktow+1;
    DaneOsobowe[iloscKontaktow].imie=imie;
    DaneOsobowe[iloscKontaktow].nazwisko=nazwisko;
    DaneOsobowe[iloscKontaktow].numerTelefonu=numerTelefonu;
    DaneOsobowe[iloscKontaktow].email=email;
    DaneOsobowe[iloscKontaktow].adres=adres;
    DaneOsobowe[iloscKontaktow].indywidulanyNumer=IndywidulanyNumer;
    fstream plikZAdresami;
    plikZAdresami.open("PlikTekstowy.txt", ios::out|ios::app);
    if (plikZAdresami.good()) {
        plikZAdresami<<imie<<endl;
        plikZAdresami<<nazwisko<<endl;
        plikZAdresami<<numerTelefonu<<endl;
        plikZAdresami<<email<<endl;
        plikZAdresami<<adres<<endl;
        plikZAdresami<<IndywidulanyNumer<<endl;
        plikZAdresami.close();
        cout<<"Kontakt zostal zapisany.";
    } else cout<<"Problemy z otwarciem pliku ";
    Sleep(1000);
    return iloscKontaktow+1;
}
void wyszukiwanieKontaktuPoImieniu(int iloscKontaktow, WiadomosciOZnajomym DaneOsobowe[]) {
    string imie;
    cout<<"Podaj imie: ";
    cin>> imie;
    int j=0;
    for (int i=0; i<iloscKontaktow; i++) {
        if (imie==DaneOsobowe[i].imie) {
            cout<<"----------------------"<<endl;
            cout<<"Nazwisko: "<<DaneOsobowe[i].nazwisko<<endl;
            cout<<"Adres: "<<DaneOsobowe[i].adres<<endl;
            cout<<"Numer telefonu: "<<DaneOsobowe[i].numerTelefonu<<endl;
            cout<<"Email: "<<DaneOsobowe[i].email<<endl;
            cout<<endl;
            j++;
        }
    }
    if (j==0) {
        cout<<"Nie znaleziono takiego kontaktu."<<endl;
    }
    getch();
}
void wyszukiwanieKontaktuPoNazwisku(int iloscKontaktow,WiadomosciOZnajomym DaneOsobowe[]) {
    string nazwisko;
    cout<<"Podaj nazwisko: ";
    cin>> nazwisko;
    int j=0;
    for (int i=0; i<iloscKontaktow; i++) {
        if (nazwisko==DaneOsobowe[i].nazwisko) {
            cout<<"----------------------"<<endl;
            cout<<"Nazwisko: "<<DaneOsobowe[i].imie<<endl;
            cout<<"Adres: "<<DaneOsobowe[i].adres<<endl;
            cout<<"Numer telefonu: "<<DaneOsobowe[i].numerTelefonu<<endl;
            cout<<"Email: "<<DaneOsobowe[i].email<<endl;
            cout<<endl;
            j++;
        }
    }
    if (j==0) {
        cout<<"Nie znaleziono takiego kontaktu."<<endl;
    }
    getch();
}
void wyswietlWszystkieKontakty (int iloscKontaktow, WiadomosciOZnajomym DaneOsobowe[]) {
    for (int i=0; i<iloscKontaktow; i++) {
        cout<<"Kontakt nr "<<i+1<<endl;
        cout<<"----------------------"<<endl;
        cout<<"Imie: "<<DaneOsobowe[i].imie<<endl;
        cout<<"Nazwisko: "<<DaneOsobowe[i].nazwisko<<endl;
        cout<<"Adres: "<<DaneOsobowe[i].adres<<endl;
        cout<<"Numer telefonu: "<<DaneOsobowe[i].numerTelefonu<<endl;
        cout<<"Email: "<<DaneOsobowe[i].email<<endl;
        cout<<endl;
    }
    getch();
}

int main() {
    WiadomosciOZnajomym DaneOsobowe [1000];
    char wyborFunkcji;
    int iloscKontaktow=0;
    iloscKontaktow=wczytywanieDanychZPliku (DaneOsobowe, iloscKontaktow);
    while (1) {
        system("cls");
        cout<<"Menu"<<endl;
        cout<<"--------------------"<<endl;
        cout<<"1. Wprowadz nowe dane kontaktowe"<<endl;
        cout<<"2. Wyszukaj kontakt po imieniu"<<endl;
        cout<<"3. Wyszukaj kontakt po nazwisku" <<endl;
        cout<<"4. Wyswietl wszystkie kontakty"<<endl;
        cout<<"9. Wyjdz z programu"<<endl;
        cin>>wyborFunkcji;
        if (wyborFunkcji=='1') {
            iloscKontaktow = wprowadzenieNowegoKontaktu (iloscKontaktow, DaneOsobowe);
            Sleep(1000);
        } else if (wyborFunkcji=='2') {
            wyszukiwanieKontaktuPoImieniu(iloscKontaktow, DaneOsobowe);
        } else if (wyborFunkcji=='3') {
            wyszukiwanieKontaktuPoNazwisku(iloscKontaktow, DaneOsobowe);
        } else if (wyborFunkcji=='4') {
            wyswietlWszystkieKontakty (iloscKontaktow, DaneOsobowe);
        } else if (wyborFunkcji=='9') exit(0);
    }
    return 0;
}
