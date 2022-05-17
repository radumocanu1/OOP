#include <iostream>
#include <exception>
#include <string.h>
#include <stdexcept>
using namespace std;
#include <set>
#include <iterator>
#include <list>
#include <map>
#include <vector>
#include <bits/stdc++.h>

using std::runtime_error;
//sef de clasa sau diriginte
/*class Interface
{
public:
    virtual istream& citire(istream&)=0;
    virtual ostream &afisare(ostream&) const=0;
};*/

void exceptie_1(string s)
{
    for (int i=0;i<s.length();i++)
        if (s[i]>='a' && s[i]<='z')
            s[i]=s[i]-32;
    if (s=="MASCULIN" || s=="FEMININ")
        throw 1;
    else
        throw exception();
};
void exceptie_2(string s)
{
    if (s[0]<'A' || s[0]>'Z')
        throw 1;
     for (int i=1; i<s.length();i++)
         if (s[i-1]==' ' && (s[i]<'A' || s[i]>'Z'))
             throw 2;



}

class Om
{
protected:
    string nume;
    string sex;
    int varsta;

public:
    Om()
    {
        this->nume="anonim";
        this->varsta=0;
        this->sex="masculin";
    }
    Om(string nume, string sex, int varsta)
    {
        this->nume=nume;
        this->sex=sex;
        this->varsta=varsta;
    }
    Om(const Om &o)
    {
        this->nume=o.nume;
        this->sex=o.sex;
        this->varsta=o.varsta;
    }
    Om &operator=(const Om &o)
    {
        if (this!=&o)
        {
            this->nume=o.nume;
            this->varsta=o.varsta;
            this->sex=o.sex;
        }
        return *this;
    }
    friend istream &operator>>(istream &in, Om &o)
    {
        int ok=0;
        in.get();
        cout<<"NUME= ";
        while (ok!=1)
        {
            ok=1;
            try {

                std::getline(in,o.nume);
                exceptie_2(o.nume);

            }
            catch(int a)
            {
                ok=0;
                if (a==1)
                cout<<endl<<"Numele unei persoane trebuie sa inceapa cu litera mare (nu cu spatii sau alte caractere) ";
                else
                    cout<<endl<<"Atat numele, cat si prenumele unei persoane trebuie sa inceapa cu litera mare ";
            }
            catch(...)
            {
                cout<<"Exceptie necunoscuta, incercati din nou ";
                ok=0;
            }
        }
        cout<<"VARSTA= ";
        in>>o.varsta;
        cout<<"SEX (masculin/feminin)= ";
        ok=0;
        while (ok!=1)
        {
            ok=1;
            try {
                in>>o.sex;
                if (o.sex!="masculin" && o.sex!="feminin")
                {

                    exceptie_1(o.sex);
                }



            }
            catch(int)
            {
                cout<<endl<<"Atentie, programul este case sensitive! (introduceti valoarea din nou)  ";
                ok=0;
            }
            catch(...)
            {
                cout<<"Variatele sunt: masculin/feminin, incercati din nou  ";
                ok=0;
            }
        }






        return in;

    }
    bool operator<(const Om &o) const
    {
        if (this->varsta<o.varsta)
            return true;
        else
            return false;
    }
    friend ostream &operator<<(ostream &out, const Om &o)
    {
        out<<endl<<"NUME= "<<o.nume;
        out<<endl<<"VARSTA= "<<o.varsta;
        out<<endl<<"SEX= "<<o.sex;
        return out;
    }
    int get_varsta() const {
        return this->varsta;
    }
    virtual int get_id()
    {
        return 1;
    }

