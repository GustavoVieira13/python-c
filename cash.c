//Programa que exibe o número mínimo possível de moedas a serem oferecidas como troco
//Gustavo Vieira

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main()
{
    float change = 0;
    int cents = 0;
    int coins;
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    int r_quarters = 0;
    int r_dimes = 0;
    int r_nickels = 0;
    int r_pennies = 0;
    int sec_dimes = 0;
    int r_sec_dimes = 0;
    int sec_nickels = 0;
    int r_sec_nickels = 0;
    int sec_pennies = 0;
    int thr_nickels = 0;
    int r_thr_nickels = 0;
    int thr_pennies = 0;
    int frth_pennies = 0;

    do
    {
        change = get_float("Change owed: ");
    }
    while (change <= 0);

    cents = round(change * 100);                    //converts the value in bucks for cents
    /////////////////////////////////////
    if (cents >= 25)
    {
        quarters = floor(cents / 25);               //value above 0.25
        r_quarters = cents % 25;
    }

    else if (cents >= 10 && cents < 25)             //value between 0.10 and 0.25
    {
        dimes = floor(cents / 10); //
        r_dimes = cents % 10;
        //printf("%f\n", floor(dimes));
    }

    else if (cents >= 5 && cents < 10)              //value between 0.05 and 0.10 
    {
        nickels = floor(cents / 5); //
        r_nickels = cents % 5;
    }

    else if (cents >= 1 && cents < 5)               //value between 0.01 and 0.05
    {
        pennies = cents;
    }

    /////////////////////////////////////
    if (r_quarters >= 10 && r_quarters < 25)        //second row (0.25): remainder above 0.10
    {
        sec_dimes = floor(r_quarters / 10);       
        r_sec_dimes = r_quarters % 10;
    }

    else if (r_quarters >= 5 && r_quarters < 10)    //second row (0.25): remainder between 0.05 and 0.10
    {
        sec_nickels = floor(r_quarters / 5);
        r_sec_nickels = r_quarters % 5;
    }

    else if (r_quarters >= 1 && r_quarters < 5)      //second row (0.25): remainder between 0.01 and 0.05
    {
        pennies = r_quarters;
    }
    
    /////////////////////////////////////
    if (r_sec_dimes >= 5 && r_sec_dimes < 10)
    {
        thr_nickels = floor(r_sec_dimes / 5);        //third row (0.25): remainder above 0.05
        r_thr_nickels = r_sec_dimes % 5;
    }

    else if (r_sec_dimes >= 1 && r_sec_dimes < 5)    //third row (0.25): remainder between 0.01 and 0.05
    {
        thr_pennies = r_sec_dimes;
    }

    /////////////////////////////////////
    if (r_thr_nickels >= 1  && r_thr_nickels < 5)     //fourth row (0.25): remainder above 0.01
    {
        frth_pennies = r_thr_nickels;
    }


    /////////////////////////////////////
    /////////////////////////////////////
    if (r_dimes >= 5 && r_dimes < 10)
    {
        sec_nickels = floor(r_dimes / 5);            //second row (0.10): remainder above 0.05
        r_sec_nickels = r_dimes % 5;
    }

    else if (r_dimes >= 1 && r_dimes < 5)            //second row (0.10): remainder between 0.01 and 0.05
    {
        sec_pennies = r_dimes;
    }

    ///////////////////////////////////
    //////////////////////////////////
    if (r_sec_nickels >= 1 && r_sec_nickels < 5)     //third row (0.10): remainder above 0.01
    {
        thr_pennies = r_sec_nickels;
    }
    
    ///////////////////////////////////
    ///////////////////////////////////
    ///////////////////////////////////
    if (r_nickels >= 1 && r_nickels < 5)             //second row (0.05): remainder above 0.01
    {
        pennies = r_nickels;
    }
    

    coins = quarters + dimes + nickels + pennies + sec_dimes + sec_nickels + sec_pennies + thr_nickels + thr_pennies + frth_pennies;

    printf("%i\n", coins);

    return 0;

}
