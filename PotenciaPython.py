def pot(b,e):
  if e==0:
    return 1
  else:
    return b*pot(b,e-1)
x=int(input("Ingrese la base:"))
y=int(input("Ingrese el exponente:"))
r=pot(x,y)
print("El resultado: ", r)
