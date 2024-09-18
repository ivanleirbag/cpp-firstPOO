#include <cstring>
#include <ncurses.h>

//g++ -Wall ./main.cpp -o main -lncurses

class TObject{

    protected:
        int posx;
        int posy;
        int height;
        int width;
        int txColor;
        int bgColor;

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

        void SetColors(int aTxColor, int aBgColor);
};

TObject::TObject(){
    
    posx = 0;
    posy = 0;
    height = 3;
    width = 10;
    start_color();
    txColor = COLOR_WHITE;
    bgColor = COLOR_BLACK;
    init_pair(1, txColor, bgColor);
}

void TObject::SetColors(int aTxColor, int aBgColor){
    txColor = aTxColor; 
    bgColor = aBgColor;
    init_pair(1, txColor, bgColor);
}

class LabelObj : public TObject{
    protected:
        char text[256] = {0};
        enum TEXT_ALIGN {LEFT = 0, CENTER, RIGHT};
        int align;
        char *tP = text; 
    public:
        LabelObj();

        void setTxt(char* str);
        char* getTxt(){return tP;}

        void SetAlign(int aAlign){align = aAlign;}
        int GetAlign(){return align;}
        
        void ShowText();

};

LabelObj::LabelObj() {
    align = LEFT;
}

void LabelObj::setTxt(char* str) {
    strncpy(text, str, sizeof(text) - 1);
    text[sizeof(text) - 1] = '\0';  
}

void LabelObj::ShowText(){
    int y = GetPosy();  
    int x = GetPosx();  
    int width = GetWidth();
    int height = GetHeight();
    int lines = 0;
    char* tP = getTxt();
    attron(COLOR_PAIR(1));

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

    attroff(COLOR_PAIR(1));
    refresh();
}

int main(){
    initscr();

    LabelObj lbl;

    lbl.SetPosx(16);
    lbl.SetPosy(1);
    lbl.SetColors(COLOR_BLACK, COLOR_CYAN);

    lbl.setTxt("HOLA PROBANDO");

    lbl.ShowText();

    getch();

    endwin();

    return 0;
}