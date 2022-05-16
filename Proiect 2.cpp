#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cstring>
using namespace std;
class Interface
{
public:
    virtual istream &citire (istream &in)=0;
    virtual ostream &afisare(ostream &out) const =0;
};
class Actor
{
    string nume;
    unsigned int varsta;
    bool engleza;
    int nr_filme;
public:
    Actor();
    Actor(string nume, unsigned int varsta, bool engleza, int nr_filme );
    Actor(const Actor &a);
    ~Actor();
    string  get_nume();
    unsigned int get_varsta();
    friend istream &operator>>(istream &in, Actor &a);
    friend ostream &operator<<(ostream &out, const Actor &a);
    Actor &operator=(const Actor &a);
    int calculeaza_pret();
};
Actor::~Actor()
{}
string Actor::get_nume()
{
    return this->nume;
}
unsigned int Actor::get_varsta()
{
    return this->varsta;
}
int Actor::calculeaza_pret()
{
    int pret;
    if (this->varsta<25)
        pret=10;
    else if (this->varsta<50)
        pret=20;
    else
        pret=30;
    if (this->engleza)
        pret+=50;
    pret+=10*this->nr_filme;
    return pret;
}
Actor::Actor()
{
    this->nume="-";
    this->varsta=0;
    this->engleza=false;
    this->nr_filme=0;
}
Actor::Actor(string nume, unsigned int varsta, bool engleza, int nr_filme)
{
    this->nume=nume;
    this->varsta=varsta;
    this->engleza=engleza;
    this->nr_filme=nr_filme;
}
Actor::Actor(const Actor &a)
{
    this->nume=a.nume;
    this->varsta=a.varsta;
    this->engleza=a.engleza;
    this->nr_filme=a.nr_filme;
}
istream &operator>>(istream &in, Actor &a)
{
    cout<<"Nume actor= ";
    getline(in,a.nume);
    getline(in,a.nume);
    cout<<"Varsta actor= ";
    in>>a.varsta;
    int nr,ok=0;
    cout<<"Dati valoarea 1 daca actorul vorbeste engleza/ 0 in caz contrar";
    do
    {
        in>>nr;
        if (nr!=0 && nr!=1)
            cout<<"Valoarea introdusa este incorecta, incercati din nou";
        else
            ok=1;

    }while (ok==0);
    if (nr==1)
        a.engleza=true;
    else
        a.engleza=false;
    cout<<"In cate filme a mai jucat? ";
    in>>a.nr_filme;
    return in;
}
ostream &operator<<(ostream &out, const Actor &a)
{
    out<<"---------NEW ACTOR----------";
    out<<endl<<"NUME ACTOR= "<<a.nume;
    out<<endl<<"VARSTA ACTOR= "<<a.varsta;
    if (a.engleza)
        out<<endl<<"Actorul este vorbitor de limba engleza";
    else
        out<<endl<<"Actorul nu este vorbitor de limba engleza";
    out<<endl<<"NUMAR FILME IN CARE A MAI JUCAT= "<<a.nr_filme;
    return out;
}
Actor &Actor::operator=(const Actor &a)
{
    if (this!=&a)
    {
        this->nume=a.nume;
        this->varsta=a.varsta;
        this->engleza=a.engleza;
        this->nr_filme=a.nr_filme;
    }
    return *this;
}
list <Actor> actori;
class Film:public Interface
{
protected:
    string nume;
    float durata;
    string *distributie;
    int numar;
public:
    Film();
    Film(string nume,float durata, string distributie[], int numar);
    Film(const Film &f);
    string get_nume();
    int get_numar();
    virtual int cost_distributie()=0;
    float get_durata();
    int varsta_distributie();
    friend istream &operator>>(istream &in , Film &f)
    {
        return f.citire(in);
    }
    friend ostream &operator<<(ostream &out, const Film &f)
    {
        return f.afisare(out);
    }
    ~Film();
    Film &operator=(const Film &f);
    virtual istream &citire( istream &in)
    {
        cout<<"Nume film= ";
        std::getline(in, this->nume);
        std::getline(in, this->nume);
        cout<<"Durata (ore. minute)= ";
        in>>this->durata;
        cout<<"Numar actori din distributie= ";
        in>>this->numar;
        if (this->distributie!=nullptr)
            delete [] this->distributie;
        this->distributie= new string [this->numar+1];
        if (this->numar!=0) {
            std::getline(in, this->distributie[0]);
            cout << "Introduceti actorii, separati prin enter: ";
            for (int i = 0; i < this->numar; i++) {
                std::getline(in, this->distributie[i]);

            }
        }
        else
            this->distributie=new string [1];



        return in;
    }
    virtual ostream &afisare (ostream &out) const
    {
        out<<"Nume film= "<<this->nume<<endl;
        out<<"Durata film= "<<int (this->durata)<<" ore si "<<(this->durata-int(this->durata))*100<<" minute"<<endl;
        if (this->numar!=0)
        {
            out<<"Distributie= ";
            for (int i=0;i<this->numar;i++)
                if (i!=this->numar-1)
                    out<<this->distributie[i]<<" ,";
                else
                    out<<this->distributie[i];
        }
        else
            out<<"Filmul nu are actori in distributie";


        return out;
    }
    void afisare();
};
float Film::get_durata()
{
    return this->durata;
}
int Film::varsta_distributie()
{
    int varsta_totala=0;
    list<Actor>::iterator it;
    for (int i=0;i<this->numar;i++)
        for (it=actori.begin();it!=actori.end();it++)
            if (distributie[i]==it->get_nume())
                varsta_totala+=it->get_varsta();
    return varsta_totala;
}
string Film::get_nume()
{
    return this->nume;
}
int Film::get_numar()
{
    return this->numar;
}

