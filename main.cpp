#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <conio.h>
#include <string>

using namespace std;

struct Adresat
{
    int id;
    string imie="";
    string nazwisko="";
    string numerTelefonu="";
    string email="";
    string adres="";
};


void nadpisaniePlikuDoEdycjiAdresata (vector<Adresat> &adresaci, vector<Adresat>::iterator itr)
{
    fstream plik, plikTymczasowy;

    plik.open("ksiazkaAdresowa.txt", ios::in);
    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out|ios::app);

    string linia,idKontaktu;

    while(!plik.eof())
    {
        getline(plik,idKontaktu,'|');
        getline(plik,linia);

        if (itr -> id == atoi(idKontaktu.c_str()))
        {
            plikTymczasowy << itr -> id << "|";
            plikTymczasowy << itr -> imie << "|";
            plikTymczasowy << itr -> nazwisko << "|";
            plikTymczasowy << itr -> numerTelefonu << "|";
            plikTymczasowy << itr -> email << "|";
            plikTymczasowy << itr -> adres << endl;
        }
        else if (atoi(idKontaktu.c_str()))
        {
            plikTymczasowy << idKontaktu + "|" + linia << endl;
        }
    }
    plik.close();
    plikTymczasowy.close();

    remove("ksiazkaAdresowa.txt");
    rename("Adresaci_tymczasowy.txt","ksiazkaAdresowa.txt");
}


void nadpisaniePlikuDoUsuwaniaAdresata (vector<Adresat> &adresaci, vector<Adresat>::iterator itr)
{
    fstream plik, plikTymczasowy;
    plik.open("ksiazkaAdresowa.txt", ios::in);
    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out|ios::app);

    string linia,idKontaktu;

    while(!plik.eof())
    {
        getline(plik,idKontaktu,'|');
        getline(plik,linia);

        if (itr -> id == atoi(idKontaktu.c_str()) )
        {
            continue;
        }
        else if (atoi(idKontaktu.c_str()))
        {
            plikTymczasowy << idKontaktu + "|" + linia << endl;
        }
    }

    plik.close();
    plikTymczasowy.close();

    remove("ksiazkaAdresowa.txt");
    rename("Adresaci_tymczasowy.txt","ksiazkaAdresowa.txt");
}

void dopiszAdresataDoPliku(vector <Adresat> &adresaci, int &iloscOsob)
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik << adresaci[iloscOsob].id << "|";
        plik << adresaci[iloscOsob].imie << "|";
        plik << adresaci[iloscOsob].nazwisko << "|";
        plik << adresaci[iloscOsob].numerTelefonu << "|";
        plik << adresaci[iloscOsob].email << "|";
        plik << adresaci[iloscOsob].adres <<endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku"<< endl;
        system("pause");
    }
}

int wczytajOsobyZPliku(vector <Adresat> &adresaci)
{
    fstream plik;

    plik.open("ksiazkaAdresowa.txt",ios::in);

    if(plik.good()==false)
    {
        cout << "Ksiazka adresowa jest pusta!" << endl;
        return 0;
    }

    string linia, idAdresata;
    int liczbaOsob=0;

   while (!plik.eof())
    {
        getline(plik,idAdresata,'|');
        if (idAdresata != "")
        {
            adresaci.push_back(Adresat());
            adresaci[liczbaOsob].id = atoi(idAdresata.c_str());
            getline(plik,linia,'|');
            adresaci[liczbaOsob].imie = linia;
            getline(plik,linia,'|');
            adresaci[liczbaOsob].nazwisko = linia;
            getline(plik,linia,'|');
            adresaci[liczbaOsob].numerTelefonu = linia;
            getline(plik,linia,'|');
            adresaci[liczbaOsob].email = linia;
            getline(plik,linia);
            adresaci[liczbaOsob].adres = linia;
            liczbaOsob++;
        }
    }
    plik.close();

    return liczbaOsob;
}

int pobierzIdOstatniegoAdresata(vector <Adresat> &adresaci)
{
    if (adresaci.empty() == true)
        return 1;
    else
        return adresaci.back().id + 1;
}

