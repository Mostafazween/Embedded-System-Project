int  power(int base,int exp)
{
    int count=1,power;
    if(exp==0)
    {
        power=1;
    }
    else
    {
    power=base;
    while(count<exp)
    {

        power=power*base;
        count++;
    }
    }
    return power;
}
