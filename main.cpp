
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <map>
#include <cstring>
#include <cstdlib>
//#include "solve_code.c"

#define iftag 101
#define elsetag 102
#define switchtag 103
#define casetag 104
#define whiletag 105
#define consttag 106
#define inttag 107
#define chartag 108
#define voidtag 109
#define maintag 110
#define scanftag 111
#define printftag 112
#define idtag 113
#define returntag 115
#define defaulttag 116

#define plustag 122
#define minustag 123
#define startag 124
#define divtag 125
#define lpartag 126
#define rpartag 127
#define commatag 128
#define semitag 129
#define colontag 130
#define assigntag 131
#define equtag 132
#define leseqtag 133
#define lesstag 134
#define moreeqtag 135
#define moretag 136
#define noteqtag 137
#define LPtag 138
#define RPtag 139
#define lmidtag 140
#define rmidtag 141
#define numtag 142
#define CHtag 199
/////////////////////////////////////////////////////////////////////////////////
#define stringtag 114
#define intarraytype 50
#define chararraytype 51
#define intretag 53
#define charretag 54
#define array_maxpos 1000
#define alloc_size 400
////////////////////////////////////////////////////////////////////////////////

using namespace std;
/////////////////////////////////////////////////////////////////////////////////

int solve_if();
int solve_simple();
int solve_expression();
void solve_assign();
void solve_while();
int solve_const(int a);
int solve_statement(int a);
int solve_sentence(bool ish = 0);
void solve_printf();
void solve_scanf();
void solve_return();


struct jj
{
    string name;
    int type;
    int size;
    int last;
    int depth;
    int constvalue;
    int addr;
    int arr[100];
    bool con = 0;
    bool ret = 0;
    int position;
}tab[10010];
struct kk
{
    string type;
    string idname;
    int pos1;
    int pos2;
    int pos3;
    int self;
}code1[5000010];
int codepos = 0;
int storeposition;
int tabpos = 0;
map <string,int>find_t;
int depth;
struct lldd
{
    string type;
    string p1;
    string p2;
    string p3;
    int pos1,pos2,pos3;
}MIPS1[5000010];
FILE *fp=NULL;
int sum_string_tag;
string st_output[10010];
int charsostrong = 1;
int sumchar = 0;
//fprintf(f,"%d ",a[i]);
////////////////////////////////////////////////////////////////////////////////


//sint st_use;

char code[10000060];
bool Mul[10000060];
int line[10000006];
char id[400],string_1[6000];
int Int_Value;
int length_of_code,pos;
void error(string s = "error2")
{
    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    cout<<"ERROR! Near line "<<line[pos]<<":"<<endl;
    cout<<s<<endl;
}
char next()
{
    char ret = code[pos];
    pos ++;
    return ret;
}
char last()
{
    pos --;
    return code[pos];
}
bool isAlpha(char a)
{
    return  (a == '_' || (a >='a' && a <= 'z') || (a >='A' && a <= 'Z'));
}
bool isNum(char a)
{
    return (a >= '0' && a <= '9');
}
int solveReserve(char a)
{
    int pos1 = pos;
    memset(id,0,sizeof(id));
    int i = 0;
    while(isAlpha(a) || isNum(a))
    {
        a = next();
        if(a >= 'A' && a <= 'Z') a -= ('A' - 'a');
        //cout<<"a:"<<a<<endl;
        if(isAlpha(a) || isNum(a))
        id[i] = a;

        i ++;
        //if(i > 100 || a == 0)error();
    }i --;
    cout<<"ID:"<<id<<' '<<i<<endl;
    last();
    if(i == 2)//if
    {
        if(id[0] == 'i'){
        if(id[1] == 'f')
            return iftag;
        else return -1;}
        else return -1;
    }
    else if(i == 3)//int
    {
       // cout<<"Yes! Party time!"<<endl;
        if(id[0] == 'i'){
        if(id[1] == 'n'){
        if(id[2] == 't')
        {
           // cout<<"int"<<endl;
             return inttag;
        }

        else return -1;}
        else return -1;}
        else return -1;
    }
    else if(i == 4)//char,else,case,void,main
    {
        if(id[0] == 'c'){
        if(id[1] == 'h'){if(id[2] == 'a'){if(id[3] == 'r')return chartag;else return -1;}else return -1;}
        else if(id[1] == 'a' && id[2] == 's' && id[3] == 'e')return casetag;
        else return -1;}
        else {

        if(id[0] == 'e'){
        if(id[1] == 'l'){
        if(id[2] == 's'){
        if(id[3] == 'e')
            return elsetag;
        else return -1;}
        else return -1;}
        else return -1;}
        else {

        if(id[0] == 'v'){
        if(id[1] == 'o'){
        if(id[2] == 'i'){
        if(id[3] == 'd')
            return voidtag;
        else return -1;}
        else return -1;}
        else return -1;}
        else {

        if(id[0] == 'm'){
        if(id[1] == 'a'){
        if(id[2] == 'i'){
        if(id[3] == 'n')
            return maintag;
        else return -1;}
        else return -1;}
        else return -1;}
        else return -1;
        }
        }
        }
    }
    else if(i == 5)//while,const,scanf
    {
        if(id[0] == 'w' && id[1] == 'h' && id[2] == 'i' && id[3] == 'l' && id[4] == 'e') return whiletag;
        else if(id[0] == 'c' && id[1] == 'o' && id[2] == 'n' && id[3] == 's' && id[4] == 't') return consttag;
        else if(id[0] == 's' && id[1] == 'c' && id[2] == 'a' && id[3] == 'n' && id[4] == 'f') return scanftag;
        else return -1;
    }
    else if(i == 6)//switch,printf,return
    {
        if(id[0] == 's' && id[1] == 'w' && id[2] == 'i' && id[3] == 't' && id[4] == 'c' && id[5] == 'h') return switchtag;
        else if(id[0] == 'p' && id[1] == 'r' && id[2] == 'i' && id[3] == 'n' && id[4] == 't' && id[5] == 'f') return printftag;
         else if(id[0] == 'r' && id[1] == 'e' && id[2] == 't' && id[3] == 'u' && id[4] == 'r' && id[5] == 'n') return returntag;

        else return -1;
    }
    else if(i == 7)
    {
        if(id[0] == 'd' && id[1] == 'e' && id[2] == 'f' && id[3] == 'a' && id[4] == 'u' && id[5] == 'l' && id[6] == 't') return defaulttag;
        else return -1;
    }
    else return -1;
return -1;
}
int solveString()
{
    memset(string_1,0,sizeof(string_1));
    char a = code[pos];
    int i = 0;
    while(a != '"')
    {
        a = next();
        if(a == '"')break;
        //cout<<"a = "<<a<<endl;
        if(!(a == 32 || a == 33 || (a >= 35 && a <= 126))) error("字符串中含有非法字符!");
        string_1[i] = a;//cout<<string_1<<endl;

        if(i > 3000 || a == 0)
        {if(a != 0)error("长度超过最大值!");else error("缺少右括号!");exit(0);}
        i ++;
    }
    if(i == 0)
    next();
    return stringtag;
}
int solveChar()
{
    memset(string_1,0,sizeof(string_1));
    char a = next();
    if((! isNum(a)) && (! isAlpha(a)) && a != '+' && a != '-' && a != '*' && a != '/')error("非法单个字符");
    string_1[0] = a;
    //cout<<a<<endl;
    a = next();
    if(a != '\'')
    {error("缺少右边的单引号");last();}
    //next();
    cout<<code[pos]<<code[pos + 1]<<endl;
    return CHtag;
}
bool isNumber(char a)
{
    return a >= '1' && a <= '9';
}
int nextsym()
{
    int sum = 0;
    bool tag = 0;
    //cout<<"pos:"<<pos<<endl;
    char a = code[pos];
   // cout<<"a:="<<a<<endl;
    while (isspace(a))
    {
         a = next();
         tag = 1;
    }
    if(tag) pos --;
    if(a == '/')
    {
        //cout<<"love letter"<<endl;
        a = next();
        a = next();
        //cout<<a<<endl;
        if(a == '/')
        {
            while(a != '\n')
            a = next();
            if(a == '\n'){return -2;}
        }
        else if(a == '*')
        {
          //  cout<<"yes,party time!"<<endl;
            while(1)
            {
                a = next();
                if(a == '*')
                {
                    a = next();
                    if(a == '/'){next();return -2;}
                    last();
                }
            }

        }
        else {last();return divtag;}
    }
    else if(isAlpha(a))
    {
          int i = solveReserve(a);
          if(i != -1)return i;
          else
          {
              return idtag;
          }
    }
    else if(isNumber(a))
    {
        long long z = 0;
        a = next();
        while(isNum(a))
        {
            z *= 10;
          z += a - '0';//if(z > 2147483647)error();
          a = next();
        }
        last();
        Int_Value = z;
        cout<<"INT VALUE:"<<Int_Value<<endl;
        return numtag;
    }
    else if(a == '<')
    {
        a = next();
        a = next();
        if(a == '='){return leseqtag;}
        last();
        return lesstag;
    }
    else if(a == '>')
    {
        a = next();
        a = next();
        if(a == '='){return moreeqtag;}
        last();
        return moretag;
    }
    else if(a == '=')
    {
         a = next();
         a = next();
        if(a == '='){return equtag;}
        last();
        return assigntag;
    }
    else if(a == '!')
    {
        a = next();
        a = next();
        if(a == '='){return noteqtag;}
        last();
        error("!后应该紧接着等于号");
    }
    else if(a == '"')
    {
        next();
        return solveString();
    }
    else if(a == '\'')
    {
        next();
        return solveChar();
    }
    else if(a == '+')
    {
        next();
        return plustag;
    }
    else if(a == '-')
    {
        next();
        return minustag;
    }
    else if(a == '*')
    {
        next();
        return startag;
    }
    else if(a == '(')
    {
        next();
        return lpartag;
    }
    else if(a == ')')
    {
        next();
        return rpartag;
    }
    else if(a == ',')
    {
        next();
        return commatag;
    }
    else if(a == '{')
    {
        next();
        return LPtag;
    }
    else if(a == '}')
    {
        next();
        return RPtag;
    }
    else if(a == ':')
    {
        next();
        return colontag;
    }
    else if(a == ';')
    {
        next();
        return semitag;
    }
    else if(a == '[')
    {
        next();
        return lmidtag;
    }
    else if(a == ']')
    {
        next();
        return rmidtag;
    }
    else if(a == '0')
    {
        next();
        a = next();
        if(!(a >= '0' && a <= '9'))
        {
            last();
            Int_Value = 0;
            return numtag;
        }
        else error("非0整数不能以0开头");
    }
    else
    {if(a == 0)return 0;
    else error("非法字符开头!");
    next();
    return 7;}
}

