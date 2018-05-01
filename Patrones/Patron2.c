int main()
{
  int posu,i,j;  
  posu=0;
  i=0;
  j=0;  
  for (i=0; i<=4;i++)
  {
      for (j=0; j<=4;j++)
      {
         if (j == posu)
             printf("%c",'u');
         else
             printf("%c",'n');
      }
      posu++;
      printf("%c",'.');
  }
  printf("\n");
  
  system("PAUSE");	
  return 0;
}
