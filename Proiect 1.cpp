#include <iostream>
#include <ctime>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <list>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;


//                                --------------------------------CLASA MATERIE--------------------------------------------
class Materie
{
    string denumire;
    bool optional;
    int* note;
    int nr_note;
public:
    const Materie operator--();
    const Materie operator--(int);
    friend bool operator==(const Materie mat1, const Materie mat2);
    friend bool operator<(const Materie mat1, const Materie mat2);
    int operator[](int index);
    friend istream &operator>>(istream &in, Materie& mat);
    friend ostream &operator<<(ostream &out, const Materie &mat);
    void set_note(int *note, int nr_note);
    const int* get_note();
    Materie &operator=(const Materie &mat);
    Materie()
    {
        denumire="-";
        optional=false;
        note=nullptr;
        nr_note=0;


    }
    Materie(char* denumire, bool optional, int note[], int nr_note)
    {
        this->denumire=denumire;
        this->optional=optional;
        this->nr_note=nr_note;
        this->note=new int[this->nr_note];
        for(int i=0; i<this->nr_note; i++)
            this->note[i]=note[i];


    }
    Materie(char denumire[], bool optional)
    {
        this->denumire=denumire;
        this->optional=optional;
        note=new int[0];
        nr_note=0;
    }
    Materie(const Materie &materie)
    {
        this->denumire=materie.denumire;
        this->optional=materie.optional;
        this->nr_note=materie.nr_note;
        this->note=new int[materie.nr_note];
        for(int i=0; i<this->nr_note; i++)
            this->note[i]=materie.note[i];
    }
    ~Materie()
    {
        delete []this->note;

    }
    string get_denumire()
    {
        return denumire;
    }
    void set_denumire( char denumire[])
    {
        this->denumire=denumire;
    }
    void adaugare_nota(int nota)
    {

        int *aux;
        this->nr_note++;
        aux=new int[this->nr_note];
        for (int i=0; i<nr_note-1; i++)
            aux[i]=this->note[i];
        aux[nr_note-1]=nota;
        delete []this->note;
        this->note=new int[this->nr_note];
        for(int i=0; i<nr_note; i++)
            this->note[i]=aux[i];




        delete []aux;


    }
    float medie()
    {
        float media,suma=0;
        for (int i=0; i<=nr_note-1; i++)
            suma+=*(note+i);
        media=suma/nr_note;
        return media;
    }
    int medie_rotunjita()
    {
        float media;
        media=this->medie();
        if (media-int(media)>=0.5)
            media=int(media)+1;
        else
            media=int(media);
        return media;
    }
    int get_nr_note()
    {
        return this->nr_note;
    }
};
bool operator<(const Materie mat1, const Materie mat2)
{
    if(mat1.nr_note<mat2.nr_note)
        return true;
    else
        return false;
}
bool operator==(const Materie mat1, const Materie mat2)
{
    if (mat1.denumire==mat2.denumire)
        return true;
    else
        return false;
}
const Materie Materie::operator--(int)
{
    Materie aux(*this);
    this->nr_note--;
    return aux;

}
const Materie Materie::operator--()
{
    this->nr_note--;
    return *this;
}
int Materie::operator[](int index)
{
    if (0<=index && index <=this->nr_note)
    {
        int nr=0;
        for(int i=0; i<=this->nr_note; i++)
        {
            if(nr==index)
                return *(this->note+i);
            nr++;
        }
    }
    cout<<endl<<"index invalid";
}
void Materie::set_note(int *note, int nr_note)
{
    if (this->note!=nullptr)
        delete [] this->note;
    this->nr_note=nr_note;
    this->note=new int[this->nr_note];
    for (int i=0; i<nr_note; i++)
        this->note[i]=note[i];
}
const int* Materie::get_note()
{
    return this->note;
}
Materie &Materie:: operator=(const Materie &mat)
{

    if (this !=&mat)
    {
        if(this->note!=nullptr)
            delete[] this->note;
        this->denumire=mat.denumire;

        this->optional=mat.optional;
        this->nr_note=mat.nr_note;

        this->note=new int[nr_note];
        for(int i=0; i<this->nr_note; i++)
            this->note[i]=mat.note[i];

    }
    return *this;
}
istream &operator>>(istream &in, Materie& mat)
{
    cout<<"Numele materiei= ";
    in>>mat.denumire;
    int optional;
    cout<<endl<<"Dati valoarea 1 daca materia este optionala sau 0 daca este obligatorie: ";

    do
    {

        in>>optional;
        switch(optional)
        {
        case 1:
            mat.optional=true;
            break;
        case 0:
            mat.optional=false;
            break;
        default:
            cout<<"valoare incorecta, incercati din nou: ";

        }



    }
    while(optional!=0 && optional!=1);
    cout<<endl<<"Care este numarul de note de la materia "<<mat.denumire<<" : ";
    in>>mat.nr_note;
    cout<<"Introduceti notele separate prin enter: ";
    if(mat.note!=nullptr)
        delete[] mat.note;
    mat.note=new int[mat.nr_note];
    for (int i=0; i<mat.nr_note; i++)
        in>>mat.note[i];
    return in;

}
ostream &operator<<(ostream &out, const Materie &mat)
{
    out<<endl<<"__________MATERIE______";
    out<<endl<<"NUME= "<<mat.denumire<<endl<<"NR_NOTE= "<<mat.nr_note<<endl;
    if (mat.optional==true)
        out<<"Materia este optionala";
    else
        out<<"Materia este obligatorie";
    out<<endl;
    if (mat.nr_note==0)
        out<<"Inca nu exista note"<<" ";
    else
    {
        out<<"NOTE= ";
        for (int i=0; i<=mat.nr_note-1; i++)
            out<<*(mat.note+i)<<" ";
    }


    return out;
}