void word_temp()
{
    int po = pos;
    while(1)
    {
        po = pos;
        int i = nextsym();
        cout<<"At line :"<<line[po]<<endl;
        for(int j = po;j < pos;j ++)
            cout<<code[j];
        cout<<endl;
        cout<<"code = "<<i<<endl;
        switch (i)
        {

            case 101: cout<<"if语句"<<endl;break;
            case 102: cout<<"else语句"<<endl;break;
            case 103: cout<<"switch语句"<<endl;break;
            case 104: cout<<"case语句"<<endl;break;
            case 105: cout<<"while语句"<<endl;break;
            case 106: cout<<"const语句"<<endl;break;
            case 107: cout<<"int语句"<<endl;break;
            case 108: cout<<"char语句"<<endl;break;
            case 109: cout<<"void语句"<<endl;break;
            case 110: cout<<"main语句"<<endl;break;
            case 111: cout<<"scanf语句"<<endl;break;
            case 112: cout<<"printf语句"<<endl;break;
            case 113: cout<<"id语句"<<endl;break;
            case 114: cout<<"string类型字符串"<<endl;break;
            case 115: cout<<"return语句"<<endl;break;
            case 122: cout<<"加法符号+"<<endl;break;
            case 123: cout<<"减法符号-"<<endl;break;
            case 124: cout<<"星星符号*"<<endl;break;
            case 125: cout<<"除法符号/"<<endl;break;
            case 126: cout<<"左小括号("<<endl;break;
            case 127: cout<<"右小括号)"<<endl;break;
            case 128: cout<<"逗号,"<<endl;break;
            case 129: cout<<"分号;"<<endl;break;
            case 130: cout<<"冒号:"<<endl;break;
            case 131: cout<<"赋值语句="<<endl;break;
            case 132: cout<<"等于判断 == "<<endl;break;
            case 133: cout<<"小于等于 <="<<endl;break;
            case 134: cout<<"小于<"<<endl;break;
            case 135: cout<<"大于等于 >="<<endl;break;
            case 136: cout<<"大于 >"<<endl;break;
            case 137: cout<<"不等于 !="<<endl;break;
            case 138: cout<<"左大于号{"<<endl;break;
            case 139: cout<<"右大于号}"<<endl;break;
            case 140: cout<<"左中括号["<<endl;break;
            case 141: cout<<"右中括号]"<<endl;break;
        }

        cout<<"_______________________________________________________"<<endl;
        if(i == 0)break;
    }
}
void solve_line()
{

    for(int i = 1;code[i] != 0;i ++)
    {
        if(code[i - 1] == '\n')
        {
             line[i] = line[i - 1] + 1;

        }
        else line[i] = line[i-1];

    }
}
void input()
{
    char s[500];
    cout<<"Please input the path of our code!"<<endl;
    cin>>s;
    string c = s;
    freopen(s,"r",stdin);
    int i = 0;
    while(scanf("%c",&code[i]) != EOF)
    {
        i ++;
        if(i == 10000000)
        {
            cout<<"Code too long! Exit!"<<endl;
            exit(0);
        }
    }
    length_of_code = i;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
int filltab(int type = inttag,int depth = 1,string id = "")
{
    string c = id;
    int ret;
    if(find_t[c] == 0)
    {
        tabpos ++;
        tab[tabpos].name = c;
        tab[tabpos].last = find_t[c];
        find_t[c] = tabpos;
        tab[tabpos].type = type;
        tab[tabpos].depth = depth;
        tab[tabpos].con = 0;
        tab[tabpos].ret = 0;
        tab[tabpos].size = 1;
        if(tab[tabpos - 1].depth == tab[tabpos].depth)
        {
            tab[tabpos].addr = tab[tabpos - 1].addr + ((tab[tabpos - 1].ret)?0:(tab[tabpos-1].size));
        }
        else
        {
            tab[tabpos].addr = 2;
        }
        ret = tabpos;
    }
    else
    {
        //cout<<"符号表:"<<c<<endl;
        //cout<<depth<<endl;
      //  cout<<tab[find_t[c]].name<<' '<<tab[find_t[c]].depth<<endl;;
        if(tab[find_t[c]].depth == depth){error("重复定义!");}//
        else
        {
        tabpos ++;
        tab[tabpos].name = c;
        tab[tabpos].last = find_t[c];
        find_t[c] = tabpos;
        tab[tabpos].type = type;
        tab[tabpos].depth = depth;
        tab[tabpos].con = 0;
        tab[tabpos].ret = 0;
        tab[tabpos].size = 1;
        ret = tabpos;
        if(tab[tabpos].depth == tab[tabpos - 1].depth)
        {
            tab[tabpos].addr = tab[tabpos - 1].addr + ((tab[tabpos - 1].ret)?0:(tab[tabpos-1].size));
        }
        else
        {
            tab[tabpos].addr = 2;
        }
        }
    }
    return tabpos;
}
int lastcode;

int tab_pos;
int find_tab(string a = "a")
{
    int ppp = find_t[a];
    cout<<a<<endl;
    if(ppp == 0)error("不存在变量!");
    else
    {
        tab_pos = ppp;
        if(tab[ppp].ret)
        {
            if(tab[ppp].type == inttag)return intretag;
            if(tab[ppp].type == chartag)return charretag;
            return voidtag;
        }
        if(tab[ppp].size>1)
        {
            //cout<<"findpos!:"<<tab[ppp].name<<endl;
            if(tab[ppp].type == inttag)return intarraytype;
            if(tab[ppp].type == chartag)return chararraytype;
        }
        return tab[ppp].type;
    }
    return tab[ppp].type;
}
void push_tab(int depth = 1)
{
    int i;
    while(tab[tabpos].depth == 1)
    {
        find_t[tab[tabpos].name] = tab[tabpos].last;
        tab[tabpos].size = 0;
        tab[tabpos].last = 0;
        tab[tabpos].ret = 0;
        tab[tabpos].con = 0;
        tabpos --;
    }
}

int sumtag = 0;
void emitstr(int i)
{
    fprintf(fp,"li $a0 %d\n",i);
    fprintf(fp,"li $v0 11\n");
    fprintf(fp,"syscall\n");
}
void emitprintfstring()
{
    int i = 0;
    for(i = 0;string_1[i] != 0;i ++)
    {
        emitstr(string_1[i]);
    }
    fprintf(fp,"li $a0 10\n");
    fprintf(fp,"li $v0 11\n");
    fprintf(fp,"syscall\n");
}
void emitmipspex(int pos)
{
    fprintf(fp,"lw $a0 %d($sp)\n",pos*4);
    fprintf(fp,"li $v0 1\n");
    fprintf(fp,"syscall\n");
    fprintf(fp,"li $a0 10\n");
    fprintf(fp,"li $v0 11\n");
    fprintf(fp,"syscall\n");
}
void emitprintfex(int pos)
{
    codepos ++;
    code1[codepos].type = "Printf";
    code1[codepos].pos1 = pos;
    emitmipspex(pos);
}
void emitmipspchar(int pos)
{
    fprintf(fp,"lw $a0 %d($sp)\n",pos*4);
    fprintf(fp,"li $v0 11\n");
    fprintf(fp,"syscall\n");
    fprintf(fp,"li $a0 10\n");
    fprintf(fp,"li $v0 11\n");
    fprintf(fp,"syscall\n");
}
void emitprintfchar(int pos)
{
    codepos ++;
    code1[codepos].type = "Printfc";
    code1[codepos].pos1 = pos;
    emitmipspchar(pos);
}
void emitmipsscanf(int PO)
{
    if(tab[PO].type == chartag)
    {
        fprintf(fp,"li $v0 12\n");
    }
    else if(tab[PO].type == inttag)
    {
        fprintf(fp,"li $v0 5\n");
    }
    else {error("读入非法类型!");return;}

    fprintf(fp,"syscall\n");
    if(tab[PO].depth == 0)
    {
        fprintf(fp,"sw $v0 %d($0)\n",tab[PO].addr * 4);
    }
    else
    {
        fprintf(fp, "sw $v0 %d($sp)\n",tab[PO].addr * 4);
        cout<<"SCSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS:"<<tab[PO].name<<' '<<tab[PO].addr<<' '<<tab[PO].size<<' '<<tab[PO].depth<<endl;
    }
}
void emitscanf(int PO)
{
    codepos ++;
    code1[codepos].type = "Scanf";
    code1[codepos].idname = tab[PO].name;
    emitmipsscanf(PO);
}
void emitmfret(int pos1)
{
    fprintf(fp,"sw $a1 %d($sp)\n",pos1*4);
}
void emitmipsrv(int pos1)
{
    fprintf(fp,"lw $a1 %d($sp)\n",pos1 * 4);
}
void emitret_value(int pos1)
{
    codepos ++;
    code1[codepos].type = "SetRetValue";
    code1[codepos].pos1 = pos1;
    emitmipsrv(pos1);
}
void emitmipsexpression()
{
    fprintf(fp,"lw $s1 %d($sp)\n",code1[codepos].pos2*4);
    fprintf(fp,"lw $s2 %d($sp)\n",code1[codepos].pos3*4);
    if(code1[codepos].type == "ADD")
    {
        fprintf(fp,"addu $s1 $s1 $s2\n");
        fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
    }
    else if(code1[codepos].type == "MINUS")
    {
        fprintf(fp,"subu $s1 $s1 $s2\n");
        fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
    }
    else if(code1[codepos].type == "DIV")
    {
        fprintf(fp,"div $s1 $s2\n");
        fprintf(fp,"mflo $s1\n");
        fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
    }
    else if(code1[codepos].type == "MULT")
    {
        fprintf(fp,"mult $s1 $s2\n");
        fprintf(fp,"mflo $s1\n");
        fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
    }
}
void emitexpression(string a,int pos1,int pos2,int pos3)
{
    codepos ++;
    code1[codepos].type = a;
    code1[codepos].pos1 = pos1;
    code1[codepos].pos2 = pos2;
    code1[codepos].pos3 = pos3;
    emitmipsexpression();
}
void emitmipsloadarray(int PO)
{
    if(tab[PO].depth == 0)
    {
        fprintf(fp,"li $s2 %d\n",tab[PO].addr *4);
        fprintf(fp,"lw $s3 %d($sp)\n",code1[codepos].pos2 * 4);
        fprintf(fp,"sll $s3 $s3 2\n");
        fprintf(fp,"addu $s2 $s2 $s3\n");
        fprintf(fp,"lw $s1 0($s2)\n",tab[PO].addr*4);
    }
    else
    {
        fprintf(fp,"li $s2 %d\n",tab[PO].addr *4);
        fprintf(fp,"addu $s2 $s2 $sp\n");
        fprintf(fp,"lw $s3 %d($sp)\n",code1[codepos].pos2 * 4);
        fprintf(fp,"sll $s3 $s3 2\n");
        fprintf(fp,"addu $s2 $s2 $s3\n");
        fprintf(fp,"lw $s1 0($s2)\n",tab[PO].addr*4);
    }

 //   fprintf(fp,"add $s1 $s1 %d\n",code1[codepos].pos2*4);
    fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
}
void emitloadarray(int PO,int lastmodify,int spp)
{
    codepos ++;
    code1[codepos].type = "loadarray";
    code1[codepos].idname = tab[PO].name;
    code1[codepos].pos2 = spp;
    code1[codepos].pos1 = lastmodify;
    emitmipsloadarray(PO);
}
void emitmipslid(int PO)
{
    if(tab[PO].con)
    {
        fprintf(fp,"li $s1 %d\n",tab[PO].constvalue);
    }
    else if(tab[PO].depth == 0)
    {
        fprintf(fp,"lw $s1 %d($0)\n",tab[PO].addr*4);
    }
    else
    fprintf(fp,"lw $s1 %d($sp)\n",tab[PO].addr*4);

    fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
}
void emitload(int PO,int lastmodify)
{
    codepos ++;
    code1[codepos].type = "loadID";
    code1[codepos].idname = tab[PO].name;
    code1[codepos].pos1 = lastmodify;
    emitmipslid(PO);
}
void emitmipslc()
{
    fprintf(fp,"li $s1 %d\n",code1[codepos].pos2);
    fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
}
void emitloadchar(int lastmodify,int a)
{
    codepos ++;
    code1[codepos].type = "loadchar";
    code1[codepos].pos2 = a;
    code1[codepos].pos1 = lastmodify;
    emitmipslc();
}
void emitmipsli()
{
    fprintf(fp,"li $s1 %d\n",code1[codepos].pos2);
    fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
}
void emitloadint(int lastmodify,int a)
{
    codepos ++;
    code1[codepos].type = "loadint";
    code1[codepos].pos2 = a;
    code1[codepos].pos1 = lastmodify;
    emitmipsli();
}
void emitmipsloadw()
{
    fprintf(fp,"lw $s1 %d($sp)\n",code1[codepos].pos2*4);
    fprintf(fp,"lw $s2 %d($sp)\n",code1[codepos].pos1*4);
    fprintf(fp,"sw $s1 0($s2)\n");
}
void emitloadw(int pos1,int pos2)
{
    codepos ++;
    code1[codepos].type = "LW";
    code1[codepos].pos1 = pos1;
    code1[codepos].pos2 = pos2;
    emitmipsloadw();
}
void emitmipsidpos(int PO)
{
    if(tab[PO].depth == 0)
    {
        fprintf(fp,"li $s1 %d\n",tab[PO].addr*4);
        fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
    }
    else
    {
        fprintf(fp,"li $s1 %d\n",tab[PO].addr*4);
        fprintf(fp,"addu $s1 $s1 $sp\n");
        fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
    }
}
void emitidpos(int PO,int pos1)
{
    codepos ++;
    code1[codepos].type = "LoadIdPos";
    code1[codepos].pos1 = pos1;
    code1[codepos].idname = tab[PO].name;
    emitmipsidpos(PO);
}
void emitloadarraypos(int PO)
{
        if(tab[PO].depth == 0)
    {
        fprintf(fp,"li $s1 %d\n",tab[PO].addr*4);
        fprintf(fp,"lw $s3 %d($sp)\n",code1[codepos].pos2*4);
        fprintf(fp,"li $s5 4\n");
        fprintf(fp,"mult $s5 $s3\n");
        fprintf(fp,"mflo $s3\n");
        fprintf(fp,"addu $s1 $s1 $s3\n");
        fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
    }
    else
    {
        fprintf(fp,"li $s1 %d\n",tab[PO].addr*4);
        fprintf(fp,"lw $s3 %d($sp)\n",code1[codepos].pos2*4);
        fprintf(fp,"li $s5 4\n");
        fprintf(fp,"mult $s5 $s3\n");
        fprintf(fp,"mflo $s3\n");
        fprintf(fp,"addu $s1 $s1 $s3\n");
        fprintf(fp,"addu $s1 $s1 $sp\n");
        fprintf(fp,"sw $s1 %d($sp)\n",code1[codepos].pos1*4);
    }
}
void emitarraypos(int PO,int pos1,int pos2)
{
    codepos ++;
    code1[codepos].type = "LoadArrayPos";
    code1[codepos].pos1 = pos1;
    code1[codepos].pos2 = pos2;
    emitloadarraypos(PO);
}
void emitmipstag()
{
    fprintf(fp,"tag%d:\n",code1[codepos].pos1);
}
void emittag(int pos)
{
    codepos ++;
    code1[codepos].type = "tag:";
    code1[codepos].pos1 = pos;
    emitmipstag();
}
void emitmipsjump()
{
    fprintf(fp,"j tag%d\n",code1[codepos].pos1);
}
void emitjump(int tag)
{
    codepos ++;
    code1[codepos].type = "JUMP";
    code1[codepos].pos1 = tag;
    emitmipsjump();
}
void emitmipsbeq()
{
    fprintf(fp,"lw $s1 %d($sp)\n",((code1[codepos].pos1)*4));
    fprintf(fp,"lw $s2 %d($sp)\n",((code1[codepos].pos2)*4));
    fprintf(fp,"beq $s1 $s2 tag%d\n",code1[codepos].pos3);
}
void emitbeq(int pos1,int pos2,int pos3)
{
    codepos ++;
    code1[codepos].type = "BEQ";
    code1[codepos].pos1 = pos1;
    code1[codepos].pos2 = pos2;
    code1[codepos].pos3 = pos3;
    emitmipsbeq();
}
void emitmipsless()
{
    fprintf(fp,"lw $s1 %d($sp)\n",((code1[codepos].pos1)*4));
    fprintf(fp,"lw $s2 %d($sp)\n",((code1[codepos].pos2)*4));
    fprintf(fp,"li $s3 0\n");
    fprintf(fp,"slt $s3 $s1 $s2\n");
    fprintf(fp,"beq $s3 $0 tag%d\n",code1[codepos].pos3);
}
void emitless(int pos1,int pos2,int pos3)
{
    codepos ++;
    code1[codepos].type = "Bless";
    code1[codepos].pos1 = pos1;
    code1[codepos].pos2 = pos2;
    code1[codepos].pos3 = pos3;
    emitmipsless();
}
void emitmipslesseq()
{
    fprintf(fp,"lw $s1 %d($sp)\n",((code1[codepos].pos1)*4));
    fprintf(fp,"lw $s2 %d($sp)\n",((code1[codepos].pos2)*4));
    fprintf(fp,"li $s3 0\n");
    fprintf(fp,"slt $s3 $s2 $s1\n");
    fprintf(fp,"bne $s3 $0 tag%d\n",code1[codepos].pos3);
}
void emitlesseq(int pos1,int pos2,int pos3)
{
    codepos ++;
    code1[codepos].type = "Blesseq";
    code1[codepos].pos1 = pos1;
    code1[codepos].pos2 = pos2;
    code1[codepos].pos3 = pos3;
    emitmipslesseq();
}
void emitmipsmore()
{
    fprintf(fp,"lw $s1 %d($sp)\n",((code1[codepos].pos1)*4));
    fprintf(fp,"lw $s2 %d($sp)\n",((code1[codepos].pos2)*4));
    fprintf(fp,"li $s3 0\n");
    fprintf(fp,"slt $s3 $s2 $s1\n");
    fprintf(fp,"beq $s3 $0 tag%d\n",code1[codepos].pos3);
}
void emitmore(int pos1,int pos2,int pos3)
{
    codepos ++;
    code1[codepos].type = "Bmore";
    code1[codepos].pos1 = pos1;
    code1[codepos].pos2 = pos2;
    code1[codepos].pos3 = pos3;
    emitmipsmore();
}
void emitmipsmoreeq()
{
    fprintf(fp,"lw $s1 %d($sp)\n",((code1[codepos].pos1)*4));
    fprintf(fp,"lw $s2 %d($sp)\n",((code1[codepos].pos2)*4));
    fprintf(fp,"li $s3 0\n");
    fprintf(fp,"slt $s3 $s1 $s2\n");
    fprintf(fp,"bne $s3 $0 tag%d\n",code1[codepos].pos3);
}
void emitmoreeq(int pos1,int pos2,int pos3)
{
    codepos ++;
    code1[codepos].type = "Bmoreeq";
    code1[codepos].pos1 = pos1;
    code1[codepos].pos2 = pos2;
    code1[codepos].pos3 = pos3;
    emitmipsmoreeq();
}
void emitmipsbsingle()
{
    fprintf(fp,"lw $s1 %d($sp)\n",((code1[codepos].pos1)*4));
    fprintf(fp,"beq $s1 $0 tag%d\n",code1[codepos].pos3);
}
void emitsingle(int pos,int tag)
{
    codepos ++;
    code1[codepos].type = "Bsingle";
    code1[codepos].pos1 = pos;
    code1[codepos].pos3 = tag;
    emitmipsbsingle();
}
void emitmipsbne()
{
    fprintf(fp,"lw $s1 %d($sp)\n",((code1[codepos].pos1)*4));
    fprintf(fp,"lw $s2 %d($sp)\n",((code1[codepos].pos2)*4));
    fprintf(fp,"bne $s1 $s2 tag%d\n",code1[codepos].pos3);
}
void emitbne(int pos1,int pos2,int pos3)
{
    codepos ++;
    code1[codepos].type = "BNE";
    code1[codepos].pos1 = pos1;
    code1[codepos].pos2 = pos2;
    code1[codepos].pos3 = pos3;
    emitmipsbne();
}
void emitmipsreturn()
{
fprintf(fp,"lw $31 4($sp)\n");
 fprintf(fp,"addi $sp $sp %d\n",alloc_size);
 fprintf(fp,"jr $31\n");
}
void emitreturn()
{
    codepos ++;
    code1[codepos].type = "RET";
    emitmipsreturn();
}
void emitmipscall(int PO)
{
    fprintf(fp,"sw $31 4($sp)\n");
    fprintf(fp,"subi $sp $sp %d\n",alloc_size);
    fprintf(fp,"jal tag%d\n",tab[PO].position);
}
void emitcall(int PO)
{
    codepos ++;
    code1[codepos].type = "CALL";
    code1[codepos].idname = tab[PO].name;
    emitmipscall(PO);
}
void emitrere()
{
    //cout<<"REEEEEEEEEEEEEREEEEEEEEEEEEEE!"<<endl;
    fprintf(fp,"lw $31 4($sp)\n");
}
void emitmipsmain()
{
    fprintf(fp,"main:\n");
}
void emitmaintag()
{
    codepos ++;
    code1[codepos].type = "MAIN";
    emitmipsmain();
}
void emitmipsjmain()
{
    fprintf(fp,"jal main\n");
    fprintf(fp,"j end\n");
}
void emitend()
{
    fprintf(fp,"end:\n");
}
void emitjmain()
{
    codepos ++;
    code1[codepos].type = "J";
    code1[codepos].idname = "main";
    emitmipsjmain();
}
void emitmipscallmain()
{
    fprintf(fp,"li $sp 0x00002ffc\n");
    fprintf(fp,"subi $sp $sp %d\n",alloc_size);
}
void emitcallmain()
{
    codepos ++;
    code1[codepos].type = "callmain";
    emitmipscallmain();
}

void emitmipscallpre()
{
}
void emitcallpre()
{
    codepos ++;
    code1[codepos].type = "call_pre";
    emitmipscallpre();
}
void mipsfillpos(int pos1,int pos2)
{
    fprintf(fp,"lw $s1 %d($sp)\n",pos2*4);
    fprintf(fp,"sw $s1 %d($sp)\n",(- alloc_size + 8 + pos1*4));
}
int solve_if()
{
    cout<<"第"<<line[pos]<<"为if语句"<<endl;
    int tag;
    int tt1,tt2,tt3;
    int lastmodify,lastmodify2 = 0;
//storeposition
    sumtag ++;
    tt1 = sumtag;
    sumtag ++;
    tt2 = sumtag;
    tag = nextsym();
    if(tag != lpartag)
    {
       // error();
    }
    storeposition ++;
    lastmodify = storeposition + 1;
    tag = solve_expression();
    //tag = nextsym();
    //emit();//生成跳转语句
    //if(tag == equtag){//cout<<"Yes, party time!"<<endl;
    //tag = solve_expression();}
    if(tag == moretag){storeposition ++; lastmodify2 = storeposition + 1; tag = solve_expression();emitmore(lastmodify,lastmodify2,tt1);}
    else if(tag == moreeqtag){storeposition ++; lastmodify2 = storeposition + 1; tag = solve_expression();emitmoreeq(lastmodify,lastmodify2,tt1);}
    else if(tag == lesstag){storeposition ++; lastmodify2 = storeposition + 1; tag = solve_expression();emitless(lastmodify,lastmodify2,tt1);}
    else if(tag == leseqtag){storeposition ++; lastmodify2 = storeposition + 1; tag = solve_expression();emitlesseq(lastmodify,lastmodify2,tt1);}
    else if(tag == equtag){storeposition ++;lastmodify2 = storeposition+1;tag = solve_expression();emitbne(lastmodify,lastmodify2,tt1);}
    else if(tag == noteqtag){storeposition ++;lastmodify2 = storeposition+1;tag = solve_expression();emitbeq(lastmodify,lastmodify2,tt1);}
    else {emitsingle(lastmodify,tt1);}
    if(tag != rpartag)error();

    solve_sentence();
    emitjump(tt2);
    emittag(tt1);
   // cout<<"waxiue"<<code[pos]<<endl;
    tag = nextsym();
    if(tag != elsetag){error;}
    tag =  solve_sentence();
    emittag(tt2);
    cout<<line[pos]<<endl;
    return tag;
    //在这里需要补充跳转后的位置
}

int solve_switch()
{
    cout<<"第"<<line[pos]<<"为switch语句"<<endl;

    int a = nextsym();
    if(a != lpartag)error();
    storeposition ++;
    int popo1 = storeposition + 1;
    a = solve_expression();
    if(a != rpartag){error();cout<<"卡卡卡卡卡卡卡"<<endl;}
    a = nextsym();
    if(a != LPtag){error();
    //cout<<"汪汪汪汪无无"<<endl;
    }
    a = nextsym();
    sumtag ++;
    int tagend = sumtag;
   // cout<<a<<' '<<casetag<<' '<<idtag<<endl;
    while(a == casetag)
    {
        //a = nextsym();
        //if(a != numtag)error();
        sumtag ++;
       int ttaagg = sumtag;
        storeposition = popo1;
        int popo2 = popo1 + 1;
        a = solve_expression();
        emitbne(popo1,popo2,ttaagg);
        //a = nextsym();
        if(a != colontag)
        {
            error();
        }
        a = solve_sentence();
        emitjump(tagend);
        emittag(ttaagg);
        a = nextsym();
    }

    if(a == defaulttag)
    {
        a = nextsym();
        if(a != colontag)
        {
            error();
        }
        a = solve_sentence();
        a = nextsym();
    }emittag(tagend);
    if(a != RPtag)error();

    return a;

}
int simplelastpos;
int solve_simple(string lasttype,int lastpos)
{
    int a = nextsym(),type;
    int popopos = storeposition + 1;
    int inipos = lastpos;
    if(a == lpartag)
    {
        popopos = storeposition + 1;
        a = solve_expression();if(a != rpartag)error();a = nextsym();
        emitexpression(lasttype,inipos,inipos,popopos);
        storeposition ++;
    }
    else
    {
        int PP ;
    if(a != idtag && a != numtag && a != CHtag && a != chartag&& a != plustag && a != minustag){error("表达式乘除法后应该跟变量");}
    if(a == idtag)
    {
       type = find_tab(id);
    PP = tab_pos;
    }
    else type = 0;
    if(type == intarraytype || type == chararraytype || type == lpartag)
    {

        //cout<<"Yes!"<<endl;
        a = nextsym();
        if(a != lmidtag)error("数组维数问题");
        int fff = 0;
        storeposition ++;
        popopos = storeposition + 1;
        while(a == lmidtag)
        {
        fff ++;
        a = solve_expression();
        //a = nextsym();
        if(a != rmidtag)error();
        a = nextsym();
        }storeposition ++;

        emitloadarray(PP,popopos - 1,popopos);
        emitexpression(lasttype,inipos,inipos,popopos - 1);
        storeposition ++ ;
        if(fff != 1)error("数组维数有问题");
    }
    else if(type == voidtag || type == intretag || type == charretag)
                {
                    popopos = storeposition + 1;
                    storeposition ++;
                    int i;
                    if(tab[PP].size != 0)
                    {
                        a = nextsym();
                        int popping = storeposition + 1;
                        int popping1 = popping;
                        if(a != lpartag)error("函数调用缺少左括号!!");
                        for(i = 1;i <= tab[PP].size;i ++)
                        {

                            a = solve_expression();
                            if(a != commatag && i != tab[PP].size)error();
                           // mipsfillpos(i-1,poppin);
                            storeposition = popping ;
                            popping = storeposition + 1;
                        }
                        for(i = popping1;i < popping;i ++)
                        {
                            mipsfillpos(i-popping1,i);
                        }
                        if(a != rpartag)error("函数调用缺少右括号");
                        emitcall(PP);
                        emitrere();
                        emitmfret(popopos);
                        emitexpression(lasttype,inipos,inipos,popopos);

                    }
                    else
                    {
                        emitcall(PP);
                        emitrere();
                        emitmfret(popopos);
                        emitexpression(lasttype,inipos,inipos,popopos);
                    }
                        a = nextsym();
                }
     else if(type == inttag || type == chartag)
        {
            popopos = storeposition + 1;
            storeposition ++;
            emitload(PP,popopos);
            emitexpression(lasttype,inipos,inipos,popopos);
            a = nextsym();

        }

   else
    {
           if(a == CHtag)
            {
                popopos = storeposition + 1;
                storeposition ++;
                emitloadchar(popopos,string_1[0]);
                emitexpression(lasttype,inipos,inipos,popopos);

            }
            else if(a == numtag)
            {
                popopos = storeposition + 1;
                storeposition ++;
                emitloadint(popopos,Int_Value);
                emitexpression(lasttype,inipos,inipos,popopos);
            }
            else if(a == plustag || a == minustag)
            {
                int aa = a;
                a = nextsym();
                if(a != numtag)error("应该接整数!");
                popopos = storeposition + 1;
                storeposition ++;
                if(aa == minustag)
                    emitloadint(popopos,-Int_Value);
                else emitloadint(popopos,Int_Value);
                emitexpression(lasttype,inipos,inipos,popopos);
            }
            else error("类型有问题!(○｀ 3′○)");
           a = nextsym();
       //    storeposition  ++;
       }
    }
    //cout<<"????"<<endl;
    while(a == startag || a == divtag)
    {
        int PP;
       if(a == startag || a == divtag)
        {

           if(a == startag)lasttype = "MULT";
           else lasttype = "DIV";
            a = nextsym();
       if(a == idtag)
       {
           type = find_tab(id);
            PP = tab_pos;
       }

    else type = 0;
    if(a == lpartag)
    {
        popopos = storeposition + 1;
        a = solve_expression();
        if(a != rpartag)error("缺少右小括号");
         emitexpression(lasttype,inipos,inipos,popopos);
        storeposition ++;
        a = nextsym();
    }
    else if(type == intarraytype || type == chararraytype)
    {
        a = nextsym();
        if(a != lmidtag)error();
        int fff = 0;
        storeposition ++;
        popopos = storeposition + 1;
        //storeposition ++;
        while(a == lmidtag)
        {
        fff ++;
        a = solve_expression();
        //a = nextsym();
        if(a != rmidtag)error();
        a = nextsym();
        }emitloadarray(PP,popopos - 1,popopos);
        emitexpression(lasttype,inipos,inipos,popopos - 1);
        if(fff != 1)error("数组维数有问题");
    }
    else if(type == voidtag || type == intretag || type == charretag)
                {
                    int i;
                    popopos = storeposition + 1;
                    storeposition ++;
                    if(tab[PP].size != 0)
                    {
                        a = nextsym();
                        int popping = storeposition + 1;
                        int popping1 = popping;
                        if(a != lpartag)error("函数调用缺少左括号!!");
                        for(i = 1;i <= tab[PP].size;i ++)
                        {

                            a = solve_expression();
                            if(a != commatag && i != tab[PP].size)error();
                           // mipsfillpos(i-1,poppin);
                            storeposition = popping ;
                            popping = storeposition + 1;
                        }
                        for(i = popping1;i < popping;i ++)
                        {
                            mipsfillpos(i-popping1,i);
                        }
                        if(a != rpartag)error("函数调用缺少右括号");
                        emitcall(PP);
                        emitrere();
                        emitmfret(popopos);
                        emitexpression(lasttype,inipos,inipos,popopos);
                        storeposition = popping1 - 2;
                    }
                    else
                    {
                        emitcall(PP);
                        emitrere();
                        emitmfret(popopos);
                        emitexpression(lasttype,inipos,inipos,popopos);
                    }
                        a = nextsym();
                }
    else if(type == inttag || type == chartag)
        {
            popopos = storeposition + 1;
            storeposition ++;
            emitload(PP,popopos);
            emitexpression(lasttype,inipos,inipos,popopos);
            a = nextsym();

        }
   else
    {
           if(a == CHtag)
            {
                popopos = storeposition + 1;
                storeposition ++;
                emitloadchar(popopos,string_1[0]);
                emitexpression(lasttype,inipos,inipos,popopos);

            }
            else if(a == numtag)
            {
                popopos = storeposition + 1;
                storeposition ++;
                emitloadint(popopos,Int_Value);
                emitexpression(lasttype,inipos,inipos,popopos);
            }
            else if(a == plustag || a == minustag)
            {
                int aa = a;
                a = nextsym();
                if(a != numtag)error("应该接整数!");
                popopos = storeposition + 1;
                storeposition ++;
                if(aa == minustag)
                    emitloadint(popopos,-Int_Value);
                else emitloadint(popopos,Int_Value);
                emitexpression(lasttype,inipos,inipos,popopos);
            }
            else error("类型有问题!(○｀ 3′○)");
           a = nextsym();
       //    storeposition  ++;
       }
        //else error();
        }
    }
  //  cout<<"outside simple!"<<endl;
    return a;

}
void mipsstart()
{
    fprintf(fp,"sw $31 4($sp)\n");
}
int solve_expression()
{
    int charsost = 1;
    int sumcha = 0;
   // cout<<"哈哈哈哈哈哈哈哈expression!"<<endl;
   int spo = storeposition + 1;
   storeposition ++;
    int poss = pos;
    int start_pos = pos;
    int a = nextsym(),type;
    string lasttype = "ADD";
    int lastmodify = 0;//storeposition + 1;////////////
    emitloadint(spo,0);
    //emitloadint(0,0);
   // emitloadint(lastmodify,0);///////////
    storeposition ++;
    bool tata = 0;
    if(a == idtag || a == numtag || a == CHtag || a == lpartag )
    {
        lastmodify = storeposition + 1;
        tata = 1;
     if(a == lpartag)
     {
         if(a == lpartag)
        {
            tata = 1;
            a = solve_expression();
            //lastmodify = store_position;
            if(a != rpartag)error();
            a = nextsym();
        }
     }
      else if(a == idtag)
      {
          int type1 = find_tab(id);
          int PO = tab_pos;
          if(type1 == intarraytype || type1 == chararraytype)
        {
            if(type1 == intarraytype)charsost = 0;
            else sumcha ++;
            a = nextsym();
            if(a != lmidtag)error("应输入数组的维数");
            storeposition ++;
            int spp = storeposition + 1;
            int fff = 0;
            while(a == lmidtag)
            {
                fff ++;

                a = solve_expression();
                if(a != rmidtag)error();
                a = nextsym();
            }
            if(fff != 1)error("数组维数有问题");
            emitloadarray(PO,lastmodify,spp);

        }else if(type1 == voidtag || type1 == intretag || type1 == charretag)
                {
                    if(type1 != charretag)charsost = 0;
                    else sumcha ++;
                    if(type1 == voidtag)error("不应该调用无返回值的函数!");
                    int i;
                    if(tab[PO].size != 0)
                    {
                        storeposition ++;
                        int popping = storeposition + 1;
                        int popping1 = popping;
                        a = nextsym();
                        if(a != lpartag)error("函数调用缺少左括号!!!");
                        for(i = 1;i <= tab[PO].size;i ++)
                        {
                            a = solve_expression();
                            if(a != commatag && i != tab[PO].size)error();
                            storeposition = popping;
                            popping = storeposition + 1;
                            //mipsfillpos(i-1,popping);
                        }
                        for(i = popping1;i < popping;i ++)
                            mipsfillpos(i-popping1,i);
                        storeposition = popping1 - 2;
                        emitcall(PO);
                        emitrere();
                        emitmfret(lastmodify);

                        if(a != rpartag)error("函数调用缺少右括号");
                } else
                {
                emitcall(PO);
                        emitrere();
                        emitmfret(lastmodify);
                }
                a = nextsym();
                }
        else
        {
            if(tab[PO].type != chartag)charsost = 0;
            else sumcha ++;
            emitload(PO,lastmodify);
            a = nextsym();
        }
       }else
       {
           if(a == CHtag)
            {
                sumcha ++;
                emitloadchar(lastmodify,string_1[0]);
            }
            else if(a == numtag)
            {
                charsost = 0;
                emitloadint(lastmodify,Int_Value);
            }
            else if(a == plustag || a == minustag)
            {
                charsost = 0;
                int aa = a;
                a = nextsym();
                if(aa == plustag)
                emitloadint(lastmodify,Int_Value);
                else
                emitloadint(lastmodify,-Int_Value);
            }
            else error("类型有问题!(○｀ 3′○)");
           a = nextsym();
       }
        storeposition ++;
    }
    while( a == plustag || a == minustag  || a == startag || a == divtag)
    {
        if(a == startag || a == divtag)
        {
            charsost = 0;
            if(!tata)error("不能以乘除法开头");
            string llss;
            if(a == startag)llss = "MULT";
            else llss = "DIV";
            a = solve_simple(llss,lastmodify);
        }
        else
        {
            tata = 1;
            emitexpression(lasttype,spo,spo,lastmodify);
            if(a == plustag)lasttype = "ADD";
            else if(a == minustag)lasttype = "MINUS";
            a = nextsym();
            if(a == lpartag)
            {
                lastmodify = storeposition + 1;
                a = solve_expression();
                //lasttype =
            if(a != rpartag)error("缺少右小括号");
            a = nextsym();
            }
            else
            {
            if(a == numtag || a == idtag || a == CHtag|| a == plustag|| a == minustag)
            {
        if(a == idtag)
      {
          int type1 = find_tab(id);
          int PO = tab_pos;
          lastmodify = storeposition + 1;
          if(type1 == intarraytype || type1 == chararraytype)
        {
            if(type1 == intarraytype)charsost = 0;
            else sumcha ++;
            a = nextsym();
            if(a != lmidtag)error("数组维数问题!");
            int fff = 0;
            storeposition ++;
            int spp = storeposition + 1;
            while(a == lmidtag)
            {
                fff ++;
                a = solve_expression();
                if(a != rmidtag)error("右中括号问题");
                a = nextsym();
            }
            if(fff != 1)error("数组维数有问题");
            emitloadarray(PO,lastmodify,spp);
        }
        else if(type1 == voidtag || type1 == intretag || type1 == charretag)
                {
                    if(type1 != charretag)charsost = 0;
                    else sumcha ++;
                    storeposition ++;
                    int popping = storeposition + 1;
                    int popping1 = popping;
                    if(type1== voidtag)error("不应该调用无返回值函数!");
                    int i;
                    if(tab[PO].size != 0)
                    {
                        a = nextsym();
                        if(a != lpartag)error("函数调用缺少左括号!!!!");
                        for(i = 1;i <= tab[PO].size;i ++)
                        {
                            a = solve_expression();
                            //mipsfillpos(i-1,popping);
                            storeposition = popping;
                            popping = storeposition +1;
                            if(a != commatag && i != tab[PO].size)error();
                        }
                        for(i = popping1;i < popping;i ++)
                            mipsfillpos(i-popping1,i);
                        storeposition = popping1 - 2;
                        if(a != rpartag)error("函数调用缺少右括号");
                    } a = nextsym();emitcall(PO);emitrere();emitmfret(lastmodify);
                }//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        else
        {
            if(tab[PO].type != chartag)charsost = 0;
            else sumcha ++;
            emitload(PO,lastmodify);
            a = nextsym();
        }
       }else
       {    if(a == CHtag)
            {
                sumcha ++;
                lastmodify = storeposition + 1;
                emitloadchar(lastmodify,string_1[0]);
            }
            else if(a == numtag)
            {
                charsost = 0;
                lastmodify = storeposition + 1;
                emitloadint(lastmodify,Int_Value);
            }
            else if(a == plustag || a == minustag)
            {
              //  cout<<"?????????????????????"<<endl;
                charsost = 0;
                int aa = a;
                a = nextsym();
                lastmodify = storeposition + 1;
                if(aa == plustag)
                emitloadint(lastmodify,Int_Value);
                else
                emitloadint(lastmodify,-Int_Value);
            }
            else
            {cout<<a<<endl;error("类型有问题!(○｀ 3′○)");}
           a = nextsym();
       }storeposition ++;
            }else error("表达式格式有问题");

            }
        }

    }
    emitexpression(lasttype,spo,spo,lastmodify);
    charsostrong = charsost;
    sumchar = sumcha;
    cout<<"expression:";
    for(int i = poss;i < pos;i ++)cout<<code[i];cout<<endl;
    //cout<<"outside expression!"<<endl;
    return a;

}

void solve_assign()
{
    cout<<"第"<<line[pos]<<"行为赋值语句!"<<endl;
    int type = find_tab(id);
    int PO = tab_pos,fff = 0;
    //cout<<tab[PO].name<<' '<<tab[PO].size<<endl;
    int a;
    int assignpos1,assignpos2;
    if(type == intarraytype || type == chararraytype)
        {
      //      cout<<"Yes!"<<endl;
            a = nextsym();
            int pos_expcode1 = storeposition + 1;
            while(a == lmidtag)//error();
            {

                a = solve_expression();
                if(a != rmidtag)error();
                a = nextsym();
                fff ++;
            }
            //
            if(fff != 1)error("等号左边数组维数有问题");
            storeposition ++;
            emitarraypos(PO,storeposition,pos_expcode1);
        }
        //需要存储下地址之类的
        //cout<<"呱呱呱"<<endl;
        else
        {   storeposition ++;
            emitidpos(PO,storeposition);
            a = nextsym();}
     //   cout<<a<<' '<<assigntag<<endl;
        if(a != assigntag)
            {error("等号问题");}
            assignpos1 = storeposition;
            assignpos2 = storeposition + 1;
            //storeposition ++;
        a = solve_expression();
            emitloadw(assignpos1,assignpos2);
       // emit();
        if(a != semitag)error("分号不对!");
       // cout<<"退出呱呱呱"<<endl;

}
void solve_while()
{
    cout<<"第"<<line[pos]<<"行为while语句!"<<endl;
    int lastmodify,lastmodify2 = 0;
    int tt1,tt2;
//storeposition
    sumtag ++;
    tt1 = sumtag;
    sumtag ++;
    tt2 = sumtag;
    emittag(tt2);
    int a = nextsym();
    if(a != lpartag)error();
    //storeposition ++;
    lastmodify = storeposition + 1;
    a = solve_expression();

  //  a = nextsym();
    if(a != rpartag)
    {
       // cout<<"wawawaawa"<<endl;
        if(a == equtag)
        {
            storeposition ++;
            lastmodify2 = storeposition+1;
            a = solve_expression();
            emitbne(lastmodify,lastmodify2,tt1);
        }
        else if(a == lesstag)
        {
            storeposition ++;
            lastmodify2 = storeposition+1;
            a = solve_expression();
            emitless(lastmodify,lastmodify2,tt1);
        }
        else if(a == leseqtag)
        {
            storeposition ++;
            lastmodify2 = storeposition+1;
            a = solve_expression();
            emitlesseq(lastmodify,lastmodify2,tt1);
        }
        else if(a == moretag)
        {
            storeposition ++;
            lastmodify2 = storeposition+1;
            a = solve_expression();
            emitmore(lastmodify,lastmodify2,tt1);
        }
        else if(a == moreeqtag)
        {
            storeposition ++;
            lastmodify2 = storeposition+1;
            a = solve_expression();
            emitmoreeq(lastmodify,lastmodify2,tt1);
        }
        else if(a == noteqtag)
        {
            storeposition ++;
            lastmodify2 = storeposition+1;
            a = solve_expression();
            emitbeq(lastmodify,lastmodify2,tt1);
        }
        else error();
        //a = solve_expression();
        //a = nextsym();
        if(a != rpartag)
            error();
        //solve_expression();
    }else{emitsingle(lastmodify,tt1);}
    solve_sentence();
    emitjump(tt2);
    emittag(tt1);


}
int solve_const(int a)
{
    cout<<"第"<<line[pos]<<"行为const声明语句!"<<endl;
    while(a == consttag)
    {
        int type;
       a = nextsym();
        type = a;       //记录类型!!!!!!!!!!!!!!!!!!
       a = nextsym();

       //cout<<a<<' '<<idtag<<endl;
       if(a != idtag)error();
       int PO = filltab(type,depth,id);
       tab[PO].con= 1;

       a = nextsym();
       if(a != assigntag)error();
       a = nextsym();
       int nunu = 1;
       if(a == plustag || a == minustag)
       {
           nunu = (a == minustag)?-1:1;
           a = nextsym();
           if(a != numtag )
           {
                error();
           }

           //if(num == 0)error();
       }//filltab!!!!!!!!!!!!!!!!!!!
      if(a != numtag && a != CHtag)error();
      if(a == numtag)
        tab[PO].constvalue = nunu * Int_Value;
    else
        tab[PO].constvalue = string_1[0];
       a = nextsym();
       if(a == commatag)
       {
      //     cout<<"comma right!"<<endl;
           while(a == commatag)
           {
                a = nextsym();
                if(a != idtag)error();
                int PO = filltab(type,depth,id);
                tab[PO].con= 1;
                a = nextsym();
                if(a != assigntag)error();
                a = nextsym();
                int nunu = 1;
                if(a == plustag || a == minustag)
                {
                    nunu = (a == minustag)?-1:1;
                    a = nextsym();
                    if(a != numtag )
                    {
                        error();
                    }
           //if(num == 0)error();
                }//filltab
                if(a != numtag && a != CHtag)error();
                if(a == numtag)
                    tab[PO].constvalue = nunu * Int_Value;
                else
                    tab[PO].constvalue = string_1[0];
                a = nextsym();
           }
       }
        if(a != semitag)error();
        //filltab();
        a = nextsym();
    }return a;

}

int solve_statement(int a)
{
  cout<<"第"<<line[pos]<<"行为变量语句!"<<endl;
    while(a == inttag || a == chartag)
    {
        int poppop = pos;
        int type = a;
       a = nextsym();
       if(a != idtag)error();
       string idid = id;
        a = nextsym();
        if(a == LPtag || a == lpartag)
        {
            pos = poppop;
            return type;
        }int PO = filltab(type,depth,idid);
        int gg = 0;
        while(a == lmidtag)
        {
            gg ++;
            a = nextsym();
            if(a != numtag)error();
            tab[PO].arr[gg] = Int_Value;
            tab[PO].size = Int_Value;
            if(tab[PO].size == 1)tab[PO].size ++;
            //if(int == 0)error()
            a = nextsym();
            if(a != rmidtag)error();
            a = nextsym();
        }//tab[PO].size = gg;
        while(a == commatag)

       { a = nextsym();
           if(a != idtag)error("bu");
           int PO = filltab(type,depth,id);
        a = nextsym();
        int gg = 0;
        while(a == lmidtag)
        {
            gg ++;
            a = nextsym();
            if(a != numtag)error();
            if(Int_Value == 0)error("数组大小不应为0");
            tab[PO].arr[gg] = Int_Value;
            tab[PO].size = Int_Value;
            if(tab[PO].size == 1)tab[PO].size ++;
            a = nextsym();
            if(a != rmidtag)error();
            a = nextsym();
        }//filltab
        //tab[PO].size = gg;
       }if(a != semitag)error("que");

     //  next();       //记录类型!!!!!!!!!!!!!!!!!!
    a = nextsym();

    }//return nextsym();
    return a;

}

void solve_printf()
{
     cout<<"第"<<line[pos]<<"行为printf语句!"<<endl;
    int a = nextsym();
    if(a != lpartag)error();
    int nowpos = pos;
    a = nextsym();
    if(a != stringtag)
    {
        pos = nowpos;
        storeposition ++;
        int yes = storeposition + 1;
        charsostrong = 1;
        sumchar = 0;
        a = solve_expression();
        cout<<charsostrong<<' '<<sumchar<<"SSSSSSSSSSSSSSSSSSOOOOOOOOOOOOOOOOOOOOOOOO"<<endl;
        if((!charsostrong)||(sumchar != 1))
        emitprintfex(yes);
        else emitprintfchar(yes);
        if(a != rpartag)error();
        a = nextsym();
    }
    else
    {
        emitprintfstring();
        a = nextsym();
        if(a == commatag)
        {
            storeposition ++;
            int yes = storeposition + 1;
            charsostrong = 1;
            sumchar = 0;
        a = solve_expression();
        if((!charsostrong)||(sumchar != 0))
        emitprintfex(yes);
        else emitprintfchar(yes);
        }
        if(a != rpartag)error("输出语句缺少右括号");
        a = nextsym();
    }
    if(a != semitag)error("输出语句缺少分号");

}
void solve_scanf()
{
     cout<<"第"<<line[pos]<<"行为scanf语句!"<<endl;
    int a = nextsym();
    if(a != lpartag)error();
    a = nextsym();
    if(a != idtag)error();
    find_tab(id);
    int PO = tab_pos;
    emitscanf(PO);
    a = nextsym();
    cout<<"SCANF"<<endl;
    while(a == commatag)
    {
        a = nextsym();
        if(a != idtag)error();
        find_tab(id);
        PO = tab_pos;
        emitscanf(PO);
        a = nextsym();
    }
    if(a != rpartag)error();
    a = nextsym();
    if(a != semitag)error();
}
void solve_return()
{
     cout<<"第"<<line[pos]<<"行为return语句!"<<endl;
    // int popo = pos;
    int a = nextsym();
    if(a == semitag){emitreturn(); return;}
    //cout<<"fafafa"<<endl;
  //  cout<<"STO:"<<storeposition <<endl;
    if(a != lpartag)error();
    storeposition ++;
    int sp = storeposition + 1;
    a = solve_expression();
    emitret_value(sp);
    if(a != rpartag)error();
    a = nextsym();
    if(a != semitag)error();
    emitreturn();
}
void solve_statement_strong(int a)
{
    int type = a;

     cout<<"第"<<line[pos]<<"行为函数声明语句!"<<endl;
     int lastpos = pos;
    a = nextsym();
    int PO = filltab(type,0,id);
    tab[PO].ret = 1;
    int hehe = 0;
    sumtag ++;
    emittag(sumtag);
    tab[PO].position = sumtag;
    if(a != lpartag)
    {
        pos = lastpos;
        tab[PO].size = 0;
       // cout<<"emmmm?"<<endl;
        solve_sentence(1);
    }
    else
    {
        hehe ++;

        a = nextsym();
        int tyty;
        if(a != chartag && a != inttag)error();
        tyty = a;
        tab[PO].arr[hehe] = a;
        a = nextsym();
        if(a != idtag)error();filltab(tyty,1,id);
        a = nextsym();
        while(a == commatag)
        {
            hehe ++;
             a = nextsym();
             tyty = a;
             tab[PO].arr[hehe] = a;
        if(a != chartag && a != inttag)error();
            a = nextsym();filltab(tyty,1,id);
            if(a != idtag)error();
            a = nextsym();
        }
        if(a != rpartag)error();
        tab[PO].size = hehe;
        solve_sentence(1);
    }
}
int st_use;
int solve_sentence(bool ish)
{
    int a = nextsym();
    //int b;
    int pos1 = pos;
    int pos2;
    if(a != LPtag)
    {
 switch (a)
        {
        case iftag:
            {
                cout<<"if"<<endl;
                solve_if();
                //cout<<"eeeeeeeeeeeeennnnnnnnnnnnnnnnnnndddddddddddd"<<endl;
                //cout<<code[pos - 3]<<code[pos - 2]<<code[pos - 1]<<endl;
                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case whiletag:
            {
                cout<<"while"<<endl;
                solve_while();
                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case idtag:
            {
                cout<<"id"<<endl;

    //            cout<<"emmmmmmmm"<<endl;
                int type = find_tab(id);
                int PO = tab_pos;
                //cout<<type<<endl;
                //cout<<tab[PO].ret<<endl;
                if(type == voidtag || type == intretag || type == charretag)
                {
                    //cout<<"MMMMMMMMMMMMMMMMMMMMMMMMMMM"<<endl;
                    int i;
                    emitcallpre();
                    if(tab[PO].size != 0)
                    {
                       // cout<<tab[PO].size<<endl;
                        storeposition ++;
                        int ss = storeposition + 1;
                        int ss1 = ss;
                        a = nextsym();
                        if(a != lpartag)error("函数调用缺少左括号!!!!!");
                        for(i = 1;i <= tab[PO].size;i ++)
                        {
                            storeposition = ss;
                            ss = storeposition + 1;
                            a = solve_expression();
                            //mipsfillpos(i-1,ss);
                            storeposition = ss;
                            if(a != commatag && i != tab[PO].size)error();
                        }
                        for(i = ss1+1;i <= ss;i ++)
                        {
                            mipsfillpos(i-ss1-1,i);
                        }
                            int ssv,ssd;
                        for(int j = PO;tab[j].depth == 1;j ++)
                        {
                            ssv = tab[j].addr + ((tab[j].ret)?0:tab[j].size);
                        }
                        if(a != rpartag)error("函数调用缺少右括号");

                    } emitcall(PO);
                    //cout<<"???????!!!!!!!!!!!!"<<endl;
                        emitrere();
                        a = nextsym();
                        if(a != semitag)error("函数调用缺少分号");

                }
                else
                 solve_assign();

                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case printftag:
            {
                cout<<"printf"<<endl;

                solve_printf();
                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case scanftag:
            {
                cout<<"scanf"<<endl;
                solve_scanf();
                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case returntag:
            {
                cout<<"return"<<endl;
                solve_return();
                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case LPtag:
            {
              //  cout<<"LP"<<endl;
               a = solve_sentence();
                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case switchtag:
            {
                //cout<<"!!!!!!!!!!!!!!!!!!!!!!!!switch"<<endl;
                solve_switch();
                 pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                            break;
            }
            case semitag:{break;}
        default:error("哇塞!");
            a = nextsym();
        }
    }
    //////////////////////////////////////((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
    else
    {//int st_use;
        pos1 = pos;
        a = nextsym();
if(ish){mipsstart();
        if(a == consttag){  //cout<<"inside successfully"<<endl;
                            a = solve_const(a);

                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;

                          //  a = nextsym();

                            }
    //    cout<<"a := "<<a<<' '<<chartag<<' '<<inttag<<endl;
        if(a == chartag || a == inttag)
            {//cout<<"inside successfully2"<<endl;
            a = solve_statement(a);
                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
        //a = nextsym();
        }
        if(!tab[tabpos].ret)
        st_use = tab[tabpos].addr+tab[tabpos].size;
        else st_use = 2;
        //cout<<"ST_USE!"<<st_use;
}
        //cout<<"________________________________"<<endl;
        while(a != RPtag && a != 0)
        {
            //cout<<"__________________________________"<<endl;
        //cout<<a<<endl;
        storeposition = st_use;
        cout<<"SP:"<<storeposition<<' '<<st_use<<"wwwwwwwwwwwwwww"<<endl;
        switch (a)
        {
        case iftag:
            {
                cout<<"if"<<endl;
                solve_if();
                //cout<<"eeeeeeeeeeeeennnnnnnnnnnnnnnnnnndddddddddddd"<<endl;
                //cout<<code[pos - 3]<<code[pos - 2]<<code[pos - 1]<<endl;
                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case whiletag:
            {
                cout<<"while"<<endl;
                solve_while();
                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case idtag:
            {
                cout<<"id"<<endl;
    //            cout<<"emmmmmmmm"<<endl;
                int type = find_tab(id);
                int PO = tab_pos;
                if(type == voidtag || type == intretag || type == charretag)
                {
                    int i;
                    emitcallpre();
                    if(tab[PO].size != 0)
                    {
                     //   cout<<tab[PO].size<<' '<<tab[PO].name<<' '<<type<<' '<<voidtag<<endl;
                        storeposition ++;
                        int ss = storeposition + 1;
                        int ss1 = ss;
                        a = nextsym();
                        if(a != lpartag)error("函数调用缺少左括号!!!!!");
                        for(i = 1;i <= tab[PO].size;i ++)
                        {
                            storeposition = ss;
                            ss = storeposition + 1;
                            a = solve_expression();
                            //mipsfillpos(i-1,ss);
                            storeposition = ss;
                            if(a != commatag && i != tab[PO].size)error();
                        }
                        for(i = ss1+1;i <= ss;i ++)
                        {
                            mipsfillpos(i-ss1-1,i);
                        }
                            int ssv,ssd;
                        for(int j = PO;tab[j].depth == 1;j ++)
                        {
                            ssv = tab[j].addr + ((tab[j].ret)?0:tab[j].size);
                        }

                        if(a != rpartag)error("函数调用缺少右括号");
                       // st_use = ssd;

                    }emitcall(PO);
                        emitrere();
                        a = nextsym();
                        if(a != semitag)error("函数调用缺少分号");

                }
                else
                 solve_assign();

                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case printftag:
            {
                cout<<"printf"<<endl;

                solve_printf();
                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case scanftag:
            {
                cout<<"scanf"<<endl;
                solve_scanf();
                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case returntag:
            {
                cout<<"return"<<endl;
                solve_return();
                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case LPtag:
            {
              //  cout<<"LP"<<endl;
              pos = pos1;
                a = solve_sentence();
                                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                break;
            }
        case switchtag:
            {
                solve_switch();
                 pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
                            break;
            }
            case semitag:{break;}
        default:error("哇塞!");

        }a = nextsym();//cout<<a<<' '<<RPtag<<' '<<pos<<endl;
        }if(a != RPtag){error();}
        //cout<<line[pos]<<endl;
    }
    if(ish)emitmipsreturn();
    return a;
}






void solve_all()
{
    //cout<<"fff"<<endl;
    emitcallmain();
    emitjmain();

    int a = nextsym();
    int pos2,pos1;
    depth = 0;
        if(a == consttag){ // cout<<"inside successfully"<<endl;
                            a = solve_const(a);

                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;

                          //  a = nextsym();

                            }
        if(a == chartag || a == inttag)
            {
            a = solve_statement(a);
                            pos2 = pos;
                            for(int i = pos1;i < pos2;i ++)
                                cout<<code[i];
                            cout<<endl;
                            pos1 = pos2;
        //a = nextsym();
        }
        depth = 1;
        while(a == voidtag || a == inttag || a == chartag)
        {

            int gg = a;
            a = nextsym();
            if(a != idtag && a != maintag)error();
            if(a != maintag)
            {
               solve_statement_strong(gg);
               emitreturn();
                push_tab();
            //cout<<"歪歪歪歪歪歪"<<endl;
            //cout<<a<<' '<<voidtag<<endl;
            }

            else
            {
                cout<<"now main!"<<endl;
            if(gg != voidtag)error();
              a = nextsym();
              if(a != lpartag)error();
              a = nextsym();
              if(a != rpartag)error();
              emitmaintag();
              solve_sentence(1);
              break;
            }

            //if(a == maintag)break;
            a = nextsym();
            //cout<<a<<endl;
        }
        emitend();
}














void outputcode()
{
    for(int i = 1;i <= codepos;i ++)
    {
        cout<<code1[i].type<<' '<<code1[i].pos1<<' '<<code1[i].pos2<<' '<<code1[i].idname<<' '<<code1[i].pos3<<endl;

    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{

    input();
    solve_line();
    fp = fopen("MIPS1.txt","w");
   // freopen("ans.txt","w",stdout);
    solve_all();
    //word_temp();
    //freopen("code_mid.txt","w",stdout);
    cout<<"---------------------------code start!---------------------------------"<<endl;
    outputcode();
    return 0;
}
