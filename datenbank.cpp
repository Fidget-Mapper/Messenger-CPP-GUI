#include <iostream>
#include "datenbank.h"

datenbank::datenbank()
{
}

/*void datenbank::setConn(MYSQL* setConnConn, const char* setConnDbname, const char* setConnNutzername, const char* setConnPasswort, const char* setConnName)
{
    //conn = mysql_real_connect(setConnConn, setConnDbname, setConnNutzername, setConnPasswort, setConnName, 0, NULL, 0)
    conn = mysql_real_connect(setConnConn, setConnDbname, setConnNutzername, setConnPasswort, setConnName, 0, NULL, 0);
}
*/
MYSQL* datenbank::getConn()
{
return conn;
}
void datenbank::setConn(MYSQL* conn)
{
    this->conn = conn;
}
bool datenbank::einloggen(std::string nutzername, std::string passwort, int nutzeridAbsender)
{
    std::string query = "SELECT * FROM nutzer WHERE nutzer.Name = '"+nutzername+"' AND Passwort = '"+passwort+"'";
    const char* q = query.c_str();
    int qstate = mysql_query(getConn(), q);
    if(!qstate)
        {
            res = mysql_store_result(getConn());
            while(row = mysql_fetch_row(res))
                {
                    if(row)
                    {
                        this->nutzername = row[0];
                        this->passwort = row[1];
                        this->nutzeridAbsender = std::stoi(row[2]);
                      /*  this->nutzeridAbsender = nutzeridAbsender;
                        std::cout<<nutzeridAbsender;
                        */istEingeloggt = true;
                        return true;
                    }
                }
        }
        return false;
}
/*bool datenbank::registrieren(std::string nutzername, std::string passwort)
{
    std::string query = "INSERT INTO nutzer(Name, Passwort)VALUES('"+nutzername+"', '"+passwort+"');";
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);
    if(!qstate)
    {
        res = mysql_store_result(conn);

        while(row = mysql_fetch_row(res))
        {
            std::cout<<row[0];
        }
    }

    return true;
}*/