//                            -------------------------CLASA ELEV--------------------------
class Elev
{
    string nume, prenume;
    int varsta, clasa;
    list<Materie>materii;
    static int contor;
    const int id_elev;
public:
    Elev();
    Elev(string nume, string prenume, int varsta, list <Materie> materii, int clasa);
    friend istream &operator>>(istream &in, Elev& el);
    friend ostream &operator<<(ostream &out, Elev &el);
    int get_id();
    int get_varsta();
    string get_nume();
    string get_prenume();
    void set_nume(string nume);
    void set_prenume(string prenume);
    int get_clasa();
    void set_varsta(int varsta);
    void set_clasa(int clasa);
    void afisare_elev();
    Elev &operator=(const Elev &el);
    Elev(const Elev &el);
    void afisare_medii();
    void media_generala();
    Materie operator[](int index);
    const Elev operator++();
    const Elev operator++(int);
    friend Elev &operator+(Elev &el, string x);
    friend Elev &operator+(string x, Elev &el);
    friend Elev &operator-(Elev &el, int x);
    friend Elev &operator-(int x,Elev &el);
    explicit operator double();
    friend bool operator< (const Elev &el1, const Elev &el2);
    friend bool operator==(const Elev &el1, const Elev &el2);
    friend Elev &operator+(const Materie mat, Elev &el);
    friend Elev &operator+(Elev &el, const Materie mat);
    list<Materie> &get_list();

    ~Elev();
};

