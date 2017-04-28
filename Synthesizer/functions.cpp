#include "functions.h"

//функция возвращает значение индекса массива в пределе до m
int maximum(int m,//макисмальный индекс
            int i)//текущий индекс
{
    if(i >= m)
        return (i-m*int(i/m));
    else
        return i;
}
//функция возвращает путь в exe файлу
QString pathReader(char* path[])//полный путь до exe
{
    int slashPosition;
    QString temp(*path);
    for(int i = temp.length(); i > 0; i--)
    {
        if(temp[i] == '\\')
        {
            slashPosition = i;
            temp = temp.remove(i+1, temp.length());
            break;
        }
    }
    return temp;
}
//функция возвращает номер массива в котором содержатся изображения белых клавишх
int switchOctave(QString str, //нажвание клавиши
                 int mode)//0 для нажатия
                          //1 при отпускании
{
    str = str.remove(str.length() - 1, 1);
    QByteArray a = str.toLocal8Bit();
    char s = a.at(0);

    switch (s) {
    case 'C':
    case 'F':
        return 0;
    case 'D':
        return 1;
    case 'E':
    case 'B':
        return 2;
    case 'G':
        return (3+mode);
    case 'A':
        return (4+mode);
    }

}
