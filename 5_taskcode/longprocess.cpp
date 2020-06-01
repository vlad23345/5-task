#include "longprocess.h"

LongProcess::LongProcess(int n):n(n)
{

}
void LongProcess::doWork()
{
    for(int i = 0; i <= 1000000000; i++)
    {
    if(i%10000000==0)
    emit send(n,i/10000000);
    }
    emit finished(n);
}