int Elev::contor=0;
Elev::~Elev() {}
Elev &operator-(Elev &el, int x)
{
    el.varsta=el.varsta-x;
    return el;
}
Elev &operator-(int x, Elev &el)
{
    el.varsta=el.varsta-x;
    return el;;
}
int Elev::get_varsta()
{
    return this->varsta;
}
string Elev::get_nume()
{
    return this->nume;
}
string Elev::get_prenume()
{
    return this->prenume;
}
int Elev::get_id()
{
    return this->id_elev;
}
int Elev::get_clasa()
{
    return this->clasa;
}
void Elev::set_nume(string nume)
{
    this->nume=nume;
}
void Elev::set_prenume(string prenume)
{
    this->prenume=prenume;
}
void Elev::set_varsta(int varsta)
{
    this->varsta=varsta;
}
void Elev::set_clasa(int clasa)
{
    if (clasa<9 || clasa>12)
        while (true)
        {
            cout<<endl<<"Valoare incorecta ";
            cin>>clasa;
            if(clasa>=9 && clasa<=12)
            {
                this->clasa=clasa;
                break;
            }
        }
    else
        this->clasa=clasa;

}
list<Materie> &Elev::get_list()
{
    return this->materii;
}
Elev &operator+(Elev &el, const Materie mat)
{
    el.materii.push_back(mat);
    return el;
}
Elev &operator+(const Materie mat, Elev &el)
{
    el.materii.push_back(mat);
    return el;
}
bool operator==(const Elev &el1, const Elev &el2)
{
    if (el1.varsta==el2.varsta && el1.nume==el2.nume && el1.prenume==el2.prenume && el1.clasa==el2.clasa)
        return true;
    return false;
}
Elev::operator double()
{
    return (double)this->varsta;
}
bool operator< (const Elev &el1,const Elev &el2)
{
    if (el1.varsta<el2.varsta)
        return true;
    else
        return false;
}
Elev &operator+(Elev &el, string x)
{

    el.prenume=el.prenume+" "+x;
    return el;
}
Elev &operator+(string x, Elev &el)
{
    el.prenume=x+" "+el.prenume;
    return el;
}
const Elev Elev::operator++()
{
    this->clasa++;
    return *this;
}
const Elev Elev::operator++(int)
{
    Elev aux(*this);
    this->clasa++;
    return aux;
}
Materie Elev::operator[] (int index)
{
    if (0<=index && index <=this->materii.size())
    {
        int contor=0;
        list <Materie>::iterator it;
        for (it=this->materii.begin(); it!=this->materii.end(); it++)
        {
            if (contor==index)
            {
                return *it;
                break;
            }
            else
                contor++;
        }
    }
    cout<<endl<<"index invalid";
}
void Elev:: afisare_medii()
{
    list <Materie>::iterator it;
    for (it=materii.begin(); it!=materii.end(); it++)
    {
        cout<<endl<<"Media notelor la materia "<<it->get_denumire()<<" este= "<<it->medie();
        cout<<"----> "<<"Media finala, in urma rotunjirii este= "<<it->medie_rotunjita();
    }

}
void Elev::media_generala()
{
    float nr=0, suma=0;
    int corigent=0;
    list <Materie>::iterator it;
    for(it=materii.begin(); it!=materii.end(); it++)
    {
        nr++;
        suma+=it->medie_rotunjita();
        if(it->medie_rotunjita()<5)
            corigent++;
    }
    if(corigent==0)
        cout<<endl<<"Media generala a elevului "<<nume<<" "<<prenume<<" este= "<<suma/nr;
    else
        cout<<endl<<"Media generala a elevului "<<nume<<" "<<prenume<<" este= "<<suma/nr<<", dar acesta este corigent la "<<corigent<<" materii";
}
Elev &Elev::operator=(const Elev &el)
{

    if(this !=&el)
    {
        this->nume=el.nume;
        this->prenume=el.prenume;
        this->varsta=el.varsta;
        this->materii=el.materii;
        this->clasa=el.clasa;
    }
    return *this;

}
Elev::Elev(const Elev &el):id_elev(contor)
{
    this->nume=el.nume;
    this->prenume=el.prenume;
    this->varsta=el.varsta;
    this->materii=el.materii;
    this->clasa=el.clasa;
}
Elev::Elev():id_elev(contor++)
{
    this->nume="anonim";
    this->prenume="anonim";
    this->varsta=0;
    list<Materie> materii= {};
    this->clasa=0;
}
Elev::Elev(string nume, string prenume, int varsta, list <Materie> materii, int clasa):id_elev(contor++)
{
    this->nume=nume;
    this->prenume=prenume;
    this->varsta=varsta;
    this->materii=materii;
    this->clasa=clasa;
}
istream &operator>>(istream &in, Elev& el)
{

    cout<<"nume elev= ";
    in>>el.nume;
    cout<<endl<<"prenume elev= ";
    in>>el.prenume;
    cout<<endl<<"varsta elev= ";
    in>>el.varsta;
    cout<<endl<<"in ce clasa este elevul 9/10/11/12 ";
    int ok;
    while (true)
    {
        in>>ok;
        if(ok>=9 && ok<=12)
        {
            el.clasa=ok;
            break;
        }
        else
            cout<<endl<<"Valoare incorecta ";
    }
    while (true)
    {
        cout<<"Apasati tasta 1 pentru a adauga o materie elevului "<<el.nume<<" "<<el.prenume<<"( orice alt input va intrerupe procesul de adaugare): ";
        in>>ok;

        if (ok==1)
        {
            Materie mat;
            in>>mat;
            el.materii.push_back(mat);
        }
        else
            break;
    }
    return in;
}
void Elev::afisare_elev()
{
    cout<<endl<<"_______ELEV_______"<<endl;
    list<Materie>::iterator it;
    cout<<endl<<"#ID ELEV= "<<this->id_elev;
    cout<<endl<<"NUME= "<<this->nume;
    cout<<endl<<"PRENUME= "<<this->prenume;
    cout<<endl<<"VARSTA= "<<this->varsta;
    cout<<endl<<"CLASA= "<<this->clasa;
}
ostream &operator<<(ostream &out,  Elev &el)
{
    out<<endl<<"_______ELEV_______"<<endl;
    list<Materie>::iterator it;
    out<<endl<<"#ID ELEV= "<<el.id_elev;
    out<<endl<<"NUME= "<<el.nume;
    out<<endl<<"PRENUME= "<<el.prenume;
    out<<endl<<"VARSTA= "<<el.varsta;
    out<<endl<<"CLASA= "<<el.clasa;
    if (el.materii.empty()==true)
        cout<<endl<<"Elevul nu are inca materii adaugate ";
    else
        for (it=el.materii.begin(); it!=el.materii.end(); it++)
            out<<*it<<endl;
    return out;
}
list<Elev> elevi;
//-----------------------------------------------------------------Class CLASA--------------------------------------------
class Clasa
{
    char *profil;
    string materii[50];
    int numar, etaj;
    int numar_materii;
    static int contor;
    const int id_clasa;
public:
    Clasa();
    Clasa(char profil[],string materii[], int numar, int etaj, int numar_materii);
    Clasa(const Clasa &cls);
    friend bool operator>(const Clasa cls1, const Clasa cls2);
    const Clasa operator++();
    const Clasa operator++(int);
    friend Clasa &operator+(Clasa &cls, int x);
    friend Clasa &operator+(int x, Clasa &cls);
    friend Clasa &operator-(Clasa &cls, int x);
    friend Clasa &operator-(int x, Clasa &cls);
    ~Clasa();
    friend bool operator==(const Clasa cls1,const  Clasa cls2);
    Clasa &operator=(const Clasa &cls);
    bool verificare_elev(Elev &el);
    friend istream &operator>>(istream &in, Clasa &cls);
    friend ostream &operator<<(ostream &out, Clasa &cls);



};