bool datenbank::registrieren(std::string nutzername, std::string passwort)
{

    //eingabe der nutzerdaten sowie bildschirminhalt loeschung
    std::string name = nutzername;

    //sql statement zur registrierung
    std::string query = "insert into nutzer(Name, Passwort) values('"+name+"', '"+passwort+"')";

    //sql statement zur doppeleintragspruefung
    std::string pruefeDoppeltenLogin = "SELECT Name FROM nutzer WHERE Name = '"+name+"'";
    const char* q = pruefeDoppeltenLogin.c_str();

    //hier weitermachen. pruefung, ob nutzer bereits existiert
    int qstate = mysql_query(conn, q);
    int doppenPruefZahl = 0;
    if(!qstate)
    {

            res = mysql_store_result(conn);

            //solange bis eof
            while(row = mysql_fetch_row(res))
            {

                //ist registrierender nutzer bereits vorhanden?
                if(row[0] == name)
                {
                    //wenn ja, gib hinweis aus
                    std::cout<<"benutzer existiert bereits. ";

                    //erhoehe zaehler damit registrierung nicht stattfindet
                    return false;
                }
            }

            //wenn der zaehler nicht erhoeht wurde
            if(doppenPruefZahl == 0)
            {
                const char* q2 = query.c_str();
                int qstate2 = mysql_query(conn, q2);
                if(!qstate)
                {
                    res = mysql_store_result(conn);
                }
                std::cout<<"erfolgreich registriert!";
                return true;
            }

    }
    //zaehler zuruecksetzen
    doppenPruefZahl = 0;
    return true;
}
bool datenbank::vectorFuellenNutzerSuche()
{
    std::string query = "SELECT * FROM nutzer";
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);
    if(!qstate)
        {
            res = mysql_store_result(getConn());
            while(row = mysql_fetch_row(res))
                {
                    if(row)
                    {
                        platzhalter.push_back("Nutzer: ");
                        platzhalter.push_back(row[0]);
                        platzhalter.push_back("\r\n\r");
                        platzhalter.push_back("ID: ");
                        platzhalter.push_back(row[2]);
                        platzhalter.push_back("\r\n\r");
                    }
                }
        }
       /* for(int i = 0; i<platzhalter.size();i++)
        {
            std::cout<<platzhalter[i]<<std::endl;
        }*/
    return true;
}
std::string datenbank::vectorAusgabeStringFunktion()
{
    std::string vectorAusgabeString;
    for(int i = 0; i < platzhalter.size(); i++)
    {
        vectorAusgabeString = vectorAusgabeString+platzhalter[i];
    }
    return vectorAusgabeString;
}
bool datenbank::nachrichtSenden (int nutzerID, std::string nachricht)
{
    time_t timet = std::time(nullptr);
    std::string nutzerIDString, nutzeridAbsenderString, timee;
    nutzeridAbsenderString      = std::to_string(nutzerID);
    nutzerIDString              = std::to_string(nutzeridAbsender);
    timee                        = std::to_string(timet);
    //std::cout<<std::endl<<"nutzerdaten:: "<<std::endl<<nutzeridAbsenderString<<std::endl<<nutzerIDString<<std::endl<<time<<std::endl<<nachricht<<std::endl;
//    std::string query           = "INSERT INTO empfangenenachricht(AbsenderID, EmpfaengerID, Zeit, Nachricht) VALUES('"++"','"++"','"++"','"++"')";
    std::string query           = "insert into empfangenenachricht(AbsenderID, EmpfaengerID, Nachricht, Zeit) values('"+nutzeridAbsenderString+"','"+nutzerIDString+"','"+nachricht+"','"+timee+"')";
    const char* q = query.c_str();

    int qstate;
    qstate = mysql_query(conn, q);
    std::cout<<qstate;
    return true;
}
bool datenbank::vectorFuellenNachrichten()
{
    std::string query           = "select empfangenenachricht.Nachricht, empfangenenachricht.AbsenderID, empfangenenachricht.Zeit, nutzer.Name from empfangenenachricht left join nutzer on empfangenenachricht.AbsenderID = nutzer.NutzerID where empfangenenachricht.EmpfaengerID = '"+std::to_string(nutzeridAbsender)+"'";
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);
    std::cout<<query;
    if(!qstate)
        {
            res = mysql_store_result(getConn());
            while(row = mysql_fetch_row(res))
                {
                    if(row)
                    {
                        platzhalter.push_back("Von: ");
                        if(row[3])
                        {
                            platzhalter.push_back(row[3]);
                        }else
                        {
                            platzhalter.push_back("unbekannt");
                        }
                        platzhalter.push_back(" um: ");
                        platzhalter.push_back(row[2]);
                        platzhalter.push_back("\r\n\r");
                        platzhalter.push_back(row[0]);
                        platzhalter.push_back("\r\n\r");
                        platzhalter.push_back("\r\n\r");
                    }
                }
        }
    return true;
}
int datenbank::getNutzerSucheVectorSize()
{
    return platzhalter.size();
}
bool datenbank::getIstEingeloggt()
{
    return istEingeloggt;
}
int datenbank::getAbsenderID()
{
    return nutzeridAbsender;
}
void datenbank::platzhalterLeeren()
{
    platzhalter.clear();
}
/*std::string datenbank::abfrage()
{
    const char* query = "SELECT * FROM EmpfangeneNachricht ";
    int qstate = mysql_query(conn, query);
    std::string rueckgabe;
    size_t n = sizeof(row = mysql_fetch_row(res));
    std::cout<<n;
    if(!qstate)
    {
        res = mysql_store_result(conn);
        int i = 0;
        while(row = mysql_fetch_row(res))
            {
                if(i < n)
                    {
                        std::cout<<std::string(row[i])<<" ";
                        rueckgabe = std::string(row[1]);
                        i++;
                    }
            }
    }

    return rueckgabe;
}
*/