Adresat podajDaneNowegoAdresata(vector <Adresat> &adresaci)
{
    string imie, nazwisko, numerTelefonu, email, adres;

    system("cls");

    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync(); // oprozniam bufor
    getline(cin, numerTelefonu); // wczytuje wszystko razem ze spacj¹ i zapisuje w zmiennej numerTelefonu
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adres);

    Adresat adresat;

    adresat.id=pobierzIdOstatniegoAdresata(adresaci);

    adresat.imie=imie;
    adresat.nazwisko=nazwisko;
    adresat.numerTelefonu=numerTelefonu;
    adresat.email=email;
    adresat.adres=adres;

    return adresat;
}

void dodajOsobe(vector <Adresat> &adresaci,int &iloscOsob)
{
    Adresat adresat=podajDaneNowegoAdresata(adresaci);

    adresaci.push_back(adresat);

    dopiszAdresataDoPliku(adresaci,iloscOsob);
    iloscOsob++;

    cout<<endl<<"Dodano adresata."<<endl;
    system("pause");
}

void wyswietlAdresata(vector <Adresat> adresaci, vector<Adresat>::iterator itr)
{
    cout << "Id: " << itr -> id << endl;
    cout << "Imie: " << itr -> imie << endl;
    cout << "Nazwisko: " << itr -> nazwisko << endl;
    cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
    cout << "Adres: " << itr -> adres << endl;
    cout << "Email: " << itr -> email << endl << endl;

}
void wyswietlWszystkichAdresatow(vector<Adresat> adresaci)
{
    if(!adresaci.empty())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            wyswietlAdresata(adresaci,itr);
        }
    }
    else cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}

void wyszukajPoImieniu(vector <Adresat> adresaci)
{
    system("cls");

    if(!adresaci.empty())
    {
        string imieSzukanejOsoby;
        cout<<"Podaj imie osoby, ktorej szukasz: ";
        cin>>imieSzukanejOsoby;
        system("cls");

        bool czyIstniejeKontakt = false;
        for(vector<Adresat>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++)
        {
            if(itr -> imie == imieSzukanejOsoby)
            {
                czyIstniejeKontakt = true;
                wyswietlAdresata(adresaci,itr);
            }
        }
        if (czyIstniejeKontakt == false)
            cout << endl << "Nie ma osoby o takim imieniu w ksiazce adresowej!" << endl << endl;
    }
    else cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}

void wyszukajPoNazwisku(vector <Adresat> adresaci)
{
    system("cls");

    if(!adresaci.empty())
    {
        string nazwiskoSzukanejOsoby;
        cout<<"Podaj nazwisko osoby, ktorej szukasz: ";
        cin>>nazwiskoSzukanejOsoby;
        system("cls");

        bool czyIstniejeKontakt = false;
        for(vector<Adresat>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++)
        {
            if(itr -> nazwisko == nazwiskoSzukanejOsoby)
            {
                czyIstniejeKontakt = true;
                wyswietlAdresata(adresaci,itr);
            }

        }
        if (czyIstniejeKontakt == false)
            cout << endl << "Nie ma osoby o takim nazwisku w ksiazce adresowej!" << endl << endl;
    }
    else cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}

int usunAdresata(vector <Adresat> &adresaci, int &iloscOsob)
{
    ofstream plik;
    system("cls");


    if(adresaci.size()>0)
    {
        int idAdresataDoUsuniecia;
        cout<<"Podaj ID adresata do usuniecia: "<<endl;
        cin>> idAdresataDoUsuniecia;
        system("cls");

        bool czyIstniejeKontaktOTakimId = false;
        for(vector <Adresat>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++)
        {
            if(itr -> id == idAdresataDoUsuniecia)
            {
                czyIstniejeKontaktOTakimId = true;
                system("cls");
                cout<<"Adresat, ktory zostanie usuniety: " <<endl;
                wyswietlAdresata(adresaci,itr);
                cout<<"Czy na pewno chcesz usunac adresata? (t)"<<endl;

                if(getch()=='t'||getch()=='T')
                {
                    nadpisaniePlikuDoUsuwaniaAdresata(adresaci,itr);
                    adresaci.erase(itr);
                    iloscOsob--;
                    cout << endl << "Kontakt zostal usuniety" << endl;

                    Sleep(1000);
                    return idAdresataDoUsuniecia;

                }
                else
                {
                    return 0;
                }
            }
            plik.close();

        }
        if (czyIstniejeKontaktOTakimId == false)
            cout << endl << "Nie ma osoby o takim numerze id w ksiazce adresowej!" << endl << endl;
    }
    else
        cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}


