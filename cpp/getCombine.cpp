#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>

typedef char ELE_TYPE;
#define ELE_FMT "%c"

//int g_count=0;

//元素类型和格式符号使用宏定义,很容易改为其他数据类型，如数组类型改为int，则格式符改为"%d ".
void printCombo(int idx_arr[], ELE_TYPE eArr[],int m)
{
    int i;
    //g_count++;
    //return ;
    for (i=0;i<m;i++)
        printf(ELE_FMT,eArr[idx_arr[i]]);
    printf("\n");
}

// 递归形式的求组合数的函数combos,使用回溯法，求从n个元素中取m个元素的所有组合
// 取到元素的序号保存在数组idx_arr[]中，以递增方式排列，每个序号的范围为从0到n-1
// level为递归深度,取值范围为0到m-1,当level==m-1时, 所有的m个元素已经取到，打印这m个元素
// combos(sizeof(eArr)/sizeof(ELE_TYPE),M,idx_arr, eArr, 0); //枚举所有6中取3的组合

void combos(int n, int m, int idx_arr[], ELE_TYPE eArr[], int level )
{
    int i,begin,end;
    if (level==0)
        begin=0;
    else
        begin=idx_arr[level-1]+1;

    end=n-m+level;
    for (i=begin;i<=end;i++)
    {
        idx_arr[level]=i;
        if ( level==m-1)
            printCombo(idx_arr,eArr,m);     //打印这m个个元素
        else
            combos(n,m,idx_arr,eArr,level+1); //继续取一个元素
    }
}


// 迭代形式的求组合数的子程序，该函数用于求n个元素中取m个元素的所有组合
// 取到元素的序号保存在数组idx_arr[]中，以递增方式排列，每个序号的范围为从0到n-1
// 其算法实质是不断地生成一个又一个的组合数，每次迭代对idx_arr中某个元素做更新操作

// 在该子程序中，2个重要的变量mode和i用于控制更新操作，
//   mode表示更新模式，其值为M_FILL或者M_INC。
//   M_FILL表示填充模式，当mode为此模式，元素idx_arr[i]的值总是被设置为比上级元素idx_arr[i-1]大1的数
//   M_INC 表示增量模式，当mode为此模式，元素idx_arr[i]的值总是递增1个单位

//关于“超限”，对于从n个元素中任取m个元素，取到的每个元素的序号是0到n-1
// 我们把取到的元素的序号按照增序排列，存入idx_arr数组
// 例，当n=5,m=3时，如果取到的最后一个元素的序号大于4，或者取到的倒数第2个元素大于3，我们称之为超限。
// 更一般的，取到的idx_arr[i] > n-m+i，则为超限

// 这个子程序用到5个if和一个while，总共6次比较，显然，其逻辑要比上面的那个递归版本复杂的多。
// 凡事有利就有弊，这个子程序的性能要比上面的递归版本好，
// 我的试验表明，将输出子程序printCombo改为只做一次整数加法，当n=28，m=14，迭代版本的性能是递归版本的130%

#define M_FILL 0   //填充模式
#define M_INC  1   //递增模式

void IterativeCombos(int n, int m, int idx_arr[], ELE_TYPE eArr[] )
{
    int i=0;  
    int mode=M_FILL;

    while (i>=0)
    {
        if (mode==M_FILL)   //填充模式
        {
            if (i==0)
                idx_arr[0]=0;
            else
                idx_arr[i] = idx_arr[i-1]+1;

            if (i == m-1)   //当前焦点已经达到最大深度
            {
                printCombo(idx_arr,eArr,m); //打印这个包含m个元素的组合
                mode=M_INC; //切换为增量模式    
            }
            else            //没有达到最大深度
                i++;        //继续填充下级节点
        }
        else                //增量模式
        {
            idx_arr[i]++;   //焦点元素递增

            if ( idx_arr[i] > n-m+i ) //已经超限
                i--;
            else
            {
                if (i==m-1)     //当前焦点已经达到最大深度
                    printCombo(idx_arr,eArr,m); //打印这个包含m个元素的组合
                else
                {
                    i++;         //继续填充下级节点
                    mode=M_FILL; //切换到填充模式
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int i;

#define N  6
#define M  5

    ELE_TYPE eArr[N]; //定义6个数组的数组，
    int idx_arr[M];   //取到的3个元素的需要放在数组idx_arr中

    for (i=0;i<sizeof(eArr)/sizeof(ELE_TYPE);i++) //数组的元素为'A'到'F'
        eArr[i]='A'+i;

    combos(sizeof(eArr)/sizeof(ELE_TYPE),M,idx_arr, eArr, 0); //枚举所有6中取3的组合

    //IterativeCombos(sizeof(eArr)/sizeof(ELE_TYPE),M,idx_arr, eArr); //枚举所有6中取3的组合

    return 0;
}

