#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct AutoInf
{
    string Auto;
    int price;
    int epower;
    double volume;
    void Out();
};

struct DLList
{
    struct Node
    {
        AutoInf data;    
        Node* next;   
        Node* prev;   
    };

    Node* F = NULL;     //first node
    Node* L = NULL;     //last node
    Node* C = NULL;     //current node
    int Count;        //node count

    void Out();
    void Info();
    void Clear();

    bool MoveNext();
    bool MovePrev();
    bool MoveFirst();
    bool MoveLast();

    bool Init(AutoInf);
    bool AddNext(AutoInf);
    bool AddPrev(AutoInf);
    bool AddFirst(AutoInf);
    bool AddLast(AutoInf);

    bool Del(AutoInf&);
    bool DelNext(AutoInf&);
    bool DelPrev(AutoInf&);
    bool DelFirst(AutoInf&);
    bool DelLast(AutoInf&);
};

bool DLList::MoveNext()
{
    if (!F)       return false;
    if (!C) { C = F; return true; }
    if (!C->next) return false;
    C = C->next;
    return true;
}

bool DLList::MovePrev()
{
    if (!F)       return false;
    if (!C) { C = F; return true; }
    if (!C->prev) return false;
    C = C->prev;
    return true;
}
bool DLList::MoveFirst()
{
    if (!F) return false;
    C = F;
    return true;
}

bool DLList::MoveLast()
{
    if (!L) return false;
    C = L;
    return true;
}

bool DLList::Init(AutoInf data)
{
    if (!F)
    {
        F = new Node;
        L = F;
        C = F;
        F->prev = NULL;
        F->next = NULL;
        F->data = data;
        Count = 1;
        return true;
    }
    else
        return false;
}

bool DLList::AddNext(AutoInf data)
{
    if (!F) return Init(data);

    Node* temp = C->next;
    C->next = new Node;
    C->next->next = temp;
    C->next->prev = C;

    if (!temp)
        L = C->next;
    else
        temp->prev = C->next;

    C = C->next;
    C->data = data;
    Count++;
    return true;

}

bool DLList::AddPrev(AutoInf data)
{
    if (!F) return Init(data);

    Node* temp = C->prev;
    C->prev = new Node;
    C->prev->next = C;
    C->prev->prev = temp;

    if (!temp)
        F = C->prev;
    else
        temp->next = C->prev;

    C = C->prev;
    C->data = data;
    Count++;
    return true;
}

bool DLList::AddFirst(AutoInf data)
{
    if (MoveFirst())return AddPrev(data);
    else return false;
}

bool DLList::AddLast(AutoInf data)
{
    if (MoveLast())return AddNext(data);
    else return false;
}

void DLList::Out()
{
    if (!F)
    {
        cout << "список пуст" << endl;
        return;
    }

    Node* temp = F;
    cout << "Список: " << endl << endl;
    do
    {
        temp->data.Out();
        temp = temp->next;
    } while (temp);
    cout << endl;
}

void DLList::Info()
{

    if (Count)
        cout << "Список узлов: "
        << Count << endl << endl;
    else
        cout << "список пуст" << endl;
    if (C)
    {
        if (MoveFirst())
        {
            cout << "текущие данные узла: ";
            C->data.Out();
        }
    }
}

bool DLList::DelFirst(AutoInf& data)
{
    if (!F)      return false;
    if (C != F)    MoveFirst();

    Node* temp = C->next;
    data = C->data;

    if (temp) temp->prev = NULL;
    delete C;

    C = temp;
    F = temp;
    Count--;
    if (!temp) { L = NULL; return false; }
    return true;
}

bool DLList::DelLast(AutoInf& data)
{
    if (!F)      return false;
    if (C != L)    MoveLast();

    Node* temp = C->prev;
    data = C->data;

    if (temp) temp->next = NULL;
    delete C;

    C = temp;
    L = temp;
    Count--;

    if (!temp) { F = NULL; return false; }
    return true;
}

bool DLList::Del(AutoInf& data)
{
    if (!F) return false;
    if (!C) return false;

    if (C == F) return DelFirst(data);
    if (C == L) return DelLast(data);

    Node* temp = C->next;
    data = C->data;

    C->prev->next = C->next;
    C->next->prev = C->prev;

    delete C;
    C = temp;
    Count--;
    return true;
}

bool DLList::DelNext(AutoInf& data)
{
    if (!F) return false;
    if (!C) return false;
    if (MoveNext()) return Del(data);
    return false;
}
bool DLList::DelPrev(AutoInf& data)
{
    if (!F) return false;
    if (!C) return false;
    if (MovePrev()) return Del(data);
    return false;
}

void DLList::Clear()
{
    if (!MoveFirst())
    {
        cout << "список пуст" << endl;
        return;
    }
    AutoInf k;
    while (Del(k));
}