int Clasa::contor=0;
bool operator>(const Clasa cls1, const Clasa cls2)
{
    if(cls1.numar>cls2.numar)
        return true;
    else
        return false;
}
bool operator==(const Clasa cls1, const Clasa cls2)
{
    if (cls1.numar==cls2.numar)
        return true;
    else
        return false;
}
Clasa &operator+(Clasa &cls, int x)
{
    if (cls.numar+x>=13)
    {
        cout<<endl<<"Numarul introdus e prea mare(nu exista elevi in clasa a "<<cls.numar+x<<"-a) ";
        return cls;
    }
    else
        cls.numar=cls.numar+x;
    return cls;
}
Clasa &operator+(int x, Clasa &cls)
{
    if (cls.numar+x>=13)
    {
        cout<<endl<<"Numarul introdus e prea mare(nu exista elevi in clasa a "<<cls.numar+x<<"-a) ";
        return cls;
    }
    else
        cls.numar=cls.numar+x;
    return cls;
}
Clasa &operator-(Clasa &cls, int x)
{
    if (cls.numar-x<=8)
    {
        cout<<endl<<"Numarul introdus e prea mare(nu exista elevi in clasa a "<<cls.numar-x<<"-a) ";
        return cls;
    }
    else
        cls.numar=cls.numar-x;
    return cls;
}
Clasa &operator-(int x, Clasa &cls)
{
    if (cls.numar-x<=8)
    {
        cout<<endl<<"Numarul introdus e prea mare(nu exista elevi in clasa a "<<cls.numar-x<<"-a) ";
        return cls;
    }
    else
        cls.numar=cls.numar-x;
    return cls;
}
const Clasa Clasa::operator++()
{
    this->etaj++;
    return *this;
}
const Clasa Clasa::operator++(int)
{
    Clasa aux(*this);
    this->etaj++;
    return aux;
}
Clasa &Clasa::operator=(const Clasa &cls)
{
    if (this!=&cls)
    {
        if (this->profil!=nullptr)
            delete [] this->profil;
        this->profil=new char [strlen(cls.profil)];
        strcpy(this->profil,cls.profil);
        this->numar_materii=cls.numar_materii;
        for(int i=0; i<this->numar_materii; i++)
            this->materii[i]=cls.materii[i];
        this->numar=cls.numar;
        this->etaj=cls.etaj;
        //this->id_clasa=cls.id_clasa;
    }
    return *this;
}
bool Clasa::verificare_elev(Elev &el)
{
    if (el.get_clasa()!=this->numar)
    {
        cout<<"Elevul nu se poate transfera la clasa de profil "<<this->profil<<" deoarece el este clasa "<<el.get_clasa()<<"-a"<<", nu a "<<this->numar<<"-a..."<<endl;
        return false;
    }
    else
    {
        int ok=0;
        list <Materie>::iterator it;
        for (int i=0; i<this->numar_materii; i++)
            for(it=el.get_list().begin(); it!=el.get_list().end(); it++)
                if (it->get_denumire()==this->materii[i])
                    if (it->medie_rotunjita()>=5)
                    {

                        ok++;
                        break;
                    }

                    else
                        ok=0;
        if (ok==this->numar_materii)
            return true;
        else
            return false;
    }


}

Clasa::Clasa(char profil[], string materii[], int numar, int etaj, int numar_materii):id_clasa(contor++)
{
    if (this->profil!=nullptr)
        delete []this->profil;
    this->profil=new char[strlen(profil)+1];
    strcpy(this->profil,profil);
    for(int i=0; i<numar_materii; i++)
        this->materii[i]=materii[i];
    this->numar=numar;
    this->etaj=etaj;

}