    virtual void descriere()
    {
        cout<<"Ființă superioară, socială, care se caracterizează prin gândire, inteligență și limbaj articulat iar din punct de vedere morfologic prin poziția verticală a corpului și structura piciorului adaptată la aceasta, mâinile libere și apte de a efectua mișcări fine și creierul deosebit de dezvoltat.";
    }

};
class Student:public Om
{
protected:
    int clasa;
    double media=5.00;
public:
    Student():Om()
    {
        this->clasa=0;
        this->media=0.00;
    }
    Student(string nume, string sex, int varsta, int clasa, double media):Om( nume,  sex, varsta)
    {
    this->clasa=clasa;
    this->media=media;
    }
    Student (const Student &s): Om(s)
    {
    this->clasa=s.clasa;
    this->media=s.media;
    }
    Student &operator=(const Student &s)
    {
        if (this!=&s)
        {
            Om::operator=(s);
            this->clasa=s.clasa;
            this->media=s.media;
        }
        return *this;
    }
    friend istream &operator>>(istream &in, Student &s)
    {
      Om *o=static_cast<Student*>(&s);
      in>>*o;
      cout<<"CLASA= ";
      in>>s.clasa;
      cout<<"MEDIA= ";
      in>>s.media;
      return in;
    }
    friend ostream &operator<<(ostream &out, const Student &s)
    {
        Student s1(s);
        Om *o=static_cast<Student*>(&s1);
        cout<<*o;
        out<<endl<<"CLASA= "<<s.clasa;
        out<<endl<<"MEDIA= "<<s.media;
        return out;
    }
    virtual void descriere()
    {
        cout<<"Persoană care urmează cursurile unei universități sau ale unui institut de învățământ superior.";
    }
    virtual int get_id()
    {
        return 1;
    }
    bool operator<(const Student &s) const
    {
        if (this->media<s.media)
            return true;
        else
            return false;
    }
    double get_media() const
    {
        return  this->media;
    }


};
class Sef_clasa:public Student
{
    const int id;
    static int contor;
    static int sef_an;
    bool sef;
public:
    Sef_clasa():Student(),id(contor)
    {
        this->sef=false;
    }
    Sef_clasa(string nume, string sex, int varsta, int clasa, double media, bool sef): Student( nume,  sex,  varsta,  clasa,  media),id(contor++)
    {
        this->sef=false;
    }
    Sef_clasa(const Sef_clasa &sef):Student(sef),id(contor++)
    {
        this->sef=sef.sef;
    }
    Sef_clasa &operator=(const Sef_clasa &sef)
    {
        if (this!=&sef)
        {
            Student::operator=(sef);
            this->sef=sef.sef;
        }


        return *this;
    }
    friend istream &operator>>(istream &in, Sef_clasa &sef)
    {
        Student *s=static_cast<Sef_clasa*>(&sef);
        in>>*s;
        cout<<"Studentul "<<sef.nume<<" este presedintele consiliului? (1=DA sau 0=NU) ";
        int ok=-1;
        while (ok==-1)
        {
            try {
            in>>ok;
            if (ok!=1 && ok!=0)

                throw 1;
            if (ok==1 && sef_an==1)
                throw exception();

            }
            catch(int)
            {
                    cout<<"Valoarea introdusa este gresita, incearca din nou (1=DA sau 0=NU) ";
                    ok=-1;

            }
            catch(...)
            {
                cout<<"Nu pot exista 2 presedinti ai consiliului ";
                ok=-1;
            }

        }
        if (ok==1)
        {
            sef_an=1;
            sef.sef=true;
        }
        else
            sef.sef=false;
        return in;

    }
    friend ostream &operator<<(ostream &out, const Sef_clasa &sef)
    {
        out<<"ID_Elev= "<<sef.id;
        Sef_clasa sef2(sef);
        Student *s=static_cast<Sef_clasa*>(&sef2);
        out<<*s;
        if (sef.sef==1)
            out<<endl<<"Studentul "<<sef.nume<<" este presedintele consiliului";
        else
            out<<endl<<"Studentul "<<sef.nume<<" nu este presedintele consiliului";
        out<<endl;
        return out;
    }
    void descriere()
    {
        cout<<"Seful clasei reprezinta liderul elevilor, persoana care are curaj sa apere interesele lor, sa discute in numele clasei cu profesorii sau chiar cu directorul.";
    }
    int get_id()
    {
        return this->id;
    }
    bool operator<(const Sef_clasa &sef) const
    {
        if (this->media<sef.media)
            return true;
        else
            return false;
    }
    bool get_sefie() const
    {
        return this->sef;
    }


};
template <class T, int lungime> class Array
{
    T* my_array;
public:
    Array(T my_array[])
    {
        cout<<"A";
        this->my_array=new T[lungime];
        for (int i=0;i<lungime;i++)
            this->my_array[i]=my_array[i];

    }


    void afisare()
    {
        for (int i=0;i<lungime;i++)
            cout<<my_array[i]<<endl;
    }
    void afisare_by_lower_id(int id)
    {
        for (int i=0;i<lungime;i++)
        {
            Sef_clasa sef;
            T *a=dynamic_cast<Sef_clasa*>(&sef);
            if(a->get_id()<=id)
            cout<<my_array[i];
        }


    }
    float media_varstelor()
    {
        float suma=0;
        for (int i=0;i<lungime;i++)
            suma+=this->my_array[i].get_varsta();
        suma=suma/lungime;
        return suma;
    }

};
class Singletone
{
private:
    static Singletone *object;
    string data;
    set<Om> oameni;
    set<Student> studenti;
    set<Sef_clasa> sefi_clasa;
    Singletone()
    {
        this->data="necunoscut";
        this->oameni.empty();
        this->studenti.empty();
        this->sefi_clasa.empty();


    }
    Singletone (const Singletone &s)
    {

    }
public:
    static Singletone* getInstance()
    {
        if (object==nullptr)
            object=new Singletone;
        return object;
    }
    void getData()
    {
         meniu_p_principal();
         meniu_p_principa_operatii();
    }
    static void meniu_p_principal()
    {
        cout<<"______MENIU SECUNDAR______"<<endl;
        cout<<"Dati valoarea 0 pentru a iesi din acest meniu"<<endl;
        cout<<"Dati valoarea 1 pentru a afisa oamenii"<<endl;
        cout<<"Dati valoarea 2 pentru a afisa studenti"<<endl;
        cout<<"Dati valoarea 3 pentru a afisa sefii de clasa"<<endl;
        cout<<"Dati caloarea 4 pentru a afisa media varstelor a celor mai tineri 2 oameni"<<endl;
        cout<<"Dati caloarea 5 pentru a afisa media varstelor elevilor cu cele mai mici medii"<<endl;
        cout<<"Dati caloarea 6 pentru a afisa media varstelor elevilor cu cele mai mici medii" <<endl;
        cout<<"Dati caloarea 7 pentru a afisa toti studentii cu id-ul mai mic decat un nr x " <<endl;

    }
    void meniu_p_principa_operatii()
    {
        int a=1;
        cout<<"Dati valoarea 10 pentru a revedea meniul in care va aflati";
        while (a!=0)
        {
            cin>>a;
            switch(a)
            {
                case 0:
                {
                    a=0;
                    break;
                }
                case 1:
                {
                    set<Om>::iterator it;
                    cout<<endl<<"Lista oamenilor (sortati in functie de varsta): ";
                    cout<<endl;
                    for (it=oameni.begin();it!=oameni.end();it++)
                        cout<<*it<<endl;
                    break;
                }
                case 2:
                {
                    set<Student>::iterator it;
                    cout<<endl<<"Lista studentilor (sortati in funcie de medie): ";
                    cout<<endl;
                    for (it=studenti.begin();it!=studenti.end();it++)
                        cout<<*it<<endl;
                    break;

                }
                case 3:
                {
                    set<Sef_clasa>::iterator it;
                    cout<<endl<<"Lista sefilor de clasa (sortati in funcie de medie): ";
                    cout<<endl;
                    for (it=sefi_clasa.begin();it!=sefi_clasa.end();it++)
                        cout<<*it<<endl;
                    break;

                }
                case 4:
                {
                Om *oamenii;
                oamenii=new Om[oameni.size()];
                int poz=0;
                set<Om>::iterator it;
                for (it=oameni.begin();it!=oameni.end();it++)
                {
                  oamenii[poz]=*it;
                  poz++;
                }
                if (oameni.size()<2)
                    cout<<endl<<"Nu exista 2 oameni in baza de date ";
                else
                {
                    Array <Om,2> ob(oamenii);
                    cout<<endl<<"Varsta medie a oamenilor este "<<ob.media_varstelor();
                }

                break;

                }
                case 5:
                {
                    Student *studentii;
                    studentii=new Student[studenti.size()];
                    int poz=0;
                    set<Student>::iterator it;
                    for (it=studenti.begin();it!=studenti.end();it++)
                    {
                        studentii[poz]=*it;
                        poz++;
                    }
                    if (studenti.size()<2)
                        cout<<endl<<"Nu exista 2 studenti in baza de date ";
                    else
                    {
                        Array <Om,2> ob(studentii);
                        cout<<endl<<"Varsta medie a oamenilor este "<<ob.media_varstelor();
                    }

                    break;
                }
                case 6:
                {
                    Sef_clasa *sefii;
                    sefii=new Sef_clasa[sefi_clasa.size()];
                    int poz=0;
                    set<Sef_clasa>::iterator it;
                    for (it=sefi_clasa.begin();it!=sefi_clasa.end();it++)
                    {
                        sefii[poz]=*it;
                        poz++;
                    }
                    if (sefi_clasa.size()<2)
                        cout<<endl<<"Nu exista 2 oameni in baza de date ";
                    else
                    {
                        Array <Om,2> ob(sefii);
                        cout<<endl<<"Varsta medie a oamenilor este "<<ob.media_varstelor();
                    }

                    break;
                }
                case 7:
                {
                    int x;
                    cout<<endl<<"X= ";
                    cin>>x;
                    Student *studentii;
                    studentii=new Student[studenti.size()];
                    int poz=0;
                    set<Student>::iterator it;
                    for (it=studenti.begin();it!=studenti.end();it++)
                    {
                        studentii[poz]=*it;
                        poz++;
                    }
                    if (studenti.size()<2)
                        cout<<endl<<"Nu exista 2 studenti in baza de date ";
                    else
                    {
                        Array <Om,2> ob(studentii);
                        cout<<endl;
                        ob.afisare_by_lower_id(x);
                    }

                    break;
                }
                case 10:
                {
                    meniu_p_principal();
                    break;
                }
                default:
                {
                    cout<<"Valoarea introdusa este incorecta ";
                }

            }

        }
    }

