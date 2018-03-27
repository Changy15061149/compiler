/*
#include "main.cpp"
#define intarraytype 50
#define chararraytype 51
#define array_maxpos 1000
using namespace std;

void solve_if();
void solve_simple();
void solve_expression();
void solve_assign();
void solve_while();
void solve_const(int a);
void solve_statement(int a);
void solve_sentence();
void solve_printf();
void solve_scanf();
void solve_return();

void filltab()
{

}
void emit()
{

}
int find_tab()
{
    return idtag;
}
void solve_if()
{
    int tag;
    tag = nextsym();
    if(tag != lpartag)
    {
       // error();
    }
    solve_expression();
    nextsym();
    //emit();//生成跳转语句
    solve_sentence();
    tag = nextsym();
    //if(tag != elsetag){error;}
    solve_sentence();
    //在这里需要补充跳转后的位置
}

void solve_simple()
{
    int a = nextsym();
    if(a == minustag)
    {
        emit();
        next();
    }
    if(a != idtag && a != numtag)error();
    int type = find_tab();
    if(type == intarraytype || type == chararraytype)
    {
        a = nextsym();
        if(a != lmidtag)error();
        a = nextsym();
        if(a != numtag || Int_Value > array_maxpos)
        {
            error();
        }
        a = nextsym();
        if(a != rmidtag)error();
    }
    emit();
    a = nextsym();
    while(a == lpartag || a == startag || a == divtag)
    {
        if(a == lpartag)
        {
            solve_expression();
            //a = nextsym();
            if(a != rpartag)error();
        }
        else if(a == startag || a == divtag)
        {
           nextsym();
        if(type == intarraytype || type == chararraytype)
        {
            a = nextsym();
            if(a != lmidtag)error();
            a = nextsym();
            if(a != numtag || Int_Value > array_maxpos)
            {
                error();
            }
            a = nextsym();
            if(a != rmidtag)error();
        }
        else error();
        }
    }

}
void solve_expression()
{
    int a = nextsym();
    if(a == minustag)
    {
        emit();
        next();
    }
    if(a != idtag && a != numtag)error();
    int type = find_tab();
    if(type == intarraytype || type == chararraytype)
    {
        a = nextsym();
        if(a != lmidtag)error();
        a = nextsym();
        if(a != numtag || Int_Value > array_maxpos)
        {
            error();
        }
        a = nextsym();
        if(a != rmidtag)error();
    }
    emit();
    a = nextsym();
    while( a == plustag || a == minustag || a == lpartag || a == startag || a == divtag)
    {
        if(a == lpartag)
        {
            solve_expression();
            //a = nextsym();
            if(a != rpartag)error();
        }
        else if(a == startag || a == divtag)
        {
            solve_simple();
        }
        else
        {
            nextsym();
            //下面是ID类型的,还差整数以及char!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            type = find_tab();
        if(type == intarraytype || type == chararraytype)
        {
            a = nextsym();
            if(a != lmidtag)error();
            a = nextsym();
            if(a != numtag || Int_Value > array_maxpos)
            {
                error();
            }
            a = nextsym();
            if(a != rmidtag)error();
        }
        emit();
        }

    }

}

void solve_assign()
{
    cout<<"第"<<line[pos]<<"行为赋值语句!"<<endl;
    int type = find_tab();
    int a;
    if(type == intarraytype || type == chararraytype)
        {
            a = nextsym();
            if(a != lmidtag)error();
            a = nextsym();
            if(a != numtag || Int_Value > array_maxpos)
            {
                error();
            }
            a = nextsym();
            if(a != rmidtag)error();
        }
        //需要存储下地址之类的
        a = nextsym();
        if(a != equtag)
            error();
        solve_expression();
        emit();

}
void solve_while()
{
    cout<<"第"<<line[pos]<<"行为while语句!"<<endl;
    int a = nextsym();
    if(a != lpartag)error();
    solve_expression();
    a = nextsym();
    if(a != rpartag)
    {
        if(a == equtag)
        {
            emit();
        }
        else if(a == lesstag)
        {
            emit();
        }
        else if(a == leseqtag)
        {
            emit();
        }
        else if(a == moretag)
        {
            emit();
        }
        else if(a == moreeqtag)
        {
            emit();
        }
        else error();
        solve_expression();
        a = nextsym();
        if(a != rpartag)
            error();
        solve_expression();
        emit();
    }


}
void solve_const(int a)
{
    while(a == consttag)
    {
       a = next();
       //记录类型!!!!!!!!!!!!!!!!!!
       a = next();
       if(a != idtag)error();
       a = next();
       if(a != assigntag)error();
       a = next();
       if(a == plustag || a == minustag)
       {
           next();
           if(a != numtag )
           {
                error();
           }
           //if(num == 0)error();
       }//filltab!!!!!!!!!!!!!!!!!!!

       a = next();
       if(a == commatag)
       {
           while(a == commatag)
           {
                a = next();
                if(a != idtag)error();
                a = next();
                if(a != assigntag)error();
                a = next();
                if(a == plustag || a == minustag)
                {
                    next();
                    if(a != numtag )
                    {
                        error();
                    }
           //if(num == 0)error();
                }//filltab
                a = next();
           }
       }
        if(a != semitag)error();
        filltab();
        a = next();
    }

}

void solve_statement(int a)
{

    while(a == inttag || a == chartag)
    {
       a = next();
       if(a != idtag)error();
        a = next();
        if(a == lmidtag)
        {
            a = next();
            if(a != inttag)error();
            //if(int == 0)error()
            a = next();
            if(a != rmidtag)error();
        }//filltab
        if(a == commatag)

       {
           if(a != idtag)error();
        a = next();
        if(a == lmidtag)
        {
            a = next();
            if(a != inttag)error();
            //if(int == 0)error()
            a = next();
            if(a != rmidtag)error();
        }//filltab
       }if(a != semitag)error();
     //  next();       //记录类型!!!!!!!!!!!!!!!!!!
    a = next();

    }

}
void solve_sentence()
{
    int a = nextsym();
    if(a != LPtag)
    {

    }
    else
    {
        if(a == consttag){solve_const(a); a = nextsym();}
        if(a == chartag || a == inttag){solve_statement(a); a = nextsym();}
        while(a != RPtag)
        {


        switch (a)
        {
        case iftag:
            {
                solve_if();break;
            }
        case whiletag:
            {
                solve_while();break;
            }
        case idtag:
            {
                solve_assign();break;
            }
        case printftag:
            {
                solve_printf();break;
            }
        case scanftag:
            {
                solve_scanf();break;
            }
        case returntag:
            {
                solve_return();break;
            }
        case LPtag:
            {
                solve_sentence();break;
            }
        default:error();

        }a = nextsym();
        }
    }
}
*/