Clasa::Clasa(const Clasa &cls):id_clasa(contor)
{
    if (this->profil!=nullptr)
        delete []this->profil;
    this->profil=new char[strlen(cls.profil)+1];
    strcpy(this->profil,cls.profil);
    this->numar=cls.numar;
    this->etaj=cls.etaj;
    this->numar_materii=cls.numar_materii;
    for(int i=0; i<numar_materii; i++)
        this->materii[i]=cls.materii[i];
}
Clasa::Clasa():id_clasa(contor++)
{
    this->profil=new char[0];
    this->numar_materii=0;
    this->etaj=0;
    this->numar=0;
}
Clasa::~Clasa()
{
    delete [] profil;
}
istream &operator>>(istream &in, Clasa &cls)
{

    cout<<"Scrieti profilul clasei: ";
    if (cls.profil!=nullptr)
        delete [] cls.profil;
    cls.profil=new char[50];
    in>>cls.profil;
    int ok;
    cout<<"In ce an sunt elevii? (9/10/11/12)";
    while (true)
    {
        in>>ok;
        if(ok>=9 && ok<=12)
        {
            cls.numar=ok;
            break;
        }
        else
            cout<<endl<<"Valoare incorecta ";
    }
    cout<<"La ce etaj se afla clasa?";
    in>>cls.etaj;
    cout<<"Cate materii obligatorii sunt in aceasta clasa? (ATENTIE, profilul este "<<cls.profil<<") ";
    in>>cls.numar_materii;
    if (cls.numar_materii!=0)
        cout<<"Introduceti materiile, separate prin enter: ";
    for(int i=0; i<cls.numar_materii; i++)
        in>>cls.materii[i];
    return in;
}
ostream &operator<<(ostream &out, Clasa &cls)
{
    out<<endl<<" __________CLASA________"<<endl;
    out<<endl<<"#ID_CLASA= "<<cls.id_clasa;
    out<<endl<<"PROFIL= "<<cls.profil;
    out<<endl<<"NUMAR= "<<cls.numar;
    out<<endl<<"ETAJ= "<<cls.etaj;
    out<<endl<<"NUMAR MATERII= "<<cls.numar_materii;
    out<<endl<<"Materii= ";
    for(int i=0; i<cls.numar_materii; i++)
        out<<cls.materii[i]<<" ";
    return out;
}
class Scoala
{
    int numar,nr_clase;
    string nume;
    bool privat;
    Clasa *clase;
public:
    Scoala();
    Scoala(int numar, int nr_clase, string nume,bool privat, Clasa clase[]);
    Clasa &operator[] (int index);
    friend bool operator>=(const Scoala scl1,const Scoala scl2);
    Scoala(const Scoala &scl);
    void afisare_scoala();
    friend bool operator==(Scoala scl1, Scoala scl2);
    const Scoala operator++();
    const Scoala operator++(int);
    friend istream &operator>>(istream &in, Scoala &scl);
    friend ostream &operator<<(ostream &out, Scoala &scl);
    Scoala &operator=(const Scoala &scl);
    bool compatibilitate_elev(int id_elev);
    ~Scoala();
};
Scoala scl;
bool operator>=(const Scoala scl1,const Scoala scl2)
{
    if (scl1.nr_clase>=scl2.nr_clase)
        return true;
    else
        return false;
}
bool operator==(Scoala scl1, Scoala scl2)
{
    if (scl1.numar==scl2.numar)
        return true;
    else
        return false;
}
const Scoala Scoala::operator++()
{
    this->numar++;
    return *this;
}
const Scoala Scoala::operator++(int)
{
    Scoala aux(*this);
    this->numar++;
    return aux;
}
void Scoala::afisare_scoala()
{
    cout<<"______________SCOALA_______________";
    cout<<endl<<"NUMAR= "<<this->numar;
    cout<<endl<<"NUME= "<<this->nume;
    if (this->privat==true)
        cout<<endl<<"Scoala este privata.";
    else
        cout<<endl<<"Scoala nu este privata.";
    cout<<endl<<"NUMAR CLASE= "<<this->nr_clase;
}
Clasa &Scoala::operator[](int index)
{
    if (0<=index && index <=this->nr_clase)
    {
        return *(this->clase+index);
    }
    cout<<endl<<"index invalid";
}
Scoala &Scoala::operator=(const Scoala &scl)
{
    if (this!=&scl)
    {
        if (this->clase!=nullptr)
            delete []clase;
        this->numar=scl.numar;
        this->nr_clase=scl.nr_clase;
        this->nume=scl.nume;
        this->privat=scl.privat;
        this->clase=new Clasa[this->nr_clase];
        for (int i=0; i<this->nr_clase; i++)
            this->clase[i]=scl.clase[i];
        //this->id_clasa=cls.id_clasa;
    }
    return *this;
}
bool Scoala::compatibilitate_elev(int id_elev)
{
    list <Elev>::iterator it;
    for(it=elevi.begin(); it!=elevi.end(); it++)
        if (it->get_id()==id_elev)
        {
            for (int i=0; i<this->nr_clase; i++)
                if (this->clase[i].verificare_elev(*it)==true)
                {
                    cout<<"Elevul "<<endl;
                    it->afisare_elev();
                    cout<<"                                                                SE POATE TRANSFERA LA CLASA:"<<endl;
                    cout<<this->clase[i];
                    return true;
                }
        }
    return false;
}
istream &operator>>(istream &in, Scoala &scl)
{
    cout<<"Numarul scolii= ";
    in>>scl.numar;
    cout<<"Numele scolii= ";
    in>>scl.nume;
    int privat;
    cout<<"Dati valoarea 0 daca scoala este privata/ 1 daca scoala este publica :";
    do
    {

        in>>privat;;
        switch(privat)
        {
        case 1:
            scl.privat=false;
            break;
        case 0:
            scl.privat=true;
            break;
        default:
            cout<<"valoare incorecta, incercati din nou: ";

        }
    }
    while(privat!=0 && privat!=1);
    cout<<"Cate clase are scoala? ";
    in>>scl.nr_clase;
    scl.clase=new Clasa [scl.nr_clase];
    for(int i=0; i<scl.nr_clase; i++)
    {
        cout<<"Clasa "<<i<<":"<<endl;
        in>>scl.clase[i];
    }

    return in;




}
ostream &operator<<(ostream &out, Scoala &scl)
{
    out<<"______________SCOALA_______________";
    out<<endl<<"NUMAR= "<<scl.numar;
    out<<endl<<"NUME= "<<scl.nume;
    if (scl.privat==true)
        out<<endl<<"Scoala este privata.";
    else
        out<<endl<<"Scoala nu este privata.";
    out<<endl<<"NUMAR CLASE= "<<scl.nr_clase;
    for(int i=0; i<scl.nr_clase; i++)
        out<<scl.clase[i];
}

