def fac(n):
   if n==0:
    return 1
   else:
    return n*fac(n-1)
n=int(input("Introduce el número a calcular factorial"))
resultado=fac(n)
print("El factorial es", resultado)