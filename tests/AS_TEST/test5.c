void myproc(int* x)
{
  *x = 5;
}

void main ()
{
  int myarr[10];
  myarr[0] = 1;
  myproc(myarr[5]);
  printf("%d",myarr[0]);
}