void Film::afisare()
{
    cout<<"Nume film= "<<this->nume;
    cout<<endl<<"Durata film= "<<int (this->durata)<<" ore si "<<(this->durata-int(this->durata))*100<<" minute";
    cout<<"Distributie= ";
    for (int i=0;i<this->numar;i++)
        if (i!=this->numar-1)
            cout<<this->distributie[i]<<" ,";
        else
            cout<<this->distributie[i];
    cout<<endl;

}
Film::~Film()
{
    if (this->distributie!=nullptr)
        delete [] this->distributie;
}
Film::Film()
{
    this->nume="";
    this->durata=0;
    this->numar=0;
    distributie= new string[0];
}
Film::Film(string nume,float durata, string distributie[], int numar)
{
    if (this->distributie!=nullptr)
        delete [] this->distributie;
    this->numar=numar;
    distributie= new string [this->numar];
    for (int i=0;i<numar;i++)
        this->distributie[i]=distributie[i];
    this->nume=nume;
    this->durata=durata;

}
Film::Film(const Film &f)
{
    if (this->distributie!=nullptr)
        delete [] this->distributie;
    this->numar=f.numar;
    distributie= new string [this->numar];
    for (int i=0;i<numar;i++)
        this->distributie[i]=f.distributie[i];
    this->nume=f.nume;
    this->durata=f.durata;
}
Film &Film::operator=(const Film &f)
{
    if (this!=&f)
    {
        if (this->distributie!=nullptr)
            delete [] this->distributie;
        this->numar=f.numar;
        distributie= new string [this->numar];
        for (int i=0;i<numar;i++)
            this->distributie[i]=f.distributie[i];
        this->nume=f.nume;
        this->durata=f.durata;
    }
    return *this;
}
vector<Film*> filme;
class Film_romantic:virtual public Film
{
protected:
    float imdb;
public:
    Film_romantic();
    Film_romantic(string nume,float durata, string distributie[], int numar, float imdb);
    Film_romantic(const Film_romantic &f);
    ~Film_romantic();
    int cost_distributie()
    {
        int cost=0;
        list<Actor>::iterator it;
        for(int i=0;i<this->numar;i++)
            for (it=actori.begin();it!=actori.end();it++)
                if (this->distributie[i]==it->get_nume())
                {
                    cost+=it->calculeaza_pret();
                    break;
                }
        return cost;
    }

