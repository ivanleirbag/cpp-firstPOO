#include <cstring>
#include <ncurses.h>
#include "TObject"

class LabelObj : public TObject{
    
    private:
        char text[256] = {0};
        enum TEXT_ALIGN {LEFT = 0, CENTER, RIGHT};
        int align;
        char *str;


    public:
        LabelObj();

        void setTxt(char* str);
        const char* getTxt(){return *txt;};

        void SetAlign(int aAlign) { align = aAlign; }
        int GetAlign() { return align; }
        
        void ShowTxt();

};

LabelObj::LabelObj() {
    align = LEFT;
}

void LabelObj::setTxt(char* str) {
    strncpy(text, str, sizeof(text) - 1);
    text[sizeof(text) - 1] = '\0';  
}

const char* LabelObj::getTxt() {
    return text;
}

void ShowText(){
    int y = GetPosy();  
    int x = GetPosx();  
    
    move(y, x);
    
    printw("%s", text);

    refresh();
}