    void setData()
    {
        if (object!=nullptr)
        {
            meniu_principal();
            meniu_principal_operatii();
        }


    }
    static void meniu_sefi_clasa()
    {
        cout<<"______MENIU SEFI CLASA______"<<endl;
        cout<<"Dati valoarea 0 pentru a iesi din acest meniu"<<endl;
        cout<<"Dati valoarea 1 pentru a adauga un sef de clasa"<<endl;
        cout<<"Dati valoarea 2 pentru a sterge toti sefii de clasa, mai putin seful de an"<<endl;

    }
    void operatii_sefi_clasa()
    {
        int a=1;
        while (a!=0)
        {
            cout<<"Dati valoarea 10 pentru a revedea meniul in care va aflati"<<endl;
            cin>>a;
            switch(a)
            {
                case 0:
                {
                    a=0;
                    break;
                }
                case 1:
                {
                    Sef_clasa sef;
                    cin>>sef;
                    sefi_clasa.insert(sef);
                    break;
                }
                case 2:
                {
                    set<Sef_clasa>::iterator it;
                    for (it=sefi_clasa.begin();it!=sefi_clasa.end();it++)
                    {
                        if (!it->get_sefie())
                        {
                            sefi_clasa.erase(it);
                            if (!sefi_clasa.empty())
                                it=sefi_clasa.begin();
                            else
                                break;
                        }
                    }
                    break;
                }
                case 10:
                {
                    meniu_sefi_clasa();
                    break;
                }

                default:
                {
                    cout<<"Valoarea introdusa este incorecta "<<endl;
                }

            }

        }
    }
    static void meniu_studenti()
    {
        cout<<"______MENIU STUDENTI______"<<endl;
        cout<<"Dati valoarea 0 pentru a iesi din acest meniu"<<endl;
        cout<<"Dati valoarea 1 pentru a adauga un student"<<endl;
        cout<<"Dati valoarea 2 pentru a sterge toti studentii care nu au media peste 5"<<endl;

    }
    void operatii_studenti()
    {
        int a=1;
        while (a!=0)
        {
            cout<<"Dati valoarea 10 pentru a revedea meniul in care va aflati"<<endl;
            cin>>a;
            switch(a)
            {
                case 0:
                {
                    a=0;
                    break;
                }
                case 1:
                {
                    Student s;
                    cin>>s;
                    studenti.insert(s);
                    break;
                }
                case 2:
                {
                    set<Student>::iterator it;
                    for (it=studenti.begin();it!=studenti.end();it++)
                    {
                        if (it->get_media()<5)
                        {
                            studenti.erase(it);
                            if (!studenti.empty())
                                it=studenti.begin();
                            else
                                break;
                        }
                    }
                    break;
                }
                case 10:
                {
                    meniu_studenti();
                    break;
                }

                default:
                {
                    cout<<"Valoarea introdusa este incorecta "<<endl;
                }

            }

        }
    }
    static void meniu_principal()
    {
        cout<<"______MENIU SECUNDAR______"<<endl;
        cout<<"Dati valoarea 0 pentru a iesi din acest meniu"<<endl;
        cout<<"Dati valoarea 1 pentru a intra in meniul oameni"<<endl;
        cout<<"Dati valoarea 2 pentru a intra in meniul studenti"<<endl;
        cout<<"Dati valoarea 3 pentru a intra in meniul sefi de clasa"<<endl;

    }
    static void meniu_oameni()
    {
        cout<<"______MENIU OAMENI______"<<endl;
        cout<<"Dati valoarea 0 pentru a iesi din acest meniu"<<endl;
        cout<<"Dati valoarea 1 pentru a adauga un om"<<endl;
        cout<<"Dati valoarea 2 pentru a sterge toti oamenii mai mari decat o varsta x"<<endl;


    }

