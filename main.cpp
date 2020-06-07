#include <iostream>
#include <string>
#include "main.h"
#include "datenbank.h"
char textSaved[20];
int nutzeridAbsender;
std::string text = "ello", nutzernameString, passwortString;
std::stringstream ss;
char* nutzernameChar;
char* passwortChar;
const char g_szClassName[] = "myWindowClass";
const char* host = "localhost";
const char* nutzernameDatenbank = "root";
const char* passwortDatenbank = "";
const char* tabelle = "nutzerdaten";
const char* unix_socket = "NULL";

unsigned int port = 0;
unsigned long flags = 0;
datenbank datei;
HWND textfield, buttonEinloggen, buttonRegistrieren, buttonSuchen, buttonSenden, buttonNachrichtenAusgabe, textFeldNutzerId, textFeldNachricht,  TextBoxName, TextBoxPasswort, TextBoxText, TextBoxTextScrollbar;
// nachrichten handler
char* eingabe(HWND eingabeTextBox)
{
    //hier werden irgendwann werte vom gui an variablen uebergeben
    const int size = 255;
    TCHAR buffer[size] = {0};
    GetWindowText(eingabeTextBox, buffer, size);
    char* wert = buffer;
    return wert;
}
void ausgabe(std::string ausgabeVariable){
    SetWindowText(TextBoxText, TEXT(ausgabeVariable.c_str()));
    datei.platzhalterLeeren();
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch(msg)                 //behandel die nachricht
    {
        case WM_CREATE:
            TextBoxName = CreateWindow("EDIT",
                                   "Max",
                                   WS_BORDER | WS_CHILD | WS_VISIBLE,
                                   20, 20, 60, 20,
                                   hwnd,
                                   NULL,
                                   NULL,
                                   NULL
                                   );
            TextBoxPasswort = CreateWindow("EDIT",
                                   "Lernen2",
                                   WS_BORDER | WS_CHILD | WS_VISIBLE,
                                   20, 40, 60, 20,
                                   hwnd,
                                   NULL,
                                   NULL,
                                   NULL
                                   );
            buttonEinloggen = CreateWindow("BUTTON",
                                  "Einloggen!",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  //links, top, breite, hoehe
                                  80, 20, 70, 20,
                                  hwnd,
                                  (HMENU) 1,
                                  NULL,
                                  NULL
                                  );
            buttonRegistrieren = CreateWindow("BUTTON",
                                  "Registrieren!",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  //links, top, breite, hoehe
                                  80, 40, 70, 20,
                                  hwnd,
                                  (HMENU) 2,
                                  NULL,
                                  NULL
                                  );
            TextBoxText = CreateWindow("EDIT",
                                   "",
                                   ES_MULTILINE | ES_READONLY | WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
                                   120, 60, 500, 200,
                                   hwnd,
                                   NULL,
                                   NULL,
                                   NULL
                                   );
//            TextBoxTextScrollbar = CreateWindow("SCROLLBAR")
            buttonSuchen = CreateWindow("BUTTON",
                                        "Nutzersuche",
                                        WS_VISIBLE |WS_CHILD | WS_BORDER,
                                        20, 60, 100, 20,
                                        hwnd,
                                        (HMENU) 3,
                                        NULL,
                                        NULL
                                        );
            textFeldNutzerId = CreateWindow("EDIT",
                                            "NutzerID",
                                            WS_BORDER | WS_CHILD | WS_VISIBLE,
                                            20, 80, 100, 20,
                                            hwnd,
                                            NULL,
                                            NULL,
                                            NULL
                                            );
            textFeldNachricht = CreateWindow("EDIT",
                                            "Nachricht",
                                            WS_BORDER | WS_CHILD | WS_VISIBLE,
                                            20, 100, 100, 20,
                                            hwnd,
                                            NULL,
                                            NULL,
                                            NULL
                                            );
            buttonSenden = CreateWindow("BUTTON",
                                        "Senden",
                                        WS_VISIBLE |WS_CHILD | WS_BORDER,
                                        20, 120, 100, 20,
                                        hwnd,
                                        (HMENU) 4,
                                        NULL,
                                        NULL
                                        );
            buttonNachrichtenAusgabe = CreateWindow("BUTTON",
                                        "N. Ausgabe",
                                        WS_VISIBLE |WS_CHILD | WS_BORDER,
                                        20, 140, 100, 20,
                                        hwnd,
                                        (HMENU) 5,
                                        NULL,
                                        NULL
                                        );

            break;
        case WM_COMMAND:

            /*if(LOWORD(wParam) == 1){
                char* TextEntered = NULL;
                TextEntered = (char*) malloc(sizeof (char) * 50);
                int lengthCopied; //in textentered kopierte textlaenge

                lengthCopied = GetWindowText(TextBoxName, TextEntered, 49);

                if(lengthCopied > 0)
                {
                 //   ::MessageBeep(MB_ICONERROR);
                 //   ::MessageBox(hwnd, TextEntered, "Titel", MB_OK);


                   SetWindowText(TextBoxText, TEXT(text.c_str()));
                }
                free(TextEntered);
            }*/
            //low order word
            switch(LOWORD(wParam)) //alternativ auch eine == erwarteter wert abfrage moeglich
            {
                //einlogbutton
                case 1:
                {

                    int gwtstate = 0;
                    char *t = &textSaved[0];
                    gwtstate = GetWindowText(TextBoxName, &textSaved[0], 20);
                    if(gwtstate)
                    {
                        //::MessageBox(hwnd, textSaved, textSaved, MB_OK);
                         SetWindowText(TextBoxText, TEXT(text.c_str()));
                    }
                    nutzernameString = eingabe(TextBoxName);
                    passwortString = eingabe(TextBoxPasswort);

                    ss>>nutzernameString;
                    ss>>passwortString;
                    std::cout<<"nutzername: "<<nutzernameString<<std::endl<<"passwort: "<<passwortString;
                    datei.einloggen(nutzernameString, passwortString, nutzeridAbsender);
                    if(datei.getIstEingeloggt() == true){
                        ausgabe("erfolg");
                    }else{
                        ausgabe("fehlschlag");
                    }
                    break;
                }
                case 2:
                {
                    std::string name = eingabe(TextBoxName);
                    std::string passwort = eingabe(TextBoxPasswort);
                    ausgabe("registrieren");
                    datei.registrieren(name, passwort);
                    break;
                }
                case 3:
                {
                    ausgabe("nutzersuche");
                    if(datei.getIstEingeloggt())
                    {
                        datei.vectorFuellenNutzerSuche();
                        ausgabe(datei.vectorAusgabeStringFunktion());
                    }
                    break;
                }
                case 4:
                {
                    ausgabe("nachricht senden");
                    if(datei.getIstEingeloggt())
                    {
                        std::string textFeldIDVariable = eingabe(textFeldNutzerId);
                        datei.nachrichtSenden(std::stoi(textFeldIDVariable), eingabe(textFeldNachricht));
                    }
                    break;
                }
                case 5:
                {
                    ausgabe("nachrichten ausgeben");
                    if(datei.getIstEingeloggt())
                    {
                        datei.vectorFuellenNachrichten();
                        ausgabe(datei.vectorAusgabeStringFunktion());
                    }
                    break;
                }
            }


            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
    datei.setConn(mysql_init(0));
    datei.setConn(mysql_real_connect(datei.getConn(), host, nutzernameDatenbank, passwortDatenbank, tabelle, port, unix_socket, flags));

    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,               //variationsmoeglichkeiten
        g_szClassName,                  //klassenname
        "The title of my window",       //titel
        WS_SYSMENU | WS_MINIMIZEBOX,            //positionsentscheidung
        CW_USEDEFAULT, CW_USEDEFAULT,   //position auf dem bildschirm
        800, 500,                     //hoehe, breite
        NULL,                           //das fenster ist ein child fenster des desktops
        NULL,                           //kein menue
        hInstance,                      //programmminstanzhandler
        NULL                            //keine windows erstelldaten
        );

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}


