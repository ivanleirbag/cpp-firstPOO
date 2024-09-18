#include <cstring>
#include <ncurses.h>

//g++ -Wall ./main.cpp -o main -lncurses

#define LEFT 0
#define CENTER 0
#define RIGHT 0

class TObject{

    protected:
        int posx;
        int posy;
        int height;
        int width;
        int txColor;
        int bgColor;
        int colorPair;

    public:
        TObject();

        void SetPosx(int aPosx){posx = aPosx;};
        int GetPosx(){return posx;};

        void SetPosy(int aPosy){posy = aPosy;};
        int GetPosy(){return posy;};

        void SetWidth(int aWidth){width = aWidth;};
        int GetWidth(){return width;};

        void SetHeight(int aHeight){height = aHeight;};
        int GetHeight(){return height;};

        void SetColors(int pair, int aTxColor, int aBgColor);
};

TObject::TObject(){
    posx = 0;
    posy = 0;
    height = 3;
    width = 10;
    colorPair = 1;
    start_color();
    txColor = COLOR_WHITE;
    bgColor = COLOR_BLACK;
    init_pair(colorPair, txColor, bgColor);
}

void TObject::SetColors(int pair, int aTxColor, int aBgColor){
    txColor = aTxColor; 
    bgColor = aBgColor;
    colorPair = pair;
    init_pair(colorPair, txColor, bgColor);
}

class LabelObj : public TObject{
    protected:
        char text[256] = {0};
        int align;
        char *tP = text; 
        int lenght;

    public:
        LabelObj();

        void SetTxt(char* str);
        char* GetTxt(){return tP;}

        void SetAlign(int aAlign){align = aAlign;}
        int GetAlign(){return align;}
        
        int GetLenght();

        void ShowText();
};

LabelObj::LabelObj() {
    align = 0;
}

void LabelObj::SetTxt(char* str) {
    strncpy(text, str, sizeof(text) - 1);
    text[sizeof(text) - 1] = '\0';  
}

int LabelObj::GetLenght(){
    lenght = strlen(text);
    return lenght;
}

void LabelObj::ShowText(){
    int y = GetPosy();  
    int x = GetPosx();  
    int width = GetWidth();
    int height = GetHeight();
    int lines = 0;
    char* tP = GetTxt();
    int align = GetAlign();
    int fullLines = GetLenght()/width;

    attron(COLOR_PAIR(colorPair));

    for (int k = 0; k < height; k++){
        for (int j = 0; j < width; j++){
            move((y+k), (x+j));
            printw(" ");
        }
    }

    if(align == 0){
        for (int i = 0; i < 256; i++){
            move(y, x);
            x++;
            if (*(tP+i) == '\0'){
                break;
            }
            if ((i+1)%width == 0){
                y++;
                lines++;
                x = GetPosx();
            }
            if ((lines == height)){
                break;
            }
            printw("%c", *(tP+i));
        }
    }else if(align == 2){
        for (int i = 0; i < 256; i++){
            move(y, x);
            x++;
            if (*(tP+i) == '\0'){
                break;
            }
            if ((i+1)%width == 0){
                if (((y+1)-GetPosy()) == fullLines){
                    y++;
                    x = posx+(width-(GetLenght()-(fullLines*width)));
                }else{
                    y++;
                    lines++;
                    x = GetPosx();
                }
            }
            if ((lines == height)){
                break;
            }
            printw("%c", *(tP+i));
        }
    }else if(align == 1){
        for (int i = 0; i < 256; i++){
            move(y, x);
            x++;
            if (*(tP+i) == '\0'){
                break;
            }
            if ((i+1)%width == 0){
                if (((y+1)-GetPosy()) == fullLines){
                    y++;
                    x = posx+((width-(GetLenght()-(fullLines*width)))/2);
                }else{
                    y++;
                    lines++;
                    x = GetPosx();
                }
            }
            if ((lines == height)){
                break;
            }
            printw("%c", *(tP+i));
        }
    }


    attroff(COLOR_PAIR(colorPair));
}

int main(){
    initscr();
    curs_set(0);
    start_color();

    LabelObj lbl;
    lbl.SetPosx(10);
    lbl.SetPosy(3);
    lbl.SetAlign(2);
    lbl.SetColors(2, COLOR_BLACK, COLOR_CYAN);
    lbl.SetTxt("HOLA PROBANDO");

    lbl.ShowText();

    LabelObj lbl2;
    lbl2.SetPosx(27);
    lbl2.SetHeight(6);
    lbl2.SetWidth(18);
    lbl2.SetPosy(3);
    lbl2.SetAlign(1);
    lbl2.SetColors(3, COLOR_BLACK, COLOR_RED);
    lbl2.SetTxt("HOLA PROB ANDO ANDOADNO");

    lbl2.ShowText();

    LabelObj lbl3;
    lbl3.SetPosx(4);
    lbl3.SetPosy(10);
    lbl3.SetHeight(7);
    lbl3.SetWidth(4);
    lbl3.SetAlign(0);
    lbl3.SetColors(4, COLOR_BLUE, COLOR_YELLOW);
    lbl3.SetTxt("WWW.HTML.CSS.COM.AR");

    lbl3.ShowText();

    refresh();
    getch();
    endwin();
    return 0;
}