    void meniu_oameni_operatii()
    {

        int a=1;
        while (a!=0)
        {
            cout<<"Dati valoarea 10 pentru a revedea meniul in care va aflati"<<endl;
            cin>>a;
            switch(a)
            {
                case 0:
                {
                    a=0;
                    break;
                }
                case 1:
                {
                    Om o;
                    cin>>o;
                    oameni.insert(o);
                    break;
                }
                case 2:
                {
                    int x;
                    cout<<endl<<"Intorduceti varsta= ";
                    cin>>x;
                    set<Om>::iterator it;
                    for (it=oameni.begin();it!=oameni.end();it++)
                    {
                        if (it->get_varsta()>x)
                        {
                            oameni.erase(it);
                            if (!oameni.empty())
                                it=oameni.begin();
                            else
                                break;
                        }
                    }




                    break;
                }
                case 10:
                {
                    meniu_oameni();
                    break;
                }

                default:
                {
                    cout<<"Valoarea introdusa este incorecta "<<endl;
                }

            }

        }
    }
     void meniu_principal_operatii()
    {
        int a=1;
        while (a!=0)
        {
            cout<<"Dati valoarea 10 pentru a revedea meniul in care va aflati"<<endl;
            cin>>a;
            switch(a)
            {
                case 0:
                {
                    a=0;
                    break;
                }
                case 1:
                {
                   meniu_oameni();
                   this->meniu_oameni_operatii();
                   break;
                }
                case 2:
                {
                    meniu_studenti();
                    this->operatii_studenti();
                    break;
                }
                case 3:
                {
                    meniu_sefi_clasa();
                    this->operatii_sefi_clasa();
                    break;
                }
                case 10:
                {
                    meniu_principal();
                    break;
                }

                default:
                {
                    cout<<"Valoarea introdusa este incorecta "<<endl;
                }

            }

        }
    }


};
Singletone *Singletone::object=nullptr;
int Sef_clasa::contor=0;
int Sef_clasa::sef_an=0;
int main() {
    list <Om*> fiinte;
    Om *o=new Om;
    Student *st=new Student;
    Sef_clasa *sef=new Sef_clasa;
    fiinte.push_back(new Om(*o));
    fiinte.push_back(new Student(*st));
    fiinte.push_back(new Sef_clasa(*sef));
    Singletone *s=s->getInstance();
    int a=1;
    while (a!=0)
    {
        cout<<"______MENIU PRINCIPAL______"<<endl;
        cout<<"Dati valoarea 0 pentru a inchide programul"<<endl;
        cout<<"Dati valoarea 1 pentru a modifica datele din memorie"<<endl;
        cout<<"Dati valoarea 2 pentru a afisa datele din memorie "<<endl;
        cout<<"Dati valoarea 3 pentru a afisa diferenta intre cele 3 categorii "<<endl;
        cout<<"Dati valoarea 4 pentru a elimina o sub-categorie"<<endl;

        cin>>a;
        switch (a)
        {
            case 0:
            {
                a=0;
                break;
            }
            case 1:
            {
                s->setData();
                break;
            }
            case 2:
            {
                s->getData();
                break;

            }
            case 3:
            {
                list<Om*>::iterator it;
                for (it=fiinte.begin();it!=fiinte.end();it++)
                {
                    (**it).descriere();
                    cout<<endl;
                }


                break;
            }
            case 4:
            {
                list<Om*>::iterator it;
                it=prev(fiinte.end());
                fiinte.erase(it);
                break;
            }

            default:
                cout<<"Valoare incorecta "<<endl;

        }



    }





    return 0;
}