void edytujAdresata(vector <Adresat> &adresaci)
{
    system("cls");

    if(!adresaci.empty())
    {
        bool czyIstniejeKontaktOTakimId = false;
        int idAdresataDoEdycji=0;
        cout<<"Podaj ID adresata, ktorego chcesz edytowac: ";
        cin>>idAdresataDoEdycji;



        for(vector <Adresat>::iterator itr=adresaci.begin(); itr!=adresaci.end(); itr++)
        {
            if( itr -> id == idAdresataDoEdycji)
            {
                czyIstniejeKontaktOTakimId=true;

                cout<<"Adresat ktorego dane beda edytowane: " <<endl;
                wyswietlAdresata(adresaci,itr);

                char wybor;
                while(true)
                {

                    cout<<"Ktora informacje chcesz edytowac?"<<endl;
                    cout << "1. Imie" << endl;
                    cout << "2. Nazwisko" << endl;
                    cout << "3. Numer telefonu" << endl;
                    cout << "4. Email" << endl;
                    cout << "5. Adres" << endl;
                    cout << "6. Powrot do menu" << endl;
                    cout<<"Twoj wybor:";
                    cin>>wybor;

                    if(wybor=='1')
                    {
                        system("cls");
                        cout<<"Wpisz nowe imie."<<endl;
                        string noweImie;
                        cin>>noweImie;

                        itr -> imie = noweImie;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;
                        Sleep (1000);
                        system("cls");

                        continue;
                    }
                    else if(wybor=='2')
                    {
                        system("cls");
                        cout<<"Wpisz nowe nazwisko."<<endl;
                        string noweNazwisko;
                        cin>>noweNazwisko;

                        itr -> nazwisko = noweNazwisko;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;

                        Sleep (1000);
                        system("cls");

                        continue;

                    }
                    else if(wybor=='3')
                    {
                        system("cls");
                        cout<<"Wpisz nowy numer telefonu."<<endl;
                        string nowyNumerTelefonu;
                        cin.sync();
                        getline(cin,nowyNumerTelefonu);

                        itr -> numerTelefonu = nowyNumerTelefonu;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;
                        Sleep (1000);
                        system("cls");

                        continue;

                    }
                    else if(wybor=='4')
                    {
                        system("cls");
                        cout<<"Wpisz nowy email."<<endl;
                        string nowyEmail;
                        cin>>nowyEmail;

                        itr -> email = nowyEmail;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;
                        Sleep (1000);
                        system("cls");

                        continue;

                    }
                    else if(wybor=='5')
                    {
                        system("cls");
                        cout<<"Wpisz nowy adres."<<endl;
                        string nowyAdres;
                        cin.sync();
                        getline(cin,nowyAdres);

                        itr -> adres = nowyAdres;
                        nadpisaniePlikuDoEdycjiAdresata(adresaci,itr);
                        cout << "Dane zostaly zaktualizowane." << endl;

                        Sleep (1000);
                        system("cls");

                        continue;

                    }
                    else if(wybor=='6')
                    {
                        break;
                    }
                }
                break;
            }

        }
        if (czyIstniejeKontaktOTakimId == false)
            cout << endl << "Nie ma osoby o takim numerze id w ksiazce adresowej!" << endl << endl;
    }
    else
        cout<<"Ksiazka adresowa jest pusta!"<<endl;

    system("pause");
}

int main()
{
    vector <Adresat> adresaci;

    int iloscOsob=0;
    char wybor;

    iloscOsob=wczytajOsobyZPliku(adresaci);

    while (true)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: " << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            system ("cls");
            dodajOsobe(adresaci, iloscOsob);
        }
        else if (wybor == '2')
        {
            system ("cls");
            wyszukajPoImieniu(adresaci);
        }
        else if (wybor == '3')
        {
            system ("cls");
            wyszukajPoNazwisku(adresaci);
        }
        else if (wybor == '4')
        {
            system ("cls");
            wyswietlWszystkichAdresatow(adresaci);
        }
        else if (wybor == '5')
        {
            system ("cls");
            usunAdresata(adresaci, iloscOsob);

        }
        else if (wybor == '6')
        {
            system ("cls");
            edytujAdresata(adresaci);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }
    return 0;
}