    Film_romantic &operator=(const Film_romantic &f);
    virtual istream &citire(istream &in)
    {
        Film::citire(in);

        cout<<"Nota de pe imdb ( de la 1 la 10, cu 2 zecimale)= ";
        float nota;
        do {
            in>>nota;
            if (nota<0 || nota >10)
                cout<<"Valoarea introdusa este incorecta, incercati din nou: ";
        }while (nota<0 || nota >10);
        this->imdb=nota;
        return in;
    }
    virtual ostream &afisare (ostream &out) const
    {
        Film::afisare(out);
        out<<endl<<"NOTA IMDB= "<<this->imdb<<endl;
        return out;
    }
};

Film_romantic::Film_romantic():Film()
{
    this->imdb=0;
}
Film_romantic::Film_romantic(string nume, float durata, string distributie[], int numar, float imdb) :Film( nume, durata,  distributie, numar)
{
    this->imdb=imdb;
}
Film_romantic::Film_romantic(const Film_romantic &f):Film(f)
{
    this->imdb=f.imdb;
}
Film_romantic::~Film_romantic()
{

}
Film_romantic &Film_romantic::operator=(const Film_romantic &f)
{
    if (this!=&f)
{
        Film::operator=(f);
        this->imdb=f.imdb;
}
    return *this;
}
class Film_comedie:virtual public Film
{
protected:
    int an_aparitie;
public:
    Film_comedie();
    Film_comedie(string nume,float durata, string distributie[], int numar, int an_aparitie);
    Film_comedie(const Film_comedie &f);
    ~Film_comedie();
    Film_comedie &operator=(const Film_comedie &f);
    int cost_distributie()
    {
        int cost=0;
        list<Actor>::iterator it;
        for(int i=0;i<this->numar;i++)
            for (it=actori.begin();it!=actori.end();it++)
                if (this->distributie[i]==it->get_nume())
                {
                    cost+=it->calculeaza_pret();
                    break;
                }
        return cost;
    }
    virtual istream &citire(istream &in)
    {
        Film::citire(in);

        cout<<"Anul aparitiei= ";
        in>> this->an_aparitie;

        return in;
    }
    virtual ostream &afisare (ostream &out) const
    {
        Film::afisare(out);
        out<<endl<<"AN APARITIE= "<<this->an_aparitie<<endl;
        return out;
    }
};
Film_comedie::Film_comedie():Film()
{
    this->an_aparitie=0;
}
Film_comedie::Film_comedie(string nume, float durata, string distributie[], int numar, int an_aparitie) :Film( nume, durata,  distributie, numar)
{
    this->an_aparitie=an_aparitie;
}
Film_comedie::Film_comedie(const Film_comedie &f):Film(f)
{
    this->an_aparitie=f.an_aparitie;
}
Film_comedie::~Film_comedie()
{

}
Film_comedie &Film_comedie::operator=(const Film_comedie &f)
{
    if (this!=&f)
    {
        Film::operator=(f);
        this->an_aparitie=f.an_aparitie;
    }
    return *this;
}
class Film_romcom:public Film_romantic, public Film_comedie {
    float procent[2];
public:
    int cost_distributie()
    {
        int cost=0;
        list<Actor>::iterator it;
        for(int i=0;i<this->numar;i++)
            for (it=actori.begin();it!=actori.end();it++)
                if (this->distributie[i]==it->get_nume())
                {
                    cost+=it->calculeaza_pret();
                    break;
                }
        return cost;
    }
    Film_romcom() : Film_romantic(), Film_comedie(), Film() {
        this->procent[0] = 50;
        this->procent[1] = 50;
    }

    Film_romcom(string nume, float durata, string distributie[], int numar, float imdb, int an_aparitie,
                float procent[]) : Film(nume, durata, distributie, numar),
                                   Film_romantic(nume, durata, distributie, numar, imdb),
                                   Film_comedie(nume, durata, distributie, numar, an_aparitie) {
        this->procent[0] = procent[0];
        this->procent[1] = procent[1];
    }

