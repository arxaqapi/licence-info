#<>
def add_mod2(nb1, nb2):
    return (nb1 + nb2) % 2

def deg(poly):
    degCount = 0
    taille = len(poly)
    i = taille - 1

    while poly[i] == 0 and i > 0:
        degCount -= 1
        i -= 1

    if (i == 0) or (poly == []):
        return 0
    return degCount + taille - 1
"""
a = [0,0,1,0,0,0,0]
print(deg(a))
"""

def coeff(poly):
    taille = len(poly)
    if taille == 0:
        return 0
    return 1  ## pour Z / 2Z

def is_null_poly(poly):  # ex 4
    if coeff(poly) == 1:
        return False
    return True

def add_poly(poly1, poly2): ## ok ex 5
    tailleP1 = len(poly1)
    tailleP2 = len(poly2)
    poly3 = []
    if tailleP1 > tailleP2:
        tailleP1, tailleP2 = tailleP2, tailleP1

    for i in range(tailleP1):
        poly3.append(add_mod2(poly1[i], poly2[i]))

    poly3.extend(poly2[tailleP1:])
    return poly3
#print(add_poly([0,1,1,0], [1,0,1,1,0]))

def diff_poly(poly1, poly2):
    return add_poly(poly1, poly2)

def mult_poly(poly1, poly2):
    polInt = []
    polFin = []
    tailleP1 = len(poly1)
    for i in poly1:
        for j in poly2:
            polInt.append(poly1[i] * poly2[j])
    
    for i in range(tailleP1):
        addi = 0
        for j in range(tailleP1 - 1):
            addi += add_mod2(polInt[j * (tailleP1-1)], polInt[(j+1) * (tailleP1-1)])
        polFin.append(addi)
    return polFin

print(mult_poly([0,1,1], [1,0,1,1]))