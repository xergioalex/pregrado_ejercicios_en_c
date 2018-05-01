int primo(int numero);

int main()
{
  int x,raiz;
  
  printf("Por favor ingrese un numero: ");  
  scanf("%i",&x);
  if(primo(x)== 1)
      printf("NO es primo");           
  else
      printf("Es primo");           
  printf("\n");
  system("PAUSE");	
  return 0;
}

int primo(int numero)
{
    int i,raiz,primo;
    raiz=sqrt(numero);
    for (i=2;i<=raiz;i++)
    {
        primo=i*(numero/i);
        if (primo == numero)
           return 1;
    }
}   