void AutoInf::Out()
{
    cout << "Авто: " << Auto << "\t" << "цена: " << price << "\t" << "мощность двигателя: " << epower << "\t" << "объем двигателя: " << volume << endl << endl;
}

bool GetFile(DLList&, AutoInf&);
bool WriteFile(DLList&, AutoInf&);
void GetAuto(AutoInf&);

bool GetFile(DLList& DLList, AutoInf& Info)
{
    ifstream F("Auto.txt");
    if (!F)
    {
        cout << "файл не найден!" << endl;
        return false;
    }
    while (F >> Info.Auto >> Info.price >> Info.epower >> Info.volume)
    {
        DLList.AddNext(Info);
    }
    F.close();
    return true;
}

bool WriteFile(DLList& DLList, AutoInf& Info)
{
    ofstream F("Auto.txt");
    if (!F)
    {
        cout << "файл не найден!" << endl;
        return false;
    }
    DLList.MoveFirst();
    do
    {
        F << DLList.C->data.Auto << " " << DLList.C->data.price << " " << DLList.C->data.epower << " " << DLList.C->data.volume << endl;
    } while (DLList.MoveNext());
    DLList.MoveFirst();
    F.close();
    return true;
}

void GetAuto(AutoInf& Info)
{
    cout << "введите модель автомобиля: ";
    cin >> Info.Auto;
    cout << endl;
    cout << "введите цену(тыс): ";
    cin >> Info.price;
    cout << endl;
    cout << "введите мощность(л.с.): ";
    cin >> Info.epower;
    cout << endl;
    cout << "введите объем двигателя(л): ";
    cin >> Info.volume;
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    AutoInf Info;
    DLList DLList;
    GetFile(DLList, Info);
    DLList.Out();
    int num, sub = 0, sub1 = 0, sub2 = 0;
    do
    {
        cout << "1. Добавить" << endl
            << "2. Удалить" << endl
            << "3. Очистить список" << endl
            << "4. Сохранить" << endl
            << "0. Выйти" << endl;
        cout << endl << "Выберите действие: ";
        cin >> sub;
        cout << endl;
        switch (sub)
        {
        case 1:
            cout << "1. В начало" << endl
                << "2. В конец" << endl
                << "3. На выбранную позицию" << endl
                << "0. Вернуться" << endl;
            cout << endl << "Выберите действие: ";
            cin >> sub1;
            cout << endl;
            switch (sub1)
            {
            case 1:
                GetAuto(Info);
                DLList.AddFirst(Info);
                DLList.Out();
                break;
            case 2:
                GetAuto(Info);
                DLList.AddLast(Info);
                DLList.Out();
                break;
            case 3:
                cout << "Позиция: ";
                cin >> num;
                GetAuto(Info);
                if (num == 1)
                {
                    DLList.AddFirst(Info);
                    DLList.Out();
                    break;
                }
                else if (num == DLList.Count + 1)
                {
                    DLList.AddLast(Info);
                    DLList.Out();
                    break;
                }
                DLList.MoveFirst();
                for (int i = 1; i < num - 1; i++)
                {
                    DLList.MoveNext();
                }
                DLList.AddNext(Info);
                DLList.Out();
                break;
            default:
                if (sub1 != 0)
                {
                    cout << "нет такого действия!" << endl << endl;
                }
                break;
            }
            break;
        case 2:
            cout << "1. Удалить первое" << endl
                << "2. Последнее" << endl
                << "3. Удалить выбранный элемент" << endl
                << "0. Вернуться" << endl;
            cout << endl << "Select an action: ";
            cin >> sub2;
            cout << endl;
            switch (sub2)
            {
            case 1:
                DLList.DelFirst(Info);
                DLList.Out();
                break;
            case 2:
                DLList.DelLast(Info);
                DLList.Out();
                break;
            case 3:
                cout << "Позиция: ";
                cin >> num;
                if (num == 1)
                {
                    DLList.DelFirst(Info);
                    DLList.Out();
                    break;
                }
                else if (num == DLList.Count)
                {
                    DLList.DelLast(Info);
                    DLList.Out();
                    break;
                }
                DLList.MoveFirst();
                for (int i = 1; i < num; i++)
                {
                    DLList.MoveNext();
                }
                DLList.Del(Info);
                DLList.Out();
                break;
            default:
                if (sub2 != 0)
                {
                    cout << "нет такого действия!" << endl << endl;
                }
                break;
            }
            break;
        case 3:
            DLList.Clear();
            DLList.Out();
            break;
        case 4:
            WriteFile(DLList, Info);
            break;
        default:
            if (sub != 0)
            {
                cout << "нет такого действия!" << endl << endl;
            }
            DLList.Clear();
            DLList.Out();
            break;
        }
    } while (sub != 0);
}