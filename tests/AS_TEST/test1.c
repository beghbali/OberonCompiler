main ()
{
        int a, b, c;
        a = 99;
        b = a + two();
        if (b > 100) 
                printf ("%d\n", b);
}

two ()
{
        return 2;
}