    Film_romcom(const Film_romcom &f) : Film(f), Film_romantic(f), Film_comedie(f) {
        this->procent[0] = f.procent[0];
        this->procent[1] = f.procent[1];
    }

    virtual istream &citire(istream &in) {
        Film_romantic::citire(in);
        cout << "AN APARITIE= ";
        in >> this->an_aparitie;
        float p1, p2;
        do {
            cout << "Introduceti cat % filmul este romantic ";
            in>>p1;
            cout<<"introduceti cat % filmul este comic ";
            in>>p2;
            if (p1+p2!=100)
                cout<<"Suma procentelor trebuie sa fie 100, nu "<<p1+p2<<"... (mai incearca)"<<endl;

        }while (p1+p2!=100);
        this->procent[0]=p1;
        this->procent[1]=p2;
        return in;

    }
    virtual ostream &afisare(ostream &out) const
    {

    Film_romantic::afisare(out);
    out<<"AN APARITIE= "<<this->an_aparitie;
    out<<endl<<"Filmul este: "<<this->procent[0]<<"% romantic si "<<this->procent[1]<<"% comedie.";
    return out;
    }
    Film_romcom &operator=(const Film_romcom &f)
    {
        if (this!=&f)
        {
            Film_romantic::operator=(f);
            this->an_aparitie=f.an_aparitie;
            this->procent[0]=f.procent[0];
            this->procent[1]=f.procent[1];
        }
        return *this;
    }

};

void meniu_principal()
{
    cout<<"------------MENIU PRINCIPAL-------------";
    cout<<endl<<"Dati valoarea 0 pentru a inchide programul";
    cout<<endl<<"Dati valoarea 1 pentru -> Meniul Actori ";
    cout<<endl<<"Dati valoarea 2 pentru -> Meniul Filme ";
}
void meniu_actori()
{
    cout<<"------------MENIU ACTORI-------------";
    cout<<endl<<"Dati valoarea 0 pentru a iesi din acest meniu ";
    cout<<endl<<"Dati valoarea 1 pentru a adauga un actor";
    cout<<endl<<"Dati valoarea 2 pentru a afisa lista actorilor";
    cout<<endl<<"Dati valoarea 3 pentru a afisa pretul estimativ al actorilor";
    cout<<endl<<"Dati valoarea 4 pentru a sterge un actor din lista ( in functie de numele sau) ";


}
void meniu_filme()
{
    cout<<"------------MENIU FILME-------------";
    cout<<endl<<"Dati valoarea 0 pentru a iesi din acest meniu ";
    cout<<endl<<"Dati valoarea 1 pentru a adauga un film romantic";
    cout<<endl<<"Dati valoarea 2 pentru a adauga un film comic";
    cout<<endl<<"Dati valoarea 3 pentru a adauga un film romcom";
    cout<<endl<<"Dati valoarea 4 pentru a afisa filmele ";
    cout<<endl<<"Dati valoarea 5 pentru a afisa costurile distributiilor filmelor  ";
    cout<<endl<<"Dati valoarea 6 pentru a sterge filmele care dureaza mai mult de un timp x";
    cout<<endl<<"Dati valoarea 7 pentru a afisa varstele distributiilor ";

}
void operatii_filme()
{
    int a=1;
    while (a!=0)
    {
        cout<<endl<<"Dati valoarea 10 pentru a revedea meniul in care va aflati";
        cin>>a;
        switch(a)
        {
            case 0:
                break;
            case 1:
            {
                Film_romantic *f=new Film_romantic();
                cin>>*f;
                filme.push_back(new Film_romantic(*f));
                break;
            }
            case 2:
            {
                Film_comedie *f=new Film_comedie();
                cin>>*f;
                filme.push_back(new Film_comedie(*f));
                break;
            }
            case 3:
            {
                Film_romcom *f=new Film_romcom();
                cin>>*f;
                filme.push_back(new Film_romcom(*f));
                break;
            }
            case 4:
            {
                for (int i=0;i<filme.size();i++)
                {
                    cout<<"FILMUL "<<i+1<<endl;
                    cout<<*filme[i]<<endl;
                }

                break;
            }
            case 5:
            {
                for (int i=0;i<filme.size();i++)
                {
                        if (filme[i]->get_numar()==0)
                            cout<<endl<<"Filmul "<<filme[i]->get_nume()<<" nu are actori, deci costul distributiei este 0";
                        else

                        if (filme[i]->cost_distributie()==0)
                            cout<<endl<<"Actorii filmului "<<filme[i]->get_nume()<<" nu au fost adaugati -> costul este 0";
                        else
                            cout<<endl<<"Costul distributiei filmului "<<filme[i]->get_nume()<<" este "<<filme[i]->cost_distributie()<<"k dolari";

                }
                break;

            }
            case 6:
            {
                float x;
                cout<<"DATI TIMPUL MAXIM PE CARE VRETI SA IL PETRECETI PRIVIND UN FILM (ore. minute)= ";
                cin>>x;
                for (int i=0;i<filme.size();i++)
                    if (filme[i]->get_durata()>x)
                    {
                        filme.erase(filme.begin()+i);
                        i--;
                    }
                break;

            }
            case 7:
            {
                for (int i=0;i<filme.size();i++)
                {
                    if (filme[i]->get_numar()==0)
                        cout<<endl<<"Filmul "<<filme[i]->get_nume()<<" nu are actori";
                    else if (filme[i]->varsta_distributie()==0)
                        cout<<endl<<"Filmul "<<filme[i]->get_nume()<<" nu are actorii introdusi in baza de date";
                        else
                            cout<<endl<<"Varsta totala a distributiei filmului "<<filme[i]->get_nume()<<" este "<<filme[i]->varsta_distributie();

                }
                break;
            }

            case 10:
            {
                meniu_filme();
                break;
            }
            default:
                cout<<"Valoarea introdusa este incorecta, incercati din nou :(";

        }


    }
}

