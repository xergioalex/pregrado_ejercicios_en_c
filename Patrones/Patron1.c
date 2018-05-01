int main()
{
  int posuizq, posuder, i,j;  
  posuizq=2;
  posuder=2;
  i=0;
  j=0;  
  for (i=0; i<=2;i++)
  {
      for (j=0; j<=4;j++)
      {
         if (j >= posuizq & j <= posuder)
             printf("%c",'u');
         else
             printf("%c",'n');
      }
      posuizq--; 
      posuder++;
      printf("%c",'.');
  }
  printf("\n");
  
  system("PAUSE");	
  return 0;
}