Scoala::Scoala()
{
    clase=nullptr;
    numar=0;
    nume="-";
    privat=false;

}
Scoala::Scoala(int numar, int nr_clase, string nume,bool privat, Clasa clase[])
{
    this->numar=numar;
    this->nr_clase=nr_clase;
    this->nume=nume;
    this->privat=privat;
    if (this->clase!=nullptr)
        delete [] this->clase;
    this->clase=new Clasa[nr_clase];
    for(int i=0; i<nr_clase; i++)
        this->clase[i]=clase[i];
}
Scoala::Scoala(const Scoala &scl)
{
    this->numar=scl.numar;
    this->nr_clase=scl.nr_clase;
    this->nume=scl.nume;
    this->privat=scl.privat;
    this->clase=new Clasa[this->nr_clase];

    for(int i=0; i<this->nr_clase; i++)
        this->clase[i]=scl.clase[i];

}
Scoala::~Scoala()
{
    delete []clase;
}
void meniu ()
{
    cout<<endl<<"----------MENIU PRINCIPAL----------";
    cout<<endl<<"Dati valoarea 0 pentru a opri programul";
    cout<<endl<<"Dati valoarea 1 pentru a administra elevii ce vor sa se transfere";
    cout<<endl<<"Dati valoarea 2 pentru a crea scoala";
    cout<<endl<<"Dati valoarea 3 pentru a administra scoala";
    cout<<endl<<"Dati valoarea 4 pentru a incepe procesul de filtrare al elevilor, in functie de scoala ";
}
void meniu_elevi()
{
    cout<<endl<<"-----------MENIU ELEVI--------------";
    cout<<endl<<"Dati valoarea 0 pentru a iesi din acest meniu";
    cout<<endl<<"Dati valoarea 1 pentru a adauga un elev ";
    cout<<endl<<"Dati valoarea 2 pentru a afisa elevii (+materiile fiecaruia)";
    cout<<endl<<"Dati valoarea 3 pentru a afisa elevii (fara materii) ";
    cout<<endl<<"Dati valoarea 4 pentru a adauga o nota elevului(in functie de id)";
    cout<<endl<<"Dati valoarea 5 pentru a intra in meniul -> MEDII ELEVI";
    cout<<endl<<"Dati valoarea 6 pentru a creste clasa unui anumit elev";
    cout<<endl<<"Dati valoarea 7 pentru a afisa varsta celui mai mic elev";
    cout<<endl<<"Dati valoarea 8 pentru a adauga o materie unui elev";
    cout<<endl<<"Dati valoarea 9 pentru a sterge ultima nota a unui elev";
    cout<<endl<<"Dati valoarea 11 pentru a adauga un prenume unui elev ";
    cout<<endl<<"Dati valoarea 12 pentru a scadea varsta unui elev";
}
void medii_elevi()
{
    cout<<endl<<"------------MEDII ELEVI--------------";
    cout<<endl<<"Dati valoarea 0 pentru a iesi din acest meniu";
    cout<<endl<<"Dati valoarea 1 pentru a revedea toti elevii introdusi in baza de date pana in acest moment (+materiile lor)";
    cout<<endl<<"Dati valoarea 2 pentru a afla toate mediile elevilor la o anumita materie ";
    cout<<endl<<"Dati valoarea 3 pentru a afisa mediile unui anumit elev";
    cout<<endl<<"Dati valoarea 4 pentru a afisa media generala a fiecarui elev";

}
void meniu_scoala()
{
    cout<<endl<<"-------------MENIU SCOALA--------------";
    cout<<endl<<"Dati valoarea 0 pentru a parasi acest meniu";
    cout<<endl<<"Dati valoarea 1 pentru a afisa scoala (+clasele acesteia)";
    cout<<endl<<"Dati valoarea 2 pentru a afisa doar informatii despre scoala";
    cout<<endl<<"Dati valoarea 3 pentru a verifica daca un elev(in functie de id), se poate transfera la orice clasa din scoala";
    cout<<endl<<"Dati valoarea 4 pentru a verifica daca un elev(in functie de id), se poate transfera la o anumita clasa(in functie de index)" ;
    cout<<endl<<"Dati valoarea 9 pentru a afisa elevii(+materiile lor)";
}
void operatii_scoala()
{
    int nr,ok=1;
    while (ok)
    {
        cout<<endl<<"Dati valoarea 10 pentru a revedea meniul in care va aflati ";
        cin>>nr;
        switch(nr)
        {
        case 0:
        {
            ok=0;
            break;
        }
        case 1:
        {
            cout<<scl;

            break;
        }
        case 2:
        {
            scl.afisare_scoala();
            break;
        }
        case 3:
        {
                int id;
                cout<<"ID ELEV= ";
                cin>>id;
                if (scl.compatibilitate_elev(id)==false)
                    cout<<endl<<"elevul nu se poate transfera nicaieri :/";
                break;
        }

        case 4:
            {
                int id;
                cout<<"ID ELEV= ";
                cin>>id;
                list <Elev>::iterator it;
                int index;
                cout<<"INDEX CLASA= ";
                cin>>index;
                for (it=elevi.begin();it!=elevi.end();it++)
                    if (it->get_id()==id)
                    break;
                if (scl[index].verificare_elev(*it)==true)
                    cout<<endl<<"Elevul se poate transfera la clasa cu id-ul= "<<index;
            }
        case 9:
            {
               list <Elev>::iterator it;
            for (it=elevi.begin(); it!=elevi.end(); it++)
                cout<<*it;
            break;
            }
        case 10:
        {
            meniu_scoala();
            break;
        }

        default:
            cout<<"Valoare incorecta";

        }

    }
}
void operatii_medii()
{
    int nr,ok=1;
    while (ok)
    {
        cout<<endl<<"Dati valoarea 10 pentru a revedea meniul in care va aflati ";
        cin>>nr;
        switch(nr)
        {
        case 0:
        {
            ok=0;
            break;
        }
        case 1:
        {
            list <Elev>::iterator it;
            for (it=elevi.begin(); it!=elevi.end(); it++)
                cout<<*it;
            break;
        }
        case 2:
        {
            cout<<endl<<"MATERIA= ";
            string materie;
            cin>>materie;
            list <Elev>::iterator it;
            list <Materie>::iterator bit;
            for(it=elevi.begin(); it!=elevi.end(); it++)
                for (bit=it->get_list().begin(); bit!=it->get_list().end(); bit++)
                    if(bit->get_denumire()==materie)
                    {
                        cout<<endl<<"Media elevului "<<it->get_nume()<<" "<<it->get_prenume()<<" la materia "<<bit->get_denumire()<<" este= "<<bit->medie();
                        cout<<"----> "<<"Media finala, in urma rotunjirii este= "<<bit->medie_rotunjita();

                    }
            break;
        }
        case 3:
        {
            cout<<"ID ELEV= ";
            int id;
            cin>>id;
            list <Elev>::iterator it;
            for(it=elevi.begin(); it!=elevi.end(); it++)
                if (it->get_id()==id)
                {
                    Elev el(*it);
                    for (int i=0; i<it->get_list().size(); i++)
                    {
                        cout<<endl<<"Media elevului "<<it->get_nume()<<" "<<it->get_prenume()<<" la materia "<<el[i].get_denumire()<<" este= "<<el[i].medie();
                        cout<<"----> "<<"Media finala, in urma rotunjirii este= "<<el[i].medie_rotunjita();
                    }

                }
            break;



        }
        case 4:
        {
            list <Elev>::iterator it;
            for (it=elevi.begin(); it!=elevi.end(); it++)
            {
                it->media_generala();

            }
            break;
        }
        case 10:
        {
            medii_elevi();
            break;
        }
        default:
            cout<<"Valoare incorecta";
        }
    }
}
void operatii_elevi()
{
    int nr,ok=1;

    while(ok)
    {
        cout<<endl<<"Dati valoarea 10 pentru a revedea meniul in care va aflati ";
        cin>>nr;
        switch(nr)
        {
        case 0:
        {
            ok=0;
            break;
        }
        case 1:
        {
            Elev el;
            cin>>el;
            elevi.push_back(el);
            break;
        }
        case 2:
        {
            list <Elev>::iterator it;
            for (it=elevi.begin(); it!=elevi.end(); it++)
                cout<<*it;
            break;
        }
        case 3:
        {
            list <Elev>::iterator it;
            for (it=elevi.begin(); it!=elevi.end(); it++)
                it->afisare_elev();
            break;
        }
        case 4:
        {
            int id,nota;
            string materia;
            cout<<"ID ELEV= ";
            cin>>id;
            int ok=0;
            cout<<"MATERIA LA CARE VREI SA INTRODUCI NOTA= ";
            cin>>materia;
            cout<<"NOTA PE CARE VREI SA O INTRODUCI= ";
            cin>>nota;
            list <Elev>::iterator it;
            list <Materie>::iterator bit;
            for(it=elevi.begin(); it!=elevi.end(); it++)
                if (it->get_id()==id)
                    for (bit=it->get_list().begin(); bit!=it->get_list().end(); bit++)
                        if(materia==bit->get_denumire())
                        {
                            bit->adaugare_nota(nota);
                            ok=1;
                        }

            if (ok==0)
                cout<<"Datele introduse sunt eronate :/";
            break;

        }
        case 5:
        {
            medii_elevi();
            operatii_medii();
            break;
        }
        case 6:
        {
            cout<<endl<<"ID ELEV= ";
            int id;
            cin>>id;
            list <Elev>::iterator it;
            for (it=elevi.begin(); it!=elevi.end(); it++)
                if(it->get_id()==id)
                {
                    Elev el(*it);
                    el++;
                    elevi.erase(it);
                    if (el.get_clasa()!=13)
                        elevi.push_back(el);
                    break;
                }
            break;
        }
        case 7:
        {
            list <Elev>::iterator it;
            Elev el;
            it=elevi.begin();
            el=*it;
            for(it=elevi.begin(); it!=elevi.end(); it++)
                if (*it<el)
                    el=*it;
            cout<<endl<<el.get_varsta()<<" ani.";
            break;
        }
        case 8:
            {
                cout<<"ID ELEV= ";
                int id;
                cin>>id;
                list <Elev>::iterator it;
                for(it=elevi.begin(); it!=elevi.end(); it++)
                    if (it->get_id()==id)
                {
                    Materie mat;
                    cin>>mat;
                    *it=*it+mat;
                }
                break;
            }
        case 9:
            {
                 cout<<"ID ELEV= ";
                int id;
                cin>>id;
                cout<<"Index materie (acestea sunt indexate de la 0)= ";
                int index;
                cin>>index;
                list <Elev>::iterator it;
                for(it=elevi.begin(); it!=elevi.end(); it++)
                    if (it->get_id()==id)
                    {
                        Elev el(*it);
                        --el[index];
                        elevi.erase(it);
                        elevi.push_back(el);

                    }
                break;
            }
        case 10:
        {
            meniu_elevi();
            break;
        }
        case 11:
            {
                cout<<"ID ELEV= ";
                int id;
                cin>>id;
                list <Elev>::iterator it;
                for(it=elevi.begin();it!=elevi.end();it++)
                    if(it->get_id()==id)
                {
                    cout<<"PRENUMELE DE ADAUGAT ";
                    string a;
                    cin>>a;
                    Elev el(*it);
                    elevi.erase(it);
                    elevi.push_back(el+a);
                    break;

                }
            break;
            }
        case 12:
            {
              cout<<"ID ELEV= ";
              int id;
              cin>>id;
              cout<<"Numarul pe care vrei sa il scazi din varsta elevului= ";
              int x;
              cin>>x;
              list <Elev>::iterator it;
                for(it=elevi.begin();it!=elevi.end();it++)
                    if(it->get_id()==id)
                    {
                    Elev el(*it);
                    elevi.erase(it);
                    elevi.push_back(el-x);
                    break;
                    }



                break;
            }
        default:
            cout<<endl<<"Valoarea introdusa este incorecta";
        }
    }

}
int main()
{
    int nr;
    cout<<" BINE AI VENIT, APASA ORICE TASTA (URMATA DE ENTER) PENTRU A INCEPE";
    cin>>nr;
    while (true)
    {
        meniu();
        cin>>nr;
        switch (nr)
        {
        case 0:
        {
            cout<<endl<<"O ZI FRUMOASA :) ";
            return 0;
        }

        case 1:
        {
            meniu_elevi();
            operatii_elevi();
            break;
        }
        case 2:
        {

            cin>>scl;
            break;
        }
        case 3:
        {
            meniu_scoala();
            operatii_scoala();
            break;
        }
        default:

            cout<<"Valoarea introdusa este incorecta";

        }
    }




    return 0;
}