void operatii_actori()
{
    int a=1;

    while (a!=0)
    {
        cout<<endl<<"Dati valoarea 10 pentru a revedea meniul in care va aflati";
        cin>>a;
        switch (a)
        {
            case 0:
                break;
            case 1:
            {
                Actor act;
                cin>>act;
                actori.push_back(act);
                break;
            }
            case 2:
            {
                list<Actor>::iterator it;
                for (it=actori.begin(); it!=actori.end();it++)
                    cout<<*it<<endl;
                break;
            }
            case 3:
            {
                list <Actor>::iterator it;
                for (it=actori.begin(); it!=actori.end();it++)
                    cout<<endl<<"Pretul estimativ al actorului "<<it->get_nume()<<" este "<<it->calculeaza_pret()<<"k dolari";
                break;
            }
            case 4: {
                string nume;
                cout<<"NUME ACTOR= ";
                getline(cin, nume);
                getline(cin, nume);
                list<Actor>::iterator it;
                int ok = 0;
                for (it = actori.begin(); it != actori.end(); it++)
                    if (it->get_nume() == nume) {
                        ok = 1;
                        cout << "!!!!!Actorul " << it->get_nume() << " a fost sters cu succes!!!!!!";
                        actori.erase(it);
                        break;
                    }
                if (ok == 0)
                    cout << "Actorul " << nume << " nu exista";
                break;
            }


            case 10:
            {
                meniu_actori();
                break;
            }
            default:
                cout<<"Valoarea introdusa este incorecta, incercati din nou :( ";



        }

    }

}
int main()
{
    int a;
    cout<<"Bine ati venit, introduceti orice cifra urmata de enter pentru a incepe";
    cin>>a;
    a=1;


    while (a!=0)
    {
        meniu_principal();
        cin>>a;
        switch(a)
        {
            case 0:
                break;
            case 1:
            {
                meniu_actori();
                operatii_actori();
                break;
            }
            case 2:
            {
                meniu_filme();
                operatii_filme();
                break;
            }

            case 10:
            {
                meniu_principal();
                break;
            }

            default:
                cout<<"Valoarea introdusa este incorecta, incercati din nou :( ";
        }
    }
    cout<<endl<<"O zi frumoasa :) ";

    return 0;
}
